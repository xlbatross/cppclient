#include "decode.h"

Decode::Decode()
{

}

const int Decode::Type()
{
    return type;
}

const vector<vector<char> > &Decode::DataBytesList()
{
    return dataBytesList;
}

// tcp start
DecodeTCP::DecodeTCP(const char * rawData)
{
    int pointer = 0;
    int headerSize = 0;
    int dataLength = 0;
    vector<int> dataLengthList;

    // ó�� 4����Ʈ�� ����� ����
    memcpy(&headerSize, rawData + pointer, sizeof(int));
    pointer += sizeof(int);

    // ���� 4����Ʈ�� ��û �Ǵ� ���� Ÿ��
    memcpy(&type, rawData + pointer, sizeof(int));
    pointer += sizeof(int);

    // ���� 4����Ʈ���� ��� �������� �ǹ��ִ� ������ �ϳ��� ���̰���
    for (int i = 0; i < headerSize - sizeof(int); i += sizeof(int))
    {
        memcpy(&dataLength, rawData + pointer, sizeof(int));
        dataLengthList.push_back(dataLength);
        pointer += sizeof(int);
    }

    if (dataLengthList.size() > 0)
    {
        // ���� �ο쵥���͸� �ǹ��ִ� �����͵�� ��ȯ
        for (int i = 0; i < dataLengthList.size(); i++)
        {
            vector<char> dataBytes(dataLengthList[i]);
            std::copy(rawData + pointer, rawData + pointer + dataLengthList[i], dataBytes.begin());
            dataBytesList.push_back(dataBytes);
            pointer += dataLengthList[i];
        }
    }
}

DcdChat::DcdChat(DecodeTCP *dcdtcp)
{
    name.append(dcdtcp->DataBytesList()[0].data(), dcdtcp->DataBytesList()[0].size());
    msg.append(dcdtcp->DataBytesList()[1].data(), dcdtcp->DataBytesList()[1].size());
}

const string DcdChat::Name()
{
    return name;
}

const string DcdChat::Msg()
{
    return msg;
}

DcdLoginResult::DcdLoginResult(DecodeTCP *dcdtcp)
{
    int loginState;
    memcpy(&loginState, dcdtcp->DataBytesList()[0].data(), dcdtcp->DataBytesList()[0].size());

    switch(loginState)
    {
        case -2:
            isLogined = false;
            ment = "�̹� �α����� ���̵��Դϴ�.";
            break;
        case -1:
            isLogined = false;
            ment = "�����ͺ��̽����� ���� ����";
            break;
        case 0:
            isLogined = false;
            ment = "���̵� �Ǵ� ��й�ȣ�� ���� �ʽ��ϴ�.";
            break;
        case 1:
            isLogined = true;
            ment = "�α��� ����!";
            break;
    }
}

const bool DcdLoginResult::IsLogined()
{
    return isLogined;
}

const string DcdLoginResult::Ment()
{
    return ment;
}

DcdRegistResult::DcdRegistResult(DecodeTCP *dcdtcp)
{
    int registState;
    memcpy(&registState, dcdtcp->DataBytesList()[0].data(), dcdtcp->DataBytesList()[0].size());

    switch(registState)
    {
        case -2:
            isRegisted = false;
            ment = "�̹� ������ ���̵� �����մϴ�.";
            break;
        case -1:
            isRegisted = false;
            ment = "�����ͺ��̽����� ���� ����";
            break;
        case 0:
            isRegisted = true;
            ment = "ȸ������ ����!";
            break;
    }
}

const bool DcdRegistResult::IsRegisted()
{
    return isRegisted;
}

const string DcdRegistResult::Ment()
{
    return ment;
}


// // udp start
// ResponseUDP::ResponseUDP()
// {

// }

// ResponseUDP::ResponseUDP(const char *rawData, const int totalDataSize)
// {
//     int pointer = 0;

//     memcpy(&responseType, rawData + pointer, sizeof(int));
//     pointer += sizeof(int);

//     memcpy(&seqNum, rawData + pointer, sizeof(int));
//     pointer += sizeof(int);

//     vector<char> dataBytes(totalDataSize - pointer);
//     std::copy(rawData + pointer, rawData + totalDataSize, dataBytes.begin());
//     dataBytesList.push_back(dataBytes);
// }

// const int ResponseUDP::SeqNum()
// {
//     return seqNum;
// }
// // udp end



