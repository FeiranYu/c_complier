#include"AST.h"

AstStack OpStack;
AstStack GrammarStack;
NfaStack NFAStack;

string str;
int now = 0;


int main()
{
	cout << "Input an Regular Expression: "; 
	getline(cin, str);


	//-----------------------------------����AST[��ʼ]-----------------------------------------
	AstNode* ZeroNode = new AstNode;
	ZeroNode->child1 = nullptr;
	ZeroNode->child2 = nullptr;
	ZeroNode->token = '\0';
	OpStack.push(ZeroNode);


	AstNode* Node = getNode(str, now);			//��ȡһ��node
	if (Node->token == ErrChar)
	{
		exit(233);
	}

	while (!OpStack.isEmpty())
	{
		if (isOpNode(Node))
		{
			//cout << "top " << OpStack.top()->token << " Node " << Node->token << endl;
			//cout << "Priority "<< comparePriority(OpStack.top(), Node) << endl;
			if (comparePriority(OpStack.top(),Node) =='<')
			{
				//cout << "OpStack push " << endl;
				OpStack.push(Node);
				if (now < str.length())
				{
					Node = getNode(str, now);			//��ȡһ��node
				}
				else {
					Node = new AstNode;
					Node->token = '\0';
				}
			}
			else if (comparePriority(OpStack.top(), Node) == '>')
			{
				//cout << "OpStack cal " << endl;
				AstNode* op = OpStack.pop();
				if (op->token == ErrChar)
				{
					break;
				}
				if (op->token == '*')	//����һԪ�����
				{
					AstNode* grammar1 = GrammarStack.pop();
					GrammarStack.push(makeNode(op, grammar1));
				}
				else {			//���ڶ�Ԫ�����
					AstNode* grammar1 = GrammarStack.pop();
					AstNode* grammar2 = GrammarStack.pop();
					GrammarStack.push(makeNode2(op, grammar2, grammar1));
				}

			}
			else if (comparePriority(OpStack.top(), Node) == '=')
			{
				OpStack.pop();
				//cout << "OpStack pop " << endl;
				if (now < str.length())
				{
					Node = getNode(str, now);			//��ȡһ��node

				}
				else {
					Node = new AstNode;
					Node->token = '\0';
				}
			}
		}
		else if (isGrammar(Node))
		{
			//cout << Node->token << endl;
			GrammarStack.push(Node);
			if (now < str.length())
			{
				Node = getNode(str, now);			//��ȡһ��node

			}
			else {
				Node = new AstNode;
				Node->token = '\0';
			}
		}
	}

	AstNode* finalNode = GrammarStack.pop();
	int step = 0;
	int deep = 0;
	int DrawWidth = 100;
	DrawTree(finalNode,deep, step, DrawWidth/2, DrawWidth/2);
	Draw();


	


	//--------------------------------����AST[����]---------------------------


	//--------------------------------AST����NFA[��ʼ]------------------------
	int nodeSum = 0;
	for (; TokenRoad[nodeSum] != '\0'; nodeSum++)
	{
		
	}

	for (int i = nodeSum-1; i >=0; i--)
	{
		NFAStack.push(TokenRoad[i]);
	}


	//--------------------------------AST����NFA[����]------------------------


	//--------------------------------eNFA����NFA[��ʼ]-----------------------
	node* eNFAnode = NFAStack.pop();
	
	FindNoChange(eNFAnode, 1);
	cout << endl;
	validNodeList.show();

	cout << endl;
	


	int validNodeSum = validNodeList.Length();	//������ĸ���
	int findBridgeNodeIndexNow = 0;

	//��������ָ���������ֱ��e�հ��Ľ��ͱ�
	NodeList* pNodeList[100];
	BridgeList* pBridgeList[100];

	for (; findBridgeNodeIndexNow < validNodeSum; findBridgeNodeIndexNow++)
	{
		NodeList* nodelist = new NodeList;
		BridgeList* bridgeList = new BridgeList;
		node* findBridgeNodeNow = validNodeList.getNode(findBridgeNodeIndexNow);
		cout << "work now node" << endl;
		cout << findBridgeNodeNow << endl;
		FindBridgeNode(findBridgeNodeNow, nodelist,bridgeList);

		cout << "find all equal node" << endl;
		nodelist->show();
		cout << "find all bridge" << endl;
		bridgeList->show();

		for (int i = 0; i < bridgeList->Length(); i++)
		{
			bridge* NewBridge = new bridge;
			bridge* OldBridge = bridgeList->getBridge(i);
			NewBridge->bridge_char = OldBridge->bridge_char;
			NewBridge->nodeEnd = OldBridge->nodeEnd;
			NewBridge->nodeStart = findBridgeNodeNow;

			findBridgeNodeNow->BridgeIndex++;
			findBridgeNodeNow->BridgeList[findBridgeNodeNow->BridgeIndex] = NewBridge;
		}

		pNodeList[findBridgeNodeIndexNow] = nodelist;
		pBridgeList[findBridgeNodeIndexNow] = bridgeList;
	}

	//��e�հ����źͽ�����ɾ��
	for (int i = 0; i < validNodeSum; i++)
	{
		NodeList* nodeList = pNodeList[i];
		BridgeList* bridgeList = pBridgeList[i];
		int nodeListLength = nodeList->Length();
		int bridgeListLength = bridgeList->Length();

		for (int j = 1; j < nodeListLength; j++)
		{
			node* Node = nodeList->getNode(j);
			if (Node->isErrNode == false&&Node->isEndNode==false)
			{
				delete Node;
			}

		}
		for (int j = 0; j < bridgeListLength;j++)
		{
			bridge* Bridge = bridgeList->getBridge(j);

			if (isGrammar(Bridge->bridge_char) || isOpNode(Bridge->bridge_char))
			{
				delete Bridge;
			}

		}
		node* NFANodeNow = validNodeList.getNode(i);

		//���Bridge1��Bridge2����������eNFA���ţ��Ѿ�����NFA������Ҫ��
		NFANodeNow->Bridge1 = NULL;
		NFANodeNow->Bridge2 = NULL;
	}
	
	
	//--------------------------------eNFA����NFA[����]-----------------------
	

	return 0;
}