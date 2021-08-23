#ifndef MATRIXCONTROL_CPP
#define MATRIXCONTROL_CPP

#include "MatrixControl.h"
#include <iostream>
#include <string>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

MatrixControl* getMatrixControl(){
  static MatrixControl matrix_control;
  return &matrix_control;
}

std::string MatrixControl::matrixXiToString(Eigen::MatrixXi &mat){
  std::string data;
  int col = mat.cols(), row = mat.rows();
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col;j++){
      data += std::to_string(mat(i, j)) + " ";
    }
  }
  return data;
}

std::string MatrixControl::matrixXcdToString(Eigen::MatrixXcd &mat){
  std::string data;
  int col = mat.cols(), row = mat.rows();
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col;j++){
      data += std::to_string(mat(i, j).real()) + " " + std::to_string(mat(i, j).imag()) + " ";
    }
  }
  return data;
}

Eigen::MatrixXi MatrixControl::stringToMatrixXi(std::string &str, int row, int col){
  Eigen::MatrixXi res(row, col);
  std::stringstream out(str);
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col;j++){
      int num;
      out >> num;
      res(i, j) = num;
    }
  }
  return res;
}

Eigen::MatrixXcd MatrixControl::stringToMatrixXcd(std::string &str, int row, int col){
  Eigen::MatrixXcd res(row, col);
  std::stringstream out(str);
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col;j++){
      double real, imag;
      out >> real >> imag;
      res(i, j).real(real);
      res(i, j).imag(imag);
    }
  }
  return res;
}
#endif