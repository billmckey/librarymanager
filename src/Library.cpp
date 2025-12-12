#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>

Library::Library(const std::string& dataFile) : dataFile(dataFile)
{
	loadFromFile();
}
void Library::addBook(const Book& book)
{
	books.push_back(book);
}
void Library::addUser(const User& user)
{
	users.push_back(user);
}
void Library::displayAllBooks() const
{
	std::cout << "Все книги: "<< std::endl;
	for (int i = 0; i < books.size(); i++)
	{
		books[i].displayInfo();
		std::cout<< std::endl;
	}
}
void Library::displayAllUsers() const
{
	std::cout << "Все пользователи: " << std::endl;
	for (int i = 0; i < users.size(); i++)
	{
		users[i].displayProfile();
		std::cout << std::endl;
	}
}
Book* Library::findBookByISBN(const std::string& isbn)
{
	for (int i = 0; i < books.size(); i++)
	{
		if (books[i].getIsbn() == isbn)
		{
			return &books[i];
		}
	}
	return nullptr;
	
}
User* Library::findUserByName(const std::string& name)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getName() == name)
		{
			return &users[i];
		}
	}
	return nullptr;
}
void Library::returnBook(const std::string& isbn)
{
	Book* book = findBookByISBN(isbn);
	if (book == nullptr)
	{
		std::cout << "Нет такой";
		return;
	}
	if (book->getIsAvailable())
	{
		std::cout << "Никто не брал"<<std::endl;
		return;
	}
	std::string TimeName = book->getBorrowedBy();
	User* user = findUserByName(TimeName);
	if (user == nullptr)
	{
		std::cout << "Нет такого"<<std::endl;
	}
	book->returnBook();
	if (user != nullptr)
	{
		user->removeBook(isbn);
	}
	std::cout<<"Книга сдана"<<std::endl;
}
void Library::borrowBook(const std::string& userName, const std::string& isbn)
{
	Book* book = findBookByISBN(isbn);
	if (book == nullptr)
	{
		std::cout << "Нет такого" << std::endl;
		return;
	}
	if (!book->getIsAvailable())
	{
		std::cout<<"Книга уже выдана"<<std::endl;
		return;
	}
	User* user = findUserByName(userName);
	if (user == nullptr)
	{
		std::cout<<"Нет такого"<<std::endl;
		return;
	}
	if (!user->canBorrowMore())
	{
		std::cout << "Предел книг" << std::endl;
		return;
	}
	book->borrowBook(userName);
	user->addBook(isbn);
	std::cout << "Книга выдана" << std::endl;
}

void Library::saveToFile()
{
#ifdef _WIN32
	system("mkdir data 2>nul");
#else
	system("mkdir -p data 2>/dev/null");
#endif
	std::ofstream file(dataFile);
	if (!file.is_open())
	{
		std::cout << "Ошибка с путем: " << dataFile << std::endl;
		std::cout << "Пробую: library_data.txt" << std::endl;
		file.open("library_data.txt");
		if (!file) 
		{
			std::cout << "Ошибка сохранения" << std::endl;
			return;
		}
	}
	for (int i = 0; i < books.size(); i++)
	{
		const Book& book = books[i];
		file << "BOOK\n";
		file << "Title: " << book.getTitle() << "\n";
		file << "Author: " << book.getAuthor() << "\n";
		file << "Year: " << book.getYear() << "\n";
		file << "ISBN: " << book.getIsbn() << "\n";
		file << "Available: " << (book.getIsAvailable() ? "yes" : "no") << "\n";
		file << "BorrowedBy: " << book.getBorrowedBy() << "\n\n";
	}

	file << "---USERS---\n\n";

	for (int i = 0; i < users.size(); i++)
	{
		const User& user = users[i];
		file << "USER\n";
		file << "Name: " << user.getName() << "\n";
		file << "UserID: " << user.getUserId() << "\n";
		std::vector<std::string> borrowed = user.getBorrowedBooks();
		file << "BorrowedBooks: ";
		for (size_t j = 0; j < borrowed.size(); j++) 
		{
			file << borrowed[j];
			if (j != borrowed.size() - 1) file << "|";
		}
		file << "\n";
		file << "MaxBooks: " << user.getMaxBooksAllowed() << "\n\n";
	}
	file.close();
	std::cout << "Данные успешно сохранены в " << dataFile << std::endl;
}
void Library::loadFromFile()
{
	std::ifstream file(dataFile);
	if (!file.is_open()) 
	{
		std::cout << "Файл не найден" << std::endl;
		return;
	}
	std::cout << "Загрузка данных из файла..." << std::endl;
	books.clear();
	users.clear();

	std::string line;
	bool readingBooks = true;

	while (std::getline(file, line)) 
	{
		if (line.empty()) continue;
		if (line == "---USERS---") {
			readingBooks = false;
			continue;
		}
		if (readingBooks && line == "BOOK") 
		{
			std::string bookData[6];
			for (int i = 0; i < 6; i++) 
			{
				std::getline(file, bookData[i]);
			}
			std::string title = bookData[0].substr(7);
			std::string author = bookData[1].substr(8);
			int year = std::stoi(bookData[2].substr(6)); 
			std::string isbn = bookData[3].substr(6);

			try 
			{
				Book book(title, author, year, isbn);
				books.push_back(book);
			}
			catch (...) 
			{
			}
		}
		else if (!readingBooks && line == "USER") 
		{
			std::string userData[4];
			for (int i = 0; i < 4; i++)
			{
				std::getline(file, userData[i]);
			}
			std::string name = userData[0].substr(6);
			std::string userId = userData[1].substr(8);
			try 
			{
				User user(name, userId);
				users.push_back(user);
			}
			catch (...) 
			{
			}
		}
	}

	file.close();
	std::cout << "Загружено книг: " << books.size()
		<< ", пользователей: " << users.size() << std::endl;
}
