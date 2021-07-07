#pragma once
#include <vector>
using namespace std;

struct Input
{
    vector<double> numbers;
    size_t bin_count;
};
const vector <size_t> make_histogram (Input input);
void find_minmax(const vector<double>& numbers, double& min, double& max);
