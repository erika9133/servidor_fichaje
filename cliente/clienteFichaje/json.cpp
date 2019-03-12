#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDateTime>
#include <QDebug>
#include "json.h"

JSON::JSON(){}//end

QString JSON::ParseMainLogin(const QString &user, const QString &pass)
{
    QString qStringReturned = "";
    ///Json Struct
    /*{
     *      "mainlogin":
     *      {
     *          "pass":"xxxxxxx",
     *          "user":"xxxxxxx"
     *      }
     * }
     */
    ///Create login object. Contains pass and user
    QJsonObject login;
    login["user"] = user;
    login["pass"] = pass;
    ///Value contains login object and is contained by messaje
    QJsonValue value(login);
    ///Message contains type of json as well
    QJsonObject message;
    ///Message is the "root" item in the document.
    message.insert("mainlogin", value);
    QJsonDocument doc;
    doc.setObject(message);
    ///Return QString message
    qStringReturned = doc.toJson(QJsonDocument::Compact);
    return  qStringReturned;
}//end

QString JSON::ParseLogin(const QString &user, const QString &pass, const QString &type)
{
    QString qStringReturned = "";
    ///Json Struct
    /*{
     *      "login":
     *      {
     *          "pass":"xxxxxxx",
     *          "user":"xxxxxxx",
     *          "type": in/out",
     *      }
     * }
     */
    QJsonObject login;
    ///Not using date in client. Insert in db.
    //QDateTime date = QDateTime::currentDateTime();
    login["user"] = user;
    login["pass"] = pass;
    login["type"] = type;
    //login["date"] = date.toString("dd.MM.yyyy hh:mm:ss.z");

    QJsonValue value(login);
    QJsonObject message;

    message.insert("login", value);
    QJsonDocument doc;

    doc.setObject(message);
    qStringReturned = doc.toJson(QJsonDocument::Compact);
    return  qStringReturned;
}//end

QVector<QString> JSON::unParseResponse(const QString &message)
{
    QVector<QString> vectorReturned = {};
    ///Json Struct
    /*{
     *      "response":
     *      {
     *          "response1":"value",
     *          "response2":"value",...
     *      }
     * }
     */
    ///Firt it nedeed to be qByteArray
    QByteArray byteArray = message.toUtf8();

    if(!byteArray.isEmpty()) ///Check QByteArray
    {
        QJsonParseError *error = nullptr;
        QJsonDocument doc = QJsonDocument::fromJson(byteArray, error);
        if(doc.isObject() && !error->NoError){ ///Check document
            QJsonObject rootObj = doc.object();
            QVariantMap rootMap = rootObj.toVariantMap();
            QVariantMap map = rootMap["response"].toMap();
            if(!map.empty())
            {
                QVariantMap::const_iterator i = map.constBegin();
                    while (i != map.constEnd())
                    {
                        //qDebug() <<"key" <<i.key() << "value" << i.value();
                        qDebug() << i.value().toString();
                        vectorReturned.push_back(i.value().toString());
                        ++i;
                    }//end while iterate




               /*///Get two elements that we need it
                QString pass = map["pass"].toString();
                QString user = map["user"].toString();
                QString type = map["type"].toString();
                //QString date = map["date"].toString();
                pass = cleanJson(pass);
                user = cleanJson(user);
                type = cleanJson(type);

                //date = cleanJson(date);
                if(!user.isEmpty() && !pass.isEmpty())
                {
                    vectorReturned.push_back(user);
                    vectorReturned.push_back(pass);
                    vectorReturned.push_back(type);
                    //vectorReturned.push_back(date);
                }//end if
            }//end if map
        }else{
            qDebug() << error->error;
        }//end if eslse document
    }//end if bytearray*/
            }}}
    return vectorReturned;
}//end
