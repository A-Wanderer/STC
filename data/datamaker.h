#ifndef DATAMAKER_H
#define DATAMAKER_H

#include "data/data.h"
#include <iostream>
#include <array>
#include <vector>
#include <memory>
class DataMaker
{
private:
    /* data */
public:
    DataMaker(/* args */) = default;

    ~DataMaker() = default;

    virtual Data* getRandomData(int limit) = 0;

    virtual std::shared_ptr<std::vector<Data*>>
                        getDataPtrVector(int n, int limit) = 0;
};

#endif // !DATAMAKER_H