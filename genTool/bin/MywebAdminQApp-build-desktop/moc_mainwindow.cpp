/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Feb 2 22:17:33 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MywebAdminQApp/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      28,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      55,   50,   11,   11, 0x08,
      78,   11,   11,   11, 0x08,
      90,   11,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,
     131,   11,   11,   11, 0x08,
     144,   11,   11,   11, 0x08,
     155,   11,   11,   11, 0x08,
     167,   11,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0connect2mysql()\0about()\0"
    "load_topics()\0text\0filter_topics(QString)\0"
    "new_topic()\0save_topic()\0delete_topic()\0"
    "edit_topic()\0load_lists()\0new_list()\0"
    "save_list()\0delete_list()\0edit_list()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->connect2mysql(); break;
        case 1: _t->about(); break;
        case 2: _t->load_topics(); break;
        case 3: _t->filter_topics((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->new_topic(); break;
        case 5: _t->save_topic(); break;
        case 6: _t->delete_topic(); break;
        case 7: _t->edit_topic(); break;
        case 8: _t->load_lists(); break;
        case 9: _t->new_list(); break;
        case 10: _t->save_list(); break;
        case 11: _t->delete_list(); break;
        case 12: _t->edit_list(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
