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
        static const int maxHand = 7;
        Card *hand[maxHand+1];                        //Cards in this player's hand
        City *currentCity;                //City this player is in
		static const int specialAbility = 0; // 0 = Operations Expert, 1 = Scientist, 2 = Medic, 3 = Researcher, 4 = Dispatcher
        //may add parameters for actions

        Player()
        {
                color = 0; //should be assigned randomly
                actions = 4;
                currentCity = NULL; //should be assigned to Atlanta via main
        }

   	void special(Player p[4],City *earth){
        int choice = 0;
        int pswitch;
        switch (specialAbility) {
            case 1:
                cout << "\nAs the Operations Expert you can Build any Research Station"
                << " or Move to any research Station without discarding" << endl;
                // get choice
                cout << "\n1.Build\n2.Shuttle" << endl;
                cin >> choice;
                // call appropriate function
                if (choice == 1)
                    build();
                else if (choice == 2)
                    shuttle(earth);
                else
                    break;
                break;
            case 2:
                cout << "\nAs the Scientist you can Cure with only 4 of the same colored"
                << " cards" << endl;
                int b,y,r,blk;
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
                        cure();
                    else
                        break;
                }
                else
                    cout << " Currently have less than 4 Cards of same color, Special "
                    << "Ability is not available" << endl;
                break;
                
            case 3:
                cout << "\nAs the Medic you can treat a whole disease if a cure has"
                << " been found you automatically cure a disease when entering"<< endl;
                // get choice
                if(currentCity->BlueCubes > 0){
                    cout << "Can Treat all of Blue Cubes" << endl;
                    cout << "1.Treat\n2.Skip" << endl;
                    cin >> choice;
                    if (choice == 1)
                        treat();
                }
                else if(currentCity->YellowCubes > 0){
                    cout << "Can Treat all of Yellow Cubes" << endl;
                    cout << "1.Treat\n2.Skip" << endl;
                    cin >> choice;
                    if (choice == 1)
                        treat();
                }
                else if(currentCity->BlackCubes > 0){
                    cout << "Can Treat all of Black Cubes" << endl;
                    cout << "1.Treat\n2.Skip" << endl;
                    cin >> choice;
                    if (choice == 1)
                        treat();
                }
                else if(currentCity->RedCubes > 0){
                    cout << "Can Treat all of Red Cubes" << endl;
                    cout << "1.Treat\n2.Skip" << endl;
                    cin >> choice;
                    if (choice == 1)
                        treat();
                }
                // call appropriate function
                else
                    cout << "\nCurrent City has no Cubes to treat" << endl;
                break;
            default:
                cout << "\nAs the Dispatcher you can move other players to another location "
                << "or you can move them as your own piece"<< endl;
                // get choice
                cout << "\n1.Move Player to Player\n2.Move Other player\n3.Skip" << endl;
                // call appropriate function
                cin >> choice;
                if (choice == 1)
                    cout << " Move Which Players? " << endl;
                else if (choice == 2)
                    cout << " Move which Player?" << endl;
                else
                    break;
                break;
        }
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
									return;
                                if(n == 1)
                                {        
									currentCity = currentCity->connectOne;
									actions = actions - 1;
								}
                                if(n == 2)
                                {       
									currentCity = currentCity->connectTwo;
									actions = actions - 1;
								}
								if(n == 3)
                                {        
									currentCity = currentCity->connectThree;
									actions = actions - 1;
								}
								if(n == 4)
                                {        
									currentCity = currentCity->connectFour;
									actions = actions - 1;
								}
								if(n == 6)
                                {       
									currentCity = currentCity->connectFive;
									actions = actions - 1;
								}
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
            if (hand[i] && (hand[i]->color != 0 || hand[i]->color != 5))
            { 
				cout << "  [" << i+1 << "]  " << hand[i]->name << endl;
				
			} 
			//player chooses a number
        cout << "\nChoose City [#] or 0 to go back to action menu : ";
        cin >> city;
        
                //change current city & decrease actions or go back to actions menu
        if (city != 0){
            cout << "\n Flying From " << currentCity->name << " to " << hand[city-1]->name << endl;
            
///Have to change because hand array becomes pointers
            hand[city-1]->status = 2; // marks card as discarded
            
            for (int i = 0; i < 48; i++) {
                if(hand[city-1] && hand[city-1]->name == earth[i].name)
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
//tweak to handle hand pointers
            currentCity = &earth[city-1];
            for( int i = 0; i < 7; i++ )
                        {
                                if( hand[i]->name == currentCity->name )
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
        for(int i = 0; i < 48; i++)
            if (earth[i].researchStation == true){
                cout << '[' << i+1 << ']' << earth[i].name << endl;
                stations[a] = i;
                a++;
            }
                //player chooses a number
        cout << "Enter # or 0 to go back to actions menu: ";
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
            string response; 
			string response2;
			if(response == "Yes")
                        {
							
							//check if player is operations specialist
							if(specialAbility == 0)
							{
								cout << "Do you want to use your special ability?: yes/no" << endl;
								cin >> response2;
								if(response2 == "yes")
								{
									currentCity->researchStation = true;
									actions = actions - 1;
									return;
								}
								
							}

								
                                
							
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

        }
        
        void treat()//Removes disease cube from current city
		{
				/**

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
                                if (d.status == 2) currentCity->BlueCubes = 0;
                                else {
                                        currentCity->BlueCubes--;
                                }
                                actions--;
                                break;

                        case 2:
                                if (d.status == 2) currentCity->YellowCubes = 0;
                                else {
                                        currentCity->YellowCubes--;
                                }
                                actions--;
                                break;

                        case 3:
                                if (d.status == 2) currentCity->RedCubes = 0;
                                else {
                                        currentCity->RedCubes--;
                                }
                                actions--;
                                break;

                        case 4:
                                if (d.status == 2) currentCity->BlackCubes = 0;
                                else {
                                        currentCity->BlackCubes--;
                                }
                                actions--;
                                break;
                        default:
                                break;
                        }

                }

        **/}
        
		void share(Player players[4], int p)												//Give or take a current city card to/from another player in the same city
	{														//Not shown if no other players in current city
			int shar=0, maxHand = 7;											//init share
			int givCard, takCard, sharPlayer;
			
			for( int k = 0; k < 7; k++ )
			{
				if( players[p].hand[k] && players[p].hand[k]->name == players[p].currentCity->name )
				{
					for( int i = 0; i < 4; i++ )
					 {
						if( players[p].currentCity == players[i].currentCity )
							sharPlayer = i;
					 }
             	}
			}
			while (shar!=1 || shar!=2)
			{
            cout << "Give or Take Card?\n";						//prompt to give or take card
			cout << " 1) Give 2) Take\n";
			cin >> shar;										//Player chooses which
				if (shar==1 || players[p].hand>0)						//verify player has card to give
				{  
				cout << "\nPlayer's cards in hand:\n";
					for(int i = 0; i < 7; i++)
					{
						if( players[p].hand[i] && players[p].hand[i]->status == 1 )
						{
						cout << players[p].hand[i]->name << endl;
						}
					}
				cout << "Choose which card to give (0-6)\n";
				cin >> givCard;
					if ( givCard != 0 || givCard != 1 || givCard != 2 || givCard != 3 || givCard != 4 || givCard != 5 || givCard != 6)
					{
					cout << "Please choose a valid card #\n";
					}
					else
					{
						for( int j = 0; j <= maxHand; j++ )
						{
							if( hand[j] == NULL )
								players[sharPlayer].hand[j] = players[p].hand[givCard];
								players[p].hand[givCard] = NULL;
						}
					}
				}
				if (shar==2 || players[sharPlayer].hand>0)		//verify player has card to take
				{  
				cout << "\nPlayer's cards in hand:\n";
					for(int i = 0; i < 7; i++)
					{
						if( players[sharPlayer].hand[i] && players[sharPlayer].hand[i]->status == 1 )
						{
						cout << players[sharPlayer].hand[i]->name << endl;
						}
					}
				cout << "Choose which card to take (0-6)\n";
				cin >> takCard;
					if ( takCard != 0 || takCard != 1 || takCard != 2 || takCard != 3 || takCard != 4 || takCard != 5 || takCard != 6)
					{
					cout << "Please choose a valid card #\n";
					}
					else
					{
						for( int j = 0; j <= players[p].maxHand; j++ )
						{
							if( players[p].hand[j] == NULL )
							players[sharPlayer].hand[takCard] = NULL;
							players[p].hand[j] = players[sharPlayer].hand[takCard];
						}
					}
				}
			}
		actions--;											//Decrease actions or back to actions menu
		}
        
        void cure(/*Disease d[], City city[], Card card*/)//Player discards 5 same color cards to cure disease of same color
		{
			/**

                Disease d;
                City city;
                Card card;
                if (currentCity->researchStation == true)
                {
                        int blu = 0, yel = 0, bla = 0, red = 0;
                        for (int i = 0; i < 7; i++)
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
                        if (blu >= 5 || yel >= 5 || bla >= 5 || red >= 5)
                        {
                                cout << "Discard 5 cards?";
                                for (int i = 0; i < maxHand; i++) {
                                        // displays only city cards
                                        if (hand[i]) {
                                                if (hand[i]->color != 0 && hand[i]->color != 5) {
                                                        cout << "  [" << i + 1 << "]  " << hand[i]->name << endl;
                                                        if (blu >= 5 || yel >= 5 || bla >= 5 || red >= 5) {
                                                                cout << blu << endl;
                                                                cout << yel << endl;
                                                                cout << bla << endl;
                                                                cout << red << endl;
                                                        }
                                                }
                                        }
                                }
                                cout << "1. Cure blue/n2. Cure yellow/n3. Cure black/n4. Cure red";
                                int option;
                                cin >> option;
                                if (option == 1 || option == 2 || option == 3 || option == 4) {
                                        int c = 0;
                                        do {
                                                if (hand[c]->color == option) {
                                                        card.status = 2;
                                                        hand[c] = NULL;
                                                        d.status = 2;
                                                        actions--;
                                                }
                                        } while (c <= 5);
                                }
                        }
                }
        **/}
        
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
