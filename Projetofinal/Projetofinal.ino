int L1 = 10;
int L2 = 8;
int lr1 = A2;
int lr2 = A1;
int pot = A4;
void setup() {
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(lr1, INPUT);
    pinMode(lr2, INPUT);
  pinMode(pot, INPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}
int luz1, luz2, p;
unsigned int ton;
void loop() {
  p = analogRead(pot);
  p = map(p, 0, 1010, 0, 8);
  //  Serial.print("pot = ");
  //  Serial.println(p);
    luz1 = analogRead(lr1);
//    Serial.print("SEM ATT luz 1 =");
//    Serial.println(luz1);
    if (luz1 > 960) {
      ton=44;
  //    digitalWrite(L1, HIGH);
      tone(6,ton*pow(2,p));
//      Serial.println(ton*pow(2,p));
    }else{
  //    digitalWrite(L1, LOW);
      noTone(6);
      }
      luz2 = analogRead(lr2);
//    Serial.print("SEM ATT luz 2 =");
//    Serial.println(luz2);
    if (luz2 > 900) {
      ton=62;
  //    digitalWrite(L2, HIGH);
      tone(6,ton*pow(2,p));
//      Serial.print("2=");
//      Serial.println(ton*pow(2,p));
    }else{
  //    digitalWrite(L2, LOW);
      noTone(6);
      }
  
}
