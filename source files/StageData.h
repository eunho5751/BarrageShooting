#pragma once

struct EnemyData;

struct StageData
{
	typedef tuple<const EnemyData*, float, float> enemy_tuple_type;

	int stageNumber;
	float endureTime;
	Image* background;
	vector<enemy_tuple_type> enemies;

	StageData(int _stageNumber, float _endureTime, Image* _background, const vector<enemy_tuple_type>& _enemies)
		: stageNumber(_stageNumber), endureTime(_endureTime), background(_background), enemies(move(_enemies))
	{ }
};