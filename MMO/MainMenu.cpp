//
//  MainMenu.cpp
//  MMO
//
//  Created by Cole Faust on 1/24/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "MainMenu.h"
#include "ColeTexture.h"
#include "ColeFontManager.h"
#include "ColeTextBox.h"
#include <iostream>

MainMenu::MainMenu()
{
    ColeTexture* title = ColeFontManager::getInstance()->createTextTexture("Cole's MMO Game!");
    title->x = (640/3/2)-(title->getWidth()/2);
    std::cout << title->x << std::endl;
    addChild(title);
    ColeTextBox *test = new ColeTextBox(100);
    test->x = 10;
    test->y = 20;
    addChild(test);
}

//void MainMenu::render()
//{
    
//}