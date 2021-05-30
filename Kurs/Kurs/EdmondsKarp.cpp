#include "EdmondsKarp.h"

void BubbleSort(int VertexesNumber, char* Vertexes)
{
	for (int k = 0; k < VertexesNumber - 1; ++k)
	{
		for (int l = 0; l < VertexesNumber - 1; ++l)
		{
			if (Vertexes[l] > Vertexes[l + 1] && (Vertexes[l] != 'S' && Vertexes[l + 1] != 'T'))
			{
				char temp = Vertexes[l];
				Vertexes[l] = Vertexes[l + 1];
				Vertexes[l + 1] = temp;
			}
		}
	}
}

unsigned EdmondsKarp(int VertexesNumber, Graph& ThroughputCapacity)
{
	Graph* Flow = new Graph(VertexesNumber);
	LinkedList<unsigned>* ShortestPath = new LinkedList<unsigned>;
	ShortestPath = ThroughputCapacity.bfs(*Flow);
	int* ResidualThroughput = new int[ShortestPath->get_size() - 1];
	while (ShortestPath->isEmpty() || ShortestPath->get_size() == 1)
	{
		ShortestPath = ThroughputCapacity.bfs(*Flow);
		ResidualThroughput = new int[ShortestPath->get_size() - 1];
		if (!ShortestPath->isEmpty() || ShortestPath->get_size() == 1)
			break;
		for (int i = 0; i < ShortestPath->get_size() - 1; ++i)
		{
			unsigned c_f_to = ThroughputCapacity.GetValue(ShortestPath->at(i), ShortestPath->at(i + 1));
			unsigned c_f_from = ThroughputCapacity.GetValue(ShortestPath->at(i + 1), ShortestPath->at(i));
			if (c_f_to != 0)
				ResidualThroughput[i] = c_f_to - Flow->GetValue(ShortestPath->at(i), ShortestPath->at(i + 1));
			else if (c_f_from != 0)
				ResidualThroughput[i] = Flow->GetValue(ShortestPath->at(i + 1), ShortestPath->at(i));
			else
				ResidualThroughput = 0;
		}
		unsigned MinC_f = ResidualThroughput[0];
		for (int i = 1; i < ShortestPath->get_size() - 1; ++i)
			if (ResidualThroughput[i] < MinC_f)
				MinC_f = ResidualThroughput[i];
		for (int i = 0; i < ShortestPath->get_size() - 1; ++i)
		{
			unsigned to = Flow->GetValue(ShortestPath->at(i), ShortestPath->at(i + 1));
			unsigned from = Flow->GetValue(ShortestPath->at(i + 1), ShortestPath->at(i));
			if (from == 0)
				Flow->SetValue(ShortestPath->at(i), ShortestPath->at(i + 1), to + MinC_f);
			else
				Flow->SetValue(ShortestPath->at(i + 1), ShortestPath->at(i), from - MinC_f);
		}
	}

	unsigned MaxFlow = 0;
	for (int i = 0; i < VertexesNumber; ++i)
	{
		if (Flow->GetValue(0, i) != 0)
			MaxFlow += Flow->GetValue(0, i);
	}

	delete[] ResidualThroughput;
	delete ShortestPath;
	delete Flow;

	return MaxFlow;
}