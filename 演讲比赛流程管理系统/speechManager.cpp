#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();

	this->createSpeaker();

	this->loadRecord();
}

void SpeechManager::show_Menu() {
	std::cout << "----------------------------" << endl;
	std::cout << "------��ӭ�μ��ݽ�����------" << endl;
	std::cout << "-------1.��ʼ�ݽ�����-------" << endl;
	std::cout << "-------2.�鿴�����¼-------" << endl;
	std::cout << "-------3.��ձ�����¼-------" << endl;
	std::cout << "-------0.�˳���������-------" << endl;
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
		string name = "ѡ��";
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
	//��һ��
	//1.��ǩ
	this->speechDraw();
	system("pause");
	//2.�ݽ�����
	this->speechContest();
	system("pause");
	//3.��ʾ����
	this->showScore();
	system("pause");
	//�ڶ���
	this->m_Index++;
	//1.��ǩ
	this->speechDraw();
	system("pause");
	//2.�ݽ�����
	this->speechContest();
	system("pause");
	//3.��ʾ����
	this->showScore();

	this->saveRecord();
	cout << "����������" << endl;

	system("pause");
	system("cls");
	
	this->m_Index--;
}

void SpeechManager::speechDraw() {
	std::cout << "-------------��" << this->m_Index << "��ѡ�����ڳ�ǩ-------------" << endl;
	std::cout << "---------------------------" << endl;
	std::cout << "��ǩ���ݽ�˳�����£�" << endl;
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
	std::cout << "-------------��" << this->m_Index << "�ֱ�����ʽ��ʼ-------------" << endl;
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
			std::cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++) {
				std::cout << "���" << (*mit).second << "����" << this->m_Speaker[mit->second].m_Name << "�ɼ�" << this->m_Speaker[mit->second].m_Score[this->m_Index-1] << endl;
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
	//	cout << "ѡ�ֱ�ţ�" << *it << "����" << m_Speaker[*it].m_Name << "�÷�" << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
	//}

	std::cout << "-------------��" << this->m_Index << "�ֱ������-------------" << endl;
}

void SpeechManager::showScore() {
	std::cout << "-------------��" << this->m_Index << "�ֽ���ѡ����Ϣ����-------------" << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = this->v2;
	}
	else {
		victory.erase(victory.end() - 3, victory.end());
		v = this->victory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << "ѡ�ֱ�ţ�" << *it << "����" << m_Speaker[*it].m_Name << "�÷�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
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

	cout << "��¼�ѱ���" << endl;
}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ�գ�" << endl;
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
		cout << "��" << i + 1 << "��" << endl << "�ھ���ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << endl
			<< "�Ǿ���ţ�" << this->m_Record[i][2] << "�÷֣�" << this->m_Record[i][3] << endl
			<< "������ţ�" << this->m_Record[i][4] << "�÷֣�" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		m_Record.clear();

		cout << "��ճɹ�" << endl;
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