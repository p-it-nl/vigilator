#include "ConditionValidatorTest.h"

#include <QtTest/QtTest>
#include <QObject>

void ConditionValidatorTest::initTestCase() {
    // Runs once before tests
}

void ConditionValidatorTest::test_data() {

    QCOMPARE(QString("CPU"), QString("CPU"));
}

static ConditionValidatorTest TEST_QSTRING;
