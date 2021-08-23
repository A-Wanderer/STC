#ifndef MATRIXCONTROL_H
#define MATRIXCONTROL_H

#include <iostream>
#include <string>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
class MatrixControl
{
private:
    /* data */
public:
    MatrixControl(/* args */) = default;
    ~MatrixControl() = default;
    static MatrixControl* getMatrixControl();
    std::string matrixXiToString(Eigen::MatrixXi &mat);
    std::string matrixXcdToString(Eigen::MatrixXcd &mat);
    Eigen::MatrixXi stringToMatrixXi(std::string &str, int row, int col);
    Eigen::MatrixXcd stringToMatrixXcd(std::string &str, int row, int col);
};

#endif
