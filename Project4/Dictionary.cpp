#include <string>
#include <iostream>
#include <math.h>
#include <functional>
#include "Dictionary.h"

const int MAX_BUCKETS = 49957; //size of dictionary

void removeNonLetters(std::string& s);
void alphabetize(std::string &word, int left, int right);
	//uses quicksort to alphabetize the string

class DictionaryImpl
//implemented as a hash table
{
  public:
  	~DictionaryImpl();
	void insert(std::string word);
		//inserts word into dictionary
	void lookup(std::string letters, void callback(std::string)) const;
  private:
  	struct Bucket
  		//each bucket points to previous and next, and holds a value
  	{
  		Bucket* next = nullptr;
  		Bucket* prev = nullptr;

  		std::string value;
  		std::string key; //key is just the aphabetized letters
  	};

  	int hashFunc(std::string word, int size = MAX_BUCKETS) const;
  		//finds unique number for each anagram based on size of dictionary
  	Bucket* m_buckets[MAX_BUCKETS][2] = {nullptr};
  		//array of "head" and "tail" pointers to buckets 
  		//[][0] is the head
  		//[][1] is the tail: helps with performance when inserting
};

DictionaryImpl::~DictionaryImpl()
{
	int counter = 0;

	for(int i = 0; i < MAX_BUCKETS; i++)
		//checking each head for stuff, and deleting any linked lists
	{
		if(m_buckets[i][0] != nullptr)
		{
			//head = m_buckets[i][0];
			//tail = m_buckets[i][1];
			for(Bucket* walk = m_buckets[i][0]; walk->next != nullptr; walk = walk->next)
				//delete linked list by deleting previous buckets
			{
				if(walk->prev != nullptr)
				{
					delete walk->prev;
				}
			}

			delete m_buckets[i][1];
			counter++;
		}
	}
}

void DictionaryImpl::insert(std::string word)
{
	removeNonLetters(word);
	if (word.empty()) return;

	std::string alphad = word;
	alphabetize(alphad, 0, word.size() - 1);

	int place = hashFunc(alphad);

	if(m_buckets[place][0] == nullptr)
	{
		m_buckets[place][0] = new Bucket;
		m_buckets[place][1] = m_buckets[place][0];
	}
	else
		//if something is already in there
	{
		//create new bucket at tail
		m_buckets[place][1]->next = new Bucket;
		m_buckets[place][1]->next->prev = m_buckets[place][1]; 
		m_buckets[place][1] = m_buckets[place][1]->next;
	}

	m_buckets[place][1]->value = word;
	m_buckets[place][1]->key = alphad;
}

void DictionaryImpl::lookup(std::string letters, void callback(std::string)) const
{
	removeNonLetters(letters);
	if (letters.empty() || callback == nullptr) return;


	std::string alphad = letters;
	alphabetize(alphad, 0, alphad.size() - 1);

	int place = hashFunc(alphad);

	if(m_buckets[place][1] != nullptr)
	{
		for(Bucket* walk = m_buckets[place][0]; walk->next != nullptr; walk = walk->next)
		{
			if(walk->key == alphad)
				//of course there may be collision
				//so we just check each node's alphabetized "key"
				//which is guarenteed to be the same for all anagrams
			{
				callback(walk->value);
			}
		}

		if(m_buckets[place][1]->key == alphad)
			//checking last item in linked list
			//because i'm not that good at making for loops
		{
			callback(m_buckets[place][1]->value);
		}
	}
}

int DictionaryImpl::hashFunc(std::string word, int size) const
{
	std::hash<std::string> str_hash;
	unsigned int hash = str_hash(word);
	unsigned int bucket = hash % size;

	return bucket;
}

void alphabetize(std::string &word, int left, int right)
{
	int i = left;
	int j = right;
	int pivot = word[(left + right) / 2];
	int temp;

	while(i <= j)
	{
		while(word[i] < pivot) i++;
		while(word[j] > pivot) j--;
		if(i <= j)
		{
			temp = word[i];
			word[i] = word[j];
			word[j] = temp;
			i++;
			j--;
		}
	}

	if (left < j)
	{
        alphabetize(word, left, j);
	}
	if (i < right)
	{
	    alphabetize(word, i, right);
	}
}

void removeNonLetters(std::string& s)
{
    std::string::iterator to = s.begin();
    for (std::string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
} 

//dictionary thing
Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}
void Dictionary::insert(std::string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(std::string letters, void callback(std::string)) const
{
    m_impl->lookup(letters,callback);
}
