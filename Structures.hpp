#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<stdexcept>
#include "ITradingStrategy.hpp"

struct asset_info{
    int price_of_asset;
    int amount_available;
    bool isStock; //false = is crypto
    std::string full_name;
};

struct user_info{
    std::unordered_map<std::string,int> owned_assets;
    std::string password;
    std::vector<std::string> watch_list;
    std::vector<std::string> transaction_history;
    std::vector<std::string> automated_transactions;
    bool isLoggedIn;
    int wallet;
    std::vector<std::string> stored_messages;
    ITradingStrategy *account_type;
};

struct UserAlreadyRegistered : std::logic_error {
    using std::logic_error::logic_error;
};

struct PasswordIncorrect : std::logic_error {
    using std::logic_error::logic_error;
};

struct AssetDoesNotExist : std::logic_error {
    using std::logic_error::logic_error;
};

struct NonWorkingHours : std::logic_error {
    using std::logic_error::logic_error;
};

struct WrongAssetType : std::logic_error {
    using std::logic_error::logic_error;
};

struct NotEnoughAssetUnits : std::logic_error {
    using std::logic_error::logic_error;
};

struct NotEnoughMoney : std::logic_error {
    using std::logic_error::logic_error;
};