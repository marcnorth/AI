#include "pch.h"
#include "Trainer.h"
#include "BackPropagator.h"

Trainer::Trainer(const Game& game, const Agent& agent) :
	game(game), agent(agent)
{

}

void Trainer::setBatchSize(int batchSize) {
	this->batchSize = batchSize;
}

void Trainer::runBatches(int numBatches) {
	for (int i = 0; i < numBatches; i++) {
		runBatch();
	}
}

void Trainer::runBatch() {
	WeightsAndBiases gradients(agent.getNetwork()->getShape());
	for (int i = 0; i < batchSize; i++) {
		WeightsAndBiases episodeGradients = runEpisode();
		gradients = gradients + episodeGradients;
	}
	WeightsAndBiases changes = gradients * (-learningRate);
	agent.getNetwork()->shiftWeights(changes.weights);
	agent.getNetwork()->shiftBiases(changes.biases);
}

WeightsAndBiases Trainer::runEpisode() {
	game.reset();
	WeightsAndBiases gradientSum{agent.getNetwork()->getShape()};
	BackPropagator backPropagator(*agent.getNetwork());
	while (!game.getIsFinished()) {
		FeedforwardOutput output = agent.getDistribution(game.getState());
		Game::Action action = agent.chooseAction(output.getOutput());
		Vector fakeExpectedOutput = { action == Game::Action::RIGHT ? 1.0 : 0.0 };
		game.doAction(action);
		gradientSum = gradientSum + backPropagator.calculateWeightAndBiasGradients({output, fakeExpectedOutput});
	}
	int reward = game.getReward();
	return gradientSum * (static_cast<double>(reward) / 10);
}

double Trainer::test(int numGames) {
	int totalReward = 0;
	for (int i = 0; i < numGames; i++) {
		game.reset();
		while (!game.getIsFinished()) {
			Game::Action action = agent.getAction(game.getState());
			game.doAction(action);
		}
		totalReward += game.getReward();
	}
	return static_cast<double>(totalReward) / numGames;
}