#include "Graph.h"

Graph::Graph()
{
	count = 1;
	heapSize = 0;
}

Graph::~Graph()
{
	for ( int i = 0; i < vertexNum; i++ ) // 2���� �迭 ����
	{
		delete[] adjacencyMatrixArr[i];
	}
	delete[] adjacencyMatrixArr;
}

void::Graph::makeArray(int vertexNum) // �迭 ����� �Ҵ��ϴ� �� ���
{
	adjacencyMatrixArr = new int* [ vertexNum ]; // 2���� �迭 �Ҵ�
	for( int i = 0; i < vertexNum; i++ )
	{
		adjacencyMatrixArr[i] = new int [ vertexNum ];
	}

	for ( int i = 0; i < vertexNum; i++ )		// 2���� �迭 �ʱ�ȭ
	{
		for ( int j = 0; j < vertexNum; j++ )
		{
			adjacencyMatrixArr[i][j] = 0;
		}
	}

	nodeList = new Node*[vertexNum]; // ����� 2���� �迭 �Ҵ�

	for(int i = 0; i < vertexNum; i++) // ����� 2���� �迭 �ʱ�ȭ
	{
		nodeList[i] = new Node(i,0);
	}

	for( int i = 0; i < 100; i++ )
	{
		parent[i] = -1;
		num[i] = 1;
	}

} // makeArray�޼ҵ� ��

void Graph::fileRead(string fileName) // ���� ã��
{
	ifstream is;
	int v1, v2, weight; // ��������, ������(���� ������), ����ġ
	int i = 0;
	
	is.open( fileName, ios::in );	// �Է¸��

	if ( is.fail()) 
	{
		cerr << " ���� �б� ���� " << endl;
		exit(1);
	}

	if ( fileName == "graph1.txt" )
	{
		is >> vertexNum; // ������ ����
		makeArray(vertexNum); // �迭 �Ҵ� �� �ʱ�ȭ

		while(1)
		{
			is >> v1; // ����1

			if ( v1 == -1 )
				break;

			is >> v2; // ����2

			Vertex* v = new Vertex(v1, v2);

			insertAdjacencyList(v -> vertex1, v -> vertex2); // ��忡 ����
			insertAdjacencyMatrixElement(v1, v2); // ������� ����
		}
	} // if�� ( FileName = graph1.txt )


	else if ( fileName == "graph2.txt" )
	{
		is >> vertexNum; // ������ ����

		// visited �ʱ�ȭ
		visited = new bool [vertexNum];
		for ( int i = 0 ; i < vertexNum; i++ )
		{
			visited[i] = false;
		}

		setVertexNum(vertexNum);
		makeArray(vertexNum);

		while(1)
		{
			is >> v1; // ����1
			if ( v1 == -1 )
				break;

			is >> v2; // ����2
			is >> weight; // ����ġ

			Vertex* v = new Vertex(v1, v2, weight);

			insertHeap( v -> vertex1, v -> vertex2, v -> weight ); // ������ �� ����
			insertAdjacencyMatrixElement(v -> vertex1, v -> vertex2); // ������� ����
		}
	} // else if�� ( FileName = graph2.txt )


	else if ( fileName == "graph3.txt" )
	{
		is >> vertexNum; // ������ ����
		makeArray(vertexNum); // �迭 �Ҵ� �� �ʱ�ȭ
					
		while(1)
		{
			is >> v1; // ����1

			if ( v1 == -1 )
				break;

			is >> v2; // ����2

			Vertex* v = new Vertex(v1, v2);

			insertDirectedList(v -> vertex1, v -> vertex2); // ��忡 ����
		}
	} // else if�� ( FileName = graph3.txt )

	is.close();
} // fileRead�޼ҵ� ��

/**************************** 1�� *********************************/
/***** ����, ���� �켱Ž���� �̿��� ������� ã�� *****/

void Graph::insertAdjacencyMatrixElement(int v1, int v2) // ��������� ������� �Է�
{
	adjacencyMatrixArr[v2][v1] = 1;
	adjacencyMatrixArr[v1][v2] = 1;
} // insertAdjacencyMatrixElement�޼ҵ� ��

void Graph::insertAdjacencyList(int v1, int v2) // ��������Ʈ�� ��� ����
{
	Node* newNode = new Node(v2, 0); // ���ε��� ���
	Node* adjacencyNewNode = new Node(v1,0); // ���ε��� ����� �������

	Node* currentNode = nodeList[v1]; // ������
	Node* adjacencyCurrentNode = nodeList[v2]; // �������� �������

	Node* preNode = nodeList[v1]; // �������
	Node* adjacencyPreNode = nodeList[v2]; // ��������� �������


	if ( currentNode -> data == v1 && adjacencyCurrentNode -> data == v2)
	{
		if ( currentNode -> link != 0 || adjacencyCurrentNode -> link != 0)
		{
			if ( adjacencyCurrentNode -> link == 0 ) // ������� ��ũ�� ������, �����Ȱ� ��ũ�� ������
			{
				adjacencyCurrentNode -> link = adjacencyNewNode;

				currentNode = currentNode -> link;
				preNode -> link = newNode;
				newNode -> link = currentNode;
				return;
			}


			else if ( currentNode -> link == 0 ) // ������� ��ũ�� ����, �����Ȱ� ��ũ�� ������
			{
				currentNode -> link = newNode;

				adjacencyCurrentNode = adjacencyCurrentNode -> link;
				adjacencyPreNode -> link = adjacencyNewNode;
				adjacencyNewNode -> link = adjacencyCurrentNode;
				return;
			}


			else // �Ѵ� ��ũ�� ������
			{
				currentNode = currentNode -> link;
				preNode -> link = newNode;
				newNode -> link = currentNode;

				adjacencyCurrentNode = adjacencyCurrentNode -> link;
				adjacencyPreNode -> link = adjacencyNewNode;
				adjacencyNewNode -> link = adjacencyCurrentNode;
				return;
			}	
		} // �ι�° if��

		currentNode -> link = newNode;
		adjacencyCurrentNode -> link = adjacencyNewNode;
		return;
	} // ù��° if��
} // insertAdjacencyList�޼ҵ� ��

void Graph::printAdjacencyMatrix() // ������� ���
{
	for ( int i = 0; i < vertexNum; i++ )
	{
		for ( int j = 0; j < vertexNum; j++ )
		{
			cout << adjacencyMatrixArr[i][j] << " ";
		}
		cout << endl;
	} // for��
} // printAdjacencyMatrix�޼ҵ� ��

void::Graph::printAdjacencyList() // ��������Ʈ ���
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
	} // for��
} // printAdjacencyList�޼ҵ� ��

bool Graph::allVisited() // ��� ������ �湮������ true ��ȯ
{
	for ( int w = 0; w < vertexNum; w++ )
	{
		if ( visited[w] ==  false)
			return false;
	}
	return true; 
} // allVisited��


/***** DFS ��� *****/
// matrix DFS
void Graph::printDFS() // DFS���
{
	visited = new bool [vertexNum];
	 // vistied�迭 �ʱ�ȭ
	for ( int i = 0 ; i < vertexNum; i++ )
	{
		visited[i] = false;
	}

	cout << "������" << endl;
	cout << "1. ������� + DFS" << endl;

	while(1)
	{
		cout << "   ������ " << count++ << " - ";
		int v = isVisitedDFS();
		matrixDFS(v);

		if (allVisited() == true) // ��� ������ �湮 ���� ��, ����
			break;

		cout << endl;
	}
	cout << endl;

	delete[] visited;
} // printDFS�޼ҵ� ��

void Graph::matrixDFS(int v) // ������� DFS ����
{
	searchDFS(v); // DFS�� ã�´�.

	if( allVisited() == false )
		isVisitedDFS(); // ���� �湮���� ���� ���� �湮
} // matrixDFS��

void Graph::searchDFS(int v) // ������Ŀ��� DFSã��
{
	visited[v] = true; // ����v �湮��, true�� �湮 ǥ��
	cout << v << " ";

	for( int w = 0; w < vertexNum; w++ ) 
	{ 
		if( adjacencyMatrixArr[v][w] == 1 && !visited[w] ) // �湮���� ���� ���� ���� Ž�� (����Ŭ ����� �����)
			matrixDFS(w); // ���� w���� DFS ���� ���� 	
	}
} // searchDFS��

int Graph::isVisitedDFS()
{
	int index; // ���� �湮�������� ����
	for ( int w = 0; w < vertexNum; w++ ) // ����Ŭ ������ �� �� ������ ������ �湮
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
}// isVisitedDFS�޼ҵ� ��


// list DFS
void Graph::printListDFS() // ��������Ʈ DFS(���̿켱 ����)
{
	count = 1;

	// visited�迭 �ʱ�ȭ
	visited = new bool [vertexNum];
	for ( int i = 0 ; i < vertexNum; i++ )
	{
		visited[i] = false;
	}

	cout << "������" << endl;
	cout << "3. ��������Ʈ + DFS" << endl;

	while(1)
	{
		cout << "   ������ " << count++ << " - ";
		int v = isVisitedListDFS();
		listDFS(v);

		if( allVisited() == true ) // ��� ���� �湮 ��, ����
			break;

		cout << endl;
	}
	cout << endl;

	delete[] visited;
}

void Graph::searchListDFS(int v) // ��������Ʈ���� DFSã��
{
	Node* w; 

    visited[v] = true; // �湮�� ���� true�� �湮 ǥ��
    cout << v << " ";

	for( w = nodeList[v]; w; w = w -> link )  
    { 
		if(!visited[w -> data]) // �湮 ���� ���� ������ �湮
			listDFS(w -> data); 
    } 
} // searchListDFS��

void Graph::listDFS(int v) // ��������Ʈ DFS
{
	searchListDFS(v); // DFS�� ã�´�.

	if (allVisited() == false) // ���� �湮���� ���� ���� �湮
		isVisitedDFS();
} // listDFS�޼ҵ� ��

int Graph::isVisitedListDFS() // ���� �湮���� ���� ���� Ȯ��
{
	int index; // ���� �湮�������� ����
	for ( int w = 0; w < vertexNum; w++ ) // ����Ŭ ������ �� �� ������ ������ �湮
	{
		if ( allVisited() == true ) // ������� �湮�� ����
			break;

		else if( !visited[w] ) // ���� �湮 �������� ���� Ȯ�� ��, index ��°���� �ٽ� ã�� ����
		{
			index = w;
			break;
		}		
	}
	return index;
} // isVisitedListDFS�޼ҵ� ��


/***** BFS ��� *****/
// matrix BFS
void Graph::printBFS(int v) // BFS ���
{
	count = 1;
	// visited�迭 �ʱ�ȭ
	visited = new bool [vertexNum]; 
	for ( int i = 0 ; i < vertexNum; i++ )
	{
		visited[i] = false;
	}

	cout << "2. ������� + BFS" << endl;

	while(1)
	{
		cout << "   ������ " << count << " - ";
		matrixBFS(v);

		if (allVisited() == true) // ��� ���� �湮��, ����
			break;
		cout << endl;
	}
	cout << endl;

	delete[] visited;
} // printBFS�޼ҵ� ��

void Graph::matrixBFS(int v) // ������� BFS
{
	searchBFS(v);
	if ( allVisited() == false ) // �湮���� ���� ���� �湮
		isVisitedBFS();
} // matrixBFS�޼ҵ� ��

void Graph::searchBFS(int v) // ������� BFSã��
{
	queue<int> q;
	visited[v] = true; // �湮�� ���� true�� �湮 ǥ�� 
	cout << v << " ";         
	q.push(v); // ���� ���� Queue�� ����

	while( !q.empty() )
	{ 
		v = q.front(); // Queue�� ����� ���� ����  
		q.pop(); // ����

		for( int w = 0; w < vertexNum; w++ )
		{
			// ������ ���� Ž��  
			if( adjacencyMatrixArr[v][w] == 1 && !visited[w]) // ���� �湮���� ���� ���� Ȯ�� �� �湮 (����Ŭ ����� �����)
			{  
				visited[w] = true; // �湮�� ���� true�� �湮 ǥ��
				cout << w << " ";    
				q.push(w); // �湮�� ���� Queue�� ���� 
			} // if��
		} // for��
	} // while��
} // searchBFS�޼ҵ� ��

void Graph::isVisitedBFS()
{
	cout << endl;
	cout << "   ������ " << ++count << " - ";

	int index; // ���� �湮�������� ����

	for ( int w = 0; w < vertexNum; w++ )
	{
		if ( allVisited() == true ) // ��� ���� �湮��, ����
			break;

		else if ( visited[w] == false ) // ���� �湮 ���� ���� ���� ������ index���� �ٽ� �湮
		{
			index = w;
			matrixBFS(index);
		}
	} // for��
} // isVisitedBFS�޼ҵ� ��


// list BFS
void Graph::printListBFS(int v) // ��������Ʈ BFS���
{
	cout << endl;
	count = 1;
	// visited�迭 �ʱ�ȭ
	visited = new bool [vertexNum];
	for ( int i = 0 ; i < vertexNum; i++ )
	{
		visited[i] = false;
	}

	cout << "4. ������� + BFS" << endl;

	while(1)
	{
		cout << "   ������ " << count << " - ";
		listBFS(v);

		if ( allVisited() == true ) // ��� ���� �湮��, ����
			break;
		cout << endl;
	}
	cout << endl;

	delete[] visited;
} // printListBFS�޼ҵ� ��

void Graph::listBFS(int v) // ��������Ʈ BFS
{
	searchListBFS(v);
	if( allVisited() == false ) // �湮���� ���� ���� ������, Ȯ��
		isVisitedListBFS();
} // listBFS�޼ҵ� ��

void Graph::searchListBFS(int v)
{
	Node* w; 
	queue<int> q;
	visited[v] = true; // �湮�� ���� true�� �湮 ǥ�� 
	cout << v << " ";         
	q.push(v); // ���� ���� Queue�� ����

	while(!q.empty())
	{             
		v = q.front(); // Queue�� ����� ���� ����
		q.pop();  // ����

		//���� ���� Ž�� 
		for( w = nodeList[v]; w; w = w -> link ) 
		{
			if( !visited[w -> data] )  // ���� �湮���� ���� ���� Ȯ�� �� �湮 (����Ŭ ����� �����)
			{   
				visited[w -> data] = true; // �湮�� ���� true�� �湮 ǥ�� 
				cout << w -> data << " "; // �湮�� ���� ���
				q.push(w -> data); // �湮�� ���� Queue�� ���� 
			} // if��
		} // for��
	} // while��
} // searchListBFS�޼ҵ� ��

void Graph::isVisitedListBFS()
{
	cout << endl;
	cout << "   ������ " << ++count << " - ";

	int index; // ���� �湮�������� ����

	for ( int w = 0; w < vertexNum; w++ )
	{
		if (allVisited() == true) // ������� �湮��, ����
			break;

		else if ( visited[w] == false ) // ���� �湮 ���� ���� ���� ������ index���� �ٽ� �湮
		{
			index = w;
			listBFS(index);
		}
	} // for��
} // isVisitedListBFS�޼ҵ� ��



/************************* 2��******************************/
/***** Kruskal �˰������� �ּҽ���Ʈ�� ã�� *****/

void Graph::insertHeap(int v1, int v2, int weight)
{ 
	int i; 
    i = ++(heapSize); 

	while( i != 1 && weight < minimumHeap[i/2].getWeight() ) // �ڽİ� �θ� �� 
    { 
        minimumHeap[i] = minimumHeap[i/2]; 
        i = i / 2; 
    } 

	// ���� �� �Է�
	minimumHeap[i].setVertex1(v1);
	minimumHeap[i].setVertex2(v2);
	minimumHeap[i].setWeight(weight);
} // insertHeap�޼ҵ� ��

Vertex Graph::deleteHeap() // �� ����
{
	int parentNode = 1, childNode = 2; 
	Vertex data, temp; 

	data = minimumHeap[parentNode]; 
	temp = minimumHeap[(heapSize)--]; // ���� ���� �ϸ鼭 heapSize ����

	while( childNode <= heapSize ) 
    { 
         //�ڽ� ��尣�� ���� �� ��
		if( (childNode < heapSize) && (minimumHeap[childNode].getWeight()) > minimumHeap[childNode + 1].getWeight())  
            childNode++; 
         
		if( temp.getWeight() <= minimumHeap[childNode].getWeight() ) 
			break;

        minimumHeap[parentNode] = minimumHeap[childNode]; 
        parentNode = childNode; 
        childNode = childNode * 2; // ���� �ڽ� ���� �� 
    } 

    minimumHeap[parentNode] = temp; 
    return data; 
} // deleteHeap��

int Graph::collapsingFind(int v) // v�� ���ϴ� ������ ��ǥ�� ��ȯ
{ 
    int i, p, temp; 

    for( i = v; (p = parent[i]) >= 0;i = p); // ����v�� ��Ʈ�� ã�´�.
     
    temp = i; // ���� v�� �����ϴ� ������ ��ǥ ���Ҹ� ����
      
    for( i = v; (p = parent[i]) >= 0; i = p)  
        parent[i] = temp; // ������ ��� ���ҵ��� �θ� ���� 

    return temp; 
} // collapsingFind��

void Graph::weightedUnion(int v1,int v2) // �ΰ��� ���Ұ� ���� ������ ��ħ
{ 
    if( num[v1] < num[v2] ) // �ڽ��� ������ ���� 
    { 
        parent[v1] = v2; // �θ� ���� ����
        num[v1] += num[v2]; 
    } 

    else 
    { 
        parent[v2] = v1; // �θ� ���� ����
        num[v2] += num[v1]; 
    } 
} // SetUnion��

bool Graph::isCycle(int v) // DFS�� �̿��Ͽ� ����Ŭ ���� �Ǵ�
{ 
    int w; 
     
    visited[v] = true; // �湮�� ���� true�� �湮 ǥ�� 
   
	for(w = 0; w < vertexNum; w++) 
    { 
        if(adjacencyMatrixArr[v][w] == 1 && !visited[w]) // ���� �湮���� ���� ���� Ȯ�� �� �湮 (����Ŭ ����� �����)
            isCycle(w); // ���� w���� DFS ���� ���� 
    } 

	if ( allVisited() == false ) // ����Ŭ�� �߻��ϸ� ��� ������ �湮�������Ѵ�. ���� false�� ��ȯ
	{
		return false;
	}
	return true;
} // isCycle�޼ҵ� ��

void Graph::kruskal(int vertexNum ) // kruskal �˰������� �ּ� ����Ʈ�� ����
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
		cout << "> �ּҺ�� ����Ʈ���� ���� �� ����" << endl;
		return;
	}
		
	else
	{
		cout << "���õ� ���� : ";
		cout << "�ּҺ�� ����Ʈ���� ���� �� ����" << endl;
		while( edgeCount < vertexNum - 1) // ������ ������ n-1�� �� �� ���� 
		{ 
			v = deleteHeap(); // �ּ��� ����

			// ���� ����ġ�� ���� ���� ������ ���� 
			v1Find = collapsingFind( v.getVertex1() );  
			v2Find = collapsingFind( v.getVertex2() ); 

			if( v1Find != v2Find ) // ������ ��ǥ ���Ұ� ���� ���� ��� 
			{ 
				cout << "(";
				cout << v.getVertex1() << " " << v.getVertex2() << " " << v.getWeight(); 
				cout << ")";
				saveWeight[edgeCount] = v.getWeight();

				sumWeight += v.getWeight(); 
				edgeCount++; // ������ �ø���
				weightedUnion( v1Find,v2Find ); // �� ������ ��ħ
				
			} // if��
    } // while��

	cout << endl;
    cout << "�ּҺ�� ������ ���� : ";
	for(int i = 0; i < edgeCount; i++ )
	{
		cout << saveWeight[i];
		if( i == edgeCount - 1 )
			cout << " = ";

		else cout << " + ";
	}
		
	cout << sumWeight << endl;
	}

} // kruskal��

void Graph::test(int weight)
{
	//saveWeight[i] = weight;
}


/************************* 3�� *****************************/
/***** ���������� �̿��Ͽ� ������� ��� *****/

void Graph::insertDirectedList(int v1, int v2) // ���⸮��Ʈ ����
{
	Node* currentNode = nodeList[v1]; // ������
	Node* preNode = nodeList[v1]; // �������
	Node* newNode = new Node(v2, 0); // ���ε��� ���


	if ( currentNode -> link != 0 ) // �������� ��ũ�� ���� ��
	{
		currentNode = currentNode -> link;
		preNode -> link = newNode;
		newNode -> link = currentNode;
		return;

	} // ù��° if��
	  
	else // �������� ��ũ�� ���� ��
	{
		currentNode -> link = newNode;
		return;
	}
} // insertDirectedList�޼ҵ� ��

int Graph::topologicalSort() // ��������
{
	int i,u,v; 
	stack<int> s;
	Node* currentNode = new Node();

	// inEdge�迭 �ʱ�ȭ - ���԰����� ������ ī��Ʈ �ϴ� �迭
	int* inEdge = new int [vertexNum]; 
	for( int i = 0; i < vertexNum; i++ )
	{
		inEdge[i] = 0;
	}

	for( int i = 0; i < vertexNum; i++ ) // �� ������ ���� ���԰��� ���� �ľ�
    { 
		currentNode = nodeList[i]; 
		
		while( currentNode != 0 )
        { 
			Node* nextNode = currentNode -> link; // nextNode(�����尡 ����Ű�� ���)
			if( currentNode -> link != 0 ) // ���� ����� ��ũ�� ���� ��
			{
				inEdge[nextNode -> data]++; // ���� i�� ���԰��� ����
			}

			currentNode = currentNode -> link;
        } // while��
    } // for��

	for( int i = 0; i < vertexNum; i++ ) 
    { 
		// ���������� ���� ������ Stack�� ���� 
		if( inEdge[i] == 0 ) 
			s.push(i); 
    } 

    cout << "������� : "; 
	while( !s.empty() ) // ������ �� ������ �ƴҶ�
    { 
		v = s.top(); // ���� ������ ���� ���� top���� ����
		s.pop(); // ����
       
		cout << v << " ";
		currentNode = nodeList[v]; // ����v�� �������� ���� 

        while(currentNode != 0) 
        { 
			u = currentNode -> data; 
			inEdge[u]--;  // �������� ���ҽ�Ŵ
            if( inEdge[u] == 0 ) // ���� ������ �������� ���� ������ �����Ͽ�, 0�̵Ǹ� Stack�� ����
				s.push(u);

            currentNode = currentNode -> link; // ����� ��� ������ ����
        }
	}

	delete[] inEdge;
	return 0;
} // topologicalSort�޼ҵ� ��


