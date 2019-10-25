int but = 9;
int led = 13;
void setup() {
  pinMode(but, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
}
int estado = 0;
void loop() {
  if (butL()) {
    digitalWrite(led,LOW);
  } else {
    digitalWrite(led,HIGH);
  }

}

bool butL() {
  if (estado == 0 && !digitalRead(but)) {
    delay(200);
    estado = 1;
  }
  if (estado == 1 && digitalRead(but)) {
    estado = 2;
    return true;
  }
  if (estado == 2 && !digitalRead(but)) {
    delay(200);
    estado = 3;
  }
  if (estado == 3 && digitalRead(but)) {
    estado = 0;
    return false;
  }

}
