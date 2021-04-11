#pragma once

#include "GameState.h"

class Game {

	public:
		enum class Action {
			LEFT,
			RIGHT
		};

		Game();
		void reset();
		GameState getState();
		void doAction(const Action);
		int getReward();
		bool getIsFinished();

	private:
		double reward;
		bool hasKey;
		int playerPosition;
		bool isFinished;

};