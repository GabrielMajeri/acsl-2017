#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

struct board
{
    bool a[8][8];
};

// Reads to hex chars and builds a line.
void readLine(board& b, int line, std::ifstream& in)
{
	line = 7 - line;

	char num[3];
	in.read(num, 2);
	num[2] = 0;


	std::stringstream ss;
	ss << std::hex << num;

	int x;
	ss >> x;

	// Convert to binary to get lights.
	int bit = 7;

	while (x)
	{
		if (x & 1)
			b.a[line][bit] = true;

		--bit;


		x >>= 1;
	}
}

std::ifstream in("lights.in");

void cleanBoard(board& b)
{
	std::memset(b.a, 0, sizeof(b.a));
}

board readBoard()
{
	board b;

	cleanBoard(b);

	for (int i = 0; i < 8; i += 2)
	{
		readLine(b, i, in);
		readLine(b, i + 1, in);

		// Space.
		in.get();
	}

	return b;
}

board findDiff(board& a, board& b)
{
    board r;

    cleanBoard(r);

    for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (a.a[i][j] != b.a[i][j])
				r.a[i][j] = true;

    return r;
}

std::ofstream out("lights.out");

int main()
{
	board lastBoard = readBoard();

	for (int i = 0; i < 5; ++i)
	{
		board newBoard = readBoard();

		board diff = findDiff(lastBoard, newBoard);

		int minx = 99, maxx = -1, miny = 99, maxy = -1;

		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
			{
				if (diff.a[i][j])
				{
					int x = 7 - i;
					int y = j;

					if (x < minx)
						minx = x;
					if (x > maxx)
						maxx = x;

					if (y < miny)
						miny = y;
					if (y > maxy)
						maxy = y;
				}
			}

		++minx;
		++maxx;
		++miny;
		++maxy;

		if (minx == 1)
			minx -= 5 - maxx;

		if (maxx == 8)
			maxx += minx - 4;

		if (miny == 1)
			miny -= 4 - maxy + 1;

		if (maxy == 8)
			maxy += miny - 4;

		int foundX = (minx + maxx) / 2, foundY = (miny + maxy) / 2;

		out << foundX << foundY << '\n';

		lastBoard = newBoard;
	}
}
