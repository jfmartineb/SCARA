#define HPulso  7
#define HDir    8
#define HSensor 9
#define HPeriod 30

long cont = 0;
long ref = 0;

void setup() {
  pinMode(HSensor,INPUT);
  pinMode(HPulso,OUTPUT);
  pinMode(HDir,OUTPUT);
  Serial.begin(9600);
  Serial.println("ON");
  digitalWrite(HDir,LOW);
  while(!digitalRead(HSensor)){
    digitalWrite(HPulso,HIGH);
    delayMicroseconds(HPeriod);
    digitalWrite(HPulso,LOW);
    delayMicroseconds(HPeriod);
    }
  cont = 116611;
}

void loop() {

  if(ref < cont){
    digitalWrite(HDir,HIGH);
    digitalWrite(HPulso,HIGH);
    delayMicroseconds(HPeriod);
    digitalWrite(HPulso,LOW);
    delayMicroseconds(HPeriod);
    cont--;
    }
  else
    {
    digitalWrite(HDir,LOW);
    digitalWrite(HPulso,HIGH);
    delayMicroseconds(HPeriod);
    digitalWrite(HPulso,LOW);
    delayMicroseconds(HPeriod);
    cont++;
    }
  
  
  if(cont<=-20000){ref= 20000;}
  if(cont>= 20000){ref=-20000;}
}
