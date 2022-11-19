import smtplib 
import datetime
from email.message import EmailMessage

def main():
    #Open the task_store.txt file and read the lines
    with open(r"C:\Users\aiden\OneDrive\Documents\Cpp_projects\Planner\Planner\task_store.txt", "r") as task_file:
        readFileList = task_file.readlines()
    
    #Store all of the task objects
    taskList = []
    
    #Loop through each line and construct a task object for each
    for line in readFileList:
        taskList.append(Task(line)) 
    
    #Check through the taskList, send out notifications, delete any objects that have passed their deadline, and store the sanitized list
    taskList = check_deadline(taskList)
    
    #Loop through all the tasks in taskList after notifications have been sent out, and objects have been deleted: convert them back into strings
    for i in range(len(taskList)):
        task = taskList[i]
        taskList[i] = task.giveString()
  
    print(taskList)
    
    #Rewrite the task_store.txt file with the data from taskList 
    with open(r"C:\Users\aiden\OneDrive\Documents\Cpp_projects\Planner\Planner\task_store.txt", "w") as task_file_out:
        task_file_out.writelines(taskList)
   
class Task:
    #Construct a task object using the tasks in the taskList.txt file
    def __init__(self, string):
        self.name = string.split(',')[0]
        self.desc = string.split(',')[1]
        self.timeAdded = string.split(',')[2]
        self.hasDeadline = string.split(',')[3]
        self.timeDeadline = string.split(',')[4]
        #Format timeDeadline
        self.dueDate = ""
        if self.timeDeadline[0] == 0:
            self.dueDate = self.timeDeadline.split('-')[0]
        else:
            self.dueDate = "0" + self.timeDeadline.split('-')[0]
            
        self.timeDeadlineStandard = datetime.strptime(self.timeDeadline, "%m/%d/%Y-%H:%M").strftime("%m/%d/%Y-%I:%M %p")
    
    #Format the object into a single string 
    def giveString(self):
        return (self.name + "," + self.desc + "," + self.timeAdded + "," + self.hasDeadline + "," + self.timeDeadline + "," + "\n")

#Send push notification using Pushover API
def notification(message):
    import http.client, urllib
    conn = http.client.HTTPSConnection("api.pushover.net:443")
    conn.request("POST", "/1/messages.json",
        urllib.parse.urlencode({
            "token": "a1qmfqydkd2h79v5izy3zjohtsi9b8",
            "user": "uiins7cjgbrt4jwa7j9pt9qzjh871p",
            "message": message,
        }), { "Content-type": "application/x-www-form-urlencoded" })
    conn.getresponse()

#Check to see whether any of the tasks in taskList have a deadline date which matches the current date
def check_deadline(list):
    for task in list:
        if task.hasDeadline == 'n':
            remind(task)
        else:
            if task.dueDate == dateFormatted:
                remind(task)
                list.remove(task)
            else:
                remind(task)
    return list
    
#Send the formatted task notification using the "notification" function
def remind(task):
    body = ""
    if task.hasDeadline == 'y':
        body = task.name + " " + task.desc + '\n' + "Due at: " + task.timeDeadlineStandard
    else:
        body = task.name + " " + task.desc
    notification(body) 
                                 
if __name__ == '__main__':
    datetime = datetime.datetime.now()
    dateFormatted = datetime.strftime("%m/%d/%Y")
    main()
    