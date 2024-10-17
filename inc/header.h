#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;
	
//Enumerate the types of cards
enum class cardType {
	CREATURE,
	SPELL,
	ENCHANTMENT,
	MANNA
};

//Card class
class Card {
private:
	string name;
	cardType typeofCard;
	int mannaCost;

public:
	Card(string name, cardType typeofCard, int mannaCost) : name(name), typeofCard(typeofCard), mannaCost(mannaCost) {}

	virtual void play() = 0;

};

//Creature class
class Creature : public Card {
private:
	string name;
	int health;
	int damage;
	int mannaCost;

public:
	Creature(string name, int health, int damage, int mannaCost) : 
		Card(name, cardType::CREATURE, mannaCost), name(name), health(health), damage(damage), mannaCost(mannaCost) {}

	void play() override {
		cout << "Creature " << name << " played" << endl;
	}

};


//Player class
class Player {
private:
	string name = "John Doe";
	int health = 20;
	int mannaCount = 0;
	static const int MAX_CARDS = 7;
	static const int MAX_BATTLEFIELD = 5;

	Card* hand[MAX_CARDS];
	int handCount = 0;

	Card* battlefield[MAX_BATTLEFIELD];
	int battlefieldCount = 0;

public:
	Player(string name) : name(name) {
		for (int i = 0; i < MAX_CARDS; i++) {
			hand[i] = nullptr;
		}
		for (int i = 0; i < MAX_BATTLEFIELD; i++) {
			battlefield[i] = nullptr;
		}
	}

	
	
};



#endif