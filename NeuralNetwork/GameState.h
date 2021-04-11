#pragma once
class GameState {

	public:
		GameState(bool hasKey, int playerPosition) :
			hasKey(hasKey),
			playerPosition(playerPosition)
		{
			
		}

		bool getHasKey() const {
			return hasKey;
		}

		int getPlayerPosition() const {
			return playerPosition;
		}

	private:
		bool hasKey;
		int playerPosition;

};