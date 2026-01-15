#include "User.hpp"

void User::registerToServer(std::string username,std::string password){
    try{
        p_server->registerUser(username,password);
    }
    catch(const UserAlreadyRegistered& e){}
    catch(const std::exception& e){}
}

void User::deleteFromServer(){
    if(this->session_username==""){
        std::cout<<"You are not logged in!";
        return;
    }
    this->p_server->deleteUser(this->session_username);
}

void User::login(std::string username, std::string password){
    try{
        std::vector<std::string> messages=this->p_server->loginUser(username, password);
        for(std::string m : messages){
            std::cout<<m<<"\n";
        }
        this->session_username=username;
    }
    catch(const PasswordIncorrect& e){}
    catch(const std::exception& e){}
}

void User::logout(){
    if(this->session_username==""){
        std::cout<<"You are not logged in!";
        return;
    }
    this->p_server->logoutUser(this->session_username);
    this->session_username="";
}

void User::cashDeposit(int amount){
    if(this->session_username==""){
        std::cout<<"You are not logged in!";
        return;
    }
    this->p_server->cashDeposit(this->session_username, amount);
}

void User::searchAssetByTickerSymbol(std::string ticker_symbol){
    if(this->session_username==""){
        std::cout<<"You are not logged in!";
        return;
    }
    try{
        asset_info information=this->p_server->searchAssetByTickerSymbol(ticker_symbol);
        std::cout<<"full name: "<<information.full_name<<"\n";
        std::cout<<"units available: "<<information.amount_available<<"\n";
        if(information.isStock){
            std::cout<<"type: Stock";
        }
        else{
            std::cout<<"type: Cryptocurrency";
        }
        std::cout<<"price per unit:"<<information.price_of_asset<<"\n";
    }
    catch(const AssetDoesNotExist& e){}
    catch(const std::exception& e){}
}

void User::readMessages(){
    if(this->session_username==""){
        std::cout<<"You are not logged in!";
        return;
    }
    std::vector<std::string> messages=this->p_server->readMessages(this->session_username);
    for(std::string m:messages){
        std::cout<<m<<"\n";
    }
}