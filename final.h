/*      File : final.h          						*
 *      team : jenga            						*
 *      Date : 04.27.2015								*
 *		Team Members: Jessica G., Estevan B., Geena W.  */

//Function Prototypes

int checkRange (int dir, uint16_t loc, int but);
	// function for checking the range of the location to hit when white led moves clockwise or counter clockwise
void rainbowBackground(uint8_t wait, uint8_t loc);
	// function for a rainbow on the led strip that is stationary with a white led passing thru each location
int winner(int pts1, int pts2);
	// function for determing the winner of each round