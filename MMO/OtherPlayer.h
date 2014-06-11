//
//  OtherPlayer.h
//  MMO
//
//  Created by Cole Faust on 6/9/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__OtherPlayer__
#define __MMO__OtherPlayer__

#include "ColeTileset.h"
#include "ColeScene.h"
#include <memory>
#include "ColeTexture.h"

class OtherPlayer : public ColeScene
{
public:
    OtherPlayer(std::string theName, int theGameClass);
    void render();
    std::string getName();
    int getClass();
private:
    int gameClass;
    std::string name;
    std::shared_ptr<ColeTexture> nameTexture;
};

#endif /* defined(__MMO__OtherPlayer__) */
