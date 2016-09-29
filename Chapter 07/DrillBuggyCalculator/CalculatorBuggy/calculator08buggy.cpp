
/*
calculator08buggy.cpp

Helpful comments removed.
We have inserted 3 bugs that the compiler will catch and 3 that it won't.

Compilation Errors: 
1) Added Token constructor for strings
*** NOTE: Compiled after 1 change. Compiler did not catch 2 other bugs

Logic Errors:
1) In Token_stream::get(), while loop within default case:
	s = ch;  -->  s += ch;
2) In Token_stream::get(), sentinel for "quit"
	if (s == "quit") return Token(name);  -->  if (s == "quit") return Token(quit);
3) In primary(), no return statement for parenthesis ()
	Add to end of 	case '(': block:		return d;

************************************************************************
A simple calculator program that evaluates expressions.
	
The grammar for input is:

Calculation:
    Statement
    Print
    Quit
    Calculation Statement
    
Statement:
    Declaration
    Expression
    
Declaration:
    "let" Name "=" Expression

Print:
    ;

Quit:
    q 

Expression:
    Term
    Expression + Term
    Expression - Term
Term:
    Primary
    Term * Primary
    Term / Primary
    Term % Primary
Primary:
    Number
    Name
    ( Expression )
    - Primary
    + Primary
	sqrt Primary
Number:
    floating-point-literal







*/

#include "../../../std_lib_facilities.h"

// basic unit for processing input
struct Token {
	char kind;
	double value;
	string name;

	// constructors
	Token(char ch) :kind(ch), value(0), name("") { }				// operators & sentinels
	Token(char ch, double val) :kind(ch), value(val), name("") { }	// numeric values
	Token(char ch, string s) :kind(ch), value(0), name(s) { }		// user variable strings
};

// create Token objects
class Token_stream {
	Token buffer;			// store spare token
	bool full;				// buffer status
public:
	Token_stream() :full(0), buffer(0) { }				// constructor
	Token get();
	void unget(Token t) { buffer = t; full = true; }
	void ignore(char);
};

// supported symbols for token.kind
const char let = '#';		// Drill exercise 10
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqroot = 's';
const char powr = 'p';

// convert input into Token
Token Token_stream::get()
{
	// buffer can store one token at a time
	if (full) 
	{ 
		full = false; 
		return buffer; 
	}

	// read input from cin, convert to Token
	char ch;
	cin >> ch;
	switch (ch) 
	{
	case '(':		// math operators
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':		// modulo
	case ';':		// input completed sentinel
	case '=':		// variable assignment sentinel
	case ',':		// comma seperator for function(x,y) format
	case '#':		// Drill exercise 10, change let to #
		return Token(ch);
	case '.':		// numeric values
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	
		cin.unget();	// return digit to cin stream
		double val;		// then read input as double
		cin >> val;
		return Token(number, val);
	}
	default:			// read input for string sentinels
		if (isalpha(ch)) 
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == "sqrt") return Token(sqroot);
			if (s == "pow") return Token(powr);
//			if (s == "let") return Token(let);		// Drill exercise 10, change "let" to '#'
			if (s == "exit") return Token(quit);	// Drill exercise 11, change "quit" to "exit"
			return Token(name, s);
		}
		error("Bad token");
	}
}

// clear cin stream until char c
void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

// used created variable, ex: let y = 3;
struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;			// stores user-defined variables

// retrieve value for user created variable
double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

// set value for user created variable
void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

// check if user created variable name exists
bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();			// function prototype
double term();

// handle numerals, unary operators, and string sentinels
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case sqroot:
	{	// Drill exercise 7 + 8
		double d = expression();
		if (d < 0) error("cannot sqrt negative value");
		return sqrt(d);
	}
	case powr:
	{	// Drill exercise 9
		t = ts.get();
		if (t.kind != '(') error("pow(#,#) expected");
		double d = expression();
		t = ts.get();
		if (t.kind != ',') error("pow(#,#) expected");
		int exponent = narrow_cast<int>(term());
		double power = 1.0;
		for (int i = 0; i < exponent; ++i)
			power *= d;
		t = ts.get();
		if (t.kind != ')') error("pow(#,#) expected");
		return power;
	}
	default:
		error("primary expected");
	}
}

// handle multiply, divide and modulo
double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(term());
			if (i2 == 0) error("%: divide by zero");
			left = i1%i2;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

// handle addition and subtraction
double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// handle user created variable
double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

// handle execution paths for user created variables, math expressions
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

// clear out Token_stream until print char found
void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

// add set of pre-defined user variables
void predefine_variables()
{
	names.push_back(Variable("k", 1000.0));
	names.push_back(Variable("pi", 3.14159));
}

// primary program loop. begin input parsing, handle sentinel characters
// clean up errors when needed
void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
try {
	predefine_variables();
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c&& c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}
