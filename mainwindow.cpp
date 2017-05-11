#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->label,SIGNAL(click()),this,SLOT(pointClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pointClick()
{
    Point2f a[4];

    for (int i=ui->label->src.size()-1;i>=0;i--) {
        a[i] = ui->label->src.back();
        ui->label->src.pop_back();

}
    ui->label_2->setText(QString("x=%1  y=%2").arg(a[0].x).arg(a[0].y));
    ui->label_3->setText(QString("x=%1  y=%2").arg(a[1].x).arg(a[1].y));
    ui->label_4->setText(QString("x=%1  y=%2").arg(a[2].x).arg(a[2].y));
    ui->label_5->setText(QString("x=%1  y=%2").arg(a[3].x).arg(a[3].y));
}
