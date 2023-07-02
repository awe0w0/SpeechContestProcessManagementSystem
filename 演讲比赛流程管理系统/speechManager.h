#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <fstream>
#include <ctime>
#include "speaker.h"
using namespace std;

class SpeechManager {
public:
	
	SpeechManager();

	void show_Menu();

	void initSpeech();

	void createSpeaker();

	void startSpeech();

	void speechDraw();

	void speechContest();

	void showScore();

	void saveRecord();

	void loadRecord();

	void showRecord();

	void clearRecord();

	vector<int>v1;

	vector<int>v2;

	vector<int>victory;

	map<int, Speaker> m_Speaker;

	int m_Index;

	bool fileIsEmpty;

	map<int, vector<string>> m_Record;

	~SpeechManager();
};
