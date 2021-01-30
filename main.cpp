/** PROJECT 2048(Game 2048)
 *
 ** Prepared By()
 ** Jamshid Ali  &&  Humam Ahmad
 *
 **/
#include <iostream>
#include <ctime>        //to help to generate random position and random number;
#include <stdlib.h>     //for system function
#include <conio.h>      //used for getch() function
#include <iomanip>      //used for setway function ( setw() )
using namespace std;
int board[4][4];
int dirLine[]={1,0,-1,0};   //Direction of rows from 0---3,down,right,up,left
int dirColumn[]={0,1,0,-1}; //Direction of columns

void generateRandomPosition(int &line, int &column)
{
    int ocupied=1;
    while (ocupied)
    {
        line = rand()%4;                        // to generate random row or line
        column = rand()%4;                      // to generate random column
        if (board[line][column]==0)             //Condition for unoccupied position
            ocupied=0;
    }
}
int randomNumber()
{
    int number=rand()%100+1;                    //to generate random number b/w 1 t0 100
    if(number >=75 && number <=100)            //Condition for checking Probability
        return 4;
    else
        return 2;
}
void addpiece ()
{
    int line,column;
    generateRandomPosition(line,column);         //function to find the unoccupied position
    board[line][column]=randomNumber();         //place a random number 2 or 4 on unoccupied position
}
void newGame()
{
    system("cls");
    for(int i=0;i<4;i++)
        for(int j= 0;j<4;j++)
        board[i][j]=0;
    addpiece();
}
void winGame()
{
    for(int i=0 ; i<4 ; ++i)
        for(int j=0 ; j<4 ; ++j)
    if(board[i][j]==2048){
    cout<<"<------ Congratulation...! ------>"<<"\n"<<endl;
    cout<<"  <========  YOU WIN  ========>"<<"\n"<<endl;
    cout<<"f. Keep Playing\n\nn. New Game\n"<<endl;
    int ch=getch();
    if(ch=='n' || ch=='N')
        newGame();
    }
}
int loseGame()
{
    cout<<"<------ GAME OVER ------>"<<"\n"<<endl;
    cout<<"<========YOU LOSE=======>"<<"\n"<<endl;
    cout<<"t. Try again\n"<<endl;
    int ch=getch();
    if(ch=='t' || ch=='T')
        newGame();
    return 0;
}
void printUI()                    //function to print user inter face
{
    system("cls");
    for( int y = 0; y < 4; y++ )
	{
	    cout << "+------+------+------+------+" << endl << "| ";
	    for( int x = 0; x < 4; x++ )
	    {
		if(board[y][x]==0 ) cout << setw( 4 ) << " ";
		else cout << setw( 4 ) << board[y][x];
		cout << " | ";
	    }
	    cout << endl;
	}
	cout << "+------+------+------+------+" << endl << endl;
    winGame();                      //to check the board for 2048
    cout<<"\n n : New Game \n q : Quit \n w : UP \n s : Down \n a : Left \n d : Right \n";

}
bool canDoMove(int line , int column , int nextLine, int nextColumn) //function for movement if the condition are true then it will return false vice versa
{
    if(nextLine<0 || nextColumn<0 || nextLine>=4 || nextColumn >=4  || (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn]!=0))
        return false;
    else
        return true;
}

void applyMove (int direction)     //main function for movement
{
    int startLine=0, startColumn=0, lineStep=1,columnStep=1;  // down to up or from right to left
    if (direction==0)
    {
        startLine=3;
        lineStep=-1;    //going from up to down
    }
    if(direction==1)
    {
        startColumn=3;
        columnStep=-1;  //going from left to right
    }
    int MovePossible,canAddpiece=0;
    do                            //do while is used for jump to the last empty position in the board in the same row or column
    {
        MovePossible=0;
        for (int i=startLine;i>=0 && i<4;i+=lineStep)
          for(int j=startColumn;j>=0 && j<4;j+=columnStep)
          {
              int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
              if ((board[i][j] && canDoMove(i,j,nextI,nextJ))) //if and if only piece can move or board[i][j]!=0
              {
                  board[nextI][nextJ]+=board[i][j];
                  board[i][j]=0;
                  MovePossible=canAddpiece=1;
              }
          }
    }
    while(MovePossible);
      if(canAddpiece)    //condition for adding piece
        addpiece();
}
int main()
{
    srand(time(0));
    char commandToDir[122];   //a=97 and z=122
    commandToDir['s']=0;  //down
    commandToDir['d']=1;  //right
    commandToDir['w']=2;  //up
    commandToDir['a']=3;  //left
    newGame();
    while(true)
    {
        printUI();           //print user interface
        char command;
        command=getch();    //game command entry
        if(command=='n')
            newGame();
        else if(command=='q')
            break;
        else if(command=='w' || command=='a' || command =='s' || command=='d')
        {
            int currentDirection = commandToDir[command];
            applyMove(currentDirection);
        }
    }
    return 0;
}
