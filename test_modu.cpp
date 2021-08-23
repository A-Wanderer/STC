#include <iostream>
#include <random>
#include <chrono>
#include <time.h>
#include "psk/STCControl.h"
#include "psk/PskMod.h"

int main(){
  STCControl aa;
  Eigen::MatrixXi a(1, 2);//data
  a << 1, 2;
  Eigen::MatrixXcd e(1, 2);//fade
  e.setRandom();

  auto b = aa.dataModulate(8,a);
  aa.channelFade(b, e);
  auto c = aa.dataDeModulate(8, b, e);
  cout << c << "\n";
  return 0;
}
