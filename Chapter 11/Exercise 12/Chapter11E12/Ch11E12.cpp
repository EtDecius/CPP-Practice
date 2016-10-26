// Chapter11E12.cpp
// Chapter 11, Exercise 12 (p.409)
// Reverse the order of characters in a text file. For example, asdfghjkl
// becomes lkjhgfdsa.

#include "../../../std_lib_facilities.h"

void welcome()
{
	cout << "File Reverser v0.1\n\n";
}

void reverse_file_contents(const string& filename)
{
	// open file
	fstream fio{ filename, ios_base::in};
	if (!fio) error("failed to open file ", filename);

	// store buffer contents temporarily
	vector<char> buffer;
	char next;
	while (fio.get(next))
		buffer.push_back(next);

	// clear file contents
	fio.close();
	fio.open(filename, ios_base::trunc | ios_base::out);
	if (!fio) error("clear_file() failed to clear file ", filename);

	// print buffer contents from end to front
	for (int i = buffer.size() - 1; i >= 0; --i)
		fio << buffer[i];
}

int main()
try {
	welcome();

	cout << "Enter file name: ";
	string filename;
	cin >> filename;

	reverse_file_contents(filename);
	cout << "File reversed.\n";

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