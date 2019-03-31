#ifndef score_board_base_h
#define score_board_base_h
#include<iostream>
#include<vector>
using std::vector;
using std::string;
using std::ifstream;
using std::ostream;
namespace xc_std {
	/*Load or Save sequence
		0-1.data count(size_t/unsigned int)
		and loop loading
		  1-1  player_score(long)
		  1-2  proc_rate(double)
		  1-3  player_name(string)
		  1-4  score_date(string)
	*/
	struct single_score {
		long player_score;
		double proc_rate;
		string player_name;
		string score_date;
	};
	class score_board_base{
	public:
		score_board_base() = delete;
		explicit score_board_base(string);
		~score_board_base();
		void add_new_info(single_score);
		size_t get_data_len();
	private:
		vector<single_score> score_info;	
		string data_file_path;
		bool do_info_change;
		bool load_from_file();
		bool save_to_file();
		void info_sort();
		static void _read_str(string&,ifstream&);
		static void _write_str(string &,ostream &);
	};

}

#endif
