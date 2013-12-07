#pragma once

#include <iostream>
#include <string>
#include "City.h"
#include "Card.h"
#include "Disease.h"
using namespace std;

class Player
{
public:
	int actions;			//How many actions this player has left
	int specialAbility;		//Which role this player is
	static const int maxActions = 4;
	static const int maxHand = 7;
	Card *hand[maxHand + 1];			//Cards in this player's hand
	City *currentCity;		//City this player is in

	//may add parameters for actions

	Player()
	{
		actions = 4;
		specialAbility = 0;
		currentCity = NULL; //should be assigned to Atlanta via main
		for (int i = 0; i < maxHand; i++)
		{
			hand[i] = NULL;
		}
	}


	void special(Player p[4], City *earth, int numP, Disease diseases[], int &researchStations){
		int choice = 0;
		int pswitch1, pswitch2;
		switch (specialAbility) {
			////Operations
		case 1:
			cout << "\nAs the Operations Expert you can Build any Research Station withoud discarding"
				<< " or Move to any research Station by discarding any city card" << endl;
			// get choice
			cout << "\n1.Build\n2.Shuttle\n3.Menu" << endl;
			cin >> choice;
			// call appropriate function
			if (choice == 1 && !currentCity->researchStation)
				build(researchStations, earth);
			else if (choice == 2){

				for (int i = 0; i < maxHand; i++)
					// displays only city cards
				if (hand[i] && (hand[i]->color != 0 || hand[i]->color != 5))
				{
					cout << "  [" << i + 1 << "]  " << hand[i]->name << endl;

				}
				cout << "Discard which card: ";
				cin >> pswitch1;

				hand[pswitch1 - 1]->status = 2;
				hand[pswitch1 - 1] = NULL;

				shuttle(earth);
			}
			else
				break;
			break;
			/////Scientist
		case 2:
			cout << "\nAs the Scientist you can Cure with only 4 of the same colored"
				<< " cards" << endl;
			int b, y, r, blk;
			b = y = blk = r = 0;
			for (int i = 0; i < 7; i++) {
				if (hand[i] && hand[i]->color == 1)b++;
				else if (hand[i] && hand[i]->color == 2)y++;
				else if (hand[i] && hand[i]->color == 3)blk++;
				else if (hand[i] && hand[i]->color == 4)r++;
			}
			if (b == 4 || y == 4 || blk == 4 || r == 4){
				cout << "Currently have 4 cards of the same color did you want to cure? "
					<< " 1. Yes\n 2.No" << endl;
				cin >> choice;
				if (choice == 1)
				{
					cure(diseases, earth);
				}
				else
					break;
			}
			else
				cout << " Currently have less than 4 Cards of same color, Special "
				<< "Ability is not available" << endl;
			break;
			////Medic
		case 3:
			cout << "\nAs the Medic you can treat a whole disease and if a cure has"
				<< " been found you automatically cure a disease when entering" << endl;
			// get choice
			if (currentCity->BlueCubes > 0){
				cout << "Can Treat all of Blue Cubes" << endl;
				cout << "1.Treat\n2.Skip" << endl;
				cin >> choice;
				if (choice == 1)
				{
					while (currentCity->BlueCubes)
					{
						currentCity->BlueCubes--;
						diseases[1].cubes++;
					}
				}
			}
			if (currentCity->YellowCubes > 0){
				cout << "Can Treat all of Yellow Cubes" << endl;
				cout << "1.Treat\n2.Skip" << endl;
				cin >> choice;
				if (choice == 1)
				{
					while (currentCity->YellowCubes)
					{
						currentCity->YellowCubes--;
						diseases[2].cubes++;
					}
				}
			}
			if (currentCity->BlackCubes > 0){
				cout << "Can Treat all of Black Cubes" << endl;
				cout << "1.Treat\n2.Skip" << endl;
				cin >> choice;
				if (choice == 1)
				{
					while (currentCity->BlackCubes)
					{
						currentCity->BlackCubes--;
						diseases[3].cubes++;
					}
				}
			}
			if (currentCity->RedCubes > 0){
				cout << "Can Treat all of Red Cubes" << endl;
				cout << "1.Treat\n2.Skip" << endl;
				cin >> choice;
				if (choice == 1)
				{
					while (currentCity->RedCubes)
					{
						currentCity->RedCubes--;
						diseases[4].cubes++;
					}
				}
			}
			// call appropriate function
			else
				cout << "\nCurrent City has no Cubes to treat" << endl;
			break;
			////Dispatcher
		default:
			cout << "\nAs the Dispatcher you can move other players to another location "
				<< "or you can move them as your own piece" << endl;
			// get choice
			cout << "\n1.Move Player to Player\n2.Move Other player\n3.Skip" << endl;
			// call appropriate function
			cin >> choice;
			if (choice == 1){
				cout << " Move Which Players? " << endl;
				for (int i = 0; i < numP; i++) {
					cout << "Player " << i + 1 << " is currently in "
						<< p[i].currentCity->name << endl;
				}

				do{
					cout << "\n Move Player: ";
					cin >> pswitch1;
				} while (pswitch1 > numP);

				do{
					cout << "\n To Player: ";
					cin >> pswitch2;
				} while (pswitch2 > numP && pswitch2 != pswitch1);

				p[pswitch1].currentCity = p[pswitch2].currentCity;

				cout << "Player " << pswitch1 << " & " << pswitch2 << " currently in "
					<< p[pswitch1].currentCity->name << endl;


			}
			else if (choice == 2){ // ask player who to move
				cout << " Move which Player?" << endl;

				// display current locations of players
				for (int i = 0; i < numP; i++) {
					cout << "Player " << i + 1 << " is currently in "
						<< p[i].currentCity->name << endl;
				}
				//take choice
				cin >> pswitch1;

				//call move function
				p[pswitch1].move();
			}
			else
				break;
			break;
		}
	}

	//moves player to connecting city
	void move()
	{
		//Always shown
		int num = 1;
		cout << "Available cities to drive/ferry to:\n";
		cout << "1. " << currentCity->connectOne->name << endl;
		if (currentCity->connectTwo)
		{
			cout << "2. " << currentCity->connectTwo->name << endl;
			num++;
		}
		if (currentCity->connectThree)
		{
			cout << "3. " << currentCity->connectThree->name << endl;
			num++;
		}
		if (currentCity->connectFour)
		{
			cout << "4. " << currentCity->connectFour->name << endl;
			num++;
		}
		if (currentCity->connectFive)
		{
			cout << "5. " << currentCity->connectFive->name << endl;
			num++;
		}
		if (currentCity->connectSix)
		{
			cout << "6. " << currentCity->connectSix->name << endl;
			num++;
		}
		int n;
		do
		{
			cout << "City number to move to: ";
			cin >> n;
			//Statements to make current city the appropriate city & decrease actions
			//0 should go back to initial player action menu without decreasing

			if (n == 0)
				return;
			else if (n == 1)
				currentCity = currentCity->connectOne;
			else if (n == 2 && num >= 2)
				currentCity = currentCity->connectTwo;
			else if (n == 3 && num >= 3)
				currentCity = currentCity->connectThree;
			else if (n == 4 && num >= 4)
				currentCity = currentCity->connectFour;
			else if (n == 5 && num >= 5)
				currentCity = currentCity->connectFive;
			else if (n == 6 && num >= 6)
				currentCity = currentCity->connectSix;
			else
			{
				cout << "Invalid choice.\n";
				n = 10;
			}
		} while (n == 10);
		if (specialAbility == 3)
		{

		}
		actions--;
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
		for (int i = 0; i < maxHand; i++)
			// displays only city cards
		if (hand[i] && (hand[i]->color != 0 && hand[i]->color != 5))
			cout << "  [" << i + 1 << "]  " << hand[i]->name << endl;
		//player chooses a number
		cout << "\nChoose City [#] or 0 to go back to action menu : ";
		cin >> city;

		//change current city & decrease actions or go back to actions menu
		if (city != 0 && hand[city - 1]){
			cout << "\n Flying From " << currentCity->name << " to " << hand[city - 1]->name << endl;

			///Have to change because hand array becomes pointers
			hand[city - 1]->status = 2; // marks card as discarded

			for (int i = 0; i < 48; i++) {
				if (hand[city - 1] && hand[city - 1]->name == earth[i].name)
					currentCity = &earth[i];
			}
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
			cout << '[' << i + 1 << ']' << earth[i].name << endl;
			if (i == 11 || i == 23 || i == 35)
				cout << endl;
		}

		//player chooses which
		cout << "\nEnter # or 0 to go back to action menu: ";
		cin >> city;

		//change current city & decrease actions or go back to actions menu
		if (city != 0){
			cout << "\n Flying From " << currentCity->name << " to " << earth[city - 1].name << endl;
			//tweak to handle hand pointers
			currentCity = &earth[city - 1];
			for (int i = 0; i < 7; i++)
			{
				if (hand[i] && hand[i]->name == currentCity->name)
					cout << "something" << endl;
			}
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
		for (int i = 0; i < 48; i++)
		if (earth[i].researchStation == true){
			cout << '[' << i + 1 << ']' << earth[i].name << endl;
			stations[a] = i;
			a++;
		}
		//player chooses a number
		cout << "Enter # or 0 to go back to actions menu: ";
		cin >> city;

		//change current city & decrease actions or go back to actions menu
		if (city > 0 && city <= a){
			cout << "\n Flying From " << currentCity->name << " to " << earth[stations[city - 1]].name << endl;

			currentCity = &earth[stations[city - 1]];
			actions--;
		}
	}

	void build(int &researchStations, City earth[])//Builds a research station in current city
	{
		if (specialAbility == 0)
		{
			currentCity->researchStation = true;
			researchStations++;
			actions = actions - 1;
		}
		else
		{
			for (int i = 0; i < 7; i++) // run through player hand to see if they have the card
			{
				if (currentCity->name == hand[i]->name) //if current city name matches the name of a card the player has
				{
					currentCity->researchStation = true; //the current city now has a research station
					cout << "Research Station placed on " << currentCity->name << endl;
					researchStations++;
					hand[i]->status = 2;
					hand[i] = NULL;
					actions = actions - 1; // take an actions away
				}
			}
			cout << "You dont have the current city's card in your hand, therefore you cannot place a research station" << endl;
		}
		if (researchStations > 6)
		{
			int choice;
			do
			{
				cout << "You must remove a research Station.\n";
				for (int i = 0; i < 48; i++)
				{
					if (earth[i].researchStation)
					{
						cout << i + 1 << ". " << earth[i].name << endl;
					}
				}
				cin >> choice;
				if (earth[choice - 1].researchStation)
				{
					earth[choice - 1].researchStation = false;
					researchStations--;
				}
			} while (researchStations > 6);
		}

		//Not shown if research station already built and if player does not have current city card

		//Display current cities with research stations
		//Yes or no to build one in current city
		//Change city's researchStation to true
		//If researchStations = 6, let player choose another research station to remove
		//decrease actions or back to actions menu
	}

	void treat(Disease d[])//Removes disease cube from current city
	{
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
				if (d[1].status == 2)
				{
					d[1].cubes = d[1].cubes + currentCity->BlueCubes;
					currentCity->BlueCubes = 0;
				}
				else {
					currentCity->BlueCubes--;
					d[1].cubes++;
				}
				actions--;
				break;

			case 2:
				if (d[2].status == 2)
				{
					d[2].cubes = d[2].cubes + currentCity->YellowCubes;
					currentCity->YellowCubes = 0;
				}
				else {
					currentCity->YellowCubes--;
					d[2].cubes++;
				}
				actions--;
				break;

			case 3:
				if (d[3].status == 2)
				{
					d[3].cubes = d[3].cubes + currentCity->BlackCubes;
					currentCity->BlackCubes = 0;
				}
				else {
					currentCity->BlackCubes--;
					d[3].cubes++;
				}
				actions--;
				break;

			case 4:
				if (d[4].status == 2)
				{
					d[4].cubes = d[4].cubes + currentCity->BlackCubes;
					currentCity->BlackCubes = 0;
				}
				else {
					currentCity->BlackCubes--;
					d[4].cubes++;
				}
				actions--;
				break;
			default:
				break;
			}

		}

	}

	void share(Player players[4], int p)		//Give or take a current city card to/from another player in the same city
	{											 //Not shown if no other players in current city
		int shar = 0, maxHand = 7;		//init share
		int sharPlayer;
		bool available[4] = { 0, 0, 0, 0 };

		for (int i = 0; i < 4; i++)
		{
			if (players[p].currentCity == players[i].currentCity && &players[p] != &players[i])
				available[i] = true;
		}

		while (shar != 1 && shar != 2)
		{
			cout << "Give or Take Card?\n";		//prompt to give or take card
			cout << " 1) Give 2) Take\n";
			cin >> shar;		//Player chooses which
			if (shar == 1)
			{
				do
				{
					cout << "Choose a player to give the " << currentCity->name << " card to .\n";
					for (int i = 0; i < 4; i++)
					{
						if (available[i])
							cout << i + 1 << ". Player " << i + 1 << endl;
					}
					cin >> sharPlayer;
				} while (sharPlayer > 0 && sharPlayer < 5 && available[sharPlayer - 1] != true);
				for (int i = 0; i <= maxHand; i++)
				{
					if (this->hand[i] && this->hand[i]->name == this->currentCity->name)
					{
						for (int j = 0; j <= maxHand; j++)
						{
							if (hand[j] == NULL)
							{
								players[sharPlayer - 1].hand[j] = players[p].hand[i];
								j = maxHand + 1;
							}
						}
						players[p].hand[i] = NULL;
						actions--;
						cout << "Player " << p + 1 << " has given Player " << sharPlayer << " the " << currentCity->name << " card.\n";
						return;
					}
				}
				cout << "Unable to give a card.";
			}
			else if (shar == 2)
			{

				for (sharPlayer = 0; sharPlayer < 4; sharPlayer++)
				{
					if (available[sharPlayer])
					{
						for (int i = 0; i <= maxHand; i++)
						{
							if (players[sharPlayer].hand[i] && players[sharPlayer].hand[i]->name == players[sharPlayer].currentCity->name)
							{
								for (int j = 0; j <= maxHand; j++)
								{
									if (hand[j] == NULL)
									{
										players[p].hand[j] = players[sharPlayer].hand[i];
										j = maxHand + 1;
									}
								}
								players[sharPlayer].hand[i] = NULL;
								actions--;
								cout << "Player " << sharPlayer + 1 << " has given Player " << p + 1 << " the " << currentCity->name << " card.\n";
								return;
							}
						}
					}
				}
				cout << "Unable to recieve card.";
			}
			else if (shar == 0)
				return;
		}
	}

	void cure(Disease d[], City city[])//Player discards 5 same color cards to cure disease of same color
	{
		if (currentCity->researchStation == true)
		{
			int blu = 0, yel = 0, bla = 0, red = 0;
			if (specialAbility == 2)
			{
				blu++;
				yel++;
				bla++;
				red++;
			}
			for (int i = 0; i < 7; i++)
			{
				if (hand[i])
				{
					switch (hand[i]->color)
					{
					case 1:
						blu++;
						break;
					case 2:
						yel++;
						break;
					case 3:
						bla++;
						break;
					case 4:
						red++;
						break;
					default:
						break;
					}
				}

			}
			if (blu >= 5 || yel >= 5 || bla >= 5 || red >= 5)
			{
				cout << "Your hand:\n";
				for (int i = 0; i < maxHand; i++) {
					// displays only city cards
					if (hand[i]) {
						if (hand[i]->color != 0 && hand[i]->color != 5) {
							cout << "  [" << i + 1 << "]  " << hand[i]->name;
							if (hand[i]->color == 1)
								cout << "(Blue)";
							else if (hand[i]->color == 2)
								cout << "(Yellow)";
							else if (hand[i]->color == 3)
								cout << "(Black)";
							else if (hand[i]->color == 4)
								cout << "(Red)";
							cout << endl;
						}
					}
				}
				cout << "1. Cure blue\n2. Cure yellow\n3. Cure black\n4. Cure red";
				int option;
				cin >> option;
				if ((option == 1 || option == 2 || option == 3 || option == 4) && d[option].status == 1)
				{
					int c = 0;
					do {
						for (int i = 0; i < maxHand; i++)
						{
							if (hand[i] && hand[i]->color == option) {
								hand[i]->status = 2;
								hand[i] = NULL;
								c++;
							}
						}
					} while (c < 5);
					actions--;
					d[option].status = 2;
					cout << d[option].name << " disease cured!\n";
					return;
				}
				else
					cout << "Invalid choice.\n";
			}
		}
	}

	void pass()//Player does nothing for an action
	{
		int pass = 0;
		if (pass == 0)
		{
			cout << "Are you sure you want to pass?\n";
			cout << "1) Yes 2) No\n";
			cin >> pass;
		}
		if (pass == 1)
		{
			if (actions > 0)
			{
				actions = 0;
			}
		}
		//Always shown

		//player confirmation
		//decrease actions or back to actions menu
	}
};