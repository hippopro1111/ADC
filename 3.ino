const int pinLDR = 34;
const int pinLM35 = 35;
const int pinLED = 2;

const float tempLimit = 25.0;
const int ldrLimit = 1500;

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
}

void loop() {
  int valorLDR = analogRead(pinLDR);
  int valorLM35 = analogRead(pinLM35);

  float voltatge = (valorLM35 / 4095.0) * 3.3;
  float temperatura = voltatge * 100.0;

  bool alertaTemp = temperatura > tempLimit;
  bool alertaLlum = valorLDR > ldrLimit;

  if (alertaTemp || alertaLlum) {
    digitalWrite(pinLED, HIGH);
  } else {
    digitalWrite(pinLED, LOW);
  }

  if (alertaTemp) {
    Serial.println("ALERTA: Sobreescalfament al CPD");
  }

  if (alertaLlum) {
    Serial.println("AVIS: Porta oberta o llum encesa");
  }

  delay(2000);
}
