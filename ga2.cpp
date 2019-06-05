#include <bits/stdc++.h>
#include "ga.h"
using namespace std;
vector<LAOUT> laout;
vector<string> outL, outR;
int pos;
const static string empteyString = "ε";
int idd;

void init();
void addOut(string b, string s);
void Error(string name, int h, int type);
bool check(int key);
void checkAndErr(int k, string n, int h, int type);
void STMTS();
void STMT();
void REST0();
void LOC();
void RESTA();
void ELIST();
void REST1();
void REST4();
void REST5();
void REST6();
void REL();
void BOOL();
void EQUALITY();
void ROP_EXPR();
void EXPR();
void TERM();
void UNARY();
void FACTOR();

int main()
{
    init();
    STMTS();
    cout << endl;
    cout << "stmts"
         << "\t=> " << endl;
    string origin = "stmts ";
    for (int i = 0; i < outL.size(); ++i)
    {
        int p = origin.find(outL[i]);
        origin.replace(p, outL[i].size(), outR[i]);
        cout << origin << endl;
    }
}

void init()
{
    pos = 0;
    idd = 0;
    outL.clear();
    outR.clear();
    laout.clear();
    int type, num;
    string keyValue;
    cin >> num;
    for (int i = 0; i < num; ++i)
    {
        cin >> type >> keyValue;
        laout.push_back(LAOUT(type, keyValue));
    }
}
void addOut(string b, string s)
{
    cout << b << " -> " << s << endl;
    outL.push_back(b);
    if(s==empteyString) s="";
    outR.push_back(s);
}
void Error(string name, int h, int type = -1)
{
    cout << "************" << endl;

    cout << name << "\t" << h << "\t";
    if (type != -1)
    {
        cout << type << endl;
    }
    else
    {
        cout << endl;
    }
    cout << "************" << endl;
    exit(0);
}
bool check(int key)
{
    return laout[pos].key == key;
}
void checkAndErr(int k, string n, int h, int type = -1)
{
    if (!check(k))
    {
        Error(n, h, type);
    }
    pos++;
}
void STMTS()
{
    int height = idd++;
    string name = "stmts";
    addOut(name, "stmt rest0");
    STMT();
    REST0();
}
void STMT()
{
    int height = idd++;
    string name = "stmt";
    if (check(reserveIf))
    {
        pos++;
        addOut(name, "if ( bool ) stmt else stmt");
        checkAndErr(charLSB, name, height, 1);
        BOOL();
        checkAndErr(charRSB, name, height);
        STMT();
        checkAndErr(reserveElse, name, height, 2);
        STMT();
    }
    else if (check(reserveWhile))
    {
        pos++;
        addOut(name, "while ( bool ) stmt");
        checkAndErr(charLSB, name, height, 3);
        BOOL();
        checkAndErr(charRSB, name, height, 4);
        STMT();
    }
    else
    {
        addOut(name, "loc = expr ;");
        LOC();
        checkAndErr(charEqu, name, height, 5);
        EXPR();
        checkAndErr(charSem, name, height, 6);
    }
}
void REST0()
{
    int height = idd++;
    string name = "rest0";
    if (pos < laout.size())
    {
        addOut(name, "stmt rest0");
        STMT();
        REST0();
    }
    else
    {
        addOut(name, empteyString);
    }
}
void LOC()
{
    int height = idd++;
    string name = "loc";
    addOut(name, "id resta");
    checkAndErr(VarVaule, name, height);
    RESTA();
}
void RESTA()
{
    int height = idd++;
    string name = "resta";
    if (check(charLMB))
    {
        pos++;
        addOut(name, "[ elist ]");
        ELIST();
        checkAndErr(charRMB, name, height);
    }
    else
    {
        addOut(name, empteyString);
    }
}
void ELIST()
{
    int height = idd++;
    string name = "elist";
    addOut(name, "expr rest1");
    EXPR();
    REST1();
}
void REST1()
{
    int height = idd++;
    string name = "rest1";
    if (check(charCom))
    {
        pos++;
        addOut(name, "[ elist ]");
        EXPR();
        REST1();
    }
    else
    {
        addOut(name, empteyString);
    }
}
void BOOL()
{
    int height = idd++;
    string name = "bool";
    addOut(name, "equality");
    EQUALITY();
}
void EQUALITY()
{
    int height = idd++;
    string name = "equality";
    addOut(name, "rel rest4");
    REL();
    REST4();
}
void REST4()
{
    int height = idd++;
    string name = "rest4";
    if (check(tcharEquEqu))
    {
        pos++;
        addOut(name, "== rel rest4");
        REL();
        REST4();
    }
    else if (check(tcharNotEqu))
    {
        pos++;
        addOut(name, "!= rel rest4");
        REL();
        REST4();
    }
    else
    {
        addOut(name, empteyString);
    }
}
void REL()
{
    int height = idd++;
    string name = "rel";
    addOut(name, "expr rop_expr");
    EXPR();
    ROP_EXPR();
}
void ROP_EXPR()
{
    int height = idd++;
    string name = "rop_expr";
    if (check(charSma))
    {
        pos++;
        addOut(name, "< expr");
        EXPR();
    }
    else if (check(tcharSmaEqu))
    {
        pos++;
        addOut(name, "<= expr");
        EXPR();
    }
    else if (check(charBig))
    {
        pos++;
        addOut(name, "> expr");
        EXPR();
    }
    else if (check(tcharBigEqu))
    {
        pos++;
        addOut(name, ">= expr");
        EXPR();
    }
    else
    {
        addOut(name, empteyString);
    }
}
void EXPR()
{
    int height = idd++;
    string name = "expr";
    addOut(name, "term rest5");
    TERM();
    REST5();
}
void REST5()
{
    int height = idd++;
    string name = "rest5";
    if (check(charAdd))
    {
        pos++;
        addOut(name, "+ term rest5");
        TERM();
        REST5();
    }
    else if (check(charSub))
    {
        pos++;
        addOut(name, "- term rest5");
        TERM();
        REST5();
    }
    else
    {
        addOut(name, empteyString);
    }
}
void TERM()
{
    int height = idd++;
    string name = "term";
    addOut(name, "unary rest6");
    UNARY();
    REST6();
}
void REST6()
{
    int height = idd++;
    string name = "rest6";
    if (check(charMul))
    {
        pos++;
        addOut(name, "* unary rest6");
        UNARY();
        REST6();
    }
    else if (check(charDev))
    {
        pos++;
        addOut(name, "/ unary rest6");
        UNARY();
        REST6();
    }
    else
    {
        addOut(name, empteyString);
    }
}
void UNARY()
{
    int height = idd++;
    string name = "unary";
    addOut(name, "factor");
    FACTOR();
}
void FACTOR()
{
    int height = idd++;
    string name = "factor";
    if (check(charLSB))
    {
        pos++;
        addOut(name, "( expr )");
        EXPR();
        checkAndErr(charRSB, name, height);
    }
    else if (check(IntegerValue))
    {
        addOut(name, "num");
        pos++;
    }
    else
    {
        addOut(name, "loc");
        LOC();
    }
}
