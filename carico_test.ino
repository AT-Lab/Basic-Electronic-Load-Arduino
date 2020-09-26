/*
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 */
#include <SPI.h>
#include <SD.h>

#define chipSelect 4


void setup() {
  TCCR1B = TCCR1B & B11111000 | B00000001; //PWM frequency 31kHz
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("Card initialized.");

}

void loop() {
  int value = 0;
  
  value = analogRead(A0)>>2;

  if(value > 5){
    
  analogWrite(9, value);
  float current = 1000.0*float(value)/255; // 5V -> 1000mA 
  
  value = analogRead(A1);
  float voltage = float(value)*10/1023.0; // 5V -> 10V
  
//  Serial.print("Current: ");
//  Serial.print(current, 5);
//  Serial.print("Voltage: ");
//  Serial.println(voltage, 3);
  
  String dataString = String(millis());
  dataString += ",";
  dataString += String(current);
  dataString += ",";
  dataString += String(voltage);
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  else {
    Serial.println("Error opening datalog.txt");
  }
      
  }else{
    Serial.println("Stop");
  }
  
  delay(500);
}
