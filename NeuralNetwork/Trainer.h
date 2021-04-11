#pragma once

#include "Game.h"
#include "Agent.h"
#include "WeightsAndBiases.h"

class Trainer {

	private:
		Game game;
		Agent agent;
		int batchSize = 10;
		double learningRate = 0.1;

	public:
		Trainer(const Game& game, const Agent& agent);
		void setBatchSize(int batchSize);
		void runBatches(int numBatches);
		double test(int numGames);

	private:
		void runBatch();
		WeightsAndBiases runEpisode();

};