#include "pch.h"
#include "Game.h"

Game::Game() {
	reset();
}

void Game::reset() {
	hasKey = false;
	isFinished = false;
	playerPosition = 1;
}

bool Game::getIsFinished() {
	return isFinished;
}

GameState Game::getState() {
	return GameState(hasKey, playerPosition);
}

void Game::doAction(const Action action) {
	if (isFinished) {
		return;
	}
	playerPosition += action == Game::Action::LEFT ? -1 : 1;
	if (playerPosition == -1 || playerPosition == 2) {
		isFinished = true;
	}
	if (playerPosition == 0) {
		hasKey = true;
	}
}

int Game::getReward() {
	bool atExit = playerPosition == 2;
	if (hasKey && atExit) {
		return 10;
	}
	else if (atExit) {
		return 6;
	}
	else {
		return -7;
	}
}