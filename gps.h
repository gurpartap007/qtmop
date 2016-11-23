#ifndef GPS_H
#define GPS_H

#include <QObject>

class gps : public QObject
{
    Q_OBJECT
public:
    explicit gps(QObject *parent = 0);

signals:

public slots:
};

#endif // GPS_H