#include <QJsonDocument>
#include <QJsonParseError>

#include <QJsonArray>
#include <QJsonValue>
#include <QVariantMap>
#include <QDebug>
#include "json.h"

JSON::JSON()
{

}

QJsonObject isValid(const QString *message)
{

}


QVector<QString> JSON::unParseMainLogin(const QString *message)
{
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

        QJsonParseError jerror;

        ///Open a json document with the qbytearray
        QJsonDocument doc = QJsonDocument::fromJson(byteArray);

        ///Get the root object
        QJsonObject rootObj = doc.object();
        ///QVarianMap is QMap<String>,<QVariant>. Get the root map
        QVariantMap rootMap = rootObj.toVariantMap();
        ///Find the inner map inside mainlogin element
        QVariantMap map = rootMap["mainlogin"].toMap();
        ///Get two elements that we need it
        QString pass = map["pass"].toString();
        QString user = map["user"].toString();
        qDebug() << user << pass;

        QVector<QString> temp;
        return temp;
    }

    /*2

    QString qStringReturned = "";

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
    */
}
