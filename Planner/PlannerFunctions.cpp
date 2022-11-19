#include"Planner_h.h"

struct tm* timeDeadlineStruct() {
	time_t currentTime;
	struct tm* ts_Deadline;

	// give currentTime the current time
	time(&currentTime);

	// get the localtime for the tz selected
	ts_Deadline = localtime(&currentTime);

	// set back our results
	return ts_Deadline;
}

struct tm* localTime_tm() {
	time_t localTime_t;
	struct tm* ts_localTime;

	// give currentTime the current time
	time(&localTime_t);

	// get the localtime for the tz selected
	ts_localTime = localtime(&localTime_t);

	// set back our results
	return ts_localTime;
}

//Convert a string to a TM, string in format 'm/d/y(years from 1900)-h(military):m'
tm stringToTM(std::string string) {
	tm tempTM;
	std::vector<std::string> fullTime = stringSplit(string, '-');
	std::vector<std::string> date = stringSplit(fullTime[0], '/');
	std::vector<std::string> time = stringSplit(fullTime[1], ':');

	tempTM.tm_mon = stoi(date[0]);
	tempTM.tm_mday = stoi(date[1]);
	tempTM.tm_year = (stoi(date[2]) > 1900) ? (stoi(date[2]) - 1900) : stoi(date[2]);
	tempTM.tm_hour = stoi(time[0]);
	tempTM.tm_min = stoi(time[1]);

	return tempTM;
}

//Letting the user add a task
void addTask(std::vector<Task*> &tempTaskList) {
	//Initiliaze current local time
	struct tm* temp_tm;
	struct tm tempDeadline;
	struct tm localT_tm;

	temp_tm = timeDeadlineStruct();
	tempDeadline = *temp_tm;

	temp_tm = localTime_tm();
	localT_tm = *temp_tm;

	//Declare Variables
	std::string taskName;
	std::string description;
	std::string deadline;

	//User input for task members
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Name of task: ";
	std:getline(std::cin, taskName);
	std::cout << std::endl;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Description of task: ";
	std::getline(std::cin, description);
	std::cout << std::endl;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Does it have a deadline (y/n)? ";
	std::cin >> deadline;
	std::cout << std::endl;

	//If the task has a deadline, get the deadline data, otherwise, continue on
	if (!deadline.compare("y") || !deadline.compare("yes")) {
		//declare variables
		std::string storeDay;
		std::string storeMonth;
		std::string storeYear;
		std::string storeHour;
		std::string storeMin;
		std::string storeAMPM;

		std::cout << "What is the due date (00/00/0000)? " << std::endl;
		std::getline(std::cin, storeMonth, '/');
		std::getline(std::cin, storeDay, '/');
		std::getline(std::cin, storeYear);
		
		std::cout << "What is the due time (00:00)? " << std::endl;
		std::getline(std::cin, storeHour, ':');
		std::getline(std::cin, storeMin);
		
		std::cout << "AM or PM? " << std::endl;
		std::getline(std::cin, storeAMPM);

		int i_storeDay = std::stoi(storeDay);
		int i_storeMonth = std::stoi(storeMonth);
		int i_storeYear = std::stoi(storeYear);
		int i_storeHour = std::stoi(storeHour);
		int i_storeMin = std::stoi(storeMin);

		tempDeadline.tm_mday = i_storeDay;
		tempDeadline.tm_mon = i_storeMonth;
		tempDeadline.tm_year = i_storeYear;
		//Fix this, 12:45 != 24:45
		tempDeadline.tm_hour = (storeAMPM == "AM") || (storeAMPM == "am") ? (i_storeHour += 0) : (i_storeHour += 12);
		tempDeadline.tm_min = i_storeMin;

	}
	else {
	}

	//Print out task data
	std::cout << "Name: " << taskName << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Deadline: " << deadline << std::endl;
	std::cout << "Time Added: " << tmStringFormat(localT_tm) << std::endl;
	std::cout << "Time Deadline: " << tmStringFormat(tempDeadline) << std::endl;

	//Check with user if data is correct
	std::cout << "Is this data correct (y/n)?" << std::endl;
	std::string userCorrect;
	std::cin >> userCorrect;

	if (userCorrect == "y") {
		//Use different "task" constructor for deadline or no deadline
		if (deadline == "y" || "yes") {
		//Add a task to the task list using the user-input for the data{
			tempTaskList.push_back(new Task(taskName, description, localT_tm, tempDeadline, true));
		}
		else {
			tempTaskList.push_back(new Task(taskName, description, localT_tm));
		}
	}
	else {
		//Clear the screen, add task
		system("CLS");
		addTask(tempTaskList);
	}
}

//Convert tm structure into a readable string
std::string tmStringFormat(tm tm) {
	std::string string_formatted;

	string_formatted = std::to_string(tm.tm_mon) + "/" + std::to_string(tm.tm_mday) + "/" + std::to_string(tm.tm_year) + "-" + std::to_string(tm.tm_hour) + ":" + std::to_string(tm.tm_min);

	return string_formatted;
}

//Write a task object into the file
void storeTask(Task* task) {
	//Define variables
	std::fstream file;
	char deadline;
	std::string name = "name";
	std::string storeTimeAdded = tmStringFormat(task->getTimeAdded());
	std::string storeTimeDeadline = tmStringFormat(task->getTimeDeadline());

	//Open file to append
	file.open("task_store.txt", std::ios::app);
	//Change deadline character based on if object has deadline
	if (task->getHasDeadline() == true) {
		deadline = 'y';
	}
	else if (task->getHasDeadline()) {
		deadline = 'n';
	}
	
	//Store all object data into one string
	std::string storeString = task->getName() + "," + task->getDesc() + "," + storeTimeAdded + "," + deadline + "," + storeTimeDeadline + ",";
	
	//Make sure file is open before writing
	if (file.is_open()) {
		//Write the string of object data into file along with a line break
		file << storeString;
		file << "\n";
		file.close();
	}
}

std::vector<std::string> stringSplit(std::string string, char delim) {
	std::vector<std::string> stringPieces;

	while (string != "") {
		std::string new_piece = string.substr(0, string.find(delim));
		stringPieces.push_back(new_piece);
		string.erase(0, new_piece.length() + 1);
	}
	return stringPieces;
}

void displayTasks() {
	//Init variables
	std::fstream file;
	//Vector to store all of the tasks as strings
	std::vector<std::string> tasksAsStrings;
	std::vector<Task*> tasksAsObjects;
	//Open task_store.txt
	file.open("task_store.txt", std::ios::in);

	//If task_store.txt opens, continue
	if (file.is_open()) {
		std::string line;
		//Loop through all of lines and add them to the vector
		while (getline(file, line)) {
			tasksAsStrings.push_back(line);
		}
	}

	//Loop through each task in TasksAsString
	for (int i = 0; i < tasksAsStrings.size(); i++) {
		//Initiliaze variables
		std::string i_name;
		std::string i_desc;
		tm i_timeAdded;
		bool i_hasDeadline;
		tm i_timeDeadline;

		//Set cString as the current string in the loop
		std::string cString = tasksAsStrings[i];
		//Split up the string using ',' as a delim
		std::vector<std::string> splittedString = stringSplit(cString, ',');

	    //Assign all of the values using the splitted string's pieces
		i_name = splittedString[0];
		i_desc = splittedString[1];
		
		i_timeAdded = stringToTM(splittedString[2]);
		//If the bool field is "y" set bool to true, otherwise set false
		if (splittedString[3] == "y") {
			i_hasDeadline = true;
			i_timeDeadline = stringToTM(splittedString[4]);
			tasksAsObjects.push_back(new Task(i_name, i_desc, i_timeAdded, i_timeDeadline, i_hasDeadline));
		}
		else {
			i_hasDeadline = false;
			tasksAsObjects.push_back(new Task(i_name, i_desc, i_timeAdded));
		} 
	}
	
	for (int i = 0; i < tasksAsObjects.size(); i++) {
		tasksAsObjects[i]->displayTaskMethod();
		std::cout << std::endl;
	}
}