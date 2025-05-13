#include <Wire.h>

int rec_data[8] = {};
String key = "123e4567";

bool sentFlag = 0;

int counter = 0;
int temp = 0;

void requestEvent() {
  Serial.println("Looking for req bit\n");
  if (rec_data[2] == 0x01)
  {
    Serial.print("Sending Key\n");
    Wire.write(key.c_str());
  }
}

void receiveEvent(int bytes) 
{
  for (int loop = 0; loop < 8; loop++)  
  {
    int c = Wire.read();
    rec_data[loop] = c;
    Serial.println(rec_data[loop], HEX);
  }
  Serial.println("Array Formed");
}

void setup() {
  Wire.begin(0x16);                // join I2C bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  Serial.begin(9600);           // start serial for output
  Serial.println("Setup done");
}

void loop() {
  delay(1000);
  Serial.println(".");
}
