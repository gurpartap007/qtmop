#include "pis_module.h"

pis_module::pis_module(QObject *parent) : QObject(parent)
{
    view = new PIS_VIEW;
}
