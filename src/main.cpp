#include "Library.h"
#include <iostream>
#include <locale>
#include <limits>

int main() 
{
    setlocale(LC_ALL, "RU");
    Library library("data/library_data.txt");
    int choice = 0;
    while (choice != 10) 
    {
        std::cout << "\n=== БИБЛИОТЕКА ===\n";
        std::cout << "1. Просмотреть все книги\n";
        std::cout << "2. Просмотреть всех пользователей\n";
        std::cout << "3. Добавить новую книгу\n";
        std::cout << "4. Зарегистрировать пользователя\n";
        std::cout << "5. Выдать книгу пользователю\n";
        std::cout << "6. Принять книгу от пользователя\n";
        std::cout << "7. Поиск книги по ISBN\n";
        std::cout << "8. Просмотреть профиль пользователя\n";
        std::cout << "9. Сохранить данные в файл\n";
        std::cout << "10. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) 
        {
        case 1:
            library.displayAllBooks();
            break;
        case 2:
            library.displayAllUsers();
            break;
        case 3: 
        {
            std::string title, author, isbn;
            int year;
            std::cout << "Название книги: ";
            std::getline(std::cin, title);
            std::cout << "Автор: ";
            std::getline(std::cin, author);
            std::cout << "Год издания: ";
            std::cin >> year;
            std::cin.ignore();
            std::cout << "ISBN: ";
            std::getline(std::cin, isbn);
            try 
            {
                Book newBook(title, author, year, isbn);
                library.addBook(newBook);
                std::cout << "Книга добавлена!\n";
            }
            catch (const char* error) 
            {
                std::cout << "Ошибка: " << error << std::endl;
            }
            break;
        }

        case 4: 
        {
            std::string name;
            std::cout << "Имя пользователя: ";
            std::getline(std::cin, name);
            static int userCounter = 1;
            std::string userId = "USR_" + std::to_string(userCounter++);
            User newUser(name, userId);
            library.addUser(newUser);
            std::cout << "Пользователь " << name << " зарегистрирован (ID: " << userId << ")\n";
            break;
        }

        case 5: 
        {
            std::string userName, isbn;
            std::cout << "Имя пользователя: ";
            std::getline(std::cin, userName);

            std::cout << "ISBN книги: ";
            std::getline(std::cin, isbn);

            library.borrowBook(userName, isbn);
            break;
        }

        case 6: 
        {
            std::string isbn;
            std::cout << "ISBN книги для возврата: ";
            std::getline(std::cin, isbn);
            library.returnBook(isbn);
            break;
        }

        case 7: 
        {
            std::string isbn;
            std::cout << "Введите ISBN: ";
            std::getline(std::cin, isbn);
            Book* book = library.findBookByISBN(isbn);
            if (book) 
            {
                book->displayInfo();
            }
            else 
            {
                std::cout << "Книга не найдена\n";
            }
            break;
        }

        case 8: 
        {
            std::string name;
            std::cout << "Имя пользователя: ";
            std::getline(std::cin, name);
            User* user = library.findUserByName(name);
            if (user) 
            {
                user->displayProfile();
            }
            else 
            {
                std::cout << "Пользователь не найден\n";
            }
            break;
        }
        case 9:
            library.saveToFile();
            break;
        case 10:
            std::cout << "Сохранение данных..." << std::endl;
            library.saveToFile();
            std::cout << "Выход из программы." << std::endl;
            break;
        default:
            std::cout << "Неверный ввод\n";
        }
    }

    return 0;
}