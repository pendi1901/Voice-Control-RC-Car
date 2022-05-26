#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BluetoothReceive(12, 13); // TX, RX respetively
String voicecommand;
//const int pingPin = 31;
//const int echoPin = 32;
//servo motor code 
Servo myservo;
int pos = 0;


void setup() {
 BluetoothReceive.begin(9600);
 Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(45,INPUT);
  pinMode(46,OUTPUT);
  
  
  //servo code
  myservo.attach(36);

}

long microToInches(long microseconds) {
  return microseconds/74/2;
}

void loop(){
  //Serial.println("Hello");
  pos = 90;
  myservo.write(pos);
  long duration, inches;
  int temp = digitalRead(45);
  Serial.println("Intensity");
  Serial.println(temp);
//  pinMode(pingPin, OUTPUT);
//  digitalWrite(pingPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(pingPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(pingPin, LOW);
//  digitalWrite(echoPin, INPUT);
//  duration = pulseIn(echoPin, HIGH);
//  inches = microToInches(duration);
////  Serial.println(duration);
////  Serial.println("duration");
//  Serial.println(inches);
//  Serial.println("in");

  
  while(BluetoothReceive.available()){
     //Delay added to make thing stable
    delay(10); 
    //Conduct a serial read
    char c = BluetoothReceive.read(); 
    Serial.println(c);
    //build the string- "forward", "reverse", "left" and "right"
    voicecommand += c; 

  }
    //Serial.println("After Loop");
  if (voicecommand.length() > 0) {
    Serial.println(voicecommand);

  if(temp ==HIGH){
     digitalWrite(46,HIGH);
     
     
  }
  else{
    digitalWrite(46,LOW);
    
  }
  
  if ( voicecommand == "stop"){
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(10);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    delay(100);
  }


  else if(voicecommand == "forward" )
  {
    Serial.println(0);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    delay(500);
  }
  else if(voicecommand == "back"){
    Serial.println(1);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    delay(500);
  }

  else if(voicecommand == "left" ){
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    Serial.println(8);
    //servo code 
    for(pos = 90 ; pos>=0 ; pos-=1){
    myservo.write(pos);
    delay(15);
    }
    delay(1000);
    for(pos = 0 ; pos<=90 ; pos+=1){
    myservo.write(pos);
    delay(15);
    }
    delay(500);

  }
  else if(voicecommand == "right" ){
    //servo code 
    for(pos = 90 ; pos<=180 ; pos+=1){
    myservo.write(pos);
    delay(15);
    }
    delay(1000);
    for(pos = 180 ; pos>=90 ; pos-=1){
    myservo.write(pos);
    delay(15);
    }
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    
    
    delay(500);

  }
//  else if (inches < 15){
//    digitalWrite(3, LOW);
//    digitalWrite(4, HIGH);
//    delay(10);
//    digitalWrite(3, LOW);
//    digitalWrite(4, LOW);
//    delay(100);
//  }



  


   voicecommand="";}
   } //Reset the variable
