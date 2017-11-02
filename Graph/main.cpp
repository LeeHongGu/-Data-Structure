
#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;


int main()
{
	Graph g;
	string fileName;
	string choice = "0";

	while(1)
	{
		cout << "���α׷��� �����ϼ��� \n[S]earch / [M]inimum cost spanning tree / [T]opological Sort / [Q]uit : ";
		cin >> choice;

		
		if ( choice == "S" ) // S ����
		{
			cout << "> ������ �׷����� ����� ���ϸ��� �Է��Ͻÿ�(�����quit) : ";
			cin >> fileName;

			if ( fileName == "quit" )
			{
				cout << "> ���α׷��� �����մϴ�." << endl;
				exit(1);
			}

			else if ( fileName == "graph1.txt" )
			{
				g.fileRead( fileName ); // ���� �б�

				g.printAdjacencyMatrix(); cout << endl; // ������� ǥ��
				g.printAdjacencyList(); cout << endl; // ��������Ʈ ǥ��

				g.printDFS(); cout << endl; // ������� DFS ��� 
				g.printBFS(0); cout << endl; // ������� BFS ���

				g.printListDFS(); // ��������Ʈ DFS ���
				g.printListBFS(0); // ��������Ʈ BFS ���
			}

			else
			{
				cout << "> �ش� ���α׷��� ���ϸ��� [graph1.txt] �Դϴ�.." << endl;
				exit(1);
			}
		} // if�� ( S�� ���� )


		else if ( choice == "M" ) // M ����
		{
			cout << "> ������ ����ġ �׷����� ����� ���ϸ��� �Է��Ͻÿ�(�����quit) : ";
			cin >> fileName;
			

			if ( fileName == "quit" )
			{
				cout << "> ���α׷��� �����մϴ�." << endl;
				exit(1);
			}

			else if( fileName == "graph2.txt" )
			{
				g.fileRead( fileName ); // �����б�
				g.kruskal(g.getVertexNum());
			}

			else
			{
				cout << "> �ش� ���α׷��� ���ϸ��� [graph2.txt] �Դϴ�.." << endl;
				exit(1);
			}
		} // else if�� ( M�� ���� )


		else if ( choice == "T" ) // T ����
		{
			cout << "> ���� �׷����� ����� ���ϸ��� �Է��Ͻÿ�(�����quit) : ";
			cin >> fileName;
			

			if ( fileName == "quit" )
			{
				cout << "> ���α׷��� �����մϴ�." << endl;
				exit(1);
			}

			else if ( fileName == "graph3.txt" )
			{
				g.fileRead( fileName ); // ���� �б�
				g.topologicalSort(); cout << endl; // ������� ���
			}

			else
			{
				cout << "> �ش� ���α׷��� ���ϸ��� [graph3.txt] �Դϴ�.." << endl;
				exit(1);
			}
		} // else if�� ( T�� ���� )

		else if ( choice == "Q" ) // Q ����
		{
			cout << "> ���α׷��� �����մϴ�." << endl;
			exit(1);
		} // else if�� ( Q�� ���� )

		else // �� �� �Է�
			cout << "> S,M,T,Q�߿� �Է��Ͻʽÿ�." << endl;

		cout << endl;
	} // while��
	return 0;
} // main�޼ҵ� ��

