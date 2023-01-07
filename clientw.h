#ifndef CLIENTW_H
#define CLIENTW_H

#include <string.h>
#include <winsock2.h>
#include "decode.h"
#include "encode.h"

class ClientW
{
public:
    explicit ClientW();
    ~ClientW();

    string sockIp();
    int sockPort();
    
    virtual bool connectServer(const char * servIp = "127.0.0.1", int port = 2500);
    virtual bool receiveData(Decode * & ecd) = 0;
    virtual bool sendData(Encode * ecd);

protected:
    WSADATA wsaData;

    SOCKET sock;
    SOCKADDR_IN myAdr;
    SOCKADDR_IN servAdr;

    bool setSockInfo();
    virtual int receiveBytes(char * & rawData) = 0;
    virtual int sendBytes(const char * headerBytes, const int headerSize, const char * dataBytes, const int dataSize) = 0;
};

class ClientWTCP : public ClientW
{
public:
    explicit ClientWTCP();
    bool receiveData(Decode * & ecd) override;

protected:
    int receiveBytes(char * & rawData) override;
    int sendBytes(const char * headerBytes, const int headerSize, const char * dataBytes, const int dataSize) override;
};

class ClientWUDP : public ClientW
{
public:
    explicit ClientWUDP();
    bool receiveData(Decode * & ecd) override;

protected:
    int receiveBytes(char * & rawData) override;
    int sendBytes(const char * headerBytes, const int headerSize, const char * dataBytes, const int dataSize) override;
};
#endif // CLIENTW_H