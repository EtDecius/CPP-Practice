#include "..\..\..\std_lib_facilities.h"


void Exercise6()
{
	vector<string> words;
	words.push_back("zero");
	words.push_back("one");
	words.push_back("two");
	words.push_back("three");
	words.push_back("four");
	words.push_back("five");
	words.push_back("six");
	words.push_back("seven");
	words.push_back("eight");
	words.push_back("nine");

	string input;

	while (cin >> input)
	{
		if (input.size() == 1)
		{
			int convert = stoi(input);
			cout << input << ": " << words.at(convert) << "\n";
		}
		else
		{
			for (unsigned int i = 0; i < words.size(); ++i)
			{
				if (input == words.at(i))
					cout << input << ": " << i << "\n";
			}
		}

	}
}

void Exercise7()
{

}



int main()
{
	Exercise7();

	return 0;
}

