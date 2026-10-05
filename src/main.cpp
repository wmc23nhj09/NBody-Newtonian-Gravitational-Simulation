/* 
Nearly 2 years ago, I started a file name called 'New Beginnings'.A program designed to run real newtonian gravitational interactions.
I would like to blame having made it in python that was the reason of its short coming, as that was my main langauage at the time, but I have to admit, it was all me.
My model was not scientifically accurate, and instead, I even altered key values like G, to much larger exponents just to get a valid response, and I remember multiplying distance^2 by 20, for whatever reason.

Outside of its numerical instability, which saw planets flinging away god knows where, a spark was made to create simulations, and every since, I've gotten pretty far. This is my 2nd Nbody sim in C++, made to rival 'New Beginnings'.
It's designed to be as physically accurate as possible, but it's always nice to reminise about it. Thanks to me a year ago, who made a physics simulation so bad, even my computer had to pause and stare.

William Campbell - Author of Program - 11:26 04/10/26
*/

#include "game.h"

int main() {
	Game game;

	game.run();
}