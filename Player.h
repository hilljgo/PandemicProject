#pragma once

#include <iostream>
#include <string>
#include "City.h"
#include "Card.h"
using namespace std;

class Player
{
public:
        int color;                                //Which role this player is
        int actions;                        //How many actions this player has left
        static const int maxActions = 4;
        Card hand[7];                        //Cards in this player's hand
        static const int maxHand = 7;
        City *currentCity;                //City this player is in

        //may add parameters for actions

        Player()
        {
                color = 0; //should be assigned randomly
                actions = 4;
                currentCity = NULL; //should be assigned to Atlanta via main
        }

        //moves player to connecting city
        void move()
        {
                //Always shown
        
                cout << "Available cities to drive/ferry to:\n";
                cout << "1. " << currentCity->connectOne->name << endl;
                if( currentCity->connectTwo )
                        cout << "2. " << currentCity->connectTwo->name << endl;
                if( currentCity->connectThree )
                        cout << "3. " << currentCity->connectThree->name << endl;
                if( currentCity->connectFour )
                        cout << "4. " << currentCity->connectFour->name << endl;
                if( currentCity->connectFive )
                        cout << "5. " << currentCity->connectFive->name << endl;
                int n;
                cout << "City number to move to\n";
                cin >> n;

				

                //Statements to make current city the appropriate city & decrease actions
                //0 should go back to initial player action menu without decreasing
				
				if(n == 0)

				if(n == 1)
					currentCity == currentCity->connectOne;
				if(n == 2)
					currentCity == currentCity->connectTwo;
				if(n == 3)
					currentCity == currentCity->connectThree;
				if(n == 4)
					currentCity == currentCity->connectFour;
				if(n == 6)
					currentCity == currentCity->connectFive;
        }
        
        void direct()//Player discards city card to go to that city
        {
                //Not shown if player has no city cards in hand
        
                //display available cities player can fly to
                //player chooses a number
                //warn player that they will discard the coresponding city card
                //change current city & decrease actions or go back to actions menu
        }
        
        void charter()//Player discards current city card to go to any city
        {
                //Not shown if player does not have current city card
        
                //display all cities
                //player chooses which
                //warn player that they will discard current city card
                //change current city & decrease actions or go back to actions menu
        }
        
        void shuttle()//If research station in current city, moves player to another research station
        {
                //Not shown if current city does not have a research station
        
                //display all other cities with research stations
                //player chooses a number
                //change current city & decrease actions or go back to actions menu
        }
        
        void build()//Builds a research station in current city
        {
            string response; 
			if(response == "Yes")
			{

				for(int i = 0; i < 7; i++) // run through player hand to see if they have the card
				{
					if(currentCity->name == hand[i].name) //if current city name matches the name of a card the player has
					{
						currentCity->researchStation = true; //the current city now has a research station
						cout << "Research Station placed on " << currentCity->name << endl;
						actions = actions - 1; // take an actions away
					}
				}
			}
			if(response == "No")
				cout << "No research stations place" << endl;
			
			else
				cout << "You dont have the current city's card in your hand, therefore you cannot place a research station" << endl;


			//Not shown if research station already built and if player does not have current city card

				//

                //Display current cities with research stations
                //Yes or no to build one in current city
                //Change city's researchStation to true
                //If researchStations = 6, let player choose another research station to remove
                //decrease actions or back to actions menu
        }
        
        void treat()//Removes disease cube from current city
        {
                Disease d;
		City city;
		int option;
		//Not shown if no disease cubes on current city
		if (city.BlueCubes > 0 || city.YellowCubes > 0 || city.RedCubes > 0 || city.BlackCubes > 0) {
			//Display current city's infection level of each disease
			cout << "This city is infected with: " << endl;
			cout << city.BlueCubes << " blue cubes" << endl;
			cout << city.YellowCubes << " yellow cubes" << endl;
			cout << city.RedCubes << " red cubes" << endl;
			cout << city.BlackCubes << " black cubes" << endl;
			cout << "1. Treat blue\n2. Treat yellow\n3. Treat red\n4. Treat black\n";
			cin >> option;

			//Choose number to remove one or all (if cured) cube(s) of disease
			// and decrease actions or back to actions menu
			switch (option) {
			case 1:
				if (d.status == 2) city.BlueCubes = 0;
				else {
					city.BlueCubes--;
				}
				actions--;
				break;

			case 2:
				if (d.status == 2) city.YellowCubes = 0;
				else {
					city.YellowCubes--;
				}
				actions--;
				break;

			case 3:
				if (d.status == 2) city.RedCubes = 0;
				else {
					city.RedCubes--;
				}
				actions--;
				break;

			case 4:
				if (d.status == 2) city.BlackCubes = 0;
				else {
					city.BlackCubes--;
				}
				actions--;
				break;
			default:
				break;
			}

		}
        }
        
        void share()//Give or take a current city card to/from another player in the same city
        {
                //Not shown if no other players in current city
        
                //Display give or take if able to
                        //Player chooses which
                //Display available cards to give/take
                        //Player chooses
                        //If current hand is >7, player chooses to discard until 7
                //Decrease actions or back to actions menu
        }
        
        void cure()//Player discards 5 same color cards to cure disease of same color
        {
                //Show if on a research station AND >=5 same color city cards AND disease is still live
        
                //warn player that they will discard 5 cards
                        //if >5 same color city cards, player chooses which to keep
                //change color's disease to cured
                //Decrease actions or back to actions menu
        
        }
        
        void pass()//Player does nothing for an action
        {
                //Always shown
                
                //player confirmation
                //decrease actions or back to actions menu
        }
        
        //Maybe put this in main to make it easier to epidemic?
        void draw() //Player draws 2 cards
        {
                //If <2 cards in player deck, player's lose
        
                //Add two cards to player's hand
                //If epidemic is drawn, discard it instead and do epidemic
                //If current hand is >7, player discards until 7
        }
};
