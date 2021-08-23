#ifndef STCDATA_H
#define STCDATA_H
#include "data.h"
#include "MatrixControl.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
class StcData:public Data
{
private:
    /* data */
    Eigen::MatrixXi* mat_;

public:
    StcData(/* args */) = default;
    ~StcData() = default;
    void setData(void* data){
        auto* mat = static_cast<Eigen::MatrixXi*>(data);
        this->mat_ = mat;
    };

    void* getData(){
        return static_cast<void*>(mat_);
    }

    void printData(){
        std::cout<<(*mat_)<<"\n";
    }

    std::string getStringStcData(){
        std::string str_data = "";
        MatrixControl control{};
        return control.matrixXiToString(*mat_);
    }
};
#endif // !STCDATA_H