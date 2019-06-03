#ifndef GA_H
#define GA_H

#include "la.h"


struct G{
    std::string left;
    std::vector<std::string>right;
    G(std::string l):left(l){right.clear();}
};

#endif