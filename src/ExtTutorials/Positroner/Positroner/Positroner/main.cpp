#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>

#include "plate.h"
#include "player.h"

using namespace std;

typedef std::map <string, vector<string>> ConfigMap;
typedef std::map <int, ConfigMap * > AssigningChargesMap;
AssigningChargesMap * AssMap = 0;

bool doesItSucceed(vector<Plate *> plates, vector<Player *> players)
{
	Plate * curPlate = 0;
	vector<Player *> * curPlayers = 0;
	for (int i = 0; i < 4; ++i)
	{
		curPlate = plates.at(i);
		curPlayers = curPlate->getPlayers();
		if (curPlayers->size() == 0)
		{
			cout << " FAILED. plate had 0 guys on it" << endl;
			return false;
		}
		int charge = curPlayers->at(0)->getCharge();

		for (int j = 1; j < curPlayers->size(); ++j)
		{
			if (charge != curPlayers->at(j)->getCharge())
			{
				cout << " FAILED. plate had players with different charges" << endl;
				return 0;
			}
		}

	}

	return true;
}

void scrambleCharacters(std::string & a_string, int start, int duration)
{
	std::string before2 = a_string;

	std::string sub = a_string.substr(start, duration);
	
	for (int i = 0; i < sub.size(); i++)
	{
		int reploc = rand() % sub.size();
		if (i != reploc)
		{
			char temp = sub.at(i);
			sub.at(i) = sub.at(reploc);
			sub.at(reploc) = temp;
		}
	}

	for (int i = 0; i < sub.size(); i++)
	{
		a_string.at(start + i) = sub.at(i);
	}

	std::string before = before2;
	std::string after = a_string;

	int t = 1; t++;
}

void shufflePlayers(vector<Plate *> plates, vector<Player *> players)
{
	Plate * head = plates.at(0);
	Plate * curPlate = head;

	// make the head the plate with the most players
	for (int i = 1; i < 4; ++i)
	{
		if (head->getNumPlayers() < plates.at(i)->getNumPlayers())
			head = plates.at(i);
	}

	// vecDirection 1 == left (clockwise), -1 == right (counterclockwise)
	int vecDirection = 1;
	Plate * tail = head->getRight();
	// decide if counterclockwise or clockwise
	if (head->getRight()->getNumPlayers() > head->getLeft()->getNumPlayers())
	{
		vecDirection = -1;
		tail = head->getLeft();
	}

	bool isDescending = true;
	// From the head, going the direction previously found, is the order descending?
	// or, is the tail the smallest node?
	int numPlayersAcross = head->getRight()->getRight()->getNumPlayers();
	if (tail->getNumPlayers() > numPlayersAcross)
	{
		// Attempt to get a new head and direction.
		// I know me (head) is at least tied for largest.
		// I know across is lowest
		// I know my current direction

		Plate * temp_head = tail->getRight()->getRight();
		Plate * temp_tail = head->getLeft()->getLeft();

		int tempNumPlayersAcross = temp_head->getRight()->getRight()->getNumPlayers();
		if (temp_tail->getNumPlayers() > tempNumPlayersAcross
		|| head->getNumPlayers() > temp_head->getNumPlayers())
		{
			cout << " WARNING: ONLY CONFIG IS A S IN MID" << endl;
			isDescending = false;
		}
		else
		{
			head = temp_head;
			tail = temp_tail;
			if (head->getLeft() == tail)
			{
				vecDirection = -1;
			}
			else
			{
				vecDirection = 1;
			}
		}
	}

	//cout << " Head is: " << head->getName() << endl;
	//cout << " Tail is: " << tail->getName() << endl;
	//cout << " Dir is : " << vecDirection << "              1 == left (clockwise), -1 == right (counterclockwise) " << endl;

	// save the loner status of players.
	curPlate = head;
	for (int i = 0; i < 4; ++i)
	{
		vector <Player *> * platePlayers = curPlate->getPlayers();
		int numPlayers = platePlayers->size();
		if (numPlayers > 1)
		{
			for (int j = 0; j < numPlayers; ++j)
			{
				platePlayers->at(j)->setAlone(false);
			}
		}
		else
		{
			platePlayers->at(0)->setAlone(true);
		}

		if (vecDirection == 1)
			curPlate = curPlate->getLeft();
		else
			curPlate = curPlate->getRight();
	}

	// build a config string
	std::string config;
	curPlate = head;

	for (int i = 0; i < 4; ++i)
	{
		if (curPlate->getNumPlayers() > 1)
			config += "M";
		else
			config += "S";

		if (vecDirection == 1)
			curPlate = curPlate->getLeft();
		else
			curPlate = curPlate->getRight();
	}

	//cout << "Config is: " << config << endl;
	// get a string of assignments from vector
	ConfigMap * conMap = AssMap->at(players.size());
	conMap->find(config);
	vector<string> poss = conMap->at(config);
	int loc = rand() % poss.size();
	std::string assQueue = poss.at(loc);

	// apply a charge to each player based on the string
	curPlate = head;
	int placeInAssQueue = 0;
	for (int i = 0; i < 4; ++i)
	{
		vector<Player *> * platePlayers = curPlate->getPlayers();
		int numplateplayers = platePlayers->size();

		/*jumble some letters here*/
		scrambleCharacters(assQueue, placeInAssQueue, numplateplayers);

		for (int j = 0; j < numplateplayers; j++)
		{
			Player * curPlayer = platePlayers->at(j);
			char ass = assQueue.at(placeInAssQueue);
			char plus = '+';
			char minus = '-';
			if (ass == plus)
				curPlayer->giveCharge(1);
			else if (ass == minus)
				curPlayer->giveCharge(0);
			else
				curPlayer->giveCharge(rand() % 1);
			placeInAssQueue++;

//curPlayer->__displayPlayerCharge();
		}

		if (vecDirection == 1)
			curPlate = curPlate->getLeft();
		else
			curPlate = curPlate->getRight();
	}

	// check charges for matched charge or diff charges
	curPlate = head;
	for (int i = 0; i < 4; ++i)
	{
		vector<Player *> * platePlayers = curPlate->getPlayers();
		int numPlayers = platePlayers->size();
		if (numPlayers > 1)
		{
			int charge = platePlayers->at(0)->getCharge();
			bool matching = true;

			for (int j = 1; j < numPlayers; j++)
				if (platePlayers->at(j)->getCharge() != charge)
					matching = false;

			if (matching)
				for (int j = 0; j < numPlayers; j++)
					platePlayers->at(j)->setMatched(true);
			else
				for (int j = 0; j < numPlayers; j++)
					platePlayers->at(j)->setMatched(false);
		}
		else
		{
			platePlayers->at(0)->setMatched(false);
		}

		if (vecDirection == 1)
			curPlate = curPlate->getLeft();
		else
			curPlate = curPlate->getRight();
	}

	// move each player to their new plate
	for (int i = 0; i < players.size(); i++)
	{
		Player * p = players.at(i);
		if (p->getCharge())
			if (p->getAlone() || p->getMatched())
				p->assignMeToPlate(p->getCurrentPlate()->getLeft());
			else
				p->assignMeToPlate(p->getCurrentPlate()->getRight());
		else
			if (p->getAlone() || p->getMatched())
				p->assignMeToPlate(p->getCurrentPlate()->getRight());
			else
				p->assignMeToPlate(p->getCurrentPlate()->getLeft());
	}
}

int main()
{
// ======================================= MANDATORY SETUP =================================
	srand(time(0));
	rand();
	rand();

	ConfigMap * mNine = new ConfigMap();
	ConfigMap * mEight = new ConfigMap();
	ConfigMap * mSeven = new ConfigMap();
	ConfigMap * mSix = new ConfigMap();
	ConfigMap * mFive = new ConfigMap();
	ConfigMap * mFour = new ConfigMap();

	vector<string> poss;

	// Nine, MMMS
	// +-- +-- ++ e
	// -++ +-- -- e
	poss.clear();
	poss.push_back("+--+--++e");
	poss.push_back("-+++----e");
	poss.push_back("++-++-++-"); // leads to MMSM
	mNine->insert(std::pair<string, vector<string>>("MMMS", poss));

	poss.clear();
	poss.push_back("+-+-+-+++"); // only leads to mmms
	mNine->insert(std::pair<string, vector<string>>("MMSM", poss));

	// Eight, MMMS
	// +--+-++e
	// -+++---e
	poss.clear();
	poss.push_back("+--+-++e");
	//poss.push_back("-+++---e");
	//poss.push_back("++++-++e");
	//poss.push_back("---+---e");
	poss.push_back("++++-+-e"); //leads to MMSS
	poss.push_back("----+-+e"); //leads to MMSS
	mEight->insert(std::pair<string, vector<string>>("MMMS", poss));

	poss.clear();
	poss.push_back("+++-+---"); // goes back to MMMS
	poss.push_back("---+-+++");
	mEight->insert(std::pair<string, vector<string>>("MMSS", poss));

	// Seven, MMSS
	// +--+-+-
	poss.clear();
	poss.push_back("+--+-+-");
	mSeven->insert(std::pair<string, vector<string>>("MMSS", poss));
	// Seven, MMMS
	// +++-+--
	poss.clear();
	poss.push_back("+++-+--");
	mSeven->insert(std::pair<string, vector<string>>("MMMS", poss));

	// Six, MMSS
	poss.clear();
	poss.push_back("+-+-+-");
	poss.push_back("+-+--+");
	mSix->insert( std::pair<string, vector<string>>("MMSS", poss) );


	// Five, MSSS
	poss.clear();
	poss.push_back("+-+-+");
	poss.push_back("+--+-");
	mFive->insert(std::pair<string, vector<string>>("MSSS", poss));

	// Four, SSSS
	poss.clear();
	poss.push_back("+-+-");
	poss.push_back("++++");
	poss.push_back("----");
	poss.push_back("-+-+");
	mFour->insert(std::pair<string, vector<string>>("SSSS", poss));

	AssMap = new AssigningChargesMap();
	AssMap->insert(std::pair<int, ConfigMap *>(4, mFour));
	AssMap->insert(std::pair<int, ConfigMap *>(5, mFive));
	AssMap->insert(std::pair<int, ConfigMap *>(6, mSix) );
	AssMap->insert(std::pair<int, ConfigMap *>(7, mSeven));
	AssMap->insert(std::pair<int, ConfigMap *>(8, mEight));
	AssMap->insert(std::pair<int, ConfigMap *>(9, mNine));

	string platenames[] = { "North", "East", "South", "West" };
	string names[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
	int numPlayers = 9;

	cout << " testing with " << numPlayers << " players" << endl;

	vector<Player *> players;
	for (int i = 0; i < numPlayers; ++i)
	{
		string pname = names[i];
		players.push_back(new Player(pname));
	}

	vector<Plate *> plates;
	for (int i = 0; i < 4; ++i)
	{
		plates.push_back(new Plate(platenames[i]));
	}

	// Plate Setup
	plates.at(0)->assignLeft(plates.at(1));
	plates.at(0)->assignRight(plates.at(3));

	plates.at(1)->assignLeft(plates.at(2));
	plates.at(1)->assignRight(plates.at(0));

	plates.at(2)->assignLeft(plates.at(3));
	plates.at(2)->assignRight(plates.at(1));

	plates.at(3)->assignLeft(plates.at(0));
	plates.at(3)->assignRight(plates.at(2));

// ==========================================================================
// =================== Character Placement ==================================

	// PLACE THE CHARACTERS

	players.at(0)->assignMeToPlate(plates.at(0));
	players.at(1)->assignMeToPlate(plates.at(0));

	players.at(2)->assignMeToPlate(plates.at(0));
	players.at(3)->assignMeToPlate(plates.at(1));
	players.at(4)->assignMeToPlate(plates.at(1));

	players.at(5)->assignMeToPlate(plates.at(1));
	players.at(6)->assignMeToPlate(plates.at(2));
	players.at(7)->assignMeToPlate(plates.at(2));

	players.at(8)->assignMeToPlate(plates.at(3));

// ===========================================================================

	int failed = 0;
	// BEGIN THE SHUFFLE
	for (int i = 0; i < 200; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			plates.at(j)->__displayPlayersInArea();
		}

		shufflePlayers(plates, players);
		if (!doesItSucceed(plates, players))
		{
			for (int j = 0; j < 4; ++j)
			{
				plates.at(j)->__displayPlayersInArea();
			}

			cout << " SYSTEM FAILED " << endl;
			failed++;
			system("pause");
		}
		else
		{
			cout << "SUCCESS" << endl;
		}
	}

	if (failed == 0)
	{
		cout << "resounding success!" << endl;
	}
	cout << " DONE " << endl;
	system("pause");
	return 0;
}