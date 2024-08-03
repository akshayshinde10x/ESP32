#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/
#define light 2
#define WLAN_SSID       "**********"
#define WLAN_PASS       "**********"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL

#define IO_USERNAME  "*******************"
#define IO_KEY       "***************************"


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);

// Setup a feed called 'light' for subscribing to changes.
Adafruit_MQTT_Subscribe sensor2 = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/light");


void MQTT_connect();

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(light,OUTPUT);
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&sensor2);
}

int x=0;

void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &sensor2) {
      Serial.print(F("Got: "));
      Serial.println((char *)sensor2.lastread);

      String light_status = (char *)sensor2.lastread;
      Serial.print("light_status : " + light_status);
      if(light_status == "ON"){
        digitalWrite(light,HIGH);
      } else if (light_status == "OFF") {
        digitalWrite(light,LOW);
      } else {
        Serial.print("Received invalid data..");
      }
    }
  }
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
