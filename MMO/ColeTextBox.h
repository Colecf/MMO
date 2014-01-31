//
//  ColeTextBox.h
//  MMO
//
//  Created by Cole Faust on 1/30/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__ColeTextBox__
#define __MMO__ColeTextBox__

#include <iostream>
#include <SDL2/SDL.h>
#include "ColeScene.h"

class ColeTextBox : public ColeScene
{
public:
    ColeTextBox(int width);
    std::string containedText;
private:
};

#endif /* defined(__MMO__ColeTextBox__) */
