#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<ctime>
#include<iostream>
#include"ITradingStrategy.hpp"
#include"Structures.hpp"

class Server{
    private:
        int server_money;
        std::unordered_map<std::string,user_info> users_database;
        std::unordered_map<std::string,asset_info> assets_database;
    public:
        void registerUser(std::string username, std::string password);
        void deleteUser(std::string username);
        std::vector<std::string> loginUser(std::string username, std::string password);
        void logoutUser(std::string username);
        void cashDeposit(std::string username,int amount);
        asset_info searchAssetByTickerSymbol(std::string ticker_symbol);
        void buyStock(std::string username, std::string ticker_symbol, int amount);
        void sellStock(std::string username,std::string ticker_symbol,int amount);
        void buyCrypto(std::string username,std::string ticker_symbol,int amount);
        void sellCrypto(std::string username,std::string ticker_symbol,int amount);
        void addAssetToWatchListUser(std::string username,std::string ticker_symbol);
};