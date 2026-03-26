const int pinLDR = 2;
const int pinLM35 = 34;
const int pinLED = 14;

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);

  Serial.println("Comandes: STATUS, LED_OFF, LED_ON");
}

void loop() {
  int valorLDR = analogRead(pinLDR);
  int valorLM35 = analogRead(pinLM35);

  float voltatge = (valorLM35 / 4095.0) * 3.3;
  float temperatura = voltatge * 100.0;

  if (Serial.available()) {
    String comanda = Serial.readStringUntil('\n');
    comanda.trim();
    comanda.toUpperCase();

    if (comanda == "STATUS") {
      Serial.println("=== ESTAT DEL SISTEMA ===");
      Serial.print("LDR: ");
      Serial.println(valorLDR);
      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" C");
      Serial.print("LED: ");
      Serial.println(digitalRead(pinLED) ? "ENCES" : "APAGAT");
    }
    else if (comanda == "LED_OFF") {
      digitalWrite(pinLED, LOW);
      Serial.println("LED apagat");
    }
    else if (comanda == "LED_ON") {
      digitalWrite(pinLED, HIGH);
      Serial.println("LED encès");
    }
    else {
      Serial.println("Comanda no reconeguda");
    }
  }

  delay(500);
}
