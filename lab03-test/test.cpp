#include "../lab03-histogram/histogram.h"
#include <iostream>
#include <cassert>

void
test_positive1()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
    cout << "test 1 completed" << endl;
}

void
test_positive2()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
     cout << "test 2 completed" << endl;
}

void
test_positive3()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
     cout << "test 3 completed" << endl;
}

void
test_positive4()
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
     cout << "test 4 completed" << endl;
}

void
test_positive5()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
     cout << "test 5 completed" << endl;
}

int
main()
{
    test_positive1();
    test_positive2();
    test_positive3();
    test_positive4();
    test_positive5();
}
