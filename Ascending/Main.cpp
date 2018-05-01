#include <fstream>
#include <string>
#include <deque>

using namespace std;

ofstream out("ascending.out");

/// Compares two strings which hold decimal numbers.
int compare(const string& a, const string& b)
{
    if (a.size() > b.size())
		return 1;

	if (a.size() < b.size())
		return -1;

    return a.compare(b);
}


/// True = LTR
/// False = RTL
char getNextDigit(deque<char>& dq, bool direction)
{
	char c;

	if (direction)
	{
		c = dq.front();
		dq.pop_front();
	}
	else
	{
		c = dq.back();
		dq.pop_back();
	}
	return c;
}

/// Use a deque to store the characters.
void solve(deque<char> str)
{
	string last = "0";
	bool direction = true;

	while (!str.empty())
	{
		string formed;

		// LTR
		if (direction)
		{
			// Skip leading zeroes.
			while (!str.empty() && str.front() == '0')
				str.pop_front();

			// Nothing left but zeroes.
			if (str.empty())
				return;

            formed = getNextDigit(str, direction);

            while (compare(formed, last) <= 0 && !str.empty())
				formed += getNextDigit(str, direction);

			// Unable to form a bigger number.
			if (compare(formed, last) <= 0)
				return;

			last = formed;

			out << formed << ' ';
		}
		// RTL
		else
		{
			while (!str.empty() && str.back() == '0')
				str.pop_back();

			if (str.empty())
				return;

            formed = getNextDigit(str, direction);

            while (compare(formed, last) <= 0 && !str.empty())
				formed += getNextDigit(str, direction);

            if (compare(formed, last) <= 0)
				return;

			last = formed;

			out << formed << ' ';
		}

		direction = !direction;
	}

}

int main()
{
	ifstream in("ascending.in");
	string line;

	for (int i = 0; i < 5; ++i)
	{
		in >> line;

		deque<char> str(line.begin(), line.end());

		solve(str);
		out << '\n';
	}
}
