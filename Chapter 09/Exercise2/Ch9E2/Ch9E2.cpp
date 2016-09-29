// Ch9E2.cpp
// Chapter 9, Exercise 2 (p.339)

// Class: Name_pairs
// Stores set of Name + Age pairs.
// Exercise 3 not complete due to poor exercise description. 
// Exercise 2 suggests that the Name_pair would be two vectors holding names + ages
// But Exercise 3 wants Name_pair to be individual name/age elements

#include "../../../std_lib_facilities.h"

class Name_pair
{
public:
	Name_pair();			// empty constructor
	void read_names();		// prompt user to input list of names
	void read_ages();		// for each name, display and prompt user for age
	void sort();			// sort name,age pairs alphabetically by name
	void print();			// print name,age pairs in order by age
	int size() { return name.size(); }	// count of name,age pairs


private:
	vector<string> name;
	vector<double> age;
	bool duplicate_name(string n);  // check if name already exists
};

Name_pair::Name_pair()
{
}

// prompt user to input list of names
void Name_pair::read_names()
{
	const string stop_input = "done";
	cout << "Enter list of names (\"" << stop_input << "\" when complete):\n";
	string input;
	while (getline(cin, input) && input != stop_input)
	{
		if (!duplicate_name(input))
			name.push_back(input);
		else
			cout << "Name " << input << " not added, already exists.\n";
	}
}

// prompt user to input age for each name
void Name_pair::read_ages()
{
	cout << "Enter age for each person:\n";
	double input;
	for (int i = 0; i < name.size(); ++i)
	{
		cout << name[i] << ": ";
		if (cin >> input)
			age.push_back(input);
	}
}

void Name_pair::print()
{
	if (name.size() != age.size()) error("print() number name/ages do no match");
	if (name.size() == 0)
	{
		cout << "List empty.\n";
		return;
	}

	cout << "All names and ages:\n";
	for (int i = 0; i < name.size(); ++i)
		cout << name[i] << ", " << age[i] << '\n';
	cout << '\n';
}

void Name_pair::sort()
{
	if (name.size() != age.size()) error("sort() number name/ages do no match");
	vector<string> orig_name = name;
	std::sort(name.begin(), name.end());
	vector<double> sorted_age;
	int age_index;
	for (int i = 0; i < name.size(); ++i)
	{
		for (int j = 0; j < orig_name.size(); ++j)
		{
			if (name[i] == orig_name[j])
			{
				sorted_age.push_back(age[j]);
				break;
			}
		}
	}
	age = sorted_age;
}

// Hack to print names. Clean version would require breaking
// exercise requirement by making it a friend function
ostream& operator<<(ostream& os, Name_pair& np)
{
	np.print();
	return os;
}


// check if n already exists in name
bool Name_pair::duplicate_name(string n)
{
	for (int i = 0; i < name.size(); ++i)
		if (n == name[i])
			return true;	// name found, is duplicate
	return false;			// name not found
}

int main()
try {
	Name_pair students;
	students.read_names();
	students.read_ages();
	cout << '\n';
	students.print();
	cout << "\n---List Sorted---\n";
	students.sort();
	cout << students << '\n';

	return 0;
}
catch (runtime_error& e)
{
	cerr << "error: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}

