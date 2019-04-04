#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <string>

using ItemType = std::string;

class Sequence
{
  public:
    Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);

    ~Sequence();

    bool empty() const;
    int size() const;

    bool insert(int pos, const ItemType& value); 
    int insert(const ItemType& value);

    bool erase(int pos); 
    int remove(const ItemType& value);

    bool get(int pos, ItemType& value) const; 
    bool set(int pos, const ItemType& value); 
    int find(const ItemType& value) const;

    void swap(Sequence& other);

    void dump() const;

private:
	struct Node
	{
		ItemType value;
		Node* next;
		Node* prev;
	};

	int m_size; //just makes it easier. not neccessary
	Node* m_head;
	Node* m_tail;  
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif
