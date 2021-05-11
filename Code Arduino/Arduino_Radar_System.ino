/*
 * Pin LCD I2C    ||  Pin Arduino    
 *    GND               Pin GND
 *    VCC               Pin 5V
 *    SDA               Pin A4
 *    SCL               Pin A5
*/

/*
 * Pin HC-SR04   || Pin Arduino
 *     GND            Pin GND
 *     TRIG           Pin 9
 *     ECHO           Pin 8
 *     VCC            Pin 5V
*/

// Pin Servo => Pin 10
// Led       => Pin 11
// Buzzer    => Pin 12

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
const int pinled = 11;
const int pinbuz = 12;

LiquidCrystal_I2C lcd(0x27,16,2);
const int trigPin = 9;
const int echoPin = 8;
long duration;
int distance;
Servo myServo;
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(pinled, OUTPUT);
  pinMode(pinbuz, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(10);
}
void loop() {
  for(int i=15; i<=165; i++){  
  myServo.write(i);
  delay(20);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  if(distance < 20){
    myServo.write(i);
    delay(2000);
    lcd.setCursor(0,1); 
    lcd.print("Jarak: "); 
    lcd.print(distance); 
    lcd.print(" cm ");
    digitalWrite(pinled, HIGH);
    delay(100);
    digitalWrite(pinled, LOW);
    delay(100);
    digitalWrite(pinbuz, HIGH);
    delay(100);
    digitalWrite(pinbuz, LOW);
    delay(100);
    digitalWrite(pinled, HIGH);
    delay(100);
    digitalWrite(pinled, LOW);
    delay(100);
    digitalWrite(pinbuz, HIGH);
    delay(100);
    digitalWrite(pinbuz, LOW);
    delay(100);        
  }else if(distance > 21 || distance <100){
    lcd.setCursor(0,0);
    lcd.print("Benda Terdeteksi");
    lcd.setCursor(0,1);
    lcd.print("Jarak: ");  
    lcd.print(distance); 
    lcd.print(" cm ");  
  }
  }
  
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(20);
distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  if(distance < 20){
    myServo.write(i);
    delay(2000);
    lcd.setCursor(0,1); 
    lcd.print("Jarak: "); 
    lcd.print(distance); 
    lcd.print(" cm ");
    digitalWrite(pinled, HIGH);
    delay(100);
    digitalWrite(pinled, LOW);
    delay(100);
    digitalWrite(pinbuz, HIGH);
    delay(100);
    digitalWrite(pinbuz, LOW);
    delay(100); 
    digitalWrite(pinled, HIGH);
    delay(100);
    digitalWrite(pinled, LOW);
    delay(100);
    digitalWrite(pinbuz, HIGH);
    delay(100);
    digitalWrite(pinbuz, LOW);
    delay(100);
  }else if(distance > 21 || distance <100){
    lcd.setCursor(0,0);
    lcd.print("Benda Terdeteksi");
    lcd.setCursor(0,1);
    lcd.print("Jarak: ");  
    lcd.print(distance); 
    lcd.print(" cm ");  
  }else{
    lcd.noDisplay();
  }
  }
}

int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;
}
