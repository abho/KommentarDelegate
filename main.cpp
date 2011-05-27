#include <QtGui/QApplication>
#include "filmorga.h"

#include "C:\Users\hakah\Documents\QT\LiteTest\hdb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   HDB *db = new HDB();
    Filmorga w(db);
    w.show();

    w.start();

    return a.exec();
}
