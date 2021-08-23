#ifndef DATAMAKER_H
#define DATAMAKER_H
#include <iostream>
#include <array>
#include "data.h"
#include <vector>
#include <memory>
class DataMaker
{
private:
    /* data */
public:
    DataMaker(/* args */) = default;
    ~DataMaker() = default;
    virtual Data* getRandomData() = 0;
    virtual std::shared_ptr<std::vector<Data*>> getDataPtrVector(int n) = 0;
};

#endif // !DATAMAKER_H