#ifndef SQL_H
#define SQL_H

#include <QDate>
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
    QStringList circuitFinder();
    QStringList finishFInder();
    QStringList RacerData(QString sql);

    int createNewRace(QString Race,int raceNumber, QDate date,QString pole, QString fastestLap);
    void spInsertCoureur(QString persoon,int raceID,int pos,QString type);
    void spDeleteRecord(QString tabel,int ID);

    QByteArray getFoto(QString);
};

#endif // SQL_H
