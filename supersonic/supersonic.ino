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
int counter=0,c_dis,l_dis,r_dis,ltok=0,rtok=0,mtok=0;
int cdata[10],rdata[10],ldata[10],sort[10];
int m[7],once=0;
void Rotate(){
    analogWrite(rightpin2,LOW);
    analogWrite(rightpin1,200);
    analogWrite(leftpin2,200);
    analogWrite(leftpin1,LOW);
    delay(130);
    analogWrite(rightpin1,LOW);
    analogWrite(rightpin2,LOW);
    analogWrite(leftpin1,LOW);
    analogWrite(leftpin2,LOW); 
}
void reRotate(){
    analogWrite(rightpin2,200);
    analogWrite(rightpin1,LOW);
    analogWrite(leftpin2,LOW);
    analogWrite(leftpin1,200);
    delay(150);
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
void Bsort(int nSize , int A[])
{
    int i , j , t ;
    for (i = 0 ; i< nSize-1 ;i++){
        for (j = nSize-1 ; j>i ;j--){
            if (A[j] < A[j-1]){
                t = A[j] ;A[j] = A[j-1] ;A[j-1] = t;}
        }
    }
}
void blindturn(int dir){
  if(dir==6) for(int i=0;i<6;i++) Rotate();
  else for(int i=0;i<5;i++) reRotate();
  for(int i=0;i<3;i++) walkAdjust();
}
void turn(int dir){
  //c_dis = get_dis(centerTrigPin,centerEchoPin);
  if(c_dis>8||dir==8) walkAdjust();
  else if(dir==5){
    digitalWrite(rightpin1,LOW);
    digitalWrite(rightpin2,LOW);
    digitalWrite(leftpin1,LOW);
    digitalWrite(leftpin2,LOW); 
  }
  else{
    while(counter!=-1){
      if(counter!=-1&&counter<10){
        if(dir==4){
          reRotate();
          //r_dis = get_dis(rightTrigPin,rightEchoPin);
          if(r_dis<40) ldata[counter%10] = r_dis;
          else ldata[counter%10] = 0;
          counter+=1;
        }else if(dir==6){
          Rotate();
          //l_dis = get_dis(leftTrigPin,leftEchoPin);
          if(l_dis<40) rdata[counter%10] = l_dis;
          else rdata[counter%10] = 0;
          counter+=1;
        }
      }else if(counter==10){
        m[0]=m[1]=m[2]=m[3]=m[4]=100;
        for(int i=5;i<10;i++){
          if(dir==6) m[i] = rdata[i]-rdata[i-1];
          else if(dir==4) m[i] = ldata[i]-ldata[i-1];
        }
        for(int i=0;i<10;i++) sort[i] = m[i];
        Bsort(10,sort);
        for(int i=0;i<10;i++) if(sort[i]>0){if(sort[i]!=100) mtok=sort[i];else mtok=sort[i-1];break;}
        for(int i=5;i<9;i++){
          if(dir==6){
            if(m[i]<=1||counter==-1){
              counter=-1;
              reRotate();
            }
          }else if(dir==4){
            if(m[i]<=1||counter==-1){
              counter=-1;
              Rotate();
            }
          }
        }
        if(counter!=-1) counter=0;
      }else return;
      delay(50);
    }
  }
  counter=0;
}
void walkAdjust(){
  l_dis = get_dis(leftTrigPin,leftEchoPin);
  r_dis = get_dis(rightTrigPin,rightEchoPin);
  if(l_dis>13&&l_dis<25) reRotate();
  else if(r_dis>13&&r_dis<25) Rotate();
  else if(l_dis<20&&r_dis<20){
    if(l_dis-r_dis>3) reRotate();
    else if(r_dis-l_dis>3) Rotate();
  }else if(l_dis<10) Rotate();
  else if(r_dis<10) reRotate();
  analogWrite(rightpin1,255);
  analogWrite(rightpin2,LOW);
  analogWrite(leftpin1,255);
  analogWrite(leftpin2,LOW);
  delay(130);
  analogWrite(rightpin1,LOW);
  analogWrite(rightpin2,LOW);
  analogWrite(leftpin1,LOW);
  analogWrite(leftpin2,LOW);
}
void setup(){
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
  analogWrite(b_Pin,255);
}
void loop(){
  l_dis = get_dis(leftTrigPin,leftEchoPin);
  r_dis = get_dis(rightTrigPin,rightEchoPin);
  c_dis = get_dis(centerTrigPin,centerEchoPin);
  Serial.print("l,r,c:");
  Serial.print(l_dis);
  Serial.print(" ");
  Serial.print(r_dis);
  Serial.print(" ");
  Serial.println(c_dis);
  if(l_dis<15&&r_dis>40&&c_dis>40&&once<1){
    analogWrite(rightpin1,255);
    analogWrite(rightpin2,LOW);
    analogWrite(leftpin1,255);
    analogWrite(leftpin2,LOW);
    delay(160);
    analogWrite(rightpin1,LOW);
    analogWrite(rightpin2,LOW);
    analogWrite(leftpin1,LOW);
    analogWrite(leftpin2,LOW);
    c_dis=8;blindturn(6);
    once++;
  }
  else if(c_dis>10||l_dis<10) walkAdjust(); 
  else if(c_dis<10){
    blindturn(4);
    //walkAdjust();
  }else walkAdjust();
  delay(100);
}

