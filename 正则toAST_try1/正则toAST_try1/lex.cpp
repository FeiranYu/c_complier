#include"AST.h"

const char firstChar = 254;

char Lex(string& str, int& now)
{
	static char lastChar = firstChar;
	if (now == str.length())
	{
		now++;
		return '#';
	}
	if (now > str.length())
	{
		return ErrChar;
	}

	if (lastChar == firstChar)
	{
		lastChar = str[now];
		now++;
		return str[now - 1];
	}
	else if (str[now] == '|')
	{
		if (lastChar == '*')
		{
			lastChar = cat;
			return cat;
		}
		lastChar = str[now];
		now++;
		return str[now - 1];
	}
	else if (str[now] == '*')
	{
		lastChar = str[now];
		now++;
		return str[now - 1];
	}
	else if ((str[now] >= 'a' && str[now] <= 'z') || (str[now] >= 'A' && str[now] <= 'Z') || (str[now] >= '0' && str[now] <= '9'))
	{
		if (lastChar == '*')
		{
			lastChar = cat;
			return cat;
		}
		else if ((lastChar >= 'a' && lastChar <= 'z') || (lastChar >= 'A' && lastChar <= 'Z') || (lastChar >= '0' && lastChar <= '9') || lastChar == ')')
		{
			lastChar = cat;
			return cat;
		}
		else
		{
			lastChar = str[now];
			now++;
			return str[now - 1];
		}
	}
	else if (str[now] == '(')
	{
		if ((lastChar >= 'a' && lastChar <= 'z') || (lastChar >= 'A' && lastChar <= 'Z') || (lastChar >= '0' && lastChar <= '9') || lastChar == '*'||lastChar==')')
		{
			lastChar = cat;
			return cat;
		}
		else
		{
			lastChar = str[now];
			now++;
			return str[now - 1];
		}
	}
	else if (str[now] == ')')
	{
		lastChar = str[now];
		now++;
		return str[now - 1];
	}
}


AstNode *getNode(string& str, int& now)
{
	AstNode* newNode = new AstNode;
	newNode->token = Lex(str, now);
	return newNode;
}



bool isOpNode(const AstNode* Node)
{
	if (Node->token == '(' || Node->token == ')' || Node->token == '|' || Node->token == '*' || Node->token == cat||Node->token=='\0')
	{
		return true;
	}
	return false;
}

bool isOpNode(const char Char)
{
	if (Char == '(' || Char == ')' || Char == '|' || Char == '*' || Char == cat || Char == '\0')
	{
		return true;
	}
	return false;
}

bool isGrammar(const AstNode* Node)
{
	if ((Node->token >= 'a' && Node->token <= 'z') || (Node->token >= 'A' && Node->token <= 'Z') || (Node->token >= '0' && Node->token <= '9') || Node->token == '#')
	{
		return true;
	}
	return false;
}

bool isGrammar(const char Char)
{
	if ((Char >= 'a' && Char <= 'z') || (Char >= 'A' && Char <= 'Z') || (Char >= '0' && Char <= '9') || Char == '#')
	{
		return true;
	}
	return false;
}


int getPriority(const AstNode* Node)
{
	switch (Node->token)
	{
	case '\0':return -1;
	
	case '*':return 3;
	case cat:return 2;
	case '|':return 1;
	case '(':
	case ')':return 0;

	}
}

int getIndex(const AstNode* Node)
{
	switch (Node->token)
	{
	case('|'):return 0;
	case('+'):return 1;
	case('*'):return 2;
	case('('):return 3;
	case(')'):return 4;
	case('\0'):return 5;
	}
}

char comparePriority(const AstNode* nodeA, const AstNode* nodeB)
{
	int indexA = getIndex(nodeA);
	int indexB = getIndex(nodeB);

	return Priority[indexA][indexB];
}

AstNode* makeNode2(AstNode* father, AstNode* son1, AstNode* son2)
{
	father->child1 = son1;
	father->child2 = son2;
	return father;
}

AstNode* makeNode(AstNode* father, AstNode* son)
{
	father->child1 = NULL;
	father->child2 = son;
	return father;

}