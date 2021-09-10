#ifndef PSKMOD_CPP
#define PSKMOD_CPP

#include "stc/psk_mod.h"
#include "stc/matrix_control.h"
#include <iostream>
#include <string>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
using namespace std;

PskMod* PskMod::getPskMod(){
  static PskMod PskModImpl;
  return &PskModImpl;
}

int PskMod::runCmd(const std::string& cmd, std::string& out) {
	FILE* fp = popen(cmd.c_str(), "r");
	if (!fp) {
		return errno == 0 ? -1 : errno;
	}
  char buffer[4096] = {0};
  while(!feof(fp)){
		size_t len = fread(buffer, 1, 4096, fp);
		if(len > 0) out.append(buffer, len);
	}
	return pclose(fp);
}

Eigen::MatrixXcd PskMod::modulate(int max_num, Eigen::MatrixXi mat){
  int col = mat.cols(), row = mat.rows();
  auto control = MatrixControl::getMatrixControl();
  string &&data = control->matrixXiToString(mat), ans;
  modulate(max_num, data, ans);
  Eigen::MatrixXcd &&res = control->stringToMatrixXcd(ans, row, col);
  return res;
}

int PskMod::modulate(int max_num, std::string &data, std::string& out){
  string cmd = "python3 psk/Pskmod.py modulate " + to_string(max_num) + " " + data;
  return runCmd(cmd, out);
}

Eigen::MatrixXi PskMod::deModulate(int max_num, Eigen::MatrixXcd mat){
  int col = mat.cols(), row = mat.rows();
  auto control = MatrixControl::getMatrixControl();
  string &&data = control->matrixXcdToString(mat), ans;
  deModulate(max_num, data, ans);
  Eigen::MatrixXi &&res = control->stringToMatrixXi(ans, row, col);
  return res;
}

int PskMod::deModulate(int max_num, std::string &data, std::string& out){
  string cmd = "python3 psk/Pskmod.py demodulate " + to_string(max_num) + " " + data;
  return runCmd(cmd, out);
}
/*
int main(int argc, char *argv[])
{
  string ans;
  auto a = PskMod();
  Eigen::MatrixXi b(2, 2);
  b << 2, 2, 2, 2;
  auto ok = a.Modulate(8, b);
  auto ok2 = a.DeModulate(8, ok);
  return 0;
}
*/

#endif