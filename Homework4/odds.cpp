void removeOdds(vector<int>& v)
  // Remove the odd integers from v.
  // It is acceptable if the order of the remaining even integers is not
  // the same as in the original vector.
{
	for(std::vector<int>::iterator i = v.begin(); i != v.end(); i++)
	{
		if(*i % 2 == 1)
		{
			v.erase(i);
			i--;
		}
	}
}