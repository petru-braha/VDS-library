#pragma once

// if(f == nullptr) f = [](const T& x, constT& y)->bool { return x > y; } 

template <class T = int>
class array_sorting // behavioral singleton
{
	typedef const T& type;
	typedef const size_t& szt;
	
	void   merge();
	void   heapify(T*& arr, szt n, szt index, bool (*f)(type, type));
	size_t partition(T*& arr, szt left, szt rght, bool (*f)(type, type));

	static array_sorting<T>* instance;
	array_sorting() = default;
public:
	static array_sorting<T>* get_instance();

	void bubbs(T*& arr, szt n, bool (*f)(type, type) = nullptr);
	//void seles(bool (*f)(type, type) = nullptr);
	//void insrs(bool (*f)(type, type) = nullptr);

	//void mrges(bool (*f)(type, type) = nullptr);
	void heaps(T*& arr, szt n, bool (*f)(type, type) = nullptr);
	void qucks(T*& arr, szt left, szt rght, bool (*f)(type, type) = nullptr); 
};

template <class T>
array_sorting<T>* array_sorting<T>::instance = nullptr;
