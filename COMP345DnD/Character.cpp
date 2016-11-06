//! @file Character.cpp
//! @author Patrick Nicoll 27218729
//! @brief Implementation of the class representing an instance of a character

#include "stdafx.h"
#include "Character.h"
#include <random>
#include <iostream>


//! Default no param constructor
Character::Character() {
	level = 1;
	create();
}

//! Constructor that takes a level to initialize the stats accordingly
//! @param levelVal	Level of character
Character::Character(int levelVal) {
	level = 1;
	create();

	//Print statements used for testing
	std::cout << "str: " << str << std::endl;
	std::cout << "dex: " << dex << std::endl;
	std::cout << "con: " << con << std::endl;

	for (int i = 1; i < levelVal; i++) {
		levelUp();
	}

}

//! Destructor
Character::~Character()
{
}

//! Validates wheter the character has valid starting stats
//! @return Whether valid or not, true it is valid, false it is not
bool Character::validateNewCharacter()
{
	bool valid = true;

	if (str < 3 || str > 18)
		valid = false;
	if (dex < 3 || dex > 18)
		valid = false;
	if (con < 3 || con > 18)
		valid = false;
	if (intel < 3 || intel > 18)
		valid = false;
	if (wis < 3 || wis > 18)
		valid = false;
	if (cha < 3 || cha > 18)
		valid = false;

	return valid;
}

//! Method to call all the appropriate methods used during character creation.
void Character::create() {
	generateRandomStats();
	calculateHp();
	calculateAc();
	calculateBaseAttackBonus();
	calculateDamageBonus();
}

//! Generate the attribute values for the six major stats.
//! Values are between 3-18
void Character::generateRandomStats()
{
	// Will be used, but for testing purposes will hardcoded numbers will be set
	int stats[6];

	// create source of randomness, and initialize it with non-deterministic seed
	std::random_device r;
	std::seed_seq seed{ r(),r(),r(),r(),r(),r() };
	std::mt19937 eng{ seed };

	// a distribution that takes randomness and produces values in the range of 3 to 18
	std::uniform_int_distribution<> dist(3, 18);

	for (int i = 0; i < 6; i++) {
		stats[i] = dist(eng);
	}

	//Set stats
	str = stats[0];
	dex = stats[1];
	con = stats[2];
	intel = stats[3];
	wis = stats[4];
	cha = stats[5];

	//Set modifiers
	str_mod = getModifier(stats[0]);
	dex_mod = getModifier(stats[1]);
	con_mod = getModifier(stats[2]);
	intel_mod = getModifier(stats[3]);
	wis_mod = getModifier(stats[4]);
	cha_mod = getModifier(stats[5]);
}

//! Calculates the hitpoints of the character.
//! Hitpoints are calculated by adding the constitution modifier to the character level
void Character::calculateHp()
{
	hp = abs(con_mod) + level;
	maxHp = abs(con_mod) + level;
}

//! Calculates the armor class of the character.
//! Armor class is calculated by adding the dexterity modifier, armor bonus and shield bonus togther and then adding 10
void Character::calculateAc()
{
	ac = 10 + dex_mod;
}

//! Calculates the base attack bonus of the character.
//! Base attack bonus is calculated by adding the strength modifier to the character level
void Character::calculateBaseAttackBonus()
{
	attackBonus = str_mod + level;
}

//! Calculates the damage bonus of the character.
//! Damage bonus is calculated based on the strength modifier of the character
void Character::calculateDamageBonus()
{
	damageBonus = str_mod;
}

//! Will increase attributes upon levelling up
void Character::levelUp() {
	level++;
	str++;
	dex++;
	con++;

	//Call relevant methods to update based on new stat increase
	str_mod = (getModifier(str));
	dex_mod = (getModifier(dex));
	con_mod = (getModifier(con));
	calculateHp();
	calculateAc();
	calculateBaseAttackBonus();
	calculateDamageBonus();
}

//! Determines modifier based on stat entered by evaluating which range it falls in
//! @param stat	Stat to determine range of
//! @return Value of the range the stat fell under
int Character::getModifier(int stat)
{
	int mod;

	if (stat <= 1)
		mod = -5;
	else if (stat <= 3)
		mod = -4;
	else if (stat <= 5)
		mod = -3;
	else if (stat <= 7)
		mod = -2;
	else if (stat <= 9)
		mod = -1;
	else if (stat <= 11)
		mod = 0;
	else if (stat <= 13)
		mod = 1;
	else if (stat <= 15)
		mod = 2;
	else if (stat <= 17)
		mod = 3;
	else if (stat <= 19)
		mod = 4;
	else
		mod = 5;

	return mod;
}

//! Reduces character's hitpoints based on damage inputed
//! @param damage	Damage to be taken away from hitpoints
void Character::hit(int damage) {
	hp -= damage;
}