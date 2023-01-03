#ifndef CLIENTL_H
#define CLIENTL_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "encode.h"
#include "decode.h"

class ClientL
{
public:
    explicit ClientL();
    ~ClientL();

    string sockIp();
    int sockPort();

    virtual bool connectServer(const char * servIp = "127.0.0.1", int port = 2500);
    virtual int receiveBytes(char * & rawData) = 0;
    virtual bool receiveData(Decode * & ecd) = 0;
    virtual int sendBytes(const char * headerBytes, const int headerSize, const char * dataBytes, const int dataSize) = 0;
    virtual bool sendData(Encode * ecd);

protected:
    int sock;
    struct sockaddr_in myAdr;
    struct sockaddr_in servAdr;

    bool setSockInfo();
};

class ClientLTCP : public ClientL
{
public:
    explicit ClientLTCP();

    int receiveBytes(char * & rawData) override;
    bool receiveData(Decode * & ecd) override;
    int sendBytes(const char * headerBytes, const int headerSize, const char * dataBytes, const int dataSize) override;
};

class ClientLUDP : public ClientL
{
public:
    explicit ClientLUDP();

    int receiveBytes(char * & rawData) override;
    bool receiveData(Decode * & ecd) override;
    int sendBytes(const char * headerBytes, const int headerSize, const char * dataBytes, const int dataSize) override;
};


#endif // CLIENTL_H
