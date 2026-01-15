#include"ITradingStrategy.hpp"

class DayTradingStrategy : public ITradingStrategy{
    public:
        void buy(std::string username, std::string ticker_symbol, int amount, std::unordered_map<std::string, user_info> *p_users_database, std::unordered_map<std::string, asset_info> *p_assets_database, int *p_server_money);
        void sell(std::string username, std::string ticker_symbol, int amount, std::unordered_map<std::string,user_info> *p_users_database, std::unordered_map<std::string,asset_info> *p_assets_database, int *p_server_money);
};