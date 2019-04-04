#include <iostream>
#include <cassert>

#include "newSequence.h"

int main()
{
    return 0;
}

// int main()
// {
//    Sequence a(1000);   // a can hold at most 1000 items
//    Sequence b(5);      // b can hold at most 5 items
//    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items

//    Sequence d(1000);   // a can hold at most 1000 items
//    Sequence e(5);      // b can hold at most 5 items
//    Sequence f; 

//    e.insert(0, 1);
//    e.insert(0, 2);
//    e.insert(0, 3);
//    e.insert(0, 4);
//    e.insert(0, 5);
//    assert(!e.insert(0, 6));
//    e.dump();

//    std::cerr << '\n';
//    e.dump();
//    d.dump();

//    e.swap(d);
//    assert(e.size() == 0);
//    assert(d.size() == 5);

//    std::cerr << '\n';
//    e.dump();
//    d.dump();

//    Sequence g(d);
//    g.dump();

//    ItemType v = 1;

//       // No failures inserting 5 items into b
//    for (int k = 0; k < 5; k++)
//      assert(b.insert(v) != -1);

//       // Failure if we try to insert a sixth item into b

//    assert(b.insert(v) == -1);

//       // When two Sequences' contents are swapped, their capacities are
//       // swapped as well:
//    a.swap(b);
//    assert(a.insert(v) == -1  &&  b.insert(v) != -1);

//    std::cerr << "All tests passed\n";

//    Sequence z(-1);
//    return 0;
// }

