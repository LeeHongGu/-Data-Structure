#pragma once

class Node
{
friend class Graph;
private:
	int data;
	Node* link;
	
public:
	Node() { }
	~Node() { }
	Node(int vertexNumber, Node* next)
	{ 
		this -> data = vertexNumber;
		this -> link = next;
	}

};