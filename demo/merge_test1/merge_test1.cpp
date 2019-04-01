#include "link_loop_struct.hpp"
#include "xcstd"
#include "score_board.h"
#include "config_manager.h"
#include<iostream>

using namespace xc_std;
int main() {
	link_loop_struct<int> score;
	score.push_back(111);
	score.push_back(112);
	score.push_back(113);
	score_board_base score_board("1.dat");
	for (auto i = 0; i < score.get_size();i++) {
		single_score temp;
		temp.player_name = "lrsoft";
		temp.player_score = score.pop_front();
		temp.proc_rate = 0.001;
		temp.score_date = "2019/3/31 21:43";
		score_board.add_new_info(temp);
	}
	config_manager testconfig("config.cfg");
/*	testconfig.add_new_info("testconfig","true");
	testconfig.add_new_info("width","640");
	testconfig.add_new_info("height", "480");*/
	cout << testconfig.get_value("width") << "x" << testconfig.get_value("height")<<endl;
	string a;
	system("pause");
}