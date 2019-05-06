#ifndef SQL_H
#define SQL_H

#include <QSqlQueryModel>
#include <QString>
#include <QVector>

class SQL
{
public:
    SQL();

    bool connect();
    bool login(QString, QString);
    QStringList tableFinder();
    QSqlQueryModel * tableData(QString);
    void updateSQL(QString tabel,QString colom, QString input,QString id);
    QStringList RacerFinder();
    QStringList RacerData(QString sql);
};

#endif // SQL_H
