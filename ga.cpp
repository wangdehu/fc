#include "ga.h"
#include <iostream>
#include <fstream>

using namespace std;
int ruleNum;
vector<G> gs;
map<string, int> id;
vector<LAOUT> laout;
int pos;
vector<string> EndOp = {"+", "-", "*", "/", "ε", "num", "<", "<=", ">", ">=", "==", "!=", "(", ")", "=", "[", "]", "if", "else", "while", "id", ";"};
vector<string> NotEndOp = {"stmts", "stmt", "rest0", "loc", "elist", "resta", "rest1", "bool", "equality", "rel", "rest4", "rop_expr", "expr", "term", "rest5", "rest6", "factor", "unary"};
map<string, int> keyValue;
vector<string> outL;
vector<string> outR;
string empteyString = "ε";
string Begin;

void init_fir(string gaRule)
{
    id.clear();
    fstream in(gaRule, ios::in);
    string s, p;
    int num;
    in >> Begin;
    in >> ruleNum;
    for (int i = 0; i < ruleNum; ++i)
    {
        in >> s >> num;
        gs.push_back(G(s));
        id[s] = i;
        in.ignore();
        for (int j = 0; j < num; ++j)
        {
            getline(in, p);
            gs[i].right.push_back(p);
        }
    }
}
void init_sec()
{
    laout.clear();
    pos = 0;
    int type;
    string keyValue;
    int num;
    cin >> num;
    for (int i = 0; i < num; ++i)
    {
        cin >> type >> keyValue;
        laout.push_back(LAOUT(type, keyValue));
    }
}
void init_tri()
{
    keyValue["num"] = IntegerValue;
    keyValue["id"] = VarVaule;
    keyValue["while"] = reserveWhile;
    keyValue["if"] = reserveIf;
    keyValue["else"] = reserveElse;

    keyValue["+"] = charAdd;
    keyValue["-"] = charSub;
    keyValue["*"] = charMul;
    keyValue["/"] = charDev;
    keyValue[","] = charCom;
    keyValue[";"] = charSem;
    keyValue["="] = charEqu;

    keyValue["<"] = charSma;
    keyValue["<="] = tcharSmaEqu;
    keyValue[">"] = charBig;
    keyValue[">="] = tcharBigEqu;
    keyValue["=="] = tcharEquEqu;
    keyValue["!="] = tcharNotEqu;
    keyValue["("] = charLSB;
    keyValue[")"] = charRSB;
    keyValue["["] = charLMB;
    keyValue["]"] = charRMB;
}

vector<string> splitToVector(string s)
{
    vector<string> res;
    string tmp;
    stringstream sp(s);
    while (!sp.eof())
    {
        sp >> tmp;
        res.push_back(tmp);
    }
    return res;
}

bool findIn(string &s, vector<string> &q)
{
    for (int i = 0; i < q.size(); ++i)
    {
        if (q[i] == s)
            return true;
    }
    return false;
}

void addOut(string &b, string &s)
{
    cout << b << " -> " << s << endl;
    outL.push_back(b);

    if (s == empteyString)
    {
        outR.push_back("");
    }
    else
    {
        outR.push_back(s);
    }
}
int iddd = 0;
void game(string b)
{

    int idd = iddd++;
    // cout << idd << "   " << b << endl;

    if (findIn(b, EndOp))
    {
        if (b != "ε")
        {
            int s = keyValue[b];
            // cout<<b<<endl;
            // cout<<"pos   "<<laout[pos].key<<"   "<<laout[pos].token<<endl;
            if (s != laout[pos].key)
            {   
                cout<<"************";
                cout<<b<<endl;
                cout << "error" << endl;
                cout<<"************";
                exit(0);
            }
            pos++;
            if (pos > laout.size())
            {
                cout << "error" << endl;
                exit(0);
            }
        }
        return;
    }

    int k = id[b];
    bool flag = false;
    if (gs[k].right.size() == 1)
    {
        addOut(b, gs[k].right[0]);
        vector<string> q = splitToVector(gs[k].right[0]);
        for (int i = 0; i < q.size(); ++i)
        {
            game(q[i]);
        }
        return;
    }

    int fg = -1;
    int ug = -1;
    for (int i = 0; i < gs[k].right.size(); ++i)
    {
        vector<string> q = splitToVector(gs[k].right[i]);
        if (!findIn(q[0], EndOp))
        {
            fg = i;
            continue;
        }
        if (q[0] == "ε")
        {
            ug = i;
            continue;
        }
        int s = keyValue[q[0]];
        if (s == laout[pos].key)
        {
            addOut(b, gs[k].right[i]);
            for (int j = 0; j < q.size(); ++j)
            {
                game(q[j]);
            }
            return;
        }
    }

    if (ug != -1 && !(pos < laout.size() && b == "rest0"))
    {
        vector<string> q = splitToVector(gs[k].right[ug]);
        addOut(b, empteyString);
        game(q[0]);
    }
    else if (fg != -1)
    {
        vector<string> q = splitToVector(gs[k].right[fg]);
        addOut(b, gs[k].right[fg]);

        for (int j = 0; j < q.size(); ++j)
        {
            game(q[j]);
        }
    }
}

int main(int argc, char *argv[])
{
    init_fir(argv[1]);
    init_sec();
    init_tri();

    int k = id[Begin];
    pos = 0;
    game(Begin);

    cout << endl;
    cout << Begin << "\t=> " << endl;
    string origin = Begin;
    for (int i = 0; i < outL.size(); ++i)
    {
        // if (outR[i] == empteyString)
        // {
        //     outR[i] = "";
        // }
        int p = origin.find(outL[i]);
        origin.replace(p, outL[i].size(), outR[i]);
        cout << origin << endl;
    }

    // cout<<"gs.size() = "<<gs.size()<<endl;
    // for(int i=0;i<gs.size();++i){
    //     cout<<i <<" "<<gs[i].left<<"   "<<gs[i].right.size()<<endl;
    //     for(int j=0;j<gs[i].right.size();++j){
    //         cout<<gs[i].right[j]<<endl;
    //     }
    //     cout<<"***************"<<endl;
    // }
}