#include <bits/stdc++.h>
using namespace std;
#define inFile "./example.in"
// #define outFile "./example.out"
typedef pair<char, char> tChar;
#define IntegerValue 100
#define FloatValue 101
#define VarVaule 111

int pos;
map<string, int> reserveWord;
map<char, int> sOp;
map<tChar, int> dOp;
string token, code;
void init()
{
    pos = 0;
    reserveWord.clear();
    sOp.clear();
    dOp.clear();
}
void addConst()
{
    reserveWord["int"] = 5;
    reserveWord["else"] = 15;
    reserveWord["if"] = 17;
    reserveWord["while"] = 20;

    sOp['+'] = 41;
    sOp['-'] = 42;
    sOp['*'] = 43;
    sOp['/'] = 44;
    sOp['%'] = 45;
    sOp['='] = 46;
    sOp['>'] = 47;
    sOp['<'] = 49;

    sOp['('] = 81;
    sOp[')'] = 82;
    sOp[';'] = 84;
    sOp['['] = 88;
    sOp[']'] = 89;
    sOp['{'] = 86;
    sOp['}'] = 87;

    dOp[tChar('>', '=')] = 48;
    dOp[tChar('<', '=')] = 50;
    dOp[tChar('=', '=')] = 52;
    dOp[tChar('!', '=')] = 53;
    dOp[tChar('&', '&')] = 54;
    dOp[tChar('|', '|')] = 55;
    dOp[tChar('+', '+')] = 56;
    dOp[tChar('-', '-')] = 57;
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
        bool dotFlag=false;
        while (isDigit(ch)||ch=='.')
        {   
            // cout<<"ch == "<<ch<<endl;
            if(ch=='.'){
                if(dotFlag){
                    cout<<"float error";
                    exit(0);
                }else{
                    dotFlag=true;
                    token+=ch;
                }
                ch=code[++pos];
                continue;
            }
            token += ch;
            ch = code[++pos];
        }
        if(dotFlag) res=FloatValue;
        else res = IntegerValue;
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

    code = readFileIntoString(inFile);
    cout << "code :" << endl
         << code << endl;
    // removeComment();

    cout << "********begin*********" << endl;
    while (1)
    {
        int res = getWord();
        if (res == 0)
        {
            cout << "********end***********" << endl;
            break;
        }
        cout << res << "   " << token << endl;
    }
}
