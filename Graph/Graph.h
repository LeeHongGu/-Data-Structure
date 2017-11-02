#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include "Node.h"
#include "Vertex.h"

using namespace std;

class Graph
{

private:
	
	Node** nodeList; // ��带 �����ϴ� �迭
	bool* visited; // �湮�� ���� Ȯ�� �迭
	int** adjacencyMatrixArr; // ������� �迭
	int vertexNum; // ������ ����
	int count; // ������ ���� 1,2,3... ī��Ʈ
	string fileName; // �о���̴� ���� �̸�
	Vertex minimumHeap[100]; // �ּ��� �迭 
	int heapSize; // ���� ������
	int parent[100]; // �θ�
	int num[100];

	int* saveWeight;
	
public:
	Graph(void);
	~Graph(void);
	void setVertexNum(int vertexNum) { this -> vertexNum = vertexNum; }
	int getVertexNum(){ return vertexNum; }
	void fileRead(string fileName); // �����б�

	/****************************** 1������ **************************************/

	void makeArray(int vertexNum); // �迭 �Ҵ� �� �ʱ�ȭ
	void insertAdjacencyMatrixElement(int v, int e); // �������( ����� 1�� �Ǵºκ� ) ����
	void printAdjacencyMatrix(); // ������� ���
	void insertAdjacencyList(int v1, int v2); // ��������Ʈ ��� ����
	void printAdjacencyList(); // ��������Ʈ ���
	bool allVisited(); // ������ ��� �湮 �ߴ��� ���� Ȯ��

	/***** DFS ��� *****/
	// matrix DFS
	void printDFS(); // DFS ���
	void matrixDFS(int v); // ������� DFS(���̿켱 ����)
	void searchDFS(int v); // �湮 ���ο� ���� Ž����
	int isVisitedDFS(); // ����Ŭ�� �߻��� �κ��� ���� �湮���� ã����
	
	// list DFS
	void printListDFS(); // ��������Ʈ DFS(���̿켱 ����)
	void listDFS(int v); // ��������Ʈ DFS(���̿켱 ����)
	void searchListDFS(int v); // �湮 ���ο� ���� Ž����
	int isVisitedListDFS(); // ����Ŭ�� �߻��� �κ��� ���� �湮���� ã����



	/***** BFS ��� *****/
	// matrix BFS
	void printBFS(int v); // BFS ���
	void matrixBFS(int v); // ������� BFS(���̿켱 ����)
	void searchBFS(int v); // �湮 ���ο� ���� Ž����
	void isVisitedBFS(); // ����Ŭ�� �߻��� �κ��� ���� �湮���� ã����
	
	// list BFS
	void printListBFS(int v); // BFS ���
	void listBFS(int v); // ������� BFS(���̿켱 ����)
	void searchListBFS(int v); // �湮 ���ο� ���� Ž����
	void isVisitedListBFS(); // ����Ŭ�� �߻��� �κ��� ���� �湮���� ã����


	/****************************** 2������ **************************************/

	void makeHeap(int vertexNum); // �ּ��� �迭 �Ҵ� �� �ʱ�ȭ
	void insertHeap(int v1, int v2, int weight); // ���Ϸκ��� ���� �о��, ���� �־���
	Vertex deleteHeap(); // �� ����
	int collapsingFind(int v); // v�� ��ǥ ã��
	void weightedUnion(int v1,int v2); // v1�� v2�� ���� ������ ��ġ��
	void kruskal( int vertexNum ); // kruskal�˰���
	bool isCycle(int v); // ����Ŭ ���� �Ǵ�
	void test(int weight);

	/****************************** 3������ **************************************/
	void insertDirectedList(int v1, int v2); // ���⸮��Ʈ�� ��� ����
	int topologicalSort(); // ��������






	




	



	



	
	

	

	
	
};

