#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include "json.h"

JSON::JSON(){}//end

QString JSON::ParseMainLoggin(const QString user, const QString pass)
{
    QString qStringReturned = "";
    ///Json Struct
    /*{
     *      "mainloggin":
     *      {
     *          "pass":"xxxxxxx",
     *          "user":"xxxxxxx"
     *      }
     * }
     */
    ///Create login object. Contains pass and user
    QJsonObject loggin;
    loggin["user"] = user;
    loggin["pass"] = pass;
    ///Value contains login object and is contained by messaje
    QJsonValue value(loggin);
    ///Message contains type of json as well
    QJsonObject message;
    ///Message is the "root" item in the document.
    message.insert("mainloggin", value);
    QJsonDocument doc;
    doc.setObject(message);
    ///Return QString message
    qStringReturned = doc.toJson(QJsonDocument::Compact);
    return  qStringReturned;
}//end
