// Ch9Ex4.cpp
// Chapter 9, Exercise 4 (p.339)

// dangerously ugly code
struct X								// struct called X that holds a bunch of shit
{								
	void f(int x)						// X struct has a function called f(), invoke via X.f();
	{									
		struct Y						// A struct Y exists while X.f() is on stack
		{								
			int f() { return 1; }		// inline function always returns 1. Invoked by Y.f() while X.f() is on stack
			int m;						// unused member of struct Y
		};
		int m;							// local variable in X.f() (not same as Y.m)
		m = x;							// assign X.f() argument to m
		Y m2;							// Create a Y object called m2;

		return f(m2.f());				// Oh my god, is X.f() recursive?
										// To return X.f(), it calls itself and passes it m2.f() as an argument
										// Before X.f() is invoked, m2.f() is resolves to return 1
										// So return calls X.f(1)
										// Within new call to X.f(1), local m set to 1
										// But then recursion sets in and there is no terminal point
										// So program loops forever
	}	
											
	int m;								// member of X, access via X.m
	void g(int m) 						// 2nd member function of struct X
	{
		if (m)							// m is an int, so evaluates if (m == 0)
			f(m + 2);					// call to X.f, which leads us to recursive hell
		else                            // only happens if m == 0
		{								// unnecessary brackets
			g(m + 2);					// recursive call, will evaluate as g(2) and lead to X.f() infinite recursion
		}
	}
	X () {}								// empty constructor for struct X
	void m3()							// 3rd member function, does nothing
	{

	}

	void main()							// 4th member function, called main() but is not entry point to program
	{									// since it is declared within a class/struct
		X a;							// create a new struct X called a
		a.f(2);							// call X.f(2) for a, leading to infinite recursion
	}
};