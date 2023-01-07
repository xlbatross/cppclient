#include <iostream>
#include <thread>
#include <iconv.h>
// #include "clientw.h"
#include "clientl.h"
void receiveHandler(
    // ClientW * client
    ClientL * client
);

int main(int, char**) {
    // ClientW * client = new ClientWTCP();
    ClientL * client = new ClientLTCP();
    if (client->connectServer())
    {
        std::thread recvThread(receiveHandler, client);

        while (true)
        {
            std::cout << "input >> ";
            std::string k;
            getline(std::cin, k);
            EcdChat ecd(k);
            if (!client->sendData((Encode *)&ecd))
            {
                std::cout << "not connected" << std::endl;
                break;
            } 
        }
    }
    else
    {
        std::cout << "not connected" << std::endl;
    }
}

void receiveHandler(
    // ClientW * client
    ClientL * client
)
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
          DcdChat chat((DecodeTCP *)dcd);
          std::cout << chat.Name() << " : " << chat.Msg() << std::endl;
        } break;
        }

        delete dcd;
        if (ecd != NULL)
            delete ecd;
    }
}


