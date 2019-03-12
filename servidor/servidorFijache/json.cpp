#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariantMap>
#include <QDebug>
#include "json.h"

JSON::JSON(){}

QString JSON::findTypeMessage(const QString *message)
{
    QString stringReturned = "";

    QByteArray byteArray = message->toUtf8();

    if(!byteArray.isEmpty()) ///Check QByteArray
    {
        QJsonParseError *error = nullptr;
        ///Open a json document with the qbytearray
        QJsonDocument doc = QJsonDocument::fromJson(byteArray, error);
        //if (doc.isObject() && !error->NoError){ ///Check document
        ///Get the root object
        QJsonObject rootObj = doc.object();
        ///Find the first key element. (the info element)
        stringReturned = rootObj.keys().at(0);
        }
    return stringReturned;
}//end


QVector<QString> JSON::unParseMainLogin(const QString *message)
{
    QVector<QString> vectorReturned = {};
    ///Json Struct
    /*
    * {
    *      "mainlogin":
    *      {
    *          "pass":"xxxxxxx",
    *          "user":"xxxxxxx"
    *      }
    * }
    */
    ///Firt it nedeed to be qByteArray
    QByteArray byteArray = message->toUtf8();

    if(!byteArray.isEmpty()) ///Check QByteArray
    {
        QJsonParseError *error = nullptr;
        ///Open a json document with the qbytearray
        QJsonDocument doc = QJsonDocument::fromJson(byteArray, error);
        if(doc.isObject() && !error->NoError){ ///Check document
            ///Get the root object
            QJsonObject rootObj = doc.object();
            ///QVarianMap is QMap<String>,<QVariant>. Get the root map
            QVariantMap rootMap = rootObj.toVariantMap();
            ///Find the inner map inside mainlogin element
            QVariantMap map = rootMap["mainlogin"].toMap();
            if(!map.empty())
            {
                ///Get two elements that we need it
                QString pass = map["pass"].toString();
                QString user = map["user"].toString();
                pass = cleanJson(pass);
                user = cleanJson(user);
                if(!user.isEmpty() && !pass.isEmpty())
                {
                    vectorReturned.push_back(user);
                    vectorReturned.push_back(pass);
                }//end if
            }//end if map
        }else{
            qDebug() << error->error;
        }//end if eslse document
    }//end if bytearray
    return vectorReturned;
}//end

QVector<QString> JSON::unParseLogin(const QString *message)
{
    QVector<QString> vectorReturned = {};
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
    ///Firt it nedeed to be qByteArray
    QByteArray byteArray = message->toUtf8();

    if(!byteArray.isEmpty()) ///Check QByteArray
    {
        QJsonParseError *error = nullptr;
        ///Open a json document with the qbytearray
        QJsonDocument doc = QJsonDocument::fromJson(byteArray, error);
        if(doc.isObject() && !error->NoError){ ///Check document
            ///Get the root object
            QJsonObject rootObj = doc.object();
            ///QVarianMap is QMap<String>,<QVariant>. Get the root map
            QVariantMap rootMap = rootObj.toVariantMap();
            ///Find the inner map inside mainlogin element
            QVariantMap map = rootMap["login"].toMap();
            if(!map.empty())
            {
                ///Get two elements that we need it
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
    }//end if bytearray
    return vectorReturned;
}//end

QString JSON::response(const QMap<QString, QString> &values)
{
    QString stringReturned = "";
    ///Json Struct
    /*{
     *      "response":
     *      {
     *          "key":"value",
     *          "key":"value",...
     *      }
     * }
     */

    QJsonObject response;
    QMap<QString,QString>::const_iterator i = values.constBegin();
    while (i != values.constEnd())
    {
        response[i.key()] = i.value();
        ++i;
    }//end while iterate

    QJsonValue value(response);
    QJsonObject message;

    message.insert("response", value);
    QJsonDocument doc;

    doc.setObject(message);
    stringReturned = doc.toJson(QJsonDocument::Compact);
    return stringReturned;
}//end

QString JSON::cleanJson(QString toClean)
{
    QString stringReturned = "";
    ///Remove odd char
    stringReturned = toClean.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_€”+=|:;<>«»,.?/{}\'\"")));
    return stringReturned;
}
