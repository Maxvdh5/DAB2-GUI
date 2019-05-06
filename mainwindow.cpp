#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    this->labels = {ui->tl1,ui->tl2,ui->tl3,ui->tl4,ui->tl5,ui->tl6};
    this->inputs = {ui->le1,ui->le2,ui->le3,ui->le4,ui->le5,ui->le6};
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

    for(int i = 0; i< CollumCount; i++)
    {
        this->labels[i]->setText(ui->tableView->model()->headerData(i,Qt::Horizontal).toString());
        if(i!=0)
        {
          this->inputs[i]->setEnabled(true);
        }
        this->inputs[i]->setText(ui->tableView->model()->data(ui->tableView->model()->index(index,i)).toString());
    }
}

void MainWindow::setRacers(QString name)
{
    //get name
    QString sqlString = "SELECT strVoorNaam,strTussenVoegsel,strAchterNaam FROM formule1.tblpersoon WHERE strAchterNaam = \""+name+"\"";
    QStringList naam = sqlHandeler.RacerData(sqlString);

    QString heleNaam = naam.join(" ");

    ui->invName->setText(heleNaam);


    //get team

    //get country

    //get points this season racer

    //get points this season team
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
    auto val = index.row();
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
