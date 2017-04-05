#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream in("agram.in");
ofstream out("agram.out");

struct Card
{
	char value;
	char suit;
};

Card opCard;
vector<Card> cards;

Card readOneCard()
{
	Card c;

	char val;
	in >> val;

	if(val >= '2' && val <= '9')
		c.value = (val - '0');
	else if(val == 'A')
		c.value = 1;
	else if(val == 'T')
		c.value = 10;
	else if(val == 'J')
		c.value = 12;
	else if(val == 'Q')
		c.value = 13;
	else if(val == 'K')
		c.value = 14;

	in >> c.suit;

	return c;
}

void readCards()
{
	opCard = readOneCard();

	for(size_t i = 0; i < 5; ++i)
	{
		in.ignore(2);

		cards.push_back(readOneCard());
	}
}

void printCard(Card c)
{
	char value;

	if(c.value > 1 && c.value < 10)
		value = c.value + '0';
	else if(c.value == 1)
		value = 'A';
	else if(c.value == 10)
		value = 'T';
	else if(c.value == 12)
		value = 'J';
	else if(c.value == 13)
		value = 'Q';
	else if(c.value == 14)
		value = 'K';

	out << value << c.suit;
}

vector<Card> findCardsOfSuit(char suit)
{
	vector<Card> r;

	for(size_t i = 0; i < cards.size(); ++i)
		if(cards[i].suit == suit)
			r.push_back(cards[i]);

	return r;
}

bool compareCards(Card a, Card b)
{
	if(a.value < b.value)
		return true;
	else if(a.value > b.value)
		return false;
	else
		return a.suit < b.suit;
}

int main()
{
	readCards();

	sort(cards.begin(), cards.end(), compareCards);

    vector<Card> suitCards = findCardsOfSuit(opCard.suit);

    // If there are cards of same suit.
    if(!suitCards.empty())
	{
        size_t i = 0;
        while(i < suitCards.size() && suitCards[i].value < opCard.value)
			++i;

		// Found a good same-suit card.
		if(i < suitCards.size())
		{
			printCard(suitCards[i]);
		}
		else
		{
			// Play lowest card.
            printCard(suitCards[0]);
		}
	}
	// If there are no cards of same suit.
	else
        // Already sorted in clubs < diamonds < hearts < spades order.
        // Just print the lowest one.
        printCard(cards[0]);

}
