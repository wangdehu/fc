#include <bits/stdc++.h>
using namespace std;
#define inFile  "./example.in"
#define outFile "./example.out"
static map<string, int> reserveWord, opOrDel;

bool IsDigit(char digit)
{
    if (digit >= '0'&&digit <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool IsLetter(char letter)
{
    if (letter >= 'a'&&letter <= 'z' || letter >= 'A'&&letter <= 'Z'|| letter=='_')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void init()
{
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
}
string readFileIntoString(char *filename)
{
    ifstream ifile(filename);
    //将文件读入到ostringstream对象buf中
    ostringstream buf;
    char ch;
    while (buf && ifile.get(ch))
        buf.put(ch);
    //返回与流对象buf关联的字符串
    return buf.str();
}
void removeComment()
{
}
int main()
{
    init();
    addConst();

    string ss=readFileIntoString(inFile);
    removeComment();


}

