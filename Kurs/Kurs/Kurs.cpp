#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "LinkedList.h"
#include "EdmondsKarp.h"

int main()
{
	try
	{
		ifstream read("Test4.txt");
		if (!read.is_open())
			throw std::exception("File not found");

		//we read the file and fill the Vertexes array with the names of the vertexes
		char ch = ' ';
		int VertexesNumber = 0;
		string TempVertexes = "";
		while (!read.eof())
		{
			ch = read.get();
			if (ch == ' ' || isdigit(ch) || ch == '\n')
				continue;
			if (!isdigit(ch))
			{
				for (int i = 0; i < VertexesNumber; ++i)
				{
					if (TempVertexes[i] == ch)
					{
						ch = ' ';
						break;
					}
				}
				if (ch == ' ')
					continue;
				else
				{
					TempVertexes += ch;
					VertexesNumber++;
				}
			}
		}

		VertexesNumber = VertexesNumber - 1;
		char* Vertexes = new char[VertexesNumber];
		for (int k = 0; k < VertexesNumber; ++k)
			Vertexes[k] = TempVertexes[k];

		BubbleSort(VertexesNumber, Vertexes);

		//we read the file and fill the Graph structure with the throughput values for each edge from the file
		read.clear();
		read.seekg(0, ios::beg);
		string number = "";
		unsigned from_vertex_number = 0, to_vertex_number = 0;
		Graph* ThroughputCapacity = new Graph(VertexesNumber);
		while (!read.eof())
		{
			ch = read.get();
			if (ch == '\n' || ch == ' ')
				continue;
			else if (!isdigit(ch))
			{

				for (unsigned i = 0; i < VertexesNumber; ++i)
				{
					if (Vertexes[i] == ch)
						from_vertex_number = i;
				}
				ch = read.get();
				ch = read.get();
				for (unsigned i = 0; i < VertexesNumber; ++i)
				{
					if (Vertexes[i] == ch)
						to_vertex_number = i;
				}
			}
			else if (isdigit(ch))
			{
				number.push_back(ch);
				while (isdigit(ch = read.get()))
					number.push_back(ch);
				ThroughputCapacity->SetValue(from_vertex_number, to_vertex_number, atoi(number.c_str()));
				number.clear();
				if (read.eof())
					break;
			}
		}

		std::cout << "Maxflow: " << EdmondsKarp(VertexesNumber, *ThroughputCapacity);

		delete ThroughputCapacity;
		delete[] Vertexes;
		read.close();
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	return 0;
}