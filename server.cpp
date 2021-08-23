#include <iostream>
#include "WebServer.h"
int main(int argc, char const *argv[])
{
    /* code */
    const char* p = "192.168.71.129";
    int port = 54321;
    WebServer fuck(p,port);
    fuck.prepare();
    fuck.work();
}
