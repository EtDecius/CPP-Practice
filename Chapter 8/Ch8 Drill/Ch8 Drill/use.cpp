// use.cpp

/*
#include <iostream>
#include "my.h"

int foo = 7;	// must be declared outside of main()

int main()
{

//	print_foo();
//	print(99);

	const int cx = 7;
	const int cy = 9;

	swap_v(7.7, 9.9);



	
	std::cout << cx << ", " << cy << '\n';

	return 0;
}
*/

#include <iostream>

namespace X {
	int var;
	void print() { std::cout << var << '\n'; }

}

namespace Y {
	int var;
	void print() { std::cout << var << '\n'; }

}

namespace Z {
	int var;
	void print() { std::cout << var << '\n'; }
}

int main()
{
	X::var = 7;
	X::print();
	using namespace Y;
	var = 9;
	print();
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();
	}
	print();
	X::print();

}

