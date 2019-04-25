#pragma once
#ifndef _audio_module_
#define _audio_module_
#include<iostream>
#include<string>
#include<AL/alut.h>
#include<AL/al.h>
#include<mutex>
#include "audio_module_fwd.h"
using namespace std;
std::mutex al_mutex;
xc_std::al_init_module::al_init_module(){
		al_mutex.lock();
		if (!is_init) {
			alutInit(NULL, NULL);
			is_init = true;
		}
		al_mutex.unlock();
}
void xc_std::al_init_module:: release(){
		al_mutex.lock();
		if(is_init)
			alutExit();
		al_mutex.unlock();
}
xc_std::audio_module::audio_module(string path):wav_path(path){
	al_init_module init_temp;
	al_init = &init_temp;
}
xc_std::audio_module::~audio_module(){
	alDeleteBuffers(1, &music_buffer);
	alDeleteSources(1, &music_source);
	al_init->release();
}
void xc_std::audio_module::play_music(){
	alGenSources(1, &music_source);
	music_buffer = alutCreateBufferFromFile(wav_path.c_str());
	alSourcei(music_source, AL_BUFFER, music_buffer);
	alSourcePlay(music_source);
	ALint play_state=0;
	do {
		alGetSourcei(music_source, AL_SOURCE_STATE, &play_state);
	} while (play_state==AL_PLAYING);
	alDeleteBuffers(1, &music_buffer);
	alDeleteSources(1, &music_source);
}
void xc_std::audio_module::update_music(string new_wav){
	wav_path = new_wav;
}
void xc_std::audio_module::play_music(ALuint &buffer){
	alGenSources(1, &music_source);
	alSourcei(music_source, AL_BUFFER, buffer);
	alSourcePlay(music_source);
	ALint play_state = 0;
	do {
		alGetSourcei(music_source, AL_SOURCE_STATE, &play_state);
	} while (play_state == AL_PLAYING);
}
void xc_std::audio_module::play_music(ALuint &buffer, ALuint &source){
	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(source);
	ALint play_state = 0;
	do {
		alGetSourcei(source, AL_SOURCE_STATE, &play_state);
	} while (play_state == AL_PLAYING);
}
#endif