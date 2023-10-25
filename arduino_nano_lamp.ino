// THIS IS ARDUINO CODE FOR 2 LED , VARIABLE BRIGHTNESS THROUGH SINGLE TOUCH BUTTON
// FOR THIS WE NEEW MULTIPLE VARIABLES 



const int sensorPin = A0; // analog pin for touch sensor since it always output 
const int led1Pin = 6; 
const int led2Pin = 5; 

int sensorValue = 0; 
int led1State = 1;   
int led2State = 1;  

 int intensity = 100;
int reading = 0;

unsigned long Time = 0;  // the last time the output pin was toggled
unsigned long Time1 = 0; 
unsigned long debounceDelay = 50; 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);// initialise the serial comunication 
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);  
  pinMode(sensorPin,INPUT);// sensor pin as input 
 
  digitalWrite(led1Pin, LOW); // set initial LED state
  digitalWrite(led2Pin, LOW); // set initial LED state
}

void loop() {
  // put your main code here, to run repeatedly:

  sensorValue = analogRead(sensorPin);// read the analog values of the sensor 

 if (sensorValue > 900) {
           reading = 1;
          }else{
            reading = 0; // do this when lifted from the sensor 
            
            if(Time1 > 20 && Time1 < 200){// condition for touch for small time
              
                 if(led1State == 0){// 4 states in total
              led1State = 1;
              intensity = 100;
                  }else if(led1State == 1){
              led1State = 2;
              
                  }else if(led1State == 2){
              led1State = 3;
              
             }else{
              led1State = 0;
             }
             
            }else if(Time1 > 500 ){// change state if touch for longer time 
              
               if(led2State == 0){// 2 states in total
              led2State = 1;
              
                  }else{
              led2State = 0;
            }
             
            }

            if(intensity >= 250){    // add and remove values from intensity if they are greater or less than the range 
              intensity = intensity - 2;
            }else if(intensity <= 4){
              intensity = intensity + 2;
            }
             Time = millis(); // assign time to millis 
             
             Time1 = 0;// reset time1 to 0 it is not needed but ok
          }

    
    while (reading == 1) { // do this olny while reading is 1 i.e touched 
     
    
     Time1 = millis() - Time; // calculate the time for which sensor is touched 
       
    while(Time1 > 500){  // do this while long touch 
      if(intensity < 250 && intensity > 4){
            if( led2State == 1){ // increase or decrease the intensity 
                intensity++;
            }else{
              intensity--;
            }
      }
         
      
      
    
      
      break;
    }
    Serial.print(Time1);
    Serial.print("= =="); //display touch and time 
    Serial.print(led1State);
    Serial.print("===");
     Serial.print(led2State);
    Serial.print("===");
    Serial.println(intensity);
    
    break;  
    
          }

setleds();  // set leds accourding to code 


}

void setleds(){
  

      if(led1State == 0){// 3 states in total
              digitalWrite(led1Pin,LOW);
              digitalWrite(led2Pin,LOW);
           
            
                  }else if(led1State == 1){
              digitalWrite(led1Pin,LOW);
              analogWrite(led2Pin,intensity);
              
                  }else if(led1State == 2){
              analogWrite(led1Pin,intensity);
              digitalWrite(led2Pin,LOW);
              
                  }else if(led1State == 3){
            analogWrite(led1Pin,intensity);
              analogWrite(led2Pin,intensity);
              
                  }
              
             
}
