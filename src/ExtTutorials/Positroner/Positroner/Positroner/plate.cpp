#include "plate.h"

#include "player.h"

#include <iostream>

Plate::Plate(std::string a_name){ name = a_name; }

void Plate::assignRight(Plate * a_right){ pRight = a_right; }
void Plate::assignLeft(Plate * a_left){ pLeft = a_left; }

void Plate::assignPlayer(Player * p){ playersInArea.push_back(p); };
void Plate::removePlayer(Player * p)
{
	for (int i = 0; i < playersInArea.size(); i++)
	{
		if (playersInArea.at(i)->getName() == p->getName())
		{
			playersInArea.erase(playersInArea.begin() + i);
			break;
		}
	}
}

std::vector<Player *> * Plate::getPlayers() { return &playersInArea; }
int Plate::getNumPlayers(){ return playersInArea.size(); }
Plate * Plate::getRight() { return pRight; }
Plate * Plate::getLeft() { return pLeft; }

void Plate::__displayPlayersInArea()
{
	std::cout << name << " contains: ";
	for (int i = 0; i < playersInArea.size(); i++)
	{
		std::cout << playersInArea.at(i)->getName() << " ";
	}
	std::cout << std::endl;
}

std::string Plate::getName()
{
	return name;
}