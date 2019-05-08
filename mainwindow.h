#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sql.h"
#include "popupmessage.h"

#include <QString>
#include <QVector>
#include <QDebug>
#include <QSqlQueryModel>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void checkConnection();
    void fillLineEdit(int);
    void setRacers(QString name);
    QString setData(QString query);
    QStringList setListData(QString query);

    bool checkResult();
    int newRace();


private slots:

    void on_Home_clicked();

    void on_pushButton_5_clicked();

    void on_btnSubmit_clicked();

    void on_pbUpdate_clicked();

    void on_cbTables_currentIndexChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pbUpdate_2_clicked();

    void on_pbStats_clicked();

    void on_cbTopic_currentIndexChanged(const QString &arg1);

    void on_pbLogin_clicked();

    void on_cbRacers_currentIndexChanged(const QString &arg1);

    void on_pbinrace_clicked();

    void on_pbGoBack_clicked();

    void on_pInsert_clicked();

    void on_pbDelete_clicked();

private:
    Ui::MainWindow *ui;
    SQL sqlHandeler;
    PopupMessage pop;
    int val;

    std::array<QLabel*, 6> labels;
    std::array<QLineEdit*, 6> inputs;
    std::array<QComboBox*, 20> Result;
    std::array<QComboBox*, 20> Finish;
    std::array<QLabel*, 2> country;
};

#endif // MAINWINDOW_H
