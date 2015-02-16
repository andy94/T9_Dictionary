/* Andrei Ursache - 312CA */

#ifndef WORD_H_
#define WORD_H_

#include<iostream>
#include<string>

using namespace std;

struct Word
{
	/* valoarea cuvantului */
	string value;
	
	/* numar de aparitii */
	int count;
	
	Word(): count(0) { }
	
	void addData(std::string value, int count)
	{
		this->value=value;
		this->count=count;
	}
	
	~Word()
	{
		value.clear();
	}
	
	/* supraincarcare operatori */
	
	void operator++(int)
	{
		count++;
	}
	
	/* exemplu:
		a = "ana", 5
		b = "mar", 5
		c = "cad", 3
		
		=>	a > c (5 > 3)
		=>	a > b (5 == 5) si "ana" < "mar"
	*/
	
	bool operator>(Word &b)
	{
		if( ( count > b.count ) || ( count == b.count && value < b.value ) )
			return true;
			
		else
			return false;
	}
	
	bool operator<(Word &b)
	{
		if( ( count < b.count ) || ( count == b.count && value > b.value ) )
			return true;
			
		else
			return false;
	}
	
	bool operator==(Word &b)
	{
		if( count == b.count && value == b.value )
			return true;
			
		else
			return false;
	}
	
};

#endif
