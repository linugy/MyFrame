#ifndef MYCHART_GLOBAL_H
#define MYCHART_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYCHART_LIBRARY)
#  define MYCHARTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MYCHARTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MYCHART_GLOBAL_H
