#include<string.h>
#include<string>
#include<iostream>
#include<vector>
#include<deque>
using namespace std;

// section 1
class CString{
	private:
		char * m_sBuffer;
	public:
		CString(const char * str){
			m_sBuffer = 0;

			if(0 == str) {
				m_sBuffer = new char[1];	    
				m_sBuffer[0] = '\0';
				return;
			}

			int iLen = strlen(str); 
			m_sBuffer = new char[iLen+1]; 
			strncpy(m_sBuffer, str, iLen); 
		}
		// copy constructor
		CString & operator=(const CString & str)
		{
			if(&str != this){
				if(m_sBuffer){
					delete m_sBuffer, m_sBuffer = 0;
				}

				int iLen = strlen(str.m_sBuffer);
				m_sBuffer = new char[iLen+1];
				strncpy(m_sBuffer, str.m_sBuffer, iLen); 
			} 

			return *this;
		}
		// show
		void show(void){
			cout << m_sBuffer << endl;
		}
};
class CStringTest{
	public:
		static void run(){
			CString * a = new CString("This is CString a");
			a->show(); 

			CString * b = new CString("Who I'm I ? ");
			b->show(); 

			*b = *a;
			b->show();
		}
};

// section 2
class CSingleton {
	private:
		static CSingleton * instance;
		CSingleton(){
			cout << "Constructing.." << endl;
		}

	public:
		static CSingleton * getInstance()
		{
			if(0 == instance) { 
				instance = new CSingleton();    
			}
			else {
				cout << "Already have instance" << endl;
			}

			return instance; 
		} 
		static void destroyInstance()
		{
			if(instance){
				delete instance;
				instance = 0;
			}
			cout << "Destroying.." << endl;
		}
};

CSingleton * CSingleton::instance = 0;

class CSingletonTest{
	public:
		static void run(){
			CSingleton *a = CSingleton::getInstance();
			CSingleton *b = CSingleton::getInstance(); 
			CSingleton::destroyInstance();
			CSingleton *c = CSingleton::getInstance(); 
		}
};

// section 3 
class CFinder{
	public:
		static int find(vector< vector<int> > array, int iRow, int iColumn, int iKey){
			int i = iColumn-1;
			while(i >= 0 && array[0][i] >= iKey) i--;

		}
};
class CFinderTest{
	public:
		static void run(){ 
			static int a[][4] = {
				1, 2, 8, 9,
				2, 4, 9, 12,
				4, 7, 10, 13,
				6, 8, 11, 15
			};
			vector< vector<int> > array(4);
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					array[i][j] = a[i][j];
				}
			}
		}
};

// section 6, 23, 39
class CBiTreeNode {
	public:
		int iElement;
		CBiTreeNode * lChild;
		CBiTreeNode * rChild;
};
class CBiTree{
	public:
		static CBiTreeNode * reConstructBiTree(const int * preOder, const int * inOder, int iLen)
		{
			if(!preOder || !inOder || !iLen) return 0;

			int i = 0; 
			while(preOder[0] != inOder[i]) i++;

			CBiTreeNode * root = new CBiTreeNode();
			root->iElement = preOder[0];
			root->lChild = reConstructBiTree(preOder+1, inOder, i);
			root->rChild = reConstructBiTree(preOder+i+1, inOder+i+1, iLen-i-1);

			return root;
		} 

		static void tranverse(const CBiTreeNode * root)
		{
			if(!root) 
			{
				return;
			}

			cout << root->iElement << '\t';
			tranverse(root->lChild);
			tranverse(root->rChild); 
		}

		static void tranverseInOrder(const CBiTreeNode * root)
		{
			if(!root) 
			{
				return;
			}

			tranverse(root->lChild);
			cout << root->iElement << '\t';
			tranverse(root->rChild); 
		}

		static void tranverseByLevel(CBiTreeNode * root)
		{
			if(!root) return;

			CBiTreeNode * p = root;
			deque<CBiTreeNode *> treeNodeDeque;
			treeNodeDeque.push_back(p);

			while(treeNodeDeque.size())
			{
				p = treeNodeDeque.front();
				treeNodeDeque.pop_front();

				cout << p->iElement << '\t';

				if(p->lChild) treeNodeDeque.push_back(p->lChild);
				if(p->rChild) treeNodeDeque.push_back(p->rChild);
			}

			cout << endl;
		}
};
class CBiTreeTest{
	public: 
		static void run()
		{
			int preOder[] = {
				1, 2, 4, 7, 3, 5, 6, 8,
			};

			int inOder[] = {
				1, 2, 4, 7, 3, 5, 6, 8,
			};

			CBiTreeNode * root = CBiTree::reConstructBiTree(preOder, inOder, 8);
			CBiTree::tranverse(root);
			cout << endl;
			CBiTree::tranverseInOrder(root);
			cout << endl;
			CBiTree::tranverseByLevel(root);
		}
};

// SortAlgrithm 
class CSort{
	public: 
		static int partition(vector<int> &array, const int iBegin, const int iEnd)
		{
			if(0 == array.size() || iBegin >= iEnd-1) return -1;

			int iKey = array[iBegin];
			int i, j; 
			for(i = iBegin+1, j = iEnd-1;;)
			{
				while(array[i] <= iKey) i++;
				while(array[j] >= iKey) j--;

				if(i >= j) break;

				int iTemp = array[i];
				array[i] = array[j];
				array[j] = iTemp;
			}

			array[iBegin] = array[i-1]; 
			array[i-1] = iKey;

			return i-1;
		}
		static void quickSort(vector<int> &array, const int iBegin, const int iEnd)
		{
			if(!array.size() || iBegin >= iEnd-1) return;

			int iPositon = partition(array, iBegin, iEnd); 
			quickSort(array, iBegin, iPositon);
			quickSort(array, iPositon+1, iEnd);
		}

};
class CSortTest{
	public:
		static void tranverse(vector<int> & array)
		{
			for(vector<int>::iterator iter = array.begin(); array.end() != iter; iter++)
			{
				cout << *iter << '\t';
			}
			cout << endl;
		}
		static void run()
		{
			int a[] = {
				6, 5, 7, 8, 3, 4, 1, 2, 9, 0,
			};
			vector<int> array(a, a+10);
			tranverse(array);
			CSort::quickSort(array, 0, array.size());
			tranverse(array);
		}
};

// section 12
class CNumberPrinter{
	public:
		static void print(const int iBegin, const int iEnd)
		{ 
			if(iBegin > iEnd) return;

			static vector<int> array(iEnd-iBegin);

			if(iBegin == iEnd)  
			{
				for(vector<int>::iterator iter = array.begin(); array.end() != iter; iter++)
				{
					cout << *iter;
				}
				cout << '\t'; 

				return;
			}

			for(int i = 0; i<10; i++)
			{
				array[iBegin] = i;
				print(iBegin+1, iEnd);
			}
		}
};
class CNumberPrinterTest{ 
	public:
		static void run()
		{
			CNumberPrinter::print(0, 3);
			cout << endl;
		}
};

// section 16, 37
class CListNode{
	public:
		int iElement;
		CListNode * next;
		CListNode(int iElement = -1, CListNode * next = 0) { this->iElement = iElement, this->next = next; }
};

class CList{
	public:
		static void reverseList(CListNode * head)
		{
			CListNode * newHead = 0; 
		}

		static CListNode * createList(int * array, int iLen)
		{
			if(!array || iLen <= 0) return 0;

			CListNode *head = 0, *pre = 0, *cur = 0;

			head = new CListNode(array[0]); 
			pre = head;

			for(int i = 1; i < iLen; i++)
			{
				cur = new CListNode(array[i]);
				pre->next = cur;

				pre = cur;
			}

			return head;
		}

		static void tranverse(CListNode * head)
		{
			if(!head) return;

			if(head)
			{
				cout << head->iElement << '\t';
				tranverse(head->next);
			}
		}

		static int findTheCross(CListNode * head_1, CListNode * head_2)
		{// use the system stack
			static int iCross = -1; 

			// push these node to stack
			if(head_1 && head_2) 
			  findTheCross(head_1->next, head_2->next);
			else if(head_1 && !head_2) 
			  findTheCross(head_1->next, head_2);
			else if(!head_1 && head_2) 
			  findTheCross(head_1, head_2->next);
			else if(!head_1 && !head_2) 
			  return iCross;

			// reversely check the commen node. the last is the first
			if(head_1->iElement == head_2->iElement) {
				iCross = head_1->iElement;
			}

			return iCross;
		}
};
class CListTest{
	public:
		static void run()
		{
			int array_1[] = {
				1, 2, 9, 4, 5, 6, 
			};
			CListNode * head_1 = CList::createList(array_1, 6);
			CList::tranverse(head_1);
			cout << endl;

			int array_2[] = {
				3, 4, 5, 6, 
			};
			CListNode * head_2 = CList::createList(array_2, 6);
			CList::tranverse(head_2);
			cout << endl;

			cout << CList::findTheCross(head_1, head_2) << endl;
		}

};

// ----------------------------------------------------------------
int main(int argc, char * argv[])
{
	CStringTest::run();
	CSingletonTest::run();
	CBiTreeTest::run();
	CSortTest::run();
	//CNumberPrinterTest::run();
	CListTest::run();
	return 0;
}
