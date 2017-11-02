#include "Graph.h"

Graph::Graph()
{
	count = 1;
	heapSize = 0;
}

Graph::~Graph()
{
	for ( int i = 0; i < vertexNum; i++ ) // 2차원 배열 삭제
	{
		delete[] adjacencyMatrixArr[i];
	}
	delete[] adjacencyMatrixArr;
}

void::Graph::makeArray(int vertexNum) // 배열 만들고 할당하는 것 모움
{
	adjacencyMatrixArr = new int* [ vertexNum ]; // 2차원 배열 할당
	for( int i = 0; i < vertexNum; i++ )
	{
		adjacencyMatrixArr[i] = new int [ vertexNum ];
	}

	for ( int i = 0; i < vertexNum; i++ )		// 2차원 배열 초기화
	{
		for ( int j = 0; j < vertexNum; j++ )
		{
			adjacencyMatrixArr[i][j] = 0;
		}
	}

	nodeList = new Node*[vertexNum]; // 노드형 2차원 배열 할당

	for(int i = 0; i < vertexNum; i++) // 노드형 2차원 배열 초기화
	{
		nodeList[i] = new Node(i,0);
	}

	for( int i = 0; i < 100; i++ )
	{
		parent[i] = -1;
		num[i] = 1;
	}

} // makeArray메소드 끝

void Graph::fileRead(string fileName) // 파일 찾기
{
	ifstream is;
	int v1, v2, weight; // 시작정점, 끝정점(파일 읽을때), 가중치
	int i = 0;
	
	is.open( fileName, ios::in );	// 입력모드

	if ( is.fail()) 
	{
		cerr << " 파일 읽기 실패 " << endl;
		exit(1);
	}

	if ( fileName == "graph1.txt" )
	{
		is >> vertexNum; // 정점의 갯수
		makeArray(vertexNum); // 배열 할당 및 초기화

		while(1)
		{
			is >> v1; // 정점1

			if ( v1 == -1 )
				break;

			is >> v2; // 정점2

			Vertex* v = new Vertex(v1, v2);

			insertAdjacencyList(v -> vertex1, v -> vertex2); // 노드에 삽입
			insertAdjacencyMatrixElement(v1, v2); // 인접요소 삽입
		}
	} // if끝 ( FileName = graph1.txt )


	else if ( fileName == "graph2.txt" )
	{
		is >> vertexNum; // 정점의 갯수

		// visited 초기화
		visited = new bool [vertexNum];
		for ( int i = 0 ; i < vertexNum; i++ )
		{
			visited[i] = false;
		}

		setVertexNum(vertexNum);
		makeArray(vertexNum);

		while(1)
		{
			is >> v1; // 정점1
			if ( v1 == -1 )
				break;

			is >> v2; // 정점2
			is >> weight; // 가중치

			Vertex* v = new Vertex(v1, v2, weight);

			insertHeap( v -> vertex1, v -> vertex2, v -> weight ); // 히프에 값 저장
			insertAdjacencyMatrixElement(v -> vertex1, v -> vertex2); // 인접요소 삽입
		}
	} // else if끝 ( FileName = graph2.txt )


	else if ( fileName == "graph3.txt" )
	{
		is >> vertexNum; // 정점의 갯수
		makeArray(vertexNum); // 배열 할당 및 초기화
					
		while(1)
		{
			is >> v1; // 정점1

			if ( v1 == -1 )
				break;

			is >> v2; // 정점2

			Vertex* v = new Vertex(v1, v2);

			insertDirectedList(v -> vertex1, v -> vertex2); // 노드에 삽입
		}
	} // else if끝 ( FileName = graph3.txt )

	is.close();
} // fileRead메소드 끝

/**************************** 1번 *********************************/
/***** 깊이, 넓이 우선탐색을 이용한 인접요소 찾기 *****/

void Graph::insertAdjacencyMatrixElement(int v1, int v2) // 인접행렬의 인접요소 입력
{
	adjacencyMatrixArr[v2][v1] = 1;
	adjacencyMatrixArr[v1][v2] = 1;
} // insertAdjacencyMatrixElement메소드 끝

void Graph::insertAdjacencyList(int v1, int v2) // 인접리스트에 노드 삽입
{
	Node* newNode = new Node(v2, 0); // 새로들어온 노드
	Node* adjacencyNewNode = new Node(v1,0); // 새로들어온 노드의 인접노드

	Node* currentNode = nodeList[v1]; // 현재노드
	Node* adjacencyCurrentNode = nodeList[v2]; // 현재노드의 인접노드

	Node* preNode = nodeList[v1]; // 이전노드
	Node* adjacencyPreNode = nodeList[v2]; // 이전노드의 인접노드


	if ( currentNode -> data == v1 && adjacencyCurrentNode -> data == v2)
	{
		if ( currentNode -> link != 0 || adjacencyCurrentNode -> link != 0)
		{
			if ( adjacencyCurrentNode -> link == 0 ) // 현재노드는 링크가 있으나, 인접된게 링크가 없을때
			{
				adjacencyCurrentNode -> link = adjacencyNewNode;

				currentNode = currentNode -> link;
				preNode -> link = newNode;
				newNode -> link = currentNode;
				return;
			}


			else if ( currentNode -> link == 0 ) // 현재노드는 링크가 없고, 인접된게 링크가 있을때
			{
				currentNode -> link = newNode;

				adjacencyCurrentNode = adjacencyCurrentNode -> link;
				adjacencyPreNode -> link = adjacencyNewNode;
				adjacencyNewNode -> link = adjacencyCurrentNode;
				return;
			}


			else // 둘다 링크가 있을때
			{
				currentNode = currentNode -> link;
				preNode -> link = newNode;
				newNode -> link = currentNode;

				adjacencyCurrentNode = adjacencyCurrentNode -> link;
				adjacencyPreNode -> link = adjacencyNewNode;
				adjacencyNewNode -> link = adjacencyCurrentNode;
				return;
			}	
		} // 두번째 if끝

		currentNode -> link = newNode;
		adjacencyCurrentNode -> link = adjacencyNewNode;
		return;
	} // 첫번째 if끝
} // insertAdjacencyList메소드 끝

void Graph::printAdjacencyMatrix() // 인접행렬 출력
{
	for ( int i = 0; i < vertexNum; i++ )
	{
		for ( int j = 0; j < vertexNum; j++ )
		{
			cout << adjacencyMatrixArr[i][j] << " ";
		}
		cout << endl;
	} // for끝
} // printAdjacencyMatrix메소드 끝

void::Graph::printAdjacencyList() // 인접리스트 출력
{
	for( int i = 0; i < vertexNum; i++ )
	{
		cout << i << " -> ";

		if( nodeList[i] -> link == 0 ) 
			cout << "null"; 

		for( Node *currentNode = nodeList[i] -> link; currentNode != 0; currentNode = currentNode -> link )
		{
			cout << currentNode -> data;
			if( currentNode -> link != 0 )
				cout << " - ";
		}
		cout << endl;
	} // for끝
} // printAdjacencyList메소드 끝

bool Graph::allVisited() // 모든 정점을 방문했으면 true 반환
{
	for ( int w = 0; w < vertexNum; w++ )
	{
		if ( visited[w] ==  false)
			return false;
	}
	return true; 
} // allVisited끝


/***** DFS 모듈 *****/
// matrix DFS
void Graph::printDFS() // DFS출력
{
	visited = new bool [vertexNum];
	 // vistied배열 초기화
	for ( int i = 0 ; i < vertexNum; i++ )
	{
		visited[i] = false;
	}

	cout << "연결요소" << endl;
	cout << "1. 인접행렬 + DFS" << endl;

	while(1)
	{
		cout << "   연결요소 " << count++ << " - ";
		int v = isVisitedDFS();
		matrixDFS(v);

		if (allVisited() == true) // 모든 정점에 방문 했을 시, 종료
			break;

		cout << endl;
	}
	cout << endl;

	delete[] visited;
} // printDFS메소드 끝

void Graph::matrixDFS(int v) // 인접행렬 DFS 생성
{
	searchDFS(v); // DFS를 찾는다.

	if( allVisited() == false )
		isVisitedDFS(); // 아직 방문하지 않은 지점 방문
} // matrixDFS끝

void Graph::searchDFS(int v) // 인접행렬에서 DFS찾기
{
	visited[v] = true; // 정점v 방문시, true로 방문 표시
	cout << v << " ";

	for( int w = 0; w < vertexNum; w++ ) 
	{ 
		if( adjacencyMatrixArr[v][w] == 1 && !visited[w] ) // 방문하지 않은 인접 정점 탐색 (사이클 생기면 종료됨)
			matrixDFS(w); // 정점 w에서 DFS 새로 시작 	
	}
} // searchDFS끝

int Graph::isVisitedDFS()
{
	int index; // 아직 방문하지않은 지점
	for ( int w = 0; w < vertexNum; w++ ) // 사이클 때문에 못 돈 나머지 정점들 방문
	{
		if (allVisited() == true)
			break;

		else if( !visited[w] )
		{
			index = w;
			break;
		}		
	}
	return index;
}// isVisitedDFS메소드 끝


// list DFS
void Graph::printListDFS() // 인접리스트 DFS(깊이우선 선택)
{
	count = 1;

	// visited배열 초기화
	visited = new bool [vertexNum];
	for ( int i = 0 ; i < vertexNum; i++ )
	{
		visited[i] = false;
	}

	cout << "연결요소" << endl;
	cout << "3. 인접리스트 + DFS" << endl;

	while(1)
	{
		cout << "   연결요소 " << count++ << " - ";
		int v = isVisitedListDFS();
		listDFS(v);

		if( allVisited() == true ) // 모든 정점 방문 시, 종료
			break;

		cout << endl;
	}
	cout << endl;

	delete[] visited;
}

void Graph::searchListDFS(int v) // 인접리스트에서 DFS찾기
{
	Node* w; 

    visited[v] = true; // 방문한 정점 true로 방문 표기
    cout << v << " ";

	for( w = nodeList[v]; w; w = w -> link )  
    { 
		if(!visited[w -> data]) // 방문 하지 않은 정점에 방문
			listDFS(w -> data); 
    } 
} // searchListDFS끝

void Graph::listDFS(int v) // 인접리스트 DFS
{
	searchListDFS(v); // DFS를 찾는다.

	if (allVisited() == false) // 아직 방문하지 않은 지점 방문
		isVisitedDFS();
} // listDFS메소드 끝

int Graph::isVisitedListDFS() // 아직 방문하지 않은 정점 확인
{
	int index; // 아직 방문하지않은 지점
	for ( int w = 0; w < vertexNum; w++ ) // 사이클 때문에 못 돈 나머지 정점들 방문
	{
		if ( allVisited() == true ) // 모든정점 방문시 종료
			break;

		else if( !visited[w] ) // 아직 방문 하지않은 지점 확인 후, index 번째부터 다시 찾기 시작
		{
			index = w;
			break;
		}		
	}
	return index;
} // isVisitedListDFS메소드 끝


/***** BFS 모듈 *****/
// matrix BFS
void Graph::printBFS(int v) // BFS 출력
{
	count = 1;
	// visited배열 초기화
	visited = new bool [vertexNum]; 
	for ( int i = 0 ; i < vertexNum; i++ )
	{
		visited[i] = false;
	}

	cout << "2. 인접행렬 + BFS" << endl;

	while(1)
	{
		cout << "   연결요소 " << count << " - ";
		matrixBFS(v);

		if (allVisited() == true) // 모든 정점 방문시, 종료
			break;
		cout << endl;
	}
	cout << endl;

	delete[] visited;
} // printBFS메소드 끝

void Graph::matrixBFS(int v) // 인접행렬 BFS
{
	searchBFS(v);
	if ( allVisited() == false ) // 방문하지 않은 정점 방문
		isVisitedBFS();
} // matrixBFS메소드 끝

void Graph::searchBFS(int v) // 인접행렬 BFS찾기
{
	queue<int> q;
	visited[v] = true; // 방문한 정점 true로 방문 표기 
	cout << v << " ";         
	q.push(v); // 시작 정점 Queue에 저장

	while( !q.empty() )
	{ 
		v = q.front(); // Queue에 저장된 정점 선택  
		q.pop(); // 꺼냄

		for( int w = 0; w < vertexNum; w++ )
		{
			// 인접한 정점 탐색  
			if( adjacencyMatrixArr[v][w] == 1 && !visited[w]) // 아직 방문하지 않은 정점 확인 후 방문 (사이클 생기면 종료됨)
			{  
				visited[w] = true; // 방문한 정점 true로 방문 표기
				cout << w << " ";    
				q.push(w); // 방문한 정점 Queue에 저장 
			} // if끝
		} // for끝
	} // while끝
} // searchBFS메소드 끝

void Graph::isVisitedBFS()
{
	cout << endl;
	cout << "   연결요소 " << ++count << " - ";

	int index; // 아직 방문하지않은 지점

	for ( int w = 0; w < vertexNum; w++ )
	{
		if ( allVisited() == true ) // 모든 정점 방문시, 종료
			break;

		else if ( visited[w] == false ) // 아직 방문 하지 않은 정점 있으면 index부터 다시 방문
		{
			index = w;
			matrixBFS(index);
		}
	} // for끝
} // isVisitedBFS메소드 끝


// list BFS
void Graph::printListBFS(int v) // 인접리스트 BFS출력
{
	cout << endl;
	count = 1;
	// visited배열 초기화
	visited = new bool [vertexNum];
	for ( int i = 0 ; i < vertexNum; i++ )
	{
		visited[i] = false;
	}

	cout << "4. 인접행렬 + BFS" << endl;

	while(1)
	{
		cout << "   연결요소 " << count << " - ";
		listBFS(v);

		if ( allVisited() == true ) // 모든 정점 방문시, 종료
			break;
		cout << endl;
	}
	cout << endl;

	delete[] visited;
} // printListBFS메소드 끝

void Graph::listBFS(int v) // 인접리스트 BFS
{
	searchListBFS(v);
	if( allVisited() == false ) // 방문하지 않은 정점 있을시, 확인
		isVisitedListBFS();
} // listBFS메소드 끝

void Graph::searchListBFS(int v)
{
	Node* w; 
	queue<int> q;
	visited[v] = true; // 방문한 정점 true로 방문 표기 
	cout << v << " ";         
	q.push(v); // 시작 정점 Queue에 저장

	while(!q.empty())
	{             
		v = q.front(); // Queue에 저장된 정점 선택
		q.pop();  // 꺼냄

		//인접 정점 탐색 
		for( w = nodeList[v]; w; w = w -> link ) 
		{
			if( !visited[w -> data] )  // 아직 방문하지 않은 정점 확인 후 방문 (사이클 생기면 종료됨)
			{   
				visited[w -> data] = true; // 방문한 정점 true로 방문 표기 
				cout << w -> data << " "; // 방문한 정점 출력
				q.push(w -> data); // 방문한 정점 Queue에 저장 
			} // if끝
		} // for끝
	} // while끝
} // searchListBFS메소드 끝

void Graph::isVisitedListBFS()
{
	cout << endl;
	cout << "   연결요소 " << ++count << " - ";

	int index; // 아직 방문하지않은 지점

	for ( int w = 0; w < vertexNum; w++ )
	{
		if (allVisited() == true) // 모든정점 방문시, 종료
			break;

		else if ( visited[w] == false ) // 아직 방문 하지 않은 정점 있으면 index부터 다시 방문
		{
			index = w;
			listBFS(index);
		}
	} // for끝
} // isVisitedListBFS메소드 끝



/************************* 2번******************************/
/***** Kruskal 알고리즘으로 최소신장트리 찾기 *****/

void Graph::insertHeap(int v1, int v2, int weight)
{ 
	int i; 
    i = ++(heapSize); 

	while( i != 1 && weight < minimumHeap[i/2].getWeight() ) // 자식과 부모 비교 
    { 
        minimumHeap[i] = minimumHeap[i/2]; 
        i = i / 2; 
    } 

	// 힙에 값 입력
	minimumHeap[i].setVertex1(v1);
	minimumHeap[i].setVertex2(v2);
	minimumHeap[i].setWeight(weight);
} // insertHeap메소드 끝

Vertex Graph::deleteHeap() // 힙 방출
{
	int parentNode = 1, childNode = 2; 
	Vertex data, temp; 

	data = minimumHeap[parentNode]; 
	temp = minimumHeap[(heapSize)--]; // 힙을 삭제 하면서 heapSize 감소

	while( childNode <= heapSize ) 
    { 
         //자식 노드간에 작은 수 비교
		if( (childNode < heapSize) && (minimumHeap[childNode].getWeight()) > minimumHeap[childNode + 1].getWeight())  
            childNode++; 
         
		if( temp.getWeight() <= minimumHeap[childNode].getWeight() ) 
			break;

        minimumHeap[parentNode] = minimumHeap[childNode]; 
        parentNode = childNode; 
        childNode = childNode * 2; // 다음 자식 노드와 비교 
    } 

    minimumHeap[parentNode] = temp; 
    return data; 
} // deleteHeap끝

int Graph::collapsingFind(int v) // v가 속하는 집합의 대표를 반환
{ 
    int i, p, temp; 

    for( i = v; (p = parent[i]) >= 0;i = p); // 정점v의 루트를 찾는다.
     
    temp = i; // 정점 v를 포함하는 집합의 대표 원소를 지정
      
    for( i = v; (p = parent[i]) >= 0; i = p)  
        parent[i] = temp; // 집합의 모든 원소들의 부모를 설정 

    return temp; 
} // collapsingFind끝

void Graph::weightedUnion(int v1,int v2) // 두개의 원소가 속한 집합을 합침
{ 
    if( num[v1] < num[v2] ) // 자식의 개수로 비교함 
    { 
        parent[v1] = v2; // 부모를 변경 해줌
        num[v1] += num[v2]; 
    } 

    else 
    { 
        parent[v2] = v1; // 부모를 변경 해줌
        num[v2] += num[v1]; 
    } 
} // SetUnion끝

bool Graph::isCycle(int v) // DFS를 이용하여 사이클 여부 판단
{ 
    int w; 
     
    visited[v] = true; // 방문한 정점 true로 방문 표기 
   
	for(w = 0; w < vertexNum; w++) 
    { 
        if(adjacencyMatrixArr[v][w] == 1 && !visited[w]) // 아직 방문하지 않은 정점 확인 후 방문 (사이클 생기면 종료됨)
            isCycle(w); // 정점 w에서 DFS 새로 시작 
    } 

	if ( allVisited() == false ) // 사이클이 발생하면 모든 정점을 방문하지못한다. 따라서 false를 반환
	{
		return false;
	}
	return true;
} // isCycle메소드 끝

void Graph::kruskal(int vertexNum ) // kruskal 알고리즘으로 최소 신장트리 추출
{
	saveWeight = new int[vertexNum];
	for( int i = 0; i < vertexNum; i++ )
	{
		saveWeight[i] = 0;
	}

	Vertex v;
	int v1Find, v2Find; 
	int edgeCount = 0;
	int sumWeight = 0;

	if ( isCycle(0) == false )
	{
		cout << "> 최소비용 신장트리를 구할 수 없음" << endl;
		return;
	}
		
	else
	{
		cout << "선택된 간선 : ";
		cout << "최소비용 신장트리를 구할 수 있음" << endl;
		while( edgeCount < vertexNum - 1) // 간선의 갯수가 n-1이 될 때 까지 
		{ 
			v = deleteHeap(); // 최소힙 방출

			// 가장 가중치가 가장 낮은 간선을 선택 
			v1Find = collapsingFind( v.getVertex1() );  
			v2Find = collapsingFind( v.getVertex2() ); 

			if( v1Find != v2Find ) // 서로의 대표 원소가 같지 않은 경우 
			{ 
				cout << "(";
				cout << v.getVertex1() << " " << v.getVertex2() << " " << v.getWeight(); 
				cout << ")";
				saveWeight[edgeCount] = v.getWeight();

				sumWeight += v.getWeight(); 
				edgeCount++; // 간선을 늘린다
				weightedUnion( v1Find,v2Find ); // 두 집합을 합침
				
			} // if끝
    } // while끝

	cout << endl;
    cout << "최소비용 간선의 길이 : ";
	for(int i = 0; i < edgeCount; i++ )
	{
		cout << saveWeight[i];
		if( i == edgeCount - 1 )
			cout << " = ";

		else cout << " + ";
	}
		
	cout << sumWeight << endl;
	}

} // kruskal끝

void Graph::test(int weight)
{
	//saveWeight[i] = weight;
}


/************************* 3번 *****************************/
/***** 위상정렬을 이용하여 위상순서 출력 *****/

void Graph::insertDirectedList(int v1, int v2) // 방향리스트 삽입
{
	Node* currentNode = nodeList[v1]; // 현재노드
	Node* preNode = nodeList[v1]; // 이전노드
	Node* newNode = new Node(v2, 0); // 새로들어온 노드


	if ( currentNode -> link != 0 ) // 현재노드의 링크가 있을 때
	{
		currentNode = currentNode -> link;
		preNode -> link = newNode;
		newNode -> link = currentNode;
		return;

	} // 첫번째 if끝
	  
	else // 현재노드의 링크가 없을 때
	{
		currentNode -> link = newNode;
		return;
	}
} // insertDirectedList메소드 끝

int Graph::topologicalSort() // 위상정렬
{
	int i,u,v; 
	stack<int> s;
	Node* currentNode = new Node();

	// inEdge배열 초기화 - 진입간선의 갯수를 카운트 하는 배열
	int* inEdge = new int [vertexNum]; 
	for( int i = 0; i < vertexNum; i++ )
	{
		inEdge[i] = 0;
	}

	for( int i = 0; i < vertexNum; i++ ) // 각 정점에 따른 진입간선 개수 파악
    { 
		currentNode = nodeList[i]; 
		
		while( currentNode != 0 )
        { 
			Node* nextNode = currentNode -> link; // nextNode(현재노드가 가르키는 노드)
			if( currentNode -> link != 0 ) // 현재 노드의 링크가 있을 시
			{
				inEdge[nextNode -> data]++; // 정점 i의 진입간선 갯수
			}

			currentNode = currentNode -> link;
        } // while끝
    } // for끝

	for( int i = 0; i < vertexNum; i++ ) 
    { 
		// 진입차수가 없는 정점을 Stack에 저장 
		if( inEdge[i] == 0 ) 
			s.push(i); 
    } 

    cout << "위상순서 : "; 
	while( !s.empty() ) // 스택이 빈 스택이 아닐때
    { 
		v = s.top(); // 진입 차수가 없는 정점 top으로 설정
		s.pop(); // 꺼냄
       
		cout << v << " ";
		currentNode = nodeList[v]; // 정점v의 진입차수 변경 

        while(currentNode != 0) 
        { 
			u = currentNode -> data; 
			inEdge[u]--;  // 진입차수 감소시킴
            if( inEdge[u] == 0 ) // 진입 차수가 없어질때 까지 간선을 제거하여, 0이되면 Stack에 넣음
				s.push(u);

            currentNode = currentNode -> link; // 연결된 모든 간선을 제거
        }
	}

	delete[] inEdge;
	return 0;
} // topologicalSort메소드 끝


