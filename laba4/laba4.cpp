#include <iostream>
#include<fstream>
#include<Windows.h>
#include<functional> 

//Вспомогательные функции
int check_file(std::ifstream& file);
void ending(int n);
template <typename T, typename Predicat>
void Read_and_check(T& x, Predicat condition, const char* message);
int GetRandomInInterval(int a, int b);

//Менюшки
int main_menu();
int choice_menu();

//Первая задача
int task1(int size, std::istream& stream);
int task1(int size, int a, int b);

//Вторая задача
int task2(int size, int& count, int endNumb, std::istream& stream, std::function<bool(int)> predicate);
void print_answer(int ind, int res);
int task2(int size, int& count, int endNumb, int a, int b, std::function<bool(int)> predicate);

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
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						if (mainChoice == 1)
							std::cout << "\nНомер первого максимального элемента: " << task1(size, std::cin) << '\n';
						else
						{
							int endNumb;
							int count = 0;
							std::cout << "\nВведите цифру окончания числа: ";
							Read_and_check(endNumb, [](int x) {return x > 0 && x < 10; }, "\n-> ");
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							int res = task2(size, count, endNumb, std::cin, [endNumb](int x) {return abs(x) % 10 == endNumb; });
							print_answer(res, count);
						}
					}
					if (choice == 2)
					{
						std::ifstream file("task_universal.txt");
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
								std::cout << "\nНомер первого максимального элемента: " << task1(size, file) << '\n';
							else
							{
								int endNumb;
								int count = 0;
								std::cout << "\nВведите цифру окончания числа: ";
								Read_and_check(endNumb, [](int x) {return x > 0 && x < 10; }, "\n-> ");

								int res = task2(size, count, endNumb, file, [endNumb](int x) {return abs(x) % 10 == endNumb; });
								print_answer(res, count);
							}
						}
						}



					}
					if (choice == 3)
					{
						int size;
						std::cout << "\nВведите количество случайных слагаемых: ";
						Read_and_check(size, [](int x) {return x > 0; }, "\n-> ");
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						int a, b;
						std::cout << "\nВведите диапазон рандома(от A до B): ";
						Read_and_check(a, [](int x) {return true; }, "\n-> ");
						Read_and_check(b, [](int x) {return true; }, "");

						if (mainChoice == 1)
							std::cout << "\nНомер первого максимального элемента: " << task1(size, a, b) << '\n';
						else
						{
							int endNumb;
							int count = 0;

							std::cout << "\nВведите цифру окончания числа: ";
							Read_and_check(endNumb, [](int x) {return x > 0 && x < 10; }, "\n-> ");
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							int res = task2(size, count, endNumb, a, b, [endNumb](int x) {return abs(x) % 10 == endNumb; });
							print_answer(res, count);
						}
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
	std::cout << "\nВведите " << n << " элемент";
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

int GetRandomInInterval(int a, int b)
{
	return a + rand() % (b - a + 1);
}

int main_menu()
{
	std::cout << "\n--------------\n";
	std::cout << "\nМеню";
	std::cout << "\n1. Найти номер первого максимального элемента последовательности\n";
	std::cout << "2. Найти количество положительных элементов после первого элемента, оканчивающегося на заданную цифру\n";
	std::cout << "3. Завершить работу" << '\n';
	std::cout << "\n--------------\n";

	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 3;
		};
	int choice = 0;
	Read_and_check(choice, Lambda, "\n-> ");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

int choice_menu()
{
	std::cout << "\n--------------\n";
	std::cout << "\n1. Ввод чисел с клавиатуры" << '\n';
	std::cout << "2. Ввод чисел из файла" << '\n';
	std::cout << "3. Случайный набор чисел" << '\n';
	std::cout << "4. Выйти в главное меню" << '\n';
	std::cout << "\n--------------\n";

	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 4;
		};
	int choice = 0;
	Read_and_check(choice, Lambda, "\n-> ");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

int task1(int size, std::istream& stream)
{
	int x;
	int max;
	int numb = 1;

	if (&stream == &std::cin)
	{
		ending(size);
		Read_and_check(max, [](int x) {return true; }, "\n");
		for (int i = 2; i <= size; ++i)
		{
			Read_and_check(x, [](int x) {return true; }, "");
			if (x > max)
			{
				max = x;
				numb = i;
			}
		}
		std::cin.ignore(std::cin.rdbuf()->in_avail());
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
	int max = GetRandomInInterval(a, b);
	std::cout << "\nСлучайные элементы: ";
	std::cout << max << ' ';
	int numb = 1;
	for (int i = 2; i <= size; i++)
	{
		x = GetRandomInInterval(a, b);
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

int task2(int size, int& count, int endNumb, std::istream& stream, std::function<bool(int)> predicate)
{

	int x;
	int flag = 0;
	int result = 2;
	if (&stream == &std::cin)
	{
		ending(size);

		for (int i = 1; i <= size; ++i)
		{
			Read_and_check(x, [](int x) {return true; }, "");
			if (!flag)
			{
				if (predicate(x))
					flag = i;
			}
			else
				if (x > 0)
					count++;
		}
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	else
	{
		for (int i = 1; i <= size; ++i)
		{
			stream >> x;
			if (!flag)
			{

				if (predicate(x))
					flag = i;
			}
			else
				if (x > 0)
					count++;
		}
	}
	if (!flag || count == 0)
		result = -1;
	else
		if (flag == size)
			result = 0;

	return result;
}

int task2(int size, int& count, int endNumb, int a, int b, std::function<bool(int)> predicate)
{

	int x;
	int flag = 0;
	int result = 2;

	std::cout << "\nСлучайные элементы: ";

	for (int i = 1; i <= size; ++i)
	{
		x = GetRandomInInterval(a, b);
		std::cout << x << ' ';
		if (!flag)
		{

			if (predicate(x))
				flag = i;
		}
		else
			if (x > 0)
				count++;
	}
	std::cout << '\n';
	if (!flag || count == 0)
		result = -1;
	else
		if (flag == size)
			result = 0;

	return result;
}

void print_answer(int ind, int res)
{
	switch (ind)
	{
	case -1: std::cout << "Нет элементов с заданным свойством\n";
		break;
	case 0: std::cout << "Пустой диапазон\n";
		break;
	default: std::cout << "\nРезультат равен: " << res << '\n';
	}
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