#include <iostream>
#include <cassert>

#include "Sequence.h"
using namespace std;

int main()
{
    return 0;
}

// int main()
// {
//    ItemType value;

//    Sequence x;
//    //()
//    assert(x.empty());
//    assert(!x.size());

//    //(water)
//    assert(!x.insert(1, 1));
//    assert(x.insert(0, 1));
//    assert(x.size());
//    x.dump();

//    //(water, butter)
//    assert(x.insert(1, 2));
//    assert(!x.empty());
//    assert(x.size() == 2);
//    x.dump();

//    //(water, melon, butter)
//    assert(x.insert(1, 3));
//    assert(!x.empty());
//    assert(x.size() == 3);
//    assert(x.get(1, value));
//    assert(value == 3);
//    x.dump();

//    //(water, melon, juice)
//    assert(x.set(2, 4));
//    assert(x.get(2, value));
//    assert(value == 4);
//    assert(x.size() == 3);
//    x.dump();

//    //(melon, juice)
//    assert(x.erase(0));
//    assert(x.size() == 2);
//    x.dump();

//    //(melon, juice, melon)
//    assert(x.insert(2, 3));
//    assert(x.size() == 3);
//    x.dump();

//    //(juice)
//    assert(x.remove(3) == 2);
//    assert(x.size() == 1);
//    x.dump();

//    //(juice, melon, melon)
//    assert(x.insert(1, 3));
//    assert(x.insert(2, 3));
//    x.dump();

//    Sequence y;
//    y.insert(0, 5);
//    x.swap(y);
//    std::cerr << '\n';
//    x.dump();
//    y.dump();

//    Sequence z(y);
//    z.dump();

//    z = x;
//    z.dump();

//    std::cout << "All tests passed\n";

//    return 0;
// }
