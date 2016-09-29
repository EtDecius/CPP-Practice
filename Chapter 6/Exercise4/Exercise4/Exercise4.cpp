// Exercise4.cpp
// Chapter 6 exercise (p. 218)

// Define a class Name_value that holds a string and a value. Rework exercise 19
// from Chapter 4 to use a vector<Name_value> instead of two vectors
// Read and display list of names and scores

#include "../../../std_lib_facilities.h"

class Name_value
{
public:
	string name;
	int score;
	Name_value(string n, int s);
};

Name_value::Name_value(string in_name, int in_score)
{
	name = in_name;
	score = in_score;
}

int main()
{
	vector<Name_value> students;
	string name_input;
	int score_input;
	bool duplicate = false;

	cout << "Enter names and scores as a pair (ex: Joe 75):\n";
	while (cin >> name_input >> score_input)
	{
		if (name_input == "NoName" && score_input == 0)
			break;

		// check for dupelicate names
		duplicate = false;
		for (Name_value nv : students)
		{
			if (nv.name == name_input)
				duplicate = true;
		}

		if (duplicate)
			cout << name_input << " already exists, score not added.\n";
		else
			students.push_back(Name_value(name_input, score_input));
	}

	// print all names and scores
	for (Name_value nv : students)
		cout << nv.name << "\t\t" << nv.score << '\n';

	return 0;
}