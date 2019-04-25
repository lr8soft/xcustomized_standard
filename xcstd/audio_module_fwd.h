#pragma once
#ifndef _audio_module_fwd_
#define _audio_module_fwd_
#include<iostream>
#include<AL/al.h>
using std::string;
namespace xc_std {
	union al_init_module {
	private:
		bool is_init = false;
	public:
		al_init_module();
		void release();
	};
	class audio_module {
	public:
		audio_module(string);
		~audio_module();
		void play_music();
		void play_music(ALuint&);
		void play_music(ALuint&, ALuint&);
		void update_music(string);
	private:
		al_init_module *al_init;
		ALuint music_source;
		ALuint music_buffer;
		bool load_ready;
		string wav_path;
	};
}

#endif