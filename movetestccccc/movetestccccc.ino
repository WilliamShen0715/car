#include <LWiFi.h>

#define centerTrigPin 2
#define centerEchoPin 3
#define leftTrigPin 4
#define leftEchoPin 5
#define rightTrigPin 6
#define rightEchoPin 7
#define g_Pin 8
#define b_Pin 9
#define leftEnable 10
#define leftpin1 11
#define leftpin2 12
#define rightpin1 13
#define rightpin2 14
#define rightEnable 15
#define LEFT 4
#define STRAIGHT 8
#define RIGHT 6
#define NOMOVE 5

#define SSID "CSIE-WLAN"
#define PASSWD "wificsie"
#define TCP_IP "192.168.208.185"
#define TCP_PORT 5000
WiFiClient wifiClient;
static char buf[32];
static int messageLen;

class node{
  public:
  int x,y;
};
node last,check;
bool inCenter=false;
char area;
int stray,fromX,fromY,toX,toY,dir;

/*float get_dis(int trig,int echo){
  float duration;
  pinMode(trig,OUTPUT);  
  pinMode(echo,INPUT);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH,5000000);
  return duration/29/2;
}*/
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
void TurnLeft(){
    digitalWrite(rightpin1,LOW);
    digitalWrite(rightpin2,HIGH);
    digitalWrite(leftpin1,HIGH);
    digitalWrite(leftpin2,LOW);
    delay(700);
    GoStraight();
  }
void TurnRight(){
    digitalWrite(rightpin2,LOW);
    digitalWrite(rightpin1,HIGH);
    digitalWrite(leftpin2,HIGH);
    digitalWrite(leftpin1,LOW);
    delay(700);
    GoStraight();
  }
void GoStraight(){
    digitalWrite(rightpin1,HIGH);
    digitalWrite(rightpin2,LOW);
    digitalWrite(leftpin1,HIGH);
    digitalWrite(leftpin2,LOW);
    delay(200); 
    digitalWrite(rightpin1,LOW);
    digitalWrite(rightpin2,LOW);
    digitalWrite(leftpin1,LOW);
    digitalWrite(leftpin2,LOW); 
    
 }
void DirectionSelect(int x){
    if(x==4){ TurnLeft();}
    if(x==8){ GoStraight();}
    if(x==6){ TurnRight();}
}
void setup() {//wifi
  Serial.begin(115200);
//等待開啟 Serial。
    while (!Serial)
      ;
    int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED) {
        status = WiFi.begin(SSID, PASSWD);
    }
// Conenct to AP successfully
    wifiClient.connect(TCP_IP, TCP_PORT);    
    Serial.println("connect wifi");
        Serial.print("status:");
        Serial.println(status);
    wifiClient.write("join CCCCC B");  //join <ID> <team>
  
  pinMode(g_Pin, OUTPUT);//led light
  pinMode(b_Pin, OUTPUT);
  pinMode(rightpin1,OUTPUT);
  pinMode(rightpin2,OUTPUT);
  pinMode(leftpin1,OUTPUT);
  pinMode(leftpin2,OUTPUT);
  pinMode(rightEnable,OUTPUT);
  pinMode(leftEnable,OUTPUT);
  digitalWrite(rightpin1,HIGH);
  digitalWrite(rightpin2,LOW);
  digitalWrite(leftpin1,HIGH);
  digitalWrite(leftpin2,LOW);
  digitalWrite(rightEnable,HIGH);
  digitalWrite(leftEnable,HIGH);
  last.x=0;last.y=0;check.x=0;check.y=0;
}

void loop() 
{ //wifi
  int i = 0;
    while (wifiClient.available()) {
        buf[i++] = wifiClient.read();
        delayMicroseconds(10);
    }
    if (i != 0) {
      buf[i] = '\0';
//check which instruction ***********************************
      if(buf[0]=='p'){
        fromX = buf[9]-'0';
        fromY = buf[11]-'0';
      }
      Serial.print("fromX,fromY:");
      Serial.print(fromX);
      Serial.print(" ");
      Serial.println(fromY);
      Serial.print("buf:");
      Serial.println(buf);
//decide how to move
      toX = 7;
      toY = 7;
      if(fromX!=check.x||fromY!=check.y){
        last.x=check.x;last.y=check.y;
      }
      //dir = findRoad(fromX,fromY,toX,toY);
      //Serial.print("dir:");
      //Serial.println(dir);
      //DirectionSelect(dir);
      TurnLeft();
      delay(10);
      //TurnRight();
      //delay(10); 
      GoStraight();
      check.x=fromX;check.y=fromY;
    }
    i = 0;
    wifiClient.write("position");
    delay(10);  

  analogWrite(g_Pin,0);//led light
  analogWrite(b_Pin,255);
  //float dis = get_dis(centerTrigPin,centerEchoPin);
  
 }
