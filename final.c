/*      File : final.h          						*
 *      team : jenga            						*
 *      Date : 04.27.2015								*
 *		Team Members: Jessica G., Estevan B., Geena W.  */

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include "final_funct.c"
#include "final.h"

#define TRUE 1
#define FALSE 0

#define PIN 6
// light location
// contsant
const int player1_button = 2;  // push button connected to dgital pin 2
const int player2_button = 3;  // push button connected to digital pin 3
const int led_neopix =  6;     // neopixel led strip connected to digital pin 6 

//changing variables
int buttonState1 = 0;   	// current state of button1
int buttonState2 = 0;   	// current state of button2
int button1Loc = 17;		// button location 1 
int button2Loc = 55;		// button location 2 
float faster = 150;			// speed at which light moves
int lightRangeForward = 0;	// range of light going forward 
int lightRangeBack = 0;		// range of light going backwards
uint16_t ledlocation = 0;   // name of each led on strip starting from 0 to 74
int score1 = 0;				// player 1 score
int score2 = 0;				// player 2 score
int finalScore = 0;			// final score
int level = 4;				// levels of game
int score1sum = 0;			// sum of player 1 score
int score2sum = 0; 			// sum of player 2 score

Adafruit_NeoPixel strip = Adafruit_NeoPixel(75, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //opens serial monitor on arduino (prints)
  Serial.begin(9600);
  Serial.println("SMACKDOWN CHALLENGE");
  Serial.println("Level 1: First player to 5 points WINS!"); 
  strip.begin();
  // initialize all pixels to 'off'
  strip.show();	
  // sets digital pin as output
  pinMode(led_neopix, OUTPUT);      
  // sets digital pin as input
  pinMode(player1_button, INPUT); 
  pinMode(player2_button, INPUT);
 } 
void loop() {
  // loop for leds
  while(ledlocation <= 74 && ledlocation >= 0) {
  	// function for background 
    rainbowBackground(faster, ledlocation);
    //reads button input
    buttonState1 = digitalRead(player1_button); 
    buttonState2 = digitalRead(player2_button);
    // *********
    // Player 1
    // *********
    // when button 1 is pushed and the range is checked
	if (buttonState1 == HIGH && checkRange(direct, ledlocation, button1Loc) == TRUE) {
      delay(1000);
  	  // direction of led from forward to backward
  	  direct = direct * -1;
  	  // move white led faster around strip
      faster = faster * .99;
      // player 1 led location to hit a button to score 1
      if(button1Loc == ledlocation) {
        score1 = score1 + 1;
        Serial.print("Hulk Hogan score = ");
        Serial.println(score1);  
      }
      // if player one doesnt hit the right location subtract a point
      else {
        score1 = score1 -1;
        if (score1 < 0) {
          score1 = 0;
        }
        Serial.print("Hulk Hogan score = ");
        Serial.println(score1); 
      }  
     }
	// *********
    // Player 2
    // *********
    // when button 2 is pushed and the range is checked
    if (buttonState2 == HIGH && checkRange(direct, ledlocation, button2Loc) == TRUE) {
      delay(1000);
      // direction of led from forward to backward
      direct = direct * -1;
      // move white led faster around strip
      faster = faster * .999;
      // player 2 led location to hit a button to score 1
      if (button2Loc == ledlocation) {
        score2 = score2 + 1;
        Serial.print("The Rock score = ");
        Serial.println(score2); 
      }
      // if player one doesnt hit the right location subtract a point
      else {
        score2 = score2 -1;
        if (score2 < 0) {
          score2 = 0;
        }
          Serial.print("The Rock score = ");
          Serial.println(score2); 
       } 
     }
     // loop for determining winner
     if (finalScore = winner(score1, score2, level) > 0) {
       Serial.println("We have a WINNER!"); 
       // loop player1 score
       if (score1> score2) {
         Serial.println("HULK HOGAN WINS THIS ROUND!");
         colorWipe(strip.Color( 0, 255, 0), 30); // Green
         score1sum = score1sum + 1; 
       }
       // loop player2 score
       if (score2 > score1) {
         Serial.println("THE ROCK WINS THIS ROUND!");
         colorWipe(strip.Color(  0,   0, 255), 30); // Blue
         score2sum = score2sum + 1;
       }
       // determines which player wins
       if(score1sum - score2sum > 2) {
         Serial.println("Winner by a Unanimous Decision: HULK HOGAN!!");
         colorWipe(strip.Color( 0, 255, 0), 30); // Green
         Serial.println("Open new Serial Monitor to start a NEW GAME");
         break;
       }
       // determines which player wins
       if(score2sum - score1sum > 2) {
         Serial.println("Winner by a Unanimous Decision: THE ROCK!!");
         colorWipe(strip.Color(  0,   0, 255), 30); // Blue
         Serial.println("Open new Serial Monitor to start a NEW GAME");
         break;
       }
       // lights when next level
       theaterChase(strip.Color(127, 127, 127), 10); // White
       rainbowCycle(.05);
       theaterChaseRainbow(1); 
       score1 = 0; 
       score2 = 0;
       level = level - 1; 
       // loop for each level 
       if (level == 3)
         Serial.println("ENTERING LEVEL 2: First Player to 4 WINS!");
       if (level == 2)
         Serial.println("ENTERING LEVEL 3: First Player to 3 WINS!");
       if (level == 1)
         Serial.println("ENTERING LEVEL 4: First Player to 2 WINS!");
       if (level == 0)
         Serial.println("ENTERING THE ULTIMATE CHAMPIONSHIP!!: First Player to 1 WINS!");
       // player 1 score
       if (score1 > score2 && score1sum > score2sum) {
         Serial.println("We have a CHAMPION!");
         Serial.println("HULK HOGAN WINS THE GAME!");
         Serial.println("Open new Serial Monitor to start a NEW GAME");
       }
       // player 2 score
       if (score2 > score1 && score2sum > score1sum) {
         Serial.println("We have a CHAMPION!");
         Serial.println("THE ROCK WINS THE GAME!");
         Serial.println("Open new Serial Monitor to start a NEW GAME");
       }
      }
     }
	 ledlocation = ledlocation + (1 * direct);
	 // if light moves faster than 5 then the game is over
     if (faster < 5) { 
       Serial.println("TIME IS UP. GAME OVER!!");
       Serial.println("Open new Serial Monitor to start over");
       colorWipe(strip.Color(255, 0, 0), 50); // Red
       break; 
     }
    }
    // direction and location of led
    if (direct == -1) {
      ledlocation = 74;
      lightRangeBack = 0;
    }
    else {
      ledlocation = 0;
      lightRangeBack = 0; 
    }
}