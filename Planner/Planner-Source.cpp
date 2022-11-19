#include "Planner_h.h"

//Define variables
std::vector<Task*> taskList;
int taskListSize = taskList.size();
std::vector<int> day_of_month;

int main() {
	std::string str_storeAdd;
	std::string inputEnterAnother;

	
	//Check whether user will be entering task or something else
	std::cout << "Enter task (y/n): ";
	std::cin >> str_storeAdd;

	if (str_storeAdd == "Yes" || str_storeAdd == "y" || str_storeAdd == "yes") {
		//Add and store task 
		do {
			addTask(taskList);
			storeTask(taskList[taskListSize]);
			std::cout << "Enter another (y/n)?";
			std::cin >> inputEnterAnother;
		} while (inputEnterAnother == "y");

		displayTasks();
	}

	else if (str_storeAdd == "read" || str_storeAdd == "Read" || str_storeAdd == "r") {
		displayTasks();
	}
}
