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
	
	Node** nodeList; // 노드를 저장하는 배열
	bool* visited; // 방문한 정점 확인 배열
	int** adjacencyMatrixArr; // 인접행렬 배열
	int vertexNum; // 정점의 갯수
	int count; // 연결요소 숫자 1,2,3... 카운트
	string fileName; // 읽어들이는 파일 이름
	Vertex minimumHeap[100]; // 최소힙 배열 
	int heapSize; // 힙의 사이즈
	int parent[100]; // 부모
	int num[100];

	int* saveWeight;
	
public:
	Graph(void);
	~Graph(void);
	void setVertexNum(int vertexNum) { this -> vertexNum = vertexNum; }
	int getVertexNum(){ return vertexNum; }
	void fileRead(string fileName); // 파일읽기

	/****************************** 1번문제 **************************************/

	void makeArray(int vertexNum); // 배열 할당 및 초기화
	void insertAdjacencyMatrixElement(int v, int e); // 인접요소( 행렬의 1이 되는부분 ) 삽입
	void printAdjacencyMatrix(); // 인접행렬 출력
	void insertAdjacencyList(int v1, int v2); // 인접리스트 노드 삽입
	void printAdjacencyList(); // 인접리스트 출력
	bool allVisited(); // 정점을 모두 방문 했는지 여부 확인

	/***** DFS 모듈 *****/
	// matrix DFS
	void printDFS(); // DFS 출력
	void matrixDFS(int v); // 인접행렬 DFS(깊이우선 선택)
	void searchDFS(int v); // 방문 여부에 따라 탐색함
	int isVisitedDFS(); // 사이클이 발생한 부분의 다음 방문지를 찾아줌
	
	// list DFS
	void printListDFS(); // 인접리스트 DFS(깊이우선 선택)
	void listDFS(int v); // 인접리스트 DFS(깊이우선 선택)
	void searchListDFS(int v); // 방문 여부에 따라 탐색함
	int isVisitedListDFS(); // 사이클이 발생한 부분의 다음 방문지를 찾아줌



	/***** BFS 모듈 *****/
	// matrix BFS
	void printBFS(int v); // BFS 출력
	void matrixBFS(int v); // 인접행렬 BFS(넓이우선 선택)
	void searchBFS(int v); // 방문 여부에 따라 탐색함
	void isVisitedBFS(); // 사이클이 발생한 부분의 다음 방문지를 찾아줌
	
	// list BFS
	void printListBFS(int v); // BFS 출력
	void listBFS(int v); // 인접행렬 BFS(넓이우선 선택)
	void searchListBFS(int v); // 방문 여부에 따라 탐색함
	void isVisitedListBFS(); // 사이클이 발생한 부분의 다음 방문지를 찾아줌


	/****************************** 2번문제 **************************************/

	void makeHeap(int vertexNum); // 최소힙 배열 할당 및 초기화
	void insertHeap(int v1, int v2, int weight); // 파일로부터 값을 읽어와, 힙에 넣어줌
	Vertex deleteHeap(); // 힙 방출
	int collapsingFind(int v); // v의 대표 찾기
	void weightedUnion(int v1,int v2); // v1과 v2가 속한 집합을 합치기
	void kruskal( int vertexNum ); // kruskal알고리즘
	bool isCycle(int v); // 사이클 여부 판단
	void test(int weight);

	/****************************** 3번문제 **************************************/
	void insertDirectedList(int v1, int v2); // 방향리스트에 노드 삽입
	int topologicalSort(); // 위상정렬






	




	



	



	
	

	

	
	
};

