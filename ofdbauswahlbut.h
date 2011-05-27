#ifndef OFDBAUSWAHLBUT_H
#define OFDBAUSWAHLBUT_H

#include <QPushButton>

class OFDBAuswahlBut : public QPushButton
{
    Q_OBJECT
public:
    explicit OFDBAuswahlBut(int index,QWidget *parent = 0);

signals:
    void klicked(int index);
private slots:
    void clickWeiter();
private:
    int index;

};

#endif // OFDBAUSWAHLBUT_H
