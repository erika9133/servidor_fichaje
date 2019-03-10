#ifndef JSON_H
#define JSON_H

#include <QString>
/*************
 * Static class to parse and un-parse json to qstrings
 ************/
class JSON
{
public:
    explicit JSON();
    static QString ParseMainLogin(const QString &user, const QString &pass);
    static QString ParseLogin(const QString &user, const QString &pass, const QString &type);
};

#endif // JSON_H
