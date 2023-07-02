/*1.1比赛规则
* 学校举行一场演讲比赛，共有12个人参加。比赛共两轮，第一轮为淘汰赛，第二轮为决赛
*每名选手都有对应的编号，如10001-10012
* 比赛方式：分组比赛，每组六个人；
* 第一轮分为两个小组，整体按照选手编号进行抽签后顺序演讲
* 十个评委分别给每名选手打分，去除最高分和最低分，求的平均分为本轮选手的成绩
* 当小组演讲完后，淘汰组内排名最后的三个选手，前三名晋级，进入下一轮的比赛
* 第二轮为决赛，前三名胜出
* 每轮比赛过后需要显示晋级选手的信息
* 
* 1.2程序功能
* 开始演讲功能：完成整届比赛的流程，每个比赛阶段需要给用户一个提示，用户按任意键后继续下一个阶段
* 查看往届记录：查看之前的比赛前三名结果，每次比赛都会记录到文件中，文件用.csv后缀名保存
* 清空比赛记录：将文件中数据清空
* 退出比赛程序：可以退出当前程序
*/

#include "speechManager.h"

int main() {
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	
	int choice = 0;

	while (true) {
		sm.show_Menu();

		cout << "请输入选项" << endl;

		cin >> choice;

		switch (choice) {
		case 0:
			return 0;
			break;
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.loadRecord();
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		default:
			cout << "请输入正确选项" << endl;
			break;
		}
	}
}