//
//  StrToInt.cpp
//  MMO
//
//  Created by Cole Faust on 12/28/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#ifndef __MMO__StrToInt__
#define __MMO__StrToInt__

#include <sstream>
#include <string>
#include "StrToInt.h"
#include <iostream>

int strToInt(std::string s)
{
    
    std::stringstream ss;
    ss << s;
    int result;
    ss >> result;
    return result;
}

std::string intToStr(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

#endif