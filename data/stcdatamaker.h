#ifndef STCDATAMAKER_H
#define STCDATAMAKER_H
#include "stcdata.h"
#include "data.h"
#include "datamaker.h"
#include "MatrixControl.h"
#include <vector>
#include <iostream>
#include <memory>
class StcDataMaker:public DataMaker
{
private:
    /* data */
public:
    StcDataMaker(/* args */) = default;
    ~StcDataMaker() = default;

    Data* getRandomData(){
        Data* tmp = new StcData();
        Eigen::MatrixXi* mat = new Eigen::MatrixXi(2,2);
        mat->setRandom();
        tmp->setData(static_cast<void *>(mat));
        return tmp;
    }


    std::shared_ptr<std::vector<Data*>> getDataPtrVector(int n){
        auto res = std::make_shared< std::vector<Data*> >();
        while(n--){
            res->push_back(getRandomData());
        }
        return res;
    }

};

#endif // !STCDATAMAKER_H
