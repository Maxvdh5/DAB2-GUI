#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class navigator : public QMainWindow
{
    Q_OBJECT
public:
    explicit navigator(QWidget *parent = nullptr);

    void page1();
    void page2();

    void setCurrentIndex(int);

signals:

public slots:


private:
    int currentIndex;
    Ui::MainWindow *ui;
};

#endif // NAVIGATOR_H
