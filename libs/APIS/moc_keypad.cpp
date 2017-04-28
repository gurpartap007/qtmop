/****************************************************************************
** Meta object code from reading C++ file 'keypad.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../virtualKeyboard/keypad.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keypad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_keypad_t {
    QByteArrayData data[16];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_keypad_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_keypad_t qt_meta_stringdata_keypad = {
    {
QT_MOC_LITERAL(0, 0, 6), // "keypad"
QT_MOC_LITERAL(1, 7, 11), // "receiveText"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 1), // "s"
QT_MOC_LITERAL(4, 22, 16), // "on_shift_clicked"
QT_MOC_LITERAL(5, 39, 17), // "on_toggle_clicked"
QT_MOC_LITERAL(6, 57, 13), // "setButtonText"
QT_MOC_LITERAL(7, 71, 17), // "resetToggleSwitch"
QT_MOC_LITERAL(8, 89, 16), // "resetShiftSwitch"
QT_MOC_LITERAL(9, 106, 14), // "on_esc_clicked"
QT_MOC_LITERAL(10, 121, 16), // "on_esc_2_clicked"
QT_MOC_LITERAL(11, 138, 16), // "on_space_clicked"
QT_MOC_LITERAL(12, 155, 14), // "on_del_clicked"
QT_MOC_LITERAL(13, 170, 19), // "on_delete_2_clicked"
QT_MOC_LITERAL(14, 190, 16), // "on_enter_clicked"
QT_MOC_LITERAL(15, 207, 14) // "on_ent_clicked"

    },
    "keypad\0receiveText\0\0s\0on_shift_clicked\0"
    "on_toggle_clicked\0setButtonText\0"
    "resetToggleSwitch\0resetShiftSwitch\0"
    "on_esc_clicked\0on_esc_2_clicked\0"
    "on_space_clicked\0on_del_clicked\0"
    "on_delete_2_clicked\0on_enter_clicked\0"
    "on_ent_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_keypad[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       4,    0,   82,    2, 0x08 /* Private */,
       5,    0,   83,    2, 0x08 /* Private */,
       6,    1,   84,    2, 0x08 /* Private */,
       7,    0,   87,    2, 0x08 /* Private */,
       8,    0,   88,    2, 0x08 /* Private */,
       9,    0,   89,    2, 0x08 /* Private */,
      10,    0,   90,    2, 0x08 /* Private */,
      11,    0,   91,    2, 0x08 /* Private */,
      12,    0,   92,    2, 0x08 /* Private */,
      13,    0,   93,    2, 0x08 /* Private */,
      14,    0,   94,    2, 0x08 /* Private */,
      15,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void keypad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        keypad *_t = static_cast<keypad *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_shift_clicked(); break;
        case 2: _t->on_toggle_clicked(); break;
        case 3: _t->setButtonText((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 4: _t->resetToggleSwitch(); break;
        case 5: _t->resetShiftSwitch(); break;
        case 6: _t->on_esc_clicked(); break;
        case 7: _t->on_esc_2_clicked(); break;
        case 8: _t->on_space_clicked(); break;
        case 9: _t->on_del_clicked(); break;
        case 10: _t->on_delete_2_clicked(); break;
        case 11: _t->on_enter_clicked(); break;
        case 12: _t->on_ent_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject keypad::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_keypad.data,
      qt_meta_data_keypad,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *keypad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *keypad::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_keypad.stringdata0))
        return static_cast<void*>(const_cast< keypad*>(this));
    return QWidget::qt_metacast(_clname);
}

int keypad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
