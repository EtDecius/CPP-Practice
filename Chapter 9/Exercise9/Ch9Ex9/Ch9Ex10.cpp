// Ch9Ex10.cpp
// Chapter 9, Exercise 10 (p.340)
// Expand Date class from Chapter 9

#include "Chrono.hpp";

int main()
try {
	using namespace Chrono;

	Date test{ 1999, Month::dec, 31 };
	
	for (int i = 0; i < 30; ++i)
	{
		cout << test << endl;
		test.add_month(1);
	}


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