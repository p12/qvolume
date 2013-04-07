#ifndef QVOLUME_H
#define QVOLUME_H

#include <QSystemTrayIcon>

class QVolume : private QObject
{
    Q_OBJECT

private:
    QSystemTrayIcon *icon;
    int mx_fd;
    int value;
    void refresh();

public slots:
    void getVol();

public:
    QVolume(QObject *p = 0);
    bool eventFilter(QObject *o, QEvent * e);

};

#endif // QVOLUME_H
