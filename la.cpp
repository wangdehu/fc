#include <bits/stdc++.h>
#include "la.h"
using namespace std;

int pos;
map<string, int> reserveWord;
map<char, int> sOp;
map<tChar, int> dOp;
string token, code;
vector<LAOUT> outRes;
void init()
{
    pos = 0;
    reserveWord.clear();
    sOp.clear();
    dOp.clear();
    outRes.clear();
}
void addConst()
{
    reserveWord["int"] = reserveInt;
    reserveWord["else"] = reserveElse;
    reserveWord["if"] = reserveIf;
    reserveWord["while"] = reserveWhile;

    sOp['+'] = charAdd;
    sOp['-'] = charSub;
    sOp['*'] = charMul;
    sOp['/'] = charDev;
    sOp['%'] = charMod;
    sOp['='] = charEqu;
    sOp['>'] = charBig;
    sOp['<'] = charSma;
    sOp['!'] = charNot;

    sOp['('] = charLSB;
    sOp[')'] = charRSB;
    sOp['['] = charLMB;
    sOp[']'] = charRMB;
    sOp['{'] = charLLB;
    sOp['}'] = charRLB;
    sOp[';'] = charSem;
    sOp[','] = charCom;

    dOp[tChar('>', '=')] = tcharBigEqu;
    dOp[tChar('<', '=')] = tcharSmaEqu;
    dOp[tChar('=', '=')] = tcharEquEqu;
    dOp[tChar('!', '=')] = tcharNotEqu;
    dOp[tChar('&', '&')] = tcharAndAnd;
    dOp[tChar('|', '|')] = tcharOrOr;
    dOp[tChar('+', '+')] = tcharAddAdd;
    dOp[tChar('-', '-')] = tcharSubSub;
}
string readFileIntoString(string filename)
{
    ifstream ifile(filename);
    ostringstream buf;
    char ch;
    while (buf && ifile.get(ch))
        buf.put(ch);
    return buf.str();
}
bool isDigit(char x)
{
    if (x >= '0' && x <= '9')
        return true;
    return false;
}
bool isLetter(char x)
{
    if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || x == '_')
        return true;
    return false;
}
int getWord()
{
    while (pos == code.size())
    {
        return 0;
    }
    char ch = code[pos];
    int res = 0;
    while (ch == ' ')
        ch = code[++pos];
    token.clear();

    if (isLetter(ch))
    {
        token += ch;
        ch = code[++pos];
        while (isLetter(ch) || isDigit(ch))
        {
            token += ch;
            ch = code[++pos];
        }
        res = reserveWord[token];
        if (res == 0)
            res = VarVaule;
    }
    else if (isDigit(ch))
    {
        bool dotFlag = false;
        while (isDigit(ch) || ch == '.')
        {
            // cout<<"ch == "<<ch<<endl;
            if (ch == '.')
            {
                if (dotFlag)
                {
                    cout << "float error";
                    exit(0);
                }
                else
                {
                    dotFlag = true;
                    token += ch;
                }
                ch = code[++pos];
                continue;
            }
            token += ch;
            ch = code[++pos];
        }
        if (dotFlag)
            res = FloatValue;
        else
            res = IntegerValue;
    }
    else
    {
        token += ch;
        pos++;
        if (pos + 1 < code.size() && dOp[tChar(ch, code[pos])] != 0)
        {
            token += code[pos];
            res = dOp[tChar(ch, code[pos])];
            pos++;
        }
        else
        {
            res = sOp[ch];
            if (res == 0)
            {
                cout << "pos = " << pos - 1 << endl;
                cout << "ch = " << ch << endl;
                cout << "token = " << token;
                cout << "cant understand" << endl;
                exit(0);
            }
        }
    }
    return res;
}
void removeComment() {}

int main()
{
    init();
    addConst();

    code = readFileIntoString(LAinFile);
    // cout << "code :" << endl
    //      << code << endl;
    // removeComment();

    // cout << "********begin*********" << endl;
    while (1)
    {
        int res = getWord();
        if (res == 0)
        {
            // cout << "********end***********" << endl;
            break;
        }
        outRes.push_back(LAOUT(res, token));
    }
    int num = outRes.size();
    cout << num << endl;
    for (int i = 0; i < num; ++i)
    {
        cout << outRes[i].key << " " << outRes[i].token << endl;
    }
}
