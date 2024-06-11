#pragma once
#include <iostream>
#include <cstring>
#include "Main_struct_of_song.h"



template <typename T>
void addItemBack(T*& arr, int& size, T value)
{
	//1
	T* tmp = new T[size + 1];
	//2
	for (int i = 0; i < size; i++)
	{
		tmp[i] = arr[i];
	}
	//3
	tmp[size] = value;
	//4
	if (arr != nullptr) delete[] arr;
	//5
	arr = tmp;
	//6
	size++;
}



template <typename T>
void addItemBack2(T*& arr, int& size, const T& value) {
	T* tmp = new T[size + 1];
	for (int i = 0; i < size; i++) {
		tmp[i] = arr[i];
	}
	tmp[size] = value;
	delete[] arr;
	arr = tmp;
	size++;
}
