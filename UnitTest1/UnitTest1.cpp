#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <fstream>
#include <limits>
#include "../Lab12_PDC/Lab12_PDC.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestReadGraph)
		{
			// ��������� ��������� ����� ��� �����
			std::ofstream file("test_graph.txt");
			file << "5 6\n";
			file << "1 2 7\n";
			file << "1 3 9\n";
			file << "1 5 14\n";
			file << "2 3 10\n";
			file << "2 4 15\n";
			file << "3 4 11\n";
			file.close();

			// ���������� �����
			std::vector<std::vector<Edge>> graph;
			int n;
			readGraph("test_graph.txt", graph, n);

			// �������� ������� ������ � �����
			Assert::AreEqual(5, n, L"Incorrect number of vertices.");
			Assert::AreEqual(size_t(3), graph[1].size(), L"Incorrect number of edges from vertex 1.");
			Assert::AreEqual(size_t(2), graph[2].size(), L"Incorrect number of edges from vertex 2.");

			// �������� ���������� �����
			Assert::AreEqual(2, graph[1][0].to, L"Incorrect edge from vertex 1.");
			Assert::AreEqual(7, graph[1][0].weight, L"Incorrect weight for edge (1, 2).");
		}

		TEST_METHOD(TestDijkstra)
		{
			// ��������� ����� ������ ��� �����
			int n = 5;
			std::vector<std::vector<Edge>> graph(n + 1);
			graph[1].push_back({ 2, 7 });
			graph[1].push_back({ 3, 9 });
			graph[1].push_back({ 5, 14 });
			graph[2].push_back({ 3, 10 });
			graph[2].push_back({ 4, 15 });
			graph[3].push_back({ 4, 11 });

			// ��������� ��������� �������� �� ������� 1
			std::vector<int> distances = dijkstra(graph, 1);

			// �������� ����������
			Assert::AreEqual(0, distances[1], L"Distance from 1 to 1 should be 0.");
			Assert::AreEqual(7, distances[2], L"Distance from 1 to 2 should be 7.");
			Assert::AreEqual(9, distances[3], L"Distance from 1 to 3 should be 9.");
			Assert::AreEqual(20, distances[4], L"Distance from 1 to 4 should be 20.");
			Assert::AreEqual(14, distances[5], L"Distance from 1 to 5 should be 14.");
		}

		TEST_METHOD(TestNoPath)
		{
			// ��������� ����� ������ � ���������� ��������
			int n = 3;
			std::vector<std::vector<Edge>> graph(n + 1);
			graph[1].push_back({ 2, 10 });
			// ������� 3 ���������

			// ��������� ��������� �������� �� ������� 1
			std::vector<int> distances = dijkstra(graph, 1);

			// ��������, �� �� ��������� ������� 3 ������� - ������������
			Assert::AreEqual(INF, distances[3], L"Distance to unreachable vertex should be INF.");
		}
	};
}
