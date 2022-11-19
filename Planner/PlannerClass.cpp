#include "Planner_h.h"

//Task
	//Get Functions
	std::string Task::getName() {
		return m_name;
	}
	std::string Task::getDesc() {
		return m_description;
	}
	bool Task::getHasDeadline() {
		return m_hasDeadline;
	}
	tm Task::getTimeAdded() {
		return m_timeAdded;
	}
	tm Task::getTimeDeadline() {
		return m_timeDeadline;
	}
	
	//Display method
	void Task::displayTaskMethod() {
		char buff[80];
		char buff2[80];
		tm* timeptrDeadline = &m_timeDeadline;
		tm* timeptrAdded = &m_timeAdded;

		strftime(buff, 80, "%D %I:%M %p", timeptrDeadline);
		strftime(buff2, 80, "%D %I:%M %p", timeptrAdded);
		
		std::cout << m_name << '\t' << "(Deadline: " << buff << ")" << std::endl;
		std::cout << '\t' << m_description << std::endl << '\n';
		std::cout << '\t' << "(Added on: " << buff2 << ")" << std::endl;
	}