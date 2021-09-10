#ifndef STCCONTROL_CPP
#define STCCONTROL_CPP

#include "stc/stc_control.h"
#include "stc/psk_mod.h"
#include <iostream>
#include <random>
#include <chrono>
#include <time.h>

STCControl* STCControl::getSTCControl() {
    static STCControl control;
    return &control;
}

Eigen::MatrixXcd STCControl::dataModulate(int max_num, Eigen::MatrixXi& mat) {
    return dataModulate(max_num, std::move(mat));
}

Eigen::MatrixXcd STCControl::dataModulate(int max_num, Eigen::MatrixXi&& mat) {
    assert(mat.rows() == 1 && mat.cols() == 2);
    auto* psk_contorl = PskMod::getPskMod();
    Eigen::MatrixXcd modu = psk_contorl->modulate(max_num, mat);
    Eigen::MatrixXcd data(2, 2);
    data(0, 0) = modu(0, 0);
    data(0, 1) = modu(0, 1);
    data(1, 0) = -modu.conjugate()(0, 1);
    data(1, 1) = modu.conjugate()(0, 0);
    return data;
}

void STCControl::channelFade(Eigen::MatrixXcd& mat, Eigen::MatrixXcd& fade) {
    mat = fade * mat.transpose();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    // 第一个参数为高斯分布的平均值，第二个参数为标准差
    std::normal_distribution<double> distribution(0.0, 0.1);
    int row = mat.rows(), col = mat.cols();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            double real = mat(i, j).real(), imag = mat(i, j).imag();
            mat(i, j).real(real + distribution(generator));
            mat(i, j).imag(imag + distribution(generator));
        }
    }
}


Eigen::MatrixXi STCControl::dataDeModulate(int max_num, Eigen::MatrixXcd&& mat, Eigen::MatrixXcd& fade) {
    return dataDeModulate(max_num,std::move(mat),fade);
}

Eigen::MatrixXi STCControl::dataDeModulate(int max_num, Eigen::MatrixXcd& mat, Eigen::MatrixXcd& fade) {
    Eigen::MatrixXcd fade_nex(2, 2), mat_nex(1, 2);
    mat_nex(0, 0) = mat(0, 0);
    mat_nex(0, 1) = mat.conjugate()(0, 1);
    fade_nex(0, 0) = fade(0, 0);
    fade_nex(0, 1) = fade(0, 1);
    fade_nex(1, 0) = fade.conjugate()(0, 1);
    fade_nex(1, 1) = -fade.conjugate()(0, 0);
    auto res = (fade_nex.adjoint() * fade_nex).inverse() * fade_nex.adjoint() * mat_nex.transpose();
    auto* control = PskMod::getPskMod();
    return control->deModulate(max_num, res);
}

#endif