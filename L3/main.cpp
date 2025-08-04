#include <iostream>

void pp(int i)
{
    std::cout << &i << " " << i << " " << sizeof(i) << "\n";
}

int main(int argc, char* argv[])
{
    int a = 10;
    int b = 25;

    pp(a);
    pp(b);    

    return 0; 
}