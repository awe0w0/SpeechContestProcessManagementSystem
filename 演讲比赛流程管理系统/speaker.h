#pragma once
#include <iostream>
#include <string>
using namespace std;

/*功能分析：
* 比赛流程分析：
*抽签->开始演讲比赛->显示第一轮比赛结果->
* 抽签->开始演讲比赛->显示前三名结果->保存分数
*/

class Speaker {
public:
	string m_Name;
	double m_Score[2];
};