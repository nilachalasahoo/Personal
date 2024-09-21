#include<iostream>
#include<windows.h>
#include<vector>
using namespace std;
class Memory{
    public:
        void *p;
        size_t size;
        bool isFree;
        Memory *pre;
        Memory *next;
        Memory(void *p,size_t size,bool isFree){
            this->p=p;
            this->size=size;
            this->isFree=isFree;
            pre=nullptr;
            next=nullptr;
        }
};
class List{
    private:
        Memory *head;
        int n;
    public:
        List(){
            head=nullptr;
            n=0;
        }
        List(Memory *m){
            head=m;
            n=1;
        }
        void add(Memory *m1,Memory *m2){
            m2->next=m1->next;
            m1->next=m2;
            m2->pre=m1;
            if(m2->next)
                m2->next->pre=m2;
            n++;

        }
        void merger(Memory *m){
            if(m->next && m->next->isFree){
                m->size+=m->next->size;
                m->next=m->next->next;
                if(m->next)
                    m->next->pre=m;
                n--;
            }
            if(m->pre && m->pre->isFree){
                m->pre->size+=m->size;
                m->pre->next=m->next;
                if(m->next)
                    m->next->pre=m->pre;
                n--;
            }
        }
        Memory* operator[](int i){
            Memory *curr=head;
            while(i>0){
                curr=curr->next;
                i--;
            }
            return curr;
        }
        void display(){
            cout<<endl<<"Location\tSize\tIsFree"<<endl;
            Memory *curr=head;
            while(curr){
                cout<<curr->p<<"\t"<<curr->size<<"\t"<<curr->isFree<<endl;
                curr=curr->next;
            }
        }
        int size(){
            return n;
        }
};
class MemoryManager{
    private:
        void *pMem;
        size_t total_byte;
        size_t free_byte;
        List free_page;
    public:
        MemoryManager(size_t size){
            pMem=VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if(pMem==NULL){
                cout<<"Memory Allocation Failed"<<endl;
                exit(1);
            }
            total_byte=size;
            free_byte=size;
            Memory *m=new Memory(pMem,size,true);
            free_page=List(m);
        }
        void* allocate(size_t size){
            for(int i=0;i<free_page.size();i++){
                Memory *m=free_page[i];
                if(m->isFree && m->size>=size){
                    free_byte=free_byte-size;
                    m->isFree=false;
                    if(m->size>size){
                        Memory *new_m=new Memory(reinterpret_cast<char*>(m->p)+size,m->size-size,true);
                        m->size=size;
                        free_page.add(m,new_m);
                    }
                    return m->p;
                }
            }
            cout<<"Can't allocate memory sucessfully"<<endl;
            return nullptr;
        }
        void deallocate(void* p){
            for(int i=0;i<free_page.size();i++){
                Memory *m=free_page[i];
                if(m->p==p){
                    m->isFree=true;
                    free_byte=free_byte+m->size;
                    free_page.merger(m);
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
            free_byte=total_byte;
            Memory *m=new Memory(pMem,total_byte,true);
            free_page=List(m);
        }
        void display(){
            free_page.display();
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
    int* v2=reinterpret_cast<int*>(m.allocate(200));
    m.display();
    void* v3=m.allocate(300);
    m.display();
    m.allocate(500);
    int x=10;
    v2[0]=x;
    cout<<v2[0]<<endl;
    cout<<v1<<endl<<v2<<endl<<v3<<endl;
    m.display();
    m.deallocate(v2);
    m.display();
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
