#pragma once

#include <string>
#include <vector>

class Player;

class Plate
{
protected:
	std::string name;
	Plate * pRight;
	Plate * pLeft;

	std::vector<Player *> playersInArea;
public:
	Plate(std::string a_name);

	std::string getName();

	void assignRight(Plate * pRight);
	void assignLeft(Plate * pLeft);

	void assignPlayer(Player * p);
	void removePlayer(Player * p);

	std::vector<Player *> * getPlayers();
	int getNumPlayers();
	Plate * getRight();
	Plate * getLeft();

	void __displayPlayersInArea();
};