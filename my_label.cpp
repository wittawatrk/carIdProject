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
        this->src.push_back(Point2f(float(ev->x()),float(ev->y())));
    }
    else {
      emit click();
    }


}
