
#include<time.h> 
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
#pragma warning(disable : 4996)

class Task {
	std::string m_name;
	std::string m_description;
	bool m_hasDeadline;
	tm m_timeAdded;
	tm m_timeDeadline;

public:
	//Constructor
	Task(std::string new_name, std::string new_description, tm newTimeAdded, tm newTimeDeadline, bool newHasDeadline)
		:m_name(new_name), m_description(new_description), m_timeAdded(newTimeAdded), m_hasDeadline(newHasDeadline), m_timeDeadline(newTimeDeadline) {}

	Task(std::string new_name, std::string new_description, tm newTimeAdded, bool newHasDeadline = false)
		:m_name(new_name), m_description(new_description), m_timeAdded(newTimeAdded), m_hasDeadline(newHasDeadline) {}
	
	//Get function declarations
	std::string getName();
	std::string getDesc();
	bool getHasDeadline();
	tm getTimeAdded();
	tm getTimeDeadline();

	//Display method
	void displayTaskMethod();
};

//Function Declaration
	void addTask(std::vector<Task*> &tempTaskList);
	void storeTask(Task* task);
	std::vector<std::string> stringSplit(std::string string, char delim);
	//void addStoreTask(std::vector<Task*> taskList);

	std::string tmStringFormat(tm tm);
	tm stringToTM(std::string);

	void displayTasks();