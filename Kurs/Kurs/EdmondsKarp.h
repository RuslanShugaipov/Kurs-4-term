#pragma once
#include "Graph.h"

//bubble sort function for character arrays
void BubbleSort(int VertexesNumber, char* Vertexes);

//the Edmonds-Karp algorithm, which works the same way as the Ford-Fulkerson
//algorithm, but performs a path search using the BFS
unsigned EdmondsKarp(int VertexesNumber, Graph& ThroughputCapacity);