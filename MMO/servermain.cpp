//
//  main.cpp
//  MMO_server
//
//  Created by Cole Faust on 12/28/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>
#include "Player.h"
#include "StrToInt.h"
#include <vector>

bool run = true;

bool getRun() { return run; }

void handleMessage(Player* p);

class Server
{
public:
    void cleanup()
    {
        std::list<Player*>::iterator it;
        for (it = clients.begin(); it != clients.end(); it++) {
            delete *it;
            *it = NULL;
        }
        SDLNet_TCP_Close(serverSocket);
    }
    
    bool init()
    {
        IPaddress ip;
        if(SDLNet_ResolveHost(&ip,NULL,9999)==-1) {
            std::cout << "ERROR SDLNet_ResolveHost " << SDLNet_GetError() << std::endl;
            return false;
        }
        
        serverSocket = SDLNet_TCP_Open(&ip);
        if(!serverSocket) {
            std::cout << "ERROR SDLNet_TCP_Open " << SDLNet_GetError() << std::endl;
            return false;
        }
        return true;
    }
    void run()
    {
        while (getRun())
        {
            TCPsocket newClient = SDLNet_TCP_Accept(serverSocket);
            if (newClient)
            {
                Player* p = new Player;
                p->setSocket(newClient);
                clients.push_back(p);
                std::cout << "New Player!" << std::endl;
            }
            while(SDLNet_CheckSockets(Player::PlayerSSet, 0) >= 1)
            {
                std::list<Player*>::iterator it;
                for (it = clients.begin(); it != clients.end(); it++)
                {
                    if (SDLNet_SocketReady((*it)->socket))
                    {
                        char letter;
                        if(SDLNet_TCP_Recv((*it)->socket, &letter, 1) < 1)
                        {
                            std::cout << "Player disconnecting! " << (*it)->name << std::endl;
                            broadcast("leave:"+(*it)->name+";");
                            delete *it;
                            clients.erase(it);
                            continue;
                        }
                        (*it)->networkMessage += letter;
                        if (letter == ';')
                            handleMessage((*it));
                    }
                }
            }
            
            SDL_Delay(50);
        }
    }
    void broadcast(std::string message)
    {
        std::list<Player*>::iterator it;
        for (it = clients.begin(); it != clients.end(); it++) {
            (*it)->sendNetworkMessage(message);
        }
    }
    void informOfCurrentPlayers(Player* p)
    {
        std::list<Player*>::iterator it;
        for (it = clients.begin(); it != clients.end(); ++it) {
            p->sendNetworkMessage("join:"+(*it)->name+"§"+intToStr((*it)->x)+"§"+intToStr((*it)->y)+"§"+intToStr((*it)->gameClass)+";");
        }
    }
private:
    std::list<Player*> clients;
    TCPsocket serverSocket;
};

Server s;

void handleMessage(Player* p)
{
    
    std::cout << p->networkMessage << std::endl;
    p->networkMessage = p->networkMessage.substr(0, p->networkMessage.length()-1); // Remove the ;
    std::string command = p->networkMessage.substr(0, p->networkMessage.find(":"));
    std::vector<std::string> arguments;
    std::string argumentsString = p->networkMessage.substr(p->networkMessage.find(":")+1);
    std::cout << "Command: " << command << std::endl;
    if (p->name == "" && command != "join")
    {
        std::cout << "Unnamed player attempting commands!" << std::endl;
        p->networkMessage = "";
        return;
    }
    while (argumentsString.length()>0)
    {
        arguments.push_back(argumentsString.substr(0, argumentsString.find("§")));
        argumentsString = argumentsString.substr(argumentsString.find("§")+2); //It appears § takes up 2 characters, so the +2
    }
    if(command == "move")
    {
        p->x = strToInt(arguments[0]);
        p->y = strToInt(arguments[1]);
        s.broadcast("move:"+p->name+"§"+intToStr(p->x)+"§"+intToStr(p->y)+";");
    }
    if(command == "join")
    {
        std::cout << "joining..." << std::endl;
        p->name = arguments[0];
        p->gameClass = strToInt(arguments[1]);
        s.informOfCurrentPlayers(p);
        s.broadcast("join:"+arguments[0]+"§0§0§"+arguments[1]+";"); //Join:name§x§y§class
        std::cout << "New player joined named " << p->name << " with class " << p->gameClass << std::endl;
    }
    
    p->networkMessage = "";
}

int keyboardThread(void* data)
{
    std::string line;
    while (run)
    {
        getline(std::cin, line);
        if (line == "q" || line == "quit" || line == "exit")
        {
            run = false;
        }
    }
    return 0;
}



int main(int argc, const char * argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }
    if(SDLNet_Init() == -1)
    {
        std::cout << "ERROR SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return 1;
    }
    
    if(!s.init())
    {
        return 1;
    }
    
    Player::PlayerSSet = SDLNet_AllocSocketSet(100);
    
    SDL_Thread *keythread = SDL_CreateThread(keyboardThread, "keyboardThread", (void *)NULL);
    
    std::cout << "Start" << std::endl;
    s.run();
    
    int ret;
    SDL_WaitThread(keythread, &ret);
    s.cleanup();
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}

