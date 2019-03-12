#ifndef JSON_H
#define JSON_H

#include <QString>
#include <QVariantMap>
/*************
 * Static class to parse and un-parse json to qstrings
 ************/
class JSON
{
public:
    explicit JSON();
    static QString parseMainLogin(const QString &user, const QString &pass);
    static QString parseCreateUser(const QString &name, const QString &pass);
    static QVector<QString> unParseResponse(const QString &message);
};

#endif // JSON_H
