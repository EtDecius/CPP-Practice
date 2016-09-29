// Ch8Ex2plus.cpp
// Chapter 8 Exercises 2 to 14 (p.300)

#include "../../../std_lib_facilities.h"

void print(const string label, const vector<int>& vi)
// print label and contents of vector of ints
{
	cout << label << ":\n";
	for (int n : vi)
		cout << n << ' ';
	cout << '\n';
}


void print(const string label, const vector<string>& vs)
// print label and contents of vector of strings
{
	cout << label << ":\n";
	for (string s : vs)
		cout << s << ' ';
	cout << '\n';
}

// --------------------------------------------------------

void fibonacci(int x, int y, vector<int>& v, int n)
// fill vector with n fibonacci integers, begin series with x,y.
{
	if (v.size() != 0)		// ensure empty vector
		v.clear();

	if (n <= 0)				// validate number of elements
		error("fibonacci() invalid number of elements", n);

	v.push_back(x);
	v.push_back(y);

	for (int i = v.size(); i < n; ++i)
		v.push_back(v[i - 2] + v[i - 1]);

	string label = "Fibonacci series for " + to_string(x) + " " + to_string(y);
	print(label, v);
}

// --------------------------------------------------------

vector<int> reverse_copy(const vector<int>& v)
// create copy of vector with elements in reverse order
{
	vector<int> c;	// new vector of same size
	for (int i = v.size() - 1; i >= 0; --i)
		c.push_back(v[i]);

	return c;
}

vector<int> reverse_original(vector<int>& v)
// reverse elements in vector of ints
{
	int right = 0;
	for (int left = 0, right = v.size() - 1; left < right; ++left, --right)
		swap(v[left], v[right]);
	return v;
}

// --------------------------------------------------------

vector<string> reverse_copy(const vector<string>& vs)
// create copy of vector with elements in reverse order
{
	vector<string> cs;	// new vector of same size
	for (int i = vs.size() - 1; i >= 0; --i)
		cs.push_back(vs[i]);

	return cs;
}

vector<string> reverse_original(vector<string>& vs)
// reverse elements in vector of strings
{
	int right = 0;
	for (int left = 0, right = vs.size() - 1; left < right; ++left, --right)
		swap(vs[left], vs[right]);
	return vs;
}

// --------------------------------------------------------
// Create vector of Fibonnaci numbers and print them using print() from Exercise 2.
// Create function fibonacci(x,y,v,n) where x, y are first two values,
// v is an empty vector<int>, and n is number of elements to generate store in vector
void exercise3()
{
	vector<int> v;
	fibonacci(1, 2, v, 70);
}

// --------------------------------------------------------
// Write two functions that reverse the order of elments in vector<int>
// reverse_copy(): produces and returns a new vector, do not modify original
// reverse_original(): modifies and returns original
void exercise5()
{
	vector<int> v;
	v.push_back(1); v.push_back(3); v.push_back(0); v.push_back(5); v.push_back(7); v.push_back(9);
	print("Original", v);
	vector<int> c = reverse_copy(v);
	v = reverse_original(v);
	print("Original Reversed", v);
	print("Reverse Copy", c);
}

// --------------------------------------------------------
// Write the two functions from Exercise 6, but using strings instead of ints
// reverse_copy(): produces and returns a new vector, do not modify original
// reverse_original(): modifies and returns original
void exercise6()
{
	vector<string> vs;
	vs.push_back("These");	vs.push_back("warehouse");	vs.push_back("wages");	vs.push_back("kill");
	vs.push_back("the");	vs.push_back("ends");	vs.push_back("introduction");	vs.push_back("\n");
	vs.push_back("Man");	vs.push_back("I");	vs.push_back("should");	vs.push_back("have");
	vs.push_back("schooled");	vs.push_back("it");	vs.push_back("up");	vs.push_back("when");
	vs.push_back("I");	vs.push_back("was");	vs.push_back("younger");	vs.push_back("\n");
	vs.push_back("Should");	vs.push_back("have");	vs.push_back("stuck");	vs.push_back("the");
	vs.push_back("plan");

	print("Guarantees", vs);
	vector<string> reverse_vs = reverse_copy(vs);
	print("Backwards", reverse_vs);
	vs = reverse_original(vs);
	print("Reversed Original", vs);
}


void print_name_age(const vector<string>& name, const vector<int>& age)
// print name,age pairs from corresponding vectors
{
	for (int i = 0; i < name.size(); ++i)
		cout << name[i] << "\t" << age[i] << '\n';
}

// --------------------------------------------------------
// Read names into a vector, then prompt user for ages and store in another vector
// Sort names alphabetically, then print name/age pairs (age vector must be in correct order afte sort)
void exercise7()
{
	const int max_names = 5;
	vector<string> name;
	vector<int> age;
	string input;

	cout << "Enter " << max_names << " names:\n";
	while (name.size() < max_names && cin >> input)
		name.push_back(input);

	cout << "Enter age for each person: \n";
	int inp;
	for (int i = 0; i < name.size(); ++i)
	{
		cout << name[i] << ": ";
		if (!(cin >> inp))
			error("exercise7(): invalid age input");
		age.push_back(inp);
	}

	cout << "\nNames & Ages:\n";
	print_name_age(name, age);

	// Sort name aphabetically and update age to match new sorting
	vector<string> name_copy = name;	// to reference original order
	sort(name.begin(), name.end());		// sort name aphabetically

	vector<int> sorted_age;
	for (int i = 0; i < name.size(); ++i)	// for each name...
	{
		int age_index = 0;
		for (int j = 0; j < name_copy.size(); ++j)	// find index for name using copy
		{
			if (name_copy[j] == name[i])
			{
				age_index = j;						// and retrieve age
				break;
			}
		}
		sorted_age.push_back(age[age_index]);		// add age to sorted_age
	}

	cout << "\nSorted Names & Ages:\n";
	print_name_age(name, sorted_age);
}

// --------------------------------------------------------
// Repeat Exercise 7, but allow for an arbitrary number of names
void exercise8()
{
	const string done = "done";
	vector<string> name;
	vector<int> age;

	cout << "Enter names one per line (\"done\" when finished):\n";
	string input;
	while (getline(cin, input) && input != done)
		name.push_back(input);

	cout << "Enter age for each person:\n";
	int inp;
	for (int i = 0; i < name.size(); ++i)
	{
		cout << name[i] << ": ";
		if (!(cin >> inp))
			error("exercise7(): invalid age input");
		age.push_back(inp);
	}

	cout << "\nNames & Ages:\n";
	print_name_age(name, age);

	// Sort name aphabetically and update age to match new sorting
	vector<string> name_copy = name;	// to reference original order
	sort(name.begin(), name.end());		// sort name aphabetically

	vector<int> sorted_age;
	for (int i = 0; i < name.size(); ++i)	// for each name...
	{
		int age_index = 0;
		for (int j = 0; j < name_copy.size(); ++j)	// find index for name using copy
		{
			if (name_copy[j] == name[i])
			{
				age_index = j;						// and retrieve age
				break;
			}
		}
		sorted_age.push_back(age[age_index]);		// add age to sorted_age
	}

	cout << "\nSorted Names & Ages:\n";
	print_name_age(name, sorted_age);
}

// --------------------------------------------------------
double calc_value(const vector<double>& price, const vector<double>& weight)
{
	if (price.size() != weight.size())
		error("calc_value: vector sizes do not match");

	double value = 0.0;
	for (int i = 0; i < price.size(); ++i)
		value += price[i] * weight[i];

	return value;
}

// Create function that sums the price * weight for elements in a vector
void exercise9()
{
	vector<double> price;
	vector<double> weight;

	price.push_back(5.00); weight.push_back(20);
	price.push_back(1.25); weight.push_back(100);
	price.push_back(60.50); weight.push_back(4);

	cout << "Value Index: " << calc_value(price, weight) << '\n';
}

// --------------------------------------------------------
// Returns greatest value in vector
int maxv(const vector<int>& v)
{
	if (v.size() == 0)	error("maxv: empty vector");
	vector<int>::const_iterator max = std::max_element(v.begin(), v.end());
	return *max;
}

// Write a function that returns the largest element in a vector
// Treating at int due to unfamiliarity with templates
void exercise10()
{
	vector<int> v;
	v.push_back(10);	v.push_back(22);	v.push_back(8);
	v.push_back(5);		v.push_back(-7);	v.push_back(16);

	cout << maxv(v) << '\n';

}

// --------------------------------------------------------
// find least value in vector
int minv(const vector<int>& v)
{
	if (v.size() == 0)	error("minv: empty vector");
	vector<int>::const_iterator min = std::min_element(v.begin(), v.end());
	return *min;
}

// calculate mean of a vector of ints
double meanv(const vector<int>& v)
{
	if (v.size() == 0)	error("meanv: empty vector");
	double sum = 0.0;
	for (int x : v)
		sum += x;
	return sum / v.size();
}

// calculate median of a vector of ints
double medianv(const vector<int>& v)
{
	if (v.size() == 0)	error("medianv: empty vector");

	vector<int> copy = v;	// create copy of vector
	sort(copy);				// sort copy

	double median = 0.0;
	if (copy.size() % 2 == 0)
	{
		int left = copy[copy.size() / 2] - 1;
		int right = copy[(copy.size() / 2)];
		cout << "l = " << left << ", r = " << right << endl;

		return (left + right) / 2.0;
	}
	else
		return copy[copy.size() / 2];

}

// holds min, max, mean, median of a set of data
struct stats
{
	int max;
	int min;
	double mean;
	double median;
};

// collect values for stats struct
stats calc_results(const vector<int> v)
{
	stats results;
	results.max = maxv(v);
	results.min = minv(v);
	results.mean = meanv(v);
	results.median = medianv(v);

	return results;
}

// create function that finds min/max/mean/median given a vector of ints
// return results via struct or reference parameters (no globals)
void exercise11()
{
	vector<int> v;
	v.push_back(12); v.push_back(18); v.push_back(-3); v.push_back(7); v.push_back(29);
	v.push_back(-9); v.push_back(2); v.push_back(6); v.push_back(9); v.push_back(1);
	v.push_back(100);

	stats results = calc_results(v);

	cout << "Min: " << results.min << '\n'
		<< "Max: " << results.max << '\n'
		<< "Mean: " << results.mean << '\n'
		<< "Median: " << results.median << '\n';
}

// --------------------------------------------------------
// print strings in vector until quit string
void print_until_s(const vector<string> v, const string quit)
{
	for (string s : v)
	{
		if (s == quit) return;
		cout << s << '\n';
	}
}

// print strings in vector until 2nd quit string
void print_until_ss(const vector<string> v, const string quit)
{
	const int quit_count = 2;
	int sentinel = 0;
	for (string s : v)
	{
		if (s == quit)
		{
			++sentinel;
			if (sentinel == quit_count) return;
		}
		cout << s << '\n';
	}
}

// improve print_until_s() function from Chapter 8.
void exercise12()
{
	vector<string> v;

	v.push_back("My"); v.push_back("name"); v.push_back("is"); v.push_back("Inigo"); v.push_back("Montoya");
	v.push_back("quit"); v.push_back("You"); v.push_back("killed"); v.push_back("my"); v.push_back("father");
	v.push_back("Prepare"); v.push_back("quit"); v.push_back("to");  v.push_back("die");

	print_until_ss(v, "quit");


}

// --------------------------------------------------------
struct string_order
{
	string first;
	string last;
};

struct string_length
{
	string shortest;
	string longest;
};

string_order string_first_last(const vector<string>& v)
{
	if (v.size() == 0)	error("string_first_last: empty vector");
	string_order results;
	results.first = v[0];
	results.last = v[0];

	for (string s : v)
	{
		if (s < results.first)
			results.first = s;
		if (s > results.last)
			results.last = s;
	}
	return results;
}

string_length string_shortest_longest(const vector<string>& v)
{
	if (v.size() == 0) error("string_shortest_longest: empty vector");
	string_length results;
	results.shortest = v[0];
	results.longest = v[0];

	for (string s : v)
	{
		if (s.size() < results.shortest.size())
			results.shortest = s;
		if (s.size() > results.longest.size())
			results.longest = s;
	}
	return results;
}

vector<int> calc_lengths(const vector<string>& v)
{
	vector<int> lengths;
	for (string s : v)
		lengths.push_back(s.size());
	return lengths;
}

// Write function that takes vector<string> and returns a new vector<int> with string sizes
void exercise13()
{
	vector<string> words;
	words.push_back("broken"); words.push_back("sundown"); words.push_back("fatherless"); words.push_back("showdown");
	words.push_back("gun"); words.push_back("have"); words.push_back("a"); words.push_back("broken"); words.push_back("lip");
	words.push_back("bottle"); words.push_back("sip"); words.push_back("ya"); words.push_back("i"); words.push_back("suck"); words.push_back("dick");
	words.push_back("loose"); words.push_back("grip"); words.push_back("on"); words.push_back("gravity"); words.push_back("force");

	vector<int> words_length = calc_lengths(words);
	string_order alpha_order = string_first_last(words);
	string_length sizes = string_shortest_longest(words);

	cout << "List of words and their lengths:\n";
	for (int i = 0; i < words.size(); ++i)
		cout << "(" << words_length[i] << ")\t" << words[i] << "\n";
	cout << '\n';
	cout << "Shortest Word: " << sizes.shortest << '\n';
	cout << "Longest Word: " << sizes.longest << '\n';
	cout << "First Alphabetically: " << alpha_order.first << '\n';
	cout << "Last Alphabetically: " << alpha_order.last << '\n';
}

// --------------------------------------------------------

void test_const_pbv(const int n)
{
	cout << n << endl;

}


// Test using const on pass-by-value
void exercise14()
{
	int x = 5;
	test_const_pbv(x);

}



// --------------------------------------------------------
int main()
try {
	
	exercise14();
	return 0;
}
catch (runtime_error& e)
{
	cout << "error: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cout << "unknown error\n";
	return 2;
}
