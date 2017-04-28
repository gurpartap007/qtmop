/****************************************************************************
** Meta object code from reading C++ file 'PIS.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "PIS.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PIS.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PIS_VIEW_t {
    QByteArrayData data[15];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PIS_VIEW_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PIS_VIEW_t qt_meta_stringdata_PIS_VIEW = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PIS_VIEW"
QT_MOC_LITERAL(1, 9, 14), // "getEventFields"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 17), // "pis_event_handler"
QT_MOC_LITERAL(4, 43, 5), // "event"
QT_MOC_LITERAL(5, 49, 4), // "data"
QT_MOC_LITERAL(6, 54, 16), // "save_current_log"
QT_MOC_LITERAL(7, 71, 22), // "kilometrage_Calculator"
QT_MOC_LITERAL(8, 94, 16), // "on_setts_clicked"
QT_MOC_LITERAL(9, 111, 19), // "restoreKilometerage"
QT_MOC_LITERAL(10, 131, 16), // "getPISLibVersion"
QT_MOC_LITERAL(11, 148, 17), // "changeLoggingFreq"
QT_MOC_LITERAL(12, 166, 20), // "on_prerecord_clicked"
QT_MOC_LITERAL(13, 187, 19), // "on_routesel_clicked"
QT_MOC_LITERAL(14, 207, 14) // "selectPISRoute"

    },
    "PIS_VIEW\0getEventFields\0\0pis_event_handler\0"
    "event\0data\0save_current_log\0"
    "kilometrage_Calculator\0on_setts_clicked\0"
    "restoreKilometerage\0getPISLibVersion\0"
    "changeLoggingFreq\0on_prerecord_clicked\0"
    "on_routesel_clicked\0selectPISRoute"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PIS_VIEW[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    2,   70,    2, 0x0a /* Public */,
       6,    0,   75,    2, 0x0a /* Public */,
       7,    2,   76,    2, 0x0a /* Public */,
       8,    0,   81,    2, 0x0a /* Public */,
       9,    0,   82,    2, 0x0a /* Public */,
      10,    0,   83,    2, 0x0a /* Public */,
      11,    1,   84,    2, 0x08 /* Private */,
      12,    0,   87,    2, 0x08 /* Private */,
      13,    0,   88,    2, 0x08 /* Private */,
      14,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::QStringList,
    QMetaType::Void, QMetaType::LongLong, QMetaType::VoidStar,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::VoidStar,    4,    5,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void PIS_VIEW::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PIS_VIEW *_t = static_cast<PIS_VIEW *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QStringList _r = _t->getEventFields();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 1: _t->pis_event_handler((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 2: _t->save_current_log(); break;
        case 3: _t->kilometrage_Calculator((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 4: _t->on_setts_clicked(); break;
        case 5: { int _r = _t->restoreKilometerage();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { QString _r = _t->getPISLibVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: _t->changeLoggingFreq((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_prerecord_clicked(); break;
        case 9: _t->on_routesel_clicked(); break;
        case 10: _t->selectPISRoute((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PIS_VIEW::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PIS_VIEW.data,
      qt_meta_data_PIS_VIEW,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PIS_VIEW::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PIS_VIEW::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PIS_VIEW.stringdata0))
        return static_cast<void*>(const_cast< PIS_VIEW*>(this));
    return QWidget::qt_metacast(_clname);
}

int PIS_VIEW::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
