#include <iostream>


void pp(int& i)
{
    std::cout << &i << " " << i << " " << sizeof(i) << "\n";
}

template <class T>  //can also say 'typename'
class DynamicArray
{
    size_t m_size;
    T* m_arr;

    public:

    DynamicArray(size_t size)
        :m_size(size)
        ,m_arr (new T[size])
    {
        std::cout << "Array constructor\n";
    }

    ~DynamicArray()
    {
        delete[] m_arr;
        std::cout << "Array destructor" << "\n";
    }

    T get(size_t index) const
    {
        return m_arr[index];
    }

    void set(size_t index, T val)
    {
        m_arr[index] = val;
    }

    void print() const{
        for(size_t i =0; i < m_size; i++)
        {
            std::cout << i << " " << m_arr[i] << "\n";
        }
    }

    T& operator[](size_t index)
    {
        return m_arr[index];
    }

    const T& operator[](size_t index) const
    {
        return m_arr[index];
    }
};



int main(int argc, char* argv[])
{
    DynamicArray<float> myArray(10);

    myArray[2] = 17;

    std::cout << myArray[2] << "\n";

    return 0; 
}