//
//  NetworkManager.h
//  MMO
//
//  Created by Cole Faust on 2/11/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__NetworkManager__
#define __MMO__NetworkManager__

#include <iostream>
#include <string>
#include <SDL2_net/SDL_net.h>
#include "Player.h"
#include "GameScene.h"

class NetworkManager
{
public:
    friend class GameScene;
    std::string connect(std::string server);
    void setPlayer(std::shared_ptr<Player> newP);
    bool update();
    static NetworkManager* getInstance()
    {
        static NetworkManager* instance;
        if(instance == NULL)
            instance = new NetworkManager();
        return instance;
    }
private:
    std::shared_ptr<Player> p;
    IPaddress serverIP;
    NetworkManager() {};
    NetworkManager(NetworkManager const&);  // Don't Implement
    void operator=(NetworkManager const&); // Don't implement
};

#endif /* defined(__MMO__NetworkManager__) */
