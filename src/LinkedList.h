#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream> 
#include <string>   
#include <vector>       

struct Node
{
	std::vector<std::pair<std::string, std::string>> data;
	int intforsort;
	std::string stringforsort;
	Node* next;
	Node* prev;
	int sortkey;
	std::string sortkeyS;
	int id;
};

class LinkedList
{
private:
	Node* head;
	Node* tail;
public:
	// default constructor       
	LinkedList() : head(nullptr), tail(nullptr) { }
	// Destroys all the dynamically allocated memory       
	// in the list.       
	~LinkedList();
	bool deleteNode(int i);
	// Inserts val at the rear of the list       
	void insertToRear(std::vector<std::pair<std::string, std::string>> data);
	// Sets item to the value at position i stin this       
	// LinkedList and return true, returns false if        
	// there is no element i 
	std::vector<std::pair<std::string, std::string>> get(int i) const;
	// sorts the linked list in ascending order
	LinkedList* sortList(std::string column_name, int option);
	// Returns the number of items in the Linked List.       
	int size() const;
	// Add Node to front
	void insertToFront(std::vector<std::pair<std::string, std::string>> data){}; //Be able to insert in front

	void printList();


	void set(std::vector<std::pair<std::string, std::string>> v, int i);

};
#endif
