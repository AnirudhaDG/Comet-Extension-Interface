const uint8_t key[] = {0xAA, 0x01, 0x02, 0x03, 0x33, 0x05, 0x06, 0xFF};
const int key_length = sizeof(key);

const int packet_size = 8; // Start byte + 6 data bytes + end byte
uint8_t received_packet[packet_size];
bool packet_in_progress = false;
int bytes_received = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup Done!");
}

void action_request(uint8_t req_key) {
  if (req_key == 0x01) {
    // Send the key as hex array
    Serial.write(key, key_length);
  }
}

void loop() {
  while (Serial.available() > 0) {
    uint8_t incoming_byte = Serial.read();
    
    if (!packet_in_progress) {
      // Look for start byte
      if (incoming_byte == 0xAA) {
        packet_in_progress = true;
        bytes_received = 0;
        received_packet[bytes_received++] = incoming_byte;
      }
    } else {
      // Continue collecting bytes
      received_packet[bytes_received++] = incoming_byte;
      
      // Check if we've received a complete packet
      if (bytes_received >= packet_size) 
      {
        packet_in_progress = false;
        if (received_packet[0] == 0xAA && received_packet[packet_size - 1] == 0xFF) 
        {
          action_request(received_packet[2]);
          Serial.println("\nPacket Accepted");
        }
        else
        {
          Serial.println("\nPacket Discarded");
        }
      }
    }
  }
}