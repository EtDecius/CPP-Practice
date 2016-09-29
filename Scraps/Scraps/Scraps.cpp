#include "..\..\std_lib_facilities.h"


int main()
{
	try {
		int x1 = narrow_cast<int>(2.9);
		return 0;
	}
	catch (runtime_error& e) {
		cerr << "runtime error: " << e.what() << '\n';
		return 1;
	}
}