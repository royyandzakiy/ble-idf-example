#define LED_PIN 14

void ledOnOff();

void ledOnOff() {
    pinMode(LED_PIN, OUTPUT);
    
    digitalWrite(LED_PIN, HIGH);
    Serial.println("high");
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    Serial.println("low");
    delay(1000);
}