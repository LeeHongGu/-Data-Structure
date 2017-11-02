
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
		cout << "프로그램을 선택하세요 \n[S]earch / [M]inimum cost spanning tree / [T]opological Sort / [Q]uit : ";
		cin >> choice;

		
		if ( choice == "S" ) // S 선택
		{
			cout << "> 무방향 그래프가 저장된 파일명을 입력하시오(종료는quit) : ";
			cin >> fileName;

			if ( fileName == "quit" )
			{
				cout << "> 프로그램을 종료합니다." << endl;
				exit(1);
			}

			else if ( fileName == "graph1.txt" )
			{
				g.fileRead( fileName ); // 파일 읽기

				g.printAdjacencyMatrix(); cout << endl; // 인접행렬 표현
				g.printAdjacencyList(); cout << endl; // 인접리스트 표현

				g.printDFS(); cout << endl; // 인접행렬 DFS 출력 
				g.printBFS(0); cout << endl; // 인접행렬 BFS 출력

				g.printListDFS(); // 인접리스트 DFS 출력
				g.printListBFS(0); // 인접리스트 BFS 출력
			}

			else
			{
				cout << "> 해당 프로그램의 파일명은 [graph1.txt] 입니다.." << endl;
				exit(1);
			}
		} // if끝 ( S를 선택 )


		else if ( choice == "M" ) // M 선택
		{
			cout << "> 무방향 가중치 그래프가 저장된 파일명을 입력하시오(종료는quit) : ";
			cin >> fileName;
			

			if ( fileName == "quit" )
			{
				cout << "> 프로그램을 종료합니다." << endl;
				exit(1);
			}

			else if( fileName == "graph2.txt" )
			{
				g.fileRead( fileName ); // 파일읽기
				g.kruskal(g.getVertexNum());
			}

			else
			{
				cout << "> 해당 프로그램의 파일명은 [graph2.txt] 입니다.." << endl;
				exit(1);
			}
		} // else if끝 ( M을 선택 )


		else if ( choice == "T" ) // T 선택
		{
			cout << "> 방향 그래프가 저장된 파일명을 입력하시오(종료는quit) : ";
			cin >> fileName;
			

			if ( fileName == "quit" )
			{
				cout << "> 프로그램을 종료합니다." << endl;
				exit(1);
			}

			else if ( fileName == "graph3.txt" )
			{
				g.fileRead( fileName ); // 파일 읽기
				g.topologicalSort(); cout << endl; // 위상순서 출력
			}

			else
			{
				cout << "> 해당 프로그램의 파일명은 [graph3.txt] 입니다.." << endl;
				exit(1);
			}
		} // else if끝 ( T를 선택 )

		else if ( choice == "Q" ) // Q 선택
		{
			cout << "> 프로그램을 종료합니다." << endl;
			exit(1);
		} // else if끝 ( Q를 선택 )

		else // 그 외 입력
			cout << "> S,M,T,Q중에 입력하십시오." << endl;

		cout << endl;
	} // while끝
	return 0;
} // main메소드 끝

