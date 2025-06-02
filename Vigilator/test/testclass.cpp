#include "testclass.h"

TestClass::TestClass()
{
    suite().push_back(this);
}


std::vector<QObject*>& TestClass::suite()
{
    static std::vector<QObject*> objects;
    return objects;
}
