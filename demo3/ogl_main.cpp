#include<iostream>
#include "ogl_app.h"
#include<thread>
bool should_close = false;
void thread_work() {
	xc_ogl::ogl_app program;
	program.init();
	program.message_loop();
	should_close = true;
}
int main() {
	std::thread gl_thread(thread_work);
	gl_thread.detach();
	while (!should_close) {
		//loop...
	}
}