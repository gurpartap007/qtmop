/****************************************************************************
** Meta object code from reading C++ file 'running_route.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "running_route.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'running_route.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_running_route_t {
    QByteArrayData data[17];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_running_route_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_running_route_t qt_meta_stringdata_running_route = {
    {
QT_MOC_LITERAL(0, 0, 13), // "running_route"
QT_MOC_LITERAL(1, 14, 9), // "log_event"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "route_events"
QT_MOC_LITERAL(4, 38, 5), // "event"
QT_MOC_LITERAL(5, 44, 4), // "data"
QT_MOC_LITERAL(6, 49, 19), // "GPSSimulationActive"
QT_MOC_LITERAL(7, 69, 10), // "timerEvent"
QT_MOC_LITERAL(8, 80, 12), // "QTimerEvent*"
QT_MOC_LITERAL(9, 93, 17), // "message_generator"
QT_MOC_LITERAL(10, 111, 18), // "gps_data_collector"
QT_MOC_LITERAL(11, 130, 21), // "manage_device_updates"
QT_MOC_LITERAL(12, 152, 12), // "mediachanged"
QT_MOC_LITERAL(13, 165, 8), // "read_pkt"
QT_MOC_LITERAL(14, 174, 9), // "check_pkt"
QT_MOC_LITERAL(15, 184, 12), // "play_message"
QT_MOC_LITERAL(16, 197, 4) // "int*"

    },
    "running_route\0log_event\0\0route_events\0"
    "event\0data\0GPSSimulationActive\0"
    "timerEvent\0QTimerEvent*\0message_generator\0"
    "gps_data_collector\0manage_device_updates\0"
    "mediachanged\0read_pkt\0check_pkt\0"
    "play_message\0int*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_running_route[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    2,   70,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   78,    2, 0x0a /* Public */,
       9,    2,   81,    2, 0x0a /* Public */,
      10,    2,   86,    2, 0x0a /* Public */,
      11,    0,   91,    2, 0x0a /* Public */,
      12,    1,   92,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    1,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::VoidStar,    4,    5,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::VoidStar,    2,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::VoidStar,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    2,

       0        // eod
};

void running_route::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        running_route *_t = static_cast<running_route *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->log_event(); break;
        case 1: _t->route_events((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 2: _t->GPSSimulationActive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        case 4: _t->message_generator((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 5: _t->gps_data_collector((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 6: _t->manage_device_updates(); break;
        case 7: _t->mediachanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->read_pkt(); break;
        case 9: _t->check_pkt(); break;
        case 10: _t->play_message((*reinterpret_cast< int*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (running_route::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&running_route::log_event)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (running_route::*_t)(qint64 , void * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&running_route::route_events)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (running_route::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&running_route::GPSSimulationActive)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject running_route::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_running_route.data,
      qt_meta_data_running_route,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *running_route::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *running_route::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_running_route.stringdata0))
        return static_cast<void*>(const_cast< running_route*>(this));
    return QWidget::qt_metacast(_clname);
}

int running_route::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void running_route::log_event()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void running_route::route_events(qint64 _t1, void * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void running_route::GPSSimulationActive(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
