#include <iostream> //for dump()
#include "newSequence.h"


Sequence::Sequence()
{
    m_size = 0;
    m_len = DEFAULT_MAX_ITEMS;
    m_array = new ItemType[m_len];
}

Sequence::Sequence(const int length)
{
    if(length < 0)
    {
        exit(1);
    }

    m_size = 0;
    m_len = length;
    m_array = new ItemType[m_len];
}

Sequence::Sequence(const Sequence& other)
{
    m_size = other.m_size;
    m_len = other.m_len;
    m_array = new ItemType[m_len];

    //copying everything over now
    for(int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
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
    delete []m_array;
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
    //if outside of array boundaries
    if(pos < 0 || pos > m_size || m_size + 1 > m_len)
    {
        return false;
    }
    //move everything up
    for(int i = m_size; i > pos; i--)
    {
        m_array[i] = m_array[i - 1]; 
    }

    m_array[pos] = value;
    m_size++;
    return true; 
}


int Sequence::insert(const ItemType& value)
{
    int p = 0;
    for(int i = 0; i < m_size; i++)
    {
        if(value <= m_array[i])
        {
            p = i;
        }
    }

    if(insert(p, value))
    {
        return p;
    }
    else
    {
        return -1;
    }
}

 
bool Sequence::erase(int pos)
{
    //if outside of array
    if(pos < 0 || m_size <= pos)
    {
        return false;
    }
    //move everything down
    for(int i = pos; i < m_size; i++)
    {
        m_array[i] = m_array[i + 1];
    }
    
    m_size--; 
    return true;
}
 
int Sequence::remove(const ItemType& value)
{
    //counts how many items have been removed
    int counter = 0;

    for(int i = 0; i < m_size; i++)
    {
        if(value == m_array[i])
        {
            erase(i);
            counter++;
        }
    }

    //don't have to change size because erase does it for you
    return counter;
}

bool Sequence::get(int pos, ItemType& value)
{
    //if outside of array
    if(pos < 0 || m_size <= pos)
    {
        return false;
    }

    value = m_array[pos];
    return true;
}


bool Sequence::set(int pos, const ItemType& value)
{
    //if outside of array
    if(pos < 0 || m_size <= pos)
    {
        return false;
    }

    m_array[pos] = value;
    return true;
}


int Sequence::find(const ItemType& value) const
{
    for(int i = 0; i < m_size; i++)
    {
        if(value == m_array[i])
        {
           return i;
        }
    }

    return -1;
}


void Sequence::swap(Sequence& other)
{
    //swapping arrays
    ItemType* temp1 = m_array;
    m_array = other.m_array;
    other.m_array = temp1;
    
    //swapping m_lens
    int temp2 = m_len;
    m_len = other.m_len;
    other.m_len = temp2;
    
    //swapping m_size
    int temp3 = m_size;
    m_size = other.m_size;
    other.m_size = temp3;
}

void Sequence::dump() const
{
    for(int i = 0; i <= m_size + 10; i++)
    {
        std::cerr << m_array[i] << ", ";
    }
    std::cerr << "= " << m_size << ", " << m_len << '\n';
}
