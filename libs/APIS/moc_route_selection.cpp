/****************************************************************************
** Meta object code from reading C++ file 'route_selection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "route_selection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'route_selection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_route_selection_t {
    QByteArrayData data[18];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_route_selection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_route_selection_t qt_meta_stringdata_route_selection = {
    {
QT_MOC_LITERAL(0, 0, 15), // "route_selection"
QT_MOC_LITERAL(1, 16, 15), // "lineedit_filter"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "value"
QT_MOC_LITERAL(4, 39, 14), // "route_selected"
QT_MOC_LITERAL(5, 54, 6), // "option"
QT_MOC_LITERAL(6, 61, 11), // "key_process"
QT_MOC_LITERAL(7, 73, 18), // "lineedit_filtering"
QT_MOC_LITERAL(8, 92, 18), // "configure_database"
QT_MOC_LITERAL(9, 111, 24), // "create_working_route_log"
QT_MOC_LITERAL(10, 136, 10), // "updateLine"
QT_MOC_LITERAL(11, 147, 20), // "upload_database_file"
QT_MOC_LITERAL(12, 168, 18), // "selectCurrentRoute"
QT_MOC_LITERAL(13, 187, 7), // "trainNo"
QT_MOC_LITERAL(14, 195, 25), // "on_lineEdit_returnPressed"
QT_MOC_LITERAL(15, 221, 26), // "on_tableView_doubleClicked"
QT_MOC_LITERAL(16, 248, 5), // "index"
QT_MOC_LITERAL(17, 254, 21) // "updateDatabaseVersion"

    },
    "route_selection\0lineedit_filter\0\0value\0"
    "route_selected\0option\0key_process\0"
    "lineedit_filtering\0configure_database\0"
    "create_working_route_log\0updateLine\0"
    "upload_database_file\0selectCurrentRoute\0"
    "trainNo\0on_lineEdit_returnPressed\0"
    "on_tableView_doubleClicked\0index\0"
    "updateDatabaseVersion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_route_selection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    2,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   82,    2, 0x0a /* Public */,
       7,    1,   85,    2, 0x0a /* Public */,
       8,    0,   88,    2, 0x0a /* Public */,
       9,    0,   89,    2, 0x0a /* Public */,
      10,    0,   90,    2, 0x0a /* Public */,
      11,    1,   91,    2, 0x0a /* Public */,
      12,    1,   94,    2, 0x0a /* Public */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    1,   98,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::LongLong, QMetaType::VoidStar,    5,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Int, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   16,
    QMetaType::Void,

       0        // eod
};

void route_selection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        route_selection *_t = static_cast<route_selection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lineedit_filter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->route_selected((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 2: _t->key_process((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->lineedit_filtering((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->configure_database(); break;
        case 5: _t->create_working_route_log(); break;
        case 6: _t->updateLine(); break;
        case 7: _t->upload_database_file((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: { int _r = _t->selectCurrentRoute((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: _t->on_lineEdit_returnPressed(); break;
        case 10: _t->on_tableView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->updateDatabaseVersion(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (route_selection::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&route_selection::lineedit_filter)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (route_selection::*_t)(qint64 , void * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&route_selection::route_selected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject route_selection::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_route_selection.data,
      qt_meta_data_route_selection,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *route_selection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *route_selection::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_route_selection.stringdata0))
        return static_cast<void*>(const_cast< route_selection*>(this));
    return QWidget::qt_metacast(_clname);
}

int route_selection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void route_selection::lineedit_filter(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void route_selection::route_selected(qint64 _t1, void * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
