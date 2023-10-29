
#include <iostream>
#include<fstream>
#include<Windows.h>

double sum(std::istream& stream = std::cin, int size = 0);
double sum(int size);
int check_file(std::ifstream& file);
void ending(int n);

int main()
{
	SetConsoleOutputCP(1251);
	short choice;
	do
	{
		std::cout << "\n1. Ввод чисел с клавиатуры" << '\n';
		std::cout << "2. Ввод чисел из файла" << '\n';
		std::cout << "3. Случайный набор чисел" << '\n';
		std::cout << "4. Завершить работу" << '\n';
		std::cout << "->";
		std::cin >> choice;
		if (choice != 4)
		{
			if (choice == 1)
			{
				int n;
				std::cout << "\nВведите количество элементов: ";
				std::cin >> n;
				std::cout << "Сумма элементов: " << sum(std::cin, n) << '\n';

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
					std::cout << "\nСумма элементов: " << sum(file) << '\n';
				}
				}



			}
			if (choice == 3)
			{
				int n;
				std::cout << "\nВведите количество случайных слагаемых: ";
				std::cin >> n;
				std::cout << "Сумма элементов: " << sum(n) << '\n';

			}
		}
	} while (choice != 4);
}


double sum(std::istream& stream, int size)
{
	double x;
	double sum = 0;
	if (&stream == &std::cin)
	{
		ending(size);
		for (int i = 0; i < size; i++)
		{
			stream >> x;
			sum += x;
		}
	}
	else
	{
		while (stream >> x)
		{
			sum += x;
		}
	}

	return sum;
}

double sum(int size)
{
	double x;
	double sum = 0;
	std::cout << "Введите диапазон рандома(от A до B): ";
	int a, b;
	std::cin >> a >> b;
	std::cout << "\nСлучайные элементы: ";
	for (int i = 0; i < size; i++)
	{
		x = a + rand() % (b - a + 1);
		std::cout << x << ' ';
		sum += x;
	}
	std::cout << '\n';

	return sum;
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
		case4:
			std::cout << "а: ";
			break;
		default:
			std::cout << "ов: ";
			break;

		}
	}
}