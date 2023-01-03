#include <iostream>
#include <thread>
#include "clientw.h"
void receiveHandler(ClientW * client);

int main(int, char**) {
    ClientW * client = new ClientWTCP();
    if (client->connectServer())
    {
        std::thread recvThread(receiveHandler, client);

        while (true)
        {
            std::cout << "input >> ";
            string k;
            std::cin >> k;
            EncodeChat ecd(k);
            client->sendData((Encode *)&ecd);
        }
    }
}

void receiveHandler(ClientW * client)
{
    while (true)
    {
        Encode * ecd = NULL;
        Decode * dcd = NULL;
        client->receiveData(dcd);

        if (dcd == NULL)
            break;

        switch(dcd->Type())
        {
        case Decode::Chat:
        {
          DecodeChat chat((DecodeTCP *)dcd);
          std::cout << "server : " << chat.Msg() << std::endl;
        } break;
        }

        delete dcd;
        if (ecd != NULL)
            delete ecd;
    }
}


