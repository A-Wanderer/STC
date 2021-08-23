#include<iostream>
#include "data/stcdata.h"
#include "data/stcdatamaker.h"
#include <array>
#include <tuple>
#include <vector>
#include <eigen3/Eigen/Core>
int main(int argc, const char** argv) {

    auto *ab = new StcDataMaker();
    auto v = ab->getDataPtrVector(3);
    for(auto u: *v){
        u->printData();
    }
    return 0;
}