#include<string>
class Player{
        std::string name;
        char symbol;
    public:
        Player(std::string name,char symbol);
        std::string getName();
        char getSymbol();
};
Player::Player(std::string name,char symbol){
    this->name=name;
    this->symbol=symbol;
}
std::string Player::getName(){
    return this->name;
}
char Player::getSymbol(){
    return this->symbol;
}
