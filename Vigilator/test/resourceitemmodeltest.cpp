#include "ResourceItemModelTest.h"

#include <QtTest/QtTest>
#include <QObject>

void ResourceItemModelTest::initTestCase() {
    // Runs once before tests
}

void ResourceItemModelTest::test_data() {
    ResourcesList list;
    list.appendItem("CPU", new ResourceStatus());

    ResourceItemModel model;
    model.setList(&list);

    QModelIndex index = model.index(0, 0);
    QCOMPARE(model.data(index, Qt::DisplayRole).toString(), QString("CPU"));
    // or use your custom roles
}

void ResourceItemModelTest::test_data_two() {
    ResourcesList list;
    list.appendItem("CPU", new ResourceStatus());

    ResourceItemModel model;
    model.setList(&list);

    QModelIndex index = model.index(0, 0);
    QCOMPARE(QString("CPU"), QString("CPU"));
}

static ResourceItemModelTest TEST_QSTRING;
