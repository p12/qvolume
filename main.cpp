#include <QtGui>
#include <qvolume.h>

int main(int argc, char *argv[])

{
//    Q_INIT_RESOURCE(qvolume);

    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    QVolume vol;

    vol.getVol();

    return app.exec();
}
