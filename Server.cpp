#include "Server.hpp"

bool isWorkTime(){
    std::time_t now = std::time(nullptr);
    std::tm local{};
    localtime_r(&now, &local); 
    bool weekday_ok = (local.tm_wday >= 1 && local.tm_wday <= 5); 
    bool time_ok = (local.tm_hour >= 9 && local.tm_hour < 18);
    return weekday_ok && time_ok;
}

void Server::registerUser(std::string username, std::string password){
    if((this->users_database.find(username)!=this->users_database.end())||(username=="")){
        throw UserAlreadyRegistered("User is already registered or no username provided!");
    }
    user_info information;
    this->users_database.emplace(username,information);
    this->users_database.at(username).password=password;
    this->users_database.at(username).wallet=0;
    //put default trading strategy
    std::cout<<"Welcome, "+username+"!";
}

void Server::deleteUser(std::string username){
    this->users_database.erase(username);
}

std::vector<std::string> Server::loginUser(std::string username, std::string password){
    if(this->users_database.at(username).password!=password){
        throw PasswordIncorrect("Password is incorrect!");
    }
    this->users_database.at(username).isLoggedIn=1;
    std::vector<std::string> stored_messages=this->users_database.at(username).stored_messages;
    this->users_database.at(username).stored_messages.clear();
    return stored_messages;
}

void Server::logoutUser(std::string username){
    this->users_database.at(username).isLoggedIn=0;
}

void Server::cashDeposit(std::string username,int amount){
    this->users_database.at(username).wallet+=amount;
}

asset_info Server::searchAssetByTickerSymbol(std::string ticker_symbol){
    if(this->assets_database.find(ticker_symbol)==this->assets_database.end()){
        throw AssetDoesNotExist("Asset does not exist in the database!");
    }
    return this->assets_database.at(ticker_symbol);
}

void Server::buyStock(std::string username,std::string ticker_symbol,int amount){
    if(this->assets_database.find(ticker_symbol)==this->assets_database.end()){
        throw AssetDoesNotExist("Asset does not exist in the database!");
    }
    if(this->assets_database.at(ticker_symbol).isStock){
        if(!isWorkTime()){
            throw NonWorkingHours("Request unsuccessful: you are requesting this outside working hours (9AM-18PM Monday to Friday)");
        }
        this->users_database.at(username).account_type->buy(username,ticker_symbol,amount,&this->users_database,&this->assets_database, &this->server_money);
    }
    else{
        throw WrongAssetType("This is a crypto asset!");
    }
}

void sellStock(std::string username,std::string ticker_symbol,int amount);
void buyCrypto(std::string username,std::string ticker_symbol,int amount);
void sellCrypto(std::string username,std::string ticker_symbol,int amount);

void Server::addAssetToWatchListUser(std::string username,std::string ticker_symbol){
    if(this->assets_database.find(ticker_symbol)==this->assets_database.end()){
        throw AssetDoesNotExist("Asset does not exist in the database!");
    }
    this->users_database.at(username).watch_list.insert(ticker_symbol);
}

void Server::updateAssetPrice(std::string ticker_symbol,int price_difference){
    if(isWorkTime()){
        //you can also substract with this formula: by entering negative values:
        assets_database.at(ticker_symbol).price_of_asset+=price_difference;
        std::for_each(this->users_database.begin(),this->users_database.end(),[&](std::pair<std::string,user_info>pair){
            if(pair.second.watch_list.contains(ticker_symbol)){
                pair.second.stored_messages.push_back(ticker_symbol+" changed by: "+std::to_string(price_difference));
            }
        });
    }
    else{
        std::cout<<"You are working overhours. Take a break and come back at (9AM-18PM Monday to Friday).\n";
    }
}

std::vector<std::string> Server::readMessages(std::string username){
    std::vector<std::string> messages=this->users_database.at(username).stored_messages;
    this->users_database.at(username).stored_messages.clear();
    return messages;
}