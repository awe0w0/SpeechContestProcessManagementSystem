#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include "speaker.h"
using namespace std;

class SpeechManager {
public:
	
	SpeechManager();

	void show_Menu();

	void initSpeech();

	void createSpeaker();

	void startSpeech();

	void speechContest();

	void showScore();

	vector<int>v1;

	vector<int>v2;

	vector<int>victory;

	map<int, Speaker> m_Speaker;

	int m_Index;

	~SpeechManager();
};
