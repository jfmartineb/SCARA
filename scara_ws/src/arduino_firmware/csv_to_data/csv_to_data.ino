String inputString = "1,2,3,4,5,6,7,8"; 
char inputBuffer[256];

int inputInt;

void setup() {
  Serial.begin(115200);
}

void loop() {

  inputString = "1,2,3,4,5,6,7,8"; 
  inputString.toCharArray(inputBuffer,inputString.length()+1);
  Serial.println(inputBuffer);
  

  inputString = "1,2,3,4,5,6,7";
  inputString.toCharArray(inputBuffer,inputString.length()+1);
  char * partOfString;
  partOfString = strtok (inputBuffer,","); 
  inputInt = atoi(partOfString);     
  Serial.println(inputInt);
  partOfString = strtok (NULL,","); 
  inputInt = atoi(partOfString);     
  Serial.println(inputInt);
  partOfString = strtok (NULL,","); 
  inputInt = atoi(partOfString);     
  Serial.println(inputInt);
  partOfString = strtok (NULL,","); 
  inputInt = atoi(partOfString);     
  Serial.println(inputInt);
  partOfString = strtok (NULL,","); 
  inputInt = atoi(partOfString);     
  Serial.println(inputInt);
  partOfString = strtok (NULL,","); 
  inputInt = atoi(partOfString);     
  Serial.println(inputInt);
  partOfString = strtok (NULL,","); 
  inputInt = atoi(partOfString);     
  Serial.println(inputInt);
  partOfString = strtok (NULL,","); 
  inputInt = atoi(partOfString);     
  Serial.println(inputInt);
}
