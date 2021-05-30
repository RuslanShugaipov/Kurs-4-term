#pragma once
#include "LinkedList.h"

//class for a creating graph in the form of matrix
class Graph
{
	//all matrices are square, so we store the value of only one dimension
	unsigned V;
	unsigned** V_E;

public:

	//constructor with a parameter that sets all matrix values to zeros
	Graph(unsigned V);

	//destructor
	~Graph();

	//function for setting a value to a matrix
	void SetValue(unsigned V1_number, unsigned V2_number, unsigned value);

	//function for getting a value from a matrix
	unsigned GetValue(unsigned V1_number, unsigned V2_number);

	//a function that performs a bfs. Works with two objects of the Graph class, one of
	//which is throughput, the other is flow
	LinkedList<unsigned>* bfs(Graph& Flow);
};