
#define SENSOR_PIN 18 // ESP32 pin GIOP18 connected to OUT pin of IR obstacle avoidance sensor
#define LED_PIN 19 // ESP32 pin GIOP18 connected to OUT pin of IR obstacle avoidance sensor


void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int state = digitalRead(SENSOR_PIN); //analogRead(SENSOR_PIN);

  if (state == LOW){
    Serial.println("The obstacle is present");
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    digitalWrite(LED_PIN, LOW);
    Serial.println("The obstacle is NOT present");
  }1
  delay(100);
}
