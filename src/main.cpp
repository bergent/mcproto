#include "mcproto/java/types/identifier.h"
#include <mcproto/java/types/basic_types.h>
#include <mcproto/java/types/vars.h>
#include <mcproto/java/types/string.h>
#include <mcproto/common/utils.h>
#include <string>
#include <iostream>


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    uint8_t packet [1024] {};

    mcp::Byte bt (111);
    mcp::String hello {"hello, world!"};
    mcp::Identifier myid {"block", "mixer"};

    uint8_t* pbegin = packet;
    uint8_t* pcopy = pbegin;

    uint8_t* pend = packet + 1024;

    bt.encode(pbegin, pend);
    hello.encode(pbegin, pend);
    myid.encode(pbegin, pend);

    std::cout << pbegin - pcopy << '\n';


    int fd = socket(AF_INET, SOCK_STREAM, 0);

    std::string ip_str {"127.0.0.1"};
    uint32_t ip {};
    inet_pton(AF_INET, ip_str.c_str(), &ip);

    sockaddr_in sin {};
    sin.sin_addr.s_addr = ip;
    sin.sin_port = htons(25565);
    sin.sin_family = AF_INET;
    
    
    int connect_rc = connect(fd, (const sockaddr*)&sin, sizeof(sin));
    perror("connect");

    int write_rc = write(fd, packet, pbegin - pcopy);
    perror("write");
    std::cout << write_rc << '\n';
}
