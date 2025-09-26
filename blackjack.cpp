#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

class Blackjack {
private:
    vector<int> deck;
    vector<int> dealer;
    vector<int> player;

    void shuffle_deck() {
        random_shuffle(deck.begin(), deck.end());
    }

    void draw_card(vector<int>& hand) {
        hand.push_back(deck.back());
        deck.pop_back();
        tuz(hand);
    }

    void tuz(vector<int>& hand) {
        while (sum_hand(hand) > 21 && find(hand.begin(), hand.end(), 11) != hand.end()) {
            *find(hand.begin(), hand.end(), 11) = 1;
        }
    }

    int sum_hand(const vector<int>& hand) const {
        int sum = 0;
        for (int card : hand) {
            sum += card;
        }
        return sum;
    }

public:
    Blackjack() {
        deck = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
        shuffle_deck();
        draw_card(dealer);
        draw_card(dealer);
        draw_card(player);
    }

    void player_move() {
        draw_card(player);
    }

    void dealer_move() {
        while (sum_hand(dealer) < 17) {
            draw_card(dealer);
        }
    }

    string check() {
        int player_sum = sum_hand(player);
        int dealer_sum = sum_hand(dealer);

        if (player_sum > 21) {
            return "You busted, you lose!";
        }
        else if (dealer_sum > 21 || player_sum > dealer_sum) {
            return "You win!";
        }
        else if (dealer_sum == player_sum) {
            return "It's a tie!";
        }
        else {
            return "You lose!";
        }
    }

    int get_player_sum() const {
        return sum_hand(player);
    }

    int get_dealer_sum() const {
        return sum_hand(dealer);
    }

    const vector<int>& get_player_hand() const {
        return player;
    }

    const vector<int>& get_dealer_hand() const {
        return dealer;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    Blackjack game;

    cout << "You drew a card: " << game.get_player_hand().back() << ", your score: " << game.get_player_sum() << endl;
    cout << "Dealer's card: " << game.get_dealer_hand().front() << endl;

    string response;
    while (game.get_player_sum() < 21) {
        cout << "Do you want to draw another card? yes/no: ";
        cin >> response;
        if (response == "no") break;

        game.player_move();
        cout << "You drew a card: " << game.get_player_hand().back() << ", your cards: ";
        for (int card : game.get_player_hand()) cout << card << " ";
        cout << ", your score: " << game.get_player_sum() << " points." << endl;
        if (game.get_player_sum() == 21) break;
        else if (game.get_player_sum() >= 21) break;
    }

    game.dealer_move();
    cout << game.check() << endl;
    cout << "Dealer's score: " << game.get_dealer_sum() << ", dealer's cards: ";
    for (int card : game.get_dealer_hand()) cout << card << " ";
    cout << endl;

    return 0;
}

