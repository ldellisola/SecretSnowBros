#pragma once
#include <cstdint>
#include <vector>
#include "../../MVC/ScoreObserver.h"

class Score
{
public:
	Score(uint16_t playerID_)
	{
		this->playerID = playerID_;
	};
	virtual ~Score(){}
	uint16_t getActualScore() { return this->actualScore; };
	void update(uint16_t addScore) {
		this->actualScore += addScore;
	}

	Score& operator+=( uint16_t add) {
		this->actualScore += add;
		return *this;
	}



protected:
	uint16_t actualScore;
	uint16_t playerID;
};

