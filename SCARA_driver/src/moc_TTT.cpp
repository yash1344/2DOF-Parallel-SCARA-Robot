/****************************************************************************
** Meta object code from reading C++ file 'TTT.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TTT.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TTT.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN3TTTE_t {};
} // unnamed namespace

template <> constexpr inline auto TTT::qt_create_metaobjectdata<qt_meta_tag_ZN3TTTE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TTT",
        "moveRequested",
        "",
        "HolderState",
        "player",
        "gameFinished",
        "winner",
        "piecePlaced",
        "row",
        "col",
        "state",
        "QList<QPointF>",
        "trajectory",
        "processUserMove",
        "Coordinate",
        "point"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'moveRequested'
        QtMocHelpers::SignalData<void(HolderState)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'gameFinished'
        QtMocHelpers::SignalData<void(HolderState)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 6 },
        }}),
        // Signal 'piecePlaced'
        QtMocHelpers::SignalData<void(int, int, HolderState, QVector<QPointF>)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::Int, 9 }, { 0x80000000 | 3, 10 }, { 0x80000000 | 11, 12 },
        }}),
        // Slot 'processUserMove'
        QtMocHelpers::SlotData<void(Coordinate)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TTT, qt_meta_tag_ZN3TTTE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TTT::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3TTTE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3TTTE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3TTTE_t>.metaTypes,
    nullptr
} };

void TTT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TTT *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->moveRequested((*reinterpret_cast< std::add_pointer_t<HolderState>>(_a[1]))); break;
        case 1: _t->gameFinished((*reinterpret_cast< std::add_pointer_t<HolderState>>(_a[1]))); break;
        case 2: _t->piecePlaced((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<HolderState>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QList<QPointF>>>(_a[4]))); break;
        case 3: _t->processUserMove((*reinterpret_cast< std::add_pointer_t<Coordinate>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 3:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QPointF> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TTT::*)(HolderState )>(_a, &TTT::moveRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TTT::*)(HolderState )>(_a, &TTT::gameFinished, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TTT::*)(int , int , HolderState , QVector<QPointF> )>(_a, &TTT::piecePlaced, 2))
            return;
    }
}

const QMetaObject *TTT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TTT::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3TTTE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TTT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TTT::moveRequested(HolderState _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void TTT::gameFinished(HolderState _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void TTT::piecePlaced(int _t1, int _t2, HolderState _t3, QVector<QPointF> _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3, _t4);
}
QT_WARNING_POP
