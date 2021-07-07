#include "svg.h"

string
make_info_text() {
    stringstream buffer;

    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD platform = info >> 16;
    DWORD mask_2 = 0xff;

   if ((info & 0x80000000) == 0)
    {
        DWORD version_major = version & mask_2;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        buffer << "Windows v"<<version_major<<"."<<version_minor<<"(build"<<build<<") ";

    }
    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH+1;
    GetComputerNameA(computer_name, &size);
    buffer<<"Computer name:" <<computer_name;
    return buffer.str();
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
svg_text(double left, double baseline, string text, string textDecoration)
{
    cout << "<text x='" << left << "' y='" << baseline <<  "' text-decoration='"<< textDecoration << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='"<< fill << "'/>";
}

void
show_histogram_svg(const vector<size_t>& bins)
{
     size_t max_count = bins[0];

    for (size_t i = 0; i < bins.size(); i++)
    {
        if (bins[i] > max_count)
        {
            max_count = bins[i];
        }
    }
    const auto TEXT_TOP = 10;
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
        //const double bin_width = BLOCK_WIDTH * bin;
        const double bin_width = IMAGE_WIDTH * bin / max_count;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "white", "red");
        top += BIN_HEIGHT;
    }
    svg_text(0, IMAGE_HEIGHT - 20, make_info_text());
    svg_end();
}
