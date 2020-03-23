#ifndef MYUTIL_GLOBAL_H
#define MYUTIL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYUTIL_LIBRARY)
#  define MYUTILSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MYUTILSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MYUTIL_GLOBAL_H
