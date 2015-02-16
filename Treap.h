/* Andrei Ursache - 312CA */

#ifndef TREAP_H_
#define TREAP_H_

#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T> class Treap
{
	private:
	
	T key;
	int priority;
	
	Treap<T> *left, *right;
	
	bool nil;
	int nr_nodes;

	public:
	
	/* initializare date */
	Treap() : priority(-1), left(NULL), right(NULL), nil(true), nr_nodes(0) {}

	/* elibereaza recursiv memoria */
	~Treap()
	{
		if(!this->isNil())
			delete this->left;

		if(!this->isNil())
			delete this->right;
	}
	
	/* transforma un nod nil intr-unul valid */
	void addData(T &key, int priority)
	{
		this->nil = false;
		this->key = key;
		this->priority = priority;
		this->nr_nodes = 1;
		this->left = new Treap();
		this->right = new Treap();
	}

	/* transforma un nod valid intr-unul nil */
	void delData()
	{
		this->nil = true;
		this->priority = -1;
		delete this->left;
		delete this->right;
		this->nr_nodes = 0;
	}

	bool isNil()
	{
		return this->nil;
	}
	
	int get_nr()
	{
		return this->nr_nodes;
	}

	/* verifica daca este cheie key in treap */
	bool find(T &key)
	{
		if(this->key == key)
			return true;

		if(this->key < key)
		{
			if (this->right->isNil())
				return false;
			else
				return this->right->find(key);
		}

		else
		{
			if (this->left->isNil())
				return false;
			else
				return this->left->find(key);
		}

	}

	/* rotatie dreapta */
	void rotateRight(Treap<T> *&nod)
	{
		if(this->isNil() || nod->isNil())
			return;

		/* modifica numarul de noduri */
		int aux = nod->nr_nodes;
		nod->nr_nodes = nod->nr_nodes - nod->left->nr_nodes +
									nod->left->right->nr_nodes;
		nod->left->nr_nodes = aux;

		/* efectueaza rotatia */
		Treap<T> *b = nod->left; 
		nod->left = b->right;
		b->right = nod;
		nod = b;
	}

	/* rotatie stanga */
	void rotateLeft(Treap<T> *&nod)
	{
		if(this->isNil() || nod->isNil())
			return;

		/* modifica numarul de noduri */
		int aux = nod->nr_nodes;
		nod->nr_nodes = nod->nr_nodes - nod->right->nr_nodes +
									nod->right->left->nr_nodes;
		nod->right->nr_nodes = aux;

		/* efectueaza rotatia */
		Treap<T> *b = nod->right; 
		nod->right = b->left;
		b->left = nod;
		nod = b;
	}

	/* insereaza cheia key cu prioritatea priority */
	void insert(Treap<T> *&fatherPointer, T &key, int priority)
	{
		if(this->isNil())
		{
			this->addData(key, priority);
			return;
		}
		
		/* incrementeaza numarul de noduri */
		this->nr_nodes++;
		
		if(key < this->key)
		{
			this->left->insert(fatherPointer->left, key, priority);
		} 
		
		else
		{
			this->right->insert(fatherPointer->right, key, priority);
		}
		
		/* efectuare rotatii pentru pastrarea invariantului de heap */
		
		if(this->left->priority > this->priority)
		{
			rotateRight(fatherPointer);

		} 
		
		else if (this->right->priority > this->priority)
		{
			rotateLeft(fatherPointer);
		}
	}

	/* sterge cheia key din treap */
	void erase(Treap<T> *&fatherPointer, T &key) {
		
		static int it = 0;
		
		if(this->isNil())
		{
			return ;
		}

		if (key < this->key)
		{
			this->nr_nodes--;
			this->left->erase(fatherPointer->left, key);
		}
		
		else if (key > this->key)
		{
			this->nr_nodes--;
			this->right->erase(fatherPointer->right, key);
		}
		
		/* daca s-a gasit nodul */
		else if (this->left->isNil() && this->right->isNil())
		{
			this->delData();
			it = 0;
		} 
		
		else
		{
			/* daca este chiar radacina */
			if( it == 0)
			{
				this->nr_nodes--;
				it++ ;
			}	
		
			/* aduce nodul spre capatul treapului (frunza), prin rotatii */
			
			if(this->left->priority > this->right->priority)
			{
				this->rotateRight(fatherPointer);
				fatherPointer->right->erase(fatherPointer->right, key);
			} 
			
			else
			{
				this->rotateLeft(fatherPointer);
				fatherPointer->left->erase(fatherPointer->left, key);
			}
		}
	}

	/* determina a k-a cheie din treap - crescator */
	T findK(int k)
	{
		static int poz = 0 ;
		
		if(poz == 0)
		{
			poz = (this->nr_nodes - this->right->nr_nodes);
		}
		
		/* daca s-a gasit al k-lea nod */
		if ( k == poz )
		{
			poz = 0;
			return this->key;
		}
		
		/* cautare recursiva */
		
		else if ( k < poz && !this->left->isNil())
		{
			poz = poz - (this->left->right->nr_nodes) -1;
			return this->left->findK(k);
		}
		
		else 
		{
			poz = poz + (this->right->left->nr_nodes) + 1;
			return this->right->findK(k);
		}
	}
	
};

#endif
