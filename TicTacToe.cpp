#include"Board.h"
void startGame(){
    int size;
    std::cout<<"Enter the size of Tic-Tac-Toe Board : ";
    std::cin>>size;
    Board board(size);
    std::string name;
    std::cout<<"Enter Player-1 Name(X): ";
    std::cin.ignore();
    getline(std::cin,name);
    Player player1(name,'X');
    std::cout<<"Enter Player-2 Name(O): ";
    std::cin.ignore();
    getline(std::cin,name);
    Player player2(name,'O');
    Player current_player=player1;
    std::cout<<std::endl<<"Lets begin the game..."<<std::endl;
    int filled=0;
    board.displayTable();
    while(filled<size*size){
        int pos;
        std::cout<<std::endl<<"Enter Loation(Between 1-9) for "<<current_player.getName()<<"("<<current_player.getSymbol()<<"): ";
        std::cin>>pos;
        board.update(pos,current_player);
        board.displayTable();
        filled++;
        pos--;
        if(board.win(pos/size,pos%size)){
            std::cout<<"Congratulation "<<current_player.getName()<<"...You won the game...";
        }
        if(current_player.getSymbol()==player1.getSymbol())
            current_player=player2;
        else
            current_player=player1;
    }
    std::cout<<std::endl<<"OOPs....This Game is Ended...";
}
int main(){
    std::cout<<"Welcome To TicTacToe Game"<<std::endl<<std::endl;
    startGame();
    return 0;
}