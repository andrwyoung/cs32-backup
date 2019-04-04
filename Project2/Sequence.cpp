#include <iostream> //for dump
#include "Sequence.h"

Sequence::Sequence()
	:m_size(0), m_head(nullptr), m_tail(nullptr)
{
}

Sequence::Sequence(const Sequence& other)
{
	m_size = 0;
	m_head = nullptr;
	m_tail = nullptr;

	//copying other node
    Sequence::Node* walker = other.m_head;
	for(int i = 0; walker != nullptr; walker = walker->next, i++) //walk through current list
	{
		insert(i, walker->value);
	}
}

Sequence& Sequence::operator=(const Sequence& other)
{
    if(this != &other)
    {
        Sequence temp(other);
        swap(temp);
    }

    return *this;
}

Sequence::~Sequence()
{
    if(m_head != nullptr) //sequence empty?
    {
        for(Sequence::Node* walker = m_head->next; walker != nullptr; walker = walker->next)
        {
            delete walker->prev;
        }
        
        delete m_tail;
    }
}

bool Sequence::empty() const
{
	return !m_size;
}

int Sequence::size() const
{
	return m_size;
}

bool Sequence::insert(int pos, const ItemType& value)
{
	if(pos < 0 || pos > m_size)
	{
		return false;
	}
	
	//create a new node.
	// 4 cases: middle, beginning, end and empty

	//empty
	if(m_head == nullptr && m_tail == nullptr) //don't have to check both
	{
		m_head = new Sequence::Node; //create new node using m_head
		m_tail = m_head; //point m_tail to new node
		m_head->next = nullptr; //set node's next to nullptr
		m_head->prev = nullptr; //set node's prev to nullptr

		m_head->value = value; //set value
	}

	//beginning
	else if(pos == 0)
	{
		m_head->prev = new Sequence::Node; //use current m_head's prev (currently nullptr) to create new node
		m_head->prev->next = m_head; //point new node back to current m_head node
		m_head = m_head->prev; //set m_head to new node
		m_head->prev = nullptr; //set new node's prev to nullptr

		m_head->value = value; //set value

	}

	//end
	else if(pos == m_size)
	{
		m_tail->next = new Sequence::Node; //use current m_tail's next (currently nullptr) to create new node
		m_tail->next->prev = m_tail; //point new node back to current m_tail node
		m_tail = m_tail->next; //set m_tail to new node
		m_tail->next = nullptr; //set new node's next to nullptr

		m_tail->value = value; //set value
	}

    //middle. assumptions: not empty, not m_size, not 0
	else
	{
        Sequence::Node* temp = m_head;
        for(int i = 0; i < pos - 1; temp = temp->next, i++) //walk to position right before pos
        {
            //just in case
            if(temp->next == nullptr || temp == nullptr)
            {
                exit(1);
            }
        }
        temp->next->prev = new Sequence::Node;
        temp->next->prev->next = temp->next;
        temp->next->prev->prev = temp;
        temp->next = temp->next->prev;
        
        temp->next->value = value;
	}

	m_size++;
	return true;
}

int Sequence::insert(const ItemType& value)
{
    //walk through loop
    Sequence::Node* walker = m_head;
    for(int i = 0; walker != nullptr; walker = walker->next, i++)
    {
    	if(value <= walker->value)
    	{
    		if(insert(i, value))
    		{
    			return i;
    		}
    		else
    		{
    			return -1;
    		}
    	}
    }

    if(insert(m_size, value))
    {
    	return m_size;
    }
    else
    {
    	return -1;
    }
}

bool Sequence::erase(int pos)
{
	if(pos < 0 || pos >= m_size)
	{
		return false;
	}

	//empty
	if(m_head == nullptr && m_tail == nullptr)
	{
        return false;
	}

	//beginning
	else if(pos == 0)
	{
		//one item
		if(m_head->next == nullptr)
		{
			delete m_head;
			m_head = nullptr;
			m_tail = nullptr;
		}
		else
		{
			m_head = m_head->next; //move m_head to next item
			delete m_head->prev; //delete previous head
			m_head->prev = nullptr; //set new head's prev to null
		}
	}

	//end
	else if(pos == m_size - 1)
	{
		m_tail = m_tail->prev; //move m_tail to previous item
		delete m_tail->next; //delete previous tail
		m_tail->next = nullptr; //set new tail's next to null
	}

    //middle. assumptions: not empty, not m_size, not 0
	else
	{
		Sequence::Node* temp = m_head;
        for(int i = 0; i < pos; temp = temp->next, i++) //walks onto position
        {
            //just in case
            if(temp->next == nullptr || temp == nullptr)
            {
                exit(1);
            }
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
	}


	m_size--;
	return true;
}

int Sequence::remove(const ItemType& value)
{
	int counter = 0; //how many values removed

    Sequence::Node* walker = m_head;
	int i = 0; //current position
	while(walker != nullptr) //walk through the list
	{
		if(walker->value == value)
		{
			erase(i);
			counter++;
			i = 0;
			walker = m_head;
		}
		else
		{
			i++;
            walker = walker->next;
		}
	}

	return counter;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if(pos < 0 || pos >= m_size)
	{
		return false;
	}

	Sequence::Node* temp = m_head;
	for(int i = 0; i < pos; temp = temp->next, i++) //walks onto position
    {
        //just in case
        if(temp->next == nullptr || temp == nullptr)
        {
            exit(1);
        }
    }

    value = temp->value;
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
	if(pos < 0 || pos >= m_size)
	{
		return false;
	}
	
	Sequence::Node* temp = m_head;
	for(int i = 0; i < pos; temp = temp->next, i++) //walks onto position
    {
        //just in case
        if(temp->next == nullptr || temp == nullptr)
        {
            exit(1);
        }
    }

    temp->value = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
	Sequence::Node* walker = m_head;
    for(int i = 0; walker != nullptr; walker = walker->next, i++)
    {
    	if(walker->value == value)
    	{
    		return i;
    	}
    }

    return -1;
}

void Sequence::swap(Sequence& other)
{
	int temp = m_size;
	m_size = other.m_size;
	other.m_size = temp;

	Sequence::Node* temp1 = m_head;
	m_head = other.m_head;
	other.m_head = temp1;

	Sequence::Node* temp2 = m_tail;
	m_tail = other.m_tail;
    other.m_tail = temp2;
}

void Sequence::dump() const
{
    std::cerr << '\n';
    
	for(Sequence::Node* walker = m_head; walker != nullptr; walker = walker->next)
	{
		std::cerr << walker->value << ", ";
	}

    std::cerr << "= " << m_size << '\n';
    if(m_head != nullptr)
    {
        std::cerr << "\tm_head = " << m_head->value << '\t';
        
    }
    if(m_tail != nullptr)
    {
        std::cerr << "\tm_tail = " << m_tail->value << "\n\n";
    }
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	int pos = -1;
	ItemType placeholder1;
	ItemType placeholder2;

	for(int i = 0; i < seq1.size(); i++)
	{
		if(!seq1.get(i, placeholder1) || !seq2.get(0, placeholder2))
		{
			exit(1); //just in case get doesn't work
		}

		if(placeholder1 == placeholder2)
		{
			pos = i;

			for(int j = 0; j < seq2.size(); j++)
			{
				if(!seq1.get(i + j, placeholder1) || !seq2.get(j, placeholder2))
				{
					exit(1); //just in case get doesn't work
				}

				if(placeholder1 != placeholder2)
				{
					pos = -1;
				}
			}

			if(pos != -1)
			{
				return pos;
			}
		}
	}

	return pos;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	Sequence temp;
	ItemType placeholder;

	for(int i = 0; i < seq2.size() || i < seq1.size(); i++)
	{
		if(i < seq1.size())
		{
			seq1.get(i, placeholder);
			temp.insert(temp.size(), placeholder);
		}

		if(i < seq2.size())
		{
			seq2.get(i, placeholder);
            temp.insert(temp.size(), placeholder);
		}
	}

	result = temp;
}
