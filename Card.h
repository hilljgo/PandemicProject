#include <iostream>
#include <string>
using namespace std;


//For player deck, make array with one card for each city, (4,5,or6) epidemic cards, and 5 special event cards
	//For now we can leave special event cards out and add them in later
//For infection deck, make array with one card for each city

class Card	
{	
public:
	string name;	//Name of City or event or "Epidemic"
	int color;		//0-Epidemic, 1-Blue, 2-Yellow, 3-Black, 4-Red, 5-special event; 
	int status;		//Deck, Hand, Discard
}