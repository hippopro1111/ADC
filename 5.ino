const int pinLDR = 34;
const int pinLM35 = 35;
const int pinLED = 2;

const float tempLimit = 25.0;
const int ldrLimit = 1500;

bool ledManual = false;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);

  Serial.println("=== Sistema de monitorització CPD ===");
  Serial.println("Comandes: STATUS, LED_ON, LED_OFF, AUTO");
}

void loop() {
  int valorLDR = analogRead(pinLDR);
  int valorLM35 = analogRead(pinLM35);

  float voltatge = (valorLM35 / 4095.0) * 3.3;
  float temperatura = voltatge * 100.0;

  bool alertaTemp = temperatura > tempLimit;
  bool alertaLlum = valorLDR > ldrLimit;

  Serial.print("LDR: ");
  Serial.println(valorLDR);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");

  if (alertaTemp) {
    Serial.println("ALERTA: Sobreescalfament al CPD");
  }

  if (alertaLlum) {
    Serial.println("AVIS: Porta oberta o llum encesa");
  }

  if (!ledManual) {
    ledState = alertaTemp || alertaLlum;
  }

  digitalWrite(pinLED, ledState);

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
      Serial.println(ledState ? "ENCES" : "APAGAT");
    }
    else if (comanda == "LED_ON") {
      ledManual = true;
      ledState = true;
      digitalWrite(pinLED, HIGH);
      Serial.println("LED encès manualment");
    }
    else if (comanda == "LED_OFF") {
      ledManual = true;
      ledState = false;
      digitalWrite(pinLED, LOW);
      Serial.println("LED apagat manualment");
    }
    else if (comanda == "AUTO") {
      ledManual = false;
      Serial.println("Mode automàtic activat");
    }
    else {
      Serial.println("Comanda no reconeguda");
    }
  }

  Serial.println("-------------------------");
  delay(2000);
}
