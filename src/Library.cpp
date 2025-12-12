#include <Library.h>

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
	std::ofstream file(dataFile);
	if (!file.is_open())
	{
		std::cout << "Ошибка загрузки файла" << std::endl;
		return;
	}
	for (int i=0; i<books.size();i++)
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
		for (size_t j = 0; j < borrowed.size(); j++) {
			file << borrowed[j];
			if (j != borrowed.size() - 1) file << "|";
		}
		file << "\n";
		file << "MaxBooks: " << user.getMaxBooksAllowed() << "\n\n";
	}
	std::cout << "Данные сохранены" << std::endl;	
}
void Library::loadFromFile()
{
	std::ifstream file(dataFile);
	if (!file.is_open()) {
		std::cout << "Файл не найден." << std::endl;
		return;
	}
	std::cout << "Данные загружаются из файла..." << std::endl;
	books.clear();
	users.clear();
}