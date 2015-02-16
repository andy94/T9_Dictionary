/* Andrei Ursache - 312CA */

#ifndef TRIE_H_
#define TRIE_H_

#include <iostream>

#include <string>
#include <cstdlib>

#include "Treap.h"
#include "Word.h"

#define RAND 1000

class Trie
{
	private:
		
		Treap<Word> *treap;
		Trie *nodes[8];
		
		/* retine 1 daca nodul fiu de pe pozitia i este valid (este drum)
		   si 0 in caz contrar */
		bool valid[8];
		
		/* retine 1 daca nodul contine un treap (formeaza cuvant)
		   si 0 in caz contrar */
		bool empty;
		
	public:
	
		Trie(): empty(true)
		{
			this->treap = NULL;
			
			for(int i = 0 ; i < 8 ; ++i)
			{
				this->nodes[i] = NULL;
				valid[i] = false;
			}
		}
		
		/* eliberare recursiva a datelor */
		~Trie()
		{
			for(int i = 0 ; i < 8 ; ++i)
			{
				if(valid[i])
				{
					delete nodes[i];
					
				}
			}
			
			if(!empty){
				delete treap;
			}
		}
		
		/* insereaza cuvantul word la calea way */
		void insert(std::string &way, Word &word)
		{
			static int it = 0;
			
			/* daca s-a gasit locul */
			if (it == ((int)way.length()) )
			{	
				/* daca nu are treap (nu sunt cuvinte) */
				if(empty)
				{
					treap = new Treap<Word>();
					empty = false;
				}
				
				treap->insert(treap, word, rand() % RAND);
				it = 0 ;
			}
			
			else
			{	
				int index = way[it]-50;
				
				/* daca fiul cautat nu se afla in componenta niciunui drum */
				if(!valid[index])
				{
					this->nodes[index] = new Trie();
					this->valid[index] = true;
				}
				
				it++;
				nodes[index]->insert(way, word);
			}
		}
		
		/* returneaza treapul de la nodul din drumul way */
		Treap<Word>* &get_treap(std::string &way)
		{
			static int it = 0;
			
			/* daca s-a gasit nodul */
			if (it == ((int)way.length()))
			{	
				/* caz de exceptie */
				if(empty)
				{
					cout<<"Treap empty\n";
				}
				
				it = 0;
				
				return this->treap;
			}
			
			/* cauta recursiv in rest */
			else
			{	
				int index = way[it]-50;

				it++;
				return nodes[index]->get_treap (way);
			}	
		}
		
};

#endif
