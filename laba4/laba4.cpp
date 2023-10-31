#include <iostream>
#include<fstream>
#include<Windows.h>
#include<functional> 

int check_file(std::ifstream& file);
void ending(int n);
template <typename T, typename Predicat>
void Read_and_check(T& x, Predicat condition, const char* message);
int main_menu();
int choice_menu();
int task1(int size, std::istream& stream);
int task1(int size, int a, int b);


int main()
{
	SetConsoleOutputCP(1251);
	short mainChoice;
	do
	{
		mainChoice = main_menu();
		if (mainChoice != 3)
		{
			short choice;
			do
			{

				choice = choice_menu();
				if (choice != 4)
				{
					if (choice == 1)
					{
						int size;
						std::cout << "\nВведите количество элементов: ";
						Read_and_check(size, [](int x) {return x > 0; }, "\n-> ");
						if (mainChoice == 1)
							std::cout << task1(size, std::cin);
						//std::cout << "Номер первого максимального элемента: " << task1(size, std::cin) << '\n';
						else
							std::cout << "in developing...";
						//std::cout << "Количество элементов, удовлетворяющих условию: " << task2(size, std::cin) << '\n';

					}
					if (choice == 2)
					{

						std::ifstream file("data.txt");
						switch (check_file(file))
						{
						case -1:
							std::cout << "\nФайл не найден!\n";
							break;
						case 0:
							std::cout << "\nФайл пустой!\n";
							break;
						default:
						{
							int size;
							file >> size;
							if (mainChoice == 1)
								std::cout << task1(size, file);
							else
								std::cout << "in developing...";
							//std::cout << "Номер первого максимального элемента: " << task1(size, std::cin) << '\n';

							//std::cout << "Количество элементов, удовлетворяющих условию: " << task2(size, std::cin) << '\n';
						}
						}



					}
					if (choice == 3)
					{
						int size;
						std::cout << "\nВведите количество случайных слагаемых: ";
						Read_and_check(size, [](int x) {return x > 0; }, "\n-> ");
						std::cout << "Введите диапазон рандома(от A до B): ";
						int a, b;
						Read_and_check(a, [](int x) {return true; }, "\n-> ");
						Read_and_check(b, [](int x) {return true; }, "\n-> ");
						if (mainChoice == 1)
							std::cout << task1(size, a, b);
						//std::cout << "Номер первого максимального элемента: " << task1(size, std::cin) << '\n';
						else
							std::cout << "in developing...";
						//std::cout << "Количество элементов, удовлетворяющих условию: " << task2(size, std::cin) << '\n';

					}
				}
			} while (choice != 4);
		}
	} while (mainChoice != 3);
}

int check_file(std::ifstream& file)
{
	int result = 1;
	if (!file)
		result = -1;
	else
		if (file.peek() == EOF) //==-1
			result = 0;

	return result;
}

void ending(int n)
{
	std::cout << "Введите " << n << " элемент";
	if (n < 21 && n>10)
		std::cout << "ов: ";
	else
	{
		switch (n % 10)
		{
		case 1:
			break;
		case 2:
		case 3:
		case 4:
			std::cout << "а: ";
			break;
		default:
			std::cout << "ов: ";
			break;

		}
	}
}
int main_menu()
{
	std::cout << "\nМеню";
	std::cout << "\n1. Найти номер первого максимального элемента последовательности\n";
	std::cout << "2. Найти количество положительных элементов после первого элемента, оканчивающегося на заданную цифру\n";
	std::cout << "3. Завершить работу" << '\n';

	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 3;
		};
	int choice = 0;
	Read_and_check(choice, Lambda, "\n->");
	return choice;
}
int choice_menu()
{
	std::cout << "\n1. Ввод чисел с клавиатуры" << '\n';
	std::cout << "2. Ввод чисел из файла" << '\n';
	std::cout << "3. Случайный набор чисел" << '\n';
	std::cout << "4. Закрыть решение задачи" << '\n';
	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 4;
		};
	int choice = 0;
	Read_and_check(choice, Lambda, "\n-> ");
	return choice;
}

int task1(int size, std::istream& stream)
{
	int x;
	int max;
	int numb = 1;

	if (&stream == &std::cin)
	{
		Read_and_check(max, [](int x) {return true; }, "\n-> ");
		for (int i = 2; i <= size; ++i)
		{
			Read_and_check(x, [](int x) {return true; },"");
			if (x > max)
			{
				max = x;
				numb = i;
			}
		}
	}
	else
	{
		stream >> max;
		for (int i = 2; i <= size; ++i)
		{
			stream >> x;
			if (x > max)
			{
				max = x;
				numb = i;
			}
		}
	}

	return numb;
}

int task1(int size, int a, int b)
{

	int x;
	int max = a + rand() % (b - a + 1);
	std::cout << "\nСлучайные элементы: ";
	std::cout << max << ' ';
	int numb = 1;
	for (int i = 2; i <= size; i++)
	{
		x = a + rand() % (b - a + 1);
		std::cout << x << ' ';
		if (x > max)
		{
			max = x;
			numb = i;
		}

	}
	std::cout << '\n';

	return numb;
}



template<typename T, typename Predicat>
void Read_and_check(T& x, Predicat condition, const char* message)
{
	std::cout << message;
	while (!(std::cin >> x && condition(x)))
	{
		std::cout << "Ошибка ввода!\n";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message;

	}
}
