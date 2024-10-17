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
public:
	string name;
	cardType typeofCard;
	int mannaCost;

	Card(string name, cardType typeofCard, int mannaCost) : name(name), typeofCard(typeofCard), mannaCost(mannaCost) {}

	virtual void play() = 0;

};

//Creature class
class Creature : public Card {
public:
	string name;
	int health;
	int damage;

	Creature(string name, int health, int damage, int mannaCost) : 
		Card(name, cardType::CREATURE, mannaCost), name(name), health(health), damage(damage) {}

	void play() override {
		cout << "Creature " << name << " played" << endl;
	}

};


//Player class
class Player {
private:
	//Player attributes
	string name;
	int mannaCount = 0;
	static const int MAX_CARDS = 7;
	static const int MAX_BATTLEFIELD = 5;

	//Set up arrays for hand and battlefield
	Card* hand[MAX_CARDS];
	int handCount = 0;

	int battlefieldCount = 0;

public:
	//Public Player attributes
	int health = 20;
	Card* battlefield[MAX_BATTLEFIELD];


	//Constructor
	Player(string name) : name(name) {
		for (int i = 0; i < MAX_CARDS; i++) {
			hand[i] = nullptr;
		}
		for (int i = 0; i < MAX_BATTLEFIELD; i++) {
			battlefield[i] = nullptr;
		}
	}

	//Draw a card
	void drawCard(Card* card) {
		if (handCount < MAX_CARDS) {
			hand[handCount] = card;
			handCount++;
			cout << "Card " << card->name << " drawn" << endl;
		}
		else {
			cout << "Hand is full" << endl;
		}
	}

	//Play a card
	void playCard(int index){
		if (index < handCount && index >= 0) {
			Card* card = hand[index];
			if (hand[index]->mannaCost <= mannaCount) {
				if (battlefieldCount < MAX_BATTLEFIELD) {
					//Add card to the battlefield
					battlefield[battlefieldCount] = card;
					battlefieldCount++;

					//Remove card from hand
					for (int i = index; i < handCount - 1; i++) {
						hand[i] = hand[i + 1];
					}
					hand[handCount - 1] = nullptr;
					handCount--;

					//Play the Card
					card->play();
				}
				else {
					cout << "Battlefield is full" << endl;
				}
			}
			else {
				cout << "Not enough manna" << endl;
			}
		}
		else {
			cout << "Invalid index" << endl;
		}
	}

	//Print the hand
	void showHand() {
		cout << name << "'s hand:" << endl;

		for (int i = 0; i < handCount; i++) {
			cout << i << ": " << hand[i]->name << " " << hand[i]->mannaCost << endl;
		}
	}

	string getName() {
		return name;
	}
};



#endif