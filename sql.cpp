#include "sql.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

SQL::SQL()
{

}

bool SQL::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("pollop.nl");
    db.setPort(16969);
    db.setDatabaseName("formule1");
    db.setUserName("macks");
    db.setPassword("WHRAgNCS6VPMXJNs");
    return db.open();
}

bool SQL::login(QString usrnm, QString psswrd)
{
    QString pw;

    QString loginQuery = "SELECT psswrd FROM formule1.tbllogin WHERE usrnm = \""+usrnm+ "\"";

    //qDebug()<< loginQuery.toLatin1().constData();

    QSqlQuery query(loginQuery.toLatin1().constData());
    while (query.next()) {
        pw = query.value(0).toString();
    }

    if(psswrd == pw && psswrd !="")
    {
        return true;
    }
    else
    {
        return false;
    }
}

QStringList SQL::tableFinder()
{
    QStringList a;
    QString test;
    int teller = 0;

    QString loginQuery = "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE = 'BASE TABLE' AND TABLE_SCHEMA='formule1'";
    QSqlQuery query(loginQuery);


    while (query.next())
    {
        test = query.value(0).toString();
        teller++;
        a<<test;
    }

    //     for(QString &i : arr)
    //     {
    //         qDebug()<<i;
    //     }


    return a;


}

QSqlQueryModel *SQL::tableData(QString table)
{
    QSqlQueryModel *test = new QSqlQueryModel;
    QString searchQuery = "SELECT * FROM formule1."+table;
    QSqlQuery query(searchQuery);

    QSqlRecord rec = query.record();

    qDebug()<<rec.count();

    test->setQuery(query);

    return test;
}

void SQL::updateSQL(QString tabel,QString colom, QString input,QString id)
{
    QString updateQuery = "UPDATE formule1."+tabel+" SET "+colom+" = \""+input+ "\" WHERE ID = "+id;

    //qDebug()<<updateQuery.toLatin1().constData();
    QSqlQuery query(updateQuery.toLatin1().constData());
}

QStringList SQL::RacerFinder()
{
    QStringList a;
    QString test;

    QString racerQuery = "SELECT strAchterNaam FROM formule1.tblpersoon";
    QSqlQuery query(racerQuery);


    while (query.next())
    {
        test = query.value(0).toString();
        a<<test;
    }


    return a;
}

QStringList SQL::RacerData(QString sql)
{

    QSqlQuery query(sql.toLatin1().constData());

    QSqlRecord rec = query.record();

    qDebug()<<rec.count()<<sql.toLatin1().constData();

    QStringList a;

    while(query.next())
    {
        for(int i = 0; i < rec.count(); i++)
        {
            a<<query.value(i).toString();
        }
    }


    return a;
}

