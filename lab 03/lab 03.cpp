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

void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black" )
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='"<< fill << "'/>";
}

void
show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "yellow");
        top += BIN_HEIGHT;
    }
    svg_end();
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
    //show_histogram_text(bins);
    show_histogram_svg(bins);
}
