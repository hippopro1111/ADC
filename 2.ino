const int pinLM35 = 34;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int valorLM35 = analogRead(pinLM35);

  float voltatge = (valorLM35 / 4095.0) * 3.3;
  float temperatura = voltatge * 100.0;

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");

  delay(2000);
}
