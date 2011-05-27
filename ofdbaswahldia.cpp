#include "ofdbaswahldia.h"
#include <QVBoxLayout>
#include <QLabel>
#include "ofdbauswahlbut.h"
#include <QMessageBox>

OFDBAswahlDia::OFDBAswahlDia(const QString &str,QList< QPair<QString,QString > > *list,QWidget *parent) :
        QDialog(parent),list(list),result("")
{
    QVBoxLayout *mainBox = new QVBoxLayout();

    for ( int i = 0; i<list->size(); i++ ) {
        const QPair<QString,QString> &pair =list->at(i);
        if(pair.second == ""){
            QLabel *l = new QLabel(pair.first+":");
            mainBox->addWidget(l);
        } else {
            OFDBAuswahlBut *but = new OFDBAuswahlBut(i);
            but->setText(pair.first);
            mainBox->addWidget(but);
            this->connect(but,SIGNAL(klicked(int)),this,SLOT(checkResult(int)));
        }
    }

        this->edit = new QLineEdit();
        this->edit->setText(str);
        mainBox->addWidget(this->edit);
        OFDBAuswahlBut *but = new OFDBAuswahlBut(this->list->size());
        but->setText("Alternativen Titel anfragen");
        mainBox->addWidget(but);
        this->connect(but,SIGNAL(klicked(int)),this,SLOT(checkResult(int)));

    this->setLayout(mainBox);
}

void OFDBAswahlDia::checkResult(int index) {
    if(this->list->size() > index){
        this->result = list->at(index).second;
        this->done(1);

    } else {
        if(!this->edit->text().isEmpty()) {
            this->result = this->edit->text();
            this->done(2);
        } else {
            QMessageBox::information(this,"Fehler","Bitte alternativen titel eintragen.",QMessageBox::Ok);
        }
    }


}

QString OFDBAswahlDia::getResult() {
    return this->result;
}
