#include<iostream>
#include<iomanip>
#include"Player.h"
class Board{
    private:
        char **table;
        int size;
        void initialize();
    public:
        Board(int size);
        void displayTable();
        void update(int &pos,Player &player);
        bool win(int row,int col);

};
Board::Board(int size){
    this->size=size;
    table=new char*[size];
    for(int i=0;i<size;i++){
        table[i]=new char[size];
    }
    initialize();
}
void Board::initialize(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            table[i][j]='\0';
        }
    }
}
void Board::displayTable(){
    std::cout<<std::endl<<"The board is : "<<std::endl;
    for(int i=0;i<size;i++){
        std::cout<<"||\t";
        for(int j=0;j<size;j++){
            if(table[i][j]=='\0')
                std::cout<<std::setw(3)<<i*size+j+1;
            else
                std::cout<<std::setw(3)<<table[i][j];
            std::cout<<std::setw(2)<<"||";
        }
        std::cout<<std::endl;
    }
}
void Board::update(int &pos,Player &player){
    int row=(pos-1)/size;
    int col=(pos-1)%size;
    while(pos<=0||pos>size*size||table[row][col]=='X'||table[row][col]=='O'){
        std::cout<<"You Entered Invalid Loaction. Please Re-enter the Location."<<std::endl;
        std::cout<<"Enter Loation(Between 1-9) for "<<player.getName()<<"("<<player.getSymbol()<<"): ";
        std::cin>>pos;
        row=(pos-1)/size;
        col=(pos-1)%size;
    }
    table[row][col]=player.getSymbol();
    std::cout<<"Data inserted sucessfully..."<<std::endl;
}
bool Board::win(int row,int col){
    bool result1=true;
    bool result2=true;
    bool result3=true;
    bool result4=true;
    for(int i=1;i<size;i++){
        if(table[row][0]!=table[row][i])
            result1=false;
        if(table[0][col]!=table[i][col])
            result2=false;
        if(table[0][0]!=table[i][i])
            result3=false;
        if(table[0][size-1]!=table[i][size-1-i])
            result4=false;
    }
    return result1||result2||result3||result4;
}