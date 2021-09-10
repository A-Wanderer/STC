#include <iostream>
#include <random>
#include <chrono>
#include <time.h>
#include "stc/stc_control.h"
#include "stc/psk_mod.h"

int main(){
  auto aa = STCControl::getSTCControl();
  Eigen::MatrixXi a(1, 2);//data
  a << 4, 3;
  Eigen::MatrixXcd e(1, 2);//fade
  e.real() << 0.5, 0.5;
  e.imag() << 0.5, 0.5;

  auto b = aa->dataModulate(8,a);
  aa->channelFade(b, e);
  std::cout<<b.rows()<<" "<<b.cols()<<"\n";
  auto c = aa->dataDeModulate(8, b, e);
  cout << c << "\n";
  return 0;
}
