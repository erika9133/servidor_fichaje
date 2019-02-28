#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include "json.h"

JSON::JSON(){}//end

QString JSON::ParseMainLogin(const QString user, const QString pass) //pasar puntero
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
