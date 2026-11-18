#pragma once
#ifndef GRAMS_MYVECTOR_H
#define GRAMS_MYVECTOR_H

#include <cstddef>
#include <stdexcept>

template<typename T>
class MyVector{
private:
	T* elem;
	std::size_t array_size; // how many elements are actually stored (size())
	std::size_t space; // how many elements the array has room for (capacity, reserve())
public:
	MyVector(){ // constructor, by default no memory allocated
		elem = nullptr;
		array_size = 0;
		space = 0;
	}

	~MyVector(){
		delete[] elem;
	}

	MyVector(const MyVector&) = delete;
	MyVector& operator=(const MyVector&) = delete;

	std::size_t size() const {
		return array_size;
	}

	std::size_t capacity() const {
		return space;
	}

	void reserve(std::size_t new_capacity){
		if (new_capacity <= space)
		{
			return; //already big enough, nothing to do
		}

		T* new_elem = new T[new_capacity];

		// copy new elements into bigger array
		try
		{
			for (std::size_t i = 0; i < array_size; i++){
				new_elem[i] = elem[i];
			}
		}
		catch (...){
			delete[] new_elem;
			throw;
		}

		// release old array (after copying succeeds) and switch to new bigger array
		delete[] elem;
		elem = new_elem;
		space = new_capacity;
	}

	void push_back(const T& value){
		if (array_size == space){ //full? make more room
			if (space == 0){
				reserve(1); //start with room for 1 if first element
			}
			else {
				reserve(space * 2); //double - keep push back fast
			}
		}

		elem[array_size] = value;
		array_size++;
	}

	bool empty()const
	{
		return array_size == 0;
	}

	void clear()
	{
		array_size = 0;
	}

	void pop_back()
	{
		if (array_size != 0)
		{
			array_size --;
		}
	}
	T& at(std::size_t index){
		if (index >= array_size){
			throw std::out_of_range("Index out of range!");
		}

		return elem[index];
	}

};

#endif
