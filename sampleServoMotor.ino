/* 変数宣言 */
// サーボモータ関連
#include <Servo.h>
Servo myServo;  // サーボモータを角度（degree）指定で制御するためのライブラリ
int analogPin = 9;  // PWM信号を出力するピン
int degreeValue = 0;  // サーボモータに出力する角度の値
bool degreeFlag = true; // 角度の増加と減少を切り替えるためのフラグ 
// 稼働確認用LED関連
int ledPin = 13;  // Arudinoのボード上に備わるLEDを表す
String ledValue = "HIGH"; // LEDの点灯／点滅の状態を判定するための変数

void setup() {
  Serial.begin(9600); // 稼働状況をシリアルモニタで確認するために実装

  pinMode( ledPin, OUTPUT );
  myServo.attach(analogPin);  // サーボを指定のピンに接続
  analogWrite(analogPin, 0);  // 起動開始時に0度に初期化
  delay(2000);  // 通電と共に起動開始するため，いきなり動き出さないよう初期化後に2秒ほど間をあける
}

void loop() {
  // 稼働確認用LED関連：ボード上のLEDを，loop()末尾のdelay()間隔で点滅させる
   if( ledValue == "HIGH" ){
    ledValue = "LOW";
    digitalWrite( ledPin, LOW );
    Serial.println("LOW");
  }
  else if( ledValue == "LOW" ){
    ledValue = "HIGH";
    digitalWrite( ledPin, HIGH );
    Serial.println("HIGH");
  }
  
  // サーボモータ関連：
  if( degreeFlag == true){  // 180度まで増加させる
    degreeValue += 20;
    if( degreeValue > 180 ){
      degreeFlag = false; // 180度を上回ったら，減少フラグを立てる
    }
  }
  else{
    degreeValue-= 20; // 0度まで減少させる
    if( degreeValue < 0 ){
      degreeFlag = true;  // 0度を下回ったら，増加フラグを立てる
    }
  }
  myServo.write(degreeValue); // サーボモータに角度を送信する
  Serial.println(degreeValue); // 現在の角度をシリアルモニタで確認できるようにしている

  // 角度の増減量や，下記delay()の間隔は，使用する目的や環境に応じて適宜調節されたし
  delay(100);
}
