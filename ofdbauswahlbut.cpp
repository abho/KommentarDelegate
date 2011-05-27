#include "ofdbauswahlbut.h"

OFDBAuswahlBut::OFDBAuswahlBut(int index,QWidget *parent) :
    QPushButton(parent),index(index)
{
    this->connect(this,SIGNAL(clicked()),this,SLOT(clickWeiter()));
}


void OFDBAuswahlBut::clickWeiter() {
    emit this->klicked(this->index);
}
