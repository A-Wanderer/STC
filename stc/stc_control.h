#ifndef STCCONTROL_H
#define STCCONTROL_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
class STCControl
{
private:
    /* data */
public:
  STCControl(/* args */) = default;

  ~STCControl() = default;

  static STCControl* getSTCControl();

  Eigen::MatrixXcd dataModulate(int max_num, Eigen::MatrixXi &mat);

  Eigen::MatrixXcd dataModulate(int max_num, Eigen::MatrixXi &&mat);

  void channelFade(Eigen::MatrixXcd &mat, Eigen::MatrixXcd &fade);

  Eigen::MatrixXi dataDeModulate(int max_num, Eigen::MatrixXcd &mat, Eigen::MatrixXcd &fade);

  Eigen::MatrixXi dataDeModulate(int max_num, Eigen::MatrixXcd &&mat, Eigen::MatrixXcd &fade);
};

#endif