#pragma once

#include <string>

class Plate;

class Player
{
protected:
	std::string name;
	Plate * currentPlate;
	int charge;
	bool alone;
	bool matchedCharge;

public:
	Player(std::string a_name);

	bool getAlone();
	void setAlone(bool a_alone);

	bool getMatched();
	void setMatched(bool a_matched);

	std::string getName();
	void assignMeToPlate(Plate * a_plate);
	Plate * getCurrentPlate();

	void giveCharge(int a_charge);
	int getCharge();

	void __displayPlayerCharge();
};