#include <vector>
#include "histogram.h"

const vector<size_t>
make_histogram(Input input)
{
    double min;
    double max;
    vector<size_t> bins(input.bin_count);

    find_minmax(input.numbers, min, max);

    double bin_size = (max - min) / bins.size();
    for (size_t i = 0; i < input.numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; (j < bins.size() - 1) && !found; j++)
        {
            auto low = min + j * bin_size;
            auto high = min + (j + 1) * bin_size;
            if ((input.numbers[i] >= low) && (input.numbers[i] < high))
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
find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if (numbers.size() == 0) return;
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
