// Ch8Ex1.cpp
// Chapter 8, Exercise 1 (p.300)
// Modify calculator program from Chapter 7 to to make input stream an explicit parameter.

#include "../../../std_lib_facilities.h"

//------------------------------------------------------------------------------

const char number = '8';    // t.kind==number means that t is a number Token
const char quit = 'q';    // t.kind==quit means that t is a quit Token
const char print = ';';    // t.kind==print means that t is a print Token
const char name = 'a';    // name token
const char help = 'h';
const char let = 'L';    // declaration token
const char const_var = 'c';    // const variable declaration token
const string declkey = "let";    // variable declaration keyword 
const string constkey = "const"; // const variable keyword
const string quitkey = "quit";
const string helpkey = "help";
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

							//------------------------------------------------------------------------------

class Token {
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	string name;      // for names: name itself
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
	Token(char ch, string n) : kind(ch), name(n) {}
};

//------------------------------------------------------------------------------

class Token_stream {
public:
	Token_stream(istream&);   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
	void ignore(char c);      // discard tokens up to an including a c
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream(istream&)
	:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get() // read characters from cin and compose a Token
{
	if (full) {         // check if we already have a Token ready
		full = false;
		return buffer;
	}

	char ch;
	//	cin >> ch;          // note that >> skips whitespace (space, newline, tab, etc.)

	cin.get(ch);		// get next char
	while (isspace(ch) && ch != '\n')	// skip whitespace except newline
		cin.get(ch);


	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
		return Token(ch); // let each character represent itself
						  //	case 'h':
						  //	case 'H':
						  //		return help;
	case print:
	case '\n':
		return print;
	case '.':             // a floating-point literal can start with a dot
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':    // numeric literal
	{
		cin.putback(ch);// put digit back into the input stream
		double val;
		cin >> val;     // read a floating-point number
		return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.putback(ch);
			if (s == declkey) return Token(let); // keyword "let"
			if (s == constkey) return Token(const_var); // keyword "const"
			if (s == quitkey) return Token(quit);	// keyword "quit"
			if (s == helpkey) return Token(help);	// keyword "help"
			return Token(name, s);
		}
		error("Bad token");
	}
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
// c represents the kind of a Token
{
	// first look in buffer:
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	// now search input:
	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

//------------------------------------------------------------------------------

// Token_stream ts;        // provides get() and putback() 

						//------------------------------------------------------------------------------

class Variable {
public:
	string name;
	double value;
	bool is_const;		// const value, cannot be changed after creation
	Variable(string n, double v) :name(n), value(v) { }
	Variable(string n, double v, bool con) :name(n), value(v), is_const(con) {};
};

//------------------------------------------------------------------------------


class Symbol_table {
public:
	double get_value(string s);
	void set_value(string s, double d);
	double define_name(string var, double val, bool is_const);

private:
	vector<Variable> var_table;
	bool is_declared(string var);
	void set_const(string var);
};

//------------------------------------------------------------------------------

double Symbol_table::get_value(string s)
// return the value of the Variable names s
{
	for (int i = 0; i<var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined variable ", s);
}

//------------------------------------------------------------------------------

void Symbol_table::set_value(string s, double d)
// set the Variable named s to d
{
	for (int i = 0; i < var_table.size(); ++i)
	{
		if (var_table[i].name == s)
		{
			if (var_table[i].is_const == true)
				error("set: cannot change const value");
			var_table[i].value = d;
			return;
		}
	}
	error("set: undefined variable ", s);
}

//------------------------------------------------------------------------------

bool Symbol_table::is_declared(string var)
// is var already in var_table?
{
	for (int i = 0; i<var_table.size(); ++i)
		if (var_table[i].name == var) return true;
	return false;
}

//------------------------------------------------------------------------------

void Symbol_table::set_const(string var)
// set var to be const
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == var)
		{
			var_table[i].is_const = true;
			return;
		}
	error("set_const: undefined variable ", var);
}

double Symbol_table::define_name(string var, double val, bool is_const)
// add (var,val) to var_table
{
	if (is_declared(var))
	{
		set_value(var, val);
		if (is_const)
			set_const(var);
	}
	else
		var_table.push_back(Variable(var, val, is_const));
	return val;
}

//------------------------------------------------------------------------------

Symbol_table user_variable;

//------------------------------------------------------------------------------

double expression(Token_stream&);    // declaration so that primary() can call expression()

						//------------------------------------------------------------------------------

						// deal with numbers and parentheses
double primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':           // handle '(' expression ')'
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case number:
		return t.value;    // return the number's value
	case name:
	{
		Token t2 = ts.get();
		if (t2.kind == '=')		// handle variable reassignment
		{
			user_variable.set_value(t.name, expression(ts));
			return user_variable.get_value(t.name);
		}
		ts.putback(t2);			// not reassignment, put back token
		return user_variable.get_value(t.name); // return the variable's value
	}
	case '-':
		return -primary(ts);
	case '+':
		return primary(ts);
	default:
		error("primary expected");
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term(Token_stream& ts)
{
	double left = primary(ts);
	Token t = ts.get(); // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary(ts);
			t = ts.get();
			break;
		case '/':
		{
			double d = primary(ts);
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(term(ts));
			if (i2 == 0) error("%: divide by zero");
			left = i1%i2;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);        // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression(Token_stream& ts)
{
	double left = term(ts);      // read and evaluate a Term
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term(ts);    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term(ts);    // evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

double declaration(Token_stream& ts)
// handle: name = expression
// declare a variable called "name" with the initial value "expression"
{
	Token var_type = ts.get();	// const, non-const

	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression(ts);
	if (var_type.kind == let)
		user_variable.define_name(var_name, d, false); // user variable
	else
		user_variable.define_name(var_name, d, true);  // const user variable

	return d;
}

//------------------------------------------------------------------------------
void print_help()
{
	cout << "----- Calculator Help -----\n\n"
		<< "Enter mathmatical expression followed by ';' to calculte answer.\n"
		<< "    Ex: 5 + 10;\n\n"
		<< "Supported operations:\n"
		<< "    + Addition\n"
		<< "    - Subtraction\n"
		<< "    * Multiplication\n"
		<< "    / Division\n"
		<< "    % Modulus\n\n"
		<< "Parenthesis ( ) for operation priority.\n"
		<< "    Ex: (2 + 3) * 10;\n\n"
		<< "Custom variables & constants via: \n"
		<< "    let [name] = [value];\tex: let x = 10;\n"
		<< "    const [name] = [value];\tex: const y = 20;\n\n"
		<< "---------------------------\n\n";
}
//------------------------------------------------------------------------------
void print_welcome()
{
	cout << "Calculator in C++ (v. c7). Enter a mathematical statement, \""
		<< helpkey << "\" or \""
		<< quitkey << "\".\n";
}
//------------------------------------------------------------------------------//

double statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
	case const_var:
		ts.putback(t);
		return declaration(ts);
	default:
		ts.putback(t);
		return expression(ts);
	}
}

//------------------------------------------------------------------------------

void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

//------------------------------------------------------------------------------
void calculate()
{
	Token_stream ts(cin);
	
	while (cin)
		try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();    // first discard all "prints"
		if (t.kind == quit) return;        // quit
		if (t.kind == help)	print_help();
		else
		{
			ts.putback(t);
			cout << result << statement(ts) << endl;
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;        // write error message
		clean_up_mess(ts);
	}
}
//------------------------------------------------------------------------------

int main()
try {
	// predefined const variables:
	user_variable.define_name("pi", 3.1415926535, true);
	user_variable.define_name("e", 2.7182818284, true);

	print_welcome();
	calculate();

	keep_window_open();    // cope with Windows console mode
	return 0;
}
catch (exception& e) {
	cerr << e.what() << endl;
	keep_window_open("~~");
	return 1;
}
catch (...) {
	cerr << "exception \n";
	keep_window_open("~~");
	return 2;
}

//------------------------------------------------------------------------------
