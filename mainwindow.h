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


private slots:
    void on_pushButton_clicked();

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

private:
    Ui::MainWindow *ui;
    SQL sqlHandeler;
    PopupMessage pop;

    std::array<QLabel*, 6> labels;
    std::array<QLineEdit*, 6> inputs;
};

#endif // MAINWINDOW_H
