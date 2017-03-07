#include <iostream>
#include <vector>
#include <array>
using namespace std;

class PathFinder
{
	struct position {
		int x, y;
		position(int x, int y) : x(x), y(y) {}
		position(const position& rhs) = default;
		position& operator=(const position& rhs) = default;
		bool operator==(const position& rhs) const {
			return this->x == rhs.x and this->y == rhs.y;
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
	static const position Uminus; 
	static const array<position, 3> Rrules; 
	static const array<position, 3> Rminusrules; 
	static const array<position, 3> Urules; 
	static const array<position, 3> Uminusrules; 

public:
	PathFinder()
	: pathCount(0), initPos(2, 1), destPos(7, 4)
	{}

	void findAllPath()
	{
		const auto initChoice = Uminusrules;
		for (const auto& initDirection : initChoice) {
			vector<position> pathRecord {initPos, initPos + initDirection};
			findPath(initPos + initDirection, initDirection, pathRecord);
		}
		cout << pathCount << "\n";
	}

	void findPath(position currPos, position prevMov, vector<position> pathRecord)
	{
		if (currPos == destPos) {
			++pathCount;
			return;
		}

		if (prevMov == R) {
			for (const auto& nextMov : Rrules)
				if (isInBoundAndNoOverlapped(currPos, nextMov, pathRecord)) {
					pathRecord.push_back(currPos + nextMov);
					findPath(currPos + nextMov, nextMov, pathRecord);
				}
		}
		else if (prevMov == Rminus) {
			for (const auto& nextMov : Rminusrules)
				if (isInBoundAndNoOverlapped(currPos, nextMov, pathRecord)) {
					pathRecord.push_back(currPos + nextMov);
					findPath(currPos + nextMov, nextMov, pathRecord);
				}
		}
		else if (prevMov == U) {
			for (const auto& nextMov : Urules)
				if (isInBoundAndNoOverlapped(currPos, nextMov, pathRecord)) {
					pathRecord.push_back(currPos + nextMov);
					findPath(currPos + nextMov, nextMov, pathRecord);
				}
		}
		else if (prevMov == Uminus) {
			for (const auto& nextMov : Uminusrules)
				if (isInBoundAndNoOverlapped(currPos, nextMov, pathRecord)) {
					pathRecord.push_back(currPos + nextMov);
					findPath(currPos + nextMov, nextMov, pathRecord);
				}	
		}
	}
	
	bool isInBoundAndNoOverlapped(position currPos, position nextMov, const vector<position> pathRecord)
	{
		if (!((currPos.x + nextMov.x <= 7 and currPos.x + nextMov.x >= 0)
		   and (currPos.y + nextMov.y <= 4 and currPos.y + nextMov.y >= 0)))
			return false;
		for (auto& prevPath : pathRecord)
			if (prevPath == currPos + nextMov)
				return false;
		return true;
	}
};

const PathFinder::position PathFinder::U = position(0, 1);
const PathFinder::position PathFinder::R = position(1, 0);
const PathFinder::position PathFinder::Rminus = position(-1, 0);
const PathFinder::position PathFinder::Uminus = position(0, -1);
const array<PathFinder::position, 3> PathFinder::Rrules = {R, U, Uminus};
const array<PathFinder::position, 3> PathFinder::Rminusrules = {Rminus, U, Uminus};
const array<PathFinder::position, 3> PathFinder::Urules = {R, Rminus, U};
const array<PathFinder::position, 3> PathFinder::Uminusrules = {R, Rminus, Uminus};


int main()
{
	PathFinder sol;
	sol.findAllPath();

	return 0;
}
