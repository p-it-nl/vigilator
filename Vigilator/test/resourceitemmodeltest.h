#ifndef RESOURCEITEMMODELTEST_H
#define RESOURCEITEMMODELTEST_H

#include "testclass.h"
#include <QObject>
#include <resourceitemmodel.h>
#include <resourceslist.h>

class ResourceItemModelTest : public TestClass {
    Q_OBJECT

public:
    using TestClass::TestClass;

private slots:
    void initTestCase();
    void test_data();
    void test_data_two();
};


#endif // RESOURCEITEMMODELTEST_H
