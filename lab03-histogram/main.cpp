#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>

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

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    // TODO: дописывать данные к буферу.
    size_t data_size = item_size*item_count;
    stringstream *buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write((const char*) items, data_size);
    return data_size;
}

Input
download(const string& address)
{
    stringstream buffer;

    CURL* curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address);
        /* ask libcurl to show us the verbose output */
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res != CURLE_OK)
        {
            cerr << curl_easy_strerror(res);
            exit(1);
        }

    }

    return read_input(buffer, false);
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

int
main(int argc, char* argv[])
{
    Input input;
    if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
}
