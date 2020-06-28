#include "Pokemon.h"
#define ANCHO 70
#define ALTO 20
#define INTRO "Pictures/Art.txt"
#define GAMEOVER "Pictures/Game_Over.txt"
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
#include <iomanip>
#include <locale>
#include <sstream>
#include <string> 
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <cstring>
#include <fstream> 
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int kbhit(void){
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
	ungetc(ch, stdin);
	return 1;
  }

  return 0;
}
char getch(){
	char c;
	system("stty raw");
	c= getchar();
	system("stty sane");
	//printf("%c",c);
	return(c);
}
void clrscr(){
	system("clear");
	return;
}
void mySleep(int sleepMs){
	usleep(sleepMs * 1000);   
}
class Coord{
	private:
		char ID;
		int x,y;
	public:
		Coord(int a,int b):	x(a),y(b){}
		Coord(int a,int b,char x):	x(a),y(b),ID(x){}
		void addX(int a){
			x+=a;
			if(x==ANCHO) x=2;
			else if(x==1) x=ANCHO-1;
			}
		void addY(int a){
			y+=a;
			if(y==ALTO) y=2;
			else if(y==1) y=ALTO-1;
			}
		int showX(){return x;}
		int showY(){return y;}
		char showID(){return ID;}
		void giveX(int a){x=a;}
		void giveY(int a){y=a;}
		void giveID(char a){ID=a;}
				
};
class Pokesnake{
	private:
		vector <Coord*> Object;
		vector <Coord*> snake;
		int HP,potion,score,pantallaX,pantallaY,GameOver,OLDposition;
		string name,type;
	public:
		
		string getHP(){
			return SSTR(HP);
		}
		string getpotion(){
			return SSTR(potion);
		}
		string getscore(){
			return SSTR(score);
		}
		
		void gotoxy(int x,int y){
			printf("%c[%d;%df",0x1B,y,x);
		}
		void printXY(int x,int y,char a){
			gotoxy(x,y);
			cout<<a;
			gotoxy(1,1);
		}
		void printXY(int x,int y,string a){
			gotoxy(x,y);
			cout<<a;
			gotoxy(1,1);
		}
		Pokesnake():name("Snake"),type("Poison"),HP(100),potion(0),score(-20),pantallaX(ANCHO),pantallaY(ALTO),OLDposition(6){
			system("canberra-gtk-play -f musica/Musica.wav &");			
			snake.push_back(new Coord(5,4));
			grow();
			grow();
			Object.push_back(new Coord(rand()%pantallaX+1,rand()%pantallaY+1,'*'));
			startGame();
		}
		void welcomeArt(void){
			clrscr();			
			string line;
			ifstream myfile (INTRO);
			if (myfile.is_open()){
				while(getline(myfile,line)) cout<<line<<'\n';		    
				myfile.close();
			}
			while(!kbhit()){}
		 }

		void CaptureKey(){
			if (getch() == '\033') { 
				getch(); 
				switch(getch()) {
			        case 'A':
			            if(OLDposition!=2) OLDposition=8;
			            break;
			        case 'B':
			            if(OLDposition!=8) OLDposition=2;
			            break;
			        case 'C':
			            if(OLDposition!=4) OLDposition=6;
			            break;
			        case 'D':
			            if(OLDposition!=6) OLDposition=4;
			            break;
				}
			}		
		}
		void startGame(){
			welcomeArt();
			GameOver=0;
			while(!GameOver){
				mySleep(50);
				move();
				Interface();
				if(CheckHit()) GameOver++; 
				if(Eating()){
					int a=0;
					switch(Object[0]->showID()){
						case 'M':/* va a la batalla normal;*/break;
						case 'B':/* va a la batalla con boss;*/break;
						default:potion++;break;
					}
					if(a==1) GameOver++;
					grow();
				}
				if(kbhit()) CaptureKey();						
			}
			GameOverScr();
			getch();
			Score();
			if(PlayAgain()=='y'){
				HP=100;
				potion=0;
				score=-20;
				GameOver=0;
				OLDposition=6;
				int i=snake.size();
				snake.push_back(new Coord(5,4));
				grow();
				grow();
				while(i>0){
					i--;
					snake.erase(snake.begin());
				}
				startGame();
			}
		}
		void move(){
			
			for(int i=snake.size()-1;i>0;i--){
				snake[i]->giveX(snake[i-1]->showX());
				snake[i]->giveY(snake[i-1]->showY());
			}
			switch(OLDposition){
					case 6:
						snake[0]->addX(1);
						break;
					case 4:
						snake[0]->addX(-1);
						break;
					case 8:
						snake[0]->addY(-1);
						break;
					case 2:
						snake[0]->addY(1);
						break;
				}
		}
		int CheckHit(){
			for(int i=1;i<snake.size();i++){
				if(snake[0]->showX()==snake[i]->showX()&&snake[0]->showY()==snake[i]->showY()) {
					return 1;
				}
			}
			return 0;
		}
		int Eating(){
			if(snake[0]->showX()==Object[0]->showX() && snake[0]->showY()==Object[0]->showY()) return 1;
		}
		void grow(){
			snake.push_back(new Coord(1,1));
			
			switch(rand()%3){
				case 0: Object.push_back(new Coord(rand()%(pantallaX-2)+2,rand()%(pantallaY-2)+2,'*')); break;
				case 1: Object.push_back(new Coord(rand()%(pantallaX-2)+2,rand()%(pantallaY-2)+2,'M')); break;
				case 2: Object.push_back(new Coord(rand()%(pantallaX-2)+2,rand()%(pantallaY-2)+2,'B')); break;
			}
			Object.erase(Object.begin());
			score+=10;			
		}
		void Interface(){
			clrscr();
			for(int i=1;i<=pantallaX;i++) printXY(i,1,'.');
			for(int i=2;i<=pantallaY;i++) {
				printXY(1,i,'.'); printXY(pantallaX,i,'.');
			}
			for(int i=2;i<pantallaX;i++) printXY(i,pantallaY,'.');
			
			printXY(1,pantallaY+2,"HP:"+getHP());
			printXY(pantallaX/2,pantallaY+2,"Potions:"+getpotion());
			printXY(pantallaX-11,pantallaY+2,"Score:"+getscore());
			
			
			
			printXY(snake[0]->showX(),snake[0]->showY(),'X');
			for(int i=1;i<snake.size();i++) printXY(snake[i]->showX(),snake[i]->showY(),'o');
			printXY(Object[0]->showX(),Object[0]->showY(),Object[0]->showID());			
			
			
		}
		void GameOverScr(){
			string line;
			ifstream myfile ("Pictures/Game_Over.txt");
			for(int i=0;getline (myfile,line);i++)  {
				gotoxy((pantallaX-34)/2,6+i);
				cout << line << '\n';
			}
			myfile.close();		
			mySleep(50);				
		}
		void Score(){
			printXY(pantallaX/2,3,"Puntos: "+getscore());
		}
		char PlayAgain(){
			cout<<"quieres jugar otra vez?(y/n)";
			char a;
			cin>>a;
			return tolower(a);
		}
};
