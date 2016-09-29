// ErrorChecking.cpp
// Chapter 5 Drill (p.167)

#include "../../std_lib_facilities.h"

int main()
try {

	cout << "Success!\n";

}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	return 2;
}
