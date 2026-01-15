#include<string>
#include<unordered_map>
#include"Structures.hpp"

class ITradingStrategy{
    public:
        virtual void buy(std::string username, std::string ticker_symbol, int amount, std::unordered_map<std::string,user_info> *p_users_database, std::unordered_map<std::string,asset_info> *p_assets_database, int *p_server_money)=0;
        virtual void sell(std::string username, std::string ticker_symbol, int amount, std::unordered_map<std::string,user_info> *p_users_database, std::unordered_map<std::string,asset_info> *p_assets_database, int *p_server_money)=0;
};