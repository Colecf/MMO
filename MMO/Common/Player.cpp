//
//  Player.cpp
//  MMO
//
//  Created by Cole Faust on 1/12/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "Player.h"
#include "StrToInt.h"
#include "MathHelper.h"
#include <iostream>

void Player::sendNetworkMessage(std::string message)
{
    std::cout << "Sent: " << message << std::endl;
    
    //The enabled one also works, but mingw apparently doesn't have strlen
    //Disabled one was the origional
    //SDLNet_TCP_Send(socket, message.c_str(), (int)strlen(message.c_str()));
    SDLNet_TCP_Send(socket, message.c_str(), (int)message.length());
}

SDLNet_SocketSet Player::PlayerSSet;

Player::Player()
{
    networkMessage = "";
    name = "";
    socket = NULL;
    x = y = 100/2*16;
}

Player::~Player()
{
    if (socket != NULL)
    {
        SDLNet_DelSocket(PlayerSSet, (SDLNet_GenericSocket)socket);
        SDLNet_TCP_Close(socket);
    }
}

void Player::update()
{
    shootCooldown--;
}

std::string Player::connectToServer(std::string server)
{
    IPaddress serverIP;
    
    if(SDLNet_ResolveHost(&serverIP, server.c_str(), 9999)==-1) {
        std::string error = "ERROR SDLNet_ResolveHost ";
        error += SDLNet_GetError();
        std::cout << error << std::endl;
        return error;
    }
    
    setSocket(SDLNet_TCP_Open(&serverIP));
    if(!socket) {
        std::string error = "ERROR SDLNet_TCP_Open ";
        error += SDLNet_GetError();
        std::cout << error << std::endl;
        return error;
    }
    
    return "";
}

std::string Player::clientNetworkUpdate()
{
    if (!socket)
        return "";
    
    while(SDLNet_CheckSockets(Player::PlayerSSet, 0) >= 1)
    {
        if (SDLNet_SocketReady(socket))
        {
            char letter;
            if(SDLNet_TCP_Recv(socket, &letter, 1) < 1)
            {
                std::cout << "Lost Connection to server!" << std::endl;
                return "ERROR";
            }
            networkMessage += letter;
            if (letter == ';')
            {
                std::cout << networkMessage << std::endl;
                std::string toRet = networkMessage;
                networkMessage = "";
                return toRet;
            }
        }
    }
    return "";
}

void Player::setSocket(TCPsocket newSocket)
{
    socket = newSocket;
    SDLNet_AddSocket(PlayerSSet, (SDLNet_GenericSocket)socket);
}

void Player::move(int dx, int dy)
{
    x += dx;
    y += dy;
    
    std::string message = "move§"+intToStr(x)+"§"+intToStr(y)+";";
    
    sendNetworkMessage(message);
}

bool Player::shootTowards(int sx, int sy)
{
    if (shootCooldown > 0) return false;
    
    sendNetworkMessage("shoot§"+doubleToStr(angleBetween(x, y, sx, sy))+"§"+doubleToStr(5)+"§"+doubleToStr(100)+"§"+intToStr(0)+";");
    shootCooldown = SHOOTCOOLDOWNMAX;
    return true;
}