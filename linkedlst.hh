#ifndef LINKEDLIST_HH
#define LINKEDLIST_HH
#include <iostream>
using namespace std;

class LinkedListElem
{
public:
    int Value;
    LinkedListElem *next;
};

class LinkedList
{
public:
    LinkedListElem *Head;
    LinkedList()
    {
        Head = nullptr;
    }
    void addElem(int value)
    {
        LinkedListElem *New = new LinkedListElem;
        New->Value = value;
        New->next = nullptr;

        if (Head == nullptr)
        {
            Head = New;
        }
        else
        {
            LinkedListElem *current = Head;
            // Przechodzenie do ostatniego węzła na liście
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = New;
        }
    }
    LinkedListElem *&searchList(int value)
    {
        LinkedListElem *tmp = Head;
        // przeszukujemy liste w poszukiwaniu konkretnego wierzcholka do momentu kiedy nie ma juz nastepnego elementu
        while (tmp != nullptr) // sprawdzamy czy adres to nie nullptr - brak elementu - bo bylby segmentation fault inaczej
        {
            if (tmp->Value != value) // sprawdzamy czy poszukiwana wartosc
            {
                tmp = tmp->next;
            }
            else // jezeli tak to zwracamy adres znalezionego elementu
            {
                return tmp; // zwracamy adres elementu ktory ma poszukiwana wartosc
            }
        }
        tmp = nullptr;
        return tmp;
    }
    void removeElem(int Value)
    {
        LinkedListElem *SearchedElemPointer;
        LinkedListElem *NextElemPointer;
        LinkedListElem *PreviousElemPointer = Head; // adres poprzedniego elementu deklarujemy na poczatek listy
        SearchedElemPointer = searchList(Value);    // przypisujemy adres poszukiwanego elemetnu
        if (SearchedElemPointer != nullptr)
        {
            NextElemPointer = SearchedElemPointer->next; // bierzemy adres kolejnego elementu
            if (Head != SearchedElemPointer)             // sprawdzamy czy 1 element to juz poszukiwany - jak tak to do Head musimy przypisac nastepny - nullptr
            {
                while (PreviousElemPointer->next != SearchedElemPointer) // szukamy adresu poprzedniego elementu wzgledem poszukiwanego
                {
                    PreviousElemPointer = PreviousElemPointer->next;
                }
                PreviousElemPointer->next = NextElemPointer; // do adresu poprzedniego elementu - przypisujemy adres nastepnego czyli tak zeby pominac usuwany element
                delete SearchedElemPointer;                  // usuwamy element
            }
            else
            {
                Head = NextElemPointer;
                delete SearchedElemPointer;
            }
        }
    }
};
#endif