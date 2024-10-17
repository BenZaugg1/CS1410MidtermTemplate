#include <iostream>
#include "header.h" 

using namespace std;

void drawPhase(Player& player){
    // cout << player.getName() << " draw phase" << endl;
                                //Name, health, damage, mannaCost
    player.drawCard(new Creature("Goblin", 1, 1, 1));

    //TODO ADD SEVERAL DIFFERENT VARIETY OF CARDS

}

void combatPhase(Player& attacker, Player& defender){
    cout << "Combat phase" << endl;
    for (Card* card : attacker.battlefield) {
        if (card->typeofCard == cardType::CREATURE) {
            Creature* creature = dynamic_cast<Creature*>(card);
            cout << attacker.getName() << "'s " << creature->name << " attacks!" << endl;
            defender.health -= creature->damage;
            cout << defender.getName() << " takes " << creature->damage << " damage, life is now " << defender.health << endl;
        }
        //TODO ADD MANA, SPELLS AND, ENCHANTMENTS
        if (card->typeofCard == cardType::MANNA) {
            cout << "Manna card played" << endl;
            //add manna to manna count
        }
        if (card->typeofCard == cardType::SPELL) {
            cout << "Spell card played" << endl;
            //play spell

        }
        else {
            cout << "Invalid card type" << endl;
        }
    }
}


int main(){
    //Create two players
    cout << "Enter player 1 name: ";
    string player1name;
    cin >> player1name;

    cout << "Enter player 2 name: ";
    string player2name;
    cin >> player2name;

    Player player1(player1name);
    Player player2(player2name);

    //Draw cards for each player
    cout << "Drawing cards" << endl;
    for (int i = 0; i < 7; i++) {
        drawPhase(player1);
        drawPhase(player2);
    }
    player1.showHand();
    player2.showHand();

    //TODO ADD A LOOP FOR THE GAME
    do {
        combatPhase(player1, player2);
        combatPhase(player2, player1);
    }
    while (player1.health > 0 && player2.health > 0);
    //TODO ADD A WAY TO END THE GAME
    if (player1.health <= 0) {
        cout << player2.getName() << " wins!" << endl;
    }
    else if (player2.health <= 0) {
        cout << player1.getName() << " wins!" << endl;
    }
    else if (player1.health <= 0 && player2.health <= 0) {
        cout << "Game ended in a draw" << endl;
    }
    else {
        cout << "Game ended in an error" << endl;
    }

    //TODO add user input to the game

    combatPhase(player1, player2);

    return 0;
}