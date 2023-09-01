#pragma once
class InGamePlaying
{
public:
	enum MOVING_EFFECT_MODE {
		MOVING_EFFECT_MODE_NOTHING = 0xFF, // default value, if 0xFF then no plus too
		MOVING_EFFECT_MODE_NORMAL = 1,
		MOVING_EFFECT_MODE_FIVE_COLORS = 2,
		MOVING_EFFECT_MODE_BLACK_EFFECT = 3
	};
	void TogglePlayerMovingEffectMode();
	void UpdateMovingEffectAndPlusEffect();
	void SetYourPlayerIndex(int index);
private:
	MOVING_EFFECT_MODE _currentMode = MOVING_EFFECT_MODE_NOTHING;	
	int _playerIndex = 0;
	int _yourPlayerIndex = -1;
};

