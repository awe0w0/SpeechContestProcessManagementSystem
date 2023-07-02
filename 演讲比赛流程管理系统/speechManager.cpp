#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();

	this->createSpeaker();

	this->loadRecord();
}

void SpeechManager::show_Menu() {
	std::cout << "----------------------------" << endl;
	std::cout << "------欢迎参加演讲比赛------" << endl;
	std::cout << "-------1.开始演讲比赛-------" << endl;
	std::cout << "-------2.查看往届记录-------" << endl;
	std::cout << "-------3.清空比赛记录-------" << endl;
	std::cout << "-------0.退出比赛程序-------" << endl;
	std::cout << "----------------------------" << endl;
	std::cout << endl;
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
	//第一轮
	//1.抽签
	this->speechDraw();
	system("pause");
	//2.演讲评分
	this->speechContest();
	system("pause");
	//3.显示分数
	this->showScore();
	system("pause");
	//第二轮
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	system("pause");
	//2.演讲评分
	this->speechContest();
	system("pause");
	//3.显示分数
	this->showScore();

	this->saveRecord();
	cout << "本届比赛完毕" << endl;

	system("pause");
	system("cls");
	
	this->m_Index--;
}

void SpeechManager::speechDraw() {
	std::cout << "-------------第" << this->m_Index << "轮选手正在抽签-------------" << endl;
	std::cout << "---------------------------" << endl;
	std::cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << endl;
	}
	std::cout << "---------------------------" << endl;
}

void SpeechManager::speechContest() {
	std::cout << "-------------第" << this->m_Index << "轮比赛正式开始-------------" << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0;

	vector<int>v_Src;
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
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

		//for (map<int, Speaker>::iterator ait = m_Speaker.begin(); ait != m_Speaker.end(); it++) {
		//	cout << (*ait).first << endl;
		//}

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			std::cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++) {
				std::cout << "编号" << (*mit).second << "姓名" << this->m_Speaker[mit->second].m_Name << "成绩" << this->m_Speaker[mit->second].m_Score[this->m_Index-1] << endl;
			}
			int count = 0;

			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++) {
				count++;
				if (this->m_Index == 1) {
					
					v2.push_back((*mit).second);
					if (count == 6) {
						v2.erase(v2.end() - 3, v2.end());
					}
				}
				else {
					victory.push_back((*mit).second);
				}
			}
			
			

			groupScore.clear();
			std::cout << endl;
		}
		
	}

	//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	//for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
	//	cout << "选手编号：" << *it << "姓名" << m_Speaker[*it].m_Name << "得分" << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
	//}

	std::cout << "-------------第" << this->m_Index << "轮比赛完毕-------------" << endl;
}

void SpeechManager::showScore() {
	std::cout << "-------------第" << this->m_Index << "轮晋级选手信息如下-------------" << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = this->v2;
	}
	else {
		victory.erase(victory.end() - 3, victory.end());
		v = this->victory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << "选手编号：" << *it << "姓名" << m_Speaker[*it].m_Name << "得分" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	std::cout << endl;
}

void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++) {
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";
	}

	ofs << endl;

	ofs.close();

	cout << "记录已保存" << endl;
}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;

	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs >> data) {
		vector<string>v;

		int pos = -1;
		int start = 0;

		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord() {
	for (int i = 0; i < this->m_Record.size(); i++) {
		cout << "第" << i + 1 << "届" << endl << "冠军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << endl
			<< "亚军编号：" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << endl
			<< "季军编号：" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		m_Record.clear();

		cout << "清空成功" << endl;
	}
	else {
		system("pause");
		system("cls");
		return;

	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {}