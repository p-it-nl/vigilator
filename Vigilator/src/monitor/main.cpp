#include <monitor.h>
#include <monitoreddata.h>
#include <monitoredresourcereader.h>
#include <exposedresource.h>
#include <internalresource.h>
#include <onboardresource.h>
#include <iostream>
#include <thread>

int main()
{
    try {
        Monitor* monitor = Monitor::getInstance();
        monitor->setUp(new QObject());
        monitor->execute();

        clock_t start = clock();
        while ( (clock() - start)/CLOCKS_PER_SEC <= 88) {
            std::cout << (clock() - start)/CLOCKS_PER_SEC <<std::endl;

            std::this_thread::sleep_for(std::chrono::duration<int>(1));
        }

        std::cout << "finished MAIN" << std::endl;
    } catch (char const* ex) {
        std::cout << ex << std::endl;
    }

    /* tests below
    std::cout << fibonacci(1);
    std::cout << "Hello World!" << std::endl;

    Date d;
    d.Year = 2016;
    d.Month = 7;
    d.Day = 22;
    std::cout << "Year:" << d.Year << std::endl
              << "Month:" << d.Month << std::endl
              << "Day:" << d.Day << std::endl;


    Monitor monitor;
    monitor.setUpdateFrequency(100);
    monitor.addResource(new OnboardResource("test", true));
    monitor.addResource(new ExposedResource("test2", "test2@url.com", true));
    monitor.addResource(new InternalResource("test2", true));
    monitor.dingAll();


    Base* bp = new Derived();
    bp->show();

    int numbers[5] = { 2, 4, -8, 12, 18};
    int min = numbers[0];
    int max = numbers[0];

    bp->getMinMax(numbers, 5, &min, &max);

    delete bp;


    int size = 5;
    int* secondRay = new int[size];

    // do something

    delete[] secondRay;// clear memory
    secondRay = nullptr;// clear pointer

    std::cout << "min: " << min << std::endl;
    std::cout << "max: " << max << std::endl;


    std::cout << "frequency " << monitor.getUpdateFrequency() << std::endl;


    monitor.clearResources();

    std::cout << std::endl;
    std::cout << "copy tests" << std::endl;

    MonitoredData data = MonitoredData("test");
    MonitoredData secondData = MonitoredData(data);

    std::cout << data.getData()<< std::endl;
    std::cout << secondData.getData()<< std::endl;

    std::cout << "done" << std::endl;

    MonitoredData* allocatedData = new MonitoredData("secondtest");
    MonitoredData* allocatedSecondData = new MonitoredData(*allocatedData);

    std::cout << allocatedData->getData()<< std::endl;
    std::cout << allocatedSecondData->getData()<< std::endl;

    delete allocatedData;
    delete allocatedSecondData;

    int* ray = new int[2];
    ray[0] = 1;
    ray[1] = 2;
    MonitoredData* dataWithTakes = new MonitoredData("testtake", &ray);
    MonitoredData* copyWithTakes = new MonitoredData(*dataWithTakes);

    std::cout << dataWithTakes->getData()<< std::endl;
    std::cout << copyWithTakes->getData()<< std::endl;

    int* oTakes = dataWithTakes->getTakes();
    for(int i = 0; i < 2; i++) {
        std::cout << oTakes[i] << std::endl;
    }
    delete dataWithTakes;

    int* takes = copyWithTakes->getTakes();
    for(int i = 0; i < 2; i++) {
        std::cout << takes[i] << std::endl;
    }
    std::cout << copyWithTakes->getData()<< std::endl;

    delete copyWithTakes;


    // files
    try {
        std::cout << "testing file streams\n";
        std::fstream outputFile;
        // can use OR operator :  ios::out | ios::app | ios::binary
        outputFile.open("C:/Users/Patrick/Desktop/werk_en_hobby/projects/vigilator/Vigilator/resources/output.vigilator", std::ios::out); // or ios::app, or ios::ate etc...
        if(outputFile.is_open()) {
            outputFile << "yes, hello, this is a test.\n";
            outputFile << "and this is a secondline";
        } else {
            throw false;
        }
        outputFile.close();
    } catch(bool closed) {
        std::cout << "not open";
    }
    try {
        std::fstream inputFile;
        inputFile.open("C:/Users/Patrick/Desktop/werk_en_hobby/projects/vigilator/Vigilator/resources/monitored-resources.conf", std::ios::in);
        if(inputFile.is_open()) {
            int buff = 1024;
            std::string line;
            while(getline(inputFile, line)) {
                std::cout << line << std::endl;
            }
        }else {
            throw "false";
        }
        inputFile.close();
    } catch(...) {// any exception type
        std::cout << "not open";
    }*/
}

/*
struct Date
{
    unsigned int Year : 13; // 2^13 = 8192, enough for "year" representation for long time
    unsigned int Month : 4; // 2^4 = 16, enough to represent 1-12 month values.
    unsigned int Day : 5;   // 32
};
*/
