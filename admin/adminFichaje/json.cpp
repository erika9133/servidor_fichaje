#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDateTime>
#include <QDebug>
#include "json.h"

JSON::JSON(){}//end

QString JSON::parseMainLogin(const QString &user, const QString &pass)
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

QString JSON::parseCreateUser(const QString &name, const QString &pass)
{
    QString qStringReturned = "";
    ///Json Struct
    /*{
     *      "createUser":
     *      {
     *          "name":"xxxxxxx",
     *          "pass":"xxxxxxx",
     *      }
     * }
     */
    QJsonObject login;
    ///Not using date in client. Insert in db.
    login["name"] = name;
    login["pass"] = pass;

    QJsonValue value(login);
    QJsonObject message;

    message.insert("createUser", value);
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
            }}}
    return vectorReturned;
}//end
