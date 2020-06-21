#include <iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

//#define L 22475
//#define R 22477
//#define U 22472
//#define D 22480
#define GO 27 //GO means gameover
//#define PAUSE 13// the ENTER button pauses the game
bool gameOver,pause;
const int width = 30;//width of field
const int height = 30;//height of field
int x, y, fruitX, fruitY, score,fruitXPos,fruitYPos;//x and y are vars for position of snake
int tailX[100], tailY[100];//array of x and y coordinates for snake tail
int nTail;//int used to track tail length
enum eDirection {STOP = 0, LEFT, RIGHT,UP,DOWN};//this tracks the direction of the snake
eDirection dir;
void Setup()
{
    gameOver = false;
    //pause = false;
    dir = STOP;//this stops the snake from moving
    x = width/2;//initial position of snake
    y = height/2;//initial position of snake
    fruitX = rand()%width+1;//position of fruit which will be anywhere from 0 to width length
    fruitY = rand()%height+1;
    score = 0;
}
void Draw()
{
    system("cls");//this clears the console

    for(int i = 0;i < width; i++)//this creates the top wall
        cout<<'#';
        cout<<endl;
    //this for loop goes line by line from top to bottom adding a "brick" to the wall
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
        {
            if(j == 0 || j == width -1)
                cout<<'#';
            else if (i == y && j == x)
                cout<<"0";
            else if (i == fruitY && j == fruitX)
                cout<<"F";
            else{
                bool print = false;
                for (int k = 0; k < nTail; k++){
                    if (tailX[k] == j && tailY[k] == i){
                        cout<<"o";
                        print = true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
        }
        cout<<endl;
    }


    for(int i = 0;i < width; i++)//this creates the bottom wall
        cout<<'#';
        cout<<endl;
    cout<<"Score:"<<score<<endl;
    cout<<"nTail:"<<nTail<<endl;
    cout<<"fruitXPos:"<<fruitX<<endl;
    cout<<"fruitYPos:"<<fruitY<<endl;
}
void Input()
{
    if(_kbhit())//this function returns a boolean if a button on the keyboard is pressed and returns zero if not
        {
           switch(_getch()){//getch returns the ascii value of the keyboard character that was pressed
           case 75:
            dir = LEFT;
            break;

           case 77:
            dir = RIGHT;
            break;

           case 72:
            dir = UP;
            break;

           case 80:
            dir = DOWN;
            break;

           case 32:
            dir = STOP;
            break;
           case 27:
            gameOver = true;
            break;

           //case 13:
            //pause = true;
            //break;
           }

        /*if (GetAsyncKeyState(0x50)==true && pause==false) {
            pause=true;
            Sleep(700);

            while (!GetAsyncKeyState(0x50))
                Sleep(1);

            pause=true;
            }*/
        }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir){
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case STOP:
        break;
    default:
        break;
    }
        if(x > width || x <0 ||y > height || y < 0)
            gameOver = true;
        for (int i = 0; i < nTail; i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;
        //if (keyboard::isKeyPressed(Keyboard::Return))
           //pause = true;
        if (x == fruitX && y == fruitY){
            score++;
            fruitX = rand()% width+1;
            fruitY = rand()% height+1;
            if (fruitX == width || fruitY == height){
                fruitX = fruitX-2;
                fruitY = fruitY-2;
            }
            nTail++;
        }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }
    return 0;
}
