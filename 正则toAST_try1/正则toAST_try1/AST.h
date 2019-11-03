#pragma once
#include<iostream>
#include<string>


using namespace std;


//--------------------------正则到AST--------------------------------------
const char ErrChar = 254;
const char cat = '+';

struct AstNode
{
	AstNode* child1=nullptr;
	AstNode* child2=nullptr;
	char token;
};


class AstStack
{
public:
	void push(AstNode* Node);
	AstStack() { index = -1; };
	AstNode* pop();
	AstNode* top();
	bool isEmpty();
private:
	int index;
	AstNode* pNode[100] = { NULL };
};


char Lex(string& str, int& now);
AstNode* getNode(string& str, int& now);

bool isOpNode(const AstNode* Node);
bool isOpNode(const char Char);
bool isGrammar(const AstNode* Node);
bool isGrammar(const char Char);

int getPriority(const AstNode* Node);
AstNode* makeNode2(AstNode* father, AstNode* son1, AstNode* son2);
AstNode* makeNode(AstNode* father, AstNode* son);
char comparePriority(const AstNode* nodeA, const AstNode* nodeB);

const int OP_SUM = 6;
const char Priority[OP_SUM][OP_SUM] = {		//运算符优先等级 [栈顶][当前]

			/*     |      +     *     (     )    \0   */
	/*   |   */   '>',   '<',  '<',  '<',  '>',  '>',
	/*   +   */   '>',   '>',  '<',  '<',  '>',  '>',
	/*   *   */   '>',   '>',  '>',  '<',  '>',  '>',
	/*   (   */   '<',   '<',  '<',  '<',  '=',  ' ',
	/*   )   */   ' ',   ' ',  ' ',  ' ',  ' ',  ' ',
	/*   \0  */	  '<',   '<',  '<',  '<',  ' ',   '='
};

void DrawTree(const AstNode* Node, int deep, int& step, int leftNow, int leftStep);
void Draw();

extern char TokenRoad[100];
extern int DeepMap[100];
extern int Left[100];


//----------------------------------------------------------------------------------------




//-------------------------------AST到NFA-------------------------------------------------


const char eChar = 180;		// E

struct bridge;

class node
{
public:

	bool isEndNode = false; 
	bool isErrNode = false;
	bridge* Bridge1;				//在eNFA里使用
	bridge* Bridge2;				//在eNFA里使用
	bridge* BridgeList[100];		//在NFA里使用
	int BridgeIndex = -1;
	

};


struct bridge
{
	node* nodeStart;
	node* nodeEnd;
	char bridge_char;
};

node* getNodeEnd( node* Node);

class NfaStack
{
public:
	void push(char token);
	void push(node* Node);
	NfaStack() { index = -1; };
	node* pop();
	bool isEmpty();
private:
	int index;
	node* pNode[100] = { NULL };
};


//-------------------------------------------------------------------------------------


//------------------------------eNFA转NFA----------------------------------------------
class NodeList
{
public:
	void flush();
	bool Add(node* Node);	//添加会检测是否是同一个结点，是就不添加
	void show();
	int Length();
	node* getNode(int index);
private:
	int index = -1;
	node* pNode[100] = { NULL };
};


class BridgeList
{
public:
	void Add(bridge* Bridge);
	int Length();
	void show();
	bridge* getBridge(int index);
private:
	int index = -1;
	bridge* pBridge[100] = { NULL };
};

extern NodeList validNodeList;
void FindNoChange(node* Node, bool isValidInput);
void FindBridgeNode(node* Node, NodeList* nodeList,BridgeList* bridgeList);

//----------------------------------------------------------------------------------