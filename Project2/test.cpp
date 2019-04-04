#include "Sequence.h"
// 

int main()
{
    return 0;
}

// int main()
// {
//     //constructor works
//     //destructor works: for 1 item, empty string
//             //check for multiple items
    
    
//     //insert works: for empty, beginning, end
//             //check for middle
    
//     //dump: kind of
	
//     Sequence h;
//     assert(h.empty());
//     assert(h.insert(0, 10));
//     assert(!h.empty());
//     assert(h.insert(1, 15));
//     assert(h.insert(1, 20));
//     assert(h.insert(1, 30));
//     assert(h.size() == 4);
//     assert(!h.empty());

//     ItemType value;
//     assert(h.get(0, value));
//     assert(value == 10);
//     assert(h.get(1, value));
//     assert(value == 30);

//     assert(h.insert(25));
//     assert(h.insert(100));

//     assert(h.set(0, 100));
//     assert(h.set(2, 100));
    
//     assert(h.remove(100) == 3);
    
//     h.dump();
    
//     Sequence i(h);

//     i.dump();
//     assert(i.insert(0, 20));
//     assert(i.insert(0, 100));

//     i.dump();

//     std::cerr << subsequence(i, h) << '\n';
    
//     Sequence j;
//     interleave(i, h, j);
//     j.dump();

//     // Sequence i;
//     // assert(i.insert(0, 1));

//     // i.swap(h);
    
//     // i.dump();

//     h.dump();
    
//     std::cerr << "All tests passed\n";
    
//     return 0;
// }
