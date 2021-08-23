#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <iostream>
#include "data/stcdatamaker.h"
#include "psk/STCControl.cpp"
#include "WebClient.h"
int main(int argc, char const *argv[])
{
    /* code */
    const char* p = "192.168.71.129";
    int port = 54321;
    auto cli = WebClient(p,port);
    cli.prepare();
    auto a = StcDataMaker();
    std::string c =static_cast<StcData*>(a.getRandomData())
                            ->getStringStcData();
    cli.sendMsg(c);
    return 0;
}
