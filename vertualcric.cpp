
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
using namespace std;

class Player {
    public:
    Player();
    string name;
    int id;
    int runsScored;
    int ballsPlayed;
    int ballsBowled;
    int runsGiven;
    int wicketTaken;



};
Player :: Player(){
     runsScored = 0;
     ballsPlayed = 0;
     ballsBowled = 0;
     runsGiven = 0;
     wicketTaken = 0;
};

class Team {
    public:
     Team();
     std::string name;
     int totalRunsScored;
     int wicketsLost;
     int totalsBallBowled;
     vector<Player> players;



};
Team::Team(){
    totalRunsScored = 0;
    wicketsLost = 0;
    totalsBallBowled = 0;
};

class Game {
    public:
       Game();
       int playersPerTeam;
       int maxBalls;
       int totalPlayers;
       std::string players[11];

       bool isFirstInnings;
       Team teamA, teamB;
       Team *battingTeam, *bowlingTeam;
       Player *batsman, *bowler;
 
       void welcome();
	   void showAllPlayers();
	   int takeIntigerInput();
	   void selectPlayers();
	   bool validateSelectedPlayer(int);
	   void showTeamPlayers();
	   void toss();
	   void tossChoice(Team);
		void startFirstInning();
		void initializePlayers();
		void playInnings();
		void bat();
		bool validateInningsScore();
		void showGameScorecard();
		void startSecondInnings();
		void winnerTeam();
		void summary();
};
void Game:: welcome(){
    cout<<"---------------------------------"<<endl;
	cout<<"|========== Cric. In ===========|"<<endl;
	cout<<"|                               |"<<endl;
	cout<<"|Welcome to Virtual cricket game|"<<endl;
	cout<<"|                               |"<<endl;
	cout<<"--------------------------------|"<<endl<<endl<<endl;

	cout<<"------------------------------------"<<endl;
	cout<<"|=========Game Instructions=========|"<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<"|1.Create 2 teams(Team-A, Team-B)   |"<<endl;
	cout<<"|with 4 players each from a given   |"<<endl;
	cout<<"|pool of 11 players.                |"<<endl;
	cout<<"|2.Lead the toss and decide to play.|"<<endl;
	cout<<"|3.Each innings will be of 6 balls. |"<<endl;
	cout<<"-------------------------------------"<<endl;
}
void Game::showAllPlayers(){
	cout<<"----------------------"<<endl;
	cout<<"|  Pool of Players   |"<<endl;
	cout<<"----------------------"<<endl;
	
	for(int i=0; i<11; i++){
		cout<<"\t\t["<<i<<"]"<<" : "<<players[i]<<endl;
	}
}
int Game::takeIntigerInput(){
	int n;
	while(!(cin>>n)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<"Invalid Input!  Please try again"<<endl;
	}
	return n;

}

bool Game :: validateSelectedPlayer(int index){
	int n;
	vector<Player> players;

	players = teamA.players;
	n=players.size();
	for (int i = 0; i < n; i++)
	{
		if(players[i].id==index){
			return false;
		}
	}


	players = teamB.players;
	n=players.size();
	for (int i = 0; i < n; i++)
	{
		if(players[i].id==index){
			return false;
		}
	}

	return true;
	

}
void Game::selectPlayers(){
	cout<<endl;
	cout<<"--------------------------------"<<endl;
	cout<<"|== Create Team-A and Team-B ==|"<<endl;
	cout<<"--------------------------------"<<endl;
	teamAselection:
	for(int i=0; i<playersPerTeam;i++){
		cout<<endl<<"Select Player "<<i+1<<"  to Team-A ";
		int playerIndexTeamA = takeIntigerInput();
		if(playerIndexTeamA<0 || playerIndexTeamA>10){
			cout<<endl<<"Please select from the given players"<<endl;
			goto teamAselection;
		}
		else if(!validateSelectedPlayer(playerIndexTeamA)){
			cout<<endl<<"This player is already selected !, please selec t other player"<<endl;
			goto teamAselection;
		}
		else{
		Player teamAplayer;
		teamAplayer.id = playerIndexTeamA;
		teamAplayer.name = players[playerIndexTeamA];
		teamA.players.push_back(teamAplayer);
	}
		

	teamBselection:
	
		cout<<endl<<"Select Player "<<i+1<<"  to Team-B ";
		int playerIndexTeamB = takeIntigerInput();
		if(playerIndexTeamB<0 || playerIndexTeamB>10){
			cout<<endl<<"Please select from the given players"<<endl;
			goto teamBselection;
		}
		else if(!validateSelectedPlayer(playerIndexTeamB)){
			cout<<endl<<"This player is already selected !, please selec t other player"<<endl;
			goto teamBselection;
		}
		else{
		Player teamBplayer;
		teamBplayer.id = playerIndexTeamB;
		teamBplayer.name = players[playerIndexTeamB];
		teamB.players.push_back(teamBplayer);
		}
	}
}

void Game::showTeamPlayers() {

    vector<Player> teamAPlayers = teamA.players;
    vector<Player> teamBPlayers = teamB.players;

    cout << endl << endl;
    cout << "--------------------------\t\t--------------------------" << endl;
    cout << "|=======  Team-A  =======|\t\t|=======  Team-B  =======|" << endl;
    cout << "--------------------------\t\t--------------------------" << endl;

    for (int i = 0; i < playersPerTeam; i++) {
        cout << "|\t" << "[" << i << "] " << teamAPlayers[i].name << "\t |"
        	<< "\t\t"
			<< "|\t" << "[" << i << "] " << teamBPlayers[i].name << "\t |" << endl;
    }
    cout << "--------------------------\t\t--------------------------" << endl << endl;
}

void Game::toss(){
	cout<<endl;
	cout<<"Let's toss ...  "<<endl;
	cout<<"Tossing the coin"<<endl;
	srand(time(NULL));
	int randomValue = rand()%2;

	switch ((randomValue))
	{
	case 0: 
	    cout<<"Team A won the toss"<<endl<<endl;
		tossChoice(teamA);
		break;
	
	case 1:
		cout<<"Team B won the toss"<<endl<<endl;
		tossChoice(teamB);
		break;
	}
}

void Game::tossChoice(Team tossWinnerTeam){
	cout<<endl<<"Enter 1 to bat or 2 to bowl first"<<endl;
	cout<<"1.bat"<<endl<<"2.bowl"<<endl;
	tryagain:
	int tossChoice = takeIntigerInput();
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	switch(tossChoice){
		case 1: 
		cout<<endl<<tossWinnerTeam.name<<"  won the toss and elected to bat first"<<endl<<endl;
		if(tossWinnerTeam.name.compare("Team-A")==0){
			battingTeam = &teamA;
			bowlingTeam = &teamB;
		}
		else{
			battingTeam = &teamB;
			bowlingTeam = &teamA;
		}
		break;
		case 2:
		cout<<endl<<tossWinnerTeam.name<<"  won the toss and elected to bowl first"<<endl<<endl;
		if(tossWinnerTeam.name.compare("Team-A")==0){
			bowlingTeam = &teamA;
			battingTeam = &teamB;
		}
		else{
			bowlingTeam = &teamB;
			battingTeam = &teamA;
		}
		break;
		default:
		cout<<"INVALID INPUT, please try again"<<endl<<endl;
		goto tryagain;
		break;
	}

}


void Game::startFirstInning(){
	cout<<endl<<"||    First Innings Start    ||"<<endl;
	isFirstInnings = true;
	initializePlayers();
	playInnings();

}
void Game::initializePlayers(){
	batsman = &battingTeam->players[0];
	bowler = &bowlingTeam->players[0];

	cout<<battingTeam->name<<" -  "<<batsman->name<<"  is batting"<<endl;
	cout<<bowlingTeam->name<<" - "<<bowler->name<<" is bowling"<<endl<<endl;

}

void Game::playInnings(){
	for (int i = 0; i < maxBalls; i++)
	{
		cout<<"Press Enter to bowl"<<endl;
		getchar();
		cout<<"Bowling..."<<endl;
		bat();
		if(!validateInningsScore()){
			break;
		}
	}
	

}

void Game::bat(){
	srand(time(NULL));
	int runsScored = rand()%7;

	batsman->runsScored = batsman->runsScored + runsScored;
	battingTeam->totalRunsScored = battingTeam->totalRunsScored + runsScored;
	batsman->ballsPlayed ++;

	bowler->ballsBowled++; 
	bowlingTeam->totalsBallBowled++;
	bowler->runsGiven += runsScored;

	
	if(runsScored!=0){
			cout<<bowler->name<<"  to  "<<batsman->name<<"  "<<runsScored<<"  Runs"<<endl<<endl;
			showGameScorecard();
	}
	else{
		    cout<<bowler->name<<"  to  "<<batsman->name<<" Out!"<<endl<<endl;
			battingTeam->wicketsLost = battingTeam->wicketsLost + 1;
			bowler->wicketTaken = bowler->wicketTaken+1;
			showGameScorecard();
			int nextPlayerIndex = battingTeam->wicketsLost;
			batsman = &battingTeam->players[nextPlayerIndex];

	}


}

bool Game::validateInningsScore(){
	if(isFirstInnings){
		if(battingTeam->wicketsLost == playersPerTeam || bowlingTeam->totalsBallBowled == maxBalls){

			cout<<"\t\t||  First Innings Ends   ||"<<endl;
			cout << battingTeam->name << " " << battingTeam->totalRunsScored << " - "
					<< battingTeam->wicketsLost << " (" << bowlingTeam->totalsBallBowled
					<< ")" << endl;

			cout << bowlingTeam->name << " needs " << battingTeam->totalRunsScored + 1
					<< " runs to win the match" << endl << endl;
			return false;
		}
	}
	else{
		if(battingTeam->totalRunsScored>bowlingTeam->totalRunsScored){
			return false;

		}
		else if(battingTeam->wicketsLost == playersPerTeam || bowlingTeam->totalsBallBowled == maxBalls ){

			cout<<"\t\t||  Second Innings Ends   ||"<<endl;
			cout << battingTeam->name << " " << battingTeam->totalRunsScored << " - "
					<< battingTeam->wicketsLost << " (" << bowlingTeam->totalsBallBowled
					<< ")" << endl;

			return false;
		}
		
	}
	return true;
}
void Game::showGameScorecard() {

    cout << "--------------------------------------------------------------------------" << endl;

    cout << "\t" << battingTeam->name << "  " << battingTeam->totalRunsScored << " - "
      << battingTeam->wicketsLost << " (" << bowlingTeam->totalsBallBowled << ") | " << batsman->name
      << " " << batsman->runsScored << " (" << batsman->ballsPlayed << ") \t" << bowler->name << " "
	  << bowler->ballsBowled << " - " << bowler->runsGiven << " - " << bowler->wicketTaken << "\t" << endl;

    cout << "--------------------------------------------------------------------------" << endl << endl;
	int target =  battingTeam->totalRunsScored;
}

void Game::startSecondInnings(){
	cout<<endl<<"\t\t||    Second Innings Start    ||"<<endl;
	isFirstInnings = false;
	Team temp = *battingTeam;
	*battingTeam = *bowlingTeam;
	*bowlingTeam = temp;

	initializePlayers();

	playInnings();
}

void Game::winnerTeam(){
	if(battingTeam->totalRunsScored>bowlingTeam->totalRunsScored){
		cout<<battingTeam->name<<"  WINS!!!"<<endl;
	}
    else if(battingTeam->totalRunsScored==bowlingTeam->totalRunsScored){
		cout<<"MATCH TIE"<<endl;
    }
	else
	  cout<<bowlingTeam->name<<"  WINS!!!"<<endl;


}

void Game::summary(){
	cout<<endl<<"|           MATCH ENDS          |"<<endl;
	cout<<"Summary of the game : "<<endl;
	cout<<"=============================="<<endl;
	cout<<"|<< "<<battingTeam->name<<"\t"<<battingTeam->totalRunsScored<<"-"<<bowlingTeam->wicketsLost<<"\t("<<battingTeam->totalsBallBowled<<")"<<">>|"<<endl;
	
	cout<<"|<<"<<bowlingTeam->name<<"\t"<<bowlingTeam->totalRunsScored<<"-"<<battingTeam->wicketsLost<<"\t("<<bowlingTeam->totalsBallBowled<<")"<<">>|"<<endl;
	cout<<"=============================="<<endl;
	vector<Player> teamAPlayers = teamA.players;
    vector<Player> teamBPlayers = teamB.players;

    cout << endl << endl;
    cout << "----------------------------------\t\t---------------------------------" << endl;
    cout << "|===========  Team-A  ===========|\t\t|===========  Team-B  ===========|" << endl;
    cout << "--------------------------------\t\t--------------------------------" << endl;

    for (int i = 0; i < playersPerTeam; i++) {
        cout << "|\t" << "[" << i << "] " << teamAPlayers[i].name <<"\t"<<teamAPlayers[i].runsScored<< "\t |"
        	<< "\t\t"
			<< "|\t" << "[" << i << "] " << teamBPlayers[i].name <<"\t"<<teamBPlayers[i].runsScored<< "\t |" << endl;
    }
	cout << "----------------------------------\t\t----------------------------------" << endl;

}
Game :: Game(){
    playersPerTeam = 4;
    maxBalls = 6;
    totalPlayers = 11;

    players[0] = "Mohd";
    players[1] = "Yaqoob";
    players[2] = "Rahul";
    players[3] = "Virat";
    players[4] = "Rohit";
    players[5] = "Tongyal";
    players[6] = "Talib";
    players[7] = "Hassan";
    players[8] = "Mirza";
    players[9] = "Prince";
    players[10] = "Sujal";



    isFirstInnings=false;
    teamA.name = "Team-A";
    teamB.name = "Team-B";
}


int main() {
	Game game;
	game.welcome();

	cout<<"\nPress enter to continue"<<endl;
	getchar();

	game.showAllPlayers();


	cout<<"\nPress enter to continue"<<endl;
	getchar();

	game.selectPlayers();
	game.showTeamPlayers();

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout<<"\nPress enter to continue"<<endl;
	getchar();

	game.toss();
	game.startFirstInning();
	game.startSecondInnings();
	game.winnerTeam();
	game.summary();

	return 0;
}