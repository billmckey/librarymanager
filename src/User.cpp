#include <iostream>
#include <User.h>
User::User(const std::string& name, const std::string& userId)
{
	this->name = name;
	this->userId = userId;
	this->borrowedBooks = {};
	this->maxBooksAllowed = 3;

}
std::string User::getName() const
{
	return name;
}
std::string User::getUserId() const
{
	return userId;
}
const std::vector<std::string>& User::getBorrowedBooks() const
{
	return borrowedBooks;
}
int User::getMaxBooksAllowed() const
{
	return maxBooksAllowed;
}

bool User::canBorrowMore() const
{
	return borrowedBooks.size() < maxBooksAllowed;
}
void User::addBook(const std::string& isbn)
{
	if (canBorrowMore())
	{
		borrowedBooks.push_back(isbn);
	}
	else
	{
		throw"Слишком много читать вредно";
	}
}
void User::removeBook(const std::string& isbn)
{
	for (int i = 0; i < borrowedBooks.size(); i++)
	{
		if (borrowedBooks[i] == isbn)
		{
			borrowedBooks[i] = borrowedBooks.back();
			borrowedBooks.pop_back();
			return;
		}
	}
	throw"Такой книги нет";
}
void User::displayProfile() const
{
	std::cout << "USER" << std::endl;
	std::cout << "Имя: " << name << std::endl;
	std::cout << "Userid: " << userId << std::endl;
	std::cout << "Взято книг: " << borrowedBooks.size() << std::endl;
	if (borrowedBooks.size() > 0)
	{
		std::cout << "Книги: ";
		for (int i = 0; i < borrowedBooks.size(); i++)
		{
			std::cout << borrowedBooks[i] << " ";
		}
	}
	
} 