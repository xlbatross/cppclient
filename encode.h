#ifndef ENCODE_H
#define ENCODE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class Encode
{
public:
    enum EncodeType {Chat, Login, Regist};
    Encode();
    virtual ~Encode();

    virtual void packaging(const int type) = 0;

    const int Type();
    const int HeaderSize();
    const char * HeaderBytes();

    const int DataSize();
    const char * DataBytes();

protected:
    int type = -1;
    vector<vector<char>> dataBytesList;

    int headerSize = 0;
    char * headerBytes = NULL;
    
    int dataSize = 0;
    char * dataBytes = NULL;
};

class EncodeTCP : public Encode
{
public:
    EncodeTCP();
    void packaging(const int type) override;
};

class EcdChat: public EncodeTCP
{
public:
    EcdChat(const string & msg);
};

class EcdLogin: public EncodeTCP
{
public:
    EcdLogin(const string & id, const string & pw);
};

class EcdRegist: public EncodeTCP
{
public:
    EcdRegist(const string & id, const string & pw, const string & name);
};

#endif // ENCODE_H
