#include <iostream>
#include "web/web_server.h"
#include "log/log.h"
int main(int argc, char const *argv[])
{
    /* code */
    const char* p = "192.168.71.129";
    int port = 54321;
    Eigen::MatrixXcd fade(1, 2);//fade
    fade.real() << 0.5, 0.5;
    fade.imag() << 0.5, 0.5;
    WebServer ser(p,port,fade);
    ser.start();
}
