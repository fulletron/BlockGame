#include "player.h"

#include "plate.h"

#include <iostream>

Player::Player(std::string a_name)
{
	name = a_name;
	charge = -1;
	currentPlate = 0;
	alone = true;
	matchedCharge = false;
}

bool Player::getAlone() { return alone; }
void Player::setAlone(bool a_alone) { alone = a_alone; }

bool Player::getMatched() { return matchedCharge; }
void Player::setMatched(bool a_matched) { matchedCharge = a_matched; }

std::string Player::getName() { return name; }
void Player::assignMeToPlate(Plate * a_plate)
{
	if (currentPlate)
		currentPlate->removePlayer(this);
	currentPlate = a_plate;
	currentPlate->assignPlayer(this);
}
Plate * Player::getCurrentPlate(){ return currentPlate; }

void Player::giveCharge(int a_charge){ charge = a_charge; }
int Player::getCharge(){ return charge; }

void Player::__displayPlayerCharge()
{
	std::cout << name << ": " << charge << std::endl;
}