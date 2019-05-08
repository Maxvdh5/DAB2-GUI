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



    QString loginQuery = "SELECT strPassword FROM formule1.tbluser WHERE strUsername = \""+usrnm+ "\"";

    QSqlQuery query;
    query.prepare(loginQuery);
    //query.addBindValue(usrnm);
    query.exec();


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
    QString updateQuery = "CALL spUpdateTable(\""+tabel+"\",\""+colom+"\",\""+input+"\","+id+")";

    qDebug()<<updateQuery.toLatin1().constData();
    QSqlQuery query(updateQuery.toLatin1().constData());
}

QStringList SQL::RacerFinder()
{
    QStringList a;
    QString test;

    QString racerQuery = "SELECT * FROM formule1.vwGetCoureur";
    QSqlQuery query(racerQuery);


    while (query.next())
    {
        test = query.value(0).toString();
        a<<test;
    }


    return a;
}

QStringList SQL::circuitFinder()
{
    QStringList a;
    QString test;

    QString racerQuery = "SELECT strNaam from formule1.tblcircuit";
    QSqlQuery query(racerQuery);


    while (query.next())
    {
        test = query.value(0).toString();
        a<<test;
    }


    return a;
}

QStringList SQL::finishFInder()
{
    QStringList a;
    QString test;

    QString racerQuery = "SELECT * FROM formule1.tblfinishtype";
    QSqlQuery query(racerQuery);


    while (query.next())
    {
        test = query.value(1).toString();
        a<<test;
    }


    return a;
}

QStringList SQL::RacerData(QString sql)
{
    QSqlQuery query(sql.toUtf8().constData());

    QSqlRecord rec = query.record();

    qDebug()<<rec.count()<<sql.toUtf8().constData();

    QStringList a;

    while(query.next())
    {
        for(int i = 0; i < rec.count(); i++)
        {
            a<<query.value(i).toString().toUtf8();
        }
    }


    return a;
}

int SQL::createNewRace(QString Race, int raceNumber, QDate date,QString pole, QString fastestLap)
{
    int year = date.year();
    int a;

    QString racerQuery = "SELECT fnInsertRace("+QString::number(year)+",\""+Race+"\","+QString::number(raceNumber)+",\""+date.toString("yyyy-MM-dd")+"\",\""+pole+"\",\""+fastestLap+"\")";
    qDebug()<<racerQuery.toUtf8().constData();
    QSqlQuery query(racerQuery);

    while(query.next())
    {
        a=query.value(0).toInt();
    }


    return a;

}

void SQL::spInsertCoureur(QString persoon, int raceID, int pos,QString type)
{
    QString coureur = "CALL spInsertPuntenCoureur(\""+persoon+"\","+QString::number(raceID)+","+QString::number(pos)+",\""+type+"\")";
    qDebug()<<coureur.toUtf8().constData();
    QSqlQuery query(coureur);
}

void SQL::spDeleteRecord(QString tabel, int ID)
{
    QString deleteit = "CALL spDeleteRecord(\""+tabel+"\","+QString::number(ID)+")";
    qDebug()<<deleteit.toUtf8().constData();
    QSqlQuery query(deleteit);
}

QByteArray SQL::getFoto(QString naam)
{
    QByteArray ba1;
    QString foto = "SELECT blobFoto FROM formule1.tblpersoon WHERE strAchternaam = \""+naam+"\"";
    QSqlQuery query;
    query.exec(foto);
//    model.setQuery(query);

//    index = model.index(0,0);
    while(query.next())
    {
         ba1 = query.value( 0 ).toByteArray();
    }

    qDebug()<<ba1;

    return ba1;
}

