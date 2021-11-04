#include "Timer.h" 
#include <Ultrasonic.h>
#include <Servo.h>   //載入函式庫，這是內建的，不用安裝

int distance,scan,dl,dr,t=4,tr=4,tl=4,tb=4,ts=4;
Servo myservo;  // 建立SERVO物件
Ultrasonic ultrasonic(2, 3);
Timer t1;  //建立Timer物件

//.............................................................................................
void check(){
  distance = ultrasonic.read(); //不加參數就是輸出CM，可用read(INC)輸出英寸
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  if(distance<=20){
    t1.stop(scan);      //停止計時器
    
    for(int i=1;i<=10;i++){
     stepStop();
    }
    delay(200);

//................... 檢測超音波感測器左右邊距離.............................   
    myservo.write(70);  //鏡頭朝右，量右邊距離dr
    delay(200);
    dr = ultrasonic.read();
    Serial.println(dr);
    
    myservo.write(110);  //鏡頭朝左，量左邊距離dl
    delay(200);
    dl = ultrasonic.read();
    Serial.println(dl);
    
    myservo.write(90);  //旋轉到90度，讓鏡頭朝前
    delay(300);

//........................................................................

    
    if(dr>dl){                  //如果dr>dl即右轉
      for(int i=1;i<=25;i++){
          stepRight();
        }
      for(int i=1;i<=15;i++){
          stepForward();
        }
      for(int i=1;i<=25;i++){
          stepLeft();
        }
     }   
    else{                        //如果dr<=dl即左轉
      for(int i=1;i<=25;i++){
          stepLeft();
        }
      for(int i=1;i<=15;i++){
          stepForward();
        }
      for(int i=1;i<=25;i++){
          stepRight();
        }
     }
    scan=t1.every(500,check); // 重新起動計時器 
  }
  
}

void setup() {
  
  for(int i=4;i<12 ;i++){
  pinMode(i, OUTPUT);
 }
  Serial.begin(9600);
  myservo.attach(13);  // 設定要將伺服馬達接到哪一個PIN腳
  myservo.write(0);  //旋轉到0度，就是一般所說的歸零
  delay(200);
  myservo.write(90);  //旋轉到90度，讓鏡頭朝前
  delay(200);
  scan=t1.every(500,check); // 每500ms呼叫check
  
}

void loop() {
  
  stepForward();
  t1.update(); //更新t1
}


void stepForward(){
  digitalWrite(8,0);
  digitalWrite(4,0);
  digitalWrite(9,0);
  digitalWrite(5,0);
  digitalWrite(10,1);
  digitalWrite(6,1);
  digitalWrite(11,1);
  digitalWrite(7,1);
  delay(t);

  digitalWrite(4,1);
  digitalWrite(8,1);
  digitalWrite(5,0);
  digitalWrite(9,0);
  digitalWrite(6,0);
  digitalWrite(10,0);
  digitalWrite(7,1);
  digitalWrite(11,1);
  delay(t);

  digitalWrite(8,1);
  digitalWrite(4,1);
  digitalWrite(9,1);
  digitalWrite(5,1);
  digitalWrite(10,0);
  digitalWrite(6,0);
  digitalWrite(11,0);
  digitalWrite(7,0);
  delay(t);

  digitalWrite(4,0);
  digitalWrite(8,0);
  digitalWrite(5,1);
  digitalWrite(9,1);
  digitalWrite(6,1);
  digitalWrite(10,1);
  digitalWrite(7,0);
  digitalWrite(11,0);
  delay(t);

}


void stepLeft(){
  digitalWrite(8,0);
  digitalWrite(4,0);
  digitalWrite(9,0);
  digitalWrite(5,0);
  digitalWrite(10,1);
  digitalWrite(6,1);
  digitalWrite(11,1);
  digitalWrite(7,1);
  delay(tl);

  digitalWrite(4,0);
  digitalWrite(8,1);
  digitalWrite(5,0);
  digitalWrite(9,0);
  digitalWrite(6,1);
  digitalWrite(10,0);
  digitalWrite(7,1);
  digitalWrite(11,1);
  delay(tl);

  digitalWrite(8,1);
  digitalWrite(4,1);
  digitalWrite(9,1);
  digitalWrite(5,0);
  digitalWrite(10,0);
  digitalWrite(6,0);
  digitalWrite(11,0);
  digitalWrite(7,1);
  delay(tl);

  digitalWrite(4,1);
  digitalWrite(8,0);
  digitalWrite(5,0);
  digitalWrite(9,1);
  digitalWrite(6,0);
  digitalWrite(10,1);
  digitalWrite(7,1);
  digitalWrite(11,0);
  delay(tl);
  
  digitalWrite(8,0);
  digitalWrite(4,1);
  digitalWrite(9,0);
  digitalWrite(5,1);
  digitalWrite(10,1);
  digitalWrite(6,0);
  digitalWrite(11,1);
  digitalWrite(7,0);
  delay(tl);

  digitalWrite(4,1);
  digitalWrite(8,1);
  digitalWrite(5,1);
  digitalWrite(9,0);
  digitalWrite(6,0);
  digitalWrite(10,0);
  digitalWrite(7,0);
  digitalWrite(11,1);
  delay(tl);

  digitalWrite(8,1);
  digitalWrite(4,0);
  digitalWrite(9,1);
  digitalWrite(5,1);
  digitalWrite(10,0);
  digitalWrite(6,1);
  digitalWrite(11,0);
  digitalWrite(7,0);
  delay(tl);

  digitalWrite(4,0);
  digitalWrite(8,0);
  digitalWrite(5,1);
  digitalWrite(9,1);
  digitalWrite(6,1);
  digitalWrite(10,1);
  digitalWrite(7,0);
  digitalWrite(11,0);
  delay(tl);
}

void stepRight(){
  digitalWrite(4,0);
  digitalWrite(8,0);
  digitalWrite(5,0);
  digitalWrite(9,0);
  digitalWrite(6,1);
  digitalWrite(10,1);
  digitalWrite(7,1);
  digitalWrite(11,1);
  delay(tr);

  digitalWrite(8,0);
  digitalWrite(4,1);
  digitalWrite(9,0);
  digitalWrite(5,0);
  digitalWrite(10,1);
  digitalWrite(6,0);
  digitalWrite(11,1);
  digitalWrite(7,1);
  delay(tr);

  digitalWrite(4,1);
  digitalWrite(8,1);
  digitalWrite(5,1);
  digitalWrite(9,0);
  digitalWrite(6,0);
  digitalWrite(10,0);
  digitalWrite(7,0);
  digitalWrite(11,1);
  delay(tr);

  digitalWrite(8,1);
  digitalWrite(4,0);
  digitalWrite(9,0);
  digitalWrite(5,1);
  digitalWrite(10,0);
  digitalWrite(6,1);
  digitalWrite(11,1);
  digitalWrite(7,0);
  delay(tr);
  
  digitalWrite(4,0);
  digitalWrite(8,1);
  digitalWrite(5,0);
  digitalWrite(9,1);
  digitalWrite(6,1);
  digitalWrite(10,0);
  digitalWrite(7,1);
  digitalWrite(11,0);
  delay(tr);

  digitalWrite(8,1);
  digitalWrite(4,1);
  digitalWrite(9,1);
  digitalWrite(5,0);
  digitalWrite(10,0);
  digitalWrite(6,0);
  digitalWrite(11,0);
  digitalWrite(7,1);
  delay(tr);

  digitalWrite(4,1);
  digitalWrite(8,0);
  digitalWrite(5,1);
  digitalWrite(9,1);
  digitalWrite(6,0);
  digitalWrite(10,1);
  digitalWrite(7,0);
  digitalWrite(11,0);
  delay(tr);

  digitalWrite(8,0);
  digitalWrite(4,0);
  digitalWrite(9,1);
  digitalWrite(5,1);
  digitalWrite(10,1);
  digitalWrite(6,1);
  digitalWrite(11,0);
  digitalWrite(7,0);
  delay(tr);

}

void stepBack(){
  digitalWrite(8,1);
  digitalWrite(4,1);
  digitalWrite(9,1);
  digitalWrite(5,1);
  digitalWrite(10,0);
  digitalWrite(6,0);
  digitalWrite(11,0);
  digitalWrite(7,0);
  
  delay(tb);

  digitalWrite(4,1);
  digitalWrite(8,1);
  digitalWrite(5,0);
  digitalWrite(9,0);
  digitalWrite(6,0);
  digitalWrite(10,0);
  digitalWrite(7,1);
  digitalWrite(11,1);
  delay(tb);

  digitalWrite(8,0);
  digitalWrite(4,0);
  digitalWrite(9,0);
  digitalWrite(5,0);
  digitalWrite(10,1);
  digitalWrite(6,1);
  digitalWrite(11,1);
  digitalWrite(7,1);
  delay(tb);

  digitalWrite(4,0);
  digitalWrite(8,0);
  digitalWrite(5,1);
  digitalWrite(9,1);
  digitalWrite(6,1);
  digitalWrite(10,1);
  digitalWrite(7,0);
  digitalWrite(11,0);
  delay(tb);
}

void stepStop(){
  digitalWrite(8,1);
  digitalWrite(4,1);
  digitalWrite(9,1);
  digitalWrite(5,1);
  digitalWrite(10,1);
  digitalWrite(6,1);
  digitalWrite(11,1);
  digitalWrite(7,1);
  delay(ts);
}
