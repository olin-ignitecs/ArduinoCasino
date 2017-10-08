/*
  Example program game of chance
  12/03/2016
  Author: Cassandra Overney
*/

byte before_button = 1;
byte previous = 0;

// assign pin 12 to button
const byte buttonPin = 12;

// stores randum number
long randomNumber = 2;

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin 12 as input
  pinMode(buttonPin, INPUT);

  // set baud rate for serial communication
  Serial.begin(9600);

  // let's make it more random
  randomSeed(42);

  // initialize digital pin 2 to 11 as output
  for (int i = 2; i < 12; i++)
    pinMode(i, OUTPUT);
}

// the loop function runs over and over again forever
void loop()
{
  if (before_button == 1)      // check if button not pressed yet
  {
    digitalWrite(randomNumber, LOW);    // turn the LED off by making the voltage LOW
    //generate a random number
    randomNumber = random(2, 12);
    digitalWrite(randomNumber, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println(randomNumber);       // print value of randomNumber to serial port
    delay(50);                          //delay the lights so they look better
  }


  if (digitalRead(buttonPin) == HIGH)     // check if button is pressed
  {
    before_button = 0;                    //button pressed so no more moving lights
    digitalWrite(randomNumber, LOW);      // turn the LED off by making the voltage LOW
    //generate a random number
    randomNumber = random(2,12);
    if (randomNumber == 11){              //if blue light turn on, then previous variable set
      previous = 1;
      digitalWrite(randomNumber, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.println(randomNumber);       // print value of randomNumber to serial port
      delay(1000);
    }
    else{
      digitalWrite(randomNumber, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.println(randomNumber);       // print value of randomNumber to serial port
      delay(1500);
      before_button = 1;                  // back to shining lights
    }
    
  }

  if (previous == 1){                   // if blue was selected the first time, player gets a second chance
    digitalWrite(randomNumber, LOW);    // turn the LED off by making the voltage LOW
    //generate a random number
    randomNumber = random(2,12);
    if (randomNumber == 11){            // if a second blue occurs then turn it to white
      randomNumber = 2;   
    }
    digitalWrite(randomNumber, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1500);
    previous = 0;                       //previous goes back to 0
    before_button = 1;                  // back to shining lights
  }
}

