#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "City.h"
#include "Card.h"
#include "Disease.h"


class Player
{
public:
	int color;				//Which role this player is
	int actions;			//How many actions this player has left
	static const int maxActions = 4;
	static const int maxHand = 7;
	Card *hand[maxHand+1];			//Cards in this player's hand
	City *currentCity;		//City this player is in

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
            currentCity = currentCity->connectOne;
        if(n == 2)
            currentCity = currentCity->connectTwo;
        if(n == 3)
            currentCity = currentCity->connectThree;
        if(n == 4)
            currentCity = currentCity->connectFour;
        if(n == 6)
            currentCity = currentCity->connectFive;
	}
	 
	void direct(City earth[48])//Player discards city card to go to that city
	{
		int city; // city to fly to
		//Not shown if player has no city cards in hand
		//display available cities player can fly to
        	//warn player that they will discard the coresponding city card
        	cout << "Available Cities to Directly Fly to "
        		<< "[Direct Flights Remove City Card From Hand] : " << endl;
        
		 //goes through hand
        for (int i = 0; i < maxHand; i++){
        	 // displays only city cards
            if (hand[i] && hand[i]->status != 2)
			if (hand[i]->color != 0 && hand[i]->color != 5)
                		cout << "  [" << i+1 << "]  " << hand[i]->name << endl;
                //player chooses a number
        }
        	cout << "\nChoose City [#] or 0 to go back to action menu : ";
        	cin >> city;
        
                //change current city & decrease actions or go back to actions menu
        	if (city != 0){
            		cout << "\n Flying From " << currentCity->name << " to " << hand[city-1]->name << endl;
            
            		hand[city-1]->status = 2; // marks card as discarded
                
            		for (int i = 0; i < 48; i++) {
                		if(hand[city-1]->name == earth[i].name)
                			 currentCity = &earth[i];
            			}
                hand[city-1] = NULL;
        		actions--;
        	}
        
	}
	
	void charter(City earth[48])//Player discards current city card to go to any city
	{
		int city;
                //Not shown if player does not have current city card
		 cout << "Charter a flight to a city by discarding current city card "
                << "[City card will be discarded from hand]: " << endl;
        
                //display all cities
        for (int i = 0; i < 48; i++) {
            cout << '[' << i+1 << ']' << earth[i].name << endl;
            if (i == 11 || i == 23 || i == 35)
				cout << endl;
        }
        
                //player chooses which
        cout << "\nEnter # or 0 to go back to action menu: ";
        cin >> city;
        
                //change current city & decrease actions or go back to actions menu
        if (city != 0){
            cout << "\n Flying From " << currentCity->name << " to " << earth[city-1].name << endl;

            for( int i = 0; i < 7; i++ ){
                if (hand[i] && hand[i]->status != 2)
                    if( hand[i]->name == currentCity->name )
                        hand[i] = NULL;
            }
            
            currentCity = &earth[city-1];
            actions--;
        }
        
	}
	
	void shuttle(City earth[48])//If research station in current city, moves player to another research station
	{
        int stations[6]; // tracks stations city #
        int city; // player's choice
        int a = 0; // counter for research stations
        
                //Not shown if current city does not have a research station
        cout << "Shuttle from one research station to another: " << endl;
        
                //display all other cities with research stations
        for(int i = 0, j = 1; i < 48; i++)
            if (earth[i].researchStation == true && currentCity != &earth[i]){
                cout << '[' << j << ']' << earth[i].name << endl;
                stations[a] = i;
                j++;
                a++;
            }
                //player chooses a number
        cout << "\nEnter # or 0 to go back to actions menu: ";
        cin >> city;
        
        //change current city & decrease actions or go back to actions menu
        if (city != 0){
            cout << "\n Flying From " << currentCity->name << " to " << earth[stations[city-1]].name << endl;
            
            currentCity = &earth[stations[city-1]];
            actions--;
        }
	}
	
	void build()//Builds a research station in current city
	{
		//Not shown if research station already built and if player does not have current city card
        string response;
        if(response == "Yes")
        {
            
            for(int i = 0; i < 7; i++) // run through player hand to see if they have the card
            {
                if(currentCity->name == hand[i]->name) //if current city name matches the name of a card the player has
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
        if (currentCity->BlueCubes > 0 || currentCity->YellowCubes > 0 || currentCity->RedCubes > 0 || currentCity->BlackCubes > 0) {
            //Display current city's infection level of each disease
            cout << "This city is infected with: " << endl;
            cout << currentCity->BlueCubes << " blue cubes" << endl;
            cout << currentCity->YellowCubes << " yellow cubes" << endl;
            cout << currentCity->RedCubes << " red cubes" << endl;
            cout << currentCity->BlackCubes << " black cubes" << endl;
            cout << "1. Treat blue\n2. Treat yellow\n3. Treat red\n4. Treat black\n";
            cin >> option;
            
            //Choose number to remove one or all (if cured) cube(s) of disease
            // and decrease actions or back to actions menu
            switch (option) {
                case 1:
                    if (d.status == 2) city.BlueCubes = 0;
                    else {
                        currentCity->BlueCubes--;
                    }
                    actions--;
                    break;
                    
                case 2:
                    if (d.status == 2) city.YellowCubes = 0;
                    else {
                        currentCity->YellowCubes--;
                    }
                    actions--;
                    break;
                    
                case 3:
                    if (d.status == 2) city.RedCubes = 0;
                    else {
                        currentCity->RedCubes--;
                    }
                    actions--;
                    break;
                    
                case 4:
                    if (d.status == 2) city.BlackCubes = 0;
                    else {
                        currentCity->BlackCubes--;
                    }
                    actions--;
                    break;
                default:
                    break;
            }
            
        }
    }
	
	void share()												//Give or take a current city card to/from another player in the same city
	{															//Not shown if no other players in current city
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

	void pass()													//Player does nothing for an action
        {														//Alway shown
			int pass=0;											//init pass choice
			if (pass==0)										//pass confirmation
			{
			cout << "Are you sure you want to pass?\n";
			cout << "1) Yes 2) No\n";
			cin >>  pass;										//pass choice
			}
				if (pass == 1)									//set actions to 0
				{
					if (actions>0)
					{
							actions = 0;
					}
                }
        }
	
};
