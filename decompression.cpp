#include <iostream>
#include <fstream>
#include <vector>
#include<string>
using namespace std;
struct node
{
	string dat;
	node* left, *right;
	node()
	{
		dat='\0';
		left=right=nullptr;
	}
	node(string ke)         // constructor
	{
		dat=ke;
		left=right=nullptr;
	}
};
void convert(node * &ptr, ifstream &ii)             // save tree 
{
	string st;
	getline(ii,st,'`');
	if(st.length()>1)
	{
		ptr=new node;
		ptr->dat=st;
		convert(ptr->left,ii);
		convert(ptr->right,ii);
	}
	else if(st.length()==1)
	{
		ptr=new node;
		ptr->dat=st;
		return;
	}
}
union Byte
{
    unsigned char byte;
    struct
    {
        bool bit1 : 1;
        bool bit2 : 1;
        bool bit3 : 1;
        bool bit4 : 1;
        bool bit5 : 1;
        bool bit6 : 1;
        bool bit7 : 1;
        bool bit8 : 1;
    };
};
void ToByte(unsigned char b, ofstream & out)
{
	Byte a;
	a.byte=b;

	out<<a.bit1<<a.bit2<<a.bit3<<a.bit4<<a.bit5<<a.bit6<<a.bit7<<a.bit8;
}
void convert_ch(string s, node * ptr,node *ptr1, ofstream & ouut, int i)
{
	if(ptr->dat.length()==1)
	{
		i++;
		ouut<<ptr->dat;
		ptr=ptr1;
		//convert_ch(s,ptr,ptr1,ouut,i);
		return;
	}
	if(s[i]=='0')
	{
		i++;
		convert_ch(s,ptr->left,ptr1,ouut,i);
	}
	else if(s[i]=='1')
	{
		i++;
	convert_ch(s,ptr->right,ptr1,ouut,i);
	}
}
int main()
{
	ifstream in;
	ofstream out;
	in.open("save.txt");
	node *pt=nullptr;
	convert(pt,in);

	ifstream inn;
	inn.open("output.txt");
	out.open("temp1.txt");
	string get;
	getline(inn,get,'\0');
	int len=get.length();
	for(int i=0; i<len; i++)
	{
	   ToByte(get[i],out);
	}
	out.close();

	ifstream inni;
	inni.open("temp1.txt");
	ofstream oout;
	oout.open("decompress.txt");
	

	vector<int> v;

	string get1;
	getline(inni,get1,'\0');
	cout<<get1;
	int len1=0;
   len1=get1.length();

   cout<<"                            "<<len1<<"      ";

	int c1=0;

	node *ptr=pt;
	node *ptr1=pt;

	while(c1<=len1-1)
	{
		if(get1[c1]=='0')
		{
			c1++;
			ptr1=ptr1->left;
			
		}
		else if(get1[c1]=='1')
		{
			c1++;
			ptr1=ptr1->right;
		}

		if(ptr1->dat.length()==1)
		{
			oout<<ptr1->dat;
			ptr1=ptr;
		}

	}
	return 0;
}