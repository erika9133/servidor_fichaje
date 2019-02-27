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
    static QString ParseMainLoggin(const QString user, const QString pass);
};

#endif // JSON_H
