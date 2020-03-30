#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "heap.h"
using namespace std;

//prototype of structs and functions used in the code
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
struct nod2                    // struct to keep char and its code
{
	char ch;
	vector<char> ar;
};                    // struct to calculate char and its code
void code(vector<char> ca, node *pt, nod2 *a,int &i);         // programme that assign codes to variables
unsigned char tobyte(bool b[8]);                            // function to convert 8 bits into corrosponding char
void save(node *pt, ofstream & of);                                          // programme to save treee
void convert(node * ptr, ifstream &ii);             // save tree 
void clean();        // to delete a file temp
void levelOrderTraversal(node *ptr)
{
	if(!ptr)
	{
		return;
	}
	cout<<ptr->dat<<" ";
	levelOrderTraversal(ptr->left);
	levelOrderTraversal(ptr->right);
}

int main()
{

	heap<node *> heapobj;           // heap type is node *


	/****** Read data from file and finds the frequency of each character used in the file **********/
	int arra[256], k=0;
	for(int i=0; i<256; i++)
	{
		arra[i]=0;
	}

	string exp;
	ifstream in;
	ofstream out;

	in.open("input.txt");
	if(in.fail())
	{
		cout<<"file is not found "<<endl;
		exit(1);
	}

	out.open("temp.txt");
	getline(in,exp,'\0');    

	int l=exp.length();                                // length of string 

	for(int i=0; i<l ; i++)                           // frequency of each character in file
	{
		k=exp[i];
		arra[k]++;
	}

	/*********insertion of charcters with frequency into heap used in the file (using node)******/
	string ca;
	int totalCharUsed=0;
	// inserting node having character and frequency into heap
	for(int i=0; i<256; i++)
	{
		if(arra[i]!=0)
		{
			totalCharUsed++;                                    // count how many character are totally used in file  
			string s1;
			s1.push_back(i);
			node *tr=new node(s1);
			heapobj.Insert(arra[i],tr);                   // insertion of char with its frequency
		}
	} 

		heapobj.print();                    

		int var1=0, var2=0, var3=0;
		node *ptr1, *ptr2, *ptr3;

//in order to create tree 2 characters with max frequency are removed at at time and then merged
//at end of loop heap contains only one node which is root node of tree
		while(heapobj.size()>1)
		{
			heapobj.GetMin(var1,ptr1);   									  // getting minimum element from Heap
			heapobj.remove();												 // removing it from heap
			heapobj.GetMin(var2,ptr2);									// getting minimum element from Heap
			heapobj.remove();											   // removing it from heap
			ptr3=new node(ptr1->dat+ptr2->dat);					  // assigning data of both string and add it

			ptr3->left=ptr1;                           // pointing tree left side child
			ptr3->right=ptr2;			               // pointing tree right side child
			
			var3=var1+var2;                                       // adding two of them
			heapobj.Insert(var3,ptr3);
		}


/*********Traversal of tree created (located at first node of heap) and save the tree onto a file****/

		node *rot;
		int num;
		heapobj.GetMin(num,rot);                           // getting ptr of root of tree
		ofstream off;
		off.open("save.txt");
		save(rot,off);                             // saving a tree into text file
		off.close();
		cout<<endl;

		ifstream iiin;
		iiin.open("save.txt");
		heapobj.GetMin(num,rot);
		convert(rot,iiin);
		iiin.close();

		levelOrderTraversal(ptr3);
		

		vector<char> cod;						// vector array
		nod2 *ar2=new nod2[totalCharUsed];                // new dynamic struct to calculate code of alphabet and 

		node *p;
		int l1;
		heapobj.GetMin(l1,p);                     // telling us root pointer
		int i1=0;
		code(cod,p,ar2,i1);                // passing  array
		cout<<endl;

		// printing char and their codes by huffman
		for(int i=0; i<totalCharUsed; i++)
		{
			cout<<ar2[i].ch<<' '<<' ';
			for(int j=0;j<ar2[i].ar.size();j++)
				cout<<ar2[i].ar[j];
			cout<<endl;
		}

		heapobj.print();
	
		char che=0;
		int si=exp.length();
		string pla;
		for(int i=0; i<si; i++)
		{
			che=exp[i];
			for(int j=0; j<totalCharUsed; j++)
			{
				if(che==ar2[j].ch)
				{
					for(int k=0; k<ar2[j].ar.size(); k++)
					{
						out<<ar2[j].ar[k];	                  // printing codes in temp files
					}
				}
			}
		}

		out.close();                  
		string chek;
		ifstream inn;
		ofstream ouut;
//read tree and then assign binary code to each character 
		inn.open("temp.txt");
		ouut.open("output.txt");
		getline(inn,chek,'\0');


		bool flag[8];                               // bool array for conversion of bits to char
		for(int i=0; i<8; i++)
		flag[i]=0;

		int l11=chek.length();
		int k1=l11/8;
		int k2=l11%8;
		cout<<"  length "<<l11<<" "<<" mod  "<<k2<<"  divisor    "<<k1;
		cout<<endl;

		int remain=l11-k2;
		cout<<"remain "<<remain<<" ";

		int o=0;
/*******generation of binary code for character and then convert that binary code to a byte char using tobyte() function**********/
/*******and store that byte char onto output.txt used for keeping compressed data**********/
		while(o<l11-k2)                                 // reading form temp file and compressing
		{
			for(int lm=0; lm<8; lm++)
			{
				if(chek[o]=='0')
				{
					flag[lm]=false;
					o++;
				}
				else if(chek[o]=='1')
				{
					flag[lm]=true;
					o++;
		    	}
			}
			unsigned char vc=tobyte(flag);
			ouut<<vc;
		}

		for(int i=0; i<8; i++)
			flag[i]=false;


		//remaining 8 bits conversion into cmpress byte
		for(int i=0; i<8; i++)
		{
			if(remain<l11)                                            // if condition till the size of string
			{
				if(chek[remain]=='0')
				{
					flag[i]=true;
					remain++;
				}
				else if(chek[remain]=='1')
				{
					flag[i]=true;
					remain++;
				}
			}

			else
			{
				flag[i]=false;
			}
		}

			unsigned char vtotalCharUsed=tobyte(flag);
			//ouut<<vtotalCharUsed;

		ouut.close();

		atexit(clean);                        // to delete  temp file
	return 0;
}


/**********implementation of prototypes given above*******/
void code(vector<char> ca, node *pt, nod2 *a,int &i)         // programme that assign codes to variables
{
	if(pt->left==nullptr || pt->right==nullptr)
	{
		char c=pt->dat[0];
		a[i].ch=c;
		a[i].ar=ca;	
		i++;
		ca.pop_back();
		return;
	}
	ca.push_back('0');                         // if move toward left 
	code(ca,pt->left,a,i);
	ca.pop_back();
	ca.push_back('1');                        // if move towards right
	code(ca,pt->right,a,i);
}
unsigned char tobyte(bool b[8])                            // function to convert 8 bits into corrosponding char
{
	unsigned char c=0;
	for(int i=0; i<8; i++)
	{
		if(b[i])
			 c|=1<<i;
	}
	return c;
}
void save(node *pt, ofstream & of)                                          // programme to save treee
{
	if(pt==nullptr)
		return;
	of<<pt->dat<<'`';
	   save(pt->left,of);
	   save(pt->right,of);
}
void convert(node * ptr, ifstream &ii)             // save tree 
{
	string st;
	getline(ii,st,'`');
	if(st.length()!=1)
	{
		ptr=new node;
		ptr->dat=st;
		convert(ptr->left,ii);
		convert(ptr->right,ii);
	}
	else
	{
		return;
	}
}
void clean()        // to delete a file temp
{
    remove( "temp.txt" );
}