#ifndef STCDATAMAKER_H
#define STCDATAMAKER_H
#include "data/stcdata.h"
#include "data/data.h"
#include "data/datamaker.h"
#include "stc/matrix_control.h"
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

    Data* getRandomData(int limit){
        Data* tmp = new StcData();
        Eigen::MatrixXi* mat = new Eigen::MatrixXi(1,2);
        mat->setRandom();
        for(int i = 0; i < 1; i++)
            for(int j = 0; j < 2; j++)
                (*mat)(i,j) = abs((*mat)(i,j))%limit;
        tmp->setData(static_cast<void *>(mat));
        return tmp;
    }


    std::shared_ptr<std::vector<Data*>> getDataPtrVector(int n,int limit){
        auto res = std::make_shared< std::vector<Data*> >();
        while(n--){
            res->push_back(getRandomData(limit));
        }
        return res;
    }

};

#endif // !STCDATAMAKER_H
