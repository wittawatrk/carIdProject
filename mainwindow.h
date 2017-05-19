#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <player.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage img2;

public slots:
    void pointClick();

private slots:
    void on_nxtFrmBtn_clicked();

    void on_prevFrmBtn_clicked();

    void on_createImgBtn_clicked();

    void on_clrBtn_clicked();

private:
    Ui::MainWindow *ui;
    Player *myPlayer;

};

#endif // MAINWINDOW_H
