#include "pch.h"
#include "Agent.h"

Agent::Agent() :
	randomEngine((std::random_device())()),
	randomDistribution(0, 1),
	pNetwork(new FeedforwardNetwork{ 2, 3, 1 })
{

}

Agent::Agent(const std::shared_ptr<FeedforwardNetwork>& pNetwork) : pNetwork(pNetwork) {

}

Game::Action Agent::getAction(const GameState& state) {
	FeedforwardOutput output = getDistribution(state);
	return chooseAction(output.getOutput());
}

FeedforwardOutput Agent::getDistribution(const GameState& state) {
	Vector input = {
		state.getHasKey() ? 1.0 : 0.0,
		static_cast<double>(state.getPlayerPosition())
	};
	return pNetwork->feedforwardGetOutput(input);
}

Game::Action Agent::chooseAction(const Vector& distribution) {
	bool goRight = randomDistribution(randomEngine) < distribution.getEntry(0);
	return goRight ? Game::Action::RIGHT : Game::Action::LEFT;
}

std::shared_ptr<FeedforwardNetwork> Agent::getNetwork() {
	return pNetwork;
}
