#ifndef FILMINFOLADEDIALOG_H
#define FILMINFOLADEDIALOG_H

#include <QtGui>

class FilmInfoLadeDialog : public QDialog
{
    Q_OBJECT
public:
    FilmInfoLadeDialog(QWidget *parent);
    ~FilmInfoLadeDialog();
    void setMax(int max);
    enum result {EinFilm,AEinFilm,MehrereFilme,AMehrereFilme,EinBild,AEinBild};
    void setArt(result art);
    QStringList & getReadyNamen();
private:
    QProgressBar *bar;
    QLabel *label;
    QPushButton *butAbbruch, *butWeiter;
    QTextEdit *edit;
    result code;
    QStringList readyNamen;
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void beendet(int code);

public slots:
void setNextValue(const QString &name);
void wBeenden();
};

#endif // FILMINFOLADEDIALOG_H
