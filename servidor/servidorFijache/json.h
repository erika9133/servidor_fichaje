#ifndef JSON_H
#define JSON_H

#include <QString>
#include <QVector>


/*************
 * Static class to parse and un-parse json to qstrings
 ************/
class JSON
{

public:
    JSON();
    ~JSON();
    static QString findTypeMessage(const QString *message);
    static QVector<QString> unParseMainLogin(const QString *message);
    static QVector<QString> unParseLogin(const QString *message);
    static QString cleanJson(QString toClean);
};

#endif // JSON_H
