#include <iostream>
#include <Book.h>
Book::Book(const std::string& title, const std::string& author, const int year, const std::string& isbn)
{
	if (year < 1450 || year>2025)
	{
		throw "Не тот год";
	}
	this->title = title;
	this->author = author;
	this->year = year;
	this->isbn = isbn;
	this->isAvailable = true;
	this->borrowedBy = "";

}
std::string Book::getTitle() const
{
	return title;
}
std::string Book::getAuthor() const
{
	return author;
}
int Book::getYear() const
{
	return year;
}
std::string Book::getIsbn() const
{
	return isbn;
}
bool Book::getIsAvailable() const
{
	return isAvailable;
}
std::string Book::getBorrowedBy() const
{
	return borrowedBy;
}
void Book::borrowBook(const std::string& userName)
{
	borrowedBy = userName;
	isAvailable=false;
}
void Book::returnBook()
{
	borrowedBy = "";
	isAvailable = true;
}
void Book::displayInfo() const
{
	std::cout << "Название: " << getTitle() << std::endl;
	std::cout << "Автор: " << getAuthor() << std::endl;
	std::cout << "Год: " << getYear() << std::endl;
	std::cout << "Номер: " << getIsbn() << std::endl;
	std::cout << "Наличие: " << getIsAvailable() << std::endl;
	std::cout << "Владелец: " << getBorrowedBy() << std::endl;
}