//
// Prototype of first turns for two players for the Pandemic Game
// - Joeven Paulite -

#include <ctime>
#include <cstdlib> 
using std::rand;
using std::srand;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cin;

class Player{
    int hand[7]; // players hand -- needs to be conditioned to only have a max of seven and no duplicates
    string role; // defines players role -> his special ability --- error handling for duplicates needed
    
    // ability player is capable of doing -- error handling for duplicates and needs to connect to
    // function to diplay description of ability
    int spAbility;
    
    string location; // shows current location *Start point atlanta
    
public:
    Player(){ // constructor default city set as atlanta and hands set to default 0 blank card/empty 
        for (int i = 0; i < 7; i++) {
            hand[i] = 0;
        }
        role = "";
        spAbility = 0;
        location = "Atlanta";
    };
    //sets role by passing random integer role
    void setRole(int a){
        spAbility = a;
        switch (a) {
            case 1:
                role = "Contingency Planner";
                break;
            case 2:
                role = "Dispatcher";
                break;
            case 3:
                role = "Medic";
                break;
            case 4:
                role = "Scientist";
                break;
            case 5:
                role = "Researcher";
                break;
            case 6:
                role = "Quarantine Specialist";
                break;
            default:
                role = "Operations Expert";
                break;
        }
    };
    // display players hand, Keep displayed for player to see what they have
    void showHand(){
        cout << "\n**************************************\n";
        /// input card name & in case of event card list description
        cout << "\n**************************************\n";
    };
    // prints players information should also disply player's number 
    void printPlayer(){
        cout << "Role: " << role;
        cout << "\nCurrently in: " << location;
    };
    
    //Location modifiers
    void setLocation(string l){
        location = l;
    };
    string getLocation(){return location;};
};

/*
 TRADE: The trade functionality has conditions that need to be addressed such as the only tradable card is the card the city the player is in and that both players need to be in that city, special abilities overcome this
 */
void trade(Player, Player);

/*
 DRAW: Draw function takes the player's hands and adds two cards Restriction based on the handlimit and to make sure no duplicates are being played, there should only be two city cards per game, infection and player
 */
void draw(Player);
/*
 INFECT: Takes the passed city and infects it, must conditon for chain reactions
 */
void infect(string);
/*
 MOVE: Moves player from city to city, conditon to limit movement to city that is connected to current location as well as the ability to move by discarding card
 */
void move(string,Player&);
/*
 BUILD: Builds research center; Needs to designate what cities have research center and handles build conditions
*/
void build(Player);

/*
 TREAT: 'Treat' a city by removing a cube; // simplest Function ?
 */
void treat(string t);

//RollInfect: randomly select cities to infect need to condition so that the same city isn't chosen twice 
int rollInfect();

string displayCity(int n); // displays name of city based on assigned number;
//void checkRoles(Player *p); // checks for duplicates recurssively called

int main(int argc, const char * argv[])
{
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds); // randomizes rolls
    rand();
    
    int nOP; // Number of players
    
    do {
        cout << "How many players Playing[1-7]?\n";
        cin >> nOP;
        if(nOP == 0) nOP = 1;
    } while (nOP > 7); // handles choices to limit play to seven people
    
    // the seven player classes
    Player p1,p2,p3,p4,p5,p6,p7;
    Player  players[7] = {p1,p2,p3,p4,p5,p6,p7};

    //determining roles and display players
    cout << "\n\nRandomly assigning Roles: \n";
    for (int i = 0; i < nOP; i++) {
        cout << "\nPlayer " << i+1 << ":\n";
        players[i].setRole((1 + rand() % 7));
        players[i].printPlayer();
    }
/*
// example of game play needs to be in some form of conditional loop
// Each player is allowed to make 4 moves and the available options need to be shown and selectable
*/
    cout << "\n\n\nTurn 1:";
        cout << "\nPlayer1: ";
        move(displayCity(1),players[0]);
        move(displayCity(0),players[0]);
        treat(displayCity(0));
        build(players[0]);
        draw(players[0]);
//Infection phase 
    infect(displayCity(rollInfect()));
    infect(displayCity(rollInfect()));
    
        cout << "\n\nPlayer2: ";
        move(displayCity(1),players[1]);
        treat(displayCity(1));
        build(players[1]);
        trade(players[0],players[1]);
        cout << " with Player 1"; 
        draw(players[2]);
//Infection phase
    infect(displayCity(rollInfect()));
    infect(displayCity(rollInfect()));
    
// After last player's turn display current standings
    cout << "\n\nPlayer 1:\n";
    players[0].printPlayer();
    cout << "\nPlayer 2:\n";
    players[1].printPlayer();
    
//need to keep track of infected cities
//A city class should be created to handle infections and research centers as well as to show connections 
    return 0;
}

string displayCity(int n){
    string cities[48] = {
        "San Francisco", "Chicago","Montreal", "New York", "Washington", "Atlanta",
        "London","Madrid","Paris","Essen","Milan","St.Petersburg",
        
        "Los Angeles","Mexico City","Miami","Bogota","Lima","Buenos Aires",
        "Sao Paulo","Lagos","Khartoum","Johannesburg","Kinshasa","Santiago",
        
        "Algiers","Istanbul","Cairo","Moscow","Tehran","Baghdad","Karachi",
        "Riyadh","Delhi","Kolkata","Mumbai","Chennai",
        
        "Beijing","Seoul","Tokyo","Shanghai","Hong Kong","Taipei","Osaka",
        "Bangkok","Ho Chi Minh City","Manila","Jakarta","Sydney"
    };
    
    return cities[n];
}
//Proto types of commonly used functions
void trade(Player p1, Player p2){
    cout << "\n Traded";
}
void draw(Player p){
    cout << "\n\n Draws 2 Cards \n";
}
void infect(string inf){
    cout << "\n Infects " << inf;
}
void move(string mCity,Player &p){
    cout << "\n Moves to " << mCity;
    p.setLocation(mCity);
}
void build(Player p){
    cout << "\n Built a Research Center in " << p.getLocation();
}
void treat(string t){
    cout << "\n Treats " << t;
}
int rollInfect(){
    int r = 1 + rand() % 47;
    return r;
}
