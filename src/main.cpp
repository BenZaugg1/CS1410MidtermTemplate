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

void drawPhase(Player& player){
	player.drawCard(new Creature(creatures[rand() % 3]));
	//return;
}

void combatPhase(Player& attacker, Player& defender){
	cout << "Combat phase" << endl;
	if (attacker.getBattlefieldCount() == 0) {
		cout << attacker.getName() << " has no creatures to attack with." << endl;
		// return;
	}
	else{
		for (Card* card : attacker.battlefield) {
			if (card->typeofCard == cardType::CREATURE) {
				Creature* creature = dynamic_cast<Creature*>(card);
				if (creature) {
					cout << attacker.getName() << "'s " << creature->name << " attacks!" << endl;
					defender.health -= creature->damage;
					cout << defender.getName() << " takes " << creature->damage << " damage, life is now " << defender.health << endl;
				} else {
					cout << "Error: Failed to cast card to Creature" << endl;
					continue; // Skip to the next card
				}
			} else {
				cout << "Error: Non-creature card found on battlefield" << endl;
				continue; // Skip to the next card
			}
		}
	}
	//return;
}

void mainPhase(Player& player) {
    cout << player.getName() << " main phase" << endl;
    while (true) {
        cout << "Enter card index to play or (9) to see your hand: ";
        int index;
        cin >> index;
        if (index == 9) {
            player.showHand();
            continue; 
        }
		if (index >= 0 && index < player.getHandCount()) {
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

        // Debugging: Print health after combat phases
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