#pragma once

#include "General.h"
#include "Date.h"
#include "Task.h"
#include <algorithm>

class TaskManager
{
	// Temporary solution for some features:

	void Idle()
	{
		return;
	}

	// Functions related to show feature:

	void ShowFullList(vector<Task> list, bool index = false)
	{
		if (list.size() != 0)
		{
			for (int i = 0; i < list.size(); i++)
			{
				if (index == true)
					cout << "Index: " << list[i].initialIndex << endl;

				cout << "Name: " << list[i].name << endl;
				cout << "Priority: ";

				if (list[i].priority == true)
					cout << "High" << endl;
				else
					cout << "Default" << endl;

				cout << "Description: " << list[i].description << endl;
				cout << "Due date: ";
				cout << list[i].dueDate.day << "/";
				cout << list[i].dueDate.month << "/";
				cout << list[i].dueDate.year << " ";

				if (list[i].dueDate.hours < 10)
					cout << "0";

				cout << list[i].dueDate.hours << ":";

				if (list[i].dueDate.minutes < 10)
					cout << "0";

				cout << list[i].dueDate.minutes << endl;

				cout << "---" << endl;
			}
		}
		else
			cout << "List is empty!" << endl;

		cout << endl;
	}

	// Functions related to sort feature:

	vector<Task> SetInitialIndexes(vector<Task> list)
	{
		vector<Task> sortedList;

		for (int i = 0; i < list.size(); i++)
		{
			sortedList.push_back(list[i]);
			sortedList[i].initialIndex = i;
		}

		return sortedList;
	}

	static bool CompareByPriority(const Task& a, const Task& b)
	{
		return a.priority > b.priority;
	}

	vector<Task> SortByPriority(vector<Task> list, bool priority)
	{
		vector<Task> sortedList = list;

		sort(sortedList.begin(), sortedList.end(), CompareByPriority);

		return sortedList;
	}

	static bool CompareByDate(const Task& a, const Task& b)
	{
		return a.dueDate.timestamp < b.dueDate.timestamp;
	}

	vector<Task> SortByDueDate(vector<Task> list)
	{
		vector<Task> sortedList = list;

		sort(sortedList.begin(), sortedList.end(), CompareByDate);

		return sortedList;
	}

	vector<Task> GetTasksForToday(vector<Task> list)
	{
		Date date;
		date.GetCurrentTime();

		vector<Task> sortedList;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].dueDate.year == date.year &&
				list[i].dueDate.month == date.month &&
				list[i].dueDate.day == date.day)
				sortedList.push_back(list[i]);
		}

		return sortedList;
	}

	vector<Task> GetTasksForThisWeek(vector<Task> list)
	{
		Date date;
		date.GetCurrentTime();

		int daysDiff = 7 - date.weekDay;

		vector<Task> sortedList;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].dueDate.year == date.year &&
				list[i].dueDate.month == date.month &&
				list[i].dueDate.day <= (date.day + daysDiff))
				sortedList.push_back(list[i]);
		}

		return sortedList;
	}

	vector<Task> GetTasksForThisMonth(vector<Task> list)
	{
		Date date;
		date.GetCurrentTime();

		vector<Task> sortedList;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].dueDate.year == date.year &&
				list[i].dueDate.month == date.month)
				sortedList.push_back(list[i]);
		}

		return sortedList;
	}

	// Functions related to search feature:

	vector<Task> SearchByName(vector<Task> list, string name)
	{
		vector<Task> foundList;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].name == name)
				foundList.push_back(list[i]);
		}

		return foundList;
	}

	vector<Task> SearchByPriority(vector<Task> list, bool priority)
	{
		vector<Task> foundList;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].priority == priority)
				foundList.push_back(list[i]);
		}

		return foundList;
	}

	vector<Task> SearchByDescription(vector<Task> list, string description)
	{
		vector<Task> foundList;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].description == description)
				foundList.push_back(list[i]);
		}

		return foundList;
	}

	vector<Task> SearchByDueDate(vector<Task> list, Date dueDate)
	{
		vector<Task> foundList;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].dueDate.timestamp == dueDate.timestamp)
				foundList.push_back(list[i]);
		}

		return foundList;
	}

	// Functions related to add feature:

	bool AddTaskName(Task& task)
	{
		string input;

		cout << "Name limit is 60 characters!" << endl;
		cout << "Please, name your task: ";
		
		cin.ignore();
		getline(cin, input);

		if (input.size() > 60)
			return false;

		cout << endl;

		task.name = input;

		return true;
	}

	bool AddTaskPriority(Task& task)
	{
		string input;

		cout << "Please, set up a priority for your task." << endl;
		cout << "Enter \"1\" to set up a high priority and \"0\" to mark it as a default task: ";
		cin >> input;

		try 
		{
			if (stoi(input) < 0 || stoi(input) > 1)
				return false;
		}
		catch (exception ex)
		{
			return false;
		}

		cout << endl;

		task.priority = stoi(input);

		return true;
	}

	bool AddTaskDescription(Task& task)
	{
		string input;

		cout << "Description limit is 255 characters!" << endl;
		cout << "Please, describe your task: ";

		cin.ignore();
		getline(cin, input);

		if (input.size() > 255)
			return false;

		cout << endl;

		task.description = input;

		return true;
	}

	bool AddTaskDueDate(Task& task)
	{
		Date date;

		cout << "Please, set up a due date for your task following this pattern:" << endl;

		cout << "Year: ";
		cin >> date.year;
		
		if (date.year < 2021)
			return false;

		cout << "Month: ";
		cin >> date.month;

		if (date.month < 1 || date.month > 12)
			return false;

		cout << "Day: ";
		cin >> date.day;

		if (date.day < 1 || date.day > 31)
			return false;

		cout << "Hours: ";
		cin >> date.hours;

		if (date.hours < 0 || date.hours > 24)
			return false;

		cout << "Minutes: ";
		cin >> date.minutes;

		if (date.minutes < 0 || date.minutes > 60)
			return false;

		cout << endl;

		date.timestamp = date.ConvertToTimestamp(date);

		task.dueDate = date;

		return true;
	}

	// Functions related to remove feature:

	bool RemoveByIndex(vector<Task>& list, int index)
	{
		if (list.size() < index)
			return false;

		list.erase(list.begin() + index);

		return true;
	}

	// Functions related to user input feature:

	void UI_SortOutByDueDate(vector<Task>& list)
	{
		string userSelect;

		cout << "Do you want to sort list by due date?" << endl;
		cout << "Use \"y\" to agree or \"n\" to refuse: ";
		cin >> userSelect;

		if (userSelect == "y")
			list = SortByDueDate(list);
		else if (userSelect == "n")
			return;
		else
			cout << endl
			<< "Input value is incorrect!" << endl
			<< "Sort feature won't be applied!" << endl;
	}

	void UI_SortOutByPriority(vector<Task>& list)
	{
		string userSelect;

		cout << "Do you want to sort list by priority?" << endl;
		cout << "Enter \"y\" to agree or \"n\" to refuse: ";
		cin >> userSelect;

		if (userSelect == "y")
			list = SortByPriority(list, true);
		else if (userSelect == "n")
			return;
		else
			cout << endl 
			<< "Input value is incorrect!" << endl
			<< "Sort feature won't be applied!" << endl;
	}

	void UI_SortOutByTimeFrames(vector<Task>& list)
	{
		string userSelect;

		cout << "Do you want to apply time frame sort?" << endl;
		cout << "Enter \"y\" to agree or \"n\" to refuse: ";
		cin >> userSelect;

		if (userSelect == "y")
		{
			string userInput;

			cout << "Daily/Weekly/Monthly sort:" << endl;
			cout << "To show tasks for today - enter \"1\";" << endl;
			cout << "To show tasks for this week - enter \"2\";" << endl;
			cout << "To show tasks for this month - enter \"3\"." << endl;
			cout << "Please, enter your choice: ";
			cin >> userInput;

			if (userInput == "1")
				list = GetTasksForToday(list);
			else if (userInput == "2")
				list = GetTasksForThisWeek(list);
			else if (userInput == "3")
				list = GetTasksForThisMonth(list);
			else
				cout << endl
				<< "Input value is incorrect!" << endl
				<< "Sort feature won't be applied!" << endl;
		}
		else if (userSelect == "n")
			return;
		else
			cout << endl
			<< "Input value is incorrect!" << endl
			<< "Sort feature won't be applied!" << endl;
	}

public:
	void Show(vector<Task>& list)
	{
		vector<Task> sortedList = list;
		
		UI_SortOutByDueDate(sortedList);

		cout << endl;

		UI_SortOutByPriority(sortedList);

		cout << endl;

		UI_SortOutByTimeFrames(sortedList);

		cout << endl;

		ShowFullList(sortedList);
	}

	void Add(vector<Task>& list)
	{
		bool run = true;

		while (run)
		{
			Task task;

			string userSelect;

			bool name = AddTaskName(task);

			if (name == true)
			{
				bool priority = AddTaskPriority(task);

				if (priority == true)
				{
					bool description = AddTaskDescription(task);

					if (description == true)
					{
						bool dueDate = AddTaskDueDate(task);

						if (dueDate == true)
						{
							cout << "Task has been successfully added!" << endl;
							list.push_back(task);
						}
						else
							cout << endl <<
							"Input is incorrect, please, try again!" << endl;
					}
					else
						cout << endl << 
						"Input is incorrect, please, try again!" << endl;
				}
				else
					cout << endl <<
					"Input is incorrect, please, try again!" << endl;
			}
			else
				cout << endl <<
				"Input is incorrect, please, try again!" << endl;

			cout << endl;

			cout << "Do you want to add another task?" << endl;
			cout << "Enter \"y\" to agree or \"n\" to refuse: ";
			cin >> userSelect;

			cout << endl;

			if (userSelect == "y")
				Idle();
			else if (userSelect == "n")
				return;
			else
			{
				cout << "Input value is incorrect!" << endl
					<< "You will be returned back to the previous interface!" << endl;

				cout << endl;

				return;
			}
		}
	}

	void Remove(vector<Task>& list)
	{
		bool run = true;
		
		vector<Task> sortedList = SetInitialIndexes(list);

		UI_SortOutByDueDate(sortedList);

		cout << endl;

		UI_SortOutByPriority(sortedList);

		cout << endl;

		UI_SortOutByTimeFrames(sortedList);

		cout << endl;

		ShowFullList(sortedList, true);

		if (sortedList.size() != 0)
		{
			while (run)
			{
				string userInput;
				string userSelect;

				cout << "Enter an index of the task you would like to delete: ";
				cin >> userInput;

				cout << endl;

				try
				{
					if (stoi(userInput) >= 0 && stoi(userInput) < list.size())
					{
						bool del = RemoveByIndex(list, stoi(userInput));

						if (del == true)
						{
							cout << "Successfully deleted!" << endl;
						}
						else
							cout << "Something went wrong!" << endl
							<< "Please, try again!" << endl;
					}
					else
					{
						cout << "This index doesn't exist!" << endl;
					}
				}
				catch (exception ex)
				{
					cout << "Input value is incorrect!" << endl;;
				}

				cout << endl;

				cout << "Do you want to delete another task?" << endl;
				cout << "Enter \"y\" to agree or \"n\" to refuse: ";
				cin >> userSelect;

				cout << endl;

				if (userSelect == "y")
					Idle();
				else if (userSelect == "n")
					return;
				else
				{
					cout << "Input value is incorrect!" << endl
						<< "You will be returned back to the previous interface!" << endl;

					cout << endl;

					return;
				}
			}
		}
		else
			cout << "There are no tasks to delete, please, try again!" << endl;

		cout << endl;
	}

	void Search(vector<Task>& list)
	{
		bool run = true;

		while (run)
		{
			string userSelect;

			cout << "1. Search by name;" << endl;
			cout << "2. Search by priority;" << endl;
			cout << "3. Search by description;" << endl;
			cout << "4. Search by due date;" << endl;
			cout << "0. Return back." << endl;
			cout << "Please, enter your choice: ";
			cin >> userSelect;

			cout << endl;

			if (userSelect == "0")
				return;

			vector<Task> foundList;

			if (userSelect == "1")
			{
				string userInput;

				cout << "Please, enter the name to search for: ";

				cin.ignore();
				getline(cin, userInput);

				foundList = SearchByName(list, userInput);

				cout << endl;

				ShowFullList(foundList);
			}
			else if (userSelect == "2") 
			{
				int userInput;

				cout << "Hint: \"1\" is a high priority, \"0\" is a default setting!" << endl;
				cout << "Please, enter the priority to search for: ";
				cin >> userInput;

				foundList = SearchByPriority(list, userInput);

				cout << endl;

				ShowFullList(foundList);
			}
			else if (userSelect == "3")
			{
				string userInput;

				cout << "Please, enter the description to search for: ";
				
				cin.ignore();
				getline(cin, userInput);

				foundList = SearchByName(list, userInput);

				cout << endl;

				ShowFullList(foundList);
			}
			else if (userSelect == "4")
			{
				Date userInput;

				cout << "Please, enter the due date to search for:" << endl;
				cout << "Year: ";
				cin >> userInput.year;
				cout << "Month: ";
				cin >> userInput.month;
				cout << "Day: ";
				cin >> userInput.day;
				cout << "Hours: ";
				cin >> userInput.hours;
				cout << "Minutes: ";
				cin >> userInput.minutes;

				userInput.timestamp = userInput.ConvertToTimestamp(userInput);

				foundList = SearchByDueDate(list, userInput);

				cout << endl;

				ShowFullList(foundList);
			}
			else
				cout << endl
				<< "Input value is incorrect!" << endl 
				<< "Please, try again!" << endl;
		}
	}
};
