// #include <iostream>
// #include <string>
// #include <cassert>

// bool somePredicate(std::string s)
// {
// 	if(s.size() <= 2)
// 	{
// 		return true;
// 	}

// 	return false;
// }

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const std::string a[], int n)
{
	if(n <= 0)
	{
		return true;
	}

	if(!somePredicate(a[n - 1]))
	{
		return false;
	}

	return allTrue(a, n - 1);
}

  // Return the number of elements in the array for which the
  // somePredicate function returns false.
int countFalse(const std::string a[], int n)
{
	if(n <= 0)
	{
		return 0;
	}

	if(!somePredicate(a[n - 1]))
	{
		return 1 + countFalse(a, n - 1);
	}
	else
	{
		return countFalse(a, n - 1);
	}
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const std::string a[], int n)
{
    if(n <= 0)
    {
    	return -1;
    }

    if(!somePredicate(a[0]))
    {
    	return 0;
    }
    else
    {
    	if(firstFalse(a + 1, n - 1) == -1)
    	{
    		return -1;
    	}

    	return 1 + firstFalse(a + 1, n - 1);
    }
}


// Return the subscript of the least std::string in the array (i.e.,
// the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int indexOfLeast(const std::string a[], int n)
{
	if (n <= 0) 
	{
        return -1;
	}

	int value = 1 + indexOfLeast(a + 1, n - 1);
    if (a[0] <= a[value])
    {
    	return 0;
    }
    else
    {
        return value;
    }

}

  // If all n2 elements of a2 appear in the n1 element array a1, in
  // the same order (though not necessarily consecutively), then
  // return true; otherwise (i.e., if the array a1 does not include
  // a2 as a not-necessarily-contiguous subsequence), return false.
  // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
  // For example, if a1 is the 7 element array
  //    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
  // then the function should return true if a2 is
  //    "kyle" "kenny" "butters"
  // or
  //    "kyle" "cartman" "cartman"
  // and it should return false if a2 is
  //    "kyle" "butters" "kenny"
  // or
  //    "stan" "kenny" "kenny"
bool includes(const std::string a1[], int n1, const std::string a2[], int n2)
{
    if(n2 <= 0)
    	//means that all things in n2 were found
    {
    	return true;
    }
    if(n1 <= 0)
    {
    	return false;
    }

    if(a1[0] == a2[0])
    {	
    	return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    else 
    {
    	return includes(a1 + 1, n1 - 1, a2, n2);
    }
}



// int main()
// {
// 	std::string a[] = {"a", "b", "c"};
// 	std::string b[] = {"a", "bcd", "c", "d", "effgg"};
// 	std::string c[] = {"a", "e", "deeeee", "eed", "g"};
// 	std::string e[] = {""};

// 	std::string n1[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};

// 	std::string n21[] = {"kyle", "kenny", "butters"};
// 	std::string n22[] = {"kyle", "cartman", "cartman"};
// 	std::string n23[] = {"stan", "kenny", "stan"};
// 	std::string n24[] = {"kyle", "kyle", "kyle"};

// 	std::string n33[] = {"kyle", "kyle", "kyle"};


// 	assert(allTrue(a, 3));
// 	assert(!allTrue(b, 3));
// 	assert(countFalse(b, 3) == 1);
// 	assert(firstFalse(c, 5) == 2);
// 	assert(firstFalse(a, 3) == -1);
// 	assert(includes(n1, 7, n21, 3));
// 	assert(includes(n1, 7, n22, 3));
// 	assert(!includes(n1, 7, n23, 3));
// 	assert(!includes(n1, 7, n24, 3));
// 	assert(includes(n24, 3, n33, 3));
// 	assert(indexOfLeast(a, 3) == 0);
// 	assert(indexOfLeast(n1, 3) == 2);
// 	assert(indexOfLeast(e, 0) == -1);

// 	return 0;
// }