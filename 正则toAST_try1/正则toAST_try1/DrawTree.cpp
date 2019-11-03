#include"AST.h"

char TokenRoad[100] = { 0 };
int DeepMap[100] = { 0 };
int Left[100] = { 0 };


//ÖÐÐò±éÀú
void DrawTree(const AstNode* Node,int deep, int &step,int leftNow,int leftStep)
{
	TokenRoad[step] = Node->token;
	DeepMap[step] = deep;
	Left[step] = leftNow;


	step++;
	if (Node->token == '*')
	{
		DrawTree(Node->child2, deep + 1, step, leftNow, leftStep);
	}
	else
	{

		if (Node->child1 != NULL)DrawTree(Node->child1, deep + 1, step, leftNow - leftStep/2, leftStep/2);
		if (Node->child2 != NULL)DrawTree(Node->child2, deep + 1, step, leftNow + leftStep/2, leftStep/2);
	}
	
}



void Draw()
{
	int width = 30;
	//find deepest 
	int maxdeep = 0;
	int step = 1;

	for (; DeepMap[step] != 0; step++)
	{
		if (DeepMap[step] > maxdeep)
		{
			maxdeep = DeepMap[step];
		}
	};
	//cout<<"maxdeep " << maxdeep << endl;

	for (int DrawNowDeep = 0; DrawNowDeep <= maxdeep; DrawNowDeep++)
	{
		int nowleft = 0;
		for (int i = 0; i < step; i++)
		{
			
			if (DeepMap[i] == DrawNowDeep)
			{
				while (nowleft < Left[i])
				{
					cout << " ";
					nowleft++;
				}
				cout << TokenRoad[i];
				nowleft++;

			}

		}

		cout << endl;
	}
}