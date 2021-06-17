#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cerr << "Enter " << i + 1 << " number:\t";
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in, bool prompt)
{
    Input data;
    size_t number_count;
    if (prompt == true)
    {
        cerr << "Enter number count: ";
    }
    in >> number_count;
    if (prompt == true)
    {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);
    if (prompt == true)
    {
        cerr << "Enter quantity of bins: ";
    }
    in >> data.bin_count;
    return data;
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
    curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin, true);
    const vector<size_t> bins = make_histogram(input);
    // show_histogram_text(bins);
    show_histogram_svg(bins);
}
