#pragma once
#include"Server.hpp"

class User{
    private:
        Server *p_server;
        std::string session_username="";
    public:
        void registerToServer(std::string username,std::string password);
        void deleteFromServer();
        void login(std::string username, std::string password);
        void logout();
        void cashDeposit(int amount);
        void searchAssetByTickerSymbol(std::string ticker_symbol);
};