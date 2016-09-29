// Test_output.cpp
// Chapter 11 Drill (p.407)

#include "../../std_lib_facilities.h"

int main()
try {
	
	int birth_year = 1983;
	int current_year = 2016;

	cout << showbase
		<< "Decimal: " << "\t" << birth_year << '\n'
		<< "Hexadecimal: " << "\t" << hex << birth_year << '\n'
		<< "Octal: " << "\t\t" << oct << birth_year << "\n\n";

	cout << "Current Age: " << dec << current_year - birth_year << '\n';


	int a, b, c, d;
	cin >> a >> oct >> b >> hex >> c >> d;
	cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

		
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