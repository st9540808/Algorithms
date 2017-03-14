#include <iostream>
#include <array>
using namespace std;

class PathFinder
{
	struct position {
		int x, y;
		position(int x, int y) : x(x), y(y) {}
		position(const position& rhs) = default;
		position& operator=(const position& rhs) = default;
		bool operator!=(const position& rhs) const {
			return this->x != rhs.x or this->y != rhs.y;
		}
		bool operator==(const position& rhs) const {
			return !(this->operator!=(rhs));
		}
		position operator+(const position& rhs) const {
			position result(this->x + rhs.x, this->y + rhs.y);
			return result;
		}
	};

private:
	int pathCount;
	position initPos, destPos;
	static const position U; 
	static const position R; 
	static const position Rminus; 
	static const array<position, 2> Rrules; 
	static const array<position, 3> Rminusrules; 
	static const array<position, 3> Urules; 

public:
	PathFinder()
	: pathCount(0), initPos(2, 1), destPos(7, 4)
	{}

	void findAllPath()
	{
		const auto initChoice = Urules;
		for (const auto initDirection : initChoice)
			findPath(initPos + initDirection, initDirection);
		cout << pathCount << "\n";
	}

	void findPath(position currPos, position prevMov)
	{
		if (currPos == destPos) {
			pathCount++;
			return;
		}

		if (prevMov == R) {
			for (const auto nextMov : Rrules)
				if (isInBound(currPos, nextMov))
					findPath(currPos + nextMov, nextMov);
		}
		else if (prevMov == Rminus) {
			for (const auto nextMov : Rminusrules)
				if (isInBound(currPos, nextMov))
					findPath(currPos + nextMov, nextMov);
		}
		else if (prevMov == U) {
			for (const auto nextMov : Urules)
				if (isInBound(currPos, nextMov))
					findPath(currPos + nextMov, nextMov);
		}
	}
	
	inline bool isInBound(position currPos, position nextMov)
	{
		return (currPos.x + nextMov.x <= 7 and currPos.x + nextMov.x >= 0)
		   and (currPos.y + nextMov.y <= 4 and currPos.y + nextMov.y >= 0);
	}
};

const PathFinder::position PathFinder::U = position(0, 1);
const PathFinder::position PathFinder::R = position(1, 0);
const PathFinder::position PathFinder::Rminus = position(-1, 0);
const array<PathFinder::position, 2> PathFinder::Rrules = {R, U};
const array<PathFinder::position, 3> PathFinder::Rminusrules = {R, Rminus, U};
const array<PathFinder::position, 3> PathFinder::Urules = {R, Rminus, U};


int main()
{
	PathFinder sol;
	sol.findAllPath();

	return 0;
}
