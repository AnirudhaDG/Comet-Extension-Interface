String key = "123e45678";

int index = 0;
const int num_bytes = 8;
uint8_t received_hex[num_bytes];

void setup() {
  Serial.begin(115200);
}

void action_request(uint8_t req_key)
{
  if (req_key == 0x01)
  {
    Serial.print(key);
  }
}

void loop() {
  if (Serial.available() >= num_bytes) { // Wait for all 5 bytes
    for (int i = 0; i < num_bytes; i++) {
      received_hex[i] = Serial.read(); // Store each byte
    }

    // // Print received hex array (for verification)
    // for (int i = 0; i < num_bytes; i++) {
    //   if (received_hex[i] < 0x10) Serial.print("0"); // Pad leading zero
    //   Serial.print(received_hex[i], HEX);
    //   Serial.print(" ");
    // }
    // Serial.println();
    action_request(received_hex[2]);
  }

  
}
