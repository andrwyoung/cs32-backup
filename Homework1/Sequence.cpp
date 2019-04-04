#include <iostream> //for dump()
#include "Sequence.h"


Sequence::Sequence()
{
    m_size = 0;
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
    if(pos < 0 || pos > m_size || m_size + 1 > DEFAULT_MAX_ITEMS)
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
    //determine larger one
    int larger = m_size;
    if(other.size() > m_size)
    {
        larger = other.size();
    }

    //swapping each value in m_array
    for(int i = 0; i < larger; i++)
    {
        ItemType temp = m_array[i];
        m_array[i] = other.m_array[i];
        other.m_array[i] = temp;
    }
    //swap m_size now
    int temp = m_size;
    m_size = other.size();
    other.m_size = temp;

}

void Sequence::dump() const
{
    for(int i = 0; i <= m_size + 10; i++)
    {
        std::cerr << m_array[i] << ", ";
    }
    std::cerr << "= " << m_size << '\n';
}
