#include <DS3231.h> // Include the DS3231 library

DS3231 rtc(SDA, SCL); // Create an RTC object with default I2C pins

void setup() {
  // Setup Serial connection
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(15, 18, 30);     // Set the time to 14:39:30 (24hr format)
  //rtc.setDate(12, 12, 2024);   // Set the date to December 12st, 2024
}


void loop() {
 // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating
  delay (1000);
}

