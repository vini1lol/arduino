int but = 7;
int r = 8;
int l = 9;
int en = 10;
int pot = A0;
int a,b;
void setup() {
  pinMode(but, INPUT_PULLUP);
  pinMode(r, OUTPUT);
  pinMode(l, OUTPUT);
  pinMode(en, OUTPUT);
  Serial.begin(9600);
}
int estado = 0;
void loop() {
  if (digitalRead(but) == 0 && estado == 0) {
    digitalWrite(r, HIGH);
    digitalWrite(l, LOW);
    delay(200);
    Serial.println("on");
    estado = 1;
  }
  if (digitalRead(but) == 1 && estado == 1) {
    estado = 2;
  }
  if (digitalRead(but) == 0 && estado == 2) {
    digitalWrite(r, LOW);
    digitalWrite(l, LOW);
    delay(200);
    estado = 3;
  }
  if (digitalRead(but) == 1 && estado == 3) {
    estado = 4;
  }
  if (digitalRead(but) == 0 && estado == 4) {
    digitalWrite(r, LOW);
    digitalWrite(l, HIGH);
    delay(200);
    estado = 5;
  }
  if (digitalRead(but) == 1 && estado == 5) {
    estado = 6;
  }
  if (digitalRead(but) == 0 && estado == 6) {
    digitalWrite(r, LOW);
    digitalWrite(l, LOW);
    delay(200);
    estado = 7;
  }
  if (digitalRead(but) == 1 && estado == 7) {
    estado = 0;
  }
  a = analogRead(pot);
  b=map(a,0,1023,0,255);
  analogWrite(en, b);
  Serial.println(b);
}
