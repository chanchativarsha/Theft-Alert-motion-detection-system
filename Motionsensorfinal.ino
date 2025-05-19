

#define BLYNK_TEMPLATE_ID "TMPL3wb02a53V"
#define BLYNK_TEMPLATE_NAME "my theft control"
#define BLYNK_AUTH_TOKEN "SKBcF0TvNEMabXDPxRIP2PZy-oY4CDDu"


#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "RRU_Student";  // type your wifi name
char pass[] = "StudentW!F!@Rru";  // type your wifi password

#define PIR_SENSOR 4
BlynkTimer timer;

void notifyOnTheft() {
  int isTheftAlert = digitalRead(PIR_SENSOR);
  Serial.println(isTheftAlert);
  if (isTheftAlert == 1) {
    Serial.println("Theft Alert in Home");
    Blynk.logEvent("theft", "Theft Alert in Home");
  }
}

void setup() {
  pinMode(PIR_SENSOR, INPUT);
  Serial.begin(115200);  // Ensure this matches the Serial Monitor baud rate
  Serial.println("Starting Blynk...");
  Blynk.begin(auth, ssid, pass);
  
  // Wait until connected to Blynk
  while (Blynk.connected() == false) {
    Serial.println("Connecting to Blynk...");
    delay(1000);
  }

  Serial.println("Connected to Blynk");
  timer.setInterval(5000L, notifyOnTheft);
}

void loop() {
  Blynk.run();
  timer.run();
}
