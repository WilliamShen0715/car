#include <LBLE.h>
#include <LBLEPeriphral.h>
#include <Servo.h>
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
int value=0;

#define SSID "CSIE-WLAN-Sparq"
#define PASSWD "wificsie"
#define TCP_IP "192.168.209.33"
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
int stray,fromX,fromY,toX,toY,dir,j,count=0,absoturn=0,turnback=0;
int counter=0,c_dis,l_dis,r_dis;
void Rotate(){
    analogWrite(rightpin2,LOW);
    analogWrite(rightpin1,255);
    analogWrite(leftpin2,255);
    analogWrite(leftpin1,LOW);
    delay(130);
    analogWrite(rightpin1,LOW);
    analogWrite(rightpin2,LOW);
    analogWrite(leftpin1,LOW);
    analogWrite(leftpin2,LOW); 
}
void reRotate(){
    analogWrite(rightpin2,255);
    analogWrite(rightpin1,LOW);
    analogWrite(leftpin2,LOW);
    analogWrite(leftpin1,255);
    delay(160);
    analogWrite(rightpin1,LOW);
    analogWrite(rightpin2,LOW);
    analogWrite(leftpin1,LOW);
    analogWrite(leftpin2,LOW); 
}
void Rotatehalf(){
    analogWrite(rightpin2,LOW);
    analogWrite(rightpin1,255);
    analogWrite(leftpin2,255);
    analogWrite(leftpin1,LOW);
    delay(80);
    analogWrite(rightpin1,LOW);
    analogWrite(rightpin2,LOW);
    analogWrite(leftpin1,LOW);
    analogWrite(leftpin2,LOW); 
}
void reRotatehalf(){
    analogWrite(rightpin2,255);
    analogWrite(rightpin1,LOW);
    analogWrite(leftpin2,LOW);
    analogWrite(leftpin1,255);
    delay(110);
    analogWrite(rightpin1,LOW);
    analogWrite(rightpin2,LOW);
    analogWrite(leftpin1,LOW);
    analogWrite(leftpin2,LOW); 
}
float get_dis(int trig,int echo){
  float duration;
  pinMode(trig,OUTPUT);  
  pinMode(echo,INPUT);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH,400000);
  return duration/29/2;
}
void blindturn(int dir){
  if(dir==5){
    analogWrite(rightpin1,LOW);
    analogWrite(rightpin2,LOW);
    analogWrite(leftpin1,LOW);
    analogWrite(leftpin2,LOW);
  }else if(dir==4){
    if(c_dis>25) for(int i=0;i<1;i++) walkAdjust();
    for(int i=0;i<4;i++) reRotate();
    for(int i=0;i<2;i++) walkAdjust();
  }else if(dir==6){
    if(c_dis>25) for(int i=0;i<3;i++) walkAdjust();
    for(int i=0;i<5;i++) Rotate();
    for(int i=0;i<2;i++) walkAdjust();
  }else if(dir==8) walkAdjust();
  else Automove();
}
void Automove(){
  if(c_dis>10) walkAdjust();
  else if(l_dis>30) blindturn(4);
  else blindturn(6);
}
void walkAdjust(){
  c_dis = get_dis(centerTrigPin,centerEchoPin);
  l_dis = get_dis(leftTrigPin,leftEchoPin);
  r_dis = get_dis(rightTrigPin,rightEchoPin);
  if(l_dis>30&&c_dis<10){
    reRotatehalf();return;
  }
  else if(r_dis>30&&c_dis<10){
    Rotatehalf();return;
  }
  else if(l_dis<9) for(int i=0;i<1;i++) Rotatehalf();
  else if(r_dis<9) for(int i=0;i<1;i++) reRotatehalf();
  else if(r_dis>11&&r_dis<19) Rotatehalf();
  else if(l_dis>11&&l_dis<19) reRotatehalf();
  /*else if(l_dis<13&&r_dis<13){
    if(l_dis-r_dis>4) reRotate();
    else if(r_dis-l_dis>4) Rotate();
  }*/
  analogWrite(rightpin1,255);
  analogWrite(rightpin2,LOW);
  analogWrite(leftpin1,255);
  analogWrite(leftpin2,LOW);
  delay(150);
  analogWrite(rightpin1,LOW);
  analogWrite(rightpin2,LOW);
  analogWrite(leftpin1,LOW);
  analogWrite(leftpin2,LOW); 
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
    if(y<3) return 'c';
    else if(y==6||y==5||y==4) return 'i';
    else if(y==7) return 'a';
    else return 'n';
  }else if(x==4){
    if(y>4) return 'h';
    else if(y==0) return 'c';
    else if(y==3) return 'f';
    else if(y==1||y==2) return 'd';
    else return 'n';
  }else if(x==5){
    if(y>5) return 'h';
    else if(y==5) return 'g';
    else if(y==4) return 'n';
    else if(y==3) return 'f';
    else if(y==2) return 'e';
    else return 'c';
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
    if(x==2&&y==5) return 0;
    else if(x>0&&y>5) return 2;
    else return 1;
  }else if(area=='b'||area=='c'||area=='d'||area=='f') return 0;
  else if(area=='e'){
    if(x==7&&y>1) return 1;
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
  c_dis = get_dis(centerTrigPin,centerEchoPin);
  l_dis = get_dis(leftTrigPin,leftEchoPin);
  r_dis = get_dis(rightTrigPin,rightEchoPin);
  if(absoturn&&fromX==5&&fromY==2){
      return RIGHT;absoturn==0;
    }else if(absoturn&&fromX==2&&fromY==2){
      return RIGHT;absoturn==0;
    }else if(!inCenter) return goCenter(from,fromX,fromY);
  else if(inCenter&&from!=to){//in center not in same area
  //walk around
    if(fromX==4&&fromY==5&&c_dis<12) return RIGHT;
    //else if(from=='i'&&to=='i') return RIGHT;
    else if(from=='c'&&c_dis<11) return RIGHT;
    else if(from=='d'&&c_dis<11) return RIGHT;
    else if(fromX==2&&fromY==5&&l_dis<13) return RIGHT;
    else if(fromY==5&&fromX==4&&c_dis<12) return RIGHT;
    else if(fromY==2&&fromX==5&&!absoturn) return LEFT;
    else return 8;
  }else if(fromX!=toX||fromY!=toY){ //in same area
    if(from=='a'){
      if(tstray==2&&l_dis<15&&c_dis>30&&r_dis>30) return RIGHT;
      else return 1; 
    }else if(from=='b'){
      if(fromX==2&&fromY==2&&c_dis<13) return RIGHT;
      return 1;
    }
    else if(from=='c'||from=='d'){
      if(l_dis<15&&r_dis>30) return RIGHT;
      else return 1;
    }else if(from=='e'){
      if(/*tstray==2&&*/c_dis<10) return RIGHT;
      //else if(tstray==3&&c_dis<10&&fstray!=2&&fstray!=3) return RIGHT;
      //else if(tstray==3&&fstray==2&&l_dis>30) return LEFT;
      //else if(tstray==3&&l_dis<15&&r_dis>30&&c_dis>30) return RIGHT;
      else return 1;
    }else if(from=='f'){
      if(r_dis<15) return LEFT;
      else return 1;
    }else if(from=='g'){
      if(l_dis<10) return RIGHT;
      else if(tstray==2&&l_dis<15&&c_dis>30&&r_dis>30) return RIGHT;
      else if(tstray==2&&r_dis<15&&c_dis>30&&l_dis>30) return LEFT;
      else return 1;
    }else if(from=='h'){
      if(l_dis<15&&r_dis>30) return RIGHT;
      else if(tstray==2&&r_dis<15&&c_dis>30&&l_dis>30) return LEFT;
      else if(tstray==2&&l_dis<15&&c_dis>30&&r_dis>30) return RIGHT;
      else return 1;
    }else{
      /*if(tstray==1&&c_dis>30&&l_dis>30&&r_dis>30) return RIGHT;
      else */return 1;
    }
  }else return NOMOVE;//arrive destination
}
int goCenter(char area,int fromX,int fromY){
  if(area!='e'){
    if(fromX<2||fromX>5||fromY<2||fromY>5) return 1;
    else{
      inCenter=true;
      return NOMOVE;
    }
  }else{//area e
    absoturn=1;
    if(fromX!=5||fromY!=2){
      if(r_dis<15&&fromY==2&&fromX==7){
        return LEFT;
      }
      else if(fromY==2&&l_dis<15&&fromX==7){
        return RIGHT;
      }
      else return 1;
    }else{
      absoturn=1;
      inCenter=true;
      return NOMOVE;
    }
  }
}
 LBLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214");
 LBLECharacteristicInt switchCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", LBLE_READ | LBLE_WRITE);
 void setup() {
  Serial.begin(115200);
  // Initialize BLE subsystem
  LBLE.begin();
  while (!LBLE.ready()) {
    delay(100);
  }
  Serial.println("BLE ready");
  Serial.print("Device Address = [");
  Serial.print(LBLE.getDeviceAddress());
  Serial.println("]");
  LBLEAdvertisementData advertisement;
  advertisement.configAsConnectableDevice("BLE LED");
  LBLEPeripheral.setName("BLE LED");
  ledService.addAttribute(switchCharacteristic);
  LBLEPeripheral.addService(ledService);
  LBLEPeripheral.begin();
  LBLEPeripheral.advertise(advertisement);
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
    delay(1000);
    wifiClient.write("join CCCCC B");  //join <ID> <team>
  pinMode(g_Pin, OUTPUT);//led light
  pinMode(b_Pin, OUTPUT);
  pinMode(rightpin1,OUTPUT);
  pinMode(rightpin2,OUTPUT);
  pinMode(leftpin1,OUTPUT);
  pinMode(leftpin2,OUTPUT);
  pinMode(rightEnable,OUTPUT);
  pinMode(leftEnable,OUTPUT);
  digitalWrite(rightEnable,HIGH);
  digitalWrite(leftEnable,HIGH);
  analogWrite(g_Pin,0);//led light
  analogWrite(b_Pin,0);
}
void loop() {
  if (switchCharacteristic.isWritten()&&count!=0) {
    value = switchCharacteristic.getValue();
    Serial.println(value);
    if(value==5) blindturn(5);
    else if(value==8) Automove();
    else if(value==6) Rotate();
    else if(value==4) reRotate();
    if(count==4) count==0;
    else count++;
  }else{
    //wifi
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
        }else if(buf[0]=='s'){
          analogWrite(b_Pin,255);
        }
        toX = 0;
        toY = 0;
        Serial.print("fromX,fromY:");
        Serial.print(fromX);
        Serial.print(" ");
        Serial.println(fromY);
        Serial.print("buf:");
        Serial.println(buf);
       if(fromX == toX&&fromY==toY) dir = NOMOVE;
  //decide how to move
        if(fromX!=-3&&fromY!=-16&&(fromX!=toX||fromY!=toY)){
          if(fromX!=check.x||fromY!=check.y){
            last.x=check.x;last.y=check.y;
            dir = findRoad(fromX,fromY,toX,toY);blindturn(dir);
            turnback=0;
          }else{
            blindturn(1);
            if(fromX==check.x&&fromY==check.y) turnback++;
            if(turnback>50){
              analogWrite(rightpin1,LOW);
              analogWrite(rightpin2,255);
              analogWrite(leftpin1,LOW);
              analogWrite(leftpin2,255);
              delay(100);
              analogWrite(rightpin1,LOW);
              analogWrite(rightpin2,LOW);
              analogWrite(leftpin1,LOW);
              analogWrite(leftpin2,LOW);
              Rotate();Rotate();
              turnback=0;
            }
          }
          check.x=fromX;check.y=fromY;
        }else{
          blindturn(5);
        }
      i = 0;
      wifiClient.write("position");
      value = switchCharacteristic.getValue();
      if(value!=0||value!=100) count++;
    }
  }
  delay(100);
}
