#include <iostream>
using namespace std;

/*
   �������� � ����� "����������� ������" ��������� ������� :
	  �������� �������� �� �������� �������,
	  �������� ���������� ��������,
	  ����� ��������� ��������(������� ���������� ������� ���������� �������� � ������ ������ ��� NULL � ������ �������).
*/
struct Element
{
	// ������
	char data;
	// ����� ���������� �������� ������
	Element* Next;
};

// ����������� ������
class List
{
	// ����� ��������� �������� ������
	Element* Head;
	// ����� ��������� �������� ������
	Element* Tail;
	// ���������� ��������� ������
	int Count;

public:
	// �����������
	List();
	// ����������
	~List();

	// ���������� �������� � ������
	// (����� ������� ���������� ���������)
	void Add(char data);

	// �������� �������� ������
	// (��������� �������� �������)
	void Del();
	// �������� ����� ������
	void DelAll();
	void DelIndex(int index);
	// ���������� ����������� ������
	// (���������� ���������� � ��������� ��������)
	void Print();

	// ��������� ���������� ���������, ����������� � ������
	int GetCount();

	void AddIndex(char data, int index)// Z, 2
	{
		Element* temp = Head;
		int i = 1;
		while (i < index)
		{
			temp = temp->Next;
			i++;
		}
		Element* NewNode = new Element;
		NewNode->data = data;

		// ��������� ������
		NewNode->Next = temp->Next;
		temp->Next = NewNode;
	}

	void DelLast();
	int* Search(char data);

};

List::List()
{
	// ���������� ������ ����
	Head = Tail = NULL;
	Count = 0;
}

List::~List()
{
	// ����� ������� ��������
	DelAll();
}

int List::GetCount()
{
	// ���������� ���������� ���������
	return Count;
}

void List::DelLast()
{
	// ���� ������ ������
	if (Head == NULL)
	{
		cout << "List is empty" << endl;
		return;
	}

	// ���� � ������ ������ ���� �������
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = NULL;
		Count--; // ��������� ���������� ���������
		return;
	}

	// ���� ������������� �������
	Element* temp = Head;
	while (temp->Next != Tail)
	{
		temp = temp->Next;
	}

	// ������� ��������� �������
	delete Tail;
	Tail = temp;
	Tail->Next = NULL;
	Count--; // ��������� ���������� ���������
}

int* List::Search(char data)
{
	// ������������� ��������� ��� ������� �� ������
	Element* temp = Head;
	// �������, ������� ����� ����������
	int position = 1;

	// �������� �� ������
	while (temp != NULL)
	{
		// ���� ����� �������, ���������� ��������� �� �������
		if (temp->data == data) {
			return new int(position); // ���������� ��������� �� �������
		}
		// ��������� � ���������� ��������
		temp = temp->Next;
		position++;
	}

	// ���� ������� �� ������, ���������� NULL
	return NULL;
}


void List::Add(char data)
{
	// �������� ������ ��������
	Element* temp = new Element;

	// ���������� �������
	temp->data = data;
	// ��������� ������� �����������
	temp->Next = NULL;
	// ����� ������� ���������� ��������� ��������� ������
	// ���� �� �� ������ �����������
	if (Head != NULL) {
		Tail->Next = temp;
		Tail = temp;
	}
	// ����� ������� ���������� ������������
	// ���� �� ������ �����������
	else {
		Head = Tail = temp;
	}
}

void List::Del()
{
	// ���������� ����� ��������� ��������
	Element* temp = Head;
	// ������������� ������ �� ��������� �������
	Head = Head->Next;
	// ������� ������ �������� �������
	delete temp;
}

void List::DelAll()
{
	// ���� ��� ���� ��������
	while (Head != 0)
		// ������� �������� �� ������
		Del();
}

void List::DelIndex(int index)
{

	// ���������� ����� ��������� ��������
	Element* temp1 = Head;
	// ���� ��� ���� ��������
	while (temp1 != 0)
	{
		// ������� ������
		++Count;
		// ��������� �� ��������� �������
		temp1 = temp1->Next;
	}

	// ���� ������ ������ ��� ������ �����������
	if (Head == NULL || index < 1 || index > Count)
	{
		cout << "Invalid index" << endl << endl;
		return;
	}
	delete temp1;
	// ���� ����� ������� ������ ������� (������ ������)
	if (index == 1)
	{
		Element* temp = Head;
		Head = Head->Next;
		delete temp;
		Count--; // ��������� ���������� ���������
		return;
	}

	// ���������� ����� ��������� ��������
	Element* temp = Head;
	// ���� �������, �������������� ����������
	for (int i = 1; i < index - 1; i++)
	{
		temp = temp->Next;
	}

	// ������� �������
	Element* toDelete = temp->Next;
	temp->Next = toDelete->Next;

	// ���� ������� ��������� �������, ��������� Tail
	if (toDelete == Tail)
	{
		Tail = temp;
	}

	delete toDelete;
	Count--; // ��������� ���������� ���������
}

void List::Print()
{
	// ���������� ����� ��������� ��������
	Element* temp = Head;
	// ���� ��� ���� ��������
	while (temp != 0)
	{
		// ������� ������
		cout << temp->data << " ";
		// ��������� �� ��������� �������
		temp = temp->Next;
	}

	cout << "\n\n";
}


// �������� ������
void main()
{
	// ������� ������ ������ List
	List lst;
	lst.Add('A');
	lst.Add('B');
	lst.Add('C');
	lst.Add('D');
	lst.Add('E');
	lst.Add('F');
	lst.Print();

	lst.AddIndex('Z', 2);
	lst.Print();

	lst.DelIndex(5);
	lst.Print();

	lst.DelLast();
	lst.Print();

	// ���� ������� 'C'
	int* pos = lst.Search('C');
	if (pos != NULL) {
		cout << "Element 'C' found at position: " << *pos << endl;
		delete pos; // ����������� ������
	}
	else {
		cout << "Element 'C' not found" << endl;
	}

	// ���� ������� 'Z'
	pos = lst.Search('Z');
	if (pos != NULL) {
		cout << "Element 'Z' found at position: " << *pos << endl;
		delete pos; // ����������� ������
	}
	else {
		cout << "Element 'Z' not found" << endl;
	}
}

