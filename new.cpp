#include <iostream>
#include <windows.h>
using namespace std;
int main() {
    // Allocate 50 bytes of memory
    int x=10;
    int *p=new int[7];
    p[0]=10;
    cout<<p[0]<<" "<<p<<endl;
    delete[] p;
    cout<<p[0]<<" "<<p;
}
