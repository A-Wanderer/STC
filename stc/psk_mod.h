#ifndef PSKMOD_H
#define PSKMOD_H

#include "stc/matrix_control.h"
#include <iostream>
#include <string>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
using namespace std;
class PskMod
{
private:
  /* data */
public:
  PskMod(/* args */) = default;

  ~PskMod() = default;

  static PskMod *getPskMod();

  int runCmd(const std::string &cmd, std::string &out);

  Eigen::MatrixXcd modulate(int max_num, Eigen::MatrixXi mat);

  int modulate(int max_num, std::string &data, std::string &out);

  Eigen::MatrixXi deModulate(int max_num, Eigen::MatrixXcd mat);

  int deModulate(int max_num, std::string &data, std::string &out);
};

#endif