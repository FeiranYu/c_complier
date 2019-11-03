#include"AST.h"


bool NodeList::Add(node* Node)
{
	//判断是否有重复的
	for (int i = 0; i <= index; i++)
	{
		if (Node == pNode[i])
		{
			return false;
		}
	}

	index++;
	pNode[index] = Node;
	return true;
}

void NodeList::flush()
{
	index = -1;
}

node* NodeList::getNode(int index)
{
	return pNode[index];
}

void NodeList::show()
{
	for (int i = 0; i <= index; i++)
	{
		cout << pNode[i] << endl;
	}
}

int NodeList::Length()
{
	int length=0;
	for (; pNode[length] != NULL; length++) {}
	return length;
}

void BridgeList::Add(bridge* Bridge)
{
	index++;
	pBridge[index] = Bridge;
}

int BridgeList::Length()
{
	int length = 0;
	for (; pBridge[length] != NULL; length++) {}
	return length;
}

bridge* BridgeList::getBridge(int index)
{
	return pBridge[index];
}

void BridgeList::show()
{
	for (int i = 0; pBridge[i] != NULL; i++)
	{
		cout << pBridge[i]->bridge_char << endl;
	}
}


NodeList validNodeList;

void FindNoChange(node* Node,bool isValidInput)
{

	//先遍历整个NFA有向图

	//如果满足有效状态就输出
	if (isValidInput)
	{
		//为了防止出现环路死循环，每次查下之前的validNodeList，看下有没有重复的
		int validNodeListSum = validNodeList.Length();
		for (int i = 0; i < validNodeListSum; i++)
		{
			node* nodeNow = validNodeList.getNode(i);
			if (nodeNow == Node)
			{
				return;
			}
		}

		validNodeList.Add(Node);
	}
	if (Node->isEndNode &&!isValidInput)
	{
		validNodeList.Add(Node);
		return;
	}
	
	if (Node->Bridge1 != NULL)
	{
		if (Node->Bridge1->bridge_char != eChar)
		{
			cout << Node->Bridge1->bridge_char << endl;
			isValidInput = 1;
		}
		else
		{
			isValidInput = 0;
		}
		FindNoChange(Node->Bridge1->nodeEnd,isValidInput);
	}
	if (Node->Bridge2 != NULL)
	{
		if (Node->Bridge2->bridge_char != eChar)
		{
			cout << Node->Bridge2->bridge_char << endl;
			isValidInput = 1;
		}
		else
		{
			isValidInput = 0;
		}
		FindNoChange(Node->Bridge2->nodeEnd,isValidInput);
	}
}

void FindBridgeNode(node* Node,NodeList *nodeList, BridgeList* bridgeList)
{
	nodeList->Add(Node);
	if (Node->isEndNode)
	{
		node* ValidNode = nodeList->getNode(0);
		ValidNode->isEndNode = true;
	}
	if (Node->Bridge1!=NULL)
	{
		if (Node->Bridge1->bridge_char == eChar)
		{
			nodeList->Add(Node->Bridge1->nodeEnd);
			FindBridgeNode(Node->Bridge1->nodeEnd, nodeList, bridgeList);
		}
		else
		{
			bridgeList->Add(Node->Bridge1);
		}
		
	}
	if (Node->Bridge2!=NULL)
	{
		if (Node->Bridge2->bridge_char == eChar)
		{
			nodeList->Add(Node->Bridge2->nodeEnd);
			FindBridgeNode(Node->Bridge2->nodeEnd, nodeList,bridgeList);
		}
		else
		{
			bridgeList->Add(Node->Bridge2);
		}
		
	}
}
