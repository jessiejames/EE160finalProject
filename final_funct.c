/*      File : final.h          						*
 *      team : jenga            						*
 *      Date : 04.27.2015								*
 *		Team Members: Jessica G., Estevan B., Geena W.  */

// checks the range going clockwise and counter clockwise
int checkRange (int dir, uint16_t loc, int but) { 
  int condition;
  // if direction is pos: then button is greater or equal to the location -2 and location +2, else it is not.
  if (dir == 1) {
     if (but >= loc - 2 && but <= loc + 2)
       condition = TRUE;
     else
       condition = FALSE; 
  }
  // if direction is neg: then button is less than or equal to the location -2 and location +2, else it is not.
  if (dir == -1){
    if (but <= loc + 2 && but >= loc - 2)
      condition = TRUE;
    else
      condition = FALSE;
  }
return condition; //returns true or false
}
// function for a rainbow on the led strip that is stationary with a white led passing thru each location
void rainbowBackground(uint8_t wait, uint16_t loc) {
  uint16_t i, j;
  for(i=0; i< 75; i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
  strip.setPixelColor(loc % strip.numPixels() , strip.Color(255 , 255, 255));
  strip.show();
  delay(wait);  
}
// function for the color wheel
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85)
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
} 
// function for determing the winner of each round
int winner(int pts1, int pts2, int lvl) {
  if (pts1 > lvl)
    return pts1;
  if (pts2 > lvl)
    return pts2;
  else
    return 0;
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++)
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3)
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        strip.show();
        delay(wait);
        for (int i=0; i < strip.numPixels(); i=i+3)
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3)
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      strip.show();
      delay(wait);
      for (int i=0; i < strip.numPixels(); i=i+3)
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
    }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}