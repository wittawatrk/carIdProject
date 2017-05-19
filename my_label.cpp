#include "my_label.h"
#include <QLabel>
#include <QMouseEvent>

my_label::my_label(QWidget *parent):
QLabel(parent)
{

}

void my_label::mousePressEvent(QMouseEvent *ev)
{
    if (this->src.size()<4){
        this->src.push_back(Point2f(float(ev->x()-5.5),float(ev->y())));
    }
    else {


       for (int i=src.size()-1;i>=0;i--) {
            a[i] = src.back();
            src.pop_back();

    }
      emit click();
    }


}
