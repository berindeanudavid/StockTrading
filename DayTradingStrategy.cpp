#include "DayTradingStrategy.hpp"

void DayTradingStrategy::buy(std::string username, std::string ticker_symbol, int amount, std::unordered_map<std::string, user_info> *p_users_database, std::unordered_map<std::string, asset_info> *p_assets_database, int *p_server_money){
    if(p_assets_database->at(ticker_symbol).amount_available<amount){
        throw NotEnoughAssetUnits("Your selected stocks amount exceeds the available amount!");
    }
    if(p_users_database->at(username).wallet<amount*p_assets_database->at(ticker_symbol).price_of_asset){
        throw NotEnoughMoney("You are too poor for this!");
    }
    p_assets_database->at(ticker_symbol).amount_available-=amount;
    p_users_database->at(username).wallet-=amount*p_assets_database->at(ticker_symbol).price_of_asset;
    p_server_money+=amount*p_assets_database->at(ticker_symbol).price_of_asset;
    if (p_users_database->at(username).owned_assets.find(ticker_symbol)==p_users_database->at(username).owned_assets.end()){
        p_users_database->at(username).owned_assets[ticker_symbol]=0;
    }
    p_users_database->at(username).owned_assets[ticker_symbol]+=amount;
}

void DayTradingStrategy::sell(std::string username, std::string ticker_symbol, int amount, std::unordered_map<std::string,user_info> *p_users_database, std::unordered_map<std::string,asset_info> *p_assets_database, int *p_server_money){

}