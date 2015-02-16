/* Andrei Ursache - 312CA */

#include <iostream>
#include <fstream>

#include <string>
#include <cstdlib>

#include "Treap.h"
#include "Trie.h"

#define RAND 1000

using namespace std;

/*	Functie de conversie a unui string de litere
intr-un string ce contine "cifrele telefonului"
corespunzatoare literelor	*/
	
string get_way(string &value)
{
	// stringul de numere
	string way;
	way.reserve(value.length());

	for(int i = 0 ; i < (int)value.length() ; ++i)
	{
		switch( value[i] )
		{
			case 'a': case 'b': case 'c':
				way.push_back('2');
				break;
				
			case 'd': case 'e': case 'f':
				way.push_back('3');
				break;
				
			case 'g': case 'h': case 'i':
				way.push_back('4');
				break;
				
			case 'j': case 'k': case 'l':
				way.push_back('5');
				break;
				
			case 'm': case 'n': case 'o':
				way.push_back('6');
				break;
				
			case 'p': case 'q': case 'r': case 's':
				way.push_back('7');
				break;
			
			case 't': case 'u': case 'v':
				way.push_back('8');
				break;
				
			case 'w': case 'x': case 'y': case 'z':
				way.push_back('9');
				break;
				
			default:
				break;
		}
	}
	
	return way;
}

/* Program */

int main(int argc, char* argv[])
{
	/* numar de cuvinte din "baza de date" */
	int nr_data;
	
	ifstream in;
	ofstream out;
	
	in.open("date.in");
	out.open("date.out");
	
	in >> nr_data;
	
	/* numar de cuvinte invalid */
	if( nr_data <= 0)
	{
		in.close();
		out.close();
		
		return 0;
	}
	
	/* construieste Trie */
	Trie *data = new Trie;
	
	/* cuvantul de inserat */
	Word word;
	
	/* calea la care se inseareaza (in trie) */
	string way;
	
	int count;
	string value;
	
	for(int i = 0 ; i < nr_data ; ++i)
	{
		in >> value >> count;
		
		/* construieste cuvant */
		word.addData(value, count);
		
		/* determinarea "drumului" */
		way = get_way(value);
		
		data->insert(way, word);
	}
	
	int nr_operations;
	int pos;
	int capacity;
	
	string num;
	
	in >> nr_operations;
	
	/* rulare operatii */
	for(int i = 0 ; i < nr_operations ; ++i)
	{
		in >> value;
		
		pos = (int) value.find('*');
		
		/* extrage "drumul" */
		way.assign(value, 0, pos );
		
		/* daca se cere al x+1 - lea cuvant */
		if( pos > 0)
		{
			num.assign(value, pos+1, (int)value.length()) ;
			
			/* determina x */
			count = atoi(num.data());
		}
		
		else
		{
			/* numarul maxim de aparitii */
			count = 0;
		}
		
		Treap<Word> *&treap = data->get_treap(way);
		
		capacity = treap->get_nr();
		
		/* determina al <count>-lea cuvant ca numar de aparitii*/
		word = treap->findK(capacity - count % capacity);
		
		/* afiseaza cuvant */
		out << word.value << "\n";
		
		/* incrementeaza numarul de aparitii al cuvantului */
		treap->erase(treap, word);
		word++;
		treap->insert(treap, word, rand() % RAND);
	}
	
	delete data;
	
	in.close();
	out.close();
	
	return 0;
}
