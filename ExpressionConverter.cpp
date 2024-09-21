#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include <stack>
using namespace std;
template<class T>
class Converter{
    private:
        string s;
    public:
        void takeInput();
        T eval(T x1,T x2,char op);
        T getResult();
};
template<class T>
void Converter<T>::takeInput(){
    cout<<"Enter an valid expression string to evaluate result : ";
    getline(cin,s);
}
template<class T>
T Converter<T>::eval(T x1,T x2,char op){
    if(op=='+') return x1+x2;
    else if(op=='-') return x1-x2;
    else if(op=='*') return x1*x2;
    else if(op=='/') return x1/x2;
    return 0;
}
template<class T>
T Converter<T>::getResult(){
    stack<T> val;
    stack<char> operators;
    int n=s.length();
    for(int i=0;i<n;i++){
        char c=s[i];
        if(c>='0'&&c<='9'||c=='.'){
            int j=i+1;
            while(j<n){
                c=s[j];
                if(c>='0'&&c<='9'||c=='.'){
                   j++;
                }else{
                    break;
                }
            }
            T x=stod(s.substr(i,j-i));
            val.push(x);
            i=j-1;
        }else if(c=='*'||c=='/'||c=='%'){
            if(!operators.empty()&&(operators.top()=='*'||operators.top()=='/')){
                T x=val.top();
                val.pop();
                x=eval(val.top(),x,operators.top());
                val.pop();
                val.push(x);
                operators.pop();
            }
            operators.push(c);
        }else if(c=='+'||c=='-'){
            while(!operators.empty()){
                T x=val.top();
                val.pop();
                x=eval(val.top(),x,operators.top());
                val.pop();
                val.push(x);
                operators.pop();
            }
            operators.push(c);
        }else{
            throw runtime_error("This is a wrong Expression...");
        }
    }
    T res=val.top();
    val.pop();
    while(!operators.empty()){
        res=eval(val.top(),res,operators.top());
        val.pop();
        operators.pop();
    }
    return res;
}


int main(){
    Converter<double> c;
    try{
        c.takeInput();
        double res=c.getResult();
        cout<<"The result of Expression is : "<<res;
    }catch(exception& e){
        cout<<e.what()<<endl;
    }
    
    return 0;
}