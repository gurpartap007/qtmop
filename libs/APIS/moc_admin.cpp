/****************************************************************************
** Meta object code from reading C++ file 'admin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../admin/admin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'admin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_admin_t {
    QByteArrayData data[15];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_admin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_admin_t qt_meta_stringdata_admin = {
    {
QT_MOC_LITERAL(0, 0, 5), // "admin"
QT_MOC_LITERAL(1, 6, 12), // "centreDialog"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "getData"
QT_MOC_LITERAL(4, 28, 17), // "on_change_clicked"
QT_MOC_LITERAL(5, 46, 16), // "on_reset_clicked"
QT_MOC_LITERAL(6, 63, 14), // "updatePassword"
QT_MOC_LITERAL(7, 78, 10), // "updateLine"
QT_MOC_LITERAL(8, 89, 13), // "matchPassword"
QT_MOC_LITERAL(9, 103, 3), // "str"
QT_MOC_LITERAL(10, 107, 9), // "showEvent"
QT_MOC_LITERAL(11, 117, 11), // "QShowEvent*"
QT_MOC_LITERAL(12, 129, 8), // "fillData"
QT_MOC_LITERAL(13, 138, 8), // "saveData"
QT_MOC_LITERAL(14, 147, 27) // "on_password_2_returnPressed"

    },
    "admin\0centreDialog\0\0getData\0"
    "on_change_clicked\0on_reset_clicked\0"
    "updatePassword\0updateLine\0matchPassword\0"
    "str\0showEvent\0QShowEvent*\0fillData\0"
    "saveData\0on_password_2_returnPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_admin[] = {

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
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    1,   74,    2, 0x08 /* Private */,
       8,    1,   77,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x08 /* Private */,
      12,    0,   83,    2, 0x08 /* Private */,
      13,    0,   84,    2, 0x08 /* Private */,
      14,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Char,    2,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void admin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        admin *_t = static_cast<admin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->centreDialog(); break;
        case 1: { QString _r = _t->getData();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: _t->on_change_clicked(); break;
        case 3: _t->on_reset_clicked(); break;
        case 4: _t->updatePassword(); break;
        case 5: _t->updateLine((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 6: _t->matchPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 8: _t->fillData(); break;
        case 9: _t->saveData(); break;
        case 10: _t->on_password_2_returnPressed(); break;
        default: ;
        }
    }
}

const QMetaObject admin::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_admin.data,
      qt_meta_data_admin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *admin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *admin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_admin.stringdata0))
        return static_cast<void*>(const_cast< admin*>(this));
    return QDialog::qt_metacast(_clname);
}

int admin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
