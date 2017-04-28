/****************************************************************************
** Meta object code from reading C++ file 'pis_settings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pis_settings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pis_settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PIS_SETTINGS_t {
    QByteArrayData data[17];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PIS_SETTINGS_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PIS_SETTINGS_t qt_meta_stringdata_PIS_SETTINGS = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PIS_SETTINGS"
QT_MOC_LITERAL(1, 13, 15), // "StartSimulation"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "changeLogFreq"
QT_MOC_LITERAL(4, 44, 11), // "selectRoute"
QT_MOC_LITERAL(5, 56, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(6, 78, 11), // "tab_changed"
QT_MOC_LITERAL(7, 90, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(8, 114, 11), // "text_edited"
QT_MOC_LITERAL(9, 126, 25), // "resize_and_show_keywidget"
QT_MOC_LITERAL(10, 152, 11), // "updateCoach"
QT_MOC_LITERAL(11, 164, 14), // "getPISInfoList"
QT_MOC_LITERAL(12, 179, 14), // "getPISInfoData"
QT_MOC_LITERAL(13, 194, 15), // "on_save_clicked"
QT_MOC_LITERAL(14, 210, 16), // "on_close_clicked"
QT_MOC_LITERAL(15, 227, 33), // "on_comboBox_2_currentIndexCha..."
QT_MOC_LITERAL(16, 261, 5) // "index"

    },
    "PIS_SETTINGS\0StartSimulation\0\0"
    "changeLogFreq\0selectRoute\0"
    "on_pushButton_clicked\0tab_changed\0"
    "on_pushButton_2_clicked\0text_edited\0"
    "resize_and_show_keywidget\0updateCoach\0"
    "getPISInfoList\0getPISInfoData\0"
    "on_save_clicked\0on_close_clicked\0"
    "on_comboBox_2_currentIndexChanged\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PIS_SETTINGS[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       3,    1,   87,    2, 0x06 /* Public */,
       4,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   93,    2, 0x0a /* Public */,
       6,    1,   94,    2, 0x0a /* Public */,
       7,    0,   97,    2, 0x0a /* Public */,
       8,    1,   98,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    1,  102,    2, 0x0a /* Public */,
      11,    0,  105,    2, 0x0a /* Public */,
      12,    0,  106,    2, 0x0a /* Public */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    1,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QStringList,    2,
    QMetaType::QStringList,
    QMetaType::QStringList,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

void PIS_SETTINGS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PIS_SETTINGS *_t = static_cast<PIS_SETTINGS *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StartSimulation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->changeLogFreq((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->selectRoute((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->tab_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_2_clicked(); break;
        case 6: _t->text_edited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->resize_and_show_keywidget(); break;
        case 8: { int _r = _t->updateCoach((*reinterpret_cast< QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { QStringList _r = _t->getPISInfoList();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 10: { QStringList _r = _t->getPISInfoData();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 11: _t->on_save_clicked(); break;
        case 12: _t->on_close_clicked(); break;
        case 13: _t->on_comboBox_2_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PIS_SETTINGS::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PIS_SETTINGS::StartSimulation)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PIS_SETTINGS::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PIS_SETTINGS::changeLogFreq)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PIS_SETTINGS::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PIS_SETTINGS::selectRoute)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject PIS_SETTINGS::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PIS_SETTINGS.data,
      qt_meta_data_PIS_SETTINGS,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PIS_SETTINGS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PIS_SETTINGS::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PIS_SETTINGS.stringdata0))
        return static_cast<void*>(const_cast< PIS_SETTINGS*>(this));
    return QWidget::qt_metacast(_clname);
}

int PIS_SETTINGS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void PIS_SETTINGS::StartSimulation(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PIS_SETTINGS::changeLogFreq(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PIS_SETTINGS::selectRoute(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
