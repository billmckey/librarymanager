#pragma once
#include <string>
class Book
{
private:
	std::string title;
	std::string author;
	int year;
	std::string isbn;
	bool isAvailable;
	std::string borrowedBy;
public:
	Book(const std::string& title, const std::string& author, const int year, const std::string& isbn);
	void borrowBook(const std::string& userName);
	void returnBook();
	void displayInfo() const;

	std::string getTitle() const;
	std::string getAuthor() const;
	int getYear() const;
	std::string getIsbn() const;
	bool getIsAvailable() const;
	std::string getBorrowedBy() const;
};