#include <iostream>
#include "header.h" 
#include <random>

using namespace std;

// array of creatures
Creature creatures[] = {
	//Name, health, damage, mannaCost
	Creature("Goblin", 1, 1, 1),
	Creature("Orc", 2, 3, 2),
	Creature("Dragon", 5, 5, 5),
	Creature("Troll", 3, 4, 3),
	Creature("Elf", 1, 3, 1),
	Creature("Giant", 4, 4, 4),
	Creature("Fiend", 2, 2, 2),
};

//Draw Phase
void drawPhase(Player& player){
	player.drawCard(new Creature(creatures[rand() % 3]));
}

//Combat Phase
void combatPhase(Player& attacker, Player& defender){
	cout << "Combat phase" << endl;
	//Check if attacker has creatures to attack
	if (attacker.getBattlefieldCount() == 0) {
		cout << attacker.getName() << " has no creatures to attack with." << endl;
	}
	else{
		//Loop through the attacker's battlefield
		for (Card* card : attacker.battlefield) {
			//Check if the card is a creature or null
			if (card == nullptr) {
				continue; // Skip to the next card
			}
			//Creature attacks enemy player	
			if (card->typeofCard == cardType::CREATURE) {
				//Cast the card to a creature
				Creature* creature = dynamic_cast<Creature*>(card);
				cout << attacker.getName() << "'s " << creature->name << " attacks!" << endl;
				defender.health -= creature->damage;
				cout << defender.getName() << " takes " << creature->damage << " damage, life is now " << defender.health << endl;
			}
		}
	}
}

//Main Phase
void mainPhase(Player& player) {
	cout << player.getName() << " main phase" << endl;
	player.drawCard(new Creature(creatures[rand() % 3]));
	while (true) {
		//Get the player's choice of card to play
		cout << "Enter card index to play or (9) to see your hand: ";
		int index;
		cin >> index;
		//Check if the player wants to see their hand
		if (index == 9) {
			player.showHand();
			continue; 
		}
		//Check if the index is valid
		if (index >= 0 && index < player.getHandCount()) {
			//Check if the card is a creature then place it on the battlefield
			Card* card = player.hand[index];
			if (card->typeofCard == cardType::CREATURE) {
				player.playCard(index);
				break; // Exit the loop after playing a card
			} else {
				cout << "Invalid card type" << endl;
			}
		} else {
			cout << "Invalid index" << endl;
		}
	}
}

int main(){
	// Create two players
	cout << "Enter player 1 name: ";
	string player1name;
	cin >> player1name;

	cout << "Enter player 2 name: ";
	string player2name;
	cin >> player2name;

	Player player1(player1name);
	Player player2(player2name);

	// Draw cards for each player
	cout << "Drawing cards" << endl;
	for (int i = 0; i < 5; i++) {
		drawPhase(player1);
		drawPhase(player2);
	}
	player1.showHand();
	player2.showHand();

	// Main game loop
	do {
		player1.addManna(1);
		player2.addManna(1);

		mainPhase(player1);
		mainPhase(player2);

		combatPhase(player1, player2);
		combatPhase(player2, player1);

		cout << player1.getName() << "'s health: " << player1.health << endl;
		cout << player2.getName() << "'s health: " << player2.health << endl;

	} while (player1.health > 0 && player2.health > 0);

	// End game conditions
	if (player1.health <= 0) {
		cout << player2.getName() << " wins!" << endl;
	} else if (player2.health <= 0) {
		cout << player1.getName() << " wins!" << endl;
	} else if (player1.health <= 0 && player2.health <= 0) {
		cout << "Game ended in a draw" << endl;
	} else {
		cout << "Game ended in an error" << endl;
	}

	return 0;
}