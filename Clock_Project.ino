#include <Servo.h>

#include <time.h>

  Servo arrow;

  /*
   * THIS PROGRAM WILL SLOWLY ROTATE THE SERVO ACCORDING TO THE TIME IT IS GIVEN. THE FIRST THREE CONSTANT INTEGER- TYPE VARIABLES DETERMINE THE TIME TO START AT, AND EACH DAY, HOUR, MINUTE IS PASSED INTO THE 
   * CLOCK FUNCTION. 
   * 
   *  currentDay ---> 0 = SUNDAY    1 = MONDAY    2 = TUESDAY   3 = WEDNESDAY   4 = THURSDAY    5 = FRIDAY    6 = SATURDAY
   * 
   *  currentHour ---> CAN BE FROM 0 HOURS TO 23 HOURS    EX: 2pm IS currentHour = 13
   * 
   *  currentMinute ---> THIS WILL BE FROM 0 MINUTES TO 59 MINUTES, AND 60 MINUTES WILL ROUND TO 1 HOUR. IF THERE IS A TIME SUCH AS 2:13pm THEN THE currentMinute = 13 OR ANY TIME THAT HAS A REMAINDER OF MINUTES WILL BE ROUNDED
   *  TO THE NEXT HOUR AND THE PROGRAM WILL WAIT THE REMAINDER OF THE CURRENT HOUR TO SYNC ITSELF WITH THE APPROPRIATE TIME.
   *  
   *  NOTE: THE TIME PUT IN LIKE  WEDNESDAY 2:13 pm WOULD BE currentDay = 3   currentHour = 13    currentMintute = 13   , AND WHATEVER TIME PUT INTO THESE CONSTANTS, THAT WILL BE THE TIME YOU WILL PRESS THE BUTTON TO START THE CLOCK!
   *  SO IN ORDER FOR THE PROGRAM/CLOCK TO WORK APPROPRIATELY, YOU NEED TO SET A TIME A MINUTE OR MORE IN ADVANCE/AHEAD OF CURRENT TIME!
   *  
   *  LASTLY, ONCE PROGRAM IS UPLOADED TO ARDUINO AND THE CLOCK IS ON, THE LED WILL BLINK AS AN INDICATOR THE BUTTON CAN NOW BE PUSHED TO START THE CLOCK. DEPENDING ON WHAT THE ENTERED TIME IS AND WHEN THE BUTTON IS PRESSED
   *  WILL DETERMINE THE CLOCK'S PRECISION!
   */
  
  int degrees, subtractDegrees;

  const int currentDay = 0/*EDIT TO USE PROGRAM*/, currentHour = 0/*EDIT TO USE PROGRAM*/, currentMinute = 0/*EDIT TO USE PROGRAM*/;

  const int servoPin = 9, LEDPin = 4, buttonPin = 3;
  
  const int defaultDegrees = 180, degreesPerDay = 26, degreesPerHour = 1; 
  
  const int secondInMillis = 1000;
  
  int minutesDelay;

  volatile bool startClock = false;

  void ISR_continueProgram()
  {
       startClock = true;     
  }

  void setup() 
   {
     pinMode (LEDPin, OUTPUT);

    pinMode (buttonPin, INPUT_PULLUP);

    arrow.attach(servoPin);

    arrow.write(defaultDegrees); 
    
    attachInterrupt(digitalPinToInterrupt(buttonPin), ISR_continueProgram, CHANGE);

    interrupts();
    
    Serial.begin (9600);
   }

  void minuteOfDelay()
  {
    for (int sec = 0; sec < 60; sec++)
    {
        delay(secondInMillis);
    }
  }

  void delayInMinutes(int amountOfMinutes)
  {
     for (int min = 0; min < amountOfMinutes; min++)
     {
          minuteOfDelay();
     }
  }

  void hourOfDelay()
  {
      for (int _min = 0; _min < 60; _min++)
      {
          minuteOfDelay(); 
      }
  }

  void clock(int days, int hours, int minutes)
  {
         
  if (minutes != 0)
  {
     minutesDelay = 60 - minutes; 

     hours++;
  }

    for (int days_ = 0; days_ < days; days_++)
    {
        subtractDegrees = subtractDegrees + degreesPerDay;
    }
    
  for (int hours_ = 0; hours_ < hours; hours_++)
      {
          subtractDegrees =  subtractDegrees + degreesPerHour;
      }

      degrees = defaultDegrees - subtractDegrees;

      arrow.write(degrees);

      while(!startClock)
      {
       digitalWrite (4, HIGH);
       
       delay(500); 
       
       digitalWrite (4, LOW);
       
       delay(500);
      }

      delayInMinutes(minutesDelay);

    while(1)
    {
           for (NULL; days < 7; days++)
       {
          subtractDegrees++;
    
           for (NULL; hours < 24; hours++ )
            { 
               hourOfDelay();
            
               subtractDegrees++;

              degrees = defaultDegrees - subtractDegrees;

               arrow.write(degrees);
            }

             hours = 0;
       
             subtractDegrees++;
       }

       days = 0;

       subtractDegrees = 0;
    
       degrees = defaultDegrees;

       arrow.write(defaultDegrees);
       
    }
   
  }

  
  void loop() 
  {
    clock(currentDay, currentHour, currentMinute);
  }
  
