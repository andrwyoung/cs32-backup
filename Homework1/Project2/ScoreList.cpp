#include "ScoreList.h"

ScoreList::ScoreList()
    :m_sequence()
{
}

ScoreList::ScoreList(const ScoreList& other)
    :m_sequence(other.m_sequence)
{
}

ScoreList& ScoreList::operator=(const ScoreList& other)
{
    m_sequence = other.m_sequence;
    return *this;
}

bool ScoreList::add(unsigned long score)
{
    if(score > 100)
    {
        return false;
    }
    return m_sequence.insert(m_sequence.size(), score);
}

bool ScoreList::remove(unsigned long score)
{
    return m_sequence.erase(m_sequence.find(score));
}

int ScoreList::size() const
{
    return m_sequence.size();
}

unsigned long ScoreList::minimum() const
{
    if(m_sequence.empty())
    {
        return NO_SCORE;
    }
    for(int i = 0; i <= 100; i++)
    {
        if(m_sequence.find(i) != -1)
        {
            return i;
        }
    }

    return -1;
}

unsigned long ScoreList::maximum() const
{
    if(m_sequence.empty())
    {
        return NO_SCORE;
    }
    for(int i = 100; i >= 0; i--)
    {
        if(m_sequence.find(i) != -1)
        {
            return i;
        }
    }

    return -1;
}

// void ScoreList::dump() const
// {
//     m_sequence.dump();
// }
