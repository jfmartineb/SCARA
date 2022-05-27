 //int potenciometro =A2;
//int valorPot = 0;
const int Pul_hombro = 7;
const int Dir_hombro = 8;
const int Pul_codo = 30;
const int Dir_codo = 31;
const int Pul_muneca = 32;
const int Dir_muneca = 33;
const int Pul_dedo = 34;
const int Dir_dedo = 35;
const int Pul_paso = 15;
const int Dir_paso = 14;

int rele = 22; //Pin rele electrovalvula

int cont = 0;

void setup() {
  pinMode(rele, OUTPUT);

  pinMode(Dir_hombro, OUTPUT);
  pinMode(Pul_hombro, OUTPUT);
  pinMode(Dir_codo, OUTPUT);
  pinMode(Pul_codo, OUTPUT);
  pinMode(Dir_muneca, OUTPUT);
  pinMode(Pul_muneca, OUTPUT);
  pinMode(Dir_dedo, OUTPUT);
  pinMode(Pul_dedo, OUTPUT);
  pinMode(Dir_paso, OUTPUT);
  pinMode(Pul_paso, OUTPUT);
  digitalWrite(Dir_hombro, LOW);
  digitalWrite(Pul_hombro, LOW);
  digitalWrite(Dir_codo, LOW);
  digitalWrite(Pul_codo, LOW);
  digitalWrite(Dir_muneca, LOW);
  digitalWrite(Pul_muneca, LOW);
  digitalWrite(Dir_dedo, LOW);
  digitalWrite(Pul_dedo, LOW);
  digitalWrite(Dir_paso, LOW);
  digitalWrite(Pul_paso, LOW);
}
void loop() {
  if (cont < 10000)
  {
    Serial.println("Menor");
    digitalWrite(rele, HIGH);

    digitalWrite(Dir_hombro, HIGH);
    digitalWrite(Dir_codo, HIGH);
    digitalWrite(Dir_muneca, HIGH);
    digitalWrite(Dir_dedo, HIGH);
    digitalWrite(Dir_paso, HIGH);
  }
  if (cont == 10000)
  {
    delay(2000);
  }
  if (cont > 10000)
  {
    digitalWrite(rele, LOW);

    digitalWrite(Dir_hombro, LOW);
    digitalWrite(Dir_codo, LOW);
    digitalWrite(Dir_muneca, LOW);
    digitalWrite(Dir_dedo, LOW);
    digitalWrite(Dir_paso, LOW);
  }
  digitalWrite(Pul_hombro, HIGH);
  digitalWrite(Pul_codo, HIGH);
  digitalWrite(Pul_muneca, HIGH);
  digitalWrite(Pul_dedo, HIGH);
  digitalWrite(Pul_paso, HIGH);
  delayMicroseconds(200);
  digitalWrite(Pul_hombro, LOW);
  digitalWrite(Pul_codo, LOW);
  digitalWrite(Pul_muneca, LOW);
  digitalWrite(Pul_dedo, LOW);
  digitalWrite(Pul_paso, LOW);
  delayMicroseconds(200);
  cont++;
  if (cont == 20000)
  {
    cont = 0;
    delay(2000);
  }
}

