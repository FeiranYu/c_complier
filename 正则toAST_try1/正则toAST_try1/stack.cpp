#include"AST.h"

node* getNodeEnd( node* Node)
{
	node* nodeNow = Node;
	while (nodeNow->isEndNode ==false)
	{
		nodeNow = nodeNow->Bridge1->nodeEnd;
	}
	return nodeNow;
}



void AstStack::push(AstNode* Node)
{
	index++;
	pNode[index] = Node;

}

AstNode* AstStack::pop()
{
	
	if (index > -1)
	{
		index--;
		return pNode[index + 1];
	}
	else
	{
		AstNode* ErrNode = new AstNode;
		ErrNode->child1 = nullptr;
		ErrNode->child2 = nullptr;
		ErrNode->token = ErrChar;

		return ErrNode;
	}
}

AstNode* AstStack::top()
{
	if (index > -1)
	{
		return pNode[index];
	}
	else
	{
		AstNode* ErrNode = new AstNode;
		ErrNode->child1 = nullptr;
		ErrNode->child2 = nullptr;
		ErrNode->token = ErrChar;

		return ErrNode;
	}
}

bool AstStack::isEmpty()
{
	if (index == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void NfaStack::push(char token)
{
	if (isGrammar(token))
	{
		node* NodeS = new node;
		node* NodeE = new node;
		bridge* Bridge = new bridge;

		Bridge->bridge_char = token;
		Bridge->nodeStart = NodeS;
		Bridge->nodeEnd = NodeE;
		
		NodeS->Bridge1 = Bridge;
		NodeE->isEndNode = true;
		push(NodeS);
	}
	if (isOpNode(token))
	{
		if (token == '+')
		{
			node* node1=pop();
			node* node2=pop();
			node* node1End;
			node* node2End;

			node1End = getNodeEnd(node1);
			node1End->isEndNode = false;
			bridge* Bridge = new bridge;

			Bridge->bridge_char = eChar;
			Bridge->nodeStart = node1End;
			Bridge->nodeEnd = node2;

			if (node1End->Bridge1 == NULL)
			{
				node1End->Bridge1 = Bridge;
			}
			else
			{
				bridge* temp = node1End->Bridge1;
				node1End->Bridge2 = temp;
				node1End->Bridge1 = Bridge;
			}
			node2End = getNodeEnd(node2);
			node2End->isEndNode = true;
			push(node1);
		}
		if (token == '*')
		{
			node* node1 = pop();
			node* node1End = getNodeEnd(node1);
			node* nodeSE = new node;

			bridge* Bridge1 = new bridge;
			bridge* Bridge2 = new bridge;

			Bridge1->bridge_char = eChar;
			Bridge1->nodeStart = nodeSE;
			Bridge1->nodeEnd = node1;

			Bridge2->bridge_char = eChar;
			
			Bridge2->nodeStart = node1End;
			Bridge2->nodeEnd = nodeSE;

			nodeSE->Bridge1 = Bridge1;
			node1End->Bridge1 = Bridge2;

			node1End->isEndNode = false;
			nodeSE->isEndNode = true;
			push(nodeSE);
		}
		if (token == '|')
		{
			node* nodeS = new node;
			node* nodeE = new node;
			node* node1 = pop();
			node* node2 = pop();
			node* node1End = getNodeEnd(node1);
			node* node2End = getNodeEnd(node2);

			bridge* Bridge1 = new bridge;
			bridge* Bridge2 = new bridge;
			bridge* Bridge3 = new bridge;
			bridge* Bridge4 = new bridge;

			Bridge1->bridge_char = eChar;
			Bridge1->nodeStart = nodeS;
			Bridge1->nodeEnd = node1;

			Bridge2->bridge_char = eChar;
			Bridge2->nodeStart = nodeS;
			Bridge2->nodeEnd = node2;

			Bridge3->bridge_char = eChar;
			Bridge3->nodeStart = node1End;
			Bridge3->nodeEnd = nodeE;

			Bridge4->bridge_char = eChar;
			Bridge4->nodeStart = node2End;
			Bridge4->nodeEnd = nodeE;

			nodeS->Bridge1 = Bridge1;
			nodeS->Bridge2 = Bridge2;

			node1End->Bridge1 = Bridge3;
			node2End->Bridge1 = Bridge4;

			node1End->isEndNode = false;
			node2End->isEndNode = false;

			nodeE->isEndNode = true;

			push(nodeS);
		}
	}
}


void NfaStack::push(node* Node)
{
	index++;
	pNode[index] = Node;
}

node* NfaStack::pop()
{
	if (index > -1)
	{
		index--;
		return pNode[index + 1];
	}
	else
	{
		node* ErrNode = new node;
		ErrNode->isErrNode = true;
		return ErrNode;
	}
}

bool NfaStack::isEmpty()
{
	if (index > -1)
		return false;
	else
		return true;
}