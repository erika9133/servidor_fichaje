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
     *          "date: dd/mm/yyyy"
     *      }
     * }
     */
    QJsonObject login;
    QDateTime date = QDateTime::currentDateTimeUtc();
    //date.setTimeSpec(Qt::UTC);
    login["user"] = user;
    login["pass"] = pass;
    login["type"] = type;
    login["date"] = date.toString("dd.MM.yyyy hh:mm:ss.z");

    QJsonValue value(login);
    QJsonObject message;

    message.insert("login", value);
    QJsonDocument doc;

    doc.setObject(message);
    qStringReturned = doc.toJson(QJsonDocument::Compact);
    return  qStringReturned;
}//end
