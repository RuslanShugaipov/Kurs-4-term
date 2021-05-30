#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Руслан\source\repos\Kurs\Kurs\EdmondsKarp.cpp"
#include "C:\Users\Руслан\source\repos\Kurs\Kurs\Graph.cpp"
#include "C:\Users\Руслан\source\repos\Kurs\Kurs\LinkedList.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KursTest
{
	TEST_CLASS(KursTest)
	{
	public:
		
		TEST_METHOD(SetValueTest)
		{
				Graph TestGraph((unsigned)2);
				TestGraph.SetValue(0, 0, 1);
				TestGraph.SetValue(0, 1, 2);
				TestGraph.SetValue(1, 0, 3);
				TestGraph.SetValue(1, 1, 4);

				Assert::AreEqual(TestGraph.GetValue(0, 0), (unsigned)1);
				Assert::AreEqual(TestGraph.GetValue(0, 1), (unsigned)2);
				Assert::AreEqual(TestGraph.GetValue(1, 0), (unsigned)3);
				Assert::AreEqual(TestGraph.GetValue(1, 1), (unsigned)4);
		}

		TEST_METHOD(GetValueTest)
		{
			Graph TestGraph((unsigned)2);
			TestGraph.SetValue(0, 0, 1);
			TestGraph.SetValue(0, 1, 2);
			TestGraph.SetValue(1, 0, 3);
			TestGraph.SetValue(1, 1, 4);

			Assert::AreEqual(TestGraph.GetValue(0, 0), (unsigned)1);
			Assert::AreEqual(TestGraph.GetValue(0, 1), (unsigned)2);
			Assert::AreNotEqual(TestGraph.GetValue(1, 0), (unsigned)6);
			Assert::AreNotEqual(TestGraph.GetValue(1, 1), (unsigned)7);
		}

		TEST_METHOD(bfsTest)
		{
			Graph *V_E = new Graph(3);
			V_E->SetValue(0, 0, 0);
			V_E->SetValue(0, 1, 1);
			V_E->SetValue(0, 2, 1);
			V_E->SetValue(1, 0, 0);
			V_E->SetValue(1, 1, 0);
			V_E->SetValue(1, 2, 1);
			V_E->SetValue(2, 0, 0);
			V_E->SetValue(2, 1, 0);
			V_E->SetValue(2, 2, 0);
			Graph *Flow = new Graph(3);
			LinkedList<unsigned> *path = V_E->bfs(*Flow);
			Assert::AreEqual(path->at(0), 0);
			Assert::AreEqual(path->at(1), 2);
		}

		TEST_METHOD(BubbleSortTest)
		{
			char* array = new char[4]{ 'D', 'C', 'B', 'A' };
			BubbleSort(4, array);
			char testArray[4] = { 'A', 'B', 'C', 'D' };
			for (int i = 0; i < 4; ++i)
			{
				Assert::AreEqual(array[i], testArray[i]);
			}
		}

		TEST_METHOD(EdmondsKarpTest)
		{
			ifstream read("C:\\Users\\Руслан\\source\\repos\\Kurs\\KursTest\\Test1.txt");
			if (!read.is_open())
				return;

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

			unsigned MaxFlow = EdmondsKarp(VertexesNumber, *ThroughputCapacity);

			delete ThroughputCapacity;
			delete[] Vertexes;
			read.close();
			
			Assert::AreEqual(MaxFlow, (unsigned)55);
		}
	};
}
