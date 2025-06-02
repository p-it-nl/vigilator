#ifndef CONDITIONVALIDATORTEST_H
#define CONDITIONVALIDATORTEST_H

#include "testclass.h"
#include <QObject>

class ConditionValidatorTest : public TestClass {
    Q_OBJECT

public:
    using TestClass::TestClass;

private slots:
    void initTestCase();
    void test_data();
};


#endif // CONDITIONVALIDATORTEST_H
