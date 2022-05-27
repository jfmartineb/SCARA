#define HPulso  34
#define HDir    35
#define HSensor 16
#define HPeriod 10

long cont = 0;
long ref = 40000;

void setup() {
  pinMode(HSensor,INPUT);
  pinMode(HPulso,OUTPUT);
  pinMode(HDir,OUTPUT);
  Serial.begin(9600);
  Serial.println("ON");
  digitalWrite(HDir,HIGH);
  while(!digitalRead(HSensor)){
    digitalWrite(HPulso,HIGH);
    delayMicroseconds(HPeriod);
    digitalWrite(HPulso,LOW);
    delayMicroseconds(HPeriod);
    }
  cont = 0;
}

void loop() {

  if(ref > cont){
    digitalWrite(HDir,LOW);
    digitalWrite(HPulso,HIGH);
    delayMicroseconds(HPeriod);
    digitalWrite(HPulso,LOW);
    delayMicroseconds(HPeriod);
    cont++;
    }
  else
    {
    digitalWrite(HDir,HIGH);
    digitalWrite(HPulso,HIGH);
    delayMicroseconds(HPeriod);
    digitalWrite(HPulso,LOW);
    delayMicroseconds(HPeriod);
    cont--;
    }
  
  
  if(cont<= 30000){ref= 50000;}
  if(cont>= 50000){ref= 30000;}

  //Serial.println(cont);
}
