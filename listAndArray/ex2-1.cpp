/*编写代码，移除未排序列表中的重复节点*/

// 思考1：考虑用hash表记录已经出现过的节点
//，如果当前节点已经出现过，则删除，时间复杂度O(N),空间复杂度O(N)

// 思考2：使用两个指针p1和p2，p2负责查找和
//p1相同的节点，并删除，直到p1达到最后一个节点，时间复杂度O(n2),空间复杂度O(1)

#include <iostream>
#include <map>
using namespace std;

struct LNode
{
	int data;
	LNode *next;
};

class List
{
public:	
	List();
	void appendToTail(int data);
	void insertToHead(int data);
	void print();
	void deleteNode(int data);
	void deleteNode(LNode *p);
	void clearNodes();
	void removeDupNode();
	void removeDupNodeWithHash();

	LNode *findBackKthNod(int k);
	LNode *findBackKthNod_recur(int k);

	List splitByX(int x);
	List splitByX_withOldNode(int x);
	LNode *getLoopStart();

	LNode *getHead();
	LNode *getTail();
	~List();
	/* data */
private:
	LNode *head;
	LNode *tail;
};

List::List()
{
	head = new LNode;
	head->next = NULL;
	tail = head;
}

LNode* List::getHead()
{
	return head;
}

LNode* List::getTail()
{
	return tail;
}

void List::appendToTail(int data)
{
	LNode *p = new LNode;
	p->data = data;
	p->next = NULL;
	if (head == tail)
	{
		head->next = p;
	}
	else
	{
		tail->next = p;
	}
	tail = p; // update the location of tail
}

void List::insertToHead(int data)
{
	LNode *p = new LNode;
	p->data = data;
	p->next = NULL;

	if (head == tail)
	{
		tail = p; // update the location of the tail when the node is first node
	}
	p->next = head->next;
	head->next = p;
}

void List::print()
{
	if (head == tail)
	{
		cout << "the List is empty!" <<endl;
		return;
	}

	LNode *p = head->next;
	while(p != NULL)
	{
		cout << p->data << '\t';
		p = p->next;
	}
	cout << endl;
}

void List::deleteNode(int data)
{
	if (head == tail)
	{
		cout << "the list is empty!" << endl;
		return;
	}
	LNode *pre = head;
	while(pre->next != NULL)
	{
		if (pre->next->data == data)
		{
			pre->next = pre->next->next;
			if (pre->next == NULL) // if the node by deleted is the last one ,update the tail
			{
				tail = pre;
			}
		}
		pre = pre->next;
	}
}

void List::deleteNode(LNode *p)
{
	LNode *nx = p->next;
	while(nx != NULL)
	{
		// when dealing with the last node ,notice to update the tail
		if (nx->next == NULL)
		{
			tail = p;
		}
		// simliar to the delete of vector
		p->data = nx->data;
		p = nx;
		nx = nx->next;
	}
	// release the memory handly
	LNode *temp = p;
	delete temp;
	// repair the linklist
	tail->next = NULL;
}

void List::clearNodes()
{
	if (head == tail)
	{
		return;
	}
	LNode *pre = head;
	while(pre->next != NULL)
	{
		LNode *temp = pre->next;
		pre->next = pre->next->next;
		delete temp;
	}
	tail = head;
}

List::~List()
{

}

//2-1 
void List::removeDupNode()
{
	if (head == tail)
	{
		cout << "the linklist is empty!" <<endl;
		return;
	}

	LNode *p1 = head->next;
	LNode *p2;
	while(p1->next != NULL)
	{
		p2 = p1; // update the p2
		while(p2->next != NULL)
		{
			if (p1->data == p2->next->data)
			{
				LNode *temp = p2->next;
				p2->next = p2->next->next; // delete the p2->next node, so move p2 to the next
				delete temp;
				if (p2->next == NULL)
				{
					tail = p2;
				}
			}
			else
			{
				//the p2 will move to the next node
				p2 = p2->next;
			}
		}
		p1 = p1->next; // update the p1
	}
}

//2-1: use the hash table to hold the nowable node
void List::removeDupNodeWithHash()
{
	if (head == tail)
	{
		cout << "the linklist is empty!" <<endl;
		return;
	}

	map<int, bool> nodetable;
	LNode *p = head->next;
	LNode *pre = NULL;
	while(p != NULL)
	{
		if (nodetable[p->data])
		{
			LNode *temp = p;
			pre->next = p->next;
			delete temp;
		}
		else
		{
			nodetable[p->data] = true;
			pre = p;
		}
		p = p->next;
	}
}

//2-2: find the back kth node in single linklist
// example: 7->9->6->8->5->3
// the 1th is '3' and the 6th is '7'
// notice the first is 0th or 1th
LNode* List::findBackKthNod(int k)
{
	if (head == tail)
	{
		cout << "the linklist is empty!" <<endl;
		return NULL;
	}
	if (k < 1)
	{
		cout << "the k is meaningless value" <<endl;
	}

	LNode *fast = head->next;
	LNode *slow = head->next;

	for (int i = 1; i <= k; ++i)
	{
		if (fast == NULL) // k > length
		{
			//cout << "k > length" <<endl;
			return NULL;
		}
		fast = fast->next;
	}

	while(fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}

LNode* nToLast(LNode *p, int k, int &i)
{
	if (p->next == NULL)
	{
		// the tail node is the 1th from last
		return NULL;
	}
	LNode *nd = nToLast(p->next,k,i);
	i += 1;
	if (i == k)
	{
		return p;
	}
	return nd;
}

LNode* List::findBackKthNod_recur(int k)
{
	if (head == tail)
	{
		cout << "the linklist is empty!" <<endl;
		return NULL;
	}
	if (k < 1)
	{
		cout << "the k is meaningless value" <<endl;
		return NULL;
	}
	LNode *p = head->next;
	int i=1;
	return nToLast(p,k,i);
}

/*
这个方法，是重新建立一个链表，遇到比x小的则头插添加到新链表；否则用尾插法添加到新链表
如果题目限定只能用原来链表中的节点，则需要重新考虑
*/
List List::splitByX(int x)
{
	List newlist;
	LNode *p = head->next;
	LNode *temp;

	while(p != NULL)
	{
		if (p->data < x)
		{
			// when p->data is little than x, then insert it to the new list from head
			newlist.insertToHead(p->data);
		}
		else
		{
			// when p->data is equal or bigger than x, then add it to the new list from tail
			newlist.appendToTail(p->data);
		}
		// release the old node step by step
		temp = p;
		delete temp;
		p = p->next;
	}

	return newlist;
}

//分割链表，利用原来的节点构建新链表
List List::splitByX_withOldNode(int x)
{
	List newlist;
	LNode *before = NULL;
	LNode *before_tail = NULL;
	LNode *after = NULL;
	LNode *after_tail = NULL;

	LNode *p = head->next;
	LNode *temp;

	while(p != NULL)
	{
		temp = p->next; // backend the link

		p->next = NULL;
		if (p->data < x)
		{
			if (before == NULL) //first node
			{
				before = p;
				before_tail = before;
			}
			else
			{
				before_tail->next = p;
				before_tail = p;
			}
		}
		else
		{
			if (after == NULL)
			{
				after = p;
				after_tail = after;
			}
			else
			{
				after_tail->next = p;
				after_tail = p;
			}
		}
		p = temp;
	}

	if (before == NULL)
	{
		//cout << "****" << endl;
		newlist.head = after;
		newlist.tail = after_tail;
		return newlist;
	}

	before_tail->next = after;
	newlist.head->next = before;
	newlist.tail = after_tail;
	return newlist;
}

//2-6:给定一个有环链表，实现一个算法返回环路的开头结点。
//有环链表的定义：在链表中的某个结点的next元素指向在它前面出现的结点，则表明该链表存在环路
//示例：
//输入：1->2->3->4->5->3
//输出：3
LNode* List::getLoopStart()
{
	LNode *slow,*fast;
	slow = fast = head->next;

	while(fast != NULL && fast->next !=NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			// the collisionNode and the head are all k step from the loopstart
			break;
		}
	}

	if (fast == NULL || fast->next == NULL)
	{
		return NULL;
	}

	slow = head->next;
	while(slow != fast)
	{
		slow = slow->next;
		fast = fast->next;
		if (slow == fast)
		{
			break;
		}
	}

	return slow;
}

/* test functions */
void getLoopStart_test()
{
	List l;
	l.appendToTail(1);
	l.appendToTail(2);
	l.appendToTail(3);
	LNode *temp = l.getTail();
	l.appendToTail(4);
	l.appendToTail(5);
	l.getTail()->next = temp;

	LNode *loopStart = l.getLoopStart();
	if (loopStart != NULL)
	{
		cout << loopStart->data << endl;	
	}
	else
	{
		cout << "the linklist does not have loop" <<endl;
	}
}

int main(int argc, char const *argv[])
{
	/*
	List l1;
	l1.appendToTail(8);
	l1.appendToTail(5);
	l1.appendToTail(3);
	//l1.print();
	l1.insertToHead(6);
	l1.insertToHead(9);
	//l1.deleteNode(4);
	l1.insertToHead(7);
	l1.print();
	//l1.clearNodes();
	//l1.removeDupNodeWithHash();
	LNode *knode = l1.findBackKthNod_recur(4);
	if (knode != NULL)
	{
		cout << knode->data <<endl;
	}
	//l1.deleteNode(knode);

	List newlist = l1.splitByX_withOldNode(7);
	newlist.print();
	//l1.print();
	*/
	getLoopStart_test();
	return 0;
}
