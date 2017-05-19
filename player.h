/*
 * RBAnnotator
 *
 * Author: Davide Moltisanti
 * Code released under GPL license
 *
 * For this class I used code from http://codingexodus.blogspot.co.uk/2012/12/working-with-video-using-opencv-and-qt.html
 *
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QString>
#include <QtWidgets/QApplication>
using namespace cv;

class Player : public QThread{
    Q_OBJECT

 private:
    bool stop;
    bool videoLoaded;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    double frameRate;
    VideoCapture capture;
    Mat RGBframe;
    QImage img;
    Mat imgFrm;
    int numberOfFrames;

   void readCurrentFrame();

signals:
      void processedImage(const QImage &image);

 protected:
 //    void run();
  //   void msleep(int ms);

 public:
    Player(QObject *parent = 0);
    ~Player();
    bool loadVideo();
    void playVideo();
    void stopVideo();
    bool isStopped() const;
    int getNumberOfFrames();
    int getLengthMs();
    int getCurrentMsPosition();
    int getCurrentFramePosition();
    void setCurrentFrame(int framePosition);
    void setCurrentMs(double ms);
    void skipOneFrame(Mat frame);
    bool isVideoLoaded() const;
    QImage getCurrentFrameImg() const;
    Mat returnFrame() const;
    VideoCapture * getCapture();
    void getFrameSize(int *width, int *height);
};
#endif // PLAYER_H
