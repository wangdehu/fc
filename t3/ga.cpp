#include <bits/stdc++.h>
#include "ga.h"
#define Begin STMTS
using namespace std;
vector<LAOUT> laout;
vector<string> outL, outR;
int pos;
int idd;
int tmpId;

int main()
{
    init();
    Begin();
}
string newtemp()
{
    string res = "T" + to_string(++tmpId);
    return res;
}
void init()
{
    pos = 0;
    idd = 0;
    tmpId = 0;
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
#ifdef process
    cout << b << " -> " << s << endl;
#endif
    outL.push_back(b);
    if (s == empteyString)
        s = "";
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
void emit(string s)
{
    cout << s << endl;
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
        Attr loc = LOC();
        checkAndErr(charEqu, name, height, 5);
        Attr expr = EXPR();
        emit(loc.place + "=" + expr.place);
        cout<<loc.place<<" = "<<expr.val;
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
Attr LOC()
{
    Attr loc, id;
    int height = idd++;
    string name = "loc";
    addOut(name, "id resta");
    id.place = laout[pos].token;
    checkAndErr(VarVaule, name, height);
    Attr resta = RESTA(id);
    loc.place = resta.place;
    return loc;
}
Attr RESTA(Attr inArray)
{
    Attr resta;
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
        resta.place = inArray.place;
        addOut(name, empteyString);
    }
    return resta;
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
Attr EXPR()
{
    Attr expr;
    int height = idd++;
    string name = "expr";
    addOut(name, "term rest5");
    Attr term = TERM();
    Attr rest5 = REST5(term);
    expr.place = rest5.place;
    expr.val = rest5.val;

    //

    // cout << "expr.val = " << expr.val << endl;
    //
    return expr;
}
Attr REST5(Attr in)
{
    Attr rest5;
    int height = idd++;
    string name = "rest5";
    if (check(charAdd))
    {
        pos++;
        addOut(name, "+ term rest5");
        Attr term = TERM();
        string _rest5_in = newtemp();
        emit(_rest5_in + "=" + in.place + "+" + term.place);
        Attr _rest5 = REST5(Attr(in.val + term.val, _rest5_in));
        rest5.place = _rest5.place;
        rest5.val = _rest5.val;
    }
    else if (check(charSub))
    {
        pos++;
        addOut(name, "- term rest5");
        Attr term = TERM();
        string _rest5_in = newtemp();
        emit(_rest5_in + "=" + in.place + "-" + term.place);
        Attr _rest5 = REST5(Attr(in.val - term.val, _rest5_in));
        rest5.place = _rest5.place;
        rest5.val = _rest5.val;
    }
    else
    {
        addOut(name, empteyString);
        rest5.place = in.place;
        rest5.val = in.val;
    }
    return rest5;
}
Attr TERM()
{
    Attr term;
    int height = idd++;
    string name = "term";
    addOut(name, "unary rest6");
    Attr unary = UNARY();
    Attr rest6 = REST6(unary);
    term.place = rest6.place;
    term.val = rest6.val;
    return term;
}
Attr REST6(Attr in)
{
    Attr rest6;
    int height = idd++;
    string name = "rest6";
    if (check(charMul))
    {
        pos++;
        addOut(name, "* unary rest6");
        Attr unary = UNARY();
        string _rest6_in = newtemp();
        emit(_rest6_in + "=" + in.place + "*" + unary.place);
        Attr _rest6 = REST6(Attr(in.val * unary.val, _rest6_in));
        rest6.place = _rest6.place;
        rest6.val = _rest6.val;
    }
    else if (check(charDev))
    {
        pos++;
        addOut(name, "/ unary rest6");
        Attr unary = UNARY();
        string _rest6_in = newtemp();
        emit(_rest6_in + "=" + in.place + "/" + unary.place);
        Attr _rest6 = REST6(Attr(in.val / unary.val, _rest6_in));
        rest6.place = _rest6.place;
        rest6.val = _rest6.val;
    }
    else
    {
        addOut(name, empteyString);
        rest6.place = in.place;
        rest6.val = in.val;
    }
    return rest6;
}
Attr UNARY()
{
    Attr unary, factor;
    int height = idd++;
    string name = "unary";
    addOut(name, "factor");
    factor = FACTOR();
    unary.place = factor.place;
    unary.val = factor.val;
    return unary;
}
Attr FACTOR()
{
    Attr factor;
    int height = idd++;
    string name = "factor";
    if (check(charLSB))
    {
        pos++;
        addOut(name, "( expr )");
        Attr expr = EXPR();
        checkAndErr(charRSB, name, height);
        factor.place = expr.place;
        factor.val = expr.val;
    }
    else if (check(IntegerValue))
    {
        addOut(name, "num");
        factor.place = laout[pos].token;
        factor.val = atoi(laout[pos].token.c_str());
        pos++;
    }
    else
    {
        addOut(name, "loc");
        Attr loc = LOC();
        factor.val = loc.val;
        factor.place = loc.place;
    }
    return factor;
}
