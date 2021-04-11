#pragma once

#include <vector>
#include <random>
#include <memory>
#include "FeedforwardNetwork.h"
#include "Game.h"

class Agent {

	public:
		Agent();
		Agent(const std::shared_ptr<FeedforwardNetwork>&);
		Game::Action getAction(const GameState& state);
		FeedforwardOutput getDistribution(const GameState& state);
		Game::Action chooseAction(const Vector& distribution);
		std::shared_ptr<FeedforwardNetwork> getNetwork();

	private:
		std::default_random_engine randomEngine;
		std::uniform_real_distribution<float> randomDistribution;
		std::shared_ptr<FeedforwardNetwork> pNetwork;

};