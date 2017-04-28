#ifndef PIS_MODULE_H
#define PIS_MODULE_H

#include <QObject>

#include "PIS.h"
#include "PIS_global.h"
#include "pis_settings.h"
#include "prerecorded.h"
#include "route_selection.h"
#include "running_route.h"


class pis_module : public QObject
{
    Q_OBJECT
public:
    explicit pis_module(QObject *parent = 0);

    PIS_VIEW *view;
signals:

public slots:

};

#endif // PIS_MODULE_H
