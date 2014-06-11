//
//  GameScene.cpp
//  MMO
//
//  Created by Cole Faust on 3/8/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "GameScene.h"
#include "RenderManager.h"
#include "NetworkManager.h"
#include "ColeTileset.h"
#include "StrToInt.h"
#include <vector>

GameScene::GameScene(std::string name, std::shared_ptr<Player> thePlayer)
{
    p = thePlayer;
    p->name = name;
    p->gameClass = 5;
    scx = RenderManager::getInstance()->getScaledScreenX()/2-8;
    scy = RenderManager::getInstance()->getScaledScreenY()/2-8;
    p->sendNetworkMessage("join:"+name+"§5;");
}

OtherPlayer* GameScene::getOtherPlayerByName(std::string name)
{
    std::list<OtherPlayer*>::iterator it;
    for (it = otherPlayers.begin(); it != otherPlayers.end(); it++)
    {
        if ((*it)->getName() == name)
        {
            return *it;
        }
    }
    return NULL;
}

void GameScene::onEvent(SDL_Event *e)
{
    ColeScene::onEvent(e);
    if (e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
            case SDLK_LEFT:
                p->move(-10, 0);
                break;
            case SDLK_RIGHT:
                p->move(10, 0);
                break;
            case SDLK_UP:
                p->move(0, -10);
                break;
            case SDLK_DOWN:
                p->move(0, 10);
                break;
            default:
                break;
        }
    }
    
}
void GameScene::render()
{
    ColeScene::render();
    ColeTileset::loadedSet->renderTile(scx+p->x, scy+p->y, 195);
    
    std::string result = p->clientNetworkUpdate();
    while (result != "")
    {
        if(result == "ERROR") std::cout << "TODO!!!" << std::endl;
        if (result != "")
        {
            result = result.substr(0, result.length()-1); // Remove the ;
            std::string command = result.substr(0, result.find(":"));
            std::vector<std::string> arguments;
            std::string argumentsString = result.substr(result.find(":")+1);
            while (argumentsString.length()>0)
            {
                arguments.push_back(argumentsString.substr(0, argumentsString.find("§")));
                argumentsString = argumentsString.substr(argumentsString.find("§")+2); //it appears that § takes up 2 characters, so +2
            }
            if (command=="join" && arguments[0] != p->name)
            {
                std::cout << "New player joining" << std::endl;
                OtherPlayer* newPlayer = new OtherPlayer(arguments[0], strToInt(arguments[3]));
                newPlayer->x = strToInt(arguments[1]);
                newPlayer->y = strToInt(arguments[2]);
                otherPlayers.push_back(newPlayer);
            }
            if (command == "move" && getOtherPlayerByName(arguments[0]) != NULL)
            {
                OtherPlayer* thePlayer = getOtherPlayerByName(arguments[0]);
                thePlayer->x = strToInt(arguments[1]);
                thePlayer->y = strToInt(arguments[2]);
            }
            
            if (command == "leave" && getOtherPlayerByName(arguments[0]) != NULL)
            {
                OtherPlayer* thePlayer = getOtherPlayerByName(arguments[0]);
                otherPlayers.remove(thePlayer);
                delete thePlayer;
            }
        }
        
        result = p->clientNetworkUpdate();
    }
    
    std::list<OtherPlayer*>::iterator it;
    for (it = otherPlayers.begin(); it != otherPlayers.end(); it++)
    {
        (*it)->render();
    }
}