#include <iostream>
#include <cassert>

#include "ScoreList.h"

int main()
{
    return 0;
}

// int main()
// {
//     ScoreList x;
//     x.dump();

//     x.add(1);
//     x.add(10);
//     assert(!x.add(200));
//     x.add(1);
//     x.dump();

//     assert(x.maximum() == 10);
//     assert(x.minimum() == 1);

//     std::cerr << '\n';
//     ScoreList y(x);
//     y.dump();

//     ScoreList z(x);
//     z.add(2);
//     z.dump();

//     std::cerr << '\n';
//     z = y = x;
//     z.dump();
//     y.dump();
//     x.dump();

//     std::cerr << '\n';


//     assert(!x.remove(2));
//     assert(x.remove(1));
//     assert(x.size() == 2);
//     x.dump();

//     assert(x.remove(1));
//     x.dump();

//     std::cerr << "All tests passed\n";

//     return 0;
// }
