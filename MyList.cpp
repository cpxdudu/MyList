#include<iostream>
using namespace std;

template<class T> class MyList;
template<class T> MyList<T> operator+(const MyList<T> &l1, const MyList<T> &l2);
template<class T> MyList<T> operator+(const MyList<T> &l1, const T &item); 
template<class T> ostream &operator<<(ostream &os, const MyList<T> &obj);

template<class T>
class MyList{
	friend MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2){
		MyList<T> tmp=10;
		while(tmp.size<l1.size+l2.size) tmp.double_space();
		tmp.help1=l1.help1+l2.help1;tmp.size=l1.size+l2.size;
		for(int i=0;i<l1.help1;++i) tmp.a[i]=l1.a[i];
		for(int i=l1.help1;i<tmp.help1;++i) tmp.a[i]=l2.a[i-l1.help1];
		return tmp;
	}
	friend MyList<T> operator + (const MyList<T> &l1, const T &item){
		MyList<T> l2;
		l2=l1;
		l2.push(item);
		return l2;
	}
	friend ostream & operator<<(ostream &os, const MyList<T> &obj){
		bool tmp=false;
		os<<"[";
		if(obj.help1==0) {os<<"]";tmp=true;}
		else {for(int i=0;i<obj.help1;++i)  os<<obj.a[i]<<",";}
		if(tmp==false) os<<"]";
		return os; 	
	}

	
	
private:
	T *a;
	int size;
	int help1;
	void double_space(){
		T *b;size=2*size;
		b=new T [size];
		for(int i=0;i<help1;++i) b[i]=a[i];
		delete []a;
		a=b;
	}
public:
	MyList(int length=1000){
		size = length;
		help1 = 0;
		a=new T [size];
	}
	MyList(int num, const T &item){
		a= new T [num];size=help1=num;
		for(int i=0;i<num;++i)  a[i]=item;
	}
	MyList(const MyList &l){
		size=l.size;help1=l.help1;
	}
    MyList(T* arr, int len){
		T *num;
		num=new T [len];
		for(int i=0;i<len;++i) num[i]=arr[i];
		a=num; help1=size=len;
	}
	MyList<T> &operator = (const MyList &l);
	MyList<T> &operator += (const T &item);
	MyList<T> &operator += (const MyList &l);
	MyList<T> get_item(int start, int end);
	
	void push(const T &item);
	void remove(const T &item);
	void insert(int index, const T &item);
	void clean();
	void sort(bool less=true);
	void erase(int start, int end); 
	void reverse();
	void mergearray(T b[], int first, int mid, int last, T temp[]);
	void mergesort(T b[], int first, int last,T temp[]);
	
	T get_item(int index);
	T pop();
	T &operator [](int index);
	
	int get_size();
	int count(const T &item);
    
	~MyList(){delete [] a;}
};

template<class T>
void MyList<T>::push(const T &item){
	if(help1>0) double_space();
	help1+=1;size=help1;
	a[help1-1]=item;
}
template<class T>
void MyList<T>::erase(int start,int end){
	T *b;
	b=new T[help1-(end-start)-1];
	for(int i=0;i<start;++i) b[i]=a[i];
	for(int i=end+1;i<help1;++i) {b[i-end+start-1]=a[i];}
	help1=help1-(end-start)-1;
	a=b;
}
template<class T>
void MyList<T>::remove(const T &item){
	for(int i=0;i<help1;++i){
		if(a[i]==item) {erase(i,i);break;}
	}
}
template<class T>
void MyList<T>::insert(int index,const T &item){
	T *b;
	b=new T[help1+1];
	for(int i=0;i<index;++i) b[i]=a[i];
	b[index]=item;
	for(int i=help1;i>index;--i) b[i]=a[i-1];
	b[help1]=a[help1-1];
	delete []a;
	help1+=1;
	a=b;
}
template<class T>
void MyList<T>::clean(){
	size=help1=0;
}
template<class T>
void MyList<T>::reverse(){
	T *b;
	b=new T[help1];
	for(int i=0;i<help1;++i) b[i]=a[help1-i-1];
	a=b;
}
template<class T>
void MyList<T>::sort(bool less){
	T *c;
	c=new T[help1];
	mergesort(a,0,help1-1,c);
	if(less=false) reverse();
}
template<class T>
void MyList<T>::mergearray(T b[],int first,int mid,int last,T temp[]){  
    int i=first,j=mid+1;int m=mid,n=last;int k=0;  
    while(i<=m && j<=n){  
        if (b[i] <= b[j]) temp[k++] = b[i++];  
        else temp[k++] = b[j++];  
    }  
    while(i<=m) temp[k++] = b[i++];  
    while(j<=n) temp[k++] = b[j++];  
    for(i=0;i<k;i++)  b[first+i] = temp[i];  
}  
template<class T>
void MyList<T>::mergesort(T b[], int first, int last,T temp[]){  
    if (first < last){  
        int mid = (first + last) / 2;  
        mergesort(b, first, mid, temp);  
        mergesort(b, mid + 1, last, temp);   
        mergearray(b, first, mid, last, temp);  
    }  
}

template<class T>
MyList<T>& MyList<T>::operator+=(const T &item){
	push(item);
	return (*this);
}
template<class T>
MyList<T>& MyList<T>::operator+=(const MyList<T>&l1){
	*this= *this + l1;
	return(*this);
}
template<class T>
MyList<T>& MyList<T>::operator=(const MyList &l){
	if(this==&l){
		return *this;
	}
	delete []a;
	size=l.size; help1=l.help1;
	a=new T [help1];
	for(int i=0; i<help1; ++i){
		a[i]=l.a[i];
	} 
	return *this;
} 
template<class T>
MyList<T> MyList<T>::get_item(int start, int end){
	while(start<0) start+=help1;
	while(end<0) end +=help1;
	MyList<T> d;
	if(start>end){
		cout<<"wrong index"<<endl;
	}
	else{
		T *c;
		c=new T[end-start+1];
		for (int i=start; i<=end; ++i){
			d.push(a[i]);
		}
		d.size=d.help1=end-start+1;
	}
	return d;
}

template<class T>
T MyList<T>::get_item(int index){
	return a[index];
}
template<class T>
T MyList<T>::pop(){
	try{
		if(help1==0) throw(1);
		else {return a[(help1-1)--];}
	}
	catch(int){
		cout<<"already empty"<<endl;exit(1);
	}
}
template<class T>
T& MyList<T>::operator[](int index){
	return a[index];
}

template<class T>
int MyList<T>:: get_size(){
	return help1;
}   
template<class T>
int MyList<T>::count(const T &item){
	int count=0;
	for(int i=0;i<help1;++i){
		if(a[i]==item) ++count;
	}
	return count;
}

int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
	a[3] = 15; 
	a.sort();
	a.reverse();
	a += 12;
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
	b = a.get_item(4, -3);
	b = a.get_item(3, -1); 
	a += b; 
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean();
	cout<<b.get_size()<<endl;
	a.erase(2, 5); 
	b = a + a; 
	b.insert(3, 116); 
	cout<<b<<endl; 
	b.remove(4);
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	return 0;
}




