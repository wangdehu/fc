#include <bits/stdc++.h>
using namespace std;
#define inFile "./example.in"
// #define outFile "./example.out"

#define constValue 100
#define varVaule 111
int pos;
map<string, int> reserveWord, opOrDel;
string token, code;
void init()
{
    pos = 0;
    reserveWord.clear();
    opOrDel.clear();
}
void addConst()
{
    reserveWord["int"] = 5;
    reserveWord["else"] = 15;
    reserveWord["if"] = 17;
    reserveWord["while"] = 20;

    opOrDel["+"] = 41;
    opOrDel["-"] = 42;
    opOrDel["*"] = 43;
    opOrDel["/"] = 44;
    opOrDel["%"] = 45;
    opOrDel["="] = 46;
    opOrDel[">"] = 47;
    opOrDel[">="] = 48;
    opOrDel["<"] = 49;
    opOrDel["<="] = 50;
    opOrDel["=="] = 52;
    opOrDel["!="] = 53;
    opOrDel["&&"] = 54;
    opOrDel["||"] = 55;
    opOrDel["++"] = 56;
    opOrDel["--"] = 57;

    opOrDel["("] = 81;
    opOrDel[")"] = 82;
    opOrDel[";"] = 84;
    opOrDel["["] = 88;
    opOrDel["]"] = 89;
    opOrDel["{"] = 86;
    opOrDel["}"] = 87;
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
            res = varVaule;
    }
    else if (isDigit(ch))
    {
        while (isDigit(ch))
        {
            token += ch;
            ch = code[++pos];
        }
        res = constValue;
    }
    else if (ch == '*' || ch == '/' || ch == '%' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';')
    {
        token += ch;
        res = opOrDel[token];
        pos++;
    }
    else if (ch == '+')
    {
        token += ch;
        ch = code[++pos];
        if (ch == '+')
        {
            token += ch;
            pos++;
        }
        res = opOrDel[token];
    }
    else if (ch == '-')
    {
        token += ch;
        ch = code[++pos];
        if (ch == '-')
        {
            token += ch;
            pos++;
        }
        res = opOrDel[token];
    }
    else if (ch == '=')
    {
        token += ch;
        ch = code[++pos];
        if (ch == '=')
        {
            token += ch;
            pos++;
        }
        res = opOrDel[token];
    }
    else if (ch == '>')
    {
        token += ch;
        ch = code[++pos];
        if (ch == '=')
        {
            token += ch;
            pos++;
        }
        res = opOrDel[token];
    }
    else if (ch == '<')
    {
        token += ch;
        ch = code[++pos];
        if (ch == '=')
        {
            token += ch;
            pos++;
        }
        res = opOrDel[token];
    }
    else if (ch == '!')
    {
        token += ch;
        ch = code[++pos];
        if (ch == '=')
        {
            token += ch;
            pos++;
        }
        res = opOrDel[token];
    }
    else if (ch == '&')
    {
        token += ch;
        ch = code[++pos];
        if (ch == '&')
        {
            token += ch;
            pos++;
        }
        res = opOrDel[token];
    }
    else if (ch == '|')
    {
        token += ch;
        ch = code[++pos];
        if (ch == '|')
        {
            token += ch;
            pos++;
        }
        res = opOrDel[token];
    }
    else
    {
        cout << "pos = " << pos << endl;
        cout << "ch = " << ch << endl;
        cout << "token = " << token;
        cout << "cant understand" << endl;
        exit(0);
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
