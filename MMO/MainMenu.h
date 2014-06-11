//
//  MainMenu.h
//  MMO
//
//  Created by Cole Faust on 1/24/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__MainMenu__
#define __MMO__MainMenu__

#include "ColeScene.h"
#include "ColeTextBox.h"
#include <iostream>

class MainMenu : public ColeScene
{
public:
    MainMenu();
    //void render();
    virtual void onEvent(SDL_Event *e);
private:
    std::shared_ptr<ColeTextBox> serverIPBox;
    std::shared_ptr<ColeTextBox> nameBox;
};

#endif /* defined(__MMO__MainMenu__) */
