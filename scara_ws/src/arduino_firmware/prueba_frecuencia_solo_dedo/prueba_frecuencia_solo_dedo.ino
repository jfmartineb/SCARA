#define DedoPulso  34
#define DedoDirec  35
#define DedoSensor 16

volatile unsigned int DedoCount     = 0;
volatile unsigned int DedoPeriod    = 1;
volatile long         DedoPosition  = 0;
volatile bool         DedoOut       = false;
volatile bool         DedoDir       = false;

void setup_timer2() { //set timer2 interrupt at 1kHz
  cli();

  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 1khz increments
  //OCR2A = 249;// = (16e6) / (1000*64) - 1 (must be <256)
  OCR2A = 159;// = (16e6) / (250*256) - 1 (must be <256)
  //OCR2A = 155;// = (16e6) / (100*1024) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Prescalers https://microcontrollerslab.com/arduino-timer-interrupts-tutorial/
  // CS = 001 for 1
  // CS = 010 for 8
  // CS = 011 for 32
  // CS = 100 for 64
  // CS = 101 for 128
  // CS = 110 for 256
  // CS = 111 for 1024
  //TCCR2B |= (1 << CS22);
  //TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS20);
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei();//allow interrupts
}
ISR(TIMER2_COMPA_vect) {
  timed_loop();
}
void timed_loop() {
  DedoCount++;
  if (DedoCount >= DedoPeriod && DedoPeriod > 0) {
    DedoOut = !DedoOut;
    DedoCount = 0;
    digitalWrite(DedoDirec, !DedoDir);
    digitalWrite(DedoPulso, DedoOut);
    DedoPosition = DedoPosition + DedoDir * 1 - !DedoDir * 1;
  }
}
void setup_robot() {
  pinMode(DedoSensor, INPUT);
  pinMode(DedoPulso, OUTPUT);
  pinMode(DedoDirec, OUTPUT);

  while (!digitalRead(DedoSensor)) {}
  DedoPosition = 0;
  DedoPeriod = 0;
}

void setup() {
  setup_timer2();
  setup_robot();
  Serial.begin(115200);
}

void loop() {
}
