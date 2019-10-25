int but = 7;
int re1 = 8;
int re2 = 9;
void setup() {
  pinMode(but, INPUT_PULLUP);
  pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(re1, HIGH);
  digitalWrite(re2,HIGH);
}
int estado = 0;
void loop() {
  if (digitalRead(but) == 0 && estado == 0) {
    digitalWrite(re1, LOW);
    digitalWrite(re2, HIGH);
    delay(200);
    Serial.println("on");
    estado = 1;
  }
  if (digitalRead(but) == 1 && estado == 1) {
    estado = 2;
  }
  if (digitalRead(but) == 0 && estado == 2) {
    digitalWrite(re1, HIGH);
    digitalWrite(re2, HIGH);
    delay(200);
    estado = 3;
  }
  if (digitalRead(but) == 1 && estado == 3) {
    estado = 4;
  }
  if (digitalRead(but) == 0 && estado == 4) {
    digitalWrite(re1, HIGH);
    digitalWrite(re2, LOW);
    delay(200);
    estado = 5;
  }
  if (digitalRead(but) == 1 && estado == 5) {
    estado = 6;
  }
  if (digitalRead(but) == 0 && estado == 6) {
    digitalWrite(re1, HIGH);
    digitalWrite(re2, HIGH);
    delay(200);
    estado = 7;
  }
  if (digitalRead(but) == 1 && estado == 7) {
    estado = 0;
  }
}
