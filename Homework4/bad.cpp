void removeBad(list<Movie*>& li)
  // Remove the movies in li with a rating below 50 and destroy them.
  // It is acceptable if the order of the remaining movies is not
  // the same as in the original list.
{
	std::list<Movie*>::iterator i = li.begin();
	while(i != li.end())
	{
		Movie* p = *i;
		if(p->rating() < 50)
		{
			//deleting movies, and putting result in destroyed ones
			delete *i;

			//actaully erasing node
			i = li.erase(i);
		}
		else
		{
			i++;
		}
	}
}