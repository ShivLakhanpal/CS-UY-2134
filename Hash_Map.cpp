//Shiv Lakhanpal
//Data Structures Fall 2016
//Net ID: svl238
//Homework 10 - Programming Part 1

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

template<typename HashedObj>
class HashTable
{
public:
	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry {
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY)
			: element(e), info(i) {}
	};
public:
	typedef typename vector<HashEntry>::const_iterator iterator;
	explicit HashTable(int size = 101) :currentSize(0) {
		array.resize(size);
	}

  void makeEmpty();
	bool insert(const HashedObj &);
	iterator end() const;
	int capacity() const;
	bool contains(const HashedObj &);
	iterator find(const HashedObj &);
	bool remove(const HashedObj &);

private:
	std::hash<HashedObj> hf;

	vector<HashEntry> array;
	int currentSize;
	double MaxLoadFactor = 0.5;
	void rehash();
};

template<typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj & x){
	if (find(x) !=array.end()){
       return false;
}


	size_t thePosition = hf(x) % array.size();
	if (array[thePosition].info == DELETED || array[thePosition].info == EMPTY)
	{
    currentSize++;
    array[thePosition].info = ACTIVE;
		array[thePosition].element = x;
		if (currentSize >= MaxLoadFactor * array.size()) rehash();
		return true;
	}
	else if (array[thePosition].info == ACTIVE)
	{
		for (size_t theNewPosition = thePosition+1; theNewPosition < array.size(); theNewPosition++)
		{
			if (array[theNewPosition].info == DELETED || array[theNewPosition].info == EMPTY)
			{
        currentSize++;
        array[theNewPosition].info = ACTIVE;
				array[theNewPosition].element = x;
				if (currentSize >= MaxLoadFactor* array.size()) rehash();
				return true;
			}
		}
		for (int theNewPosition = 0; theNewPosition < thePosition; theNewPosition++)
		{
			if (array[theNewPosition].info == EMPTY || array[theNewPosition].info == DELETED)
			{
        currentSize++;
        array[theNewPosition].info = ACTIVE;
				array[theNewPosition].element = x;
				if (currentSize >= MaxLoadFactor* array.size())
              rehash();
				      return true;
			}
		}
	}
}
template<typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj & x)
{
	for (int i = 0; i < array.size();i++)
	{
		if (array[i].info== ACTIVE && array[i].element == x)
      return true;
	}
	return false;
}
template<class HashedObj>
typename HashTable<HashedObj>::iterator HashTable<HashedObj>::find(const HashedObj & x)
{

	size_t thePosition = hf(x) % array.size();
	iterator findItr = array.begin() + thePosition;
	if (array[thePosition].info == ACTIVE && array[thePosition].element == x)
    return findItr;


	for (int i = thePosition + 1; i < array.size(); ++i){
		if (array[i].info == EMPTY || array[i].info == DELETED) //If the info is deleted and the info is empty
      return array.end();


		else if(array[i].element == x && array[i].info == ACTIVE){     //If the info is active and the element is equal to x
			findItr = array.begin() +i;
			return findItr;
		}
	}
	for (int i = 0; i < thePosition; ++i){
		if (array[i].info == EMPTY || array[i].info == DELETED)   //If the info is deleted and the info is empty
			return array.end();
		else if (array[i].info == ACTIVE && array[i].element == x) //If the info is active and the element is equal to x
		{
			findItr = array.begin() + i;
			return findItr;
		}
	}
	return array.end();

}

template< typename HashedObj >
bool HashTable<HashedObj>::remove(const HashedObj & x) {
	int index = hf(x) % array.size();
	for (int i = index; i < array.size(); ++i) {
		if (array[i].info == EMPTY)
			return false;
		if (array[i].info == ACTIVE && array[i].element == x) {
			array[i].info = DELETED;
			--currentSize;
			return true;
		}
	}
	for (int i = 0; i < index; ++i) {
		if (array[i].info == EMPTY)
			return false;
		if (array[i].info == ACTIVE && array[i].element == x) {
			array[i].info = DELETED;
			--currentSize;
			return true;
		}
	}
	/**
	* There's a clever but convoluted way to merge the above two loops into one
	* if you would like to give it a shot.
	*/
	return false;
}

template< typename HashedObj >
void HashTable<HashedObj>::rehash() {
	vector<HashEntry> arrayPast = std::move(array);
  currentSize = 0;
	array.clear();
	array.resize(2 * arrayPast.size() + 1);
	for (int i = 0; i < arrayPast.size(); i++){
		insert(std::move(arrayPast[i].element));
	}
	return;
}

template< typename HashedObj >
void HashTable<HashedObj>::makeEmpty() {
	for (auto i : array)
		i.info = EMPTY;
}

template<typename HashedObj>
typename HashTable<HashedObj>::iterator HashTable<HashedObj>::end() const {
	return array.end();
}

template<typename HashedObj>
int HashTable<HashedObj>::capacity() const {
	return array.size();
}

SCENARIO("Testing the hash table with linear probing") {
	HashTable<int> hst;
	int n = 10; //adjust to make it less than 10 when rehash isn't implemented;
	int capacity = hst.capacity();

	GIVEN("A hash table has been created but not filled") {
		WHEN("Method insert is called") {
			THEN("All insertions of original elements should succeed") {
				for (int i = 0; i < n; ++i)
					REQUIRE(hst.insert(i*capacity) == true);
			}
			THEN("All insertions of duplicate elements should fail") {
				for (int i = 0; i < n; ++i) {
					REQUIRE(hst.insert(i * capacity) == true);
					REQUIRE(hst.insert(i * capacity) == false);
				}
			}
		}
	}

	GIVEN("A hash table has been created and filled ") {
		for (int i = 0; i < n; ++i)
			hst.insert(i * capacity);
		capacity = hst.capacity();

		WHEN("Method insert is called") {
			THEN("It should fail on all duplicate elements") {
				for (int i = 0; i < n; ++i) {
					REQUIRE(hst.insert(i*capacity) == false);
				}
			}
			THEN("It should pass on all original elements") {
				for (int i = 0; i < n; ++i) {
					hst.remove(i * capacity);
					REQUIRE(hst.insert(i*capacity) == true);
				}
				for (int i = n; i < 2 * n; ++i) {
					REQUIRE(hst.insert(i*capacity) == true);
				}
			}
		}

		WHEN("Method remove is called") {
			THEN("It should return true for any item in the table.") {
				for (int i = 0; i < n; ++i)
					REQUIRE(hst.remove(i * capacity) == true);
			}
		}

		WHEN("Method remove is called") {
			THEN("It should return false for any item not in the table.") {
				for (int i = n; i < 2 * n; ++i)
					REQUIRE(hst.remove(i * capacity) == false);
			}
		}

		WHEN("Method find is used") {
			for (int i = 0; i < n; ++i)
				hst.insert(i * capacity);
			THEN("All inserted elements should be found") {
				for (int i = 0; i < n; ++i)
					REQUIRE(hst.find(i * capacity)->element == i * capacity);
			}
			THEN("Any non-inserted element should not be found") {
				for (int i = n; i < 2 * n; ++i)
					REQUIRE(hst.find(i*capacity) == hst.end());
			}
			THEN("Any element that is deleted should not be found.") {
				for (int i = 0; i < n; ++i) {
					hst.remove(i * capacity);
					REQUIRE(hst.find(i * capacity) == hst.end());
				}
			}
		}

		WHEN("The load factor is greater than 0.5") {
			const int * temp = &(hst.find(5 * capacity)->element);
			for (int i = 1; i < 100; ++i)
				hst.insert(i);
			THEN("rehash() should be called.") {
				REQUIRE(hst.capacity() != capacity);
			}
		}
	}
}
