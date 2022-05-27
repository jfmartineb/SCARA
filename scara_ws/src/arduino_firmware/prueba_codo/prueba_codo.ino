#define HPulso  30
#define HDir    31
#define HSensor 17
#define HPeriod 200

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
  cont = 19000;
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
  
  
  if(cont<=-2000){ref= 2000;}
  if(cont>= 2000){ref=-2000;}

  //Serial.println(cont);
}
