#ifndef GAMELOGICS_H
#define GAMELOGICS_H
/*
 * MAIN LOOPS
 * 
 * state of the game before starting
 */
void standby();

/*
 * core of the game
 */
void gameloop();

/*
 * specifies some parameters at the start of each new round
 */
void initRound();

/*
 * INTERRUPT HANDLERS
 * 
 * called when MiniTimer1's timer is up
 * 
 * This function is called twice because MiniTimer1 can count up 
 * to 4 seconds and this game needs 8 seconds
 * 
 */
void timeUpRoutine();

/**
 * called by MiniTimer1 or if the player presses the down button
 * too many times
 */
void gameover();

/**
 * this function sets the flag 'playing' to true
 * called by the button start
 */
void startGame();

/*
 * 
 * this function is called when button down is
 * pressed
  */
void down();

/*
 * GAME UTILITIES
 * 
 * reads from the potentiometer and sets the difficulty (1-8)
*/
void readDifficulty();

/*
 * resets the parameter in order to start new game
 */
void reset();









#endif
