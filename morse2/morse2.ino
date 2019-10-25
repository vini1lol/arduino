int led =13;
unsigned long timera=0,timere=0,timeri=0,timero=0,timeru=0;
String texto;
bool stringcompleta = false;
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}
char letra='0';
int estado = 0,j=0;
void loop() {
  if(stringcompleta){
      letra=texto[j];
      stringcompleta = false;
  }
  /*letra a 1*/
  if(letra=='a' && estado== 0){
    timera=millis();
    digitalWrite(led,HIGH);
   estado=11;
  }
  if(millis()-timera==100){
    digitalWrite(led,LOW);
  }
  if(millis()-timera==200){
    digitalWrite(led,HIGH);
  }
  if(millis()-timera==500){
    digitalWrite(led,LOW);
    estado=0;
    delay(500);
    j++;
    letra = texto[j];
  }
  /*letra e 2*/
  if(letra=='e' && estado==0){
    timere=millis();
    digitalWrite(led,HIGH);
    estado=21;
  }
  if(millis()-timere==100){
    digitalWrite(led,LOW);
    estado=0;
    delay(500);
    j++;
    letra = texto[j];
  }
  /*letra i 3*/
  if(letra=='i' && estado==0){
    timeri=millis();
    digitalWrite(led,HIGH);
    estado=30;
  }
  if(millis()-timeri==100){
    digitalWrite(led,LOW);
  }
  if(millis()-timeri==200){
    digitalWrite(led,HIGH);
  }
  if(millis()-timeri==300){
    digitalWrite(led,LOW);
    estado=0;
    delay(500);
    j++;
    letra = texto[j];
  }
  /*letra o 4*/
  if(letra=='o' && estado==0){
    timero=millis();
    digitalWrite(led,HIGH);
    estado=41;
  }
  if(millis()-timero==300){
    digitalWrite(led,LOW);
  }
  if(millis()-timero==400){
    digitalWrite(led,HIGH);
  }
  if(millis()-timero==700){
    digitalWrite(led,LOW);
  }
  if(millis()-timero==800){
    digitalWrite(led,HIGH);
  }
  if(millis()-timero==1100){
    digitalWrite(led,LOW);
    estado=0;
    delay(500);
    j++;
    letra = texto[j];
  }
  /*letra u 5*/
  if(letra=='u' && estado==0){
    timeru=millis();
    digitalWrite(led,HIGH);
   estado=51;
  }
  if(millis()-timeru==100 && estado==51){
    digitalWrite(led,LOW);
    estado=52;
  }
  if(millis()-timeru==200 && estado==52){
    digitalWrite(led,HIGH);
    estado=53;
  }
  if(millis()-timeru==300 && estado==53){
    digitalWrite(led,LOW);
    estado=54;
  }
  if(millis()-timeru==400 && estado==54){
    digitalWrite(led,HIGH);
    estado=55;
  }
  if(millis()-timeru==700 && estado ==55){
    digitalWrite(led,LOW);
    estado=0;
    delay(500);
    j++;
    letra = texto[j];
    Serial.println(letra);
  }
  if(letra=='\n'){
    texto = ' ';
    letra = ' ';
    j=1;
  }
}
void serialEvent() {
  char inChar;
  while (Serial.available()>0) {
    // get the new byte:
    if(estado==0){
      inChar = (char)Serial.read(); 
      // add it to the inputString:
      texto += inChar;
      delay(10);
    }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringcompleta = true;
    } 
  }
}
