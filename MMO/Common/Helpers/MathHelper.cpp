//
//  MathHelper.cpp
//  MMO
//
//  Created by Cole Faust on 6/14/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "MathHelper.h"
#include <math.h>
#include <iostream>

double angleBetween(int x1, int y1, int x2, int y2)
{
    int x = x1-x2;
    int y = y1-y2;
    
    if (x==0)
    {
        if (y>0)
        {
            return -M_PI/2;
        } else {
            return M_PI/2;
        }
    }
    
    double toRet = atan((double)y/(double)x);
    
    if (x>0)
    {
        toRet += M_PI;
    }
    
    return toRet;
}