#include "General.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"

/*
	Третье задание
	Создайте приложение «Список дел».
	Приложение должно позволять:
	Добавление дел. У дела есть:
		• название;
		• приоритет;
		• описание;
		• дата, время исполнения.
	Удаление дел.
	Редактирование дел.
	Поиск дел по:
		• названию;
		• приоритету;
		• описанию;
		• дате и времени исполнения.
	Отображение списка дел:
		• на день;
		• на неделю;
		• на месяц.
	При отображении должна быть возможность сортировки:
		• по приоритету;
		• по дате и времени исполнения.
*/

int main()
{
	cout << "################################" << endl;
	cout << "##     TO-DO LIST MANAGER     ##" << endl;
	cout << "##============================##" << endl;
	cout << "## Developed by Ihor Sheremet ##" << endl;
	cout << "################################" << endl;

	cout << endl;

	cout << "This app is an examination project." << endl;
	cout << "This app may contain bugs and errors." << endl;

	cout << endl;

	bool appState = true;

	TaskManager ts;
	vector<Task> list;

	while (appState)
	{
		string userSelect;

		cout << "Features available:" << endl;
		cout << "1. Show current task list;" << endl;
		cout << "2. Add a new task;" << endl;
		cout << "3. Remove a task;" << endl;
		cout << "4. Searh for a task;" << endl;
		cout << "0. Close the app." << endl;

		cout << "Please, enter your choice: ";
		cin >> userSelect;

		cout << endl;

		if (userSelect == "0")
		{
			cout << "OK! Shutting down the app!" << endl;
			return 0;
		}

		if (userSelect == "1")
		{
			cout << "OK! There we go!" << endl
				<< "This is showing section!" << endl
				<< "Please, select your preferred options:" << endl;

			cout << endl;

			ts.Show(list);
		}
		else if (userSelect == "2")
		{
			cout << "OK! There we go!" << endl
				<< "This is adding section!" << endl
				<< "Please, fill out the following fields:" << endl;

			cout << endl;

			ts.Add(list);
		}
		else if (userSelect == "3")
		{
			cout << "OK! There we go!" << endl
				<< "This is removing section!" << endl
				<< "Please, select your preferred options:" << endl;

			cout << endl;

			ts.Remove(list);
		}
		else if (userSelect == "4")
		{
			cout << "OK! There we go!" << endl
				<< "This is searching section!" << endl;

			cout << endl;

			ts.Search(list);
		}
		else
			cout << "Input value is incorrect!" << endl 
			<< "Please, try again!" << endl;
	}
}
