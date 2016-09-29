// Drills.cpp
// 

#include "../../std_lib_facilities.h"

// represents the base unit determined by grammar
class Token
{
public:
	char kind;						// operators: + - * / ( ), '8' = a number
	double value;
	Token(char ch)
		:kind(ch), value(0) {};		// class constructor with one argument
	Token(char ch, double val)
		:kind(ch), value(val) {};	// class constructor with two arguments
};

class Token_stream
{
public:
	Token_stream();				// default constructor
	void putback(Token t);
	Token get();
private:
	bool full{ false };			// is there a Token in the buffer?
	Token buffer;				// store a token put back using putback()
};

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
	:full(false), buffer(0)    // no Token in buffer
{
}

// store a token in Token_stream
void Token_stream::putback(Token t) 
{
	if (full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch)
	{
	case ';':					// for "print"
	case 'q':					// for "quit"
	case '(':	case '+':	case '-':	case '*': case '/':
		return Token{ ch };		// let each character represent itself
	case '.':	
	case '0':	case '1':	case '2':	case '3':	case '4':
	case '5':	case '6':	case '7':	case '8':	case '9':
	{
		cin.putback(ch);		// put digit back into the input stream
		double val;
		cin >> val;
		return Token{ '8', val };
	}
	default:
		error("Bad token");
		return 0;
	}
}


Token_stream ts;				// provides get() and pushback()
double expression();			// function prototype

double primary()				// deal with numbers and parenthesis
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '8':					// token kind '8' represents a number
		return t.value;
	default:
		error("primary expected");
		return 0;
	}
}

double term()					// deal with * and /
{
	double left = primary();
	Token t = ts.get();

	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);		// put t back into the Token stream
			return left;
		}
	}
}

double expression()				// deal with + and -
{
	double left = term();
	Token t = ts.get();

	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term();		// evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();		// evaluate Term and subract
			t = ts.get();
			break;
		default:
			ts.putback(t);		// but t back into the token stream
			return left;		// finally: no more + or -, return the answer
		}
	}
}




int main()
{
	try
	{
		double val = 0;
		while (cin)
		{
			Token t = ts.get();

			if (t.kind == 'q') break; // 'q' for quit
			if (t.kind == ';')        // ';' for "print now"
				cout << "=" << val << '\n';
			else
				ts.putback(t);
			val = expression();
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
}