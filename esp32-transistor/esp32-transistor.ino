#define OUTPUT_PIN 13
#define FLASH_PIN 4
#define INPUT_PIN 12

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode(INPUT_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(FLASH_PIN, OUTPUT);

  digitalWrite(FLASH_PIN, HIGH);
  delay(500);
  digitalWrite(FLASH_PIN, LOW);
}

void loop() {
  if (digitalRead(INPUT_PIN) == HIGH) {
    Serial.println("HIGH");
    digitalWrite(OUTPUT_PIN, HIGH);
    digitalWrite(FLASH_PIN, HIGH);
  } else {
    Serial.println("LOW");
    digitalWrite(OUTPUT_PIN, LOW);
    digitalWrite(FLASH_PIN, LOW);
  }
}
