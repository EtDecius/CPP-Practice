// Ch9Ex5.cpp
// Chapter 9, Exercises 5-9 (p.339)
// Implement Book, Patron, Library classes
// Note: fees do not work properly, do not appear to be recorded

#include "../../../std_lib_facilities.h"
#include "Chrono.hpp"

// ------------------------- Book Class ------------------------
enum class Genre {
	fiction, nonfiction, periodical, biography, children
};

class Book {
public:
	class Invalid {};		// to throw as exception
	
	Book(string title, string author, string isbn, int copyright, Genre genre);
	string get_title() const { return title; }
	string get_author() const { return author; }
	string get_isbn() const { return isbn; }
	Genre get_genre() const { return genre; }
	int get_copyright() const { return copyright; }
	bool is_checked_out() const { return checked_out; }
	void check_in();
	void check_out();

private:
	string isbn;					// int'l standard book number
	string title;
	string author;
	int copyright;
	Genre genre;
	bool checked_out;
	bool valid_isbn(string s) const; // validate psuedo isbn format
};

Book::Book(string title, string author, string isbn, int copyright, Genre genre)
	: title{ title }, author{ author }, isbn{ isbn }, copyright{ copyright }, genre{ genre }
{
	if (!valid_isbn(isbn)) throw Invalid{};
	checked_out = false;
}

void Book::check_in()
{
	if (!checked_out) error("check_in() book already checked in " + title);
	checked_out = false;
}

void Book::check_out()
{
	if (checked_out) error("check_out() book already checked out " + title);
	checked_out = true;
}

// validate adherence to psuedo isbn format: #-#-#-char/digit
bool Book::valid_isbn(string isbn) const
{
	if (isbn.size() < 7) 			// min length to meet criteria
		return false;

	int i = 0;
	int dashes = 0;
	while (dashes < 3)				// check for 3 "num-dash" pairs
	{
		if (!isdigit(isbn[i]))		// must start with number
			return false;
		while (isdigit(isbn[i]))	// read in digits until next dash
			++i;
		if (isbn[i] != '-')			// expected dash not found
			return false;
		else
		{
			++dashes;
			++i;
		}
	}
	if (!(isdigit(isbn[i]) || isalpha(isbn[i]))) // check final element digit or letter
		return false;

	return true;					// all checks passed
}

// print Book details to ostream
ostream& operator<<(ostream& os, const Book& b)
{
	return os << b.get_title() << '\n'
		<< b.get_author() << '\n'
		<< "ISBN: " << b.get_isbn();
}

// compare titles & ISBNs
bool operator==(Book& b1, Book& b2)
{
	return b1.get_isbn() == b2.get_isbn()
		&& b1.get_title() == b2.get_title();
}

// compare ISBN
bool operator !=(Book& b1, Book& b2)
{
	return !(b1 == b2);
}

// ------------------------ Patron Class -----------------------
class Patron {
public:
	Patron(string name, string card_num);

	string get_name() const { return name; }
	string get_card_number() const { return card_number; }
	double get_fees() const { return fees; }
	bool owes_fees() const { return fees > 0.0; }

	void set_fees(double d);							// set fee to flat amount
	void increase_fees(double d) { fees += d; }			// increase fee by specified amount
	void decrease_fees(double d);						// reduce fee by specified amount

private:
	string name;
	string card_number;
	double fees;
	bool valid_card_number(string s);					// validate card number

};

Patron::Patron(string name, string card_num)
	: name{ name }, card_number{ card_num }, fees{ 0.0 }
{
	if (!valid_card_number(card_num)) error("Patron() invalid card number" + card_num);
}

// set fee to flat amount
void Patron::set_fees(double d)
{
	if (d < 0.0) error("set_fees() cannot set negative value");
	fees = d;

}

// reduce fee by specified amount
void Patron::decrease_fees(double d)
{
	if (d > fees) error("decrease_fees() fee less than amount paid");
	fees -= d;
}

bool Patron::valid_card_number(string s)
{
	if (s.size() <= 0)
		return false;
	for (int i = 0; i < s.size(); ++i)
		if (!isdigit(s[i]))
			return false;
	return true;
}

bool operator==(const Patron& p1, const Patron& p2)
{
	return p1.get_name() == p2.get_name()
		&& p1.get_card_number() == p2.get_card_number();
}

bool operator!=(const Patron& p1, const Patron& p2)
{
	return !(p1 == p2);
}

ostream& operator<<(ostream& os, const Patron& p)
{
	return os << p.get_name() << ", Card# " << p.get_card_number() << " Fees: " << p.get_fees();
}


// --------------------- Transaction Class ---------------------
// Record of Library transactions
struct Transaction {
	Patron patron;
	Book book;
	Chrono::Date date;
};

ostream& operator<<(ostream& os, Transaction& t)
{
	return os << t.patron.get_name() << " ("
		<< t.patron.get_card_number() << ") "
		<< t.book.get_title() << ", "
		<< t.date << '\n';
}

// ----------------------- Library Class -----------------------
// No duplicate book names
// No duplicate patron names

class Library {
public:
	Library();
	void add_book(const Book& b);
	void add_book(string title, string author, string isbn, int copyright, Genre genre);
	void add_patron(Patron& p);
	void add_patron(string name, string card_number);
	void check_book_out(Book& b, Patron& p, Chrono::Date d);
	void print_patrons() const;						// print list of patrons
	void print_all_fees() const;					// print patrons that owe a late fee

	void add_fee_by_name(string name, double fee);

private:
	vector<Book> books;
	vector<Patron> patrons;						
	vector<Transaction> transactions;			
	bool book_exists(const string title);		// search by title
	bool patron_exists(const string name);		// search by name 

};

Library::Library()
{
}

void Library::add_book(string title, string author, string isbn, int copyright, Genre genre)
{
	if (book_exists(title)) error("add_book() title already exists " + title);
	books.push_back(Book{ title, author, isbn, copyright, genre });
}

void Library::add_book(const Book& b)
{
	if (book_exists(b.get_title())) error("add_book() title already exists " + b.get_title());
	books.push_back(b);
}

void Library::add_patron(string name, string card_number)
{
	if (patron_exists(name)) error("add_patron() name already exists " + name);
	patrons.push_back(Patron{ name, card_number });
}

void Library::add_patron(Patron& p)
{
	if (patron_exists(p.get_name())) error("add_patron() name already exists " + p.get_name());
	patrons.push_back(p);
}

bool Library::book_exists(const string title)
{
	for (const Book& b : books)
		if (b.get_title() == title)
			return true;
	return false;
}

bool Library::patron_exists(const string name)
{
	for (const Patron& p : patrons)
		if (p.get_name() == name)
			return true;
	return false;
}

// print all patrons, one per line
void Library::print_patrons() const
{
	for (const Patron& p : patrons)
		cout << p << '\n';
}

void Library::check_book_out(Book& b, Patron& p, Chrono::Date d)
{
	// ensure user and book exist in system
	if (!book_exists(b.get_title())) error("check_book_out() book does not exist");
	if (!patron_exists(p.get_name())) error("check_book_out() patron does not exist");

	// check for outstanding fees
	if (p.owes_fees()) error("check_book_out() patron owes fees");

	// process checkout and print receipt
	b.check_out();
	Transaction receipt{ p, b, d };
	transactions.push_back(receipt);
	cout << "Check out success:\n" << receipt;
}

// print all patrons that owe late fees
void Library::print_all_fees() const
{
	for (const Patron& p : patrons)
	{
		if (p.owes_fees())
		{
			cout << std::fixed;
			cout << std::setprecision(2);
			cout << p.get_name() << " ("
				<< p.get_card_number() << ") Owed: "
				<< p.get_fees() << '\n';
		}
	}
}

void Library::add_fee_by_name(string name, double fee)
{
	cout << name << ' ' << fee << endl;
	
	for (Patron& p : patrons)
	{
		if (p.get_name() == name)
			p.set_fees(fee);
	}
}


int main()
try {
	
	Library libr;

	// Add some patrons
	Patron picard{ "Jean-Luc Picard", "123456789" };
	Patron riker{ "William T. Riker", "2" };
	Patron troi{ "Deanna Troi", "333333" };
	Patron data{ "Data", "01000100011000010111010001100001" };
	Patron laforge{ "Geordi La Forge", "7777777" };
	Patron worf{ "Worf", "99999" };
	Patron crusher{ "Beverly Crusher", "5555515" };
	libr.add_patron(picard); libr.add_patron(riker); libr.add_patron(troi);  libr.add_patron(data);
	libr.add_patron(laforge); libr.add_patron(worf); libr.add_patron(crusher);

	// Add some books
	Book b1 = { "There are four lights", "Captain Picard", "123-321-1-X", 1997, Genre::nonfiction };
	Book b2 = { "Every Day is a Good Day to Die", "Any Klingon", "5-55-555-0", 1995, Genre::periodical };
	Book b3 = { "Moby-Dick", "Herman Melville", "1-111-2-X", 1851, Genre::fiction };
	Book b4 = { "Every Day is a Good Day to Die, JR.", "QUSD", "1-1-1-1", 2200, Genre::children };
	Book b5 = { "Stardate", "Computer", "123-555-333-X", 2431, Genre::periodical };
	libr.add_book(b1); libr.add_book(b2); libr.add_book(b3); libr.add_book(b4); libr.add_book(b5);

	// Set Dates
	Chrono::Date today{ 2364, Chrono::Month::sep, 12 };
	Chrono::Date next_year = today;
	next_year.add_year(1);

	// Check out some books
	cout << "Check out books:\n";
	libr.check_book_out(b2, worf, today);
	libr.check_book_out(b3, picard, next_year);

	cout << "\nApplying fees to some members:\n";
	libr.add_fee_by_name("William T. Riker", 3.50);
	libr.add_fee_by_name("Data", 0.01);
	
	cout << "\nPrint all fees:\n";
	libr.print_all_fees();
	cout << '\n';
	
	cout << "All members:\n";
	libr.print_patrons();
	cout << '\n';

	libr.check_book_out(b1, data, today);
	
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
