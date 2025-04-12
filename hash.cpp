#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;
int M = 10;

template<class T>class Set {
private:
    class Structure {
        public:
        string key;
        T val;

        Structure(T val1,string key1) {key = key1; val = val1;}
        void change_val(T val1) {val = val1;}
    };
    vector<list<Structure>> v;
    size_t n;

public:

    string key;
    Set(int m = M)
    {
        n = 0;
        v.resize(m);
    }

    int IsEmpty();

    int  h(string str);

    int Find(const T&x, string str);
    int Find1(const T&x, string str);
    bool in_table(string str);

    T find_val(string str);
    bool Search(string str);
    int Get_N();
    int Del(string key) ;
    int Insert(const T&x,string str);

    int Erase(const T&x);
    template<class T1> friend ostream &operator<<(ostream &cout, Set<T1> &v);
};
template<class T> ostream &operator<<(ostream &cout, Set<T> &v){
    int k;
    for(size_t i = 0; i < v.v.size();++i)
    {
        k = 0;
        cout << "[" << i << "]\n";
        cout << "{";
        for (auto it = v.v[i].begin(); it != v.v[i].end();++it)
        {
            if (k == 0) cout << endl;
            cout <<"\t( key: " <<  it -> key << ";  value: " << it -> val << " )\n";
            k++;
        }
        cout << " }\n";
    }
    cout << endl;
    return cout;
}
template <class T> int Set<T>::Insert(const T&x, string str){
//	v[h(str)]=  12; //str;
	if(Find1(x,str)) return -1;
	if (in_table(str)) {
		int l = h(str);
		for(auto it = v[l].begin(); it != v[l].end(); ++it)
		{
			if(it -> key == str)
			it -> change_val(x);
		}
	}
	else {
	Structure t(x, str);
	v[h(str)].push_back(t); n++;}
	if(n > v.size()*4){
		size_t m = v.size();
		Set<T> s(2*m); 
		
		for(size_t i = 0;i < m; i++)
			for(auto it =v[i].begin(); it != v[i].end(); ++it) s.Insert(it -> val, it -> key);
		//v.swap(s.v);
		n = s.n;
		M = 2 * M;
	}
	return 0;
}
//-----------------
	template <class T> int Set<T>::IsEmpty()
	{
		return n == 0;
	}

	 template <class T> int Set<T>::h(string str)
	{
		int h = 0;
		int k = 2;
		for (char c : str)
		{
		    int x = (int)(c - ' ' + 1);
		    h = (h + k * x) % M;
		    k = k * k;
		}
	//	cout <<"|" <<  h << "|";
		return h;
	}

	template <class T> int Set<T>::Find(const T&x, string str)
	{
		int i = h(str);
		for(auto it = v[i].begin(); it != v[i].end(); ++it)
		{
			if(*it == x)
			return 1;
		}
		return 0;
	}
	template <class T> int Set<T>::Find1(const T&x, string str)
	{
		int i = h(str);
		for(auto it = v[i].begin(); it != v[i].end(); ++it)
		{
			if(it -> val == x)
			return 1;
		}
		return 0;
	}
    template <class T> bool Set<T>::in_table(string str)
	{
		int i = h(str);
		for(auto it = v[i].begin(); it != v[i].end(); ++it)
		{
			if(it -> key == str)
			return 1;
		}
		return 0;
	}
	
	template <class T> T Set<T>::find_val(string str)
	{
		int i = h(str);
		T res;
		for(auto it = v[i].begin(); it != v[i].end(); ++it)
		{
			if(it -> key == str) {res = it -> val; break;}
		}
		return res;
	}

	template <class T> bool Set<T>:: Search(string str) {
		if (in_table(str)) {cout << "Value: "<< find_val(str) << endl; return true;}
		cout << "No value by key: " << str << endl;
		return false;
	}

	template <class T> int Set<T>:: Get_N() {return n;}

	template <class T> int Set<T>:: Del(string key) 
	{
		if (in_table(key))
		{
			int i = h(key);
			for(auto it = v[i].begin(); it != v[i].end(); ++it)
			{
				if(it -> key == key) {cout << "Erased: " << it -> key << endl;v[i].erase(it); n--;}
				
				return 1;
			}
		} 
		cout << "No pair with this key: " << key << endl;
		return false;
	}

	template <class T> int Set<T>:: Erase(const T&x)
	{
		size_t i = h(x);
		for(auto it = v[i].begin(); it != v[i].end(); ++it)
		{
			if(it == x)
			{
				v[i].erase(it);
				n--;
				return 0;
			}
		}
		return -1;
	}

//----------------

void test1()
{
	Set<int> s;
	cout << "---int---" << endl;
	s.Insert(12,"87364");
	s.Insert(12,"87364");
	s.Insert(34,"87364");
	s.Insert(1458,"873645344");
	s.Insert(134588,"84547364");
	s.Insert(348587,"hggjkhjfg");
	s.Insert(3489,"kjghvkj");
	s.Insert(384832,"dgfcf");
	s.Insert(134588,"dgfcf");
	s.Insert(3556,"dgfcf");
	s.Search("jj"); 
	s.Search("kjghvkj");
	cout << s;
	s.Del("84547364");
	s.Del("999");
	cout << s;
	cout << s.Get_N() << endl;
	return;
}
void test2()
{
	Set<string> s;
	cout << "---string---" << endl;
	s.Insert("ddsfhgjdf","8736423");
	s.Insert("dfhdvkjkgjdf","8736423");
	s.Insert("dfhgdfdjdf","efsdf");
	s.Insert("dfhgsdfsfsddsfjdf","8sdfd3");
	s.Insert("dsdffsddsffhgjdf","8dfsg23");
	s.Insert("dfhgewwjdf","87reiu23");
	s.Insert("dfhgerwejdf","8eifhuhf3");
	s.Insert("dfhgeedjdf","wyeusd3");
	s.Insert("dfhgwkjghjjdf","ewhj3");
	s.Insert("dfhgjszzcdf","8736423");
	s.Insert("wkjhfkhfgddjhsd","87364");
	s.Insert("ejdjwesd","873");
	s.Insert("shdshjdshjjhd","834366674");
	cout << s;
	cout << "del: " << endl;
	s.Del("ddsfhgjdf");
	s.Del("efsdf");
	cout << s;
	s.Search("ddsfhgjdf");
	s.Search("ejdjwesd");
	s.Search("fkjhcj");
	s.Search("efsdf");
	s.Search("873");
	return ;
}
int main(){
	test1();
	test2();
	return 0;
}
