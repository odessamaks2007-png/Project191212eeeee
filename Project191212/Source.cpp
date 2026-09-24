#include <iostream>
using namespace std;

template <class T>
class Array
{
private:
	T* data;
	int size;
	int count;
	int grow;
public:
	Array(int size = 0, int grow = 1)
	{
		this->size = size;
		this->grow = grow;
		this->count = 0;
		if (size > 0)
		{
			data = new T[size];
		}
		else
		{
			data = nullptr;
		}
	}
	~Array()
	{
		delete[] data;
	}
	int GetSize()
	{
		return size;
	}
	void SetSize(int size, int grow = 1)
	{
		if (size == this->size)
		{
			return;
		}
		T* newData = nullptr;
		if (size > 0)
		{
			newData = new T[size];
		}
		int newCount = count;
		if (newCount > size)
		{
			newCount = size;
		}
		for (int i = 0; i < newCount; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		this->size = size;
		this->count = newCount;
		this->grow = grow;
	}
	int GetUpperBound()
	{
		if (count == 0)
		{
			return -1;
		}
		return count - 1;
	}
	bool IsEmpty()
	{
		return count == 0;
	}
	void FreeExtra()
	{
		if (count == size)
		{
			return;
		}
		T* newData = nullptr;
		if (count > 0)
		{
			newData = new T[count];
		}
		for (int i = 0; i < count; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		size = count;
	}
	void RemoveAll()
	{
		delete[] data;
		data = nullptr;
		size = 0;
		count = 0;
	}
	T GetAt(int index)
	{
		return data[index];
	}
	void SetAt(int index, T value)
	{
		if (index >= 0 && index < size)
		{
			data[index] = value;
			if (index >= count)
			{
				count = index + 1;
			}
		}
	}
	T& operator[](int index)
	{
		return data[index];
	}
	void Add(T value)
	{
		if (count >= size)
		{
			int newSize;
			if (size == 0)
			{
				newSize = grow;
			}
			else
			{
				newSize = size + grow;
			}
			SetSize(newSize, grow);
		}
		data[count] = value;
		count++;
	}
	void Append(Array<T>& other)
	{
		for (int i = 0; i < other.count; i++)
		{
			Add(other.data[i]);
		}
	}
	Array<T>& operator=(Array<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		delete[] data;
		size = other.size;
		count = other.count;
		grow = other.grow;
		if (size > 0)
		{
			data = new T[size];
		}
		else
		{
			data = nullptr;
		}
		for (int i = 0; i < count; i++)
		{
			data[i] = other.data[i];
		}
		return *this;
	}
	T* GetData()
	{
		return data;
	}
	void InsertAt(int index, T value, int amount = 1)
	{
		if (index < 0 || index > count)
		{
			return;
		}
		for (int i = 0; i < amount; i++)
		{
			Add(T());
		}
		for (int i = count - 1; i >= index + amount; i--)
		{
			data[i] = data[i - amount];
		}
		for (int i = 0; i < amount; i++)
		{
			data[index + i] = value;
		}
	}
	void RemoveAt(int index, int amount = 1)
	{
		if (index < 0 || index >= count)
		{
			return;
		}
		if (index + amount > count)
		{
			amount = count - index;
		}
		for (int i = index; i < count - amount; i++)
		{
			data[i] = data[i + amount];
		}
		count -= amount;
	}
};
int main()
{
	Array<int> arr(5, 5);
	arr.Add(10);
	arr.Add(20);
	arr.Add(30);
	arr.Add(40);
	cout << "Size: " << arr.GetSize() << endl;
	cout << "UpperBound: " << arr.GetUpperBound() << endl;
	cout << "Elements:" << endl;
	for (int i = 0; i <= arr.GetUpperBound(); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	arr.SetAt(1, 200);
	cout << "After SetAt:" << endl;
	for (int i = 0; i <= arr.GetUpperBound(); i++)
	{
		cout << arr.GetAt(i) << " ";
	}
	cout << endl;
	arr.InsertAt(2, 999);
	cout << "After InsertAt:" << endl;
	for (int i = 0; i <= arr.GetUpperBound(); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	arr.RemoveAt(1);
	cout << "After RemoveAt:" << endl;
	for (int i = 0; i <= arr.GetUpperBound(); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}