#include "Graph.h"

Graph::Graph(unsigned V)
{
	this->V = V;
	V_E = new unsigned* [V];
	for (unsigned i = 0; i < V; ++i)
		V_E[i] = new unsigned[V];
	for (unsigned k = 0; k < V; ++k)
		for (unsigned l = 0; l < V; ++l)
			V_E[k][l] = 0;
}

Graph::~Graph()
{
	for (unsigned i = 0; i < V; ++i)
		delete[] V_E[i];

	delete[] V_E;
}

void Graph::SetValue(unsigned V1_number, unsigned V2_number, unsigned value)
{
	V_E[V1_number][V2_number] = value;
}

unsigned Graph::GetValue(unsigned V1_number, unsigned V2_number)
{
	return V_E[V1_number][V2_number];
}

LinkedList<unsigned>* Graph::bfs(Graph& Flow)
{
	LinkedList<unsigned> queue;
	LinkedList<unsigned>* path = new LinkedList<unsigned>;
	unsigned* level = new unsigned[V];
	bool* visited = new bool[V];
	std::fill(visited, visited + V, false);

	level[0] = 0;
	queue.push_back(0);
	visited[0] = true;
	while (queue.isEmpty())
	{
		unsigned u = queue.peek();
		queue.pop_front();
		for (unsigned i = 0; i < V; i++)
		{
			if (u == i)
				continue;
			unsigned v = V_E[u][i];
			unsigned v2 = V_E[i][u];
			unsigned v0 = Flow.GetValue(u, i);
			unsigned v1 = Flow.GetValue(i, u);
			if (!visited[i] && ((v != v0) || ((v2 != v1) && v1 != 0)))
			{
				queue.push_back(i);
				visited[i] = true;
				level[i] = level[u] + 1;
			}
		}
	}

	int maxLevel = level[V - 1];
	path->push_front(V - 1);
	while (maxLevel != 0 && maxLevel >= 0)
	{
		for (unsigned j = 0; j < V; ++j)
		{
			unsigned v = V_E[j][path->peek()];
			unsigned v2 = V_E[path->peek()][j];
			unsigned v0 = Flow.GetValue(j, path->peek());
			unsigned v1 = Flow.GetValue(path->peek(), j);
			if (level[j] == maxLevel - 1 && ((v != v0) || ((v2 != v1) && v1 != 0)))
			{
				if (level[j] == maxLevel - 1)
				{
					path->push_front(j);
					maxLevel--;
					break;
				}
			}
		}
	}

	delete[] level;
	delete[] visited;

	return path;
}
