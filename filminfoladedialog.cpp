#include "filminfoladedialog.h"

FilmInfoLadeDialog::FilmInfoLadeDialog(QWidget *parent): QDialog(parent)
{
    QVBoxLayout *mainBox = new QVBoxLayout();
    QHBoxLayout *buttonBox = new QHBoxLayout();
    this->label = new QLabel();
    this->bar = new QProgressBar();
    this->butAbbruch = new QPushButton("Abbrechen");
    this->butWeiter = new QPushButton("Weiter");
    this->edit = new QTextEdit();

    buttonBox->addStretch();
    buttonBox->addWidget(this->butWeiter);
    buttonBox->addWidget(this->butAbbruch);

    mainBox->addWidget(this->label);
    mainBox->addWidget(this->edit);
    mainBox->addWidget(this->bar);
    mainBox->addLayout(buttonBox);

    this->setLayout(mainBox);


    this->butWeiter->setEnabled(false);
    this->bar->setValue(0);
    this->bar->setFormat("%v von %m");

    this->setWindowTitle("FilmLadeInfo");
    this->label->setText("Filminformationen werden aus dem Internet heruntergeladen.\nEinen moment Gedult bitte.");
    this->label->setWordWrap(true);
    this->connect(this->butWeiter,SIGNAL(clicked()),this,SLOT(wBeenden()));
    this->connect(this->butAbbruch,SIGNAL(clicked()),this,SLOT(close()));
this->resize(100,200);
}

void FilmInfoLadeDialog::closeEvent(QCloseEvent *event)
{
    emit beendet(this->code+1);
   this->hide();
   event->ignore();
}
FilmInfoLadeDialog::~FilmInfoLadeDialog(){

}
QStringList & FilmInfoLadeDialog::getReadyNamen(){
return this->readyNamen;
}


void FilmInfoLadeDialog::setMax(int max) {
    this->readyNamen.clear();
    this->edit->clear();
    this->bar->setValue(0);
    this->bar->setMaximum(max);
    this->butWeiter->setEnabled(false);
    this->butAbbruch->setEnabled(true);
}

void FilmInfoLadeDialog::setNextValue(const QString &name) {
    this->readyNamen.append(name);
    this->edit->append("<b>"+name+"</b> geladen");
    this->bar->setValue(bar->value()+1);

    if(this->bar->value()==this->bar->maximum()){
       this->butWeiter->setEnabled(true);
       this->butAbbruch->setEnabled(false);
       this->label->setText("Alle Informationen erfolgreich heruntergeladen.");
    }
}

void FilmInfoLadeDialog::wBeenden() {
    emit beendet(this->code);
   this->hide();
}

void  FilmInfoLadeDialog::setArt(result art){
    this->code = art;

}
