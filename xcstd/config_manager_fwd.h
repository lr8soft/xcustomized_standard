#pragma once
#ifndef _config_manager_fwd_
#define _config_manager_fwd_
#include <iostream>
#include <map>
using std::map;
using std::string;
using std::ifstream;
namespace xc_std {
	class config_manager {
	public:
		config_manager() = delete;
		explicit config_manager(string);
		~config_manager()=default;
		bool add_new_info(string,string);
		bool delete_old_info(string);
		bool replace_old_info(string,string);
		string get_value(string);
	private:
		map<string, string> map_info;
		string info_path;
		bool load_from_file();
		bool save_to_file();
		bool find_key_exist(string);
		void load_to_pair(ifstream&);
	};
}
#endif

