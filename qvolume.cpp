#include "qvolume.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/soundcard.h>
#include <time.h>

#include <QtGui>



QVolume::QVolume(QObject *p) : QObject(p)
{
    mx_fd = open("/dev/mixer4", O_RDONLY);

    icon = new QSystemTrayIcon;
    icon->installEventFilter(this);
    refresh();
    icon->setVisible(true);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getVol()));
    timer->start(250);
}

bool QVolume::eventFilter(QObject *o, QEvent *e)
{
    if (o == icon)
        if (e->type() == QEvent::Wheel)
        {
            QWheelEvent *we = static_cast<QWheelEvent *>(e);
            if (we->delta() >= 0)
                system("mixer -S vol +3");
            else
                system("mixer -S vol -3");
            return true;
        }
    return QObject::eventFilter(o, e);
}

void QVolume::getVol()
{
    int bar = 0;
    ioctl(mx_fd, MIXER_READ(0), &bar);
    int t_value = bar & 0x7f;
    if (t_value != value)
    {
        value = t_value;
        refresh();
    }
}

void QVolume::refresh()
{
    QPixmap pix(32, 22);
    pix.fill(Qt::transparent);

    QPainter pnt(&pix);
    QRect rect(0, 0, 32, 22);
    pnt.setPen(Qt::white);
    QString str;
    str.setNum(value);
    str += '%';
    pnt.drawText(rect, Qt::AlignCenter, str);
    icon->setIcon(QIcon(pix));
}
