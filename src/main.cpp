#include <iostream>
#include "header.h" 

using namespace std;

void drawPhase(Player& player){
    cout << player.getName() << " draw phase" << endl;
                                //Name, health, damage, mannaCost
    player.drawCard(new Creature("Goblin", 1, 1, 1));

    //TODO ADD SEVERAL DIFFERENT VARIETY OF CARDS

}

void combatPhase(Player& attacker, Player& defender){
    cout << "Combat phase" << endl;
    for (Card* card : attacker.battlefield) {
        if (card->typeofCard == cardType::CREATURE) {
            Creature* creature = dynamic_cast<Creature*>(card);
            std::cout << attacker.getName() << "'s " << creature->name << " attacks!" << std::endl;
            defender.health -= creature->damage;
            cout << defender.getName() << " takes " << creature->damage << " damage, life is now " << defender.health << endl;
        }
        //TODO ADD MANA, SPELLS AND, ENCHANTMENTS
    }
}


int main(){
    //Create two players
    Player player1("Player 1");
    Player player2("Player 2");

    //Draw cards for each player
    for (int i = 0; i < 7; i++) {
        drawPhase(player1);
        drawPhase(player2);
    }

    //TODO ADD A LOOP FOR THE GAME
    //TODO ADD A WAY TO END THE GAME
    //TODO add user input to the game

    combatPhase(player1, player2);

    return 0;
}