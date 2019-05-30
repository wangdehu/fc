#include "ga.h"
#include <iostream>
#include <fstream>
using namespace std;
int ruleNum;
vector<G> gs;
map<string, int> id;
vector<LAOUT> laout;
int pos;
vector<string> EndOp = {"+", "-", "*", "/", "ε", "num"};
vector<string> NotEndOp = {"expr", "term", "rest5", "rest6", "factor", "unary"};
map<string, int> keyValue;
vector<int> outKs;
vector<string> outSs;
string empteyString="";
void init_fir()
{
    id.clear();
    fstream in(gaRuleFile, ios::in);
    string s, p;
    int num;

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
    keyValue["+"] = charAdd;
    keyValue["-"] = charSub;
    keyValue["*"] = charMul;
    keyValue["/"] = charDev;
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

void addOut(string &b, int &k, string s,bool flag=false)
{   
    if(flag) s=empteyString;
    outKs.push_back(k);
    outSs.push_back(s);
    cout << b << " -> " << s << endl;
}

void game(string b)
{
    int k = id[b];
    bool flag = false;
    if (gs[k].right.size() == 1)
    {
        addOut(b, k, gs[k].right[0]);
        flag = true;
    }
    for (int i = 0; i < gs[k].right.size(); ++i)
    {

        vector<string> q = splitToVector(gs[k].right[i]);
        if (!findIn(q[0], EndOp))
        {
            for (int j = 0; j < q.size(); ++j)
                game(q[j]);
        }
        else
        {
            if (q[0] == "ε")
            {
                addOut(b,k,gs[k].right[i],true);
                return;
            }
            int s = keyValue[q[0]];
            if (s == laout[pos].key)
            {
                if (!flag)
                {   
                    addOut(b,k,gs[k].right[i]);
                }
                pos++;
                for (int j = 1; j < q.size(); ++j)
                {
                    game(q[j]);
                }
                return;
            }
        }
    }
}

int main()
{
    init_fir();
    init_sec();
    init_tri();

    int k = id[Begin];
    pos = 0;
    game(Begin);

    cout << Begin << "\t=> " << endl;
    string origin = Begin;
    for (int i = 0; i < outKs.size(); ++i)
    {
        string b = gs[outKs[i]].left;
        int p = origin.find(b);
        origin.replace(p, b.size(), outSs[i]);

        cout << origin << endl;
    }
}