#ifndef FILMORGA_H
#define FILMORGA_H

#include <QtGui>
#include <QNetworkAccessManager>
#include <QDebug>
#include "C:\Users\hakah\Documents\QT\LiteTest\hdb.h"
#include "filminfoladedialog.h"
#include "C:\Users\hakah\Documents\QT\GeFilmInfotManager\getfilminfomanager.h"
#include "C:\Users\hakah\Documents\QT\hfilm.h"

class Filmorga : public QWidget
{
    Q_OBJECT

public:
    Filmorga(HDB *db,QWidget *parent = 0);
    ~Filmorga();
    void start();

    QLabel *l_version,*l_bild,*l_nr,*l_titel,*l_inhalt,*l_art,*l_schauspieler,*l_regie,*l_zeit,*l_jahr, *l_trailer,*l_ofdb,*l_imdb,*l_bewertung,*l_image,*l_pic;
    QLineEdit *version,*nr,*titel,*art,*schauspieler,*regie,*zeit,*jahr,*trailer,*imdb,*ofdb,*bewertung,*image, *pic;
    QCheckBox *check,*activ;
    QListWidget *check_list,*list;
    QPushButton *butOFDBAuswahl, *butIMDBAuswahl,*but_reload,*but_disable,*but_uebernehmen,*but_image_laden,*but_DBUpdate, *but_list_anzeigen, *butTest;
    QSettings *setting;
    QGroupBox *filmbox;
    QTextEdit *inhalt;
    HDB *db;
    FilmInfoLadeDialog filmInfoLadeDialog;

    GetFilmInfoManager *manager;

    QListWidgetItem* last_item;
    QVector<HFilm> tmp_filme;
    HFilm  tmp_film;

    void layouten();
    void setButtons(bool x);
    void tmp_filme_einsortieren();
    void filmeAusDBLaden();
    void neueFilmeAusOrdnerLaden();
    void inListeEinsortieren(const HFilm &film, QListWidget *list);
    void abbruchAuswerten();


private slots:
    void daten_aendern_changed(QListWidgetItem * current, QListWidgetItem * previous);
    void daten_aendern_click(QListWidgetItem * current);
    void daten_aendern(QListWidgetItem *current);
    void FilmInfoLadeWidgetAuswerten(int i);
    void filmUebernehmen();
    void film_neu_senden();
    void film_deaktiveren();
    void film_store_data();
    void film_image_laden();
    void filmOFDBAuswahl();
    void filmIMDBAuswahl();
    void makeOFDBAuswhl();
    void makeIMDBAuswhl();
    void test();

};

#endif // FILMORGA_H
