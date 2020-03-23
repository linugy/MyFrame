#ifndef MYEXCEL_GLOBAL_H
#define MYEXCEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYEXCEL_LIBRARY)
#  define MYEXCELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MYEXCELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MYEXCEL_GLOBAL_H
