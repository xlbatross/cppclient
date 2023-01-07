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

    // 처음 4바이트는 헤더의 길이
    memcpy(&headerSize, rawData + pointer, sizeof(int));
    pointer += sizeof(int);

    // 다음 4바이트는 요청 또는 응답 타입
    memcpy(&type, rawData + pointer, sizeof(int));
    pointer += sizeof(int);

    // 다음 4바이트부터 헤더 끝까지는 의미있는 데이터 하나의 길이값들
    for (int i = 0; i < headerSize - sizeof(int); i += sizeof(int))
    {
        memcpy(&dataLength, rawData + pointer, sizeof(int));
        dataLengthList.push_back(dataLength);
        pointer += sizeof(int);
    }

    if (dataLengthList.size() > 0)
    {
        // 남은 로우데이터를 의미있는 데이터들로 변환
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
            ment = "이미 로그인한 아이디입니다.";
            break;
        case -1:
            isLogined = false;
            ment = "데이터베이스와의 연결 실패";
            break;
        case 0:
            isLogined = false;
            ment = "아이디 또는 비밀번호가 맞지 않습니다.";
            break;
        case 1:
            isLogined = true;
            ment = "로그인 성공!";
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
            ment = "이미 동일한 아이디가 존재합니다.";
            break;
        case -1:
            isRegisted = false;
            ment = "데이터베이스와의 연결 실패";
            break;
        case 0:
            isRegisted = true;
            ment = "회원가입 성공!";
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



