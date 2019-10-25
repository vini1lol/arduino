
int lr1 = A2;
int lr2 = A1;
int pot = A4;
int a[100][4];
int aux = 0;
int but = 5;
int but2 =12;
int caixa1 = 6;
int caixa2 = 9;
void setup() {
  pinMode(but, INPUT_PULLUP); 
    pinMode(but2, INPUT_PULLUP); 
  pinMode(lr1, INPUT);
  pinMode(lr2, INPUT);
  pinMode(pot, INPUT);
  pinMode(caixa1, OUTPUT);
  pinMode(caixa2, OUTPUT);
  Serial.begin(9600);
}
int luz1, luz2, p, estado = 0,est=0;
unsigned int ton;
int estadoluz1 = 0, estadoluz2 = 0;
unsigned int tNota1, tNota2;
unsigned int tPausa =0;
int estadoP = 0;
void loop() {
  p = analogRead(pot);
  p = map(p, 0, 1010, 0, 8);
  //  Serial.print("pot = ");
  //  Serial.println(p);
  luz1 = analogRead(lr1);
  //    Serial.print("SEM ATT luz 1 =");
   //  Serial.println(luz1);
  if (luz1 < 28) {
    ton = 44;
    //    digitalWrite(L1, HIGH);
    tone(caixa1, ton * pow(2, p));
    estadoluz1 = 1;
    if (butL()) {
      tNota1 = millis();
      if(estadoP==0){
        estadoP=1;
        tPausa = millis() - tPausa;
        }
    }
    //      Serial.println(ton*pow(2,p));
  } else if (estadoluz1 == 1) {
    //    digitalWrite(L1, LOW);
    noTone(caixa1);
    estadoluz1 = 0;
    if (butL()) {
      tNota1 = millis() - tNota1;
      gravar(caixa1,44* pow(2, p),tNota1,tPausa);
      if(estadoP ==1){
        estadoP=0;
        tPausa = millis();
        }
    }
  }
  luz2 = analogRead(lr2);
  //    Serial.print("SEM ATT luz 2 =");
   // Serial.println(luz2);
  if (luz2 < 65) {
    ton = 62;
    //    digitalWrite(L2, HIGH);
    tone(caixa2, ton * pow(2, p));
    //      Serial.print("2=");
    //      Serial.println(ton*pow(2,p));
    estadoluz2 = 1;
    if (butL()) {
      tNota2 = millis();
      if(estadoP==0){
        estadoP=1;
        tPausa = millis() - tPausa;
        }
    }
  } else if (estadoluz2 == 1) {
    //    digitalWrite(L2, LOW);
    noTone(caixa2);
    estadoluz2 = 0;
    if (butL()) {
      tNota2 = millis() - tNota1;
      gravar(caixa2,62* pow(2, p),tNota2,tPausa);
      if(estadoP ==1){
        estadoP=0;
        tPausa = millis();
        }
    }
  }
  if(butS()){
    soltGrav();
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
bool butS() {
  if (est == 0 && !digitalRead(but2)) {
    delay(200);
    est = 1;
  }
  if (est == 1 && digitalRead(but2)) {
    est = 2;
    return true;
  }
  if (est == 2 && !digitalRead(but2)) {
    delay(200);
    est = 3;
  }
  if (est == 3 && digitalRead(but2)) {
    est = 0;
    return false;
  }
}
void gravar(int porta, unsigned int fre, unsigned int timerNota, unsigned int timerP ) {
  a[aux][0] = porta;
  a[aux][1] = fre;
  a[aux][2] = timerNota;
  a[aux][3] = timerP;
  aux++;
Serial.println("gravou");
}
void soltGrav(){
  for(int i=0;i<aux;i++){
  tone(a[i][0] ,a[i][1],  a[i][2] );
  delay(a[i][3]);
  }
  }
