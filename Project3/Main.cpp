#include <iostream>
using namespace std;

/*
   Добавить в класс "Односвязный список" следующие функции :
	  удаление элемента по заданной позиции,
	  удаление последнего элемента,
	  поиск заданного элемента(функция возвращает позицию найденного элемента в случае успеха или NULL в случае неудачи).
*/
struct Element
{
	// Данные
	char data;
	// Адрес следующего элемента списка
	Element* Next;
};

// Односвязный список
class List
{
	// Адрес головного элемента списка
	Element* Head;
	// Адрес головного элемента списка
	Element* Tail;
	// Количество элементов списка
	int Count;

public:
	// Конструктор
	List();
	// Деструктор
	~List();

	// Добавление элемента в список
	// (Новый элемент становится последним)
	void Add(char data);

	// Удаление элемента списка
	// (Удаляется головной элемент)
	void Del();
	// Удаление всего списка
	void DelAll();
	void DelIndex(int index);
	// Распечатка содержимого списка
	// (Распечатка начинается с головного элемента)
	void Print();

	// Получение количества элементов, находящихся в списке
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

		// настройка связей
		NewNode->Next = temp->Next;
		temp->Next = NewNode;
	}

	void DelLast();
	int* Search(char data);

};

List::List()
{
	// Изначально список пуст
	Head = Tail = NULL;
	Count = 0;
}

List::~List()
{
	// Вызов функции удаления
	DelAll();
}

int List::GetCount()
{
	// Возвращаем количество элементов
	return Count;
}

void List::DelLast()
{
	// Если список пустой
	if (Head == NULL)
	{
		cout << "List is empty" << endl;
		return;
	}

	// Если в списке только один элемент
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = NULL;
		Count--; // Уменьшаем количество элементов
		return;
	}

	// Ищем предпоследний элемент
	Element* temp = Head;
	while (temp->Next != Tail)
	{
		temp = temp->Next;
	}

	// Удаляем последний элемент
	delete Tail;
	Tail = temp;
	Tail->Next = NULL;
	Count--; // Уменьшаем количество элементов
}

int* List::Search(char data)
{
	// Инициализация указателя для прохода по списку
	Element* temp = Head;
	// Позиция, которую будем возвращать
	int position = 1;

	// Проходим по списку
	while (temp != NULL)
	{
		// Если нашли элемент, возвращаем указатель на позицию
		if (temp->data == data) {
			return new int(position); // Возвращаем указатель на позицию
		}
		// Переходим к следующему элементу
		temp = temp->Next;
		position++;
	}

	// Если элемент не найден, возвращаем NULL
	return NULL;
}


void List::Add(char data)
{
	// создание нового элемента
	Element* temp = new Element;

	// заполнение данными
	temp->data = data;
	// следующий элемент отсутствует
	temp->Next = NULL;
	// новый элемент становится последним элементом списка
	// если он не первый добавленный
	if (Head != NULL) {
		Tail->Next = temp;
		Tail = temp;
	}
	// новый элемент становится единственным
	// если он первый добавленный
	else {
		Head = Tail = temp;
	}
}

void List::Del()
{
	// запоминаем адрес головного элемента
	Element* temp = Head;
	// перебрасываем голову на следующий элемент
	Head = Head->Next;
	// удаляем бывший головной элемент
	delete temp;
}

void List::DelAll()
{
	// Пока еще есть элементы
	while (Head != 0)
		// Удаляем элементы по одному
		Del();
}

void List::DelIndex(int index)
{

	// запоминаем адрес головного элемента
	Element* temp1 = Head;
	// Пока еще есть элементы
	while (temp1 != 0)
	{
		// Выводим данные
		++Count;
		// Переходим на следующий элемент
		temp1 = temp1->Next;
	}

	// Если список пустой или индекс некорректен
	if (Head == NULL || index < 1 || index > Count)
	{
		cout << "Invalid index" << endl << endl;
		return;
	}
	delete temp1;
	// Если нужно удалить первый элемент (голову списка)
	if (index == 1)
	{
		Element* temp = Head;
		Head = Head->Next;
		delete temp;
		Count--; // Уменьшаем количество элементов
		return;
	}

	// запоминаем адрес головного элемента
	Element* temp = Head;
	// Ищем элемент, предшествующий удаляемому
	for (int i = 1; i < index - 1; i++)
	{
		temp = temp->Next;
	}

	// Удаляем элемент
	Element* toDelete = temp->Next;
	temp->Next = toDelete->Next;

	// Если удаляем последний элемент, обновляем Tail
	if (toDelete == Tail)
	{
		Tail = temp;
	}

	delete toDelete;
	Count--; // Уменьшаем количество элементов
}

void List::Print()
{
	// запоминаем адрес головного элемента
	Element* temp = Head;
	// Пока еще есть элементы
	while (temp != 0)
	{
		// Выводим данные
		cout << temp->data << " ";
		// Переходим на следующий элемент
		temp = temp->Next;
	}

	cout << "\n\n";
}


// Тестовый пример
void main()
{
	// Создаем объект класса List
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

	// Ищем элемент 'C'
	int* pos = lst.Search('C');
	if (pos != NULL) {
		cout << "Element 'C' found at position: " << *pos << endl;
		delete pos; // Освобождаем память
	}
	else {
		cout << "Element 'C' not found" << endl;
	}

	// Ищем элемент 'Z'
	pos = lst.Search('Z');
	if (pos != NULL) {
		cout << "Element 'Z' found at position: " << *pos << endl;
		delete pos; // Освобождаем память
	}
	else {
		cout << "Element 'Z' not found" << endl;
	}
}

