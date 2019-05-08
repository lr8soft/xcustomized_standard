#pragma once
#ifndef _XCTaskList_h_
#define _XCTaskList_h_
#include<iostream>
#include<functional>
#include<map>
namespace xc_ogl {
	struct TaskBase {
		long TaskUUID;
		std::function<void(void)> CallBack;
		TaskBase(std::function<void(void)> callback,long id) {
			CallBack = callback;
			TaskUUID = id;
		}
	};
	class XCTaskList {
	private:/*priority:0~2(MAX) task*/
		std::multimap<size_t, TaskBase> *taskList;
		void SortTask();
	public:
		XCTaskList();
		~XCTaskList();
		void AddTask(TaskBase task, size_t priority);
		void StartAll();
		bool DeleteTask(long uuid);
	};
}
#endif