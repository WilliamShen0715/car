#include<iostream>
#define LEFT 4
#define STRAIGHT 8
#define RIGHT 6
#define NOMOVE 5
using namespace std;

char checkArea(int x,int y);
int checkStray(char area,int x,int y);
int goCenter(char area,int fromX,int fromY);
int findRoad(int fromX,int fromY,int toX,int toY);
class node{
	public:
	int x,y;
};
node last,check;
bool inCenter=false;
int main(){
	char area;
	int stray,fromX,fromY,toX,toY;
	last.x=0;last.y=0;check.x=0;check.y=0;
	while(1){
		cout<<"from (a,b) to (c,d):"<<endl;
		cin>>fromX>>fromY>>toX>>toY;
		if(fromX!=check.x||fromY!=check.y){
			last.x=check.x;last.y=check.y;
		}
		cout<<"move:"<<findRoad(fromX,fromY,toX,toY)<<endl;
		check.x=fromX;check.y=fromY;
	}
}

char checkArea(int x,int y){
	if(x==0||x==1){
		if(y>4) return 'a';
		else return 'b';
	}else if(x==2){
		if(y<3) return 'b';
		else if(y==6) return 'i';
		else if(y==5||y==7) return 'a';
		else return 'n';
	}else if(x==3){
		if(y<3) return 'b';
		else if(y==6) return 'i';
		else if(y==5||y==7) return 'a';
		else return 'n';
	}else if(x==4){
		if(y>4) return 'h';
		else if(y==0) return 'e';
		else if(y==3) return 'f';
		else if(y==1||y==2) return 'd';
		else return 'n';
	}else if(x==5){
		if(y>5) return 'h';
		else if(y==5) return 'g';
		else if(y==4) return 'n';
		else if(y==3) return 'f';
		else return 'e';
	}else if(x==6){
		if(y>5) return 'h';
		else if(y<3) return 'e';
		else return 'g';
	}else{
		if(y>5) return 'h';
		else if(y==5) return 'g';
		else return 'e';
	}
}
int checkStray(char area,int x,int y){
	if(area=='a'){
		if(x==2) return 0;
		else if(x>0&&y>5) return 2;
		else return 1;
	}else if(area=='b'||area=='c'||area=='d'||area=='f') return 0;
	else if(area=='e'){
		if(x<6&&y<2) return 4;
		else if(x==7&&y>1) return 1;
		else if(x==7&&y<2) return 2;
		else if(x==6&&y<2) return 3;
		else return 0;
	}else if(area=='g'){
		if(x==5) return 0;
		else if(y<5) return 2;
		else return 1;
	}else if(area=='h'){
		if(x!=7&&y==7) return 2;
		else if(x>5) return 1;
		else return 0;
	}else{
		if(y==6) return 1;
		else return 0;
	}
}

int findRoad(int fromX,int fromY,int toX,int toY){
	char from = checkArea(fromX,fromY);
	int fstray = checkStray(from,fromX,fromY);
	char to = checkArea(toX,toY);
	int tstray = checkStray(to,toX,toY);
	if(!inCenter) return goCenter(from,fromX,fromY);
	else if(inCenter&&from!=to){//in center not in same area
		if(last.x==1&&last.y==5) return RIGHT;
		else if(last.x==3&&last.y==5) return LEFT;
		else if(last.x==2&&last.y==3) return LEFT;
		else if(last.x==3&&last.y==1) return RIGHT;
		else if(last.x==4&&last.y==1) return RIGHT;
		else if(last.x==6&&last.y==2) return RIGHT;
		else if(last.x==4&&last.y==2) return LEFT;
		else if(last.x==4&&last.y==3) return LEFT;
		else if(last.x==5&&last.y==4) return LEFT;
		else if(last.x==4&&last.y==6) return RIGHT;
		else if(last.x==3&&last.y==6) return RIGHT;
		else if(last.x==3&&last.y==4) return RIGHT;
		else return STRAIGHT;
	}else if(fromX!=toX||fromY!=toY){ //in same area
		if(from=='a'){
			if(last.x==2&&last.y==5&&tstray==2) return RIGHT;
			else if(last.x==1&&last.y==6) return RIGHT;
			else if(last.x==1&&last.y==5) return RIGHT;
			else return STRAIGHT;
		}else if(from=='b'){
			if(last.x==2&&last.y==2) return RIGHT;
			else if(last.x==2&&last.y==3) return RIGHT;
			else if(last.x==1&&last.y==3) return LEFT;
			else if(last.x==1&&last.y==4) return LEFT;
			else if(last.x==0&&last.y==1) return LEFT;
			else if(last.x==0&&last.y==0) return LEFT;
			else if(last.x==1&&last.y==0) return RIGHT;
			else if(last.x==1&&last.y==1) return RIGHT;
			else return STRAIGHT;
		}else if(from=='c'){
			if(last.x==2&&last.y==2) return RIGHT;
			else return STRAIGHT;
		}else if(from=='d'){
			if(last.x==3&&last.y==2) return RIGHT;
			else return STRAIGHT;
		}else if(from=='e'){
			if(last.x==5&&last.y==1) return RIGHT;
			else if(last.x==4&&last.y==2&&tstray==4) return LEFT;
			else if(last.x==6&&last.y==2&&tstray==1) return LEFT;
			else if(last.x==6&&last.y==2&&tstray==2) return RIGHT;
			else if(last.x==6&&last.y==2&&tstray==3) return RIGHT;
			else if(last.x==7&&last.y==2&&tstray==3) return RIGHT;
			else if(last.x==7&&last.y==1&&tstray==3) return LEFT;
			else return STRAIGHT;
		}else if(from=='f'){
			if(last.x==5&&last.y==2) return LEFT;
			else return STRAIGHT;
		}else if(from=='g'){
			if(last.x==5&&last.y==4) return RIGHT;
			else if(last.x==5&&last.y==5&&tstray==2) return RIGHT;
			else return STRAIGHT;
		}else if(from=='h'){
			if(last.x==5&&last.y==5) return RIGHT;
			else if(last.x==4&&last.y==5) return RIGHT;
			else if(last.x==5&&last.y==6&&tstray==2) return LEFT;
			else if(last.x==6&&last.y==6) return LEFT;
			else return STRAIGHT;
		}else{
			if(last.x==4&&last.y==5&&tstray==1) return RIGHT;
			else if(last.x==5&&last.y==5&&tstray==0) return LEFT;
			else if(last.x==3&&last.y==5) return LEFT;
			else return STRAIGHT;
		}
	}else return NOMOVE;//arrive destination
}

int goCenter(char area,int fromX,int fromY){
	if(area=='a'){
		if(fromX!=2||fromY!=5){
			if(last.x==0&&last.y==6) return LEFT;
			else if(last.x==1&&last.y==6) return LEFT;
			else if(last.x==2&&last.y==7) return LEFT;
			else return STRAIGHT;
		}else{
			inCenter=true;
			return NOMOVE;
		}
	}else if(area=='b'){
		if(fromX!=2||fromY!=2){
			if(fromX==2&&fromY==1) return LEFT;
			else if(last.x==2&&last.y==0) return LEFT;
			else if(last.x==2&&last.y==1) return LEFT;
			else if(last.x==1&&last.y==1) return RIGHT;
			else if(last.x==1&&last.y==0) return RIGHT;
			else if(last.x==0&&last.y==3) return RIGHT;
			else if(last.x==0&&last.y==4) return RIGHT;
			else if(fromX==1&&fromY==3) return LEFT;
			else return STRAIGHT;
		}else{
			inCenter=true;
			return NOMOVE;
		}
	}else if(area=='c'){
		if(fromX!=3||fromY!=2)return STRAIGHT;
		else{
			inCenter=true;
			return NOMOVE;
		}
	}else if(area=='d'){
		if(fromX!=4||fromY!=2)return STRAIGHT;
		else{
			inCenter=true;
			return NOMOVE;
		}
	}else if(area=='e'){
		if(fromX!=5||fromY!=2){
			if(last.x==5&&last.y==0) return LEFT;
			else if(last.x==7&&last.y==1) return LEFT;
			else if(last.x==7&&last.y==3) return RIGHT;
			else if(last.x==6&&last.y==1) return LEFT;
			else if(last.x==6&&last.y==0) return RIGHT;
			else return STRAIGHT;
		}else{
			inCenter=true;
			return NOMOVE;
		}
	}else if(area=='f'){
		inCenter=true;
		return NOMOVE;
	}else if(area=='g'){
		if(fromX!=5||fromY!=5){
			if(last.x==6&&last.y==4) return LEFT;
			else return STRAIGHT;
		}else{
			inCenter=true;
			return NOMOVE;
		}
	}else if(area=='h'){
		if(fromX!=4||fromY!=5){
			if(last.x==5&&last.y==7) return RIGHT;
			else if(last.x==6&&last.y==7) return RIGHT;
			else if(last.x==7&&last.y==7) return RIGHT;
			else if(last.x==5&&last.y==6) return LEFT;
			else return STRAIGHT;
		}else{
			inCenter=true;
			return NOMOVE;
		}
	}else if(area=='i'){
		if(fromX!=4||fromY!=5){
			if(last.x==2&&last.y==6) return RIGHT;
			else return STRAIGHT;
		}else{
			inCenter=true;
			return NOMOVE;
		}
	}else{
		inCenter=true;
		return NOMOVE;
	}
}
