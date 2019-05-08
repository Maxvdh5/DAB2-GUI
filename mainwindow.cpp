#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDate>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    this->labels = {ui->tl1,ui->tl2,ui->tl3,ui->tl4,ui->tl5,ui->tl6};
    this->inputs = {ui->le1,ui->le2,ui->le3,ui->le4,ui->le5,ui->le6};
    this->Result = {ui->cb1,ui->cb2,ui->cb3,ui->cb4,ui->cb5,ui->cb6,ui->cb7,ui->cb8,ui->cb9,ui->cb10,ui->cb11,ui->cb12,ui->cb13,ui->cb14,ui->cb15,ui->cb16,ui->cb17,ui->cb18,ui->cb19,ui->cb20};
    this->Finish = {ui->cbFinish1,ui->cbFinish2,ui->cbFinish3,ui->cbFinish4,ui->cbFinish5,ui->cbFinish6,ui->cbFinish7,ui->cbFinish8,ui->cbFinish9,ui->cbFinish10,ui->cbFinish11,ui->cbFinish12,ui->cbFinish13,ui->cbFinish14,ui->cbFinish15,ui->cbFinish16,ui->cbFinish17,ui->cbFinish18,ui->cbFinish19,ui->cbFinish20};
    this->country = {ui->invCountry,ui->invCountry2};
    checkConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkConnection()
{
    if(!sqlHandeler.connect())
    {
        pop.loginMessage();
    }
}

void MainWindow::fillLineEdit(int index )
{
    int CollumCount = ui->tableView->model()->columnCount();
    if(CollumCount > 6)
    {
        CollumCount = 6;
    }

    for(int i = 0; i< 6; i++)
    {
        if(i<CollumCount)
        {
            this->labels[i]->setText(ui->tableView->model()->headerData(i,Qt::Horizontal).toString());
            if(i!=0)
            {
              this->inputs[i]->setEnabled(true);
            }
            this->inputs[i]->setText(ui->tableView->model()->data(ui->tableView->model()->index(index,i)).toString());
        }
        else
        {
            this->inputs[i]->setEnabled(false);
            this->inputs[i]->setText("");
             this->labels[i]->setText("");
        }

    }
}

void MainWindow::setRacers(QString name)
{
    //get name
    QString sqlString = "SELECT strVoorNaam,strTussenVoegsel,strAchterNaam FROM formule1.tblpersoon WHERE strAchterNaam = \""+name+"\"";
    ui->invName->setText(setData(sqlString));

    //get team
    QString sqlTeam = "SELECT fnGetTeamName(fnGetPersoonID(\""+name+"\"))";
    ui->invTeam->setText(setData(sqlTeam));

    //get country
    QString sqlCountry = "call spGetCountry(fnGetPersoonID(\""+name+"\"))";
    QStringList naam = sqlHandeler.RacerData(sqlCountry);
    for(int i = 0; i < naam.size(); i++)
    {
        country[i]->setText(naam[i]);
    }
    if(naam.size()<2)
    {
        country[1]->setText("");
    }

    //get foto
    QByteArray f = sqlHandeler.getFoto(name);
    QPixmap outPixmap = QPixmap();

    int w = ui->lbPhoto->width();
    int h = ui->lbPhoto->height();

    outPixmap.loadFromData(f);
    ui->lbPhoto->setPixmap(outPixmap.scaled(w,h,Qt::KeepAspectRatio));
}

QString MainWindow::setData(QString query)
{
    QStringList naam = sqlHandeler.RacerData(query);

    QString heleNaam = naam.join(" ");
    return heleNaam;
}

bool MainWindow::checkResult()
{
    for(int i=0;i<Result.size();i++)
    {
        for(int j=0;j<Result.size();j++)
        {
            if(i!=j)
            {
                if(Result[i]->currentText() == Result[j]->currentText())
                {
                    pop.dubDrivers();
                    return false;
                }
            }
        }
    }
    return true;
}

int MainWindow::newRace()
{
    QDate date = ui->deYear->date();
    QString Race = ui->cbCircuit->currentText();
    QString Pole = ui->cbPolePos->currentText();
    QString Fast = ui->cbFastestLap->currentText();
    int RaceNumber = ui->sbRacenr->value();
    return sqlHandeler.createNewRace(Race,RaceNumber,date,Pole,Fast);
}







void MainWindow::on_Home_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_5_clicked()
{

}

void MainWindow::on_btnSubmit_clicked()
{
    QString GbNaam = ui->leGebruikersnaam->text();
    QString Passwrd = ui->leWachtwoord->text();

    if(sqlHandeler.login(GbNaam,Passwrd))
    {
        ui->leGebruikersnaam->clear();
        ui->leWachtwoord->clear();

        QString Welkom = "Welcome " + GbNaam + "!";
        ui->lbWelcome->setText(Welkom);

        QString Ingelogd = "Ingelogd als " + GbNaam;

        ui->lbIngelogd->setText(Ingelogd);

        ui->pbUpdate->setEnabled(true);





    }
    else
    {
        pop.loginIncorrect();
        ui->leGebruikersnaam->clear();
        ui->leWachtwoord->clear();
    }
}

void MainWindow::on_pbUpdate_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QStringList data = sqlHandeler.tableFinder();

        ui->cbTables->addItems(data);



}

void MainWindow::on_cbTables_currentIndexChanged(const QString &arg1)
{
    QString hulp = arg1;
   ui->tableView->setModel(sqlHandeler.tableData(hulp));
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    val = index.row();
    qDebug()<<val;

    fillLineEdit(val);
}

void MainWindow::on_pbUpdate_2_clicked()
{
    for(int i = 0; i<5; i++)
    {
        if(inputs[i]->isEnabled())
        {
            sqlHandeler.updateSQL(ui->cbTables->currentText(),this->labels[i]->text(),this->inputs[i]->text(),inputs[0]->text());
        }

    }
}

void MainWindow::on_pbStats_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_cbTopic_currentIndexChanged(const QString &arg1)
{
    QString switcher = arg1;

    if(switcher == "Drivers")
    {
        ui->stackedWidget_2->setCurrentIndex(1);
        QStringList data = sqlHandeler.RacerFinder();

           ui->cbRacers->addItems(data);
    }
}

void MainWindow::on_pbLogin_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_cbRacers_currentIndexChanged(const QString &arg1)
{
    QString racers = arg1;
    setRacers(racers);
}

void MainWindow::on_pbinrace_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    QStringList data = sqlHandeler.RacerFinder();
    QStringList finishType = sqlHandeler.finishFInder();
    QStringList circuit = sqlHandeler.circuitFinder();
    for(int i =0;i<Result.size();i++)
    {

           Result[i]->addItems(data);
    }
    for(int j  =0; j<Finish.size(); j++)
    {
        Finish[j]->addItems(finishType);
    }

    ui->cbCircuit->addItems(circuit);
    ui->cbFastestLap->addItems(data);
    ui->cbPolePos->addItems(data);

}

void MainWindow::on_pbGoBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pInsert_clicked()
{
    if(checkResult())
    {
        int Raceid = newRace();
        for(int i = 0; i<Result.size();i++)
        {
            QString pers = Result[i]->currentText();
            int pos = i +1;

            QString type = Finish[i]->currentText();
            sqlHandeler.spInsertCoureur(pers,Raceid,pos,type);
        }
    }


}

void MainWindow::on_pbDelete_clicked()
{
    QString table = ui->cbTables->currentText();
    int ID = this->labels[0]->text().toInt();
    sqlHandeler.spDeleteRecord(table,val+1);
}
