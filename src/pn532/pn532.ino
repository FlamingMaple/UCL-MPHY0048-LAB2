#include <Wire.h>
#include <Adafruit_PN532.h>

#define PN532_IRQ   (8)
#define PN532_RESET (7) // RST not needed for operation, but defined anyway
// SDA and SCL are connected to standard XIAO I2C enabled GPIO pins

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

uint8_t data[4]; // Initialize array for reading pages which consist of 4 bytes

void setup(void) {
  //Serial.begin(57600);
  nfc.begin();
  nfc.SAMConfig();
}

void loop(void) {  
   uint8_t uid[] = {0,0,0,0,0,0,0};
   uint8_t uidLength;
   memset(data, 0, 4); // Fills the first four bytes with zeros, as four bytes per page
   if(nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
     // NFC Memory is read as pages, with each page being 4 bytes
     if(nfc.ntag2xx_ReadPage(4, data)) { // User memory starts at page 0x04h
      uint8_t spikeCount = data[0]; // First byte is spike count
      //Serial.println(spikeCount);
      delay(1000);
     }
   }
}
