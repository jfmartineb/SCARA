void setup() {
  Serial.begin(115200);
  Serial.println("0,0,0,0");
}

void loop() {
  if (Serial.available() > 0) {
    Serial.write(Serial.read());
  }
}
