#pragma once

class Vertex
{
friend class Graph;
private:
	int vertex1; // ����1
	int vertex2; // ����2
	int weight; // ����ġ

public:
	Vertex() { }
	Vertex(int v1, int v2) { this -> vertex1 = v1, this -> vertex2 = v2; }
	Vertex(int v1, int v2, int w) { this -> vertex1 = v1, this -> vertex2 = v2; this -> weight = w; }
	~Vertex() { }

	// set, get
	void setVertex1(int v1) { this -> vertex1 = v1; }
	void setVertex2(int v2) { this -> vertex2 = v2; }
	void setWeight(int w) { this -> weight = w; }
	int getVertex1() { return vertex1; }
	int getVertex2() { return vertex2; }
	int getWeight() { return weight; }
};