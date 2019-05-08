#include "XCTaskList.h"
#include <algorithm>

void xc_ogl::XCTaskList::SortTask()
{
	if (!taskList->empty()) {
		auto taskComp = [](std::pair<size_t, TaskBase> &a,std::pair<size_t, TaskBase> &b){
			return a.first < b.first;
		};
		//sort(taskList->begin(), taskList->end(), taskComp);
	}
}

xc_ogl::XCTaskList::XCTaskList()
{
	//taskList
	taskList = new std::multimap<size_t, TaskBase>;
}

xc_ogl::XCTaskList::~XCTaskList()
{
	delete taskList;
}

void xc_ogl::XCTaskList::AddTask(TaskBase task, size_t priority)
{				/*MAX           MIN*/
	if (priority > 2 || priority < 0)
		throw ("Invaild priority.");
	else {
		taskList->insert(std::pair<size_t, TaskBase>(priority, task));
		SortTask();
	}
}

void xc_ogl::XCTaskList::StartAll()
{
}

bool xc_ogl::XCTaskList::DeleteTask(long uuid)
{
	return false;
}
