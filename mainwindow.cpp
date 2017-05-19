#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <player.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

using namespace cv ;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->vdo_lbl,SIGNAL(click()),this,SLOT(pointClick()));
    myPlayer = new Player();
    myPlayer->loadVideo();

}

MainWindow::~MainWindow()
{
    delete ui;
 //   delete myPlayer;
}

void MainWindow::pointClick()
{

    ui->label_2->setText(QString("x=%1  y=%2").arg(ui->vdo_lbl->a[0].x).arg(ui->vdo_lbl->a[0].y));
    ui->label_3->setText(QString("x=%1  y=%2").arg(ui->vdo_lbl->a[1].x).arg(ui->vdo_lbl->a[1].y));
    ui->label_4->setText(QString("x=%1  y=%2").arg(ui->vdo_lbl->a[2].x).arg(ui->vdo_lbl->a[2].y));
    ui->label_5->setText(QString("x=%1  y=%2").arg(ui->vdo_lbl->a[3].x).arg(ui->vdo_lbl->a[3].y));
}

void MainWindow::on_nxtFrmBtn_clicked()
{
    int position = myPlayer->getCurrentFramePosition();
 //   ui->label->setText(QString::number(position));
    if(position <= myPlayer->getNumberOfFrames()-5){
        position+=5;
    }
    else position = myPlayer->getNumberOfFrames();

    myPlayer->setCurrentFrame(position);
    QImage img = myPlayer->getCurrentFrameImg();
    ui->vdo_lbl->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_prevFrmBtn_clicked()
{
    int position = myPlayer->getCurrentFramePosition();
    //ui->label->setText(QString::number(position));
    if(position > 5){
        position-=5;
    }
    else position = 1;

    myPlayer->setCurrentFrame(position);
    QImage img = myPlayer->getCurrentFrameImg();
    ui->vdo_lbl->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_createImgBtn_clicked()
{ vector<Point2f> dst,src;
    dst.push_back(Point2f(0,0));
    dst.push_back(Point2f(250,0));
    dst.push_back(Point2f(0,100));
    dst.push_back(Point2f(250,100));
    for(int i=0;i<4;i++){
        src.push_back(ui->vdo_lbl->a[i]);

    }

    int position = myPlayer->getCurrentFramePosition();
    myPlayer->setCurrentFrame(position);
    QImage img = myPlayer->getCurrentFrameImg();
    Mat dstn;

        cv::Mat result = myPlayer->returnFrame();

    Mat m = findHomography(src,dst,0);

    warpPerspective(result,dstn,m,Size(250,100));
     namedWindow("video", CV_WINDOW_AUTOSIZE);
     imshow("video",dstn);
    char  name[100];
     sprintf(name, "D:\\qt-project\\carProject\\img\\frame%d.jpg",position);
    imwrite(name,dstn);
    // img2 = QImage((const unsigned char*)(dstn.data), dstn.cols,dstn.rows,QImage::Format_RGB8);
   // ui->outputLbl->setPixmap(QPixmap::fromImage(img2));

}

void MainWindow::on_clrBtn_clicked()
{
    ui->vdo_lbl->src.clear();
    ui->label_2->setText("x=0  y=0");
    ui->label_3->setText("x=0  y=0");
    ui->label_4->setText("x=0  y=0");
    ui->label_5->setText("x=0  y=0");

}
