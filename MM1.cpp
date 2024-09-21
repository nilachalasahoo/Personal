#include<iostream>
#include<windows.h>
#include<vector>
using namespace std;
class MemoryManager{
    private:
        void *pMem;
        size_t total_byte;
        size_t free_byte;
        struct Memory{
            void *p;
            size_t size;
            bool isFree;
        };
        vector<Memory> free_page;
        void merger(){
            int i=1;
            while(i<free_page.size()){
                if(free_page[i-1].isFree && free_page[i].isFree){
                    free_page[i-1].size+=free_page[i].size;
                    free_page.erase(free_page.begin()+i);
                }else{
                    i++;
                }
                
            }
        }
    public:
        MemoryManager(size_t size){
            pMem=VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if(pMem==NULL){
                cout<<"Memory Allocation Failed"<<endl;
                exit(1);
            }
            total_byte=size;
            free_byte=size;
            Memory m={pMem,size,true};
            free_page.push_back(m);
        }
        void* allocate(size_t size){
            for(int i=0;i<free_page.size();i++){
                Memory& m=free_page[i];
                if(m.isFree && m.size>=size){
                    free_byte=free_byte-size;
                    m.isFree=false;
                    if(m.size>size){
                        Memory new_m={reinterpret_cast<char*>(m.p)+size,m.size-size,true};
                        m.size=size;
                        free_page.insert(free_page.begin()+i+1,new_m); 
                    }
                    return free_page[i].p;
                }
            }
            cout<<"Can't allocate memory sucessfully"<<endl;
            return nullptr;
        }
        void deallocate(void* p){
            for(int i=0;i<free_page.size();i++){
                Memory& m=free_page[i];
                if(m.p==p){
                    m.isFree=true;
                    free_byte=free_byte+m.size;
                    merger();
                    cout<<"Memory De-allocation Sucessful"<<endl;
                    return;
                }
            }
            cout<<"Memory De-allocation Failed"<<endl;
        }
        bool isMemoryLeak(){
            return total_byte!=free_byte;
        }
        void deallocateAll(){
            free_page.clear();
            free_byte=total_byte;
            Memory m={pMem,total_byte,true};
            free_page.push_back(m);
        }
        void display(){
            for(int i=0;i<free_page.size();i++){
                Memory &m=free_page[i];
                cout<<m.p<<" "<<m.size<<" "<<m.isFree<<endl;
            }
            cout<<endl;
        }
        ~MemoryManager(){
            if (!VirtualFree(pMem, 0, MEM_RELEASE)) {
                cerr << "VirtualFree failed with error: " << GetLastError() << endl;
            }
        }
};

int main() {
    MemoryManager m(1000);
    cout<<m.isMemoryLeak()<<endl;
    m.display();
    int* v1=reinterpret_cast<int*>(m.allocate(100));
    void* v4;
    m.deallocate(v4);
    m.display();
    int* v2=reinterpret_cast<int*>(m.allocate(100));
    m.display();
    void* v3=m.allocate(300);
    int x=10;
    v2[0]=x;
    cout<<v2[0]<<endl;
    m.display();
    m.deallocate(v2);
    m.display();
    m.allocate(500);
    m.deallocate(v3);
    m.display();
    m.allocate(500);
    m.display();
    cout<<m.isMemoryLeak()<<endl;
    m.deallocateAll();
    m.display();
    cout<<m.isMemoryLeak()<<endl;    
    return 0;
}
