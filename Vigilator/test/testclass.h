#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>

class TestClass: public QObject
{
public:
    TestClass();

    static std::vector<QObject*> & suite();
};

#endif // TESTCLASS_H
