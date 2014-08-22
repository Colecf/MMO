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
#include "BulletClient.h"
#include "MathHelper.h"
#include <vector>

GameScene::GameScene(std::string name, std::shared_ptr<Player> thePlayer)
{
    p = thePlayer;
    p->name = name;
    p->gameClass = rand()%10;
    scx = RenderManager::getInstance()->getScaledScreenX()/2-8;
    scy = RenderManager::getInstance()->getScaledScreenY()/2-8;
    p->sendNetworkMessage("join§"+name+"§"+intToStr(p->gameClass)+";");
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

void GameScene::onEvent(SDL_Event *e)
{
    ColeScene::onEvent(e);
}

void GameScene::update()
{
    ColeScene::update();
    p->update();
    std::string result = p->clientNetworkUpdate();
    while (result != "")
    {
        if(result == "ERROR") std::cout << "TODO!!!" << std::endl;
        if (result != "")
        {
            result = result.substr(0, result.length()-1); // Remove the ;
            std::string command = result.substr(0, result.find("§"));
            std::vector<std::string> arguments;
            std::string argumentsString = result.substr(result.find("§")+2);
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
            
            if (command == "newbullet" && arguments[0] != p->name)
            {
                std::shared_ptr<BulletClient> b = std::make_shared<BulletClient>();
                //s.broadcast("newbullet§"+p->name+"§"+doubleToStr(b->x)+"§"+doubleToStr(b->y)+"§"+doubleToStr(b->angle)+"§"+doubleToStr(b->speed)+"§"+doubleToStr(b->ttl)+"§"+doubleToStr(b->bulletType)+";");
                b->owner = arguments[0];
                b->setPos(strToDouble(arguments[1]), strToDouble(arguments[2]));
                b->angle = strToDouble(arguments[3]);
                b->speed = strToDouble(arguments[4]);
                b->ttl = strToDouble(arguments[5]);
                b->bulletType = strToInt(arguments[6]);
                b->tag = 1;
                w->addChild(b);
            }
        }
        
        
        
        result = p->clientNetworkUpdate();
    }
    
    int futurex = 0, futurey = 0;
    const Uint8 *state = SDL_GetKeyboardState( NULL );
    if (state[SDL_SCANCODE_W]) futurey--;
    if (state[SDL_SCANCODE_S]) futurey++;
    if (state[SDL_SCANCODE_A]) futurex--;
    if (state[SDL_SCANCODE_D]) futurex++;
    if (futurex != 0 || futurey != 0)
        p->move(futurex, futurey);
    
    int mousex, mousey;
    Uint32 mouseState = SDL_GetMouseState(&mousex, &mousey);
    
    if (mouseState&SDL_BUTTON(1))
    {
        int altMouseX = mousex+p->x-(RenderManager::getInstance()->getScreenX()/2);
        int altMouseY = mousey+p->y-(RenderManager::getInstance()->getScreenY()/2);
        if (p->shootTowards(altMouseX, altMouseY))
        {
            std::shared_ptr<BulletClient> b = std::make_shared<BulletClient>();
            b->setPos(p->x, p->y);
            b->speed = 5;
            b->ttl = 100;
            b->angle = angleBetween(p->x, p->y, altMouseX, altMouseY);
            b->owner = p->name;
            b->tag = 1;
            w->addChild(b);
        }
    }
}

void GameScene::render()
{
    w->x = -p->x + scx;
    w->y = -p->y + scy;
    ColeScene::render();
    ColeTileset::loadedSet->renderTile(scx, scy, 190+p->gameClass);
}