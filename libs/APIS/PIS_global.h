#ifndef PIS_GLOBAL_H
#define PIS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(APIS_LIBRARY)
#  define PIS_VIEWSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PIS_VIEWSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PIS_GLOBAL_H
