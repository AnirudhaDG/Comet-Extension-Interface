#include <Wire.h>

#define comet_packet_size 8

uint8_t rec_data[comet_packet_size] = {};
const uint8_t key[] = {0xAA, 0x01, 0x02, 0x03, 0x04, 0x06, 0x48, 0xFF};
const int key_length = sizeof(key);

bool isValid = 0;

int counter = 0;
int temp = 0;

void requestEvent() {
  if (validate_packet() && rec_data[2] == 0x01)
  {
    Serial.print("Validated, request byte found, sending Key\n");
    Wire.write(key, key_length);
  }
}

void receiveEvent(int bytes) 
{
  for (int loop = 0; loop < 8; loop++)  
  {
    int c = Wire.read();
    rec_data[loop] = c;
//    Serial.print(rec_data[loop], HEX);
//    Serial.print (" ");
  }
//  Serial.println();
}

int validate_packet()
{
  if (rec_data[0] == 0xAA && rec_data[comet_packet_size - 1] == 0xFF)
  {
//    Serial.println("Array Formed and Validated");
    isValid = 1;
    return 1;
  }
  else
  {
//    printf("Invalid Array");
    isValid = 0;
    return 0;
  }
}

void setup() {
  Wire.begin(0x16);
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  Serial.begin(115200);           // start serial for output
  Serial.println("Setup done I2C");
}

void loop() {

}