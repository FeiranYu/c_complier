#pragma once
#include<iostream>

using namespace std;
const char ErrChar = 254;
const char cat = '+';


struct node
{
	node* child1;
	node* child2;
	char token;
};


class Stack
{
public:
	void push(node *Node);
	node* pop();
	node* top();
private:
	int index;
	node* pNode[100];
};



char Lex(string& str, int& now);