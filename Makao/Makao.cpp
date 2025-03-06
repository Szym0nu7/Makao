#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

const int MAX_DECK_SIZE = 52;
const int PLAYER_COUNT = 3;
const int STARTING_CARDS = 5;

enum class Color : uint8_t
{
	Heart = 0, // kier
	Diamond, // karo
	Spade, // pik
	Club, // trefl

	Number
};

void Print(Color color)
{
	switch (color)
	{
	case Color::Heart:
		cout << "Heart";
		break;
	case Color::Diamond:
		cout << "Diamond";
		break;
	case Color::Spade:
		cout << "Spade";
		break;
	case Color::Club:
		cout << "Club";
		break;
	default:
		cout << "none";
	}
}

enum class Value : uint8_t
{
	Two = 0,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace,

	Number
};

void Print(Value value)
{
	switch (value)
	{
	case Value::Two:
		cout << "Two";
		break;
	case Value::Three:
		cout << "Three";
		break;
	case Value::Four:
		cout << "Four";
		break;
	case Value::Five:
		cout << "Five";
		break;
	case Value::Six:
		cout << "Six";
		break;
	case Value::Seven:
		cout << "Seven";
		break;
	case Value::Eight:
		cout << "Eight";
		break;
	case Value::Nine:
		cout << "Nine";
		break;
	case Value::Ten:
		cout << "Ten";
		break;
	case Value::Jack:
		cout << "Jack";
		break;
	case Value::Queen:
		cout << "Queen";
		break;
	case Value::King:
		cout << "King";
		break;
	case Value::Ace:
		cout << "Ace";
		break;
	default:
		cout << "none";
	}

}

enum class Action {
	play = 0,
	subsequentPlay,
	defencePlay,
	blockPlay,
	demandPlay,

	Number
};

class Card
{
public:
	friend class Deck;
	friend class Player;

	Card() = default;
	Card(Color color, Value value) : m_color(color), m_value(value) {}

	void PrintCard()
	{
		Print(m_value);
		cout << " of ";
		Print(m_color);
		cout << "s";
	}

	bool operator>(Card& otherCard) {
		if ((int)m_value == (int)otherCard.m_value + 1)return true;
		return false;
	}
	bool operator<(Card& otherCard) {
		if ((int)m_value == (int)otherCard.m_value - 1)return true;
		return false;
	}
	bool operator==(Card& otherCard) {
		if ((int)m_value == (int)otherCard.m_value)return true;
		return false;
	}

private:
	Color m_color = Color::Heart;
	Value m_value = Value::Two;
};

class Deck
{
public:
	friend class Deck;
	friend class Player;

	void Initialize()
	{
		int index = 0;
		for (int i = 0; i < (int)Color::Number; ++i)
		{
			for (int j = 0; j < (int)Value::Number; ++j)
			{
				m_cards[index].m_color = (Color)i;
				m_cards[index].m_value = (Value)j;
				++index;
			}
		}

		m_size = index;
	}

	void PrintCardOnTop() {
		m_cards[m_size - 1].PrintCard();
	}

	void Print() // Prints the whole deck
	{
		for (int i = 0; i < m_size; ++i)
		{
			cout << i + 1 << ". ";
			m_cards[i].PrintCard();
			cout << endl;
		}
	}

	void Sort() {
		for (int i = 0; i < m_size; i++) {
			
			for (int j = i; j < m_size; j++) {
				if (m_cards[i].m_value > m_cards[j].m_value
					|| (m_cards[i] == m_cards[j] && (int)m_cards[i].m_color < (int)m_cards[j].m_color))
						swap(m_cards[i], m_cards[j]);	
			}
		}
	}

	void Shuffle()
	{
		srand(time(NULL));

		for (int i = 0; i < m_size; ++i)
		{
			int index = rand() % m_size;
			swap(m_cards[i], m_cards[index]);
		}
	}

	bool checkForRefil(Deck& playedDeck, Deck& mainDeck) {
		if (mainDeck.m_size == 0) {
			if (playedDeck.m_size == 1)return false;
			//saves the top card
			Card temp = playedDeck.m_cards[playedDeck.m_size - 1];
			playedDeck.m_size--;
			int l = playedDeck.m_size;

			//deals cards
			for (int i = 0; i < l; ++i) { 
				mainDeck.m_cards[mainDeck.m_size] = playedDeck.m_cards[playedDeck.m_size - 1];
				mainDeck.m_size++;
				playedDeck.m_size--;
			}

			// puts the saved card back on top
			playedDeck.m_cards[playedDeck.m_size] = temp;
			playedDeck.m_size++;
			mainDeck.Shuffle();
		}
		return true;
	}
	
	void Deal(Deck& otherDeck, int num_of_cards, Deck& playedDeck, Deck& mainDeck)
	{
		for (int i = 0; i < num_of_cards; ++i) { //deals cards
			if (!checkForRefil(playedDeck, mainDeck))
				return;
			otherDeck.m_cards[otherDeck.m_size] = m_cards[m_size - 1];
			otherDeck.m_size++;
			m_size--;
		}
	}

	void removeEmptyCards(int takenCard) {
		for (int i = 0; i < m_size - takenCard; i++) {
			m_cards[takenCard + i] = m_cards[takenCard + i + 1];
		}
		
	} 


	void Play(Deck &playedDeck, int cardIndex, Deck& mainDeck) { //plays a specific card

		playedDeck.m_cards[playedDeck.m_size] = m_cards[cardIndex];
		playedDeck.m_size++;
		m_size--;
		removeEmptyCards(cardIndex);
		
	}

	int GetSize()
	{
		return m_size;
	}

private:
	Card m_cards[52];
	int m_size = 0;
};

class definitelyAnAdvancedAi {
public:
	bool inteligentDecisionMaking(int &card, Deck hand) {
		
	}
	int currentCheckedCard = 0;
};

class Player {
	friend class Game;
public:
	
	Player(Deck cards, string player_name, bool isABot, Deck& main, Deck& played,
		int& cardstodraw, int&turnstolose, Color& color, 
		Value& value, int& currentplayer)
		: Hand(cards), name(player_name), isBot(isABot), mainDeck(main), playedDeck(played), 
		cardsToDraw(cardstodraw), turnsToLose(turnstolose), currentColor(color),
		demandedCard(value), currentPlayer(currentplayer) {}
	
	void PrintDeck() {
		cout << "Your Hand:" << endl;
		Hand.Print();
	}

	bool checkForPlusCard(Card playedCard) {
		if (playedCard.m_value == Value::Two
			|| playedCard.m_value == Value::Three
			|| (playedCard.m_value == Value::King && (playedCard.m_color == Color::Heart || playedCard.m_color == Color::Spade)))
				return true;
		return false;
	}

	bool checkValidCard(Card playedCard, Action action, bool afterDraw = false) { //checks if the chosen card can be played
		Card topCard = playedDeck.m_cards[playedDeck.m_size-1];
		if(currentColor != Color::Number)topCard.m_color = currentColor;
		switch (action) {
		case Action::play:
			if (topCard.m_color == playedCard.m_color || topCard == playedCard 
				|| playedCard.m_value == Value::Queen || topCard.m_value == Value::Queen)
				return true;
			break;
		case Action::subsequentPlay:
			if ((playedCard.m_color == topCard.m_color && (playedCard < topCard || playedCard > topCard))
				|| playedCard == topCard
				|| (afterDraw && checkValidCard(playedCard, Action::play))
				|| playedCard.m_value == Value::Queen || topCard.m_value == Value::Queen)
				return true;
			break;
		case Action::defencePlay:
			if(checkValidCard(playedCard, Action::play) && checkForPlusCard(playedCard))
				return true;
		case Action::blockPlay:
			if (topCard == playedCard)
				return true;
		case Action::demandPlay:
			if (demandedCard == playedCard.m_value)
				return true;
			break;
		}
		
		return false;
	}

	bool checkCardRules(Card card) {
		string choice = "";
		int numberChoice = 1;
		switch (card.m_value) {
		case Value::Two:
			cardsToDraw += 2;
			break;
		case Value::Three:
			cardsToDraw += 3;
			break;
		case Value::Four:
			//block turn
			turnsToLose++;
			break;
		case Value::Jack:
			if (!isBot) {
				while (true) {
					cout << "Choose the card to demand (input index):" << endl
						<< "1. Five" << endl
						<< "2. Six" << endl
						<< "3. Seven" << endl
						<< "4. Eight" << endl
						<< "5. Nine" << endl
						<< "6. Ten" << endl;
					getline(cin, choice);

					bool isNumber = true;
					for (int i = 0; i < choice.length(); i++) {
						if (int(choice[i]) < 48 || int(choice[i]) > 56)isNumber = false;
					}
					if (isNumber) {
						numberChoice = stoi(choice);
						if (numberChoice > 0 && numberChoice < 7) {
							break;
						}
					}
					cout << "This is not a valid card" << endl;
				};
			}
			else {
				srand(time(NULL));
				numberChoice = rand() % 7;
			}
				switch (numberChoice) {
				case 1:
					demandedCard = Value::Five;
					break;
				case 2:
					demandedCard = Value::Six;
					break;
				case 3:
					demandedCard = Value::Seven;
					break;
				case 4:
					demandedCard = Value::Eight;
					break;
				case 5:
					demandedCard = Value::Nine;
					break;
				case 6:
					demandedCard = Value::Ten;
					break;
				}
				if (isBot) {
					cout << name << " has chosen ";
					Print(demandedCard);
					if (demandedCard == Value::Six) cout << "e";
					cout << "s" << endl;
				}
				demandingPlayer = currentPlayer;
			break;
		case Value::Queen:
			// can be put on anything and anything can be put on it
			break;
		case Value::King:
			if(card.m_color == Color::Heart || card.m_color == Color::Spade)cardsToDraw += 5;
			else return false;
			break;
		case Value::Ace:
			if (!isBot) {
				while (true) {
					cout << "Choose current suit(input index):" << endl
						<< "1. Heart" << endl
						<< "2. Diamond" << endl
						<< "3. Spade" << endl
						<< "4. Club" << endl;
					getline(cin,choice);

					bool isNumber = true;
					for (int i = 0; i < choice.length(); i++) {
						if (int(choice[i]) < 48 || int(choice[i]) > 56)isNumber = false;
					}
					if (isNumber) {
						numberChoice = stoi(choice);
						if (numberChoice > 0 && numberChoice < 5) {
							break;
						}
					}
				};
			}
			else {
				srand(time(NULL));
				numberChoice = rand() % 5;
			}
			switch (numberChoice) {
			case 1:
				currentColor = Color::Heart;
				break;
			case 2:
				currentColor = Color::Diamond;
				break;
			case 3:
				currentColor = Color::Spade;
				break;
			case 4:
				currentColor = Color::Club;
				break;
			}

			break;
		default:
			return false;
			break;
		}
		return true;
	}

	void playCard(Action action, bool afterDraw = false) {	
		string choice = "";
		int card = 0;
		Card chosenCard;
		Hand.Sort();;
		cout << endl << "Current card: ";
		playedDeck.PrintCardOnTop();
		cout << endl;
		if (currentColor != Color::Number) {
			cout << "Current suit: ";
			Print(currentColor);
			cout << endl;
		}

		if(!isBot)PrintDeck();// print hand

		if (lostTurns != 0 &&
			(action != Action::defencePlay || action != Action::blockPlay || action != Action::demandPlay)) {
			lostTurns--;
			if (!isBot)cout << "You lost your turn";
			else cout << name << " has lost his turn";
			cout << endl << "Turns left: " << lostTurns << endl;
			return;
		}

		//choice loop
		if (!isBot)while (true) {
			card = 0;

			//Display message

			switch (action) {
			case Action::play:
				cout << "Choose a card to play (input index) or type 'draw' to draw: ";
				break;
			case Action::subsequentPlay:
				cout << "Choose a card to play (input index) or type 'end' to end your turn: ";
				break;
			case Action::defencePlay:
				cout << "Choose a card to deflect (input index) or type 'give up' to draw " << cardsToDraw << " cards: ";
				break;
			case Action::blockPlay:
				cout << "Choose a card to deflect (input index) or type 'give up' to lose " << turnsToLose << " turn"; if (turnsToLose > 1)cout << "s"; cout << ": ";
				break;
			case Action::demandPlay:
				cout << "Play a ";
				Print(demandedCard);
				cout << " (input index) or type 'give up' to draw a card: ";
			}
			getline(cin, choice);
			
			//converts choice to lowercase
			for (int i = 0; i < choice.length(); i++) {
				choice[i] = tolower(choice[i]);
			}

			// checks user input

			if ((choice == "draw" && action == Action::play)
				|| (choice == "end" && action == Action::subsequentPlay)
				|| (choice == "give up" && (action == Action::defencePlay || action == Action::blockPlay || action == Action::demandPlay)))
				break;

			// checks if the input is a number
			bool isNumber = true;
			for (int i = 0; i < choice.length(); i++) {
				if (int(choice[i]) < 48 || int(choice[i]) > 56)isNumber = false;
			}

			if (isNumber) {
				card = stoi(choice);
				//checks if input is a valid card and can be played
				if (card > 0 && card <= Hand.GetSize()) {
					chosenCard = Hand.m_cards[card - 1];
					if (checkValidCard(chosenCard, action, afterDraw)) break;
				}
			}
			cout << endl << "This is not a valid card" << endl;
		}
		else for (int i = 1; i <= Hand.GetSize(); i++) {
			chosenCard = Hand.m_cards[i-1];
			if (checkValidCard(chosenCard, action, afterDraw)) {
				card = i;
				break;
			}
		}
		
		if (card != 0) {
			if (!isBot)cout << "Played card: ";
			else cout << name << " has played: ";
			chosenCard.PrintCard();
			cout << endl;
			Hand.Play(playedDeck, card - 1,mainDeck);
			currentColor = Color::Number;
			if (isBot) cout << name << " has " << Hand.GetSize() << " cards left" << endl;
			if(checkCardRules(chosenCard))action = Action::defencePlay;
			switch (action) {
				case Action::play:
				case Action::subsequentPlay:
					playCard(Action::subsequentPlay);
					break;
				case Action::defencePlay:
				case Action::blockPlay:
					break;
				case Action::demandPlay:
					if (demandingPlayer == currentPlayer) {
						demandedCard = Value::Number;
						demandingPlayer = -1;
					}
					break;
			}
		}
		else switch (action) {
		case Action::play:
			//draw card
			if (!isBot) cout << "You have drawn one card" << endl;
			else cout << name << " has drawn one card" << endl;
			mainDeck.Deal(Hand, 1, playedDeck, mainDeck);
			if (isBot) cout << name << " has " << Hand.GetSize() << " cards left" << endl;
			playCard(Action::subsequentPlay, true);
			break;
		case Action::subsequentPlay:
			//nothin
			if (isBot) cout << name << " has " << Hand.GetSize() << " cards left" << endl;
			break;
		case Action::defencePlay:
			if (!isBot) cout << "You have drawn " << cardsToDraw << " cards" << endl;
			else cout << name << " has drawn " << cardsToDraw << " cards" << endl;
			mainDeck.Deal(Hand, cardsToDraw, playedDeck, mainDeck);
			if (isBot) cout << name << " has " << Hand.GetSize() << " cards left" << endl;
			cardsToDraw = 0;
			playCard(Action::subsequentPlay, true);
			break;
		case Action::blockPlay:
			if (!isBot) cout << "You have lost a turn" << endl;
			else cout << name << " has lost a turn" << endl;
			lostTurns = turnsToLose - 1;
			if(lostTurns != 0)cout << "Turns left: " << lostTurns << endl;
			turnsToLose = 0;
			if (isBot) cout << name << " has " << Hand.GetSize() << " cards left" << endl;
			break;
		case Action::demandPlay:
			if (!isBot) cout << "You have drawn one card" << endl;
			else cout << name << " has drawn one card" << endl;
			mainDeck.Deal(Hand, 1, playedDeck, mainDeck);
			if (isBot) cout << name << " has " << Hand.GetSize() << " cards left" << endl;
			if (demandingPlayer == currentPlayer) {
				demandedCard = Value::Number;
				demandingPlayer = -1;
			}
			break;
		}

	}
private:
	Deck& mainDeck;
	Deck& playedDeck;
	int& cardsToDraw;
	int& turnsToLose;
	Color& currentColor;
	Value& demandedCard;
	int demandingPlayer = -1;
	int& currentPlayer;
	int lostTurns = 0;
	bool isBot = false;
	definitelyAnAdvancedAi myIq;
	string name;
	Deck Hand;
};

class Game {
public:
	friend class Player;

	void PrintRules() {
		cout 
			<< "Macau Rules" << endl
			<< endl
			<< "1. Macau is played with a 52 card deck." << endl
			<< "2. Each player is dealt 5 cards each while one card is put in the discard card." << endl
			<< "3. In their turn, a player first puts a card of the same suit or value as the one on top of the" << endl
			<< "   discard pile, or draws a card from the deck." << endl
			<< "4. Then the player can play cards in runs. Once they're done, the next player takes a turn." << endl
			<< "5. A run is when one playes cards where each consecutive card is either of the same value as the" << endl
			<< "   one before it, or of the same suit and either of one step lower or one step higher value." << endl
			<< "6. Action cards end a players turn." << endl
			<< "7. Each action card has a different effect." << endl
			<< "  Two - The next player draws two cards" << endl
			<< "  Three - The next player draws three cards" << endl
			<< "  Four - The next player loses a turn" << endl
			<< "  Jack - The current player choses a non-action card. Then the next player must either play that" << endl
			<< "         card or draw one card from the deck. This continues until all players including the one that" << endl
			<< "         played a jack either plays or draws a card." << endl
			<< "  Queen - A queen can be placed on any card and any card can be placed on a queen. No matter the" << endl
			<< "          suit." << endl
			<< "  King of Hears or Spades - The next player draws five cards" << endl
			<< "  Ace - Choose a suit. For the purposes of playing the next card this ace is treated as of the" << endl
			<< "        chosen suit." << endl
			<< "8. Twos, Threes and action Kings can be deflected onto the next player. To do so, the affected" << endl
			<< "   player must play another Two, Three or an action King of the same suit or value as the one affecting" << endl
			<< "   them. The next player must take a sum of all the previous plus cards." << endl
			<< "9. Fours can also be delfected. To do so the affected player must play another four. The next player" << endl
			<< "   loses turns equal to the sum of all previous fours." << endl
			<< "10. The game ends, when one player has no more cards in their hand." << endl
			<< endl
			;
	}

	void Initialize(){
		//Initialize main deck
		m_Deck.Initialize();
		m_Deck.Shuffle();

		// Initialize Players

		for (int i = 0; i < PLAYER_COUNT; i++) {

			Deck hand;
			Player player(hand, "Player " + to_string(i+1), true, m_Deck, played, cardsToDraw, turnsToLose, currentColor, demandedCard, currentPlayer);
			m_Deck.Deal(player.Hand, STARTING_CARDS, played, m_Deck);
			players.push_back(player);
		}
		players[0].isBot = false;

		//Initialize played deck
		m_Deck.Deal(played, 1, played, m_Deck);

		//Print Rules
		PrintRules();
	}

	void nextPlayer() {
		if (currentPlayer != PLAYER_COUNT - 1) currentPlayer++;
		else currentPlayer = 0;
	}
	bool checkWin() {
		if (players[currentPlayer].Hand.GetSize() == 0) return true;
		return false;

	}
	void playerTurn() {
		
		cout << endl << endl << "Current player: " << players[currentPlayer].name << endl;
		
		if(cardsToDraw != 0)players[currentPlayer].playCard(Action::defencePlay);
		else if (turnsToLose != 0)players[currentPlayer].playCard(Action::blockPlay);
		else if(demandedCard != Value::Number)players[currentPlayer].playCard(Action::demandPlay);
		else players[currentPlayer].playCard(Action::play);

		if (!players[currentPlayer].isBot) cout << "You have ended your turn" << endl;
		else cout << players[currentPlayer].name << " has ended his turn" << endl;
	}
	void gameLoop() {
		while (true) {
			playerTurn();
			if (checkWin())break;
			nextPlayer();
		}
		 cout << endl << players[currentPlayer].name << " has just won" << endl;
	}
private:
	Deck m_Deck;
	Deck played;
	bool isAttacked = false;
	vector<Player> players;
	int currentPlayer = 0;
	int cardsToDraw = 0;
	int turnsToLose = 0;
	Color currentColor = Color::Number;
	Value demandedCard = Value::Number;
};

int main()
{
	Game Makao;

	Makao.Initialize();
	Makao.gameLoop();

	return 0;
}