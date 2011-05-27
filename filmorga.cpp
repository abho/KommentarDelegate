#include "filmorga.h"
#include "ofdbaswahldia.h"

Filmorga::Filmorga(HDB *db,QWidget *parent)
    : QWidget(parent),db(db),filmInfoLadeDialog(this)
{


    this->setting = new QSettings("hakah","filmorga", this);
    if(setting->contains("size")) {
        this->resize(this->setting->value("size").toSize());
    }
    this->layouten();
    this->manager = new GetFilmInfoManager(this->tmp_filme,this);

    connect(this->check_list,SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,SLOT(daten_aendern_changed(QListWidgetItem* , QListWidgetItem*)));
    connect(this->check_list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(daten_aendern_click(QListWidgetItem*)));
    connect(this->list,SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,SLOT(daten_aendern_changed(QListWidgetItem* , QListWidgetItem* )));
    connect(this->list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(daten_aendern_click(QListWidgetItem*)));
    connect(this->but_list_anzeigen,SIGNAL(clicked(bool)),this->list,SLOT(setVisible(bool)));
    this->connect(&this->filmInfoLadeDialog,SIGNAL(beendet(int)),this,SLOT(FilmInfoLadeWidgetAuswerten(int)));
    this->connect(this->manager,SIGNAL(finishedOne(const QString &)),&this->filmInfoLadeDialog,SLOT(setNextValue(const QString &)));
    this->connect(this->manager,SIGNAL(OFDBAuswahlFin()),this,SLOT(makeOFDBAuswhl()));
    this->connect(this->manager,SIGNAL(IMDBAuswahlFin()),this,SLOT(makeIMDBAuswhl()));


    connect(this->but_uebernehmen,SIGNAL(clicked()),this,SLOT(filmUebernehmen()));
    connect(this->but_reload,SIGNAL(clicked()),this,SLOT(film_neu_senden()));
    connect(this->but_disable,SIGNAL(clicked()),this,SLOT(film_deaktiveren()));
    connect(this->but_DBUpdate,SIGNAL(clicked()),this,SLOT(film_store_data()));
    connect(this->but_image_laden,SIGNAL(clicked()),this,SLOT(film_image_laden()));
    this->connect(this->butOFDBAuswahl,SIGNAL(clicked()),this,SLOT(filmOFDBAuswahl()));
    this->connect(this->butIMDBAuswahl,SIGNAL(clicked()),this,SLOT(filmIMDBAuswahl()));
    this->connect(this->butTest,SIGNAL(clicked()),this,SLOT(test()));




}
void Filmorga::layouten()  {
    QVBoxLayout *main_box= new QVBoxLayout;
    QHBoxLayout *but_box = new QHBoxLayout;
    this->but_list_anzeigen = new QPushButton("List anzigen");
    this->but_list_anzeigen->setCheckable(true);
    but_box->addWidget(this->but_list_anzeigen);
    but_box->addStretch();
    main_box->addLayout(but_box);


    QVBoxLayout *filmDatenBox = new QVBoxLayout;

    this->l_titel = new QLabel("Titel:");
    this->titel =new QLineEdit("");
    filmDatenBox->addWidget(this->l_titel);
    filmDatenBox->addWidget(this->titel);
    this->l_inhalt = new QLabel("Inhalt:");
    this->inhalt = new QTextEdit("");
    filmDatenBox->addWidget(this->l_inhalt);
    filmDatenBox->addWidget(this->inhalt);
    QHBoxLayout *box2= new QHBoxLayout();
    this->l_jahr = new QLabel("Jahr:");
    this->jahr = new QLineEdit("");
    box2->addWidget(this->l_jahr);
    box2->addWidget(this->jahr);
    this->regie =new QLineEdit("");
    this->l_regie = new QLabel("REgie:");
    box2->addWidget(this->l_regie);
    box2->addWidget(this->regie);
    this->l_art = new QLabel("Art:");
    this->art = new QLineEdit("");
    box2->addWidget(this->l_art);
    box2->addWidget(this->art);
    filmDatenBox->addLayout(box2);
    this->l_schauspieler = new QLabel("Schauspieler:");
    this->schauspieler = new QLineEdit("");
    filmDatenBox->addWidget(this->l_schauspieler);
    filmDatenBox->addWidget(this->schauspieler);
    QHBoxLayout *box3 = new QHBoxLayout();

    this->l_bewertung = new QLabel("Bewertung:");
    this->bewertung = new QLineEdit("");
    box3->addWidget(this->l_bewertung);
    box3->addWidget(this->bewertung);
    this->l_zeit = new QLabel("Zeit;");
    this->zeit= new QLineEdit("");
    box3->addWidget(this->l_zeit);
    box3->addWidget(this->zeit);
    this->l_nr= new QLabel("Nr:");
    this->nr = new QLineEdit("");
    box3->addWidget(this->l_nr);
    box3->addWidget(this->nr);
    filmDatenBox->addLayout(box3);
    this->l_trailer = new QLabel("Trailer:");
    this->trailer = new QLineEdit("");
    filmDatenBox->addWidget(this->l_trailer);
    filmDatenBox->addWidget(this->trailer);

    this->l_pic = new QLabel("bild_url");
    filmDatenBox->addWidget(this->l_pic);
    this->pic = new QLineEdit();
    filmDatenBox->addWidget(this->pic);
    this->l_imdb = new QLabel("imdb:");
    this->imdb = new QLineEdit("");
    filmDatenBox->addWidget(this->l_imdb);
    filmDatenBox->addWidget(this->imdb);
    this->l_ofdb = new QLabel("ofdb");
    this->ofdb = new QLineEdit("");
    filmDatenBox->addWidget(this->l_ofdb);
    filmDatenBox->addWidget(this->ofdb);
    this->image = new QLineEdit("");
    this->l_image= new QLabel("image:");
    filmDatenBox->addWidget(this->l_image);
    filmDatenBox->addWidget(this->image);
    QHBoxLayout *check_box = new QHBoxLayout();
    this->check = new QCheckBox("check?");
    this->check->setDisabled(true);
    check_box->addWidget(this->check);
    this->activ = new QCheckBox("active?");
    this->activ->setDisabled(true);
    check_box->addWidget(this->activ);
    this->l_version = new QLabel("version:");
    this->version = new QLineEdit();
    check_box->addWidget(this->l_version);
    check_box->addWidget(this->version);
    filmDatenBox->addLayout(check_box);



    QHBoxLayout *film_but_box = new QHBoxLayout();

    this->but_uebernehmen= new QPushButton("check");
    this->but_reload= new QPushButton("Neu Senden");
    this->but_disable = new QPushButton("Deaktivieren");
    this->but_DBUpdate = new QPushButton("daten_übernehmen");
    this->but_image_laden = new QPushButton("Bild neu laden");
    this->butOFDBAuswahl = new QPushButton("OFDBAuswahl");
    this->butIMDBAuswahl = new QPushButton("IMDBAuswahl");
    this->butTest = new QPushButton("test");

    film_but_box->addWidget(this->but_uebernehmen);
    film_but_box->addWidget(this->but_reload);
    film_but_box->addWidget(this->but_disable);
    film_but_box->addWidget(this->but_DBUpdate);
    film_but_box->addWidget(this->but_image_laden);
    film_but_box->addWidget(this->butOFDBAuswahl);
    film_but_box->addWidget(this->butIMDBAuswahl);
    film_but_box->addWidget(this->butTest);
    filmDatenBox->addLayout(film_but_box);


    QSplitter *split =new QSplitter;
    this->check_list = new QListWidget;
    if(this->setting->contains("check_list")){
        this->check_list->resize(this->setting->value("check_list").toSize());
    }
    split->addWidget(this->check_list);

    this->list=new QListWidget;
    if(this->setting->contains("list")){
        this->list->resize(this->setting->value("list").toSize());
    }
    split->addWidget(this->list);

    this->list->setVisible(false);
    this->l_bild=new QLabel("");


    this->filmbox = new QGroupBox;
    QHBoxLayout *film_box = new QHBoxLayout;
    film_box->addWidget(this->l_bild);
    film_box->addLayout(filmDatenBox);
    filmbox->setLayout(film_box);
    if(this->setting->contains("filmbox")) {
        filmbox->resize(this->setting->value("filmbox").toSize());
    }

    split->addWidget(filmbox);


    main_box->addWidget(split);

    this->setLayout(main_box);
}
void Filmorga::filmOFDBAuswahl(){
    if(!this->titel->text().isEmpty()){
        this->setButtons(false);
       this->manager->getOFDBAuswahl(this->titel->text());
    }
}
void Filmorga::filmIMDBAuswahl(){
    if(!this->titel->text().isEmpty()){
        this->setButtons(false);
       this->manager->getIMDBAuswahl(this->titel->text());
    }
}

void Filmorga::makeOFDBAuswhl(){
    qDebug() << "auswahl!!";
  QList< QPair<QString,QString > >*list = this->manager->getOFDBQuswahlList();
  OFDBAswahlDia *dialog = new OFDBAswahlDia(this->titel->text(),list,this);
int code =dialog->exec();
  if(code ==1){
      qDebug() << dialog->getResult();

      this->filmInfoLadeDialog.setMax(1);
      this->filmInfoLadeDialog.setArt(FilmInfoLadeDialog::EinFilm);
      this->filmInfoLadeDialog.show();
      this->tmp_filme.append(this->db->film(this->last_item->data(Qt::UserRole).toInt()));
      this->manager->getOFDBFilmInfo("http://www.ofdb.de/"+dialog->getResult());
  } else if(code == 2){
  this->manager->getOFDBAuswahl(dialog->getResult());
  }else {
  this->setButtons(true);
}
  delete dialog;

}
void Filmorga::makeIMDBAuswhl(){
    qDebug() << "auswahl!!";
  QList< QPair<QString,QString > >*list = this->manager->getOFDBQuswahlList();
  OFDBAswahlDia *dialog = new OFDBAswahlDia(this->titel->text(),list,this);
int code =dialog->exec();
  if(code ==1){
      qDebug() << dialog->getResult();

      this->filmInfoLadeDialog.setMax(1);
      this->filmInfoLadeDialog.setArt(FilmInfoLadeDialog::EinFilm);
      this->filmInfoLadeDialog.show();
      this->tmp_filme.append(this->db->film(this->last_item->data(Qt::UserRole).toInt()));
     this->manager->getIMDBFilmInfo("http://www.imdb.com"+dialog->getResult());
  } else if(code == 2){
  this->manager->getIMDBAuswahl(dialog->getResult());
  }else {
  this->setButtons(true);
}
  delete dialog;

}

void Filmorga::filmUebernehmen(){
    qDebug() << this->last_item;
    HFilm film = this->db->film(this->last_item->data(Qt::UserRole).toInt());
    if(this->last_item->listWidget() == this->list) {
        film.setCheck(false);
        this->db->update(film);
        this->inListeEinsortieren(film,this->check_list);
        this->last_item=NULL;
        qDebug() << "ü"<<this->last_item;
        delete this->list->takeItem(this->list->currentRow());
    }
    else if(this->last_item->listWidget() == this->check_list) {
        film.setCheck(true);
        this->db->update(film);
        this->inListeEinsortieren(film,this->list);
        this->last_item=NULL;
        qDebug() << "ü"<<this->last_item;
        delete this->check_list->takeItem(this->check_list->currentRow());
    }

}

void Filmorga::film_neu_senden() {
    this->setButtons(false);
    this->filmInfoLadeDialog.setMax(1);
    this->filmInfoLadeDialog.setArt(FilmInfoLadeDialog::EinFilm);
    this->filmInfoLadeDialog.show();
    this->tmp_filme.append(this->db->film(this->last_item->data(Qt::UserRole).toInt()));
    if(this->image->text().isEmpty())
        this->manager->getFilmInfo(this->imdb->text(),this->ofdb->text());
    else
        this->manager->getInfoUndPic(this->image->text(),this->imdb->text(),this->ofdb->text());
}
void Filmorga::film_deaktiveren(){
    this->tmp_film =this->db->film(this->last_item->data(Qt::UserRole).toInt());
    if(this->tmp_film.getActive()) {
        this->tmp_film.setActive(false);
        this->last_item->setBackgroundColor(Qt::red);
    } else {
        this->tmp_film.setActive(true);

        this->last_item->setBackgroundColor(Qt::white);
    }
    this->db->update(this->tmp_film);
    this->last_item->listWidget()->repaint();
    this->daten_aendern(this->last_item);
}

void Filmorga::film_store_data(){
    this->tmp_film =this->db->film(this->last_item->data(Qt::UserRole).toInt());

    this->tmp_film.setTitel(this->titel->text());
    this->tmp_film.setPic(this->pic->text());
    this->tmp_film.setInfo(this->inhalt->toPlainText());
    this->tmp_film.setJahr(this->jahr->text());
    this->tmp_film.setZeit(this->zeit->text().toInt());
    this->tmp_film.setTrailer(this->trailer->text());
    this->tmp_film.setRegie(this->regie->text());
    this->tmp_film.setSchauspieler(this->schauspieler->text().split(","));
    this->tmp_film.setGenres(this->art->text().split(","));
    this->tmp_film.setBewertung(this->bewertung->text());
    this->tmp_film.setVersion(this->version->text().toInt());
    this->db->update(this->tmp_film);
    QMessageBox::information(this,"Daten übernommen","Daten wurden erfolgreich in die Datenbank übernommen.",QMessageBox::Ok);
}
void Filmorga::film_image_laden(){
    qDebug() << "film" <<this->last_item;
    if(!this->image->text().isEmpty()){
        this->setButtons(false);
        this->filmInfoLadeDialog.setMax(1);
        this->filmInfoLadeDialog.setArt(FilmInfoLadeDialog::EinBild);
        this->filmInfoLadeDialog.show();
        this->tmp_filme.append(this->db->film(this->last_item->data(Qt::UserRole).toInt()));
        this->manager->getPic(this->image->text());
    } else {
        QMessageBox::information(this,"Fehler","Keine URL angeben.");
    }

}

void Filmorga::start() {
    this->filmeAusDBLaden();
    this->neueFilmeAusOrdnerLaden();

}

void Filmorga::filmeAusDBLaden(){
    foreach(HFilm film,this->db->filme()) {
        if(film.getCheck()){
            this->inListeEinsortieren(film,this->list);
        } else {
            this->inListeEinsortieren(film,this->check_list);
        }
    }
}

void  Filmorga::neueFilmeAusOrdnerLaden(){
    QDir dir("S://ftp//Film");
    QStringList film_list= dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);
    film_list.removeFirst();
    qDebug() << film_list.size();
    HFilm film;
    foreach(QString film_name,film_list) {
        if(!this->db->contains(film_name.remove(".mkv"))) {
            qDebug() << film_name;
            film.setTitel(film_name.remove(".mkv"));
            this->tmp_filme.append(film);
        }
    }
    if(!this->tmp_filme.isEmpty()){
        int ret = QMessageBox::question(this,"Neue Filme","Es gibt "+QString::number(this->tmp_filme.size())
                                        +" neue Filme.\nIm Internat nach Filminformationen suchen ?",
                                        QMessageBox::Yes| QMessageBox::No);
        if(ret == QMessageBox::Yes) {
            this->setButtons(false);
            this->filmInfoLadeDialog.setMax(this->tmp_filme.size());
            this->filmInfoLadeDialog.setArt(FilmInfoLadeDialog::MehrereFilme);
            this->filmInfoLadeDialog.show();

            this->manager->getFilmInfos();
        }
    }
}

void Filmorga::FilmInfoLadeWidgetAuswerten(int i){
    qDebug() << "Fertig";
    if(i == FilmInfoLadeDialog::MehrereFilme) {
        this->tmp_filme_einsortieren();
    } else if (i == FilmInfoLadeDialog::EinFilm){
        this->db->update(this->tmp_filme[0]);
        this->tmp_filme.clear();
        this->daten_aendern(this->last_item);
    } else if( i == FilmInfoLadeDialog::EinBild) {
        this->db->update(this->tmp_filme[0]);
        this->tmp_filme.clear();
        this->daten_aendern(this->last_item);
    } else if(i == FilmInfoLadeDialog::AMehrereFilme){
        this->manager->stop();
        this->abbruchAuswerten();
    }else if(i == FilmInfoLadeDialog::AEinBild){
        this->manager->stop();
    }else if(i == FilmInfoLadeDialog::AEinFilm){
        this->manager->stop();
    }
    this->setButtons(true);
}

void Filmorga::tmp_filme_einsortieren(){
    QElapsedTimer timer;
         timer.start();

this->db->startTrans();
    for(int i =0;i<this->tmp_filme.size();i++){
        this->db->append(this->tmp_filme[i]);
        this->inListeEinsortieren(this->db->film(this->tmp_filme.at(i).getTitel()),this->check_list);
    }
    this->tmp_filme.clear();
    this->db->endTrans();
     qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";
}
void Filmorga::inListeEinsortieren(const HFilm &film, QListWidget *list){
    QListWidgetItem *item = new QListWidgetItem(list);
    if(!film.getActive())
        item->setBackgroundColor(Qt::red);
    item->setText(film.getTitel());
    item->setData(Qt::UserRole,QVariant(film.getNr()));
}
void Filmorga::abbruchAuswerten() {
    QStringList &namen = this->filmInfoLadeDialog.getReadyNamen();
    foreach(HFilm film,this->tmp_filme){
        if(namen.contains(film.getTitel())){
            this->db->append(film);
            this->inListeEinsortieren(this->db->film(film.getTitel()),this->check_list);
        }
    }
    this->tmp_filme.clear();
}

void Filmorga::daten_aendern(QListWidgetItem * current) {    
    qDebug() <<"muh"<< current;
    this->last_item =current;
    qDebug() << "muh3"<< this->last_item->data(Qt::UserRole).toInt();
    this->imdb->clear();
    this->ofdb->clear();
    this->image->clear();
    if (current !=0) {
        if(this->last_item->listWidget()==this->list){
            this->but_uebernehmen->setText("Uncheck");
        } else if(this->last_item->listWidget()==this->check_list){
            this->but_uebernehmen->setText("Check");
        }
        HFilm const &film=this->db->film(this->last_item->data(Qt::UserRole).toInt());
        if (film.getActive()){
            this->but_disable->setText("Deaktivieren");
        } else {
            this->but_disable->setText("Reaktiveren");
        }
        qDebug() << film.getGenres();
        this->titel->setText(film.getTitel());
        this->l_bild->setPixmap(QPixmap(film.getPic()));
        this->inhalt->setText(film.getInfo());
        this->jahr->setText(film.getJahr());
        this->zeit->setText(QString("%1").arg(film.getZeit()));
        this->trailer->setText(film.getTrailer());
        this->regie->setText(film.getRegie());
        this->nr->setText(QString("%1").arg(film.getNr()));
        this->schauspieler->setText(film.getSchauspieler().join(","));
        this->art->setText(film.getGenres().join(","));
        this->bewertung->setText(film.getBewertung());
        this->pic->setText(film.getPic());
        this->check->setChecked(film.getCheck());
        this->activ->setChecked(film.getActive());
        this->version->setText(QString::number(film.getVersion()));
    } else {
        this->titel->setText("");
        this->l_bild->setPixmap(QPixmap(""));
        this->inhalt->setText("");
        this->jahr->setText("");
        this->zeit->setText("");
        this->trailer->setText("");
        this->regie->setText("");
        this->nr->setText("");
        this->schauspieler->setText("");
        this->art->setText("");
        this->bewertung->setText("");
        this->pic->setText("");
        this->check->setChecked(false);
        this->activ->setChecked(false);
        this->version->setText("");

    }
}
void Filmorga::daten_aendern_changed(QListWidgetItem *current, QListWidgetItem *previous) {
    this->daten_aendern(current);
}
void Filmorga::daten_aendern_click(QListWidgetItem *current) {
    this->daten_aendern(current);
}

void Filmorga::setButtons(bool x) {
    this->but_DBUpdate->setEnabled(x);
    this->but_disable->setEnabled(x);
    this->but_image_laden->setEnabled(x);
    this->but_reload->setEnabled(x);
    this->but_uebernehmen->setEnabled(x);
    this->butOFDBAuswahl->setEnabled(x);
    this->butIMDBAuswahl->setEnabled(x);
}

Filmorga::~Filmorga() {
    this->setting->setValue("list",this->list->size());
    this->setting->setValue("check_ist",this->check_list->size());
    this->setting->setValue("filmbox",this->filmbox->size());
    this->setting->setValue("size",this->size());
    delete this->db;
}

void Filmorga::test() {
}


