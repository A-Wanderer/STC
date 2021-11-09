#include "data/stcdatamaker.h"
#include "stc/stc_control.h"
#include "web/web_client.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    /*
        假设信道衰落矩阵如下:
        ((0.5,0.5) (0.5,0.5))
    */
    Eigen::MatrixXcd fade(1, 2);//fade
    fade.real() << 0.5, 0.5;
    fade.imag() << 0.5, 0.5;

    /* prepare cli */
    const char* p = "127.0.0.1";
    int port = 54321;
    auto *cli = new WebClient(p,port);
    cli->prepare();

    /* prepare data */
    auto *maker = new StcDataMaker();
    auto *data =  static_cast<StcData*>(maker->getRandomData(5));
    std::cout<<"send msg :" + data->getStringStcData()<<"\n";
    /* pskmod */
    auto *control = new STCControl();
    auto psk_data = control->dataModulate(8,*(data->getStcData()));

    std::cout<<"psk msg :\n" << psk_data<<"\n";
    /* Start analog data incoming channel */
    control->channelFade(psk_data, fade);
    /* Send data to server */
    auto *mat_control = new MatrixControl();
    std::cout<<"msg cross fade channel :\n" << psk_data<<"\n";
    cli->sendMsg(mat_control->matrixXcdToString(psk_data));
    return 0;
}
