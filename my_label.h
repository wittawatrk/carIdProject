#ifndef MY_LABEL_H
#define MY_LABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;


class my_label : public QLabel
{
    Q_OBJECT
public:
    explicit  my_label(QWidget *parent=0);
    void mousePressEvent(QMouseEvent *ev);
    vector<Point2f> src;
signals :
    void click();
};

#endif // MY_LABEL_H
