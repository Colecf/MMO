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
    w = std::make_shared<World>();
    addChild(w);
}

std::shared_ptr<OtherPlayer> GameScene::getOtherPlayerByName(std::string name)
{
    std::list<std::shared_ptr<OtherPlayer>>::iterator it;
    for (it = otherPlayers.begin(); it != otherPlayers.end(); it++)
    {
        if ((*it)->getName() == name)
        {
            return *it;
        }
    }
    return NULL;
}

void GameScene::update()
{
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
                std::shared_ptr<OtherPlayer> newPlayer = std::make_shared<OtherPlayer>(arguments[0], strToInt(arguments[3]));
                newPlayer->x = strToInt(arguments[1]);
                newPlayer->y = strToInt(arguments[2]);
                otherPlayers.push_back(newPlayer);
                w->addChild(newPlayer);
            }
            if (command == "move" && getOtherPlayerByName(arguments[0]) != NULL)
            {
                std::shared_ptr<OtherPlayer> thePlayer = getOtherPlayerByName(arguments[0]);
                thePlayer->x = strToInt(arguments[1]);
                thePlayer->y = strToInt(arguments[2]);
            }
            
            if (command == "leave" && getOtherPlayerByName(arguments[0]) != NULL)
            {
                std::shared_ptr<OtherPlayer> thePlayer = getOtherPlayerByName(arguments[0]);
                otherPlayers.remove(thePlayer);
                w->removeChild(thePlayer);
            }
            
            if (command == "world")
            {
                int worldSize = strToInt(arguments[0]);
                int tilex = 0;
                int tiley = 0;
                for (int i=1; i<arguments.size(); i++) {
                    w->setTile(tilex, tiley, strToInt(arguments[i]));
                    tiley++;
                    if (tiley == worldSize)
                    {
                        tiley = 0;
                        tilex++;
                    }
                }
            }
        }
        
        result = p->clientNetworkUpdate();
    }
    
    int futurex = 0, futurey = 0;
    const Uint8 *state = SDL_GetKeyboardState( NULL );
    if (state[SDL_SCANCODE_UP]) futurey--;
    if (state[SDL_SCANCODE_DOWN]) futurey++;
    if (state[SDL_SCANCODE_LEFT]) futurex--;
    if (state[SDL_SCANCODE_RIGHT]) futurex++;
    p->move(futurex, futurey);
}

void GameScene::render()
{
    w->x = -p->x + scx;
    w->y = -p->y + scy;
    ColeScene::render();
    ColeTileset::loadedSet->renderTile(scx, scy, 195);
}