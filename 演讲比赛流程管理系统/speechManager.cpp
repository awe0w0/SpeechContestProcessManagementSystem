#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();

	this->createSpeaker();
}

void SpeechManager::show_Menu() {
	cout << "----------------------------" << endl;
	cout << "------欢迎参加演讲比赛------" << endl;
	cout << "-------1.开始演讲比赛-------" << endl;
	cout << "-------2.查看往届记录-------" << endl;
	cout << "-------3.清空比赛记录-------" << endl;
	cout << "-------0.退出比赛程序-------" << endl;
	cout << "----------------------------" << endl;
	cout << endl;
}

void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;
}

void SpeechManager::createSpeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++) {
		string name = "选手";
		name += nameseed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_Score[i] = 0;
		}

		this->v1.push_back(10001 + i);

		this->m_Speaker.insert(make_pair(10001 + i, sp));
	}
}

void SpeechManager::startSpeech() {

}

void SpeechManager::speechContest() {
	cout << "-------------第" << this->m_Index << "轮比赛正式开始-------------" << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0;

	vector<int>v_Src;
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else if (this->m_Index == 2) {
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.f);
		double avg = sum / (double)d.size();

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++) {
				cout << "编号" << (*mit).second << "姓名" << this->m_Speaker[mit->second].m_Name << "成绩" << this->m_Speaker[mit->second].m_Score[this->m_Index-1] << endl;
			}
			int count = 0;

			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++) {
				count++;
				if (this->m_Index == 1) {
					v2.push_back((*mit).second);
				}
				else {
					victory.push_back((*mit).second);
				}
			}
			groupScore.clear();

			cout << endl;
		}
	}

	cout << "-------------第" << this->m_Index << "轮比赛完毕-------------" << endl;
}

void SpeechManager::showScore() {
	
}

SpeechManager::~SpeechManager() {}