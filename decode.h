#ifndef DECODE_H
#define DECODE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class Decode
{
public:
    enum Type {Chat, LoginResult, RegistResult};
    Decode();

    const int Type();
    const vector<vector<char>> & DataBytesList();

protected:
    int type;
    vector<vector<char>> dataBytesList;
};

class DecodeTCP : public Decode
{
public:
    DecodeTCP(const char * rawData);
};

class DcdChat
{
public:
    DcdChat(DecodeTCP * dcdtcp);
    const string Name();
    const string Msg();
private:
    string name;
    string msg;
};

class DcdLoginResult
{
public:
    DcdLoginResult(DecodeTCP * dcdtcp);
    const bool IsLogined();
    const string Ment();

private:
    bool isLogined;
    string ment;
};

class DcdRegistResult
{
public:
    DcdRegistResult(DecodeTCP * dcdtcp);
    const bool IsRegisted();
    const string Ment();

private:
    bool isRegisted;
    string ment;
};

#endif // DECODE_H
