#ifndef DATA_H
#define DATA_H
#include <cstring>
#include <iostream>
class Data
{
private:
    /* data */
public:
    Data(/* args */) = default;

    ~Data() = default;

    virtual void* getData() = 0;

    virtual void setData(void*) = 0;

    virtual void printData() = 0;
};

#endif // !DATA_H
