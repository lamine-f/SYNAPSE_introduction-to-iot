#define SENSOR_PIN 8       
#define RELAY_PIN 7        

int clapCount = 0;         
unsigned long clapStartTime = 0;   
unsigned long lastClapTime = 0;    
bool lightsOn = false;             

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(13, OUTPUT);         
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
  int sensorStatus = digitalRead(SENSOR_PIN);

    Serial.println(sensorStatus);

  if (sensorStatus == 0) {
    if (clapCount == 0) {
      clapStartTime = lastClapTime = millis();
      clapCount++;
    } else if (millis() - lastClapTime >= 50) {
      lastClapTime = millis();
      clapCount++;
    }
  }

  if (millis() - clapStartTime >= 400) {
    if (clapCount == 2) { 
      lightsOn = !lightsOn;
      digitalWrite(13, lightsOn ? HIGH : LOW);
      digitalWrite(RELAY_PIN, lightsOn ? LOW : HIGH);
    }
    clapCount = 0;
  }
}
