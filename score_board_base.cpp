#include "score_board_base.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
xc_std::score_board_base::score_board_base(string path):data_file_path(path){
	do_info_change = false;
	auto _do_load=load_from_file();
	//if(!_do_load)
}

xc_std::score_board_base::~score_board_base(){
	if (do_info_change)
		save_to_file();
}

bool xc_std::score_board_base::load_from_file(){
	ifstream file_io(data_file_path,ios::in|ios::binary);
	if (file_io) {
		size_t info_size = 0;
		file_io.read((char*)&info_size,sizeof(info_size));
		if (!score_info.empty()) score_info.clear();
		for (size_t r_size = 0; r_size < info_size;r_size++) {
			long player_score;double proc_rate;
			string t_playername,t_date;
			file_io.read((char*)&player_score,sizeof(player_score));
			file_io.read((char*)&proc_rate, sizeof(proc_rate));
			_read_str(t_playername,file_io);
			_read_str(t_date, file_io);

			single_score temp_data;
			temp_data.player_name = t_playername;
			temp_data.player_score = player_score;
			temp_data.proc_rate = proc_rate;
			temp_data.score_date = t_date;

			score_info.push_back(temp_data);
		}			
		file_io.close();
		return true;
	}else
		return false;
}

bool xc_std::score_board_base::save_to_file(){
	ofstream file_io(data_file_path,ios::out|ios::binary);
	if (file_io) {
		do_info_change = true;
		auto size = get_data_len();
		file_io.write((char*)&size,sizeof(size));//write info size
		for (auto score_ele = score_info.begin(); score_ele != score_info.end(); score_ele++) {
			string t_name = score_ele->player_name;
			string t_date = score_ele->score_date;
			auto t_score = score_ele->player_score;
			auto t_proc = score_ele->proc_rate;
			file_io.write((char*)&t_score,sizeof(t_score));
			file_io.write((char*)&t_proc, sizeof(t_proc));
			_write_str(t_name,file_io);
			_write_str(t_date, file_io);
		}
		file_io.close();
		return true;
	}else
		return false;
}

void xc_std::score_board_base::info_sort(){
	sort(score_info.begin(), score_info.end(),[](const single_score &d1, const single_score &d2)->bool {
		return d1.player_score > d2.player_score;
	});
	save_to_file();
}

void xc_std::score_board_base::add_new_info(single_score info){
	score_info.push_back(info);
	do_info_change = true;
	save_to_file();
}
size_t xc_std::score_board_base::get_data_len(){
	return score_info.size();
}
void xc_std::score_board_base::_read_str(string& str, ifstream &fs) {
	size_t len = 0;
	fs.read((char*)&len, sizeof(len));//get char length
	char *temp = (char*)malloc(sizeof(char)*len);
	stringstream os;
	for (size_t i = 0; i < len; i++) {
		fs.read(temp, sizeof(char));
		os << *temp;
	}
	free(temp);
	os >> str;
}
void xc_std::score_board_base::_write_str(string &in,ostream &fs ) {
	auto len = in.size();
	fs.write((char*)&len, sizeof(len));
	fs.write(in.c_str(), sizeof(char)*len);
}
