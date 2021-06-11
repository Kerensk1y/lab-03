// lab 03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>
input_numbers(size_t count) 
{
	vector<double> result(count);
	for (size_t i = 0; i < count; i++) 
	{
		cerr << "Введите " << i + 1 << " число:\t";
		cin >> result[i];
	}
	return result;
}

void
find_minmax(const vector<double>& numbers, double& min, double& max) 
{
	min = numbers[0];
	max = numbers[0];
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] < min)
		{
			min = numbers[i];
		}
		if (numbers[i] > max)
		{
			max = numbers[i];
		}
	}
}

const vector<size_t>
make_histogram(const vector<double>& numbers, size_t bin_count)
{
	double min;
	double max;
	vector<size_t> bins(bin_count);

	find_minmax(numbers, min, max);

	double bin_size = (max - min) / bins.size();
	for (size_t i = 0; i < numbers.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; (j < bins.size() - 1) && !found; j++)
		{
			auto low = min + j * bin_size;
			auto high = min + (j + 1) * bin_size;
			if ((numbers[i] >= low) && (numbers[i] < high))
			{
				bins[j]++;
				found = true;
			}
		}
		if (!found)
		{
			bins[bins.size() - 1]++;
		}
	}
	return bins;
}

void
show_histogram_text(const vector<size_t> bins)
{
	size_t max_count = bins[0];

	for (size_t i = 0; i < bins.size(); i++)
	{
		if (bins[i] > max_count)
		{
			max_count = bins[i];
		}
	}
	if (max_count > MAX_ASTERISK)
	{

		size_t height;
		for (size_t i = 0; i < bins.size(); i++)
		{
			height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
			if (bins[i] < 100)
				cout << " ";
			if (bins[i] < 10)
				cout << " ";
			cout << bins[i] << "|";
			for (size_t j = 0; j < height; j++)
			{
				cout << "*";
			}
			cout << endl;
		}
	}
	else
	{
		for (size_t i = 0; i < bins.size(); i++)
		{
			if (bins[i] < 100)
				cout << " ";
			if (bins[i] < 10)
				cout << " ";
			cout << bins[i] << "|";
			for (size_t j = 0; j < bins[i]; j++)
			{
				cout << "*";
			}
			cout << endl;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");

	size_t number_count;
	cerr << "Введите количество чилел:\t"; 
	cin >> number_count;

	const auto numbers = input_numbers(number_count);

	size_t bin_count;
	cerr << "Введите количество групп:\t"; 
	cin >> bin_count;

	
	const vector<size_t> bins = make_histogram(numbers, bin_count);
	show_histogram_text(bins);
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
