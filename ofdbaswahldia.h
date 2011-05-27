#ifndef OFDBASWAHLDIA_H
#define OFDBASWAHLDIA_H

#include <QDialog>
#include <QtCore>
#include <QLineEdit>

class OFDBAswahlDia : public QDialog
{
    Q_OBJECT
public:
    explicit OFDBAswahlDia(const QString &str,QList< QPair<QString,QString > >*list,QWidget *parent = 0);
    QString getResult();
private:
    QList< QPair<QString,QString > >*list;
    QString result;
    QLineEdit *edit;
signals:

private slots:
    void checkResult(int index);

};

#endif // OFDBASWAHLDIA_H
