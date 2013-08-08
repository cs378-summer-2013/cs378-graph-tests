// A unit test source that makes use of gtest
#include <iostream>         // ostream
#include <algorithm>        // equal
#include <cstring> // strcmp
#include <sstream> // ostringstream
#include <stdexcept> // invalid_argument
#include <string> // ==#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream> // ostringstream
#include <utility> // pair

#include "boost/graph/adjacency_list.hpp" // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort
/*
 * This is the gtest header.
 * The usual installation is in /usr/include/
 *
 * It's already installed there on the CS machines,
 * but if you've installed it elsewhere on your own,
 * there's no need to change this line.
 *
 * You just need to make sure to include the folder where
 * you put the gtest folder when compiling.
 */
#include "Graph.h"
#include "gtest/gtest.h"

//g++ -pedantic -std=c++0x -Wall TestStuff.c++ -o TestStuff -lgtest -lgtest_main -pthread


class MyGraphTest: public testing::Test{
protected:
	typedef typename boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>		graph_type;
	typedef typename graph_type::vertex_descriptor vertex_descriptor;
	typedef typename graph_type::edge_descriptor edge_descriptor;

	typedef typename graph_type::vertex_iterator vertex_iterator;
	typedef typename graph_type::edge_iterator edge_iterator;
	typedef typename graph_type::adjacency_iterator adjacency_iterator;

	typedef typename graph_type::vertices_size_type vertices_size_type;
	typedef typename graph_type::edges_size_type edges_size_type;
	graph_type g1;
	graph_type g2;
	graph_type g3;
	graph_type g4;
	graph_type g5;
	graph_type g6;
	
	// g1
	vertex_descriptor vdA;
	vertex_descriptor vdB;
	vertex_descriptor vdC;
	vertex_descriptor vdD;
	vertex_descriptor vdE;
	vertex_descriptor vdF;
	vertex_descriptor vdG;
	vertex_descriptor vdH;
	edge_descriptor edAB;
	edge_descriptor edAC;
	edge_descriptor edAE;
	edge_descriptor edBD;
	edge_descriptor edBE;
	edge_descriptor edCD;
	edge_descriptor edDE;
	edge_descriptor edDF;
	edge_descriptor edFD;
	edge_descriptor edFH;
	edge_descriptor edGH;
	
	//g3
	vertex_descriptor vdI;
	vertex_descriptor vdJ;
	vertex_descriptor vdK;
	vertex_descriptor vdL;
	vertex_descriptor vdM;
	vertex_descriptor vdN;
	vertex_descriptor vdO;
	vertex_descriptor vdP;
	edge_descriptor edIJ;
	edge_descriptor edIK;
	edge_descriptor edIM;
	edge_descriptor edJL;
	edge_descriptor edJM;
	edge_descriptor edKL;
	edge_descriptor edLM;
	edge_descriptor edLN;
	edge_descriptor edNL;
	edge_descriptor edNP;
	edge_descriptor edOP;
	
	//g4
	vertex_descriptor vdQ;
	vertex_descriptor vdR;
	edge_descriptor edQR;
	
	//g5
	vertex_descriptor vdS;
	vertex_descriptor vdT;
	vertex_descriptor vdU;
	vertex_descriptor vdV;
	vertex_descriptor vdW;
	vertex_descriptor vdX;
	vertex_descriptor vdY;
	vertex_descriptor vdZ;
	vertex_descriptor vdAA;
	vertex_descriptor vdBB;
	vertex_descriptor vdCC;
	edge_descriptor edBBCC;
	
	//g6
	vertex_descriptor vdAAA;
	vertex_descriptor vdBBB;
	vertex_descriptor vdCCC;
	vertex_descriptor vdDDD;
	vertex_descriptor vdEEE;
	vertex_descriptor vdFFF;
	vertex_descriptor vdGGG;
	vertex_descriptor vdHHH;
	edge_descriptor edAAABBB;
	edge_descriptor edAAACCC;
	edge_descriptor edAAAEEE;
	edge_descriptor edBBBDDD;
	edge_descriptor edBBBEEE;
	edge_descriptor edCCCDDD;
	edge_descriptor edDDDEEE;
	edge_descriptor edDDDFFF;
	edge_descriptor edFFFHHH;
	edge_descriptor edGGGHHH;
	
	//std::deque<int> v3;
	//######################
	typedef Graph<int>	graph_type2;
	typedef typename graph_type2::vertex_descriptor vertex_descriptor2;
	typedef typename graph_type2::edge_descriptor edge_descriptor2;

	typedef typename graph_type2::vertex_iterator vertex_iterator2;
	typedef typename graph_type2::edge_iterator edge_iterator2;
	typedef typename graph_type2::adjacency_iterator adjacency_iterator2;

	typedef typename graph_type2::vertices_size_type vertices_size_type2;
	typedef typename graph_type2::edges_size_type edges_size_type2;
	graph_type2 g12;
	graph_type2 g22;
	graph_type2 g32;
	graph_type2 g42;
	graph_type2 g52;
	graph_type2 g62;
	
	//g12
	vertex_descriptor2 vdA2;
	vertex_descriptor2 vdB2;
	vertex_descriptor2 vdC2;
	vertex_descriptor2 vdD2;
	vertex_descriptor2 vdE2;
	vertex_descriptor2 vdF2;
	vertex_descriptor2 vdG2;
	vertex_descriptor2 vdH2;
	edge_descriptor2 edAB2;
	edge_descriptor2 edAC2;
	edge_descriptor2 edAE2;
	edge_descriptor2 edBD2;
	edge_descriptor2 edBE2;
	edge_descriptor2 edCD2;
	edge_descriptor2 edDE2;
	edge_descriptor2 edDF2;
	edge_descriptor2 edFD2;
	edge_descriptor2 edFH2;
	edge_descriptor2 edGH2;
	
	//g32
	vertex_descriptor2 vdI2;
	vertex_descriptor2 vdJ2;
	vertex_descriptor2 vdK2;
	vertex_descriptor2 vdL2;
	vertex_descriptor2 vdM2;
	vertex_descriptor2 vdN2;
	vertex_descriptor2 vdO2;
	vertex_descriptor2 vdP2;
	edge_descriptor2 edIJ2;
	edge_descriptor2 edIK2;
	edge_descriptor2 edIM2;
	edge_descriptor2 edJL2;
	edge_descriptor2 edJM2;
	edge_descriptor2 edKL2;
	edge_descriptor2 edLM2;
	edge_descriptor2 edLN2;
	edge_descriptor2 edNL2;
	edge_descriptor2 edNP2;
	edge_descriptor2 edOP2;
	
	//g42
	vertex_descriptor2 vdQ2;
	vertex_descriptor2 vdR2;
	edge_descriptor2 edQR2;
	
	//g52
	vertex_descriptor2 vdS2;
	vertex_descriptor2 vdT2;
	vertex_descriptor2 vdU2;
	vertex_descriptor2 vdV2;
	vertex_descriptor2 vdW2;
	vertex_descriptor2 vdX2;
	vertex_descriptor2 vdY2;
	vertex_descriptor2 vdZ2;
	vertex_descriptor2 vdAA2;
	vertex_descriptor2 vdBB2;
	vertex_descriptor2 vdCC2;
	edge_descriptor2 edBBCC2;
	
	//g62
	vertex_descriptor2 vdAAA2;
	vertex_descriptor2 vdBBB2;
	vertex_descriptor2 vdCCC2;
	vertex_descriptor2 vdDDD2;
	vertex_descriptor2 vdEEE2;
	vertex_descriptor2 vdFFF2;
	vertex_descriptor2 vdGGG2;
	vertex_descriptor2 vdHHH2;
	edge_descriptor2 edAAABBB2;
	edge_descriptor2 edAAACCC2;
	edge_descriptor2 edAAAEEE2;
	edge_descriptor2 edBBBDDD2;
	edge_descriptor2 edBBBEEE2;
	edge_descriptor2 edCCCDDD2;
	edge_descriptor2 edDDDEEE2;
	edge_descriptor2 edDDDFFF2;
	edge_descriptor2 edFFFHHH2;
	edge_descriptor2 edGGGHHH2;

	virtual void SetUp(){     
	    //g1
	    vdA = add_vertex(g1);
	    vdB = add_vertex(g1);
	    vdC = add_vertex(g1);
	    vdD = add_vertex(g1);
	    vdE = add_vertex(g1);
	    vdF = add_vertex(g1);
	    vdG = add_vertex(g1);
	    vdH = add_vertex(g1);
	    edAB = add_edge(vdA, vdB, g1).first;
	    edAC = add_edge(vdA, vdC, g1).first;
	    edAE = add_edge(vdA, vdE, g1).first;
	    edBD = add_edge(vdB, vdD, g1).first;
	    edBE = add_edge(vdB, vdE, g1).first;
	    edCD = add_edge(vdC, vdD, g1).first;
	    edDE = add_edge(vdD, vdE, g1).first;
	    edDF = add_edge(vdD, vdF, g1).first;
	    edFD = add_edge(vdF, vdD, g1).first;
	    edFH = add_edge(vdF, vdH, g1).first;
	    edGH = add_edge(vdG, vdH, g1).first;
	    
	    //g3
	    vdI = add_vertex(g3);
	    vdJ = add_vertex(g3);
	    vdK = add_vertex(g3);
	    vdL = add_vertex(g3);
	    vdM = add_vertex(g3);
	    vdN = add_vertex(g3);
	    vdO = add_vertex(g3);
	    vdP = add_vertex(g3);
	    edIJ = add_edge(vdI, vdJ, g3).first;
	    edIK = add_edge(vdI, vdK, g3).first;
	    edIM = add_edge(vdI, vdM, g3).first;
	    edJL = add_edge(vdJ, vdL, g3).first;
	    edJM = add_edge(vdJ, vdM, g3).first;
	    edKL = add_edge(vdK, vdL, g3).first;
	    edLM = add_edge(vdL, vdM, g3).first;
	    edLN = add_edge(vdL, vdN, g3).first;
	    edNL = add_edge(vdN, vdL, g3).first;
	    edNP = add_edge(vdN, vdP, g3).first;
	    edOP = add_edge(vdO, vdP, g3).first;
	    
	    //g4
	    vdQ = add_vertex(g4);
	    vdR = add_vertex(g4);
	    edQR = add_edge(vdQ, vdR, g4).first;
	    
	    //g5
	    vdS = add_vertex(g5);
	    vdT = add_vertex(g5);
	    vdU = add_vertex(g5);
	    vdV = add_vertex(g5);
	    vdW = add_vertex(g5);
	    vdX = add_vertex(g5);
	    vdY = add_vertex(g5);
	    vdZ = add_vertex(g5);
	    vdAA = add_vertex(g5);
	    vdBB = add_vertex(g5);
	    vdCC = add_vertex(g5);
	    edBBCC = add_edge(vdBB, vdCC, g5).first;
	    
	    //g6
	    vdAAA = add_vertex(g6);
	    vdBBB = add_vertex(g6);
	    vdCCC = add_vertex(g6);
	    vdDDD = add_vertex(g6);
	    vdEEE = add_vertex(g6);
	    vdFFF = add_vertex(g6);
	    vdGGG = add_vertex(g6);
	    vdHHH = add_vertex(g6);
	    edAAABBB = add_edge(vdAAA, vdBBB, g6).first;
	    edAAACCC = add_edge(vdAAA, vdCCC, g6).first;
	    edAAAEEE = add_edge(vdAAA, vdEEE, g6).first;
	    edBBBDDD = add_edge(vdBBB, vdDDD, g6).first;
	    edBBBEEE = add_edge(vdBBB, vdEEE, g6).first;
	    edCCCDDD = add_edge(vdCCC, vdDDD, g6).first;
	    edDDDEEE = add_edge(vdDDD, vdEEE, g6).first;
	    edDDDFFF = add_edge(vdDDD, vdFFF, g6).first;
	    edFFFHHH = add_edge(vdFFF, vdHHH, g6).first;
	    edGGGHHH = add_edge(vdGGG, vdHHH, g6).first;

	    //##############################        
	    //g12
	    vdA2 = add_vertex(g12);
	    vdB2 = add_vertex(g12);
	    vdC2 = add_vertex(g12);
	    vdD2 = add_vertex(g12);
	    vdE2 = add_vertex(g12);
	    vdF2 = add_vertex(g12);
	    vdG2 = add_vertex(g12);
	    vdH2 = add_vertex(g12);
	    edAB2 = add_edge(vdA2, vdB2, g12).first;
	    edAC2 = add_edge(vdA2, vdC2, g12).first;
	    edAE2 = add_edge(vdA2, vdE2, g12).first;
	    edBD2 = add_edge(vdB2, vdD2, g12).first;
	    edBE2 = add_edge(vdB2, vdE2, g12).first;
	    edCD2 = add_edge(vdC2, vdD2, g12).first;
	    edDE2 = add_edge(vdD2, vdE2, g12).first;
	    edDF2 = add_edge(vdD2, vdF2, g12).first;
	    edFD2 = add_edge(vdF2, vdD2, g12).first;
	    edFH2 = add_edge(vdF2, vdH2, g12).first;
	    edGH2 = add_edge(vdG2, vdH2, g12).first;
	    
	    //g32
	    vdI2 = add_vertex(g32);
	    vdJ2 = add_vertex(g32);
	    vdK2 = add_vertex(g32);
	    vdL2 = add_vertex(g32);
	    vdM2 = add_vertex(g32);
	    vdN2 = add_vertex(g32);
	    vdO2 = add_vertex(g32);
	    vdP2 = add_vertex(g32);
	    edIJ2 = add_edge(vdI2, vdJ2, g32).first;
	    edIK2 = add_edge(vdI2, vdK2, g32).first;
	    edIM2 = add_edge(vdI2, vdM2, g32).first;
	    edJL2 = add_edge(vdJ2, vdL2, g32).first;
	    edJM2 = add_edge(vdJ2, vdM2, g32).first;
	    edKL2 = add_edge(vdK2, vdL2, g32).first;
	    edLM2 = add_edge(vdL2, vdM2, g32).first;
	    edLN2 = add_edge(vdL2, vdN2, g32).first;
	    edNL2 = add_edge(vdN2, vdL2, g32).first;
	    edNP2 = add_edge(vdN2, vdP2, g32).first;
	    edOP2 = add_edge(vdO2, vdP2, g32).first;
	    
	    //g42
	    vdQ2 = add_vertex(g42);
	    vdR2 = add_vertex(g42);
	    edQR2 = add_edge(vdQ2, vdR2, g42).first;
	    
	    //g52
	    vdS2 = add_vertex(g52);
	    vdT2 = add_vertex(g52);
	    vdU2 = add_vertex(g52);
	    vdV2 = add_vertex(g52);
	    vdW2 = add_vertex(g52);
	    vdX2 = add_vertex(g52);
	    vdY2 = add_vertex(g52);
	    vdZ2 = add_vertex(g52);
	    vdAA2 = add_vertex(g52);
	    vdBB2 = add_vertex(g52);
	    vdCC2 = add_vertex(g52);
	    edBBCC2 = add_edge(vdBB2, vdCC2, g52).first;
	    
	    //g62
	    vdAAA2 = add_vertex(g62);
	    vdBBB2 = add_vertex(g62);
	    vdCCC2 = add_vertex(g62);
	    vdDDD2 = add_vertex(g62);
	    vdEEE2 = add_vertex(g62);
	    vdFFF2 = add_vertex(g62);
	    vdGGG2 = add_vertex(g62);
	    vdHHH2 = add_vertex(g62);
	    edAAABBB2 = add_edge(vdAAA2, vdBBB2, g62).first;
	    edAAACCC2 = add_edge(vdAAA2, vdCCC2, g62).first;
	    edAAAEEE2 = add_edge(vdAAA2, vdEEE2, g62).first;
	    edBBBDDD2 = add_edge(vdBBB2, vdDDD2, g62).first;
	    edBBBEEE2 = add_edge(vdBBB2, vdEEE2, g62).first;
	    edCCCDDD2 = add_edge(vdCCC2, vdDDD2, g62).first;
	    edDDDEEE2 = add_edge(vdDDD2, vdEEE2, g62).first;
	    edDDDFFF2 = add_edge(vdDDD2, vdFFF2, g62).first;
	    edFFFHHH2 = add_edge(vdFFF2, vdHHH2, g62).first;
	    edGGGHHH2 = add_edge(vdGGG2, vdHHH2, g62).first;


	}
	
	virtual void TearDown() {
	}
};

//********************************************

 TEST_F(MyGraphTest, AddVertexTest1) {
	ASSERT_EQ(0, num_vertices(g2));
	vertex_descriptor q = 0;
	ASSERT_EQ(q, add_vertex(g2));
	ASSERT_EQ(1, num_vertices(g2));
	//#######################################
	ASSERT_EQ(0, num_vertices(g22));
	vertex_descriptor2 q2 = 0;
	ASSERT_EQ(q2, add_vertex(g22));
	ASSERT_EQ(1, num_vertices(g22));
}

 TEST_F(MyGraphTest, AddVertexTest2) {
	ASSERT_EQ(8, num_vertices(g1));
	vertex_descriptor q = 8;
	ASSERT_EQ(q, add_vertex(g1));
	ASSERT_EQ(9, num_vertices(g1));
	//#######################################
	ASSERT_EQ(8, num_vertices(g12));
	vertex_descriptor2 q2 = 8;
	ASSERT_EQ(q2, add_vertex(g12));
	ASSERT_EQ(9, num_vertices(g12));
}

//********************************************

 TEST_F(MyGraphTest, NumVerticesTest1) {
	ASSERT_EQ(0, num_vertices(g2));
	//#######################################
	ASSERT_EQ(0, num_vertices(g22));
}

 TEST_F(MyGraphTest, NumVerticesTest2) {
	ASSERT_EQ(8, num_vertices(g1));
	//#######################################
	ASSERT_EQ(8, num_vertices(g12));
}

//********************************************

 TEST_F(MyGraphTest, NumEdgesTest1) {
	ASSERT_EQ(0, num_edges(g2));
	//#######################################
	ASSERT_EQ(0, num_edges(g22));
}

 TEST_F(MyGraphTest, NumEdgesTest2) {
	ASSERT_EQ(11, num_edges(g1));
	//#######################################
	ASSERT_EQ(11, num_edges(g12));
}

//********************************************

 TEST_F(MyGraphTest, AddEdgeTest1) {
	ASSERT_EQ(0, num_edges(g2));
	vertex_descriptor q = add_vertex(g2);
	vertex_descriptor r = add_vertex(g2);
	std::pair<edge_descriptor, bool> p2 = add_edge(q, r, g2);
	ASSERT_EQ(source(edQR, g2), source(p2.first, g2));
	ASSERT_EQ(target(edQR, g2), target(p2.first, g2));
	//ASSERT_EQ(edQR, p2.first);
	ASSERT_EQ(true, p2.second);
	ASSERT_EQ(1, num_edges(g2));
	//#######################################
	ASSERT_EQ(0, num_edges(g22));
	vertex_descriptor2 q2 = add_vertex(g22);
	vertex_descriptor2 r2 = add_vertex(g22);
	std::pair<edge_descriptor2, bool> p22 = add_edge(q2, r2, g22);
	ASSERT_EQ(source(edQR2, g22), source(p22.first, g22));
	ASSERT_EQ(target(edQR2, g22), target(p22.first, g22));
	//ASSERT_EQ(false, p22.first == edQR2);
	ASSERT_EQ(true, p22.second);
	ASSERT_EQ(1, num_edges(g22));
}

 TEST_F(MyGraphTest, AddEdgeTest2) {
	ASSERT_EQ(11, num_edges(g1));
	std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g1);
	ASSERT_EQ(edAB, p.first);
	ASSERT_EQ(true, p.second == false);
	ASSERT_EQ(11, num_edges(g1));
	//#######################################
	ASSERT_EQ(11, num_edges(g12));
	std::pair<edge_descriptor2, bool> p2 = add_edge(vdA2, vdB2, g12);
	ASSERT_EQ(edAB2, p2.first);
	ASSERT_EQ(true, p2.second == false);
	ASSERT_EQ(11, num_edges(g12));
}

 TEST_F(MyGraphTest, AddEdgeTest3) {
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	vertex_descriptor q = vertex(100, g2);
	vertex_descriptor r = vertex(101, g2);
	ASSERT_EQ(0, num_vertices(g2));
	std::pair<edge_descriptor, bool> p2 = add_edge(q, r, g2);
	ASSERT_EQ(1, num_edges(g2));
	ASSERT_EQ(102, num_vertices(g2));
	//#######################################
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
	vertex_descriptor2 q2 = vertex(100, g22);
	vertex_descriptor2 r2 = vertex(101, g22);
	ASSERT_EQ(0, num_vertices(g22));
	std::pair<edge_descriptor2, bool> p22 = add_edge(q2, r2, g22);
	ASSERT_EQ(1, num_edges(g22));
	ASSERT_EQ(102, num_vertices(g22));
}

 TEST_F(MyGraphTest, AddEdgeTest4) {
	ASSERT_EQ(11, num_edges(g1));
	ASSERT_EQ(8, num_vertices(g1));
	vertex_descriptor q = vertex(100, g1);
	vertex_descriptor r = 1;
	ASSERT_EQ(8, num_vertices(g1));
	std::pair<edge_descriptor, bool> p2 = add_edge(q, r, g1);
	ASSERT_EQ(12, num_edges(g1));
	ASSERT_EQ(101, num_vertices(g1));
	//#######################################
	ASSERT_EQ(11, num_edges(g12));
	ASSERT_EQ(8, num_vertices(g12));
	vertex_descriptor2 q2 = vertex(100, g12);
	vertex_descriptor2 r2 = 1;
	ASSERT_EQ(8, num_vertices(g12));
	std::pair<edge_descriptor2, bool> p22 = add_edge(q2, r2, g12);
	ASSERT_EQ(12, num_edges(g12));
	ASSERT_EQ(101, num_vertices(g12));
}

 TEST_F(MyGraphTest, AddEdgeTest5) {
	ASSERT_EQ(11, num_edges(g1));
	ASSERT_EQ(8, num_vertices(g1));
	vertex_descriptor q = vertex(100, g2);
	vertex_descriptor r = 1;
	ASSERT_EQ(8, num_vertices(g1));
	std::pair<edge_descriptor, bool> p2 = add_edge(q, r, g1);
	ASSERT_EQ(12, num_edges(g1));
	ASSERT_EQ(101, num_vertices(g1));
	//#######################################
	ASSERT_EQ(11, num_edges(g12));
	ASSERT_EQ(8, num_vertices(g12));
	vertex_descriptor2 q2 = vertex(100, g22);
	vertex_descriptor2 r2 = 1;
	ASSERT_EQ(8, num_vertices(g12));
	std::pair<edge_descriptor2, bool> p22 = add_edge(q2, r2, g12);
	ASSERT_EQ(12, num_edges(g12));
	ASSERT_EQ(101, num_vertices(g12));
}

 TEST_F(MyGraphTest, AddEdgeTest6) {
	ASSERT_EQ(11, num_edges(g1));
	ASSERT_EQ(8, num_vertices(g1));
	vertex_descriptor q = 1;
	vertex_descriptor r = vertex(100, g2);
	ASSERT_EQ(8, num_vertices(g1));
	std::pair<edge_descriptor, bool> p2 = add_edge(q, r, g1);
	ASSERT_EQ(12, num_edges(g1));
	ASSERT_EQ(101, num_vertices(g1));
	//#######################################
	ASSERT_EQ(11, num_edges(g12));
	ASSERT_EQ(8, num_vertices(g12));
	vertex_descriptor2 q2 = 1;
	vertex_descriptor2 r2 = vertex(100, g22);
	ASSERT_EQ(8, num_vertices(g12));
	std::pair<edge_descriptor2, bool> p22 = add_edge(q2, r2, g12);
	ASSERT_EQ(12, num_edges(g12));
	ASSERT_EQ(101, num_vertices(g12));
}

 TEST_F(MyGraphTest, AddEdgeTest7) {
	ASSERT_EQ(11, num_edges(g1));
	std::pair<edge_descriptor, bool> p = add_edge(vdA, vdA, g1);
	ASSERT_EQ(0, source(p.first, g1));
	ASSERT_EQ(0, target(p.first, g1));
	ASSERT_EQ(true, p.second == true);
	ASSERT_EQ(12, num_edges(g1));
	//#######################################
	ASSERT_EQ(11, num_edges(g12));
	std::pair<edge_descriptor2, bool> p2 = add_edge(vdA2, vdA2, g12);
	ASSERT_EQ(0, source(p2.first, g12));
	ASSERT_EQ(0, target(p2.first, g12));
	ASSERT_EQ(true, p2.second == true);
	ASSERT_EQ(12, num_edges(g12));
}

//********************************************
/*
 TEST_F(MyGraphTest, AdjacenctVerticesTest1) {
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	//produces runtime-error
        //std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g2); //produces runtime-error
	
        //adjacency_iterator b = p.first; 
        //adjacency_iterator e = p.second;
        //ASSERT_EQ(true, b != e);
        //if (b != e) {
            //vertex_descriptor vd = *b;
            //ASSERT_EQ(true, vd == vdB);}
        //++b;
        //if (b != e) {
            //vertex_descriptor vd = *b;
            //ASSERT_EQ(true, vd == vdC);}
	//#######################################
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
	//produces runtime-error
        //std::pair<adjacency_iterator2, adjacency_iterator2> p2 = adjacent_vertices(vdA2, g22); //produces runtime-error
	
        //adjacency_iterator b2 = p2.first; 
        //adjacency_iterator e2 = p2.second;
        //ASSERT_EQ(true, b2 != e2);
        //if (b2 != e2) {
            //vertex_descriptor vd2 = *b2;
            //ASSERT_EQ(true, vd2 == vdB2);}
        //++b2;
        //if (b2 != e2) {
            //vertex_descriptor vd2 = *b2;
            //ASSERT_EQ(true, vd2 == vdC2);}
}
*/
 TEST_F(MyGraphTest, AdjacenctVerticesTest1) {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g1);
        adjacency_iterator b = p.first; 
        adjacency_iterator e = p.second;
        ASSERT_EQ(true, b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_EQ(true, vd == vdB);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_EQ(true, vd == vdC);}
	//#######################################
        std::pair<adjacency_iterator2, adjacency_iterator2> p2 = adjacent_vertices(vdA2, g12);
        adjacency_iterator2 b2 = p2.first; 
        adjacency_iterator2 e2 = p2.second;
        ASSERT_EQ(true, b2 != e2);
        if (b2 != e2) {
            vertex_descriptor2 vd2 = *b2;
            ASSERT_EQ(true, vd2 == vdB2);}
        ++b2;
        if (b2 != e2) {
            vertex_descriptor2 vd2 = *b2;
            ASSERT_EQ(true, vd2 == vdC2);}
}

 TEST_F(MyGraphTest, AdjacenctVerticesTest2) {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdQ, g4);
        adjacency_iterator b = p.first; 
        adjacency_iterator e = p.second;
        ASSERT_EQ(true, b != e);
        vertex_descriptor vd = *b;
        ASSERT_EQ(true, vd == vdR);
        ++b;
	ASSERT_EQ(true, b == e);
	
	add_edge(vdQ, vdQ, g4);
        p = adjacent_vertices(vdQ, g4);
        b = p.first; 
        e = p.second;
        ASSERT_EQ(true, b != e);
        vd = *b;
        ASSERT_EQ(true, vd == vdQ);
        ++b;
        vd = *b;
        ASSERT_EQ(true, vd == vdR);
	++b;
	ASSERT_EQ(true, b == e);
	
	//#######################################
        std::pair<adjacency_iterator2, adjacency_iterator2> p2 = adjacent_vertices(vdQ2, g42);
        adjacency_iterator2 b2 = p2.first; 
        adjacency_iterator2 e2 = p2.second;
        ASSERT_EQ(true, b2 != e2);
        vertex_descriptor vd2 = *b2;
        ASSERT_EQ(true, vd2 == vdR2);
        ++b2;
	ASSERT_EQ(true, b2 == e2);
	
	add_edge(vdQ2, vdQ2, g42);
        p2 = adjacent_vertices(vdQ2, g42);
        b2 = p2.first; 
        e2 = p2.second;
        ASSERT_EQ(true, b2 != e2);
        vd2 = *b2;
        ASSERT_EQ(true, vd2 == vdQ2);
        ++b2;
        vd2 = *b2;
        ASSERT_EQ(true, vd2 == vdR2);
	++b2;
	ASSERT_EQ(true, b2 == e2);
}

//********************************************

 TEST_F(MyGraphTest, EdgeTest1) {
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	// produces runtime-error
        //std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g2);
        //ASSERT_EQ(true, p.first  == edAB);
	//ASSERT_EQ(true, p.second == true);
	//#######################################
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	// produces runtime-error
        //std::pair<edge_descriptor2, bool> p2 = edge(vdA2, vdB2, g22);
        //ASSERT_EQ(true, p2.first  == edAB2);
	//ASSERT_EQ(true, p2.second == true);
}

 TEST_F(MyGraphTest, EdgeTest2) {
	ASSERT_EQ(0, source(edAB, g1));
	ASSERT_EQ(1, target(edAB, g1));
	ASSERT_EQ(11, num_edges(g1));
	ASSERT_EQ(8, num_vertices(g1));
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g1);
	ASSERT_EQ(11, num_edges(g1));
	ASSERT_EQ(8, num_vertices(g1));
        ASSERT_EQ(source(edAB, g1), source(p.first, g1));
        ASSERT_EQ(target(edAB, g1), target(p.first, g1));
	ASSERT_EQ(0, source(edAB, g1));
	ASSERT_EQ(1, target(edAB, g1));
        ASSERT_EQ(true, p.first  == edAB);
        ASSERT_EQ(true, p.second == true);
	//#######################################
	ASSERT_EQ(0, source(edAB2, g12));
	ASSERT_EQ(1, target(edAB2, g12));
	ASSERT_EQ(11, num_edges(g12));
	ASSERT_EQ(8, num_vertices(g12));
        std::pair<edge_descriptor2, bool> p2 = edge(vdA2, vdB2, g12);
	ASSERT_EQ(11, num_edges(g12));
	ASSERT_EQ(8, num_vertices(g12));
        ASSERT_EQ(source(edAB2, g12), source(p2.first, g12));
        ASSERT_EQ(target(edAB2, g12), target(p2.first, g12));
	ASSERT_EQ(0, source(edAB2, g12));
	ASSERT_EQ(1, target(edAB2, g12));
        ASSERT_EQ(true, p2.first  == edAB2);
        ASSERT_EQ(true, p2.second == true);
}

 TEST_F(MyGraphTest, EdgeTest3) {
	ASSERT_EQ(11, num_edges(g1));
	ASSERT_EQ(8, num_vertices(g1));
	ASSERT_EQ(9, vdBB);
	ASSERT_EQ(10, vdCC);
        //std::pair<edge_descriptor, bool> p = edge(vdBB, vdCC, g1);
	// ___ASSERT_EQ(11, num_edges(g1));
	//ASSERT_EQ(8, num_vertices(g1));
        //ASSERT_EQ(source(edBBCC, g1), source(p.first, g1));
        //ASSERT_EQ(target(edBBCC, g1), target(p.first, g1));
	//ASSERT_EQ(9, source(edBBCC, g1));
	//ASSERT_EQ(10, target(edBBCC, g1));
	
	// extra wrinkle/detail of edge_descriptor: why does/should the ASSERT_EQ below work??
        //ASSERT_EQ(false, p.first == edBBCC);
        //ASSERT_EQ(true, p.second == false);^^^
	//#######################################
	// ___
	//ASSERT_EQ(11, num_edges(g12));
	//ASSERT_EQ(8, num_vertices(g12));
	//ASSERT_EQ(9, vdBB2);
	//ASSERT_EQ(10, vdCC2);
        //std::pair<edge_descriptor2, bool> p2 = edge(vdBB2, vdCC2, g12);
	//ASSERT_EQ(11, num_edges(g12));
	//ASSERT_EQ(8, num_vertices(g12));
        //ASSERT_EQ(source(edBBCC2, g12), source(p2.first, g12));
        //ASSERT_EQ(target(edBBCC2, g12), target(p2.first, g12));
	//ASSERT_EQ(9, source(edBBCC2, g12));
	//ASSERT_EQ(10, target(edBBCC2, g12));
	// NOTICE: the assertion below fails b/c p2.first == edBBCC2 is true
        // ASSERT_EQ(false, p2.first == edBBCC2);
        //ASSERT_EQ(true, p2.second == false);
        // ^^^
}
// ^^^
//********************************************
// ___
 TEST_F(MyGraphTest, EdgesTest1) {
        std::pair<edge_iterator, edge_iterator> p = edges(g2);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        ASSERT_EQ(true, b == e);
	//#######################################
        std::pair<edge_iterator2, edge_iterator2> p2 = edges(g22);
        edge_iterator2                           b2 = p2.first;
        edge_iterator2                           e2 = p2.second;
        ASSERT_EQ(true, b2 == e2);
}

 TEST_F(MyGraphTest, EdgesTest2) {
        std::pair<edge_iterator, edge_iterator> p = edges(g1);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        ASSERT_EQ(true, b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            ASSERT_EQ(true, ed == edAB);}
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            ASSERT_EQ(true, ed == edAC);}
	//#######################################
        std::pair<edge_iterator2, edge_iterator2> p2 = edges(g12);
        edge_iterator2                           b2 = p2.first;
        edge_iterator2                           e2 = p2.second;
        ASSERT_EQ(true, b2 != e2);
        if (b2 != e2) {
            edge_descriptor2 ed2 = *b2;
            ASSERT_EQ(true, ed2 == edAB2);}
        ++b2;
        if (b2 != e2) {
            edge_descriptor2 ed2 = *b2;
            ASSERT_EQ(true, ed2 == edAC2);}
}

//********************************************

 TEST_F(MyGraphTest, SourceTest1) {
	// NOTICE: source() doesn't care if the 
	// edge_descriptor is in the graph that
	// you give it, so long as the 
	// edge_descriptor is in scope
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
        vertex_descriptor vd = source(edAB, g2);
        ASSERT_EQ(true, vd == vdA);
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	//#######################################
	// NOTICE: source() doesn't care if the 
	// edge_descriptor is in the graph that
	// you give it, so long as the 
	// edge_descriptor is in scope
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
        vertex_descriptor2 vd2 = source(edAB2, g22);
        ASSERT_EQ(true, vd2 == vdA2);
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
}

 TEST_F(MyGraphTest, SourceTest2) {
        vertex_descriptor vd = source(edAB, g1);
        ASSERT_EQ(true, vd == vdA);
	//#######################################
        vertex_descriptor2 vd2 = source(edAB2, g12);
        ASSERT_EQ(true, vd2 == vdA2);
}

//********************************************

 TEST_F(MyGraphTest, TargetTest1) {
	// NOTICE: target() doesn't care if the 
	// edge_descriptor is in the graph that
	// you give it, so long as the 
	// edge_descriptor is in scope
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
        vertex_descriptor vd = target(edAB, g2);
        ASSERT_EQ(true, vd == vdB);
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	//#######################################
	// NOTICE: target() doesn't care if the 
	// edge_descriptor is in the graph that
	// you give it, so long as the 
	// edge_descriptor is in scope
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
        vertex_descriptor2 vd2 = target(edAB2, g22);
        ASSERT_EQ(true, vd2 == vdB2);
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
}

 TEST_F(MyGraphTest, TargetTest2) {
        vertex_descriptor vd = target(edAB, g1);
        ASSERT_EQ(true, vd == vdB);
	//#######################################
        vertex_descriptor2 vd2 = target(edAB2, g12);
        ASSERT_EQ(true, vd2 == vdB2);
}

//********************************************

 TEST_F(MyGraphTest, VertexTest1) {
	//NOTICE: vertex() doesn't require that
	// the vertex be in the graph given to
	// it ie vertex(vertex_descriptor, graph)
   
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
        vertex_descriptor vd = vertex(0, g2);
        ASSERT_EQ(true, vd == vdA);
        ASSERT_EQ(true, vd == vdI);
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	//#######################################
	//NOTICE: vertex() doesn't require that
	// the vertex be in the graph given to
	// it ie vertex(vertex_descriptor, graph)
   
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
        vertex_descriptor2 vd2 = vertex(0, g22);
        ASSERT_EQ(true, vd2 == vdA2);
        ASSERT_EQ(true, vd2 == vdI2);
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
}

 TEST_F(MyGraphTest, VertexTest2) {
        vertex_descriptor vd = vertex(0, g1);
        ASSERT_EQ(true, vd == vdA);
	//#######################################
        vertex_descriptor2 vd2 = vertex(0, g12);
        ASSERT_EQ(true, vd2 == vdA2);
}

 TEST_F(MyGraphTest, VertexTest3) {
	// vertex() seems to act like a 
	// vertex_descriptor constructor
	int wayOutOfRange = 1000;
        vertex_descriptor vd = vertex(wayOutOfRange, g1);
        ASSERT_EQ(true, vd == wayOutOfRange);
	vertex_descriptor vd1 = vd;
	vd = 80;
        ASSERT_EQ(true, vd == 80);
        ASSERT_EQ(true, vd != wayOutOfRange);
        ASSERT_EQ(true, vd1 != 80);
        ASSERT_EQ(true, vd1 == wayOutOfRange);
	//#######################################
	// vertex() seems to act like a 
	// vertex_descriptor constructor
	int wayOutOfRange2 = 1000;
        vertex_descriptor2 vd2 = vertex(wayOutOfRange2, g12);
        ASSERT_EQ(true, vd2 == wayOutOfRange2);
	vertex_descriptor2 vd12 = vd2;
	vd2 = 80;
        ASSERT_EQ(true, vd2 == 80);
        ASSERT_EQ(true, vd2 != wayOutOfRange2);
        ASSERT_EQ(true, vd12 != 80);
        ASSERT_EQ(true, vd12 == wayOutOfRange2);
}

//********************************************

 TEST_F(MyGraphTest, VerticesTest1) {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g2);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ASSERT_EQ(true, b == e);
	//#######################################
        std::pair<vertex_iterator2, vertex_iterator2> p2 = vertices(g22);
        vertex_iterator2                             b2 = p2.first;
        vertex_iterator2                             e2 = p2.second;
        ASSERT_EQ(true, b2 == e2);
}

 TEST_F(MyGraphTest, VerticesTest2) {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g1);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ASSERT_EQ(true, b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_EQ(true, vd == vdA);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_EQ(true, vd == vdB);}
	//#######################################
        std::pair<vertex_iterator2, vertex_iterator2> p2 = vertices(g12);
        vertex_iterator2                             b2 = p2.first;
        vertex_iterator2                             e2 = p2.second;
        ASSERT_EQ(true, b2 != e2);
        if (b2 != e2) {
            vertex_descriptor vd2 = *b2;
            ASSERT_EQ(true, vd2 == vdA2);}
        ++b2;
        if (b2 != e2) {
            vertex_descriptor vd2 = *b2;
            ASSERT_EQ(true, vd2 == vdB2);}
}

//********************************************

  TEST_F(MyGraphTest, HasCycleTest1){
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	ASSERT_EQ(false, has_cycle(g2));
	ASSERT_EQ(0, num_edges(g2));
	ASSERT_EQ(0, num_vertices(g2));
	//#######################################
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
	ASSERT_EQ(false, has_cycle(g22));
	ASSERT_EQ(0, num_edges(g22));
	ASSERT_EQ(0, num_vertices(g22));
}

 TEST_F(MyGraphTest, HasCycleTest2) {
	ASSERT_EQ(true, has_cycle(g1));
	//#######################################
	ASSERT_EQ(true, has_cycle(g12));
}

  TEST_F(MyGraphTest, HasCycleTest3){
	ASSERT_EQ(1, num_edges(g4));
	ASSERT_EQ(2, num_vertices(g4));
	ASSERT_EQ(false, has_cycle(g4));
	ASSERT_EQ(1, num_edges(g4));
	ASSERT_EQ(2, num_vertices(g4));
	//#######################################
	ASSERT_EQ(1, num_edges(g42));
	ASSERT_EQ(2, num_vertices(g42));
	ASSERT_EQ(false, has_cycle(g42));
	ASSERT_EQ(1, num_edges(g42));
	ASSERT_EQ(2, num_vertices(g42));
}

  TEST_F(MyGraphTest, HasCycleTest4){
	ASSERT_EQ(10, num_edges(g6));
	ASSERT_EQ(8, num_vertices(g6));
	ASSERT_EQ(false, has_cycle(g6));
	ASSERT_EQ(10, num_edges(g6));
	ASSERT_EQ(8, num_vertices(g6));
	//#######################################
	ASSERT_EQ(10, num_edges(g62));
	ASSERT_EQ(8, num_vertices(g62));
	ASSERT_EQ(false, has_cycle(g62));
	ASSERT_EQ(10, num_edges(g62));
	ASSERT_EQ(8, num_vertices(g62));
}

 TEST_F(MyGraphTest, HasCycleTest5) {
	//add self-loop
	
	ASSERT_EQ(false, has_cycle(g6));
	
	ASSERT_EQ(10, num_edges(g6));
	ASSERT_EQ(8, num_vertices(g6));
	std::pair<edge_descriptor, bool> p = add_edge(vdAAA, vdAAA, g6);
	ASSERT_EQ(0, source(p.first, g6));
	ASSERT_EQ(0, target(p.first, g6));
	ASSERT_EQ(true, p.second == true);
	ASSERT_EQ(11, num_edges(g6));
	ASSERT_EQ(8, num_vertices(g6));
	
	ASSERT_EQ(true, has_cycle(g6));
	
	ASSERT_EQ(11, num_edges(g6));
	ASSERT_EQ(8, num_vertices(g6));
	//#######################################
	//add self-loop
	
	ASSERT_EQ(false, has_cycle(g62));
	
	ASSERT_EQ(10, num_edges(g62));
	ASSERT_EQ(8, num_vertices(g62));
	std::pair<edge_descriptor2, bool> p2 = add_edge(vdAAA2, vdAAA2, g62);
	ASSERT_EQ(0, source(p2.first, g62));
	ASSERT_EQ(0, target(p2.first, g62));
	ASSERT_EQ(true, p2.second == true);
	ASSERT_EQ(11, num_edges(g62));
	ASSERT_EQ(8, num_vertices(g62));
	
	ASSERT_EQ(true, has_cycle(g62));
	
	ASSERT_EQ(11, num_edges(g62));
	ASSERT_EQ(8, num_vertices(g62));
}

//********************************************

  TEST_F(MyGraphTest, TopologicalSortTest1){
        std::ostringstream out;
        topological_sort(g2, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(true, out.str() == "");
	//#######################################
        std::ostringstream out2;
        topological_sort(g22, std::ostream_iterator<vertex_descriptor2>(out2, " "));
        ASSERT_EQ(true, out2.str() == "");
}

 TEST_F(MyGraphTest, TopologicalSortTest2) {
        std::ostringstream out;
	try {
	    topological_sort(g1, std::ostream_iterator<vertex_descriptor>(out, " "));
	    ASSERT_EQ(false, true); // must fail if reaches this point
	} catch (const boost::not_a_dag& e){
	    ASSERT_EQ("The graph must be a DAG.",  std::string(e.what()));
	}
	//#######################################
        std::ostringstream out2;
	try {
	    topological_sort(g12, std::ostream_iterator<vertex_descriptor2>(out2, " "));
	    ASSERT_EQ(false, true); // must fail if reaches this point
	} catch (const boost::not_a_dag& e2){
	    ASSERT_EQ("The graph must be a DAG.",  std::string(e2.what()));
	}
}

  TEST_F(MyGraphTest, TopologicalSortTest3){
        std::ostringstream out;
        topological_sort(g4, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ("1 0 ",out.str());
	//#######################################
        std::ostringstream out2;
        topological_sort(g42, std::ostream_iterator<vertex_descriptor2>(out2, " "));
        ASSERT_EQ("1 0 ",out2.str());
}

  TEST_F(MyGraphTest, TopologicalSortTest4){
        std::ostringstream out;
        topological_sort(g6, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ("4 7 5 3 1 2 0 6 ", out.str());
	//#######################################
        std::ostringstream out2;
        topological_sort(g62, std::ostream_iterator<vertex_descriptor2>(out2, " "));
        ASSERT_EQ("4 7 5 3 1 2 0 6 ", out2.str());
}

//********************************************

  TEST_F(MyGraphTest, DefaultConstructorTest1){
      graph_type gr;
      ASSERT_EQ(0, num_vertices(gr));
      ASSERT_EQ(0, num_edges(gr));
      //#######################################
      graph_type2 gr2;
      ASSERT_EQ(0, num_vertices(gr2));
      ASSERT_EQ(0, num_edges(gr2));
  }

//********************************************

  TEST_F(MyGraphTest, ValidTest1){
      graph_type gr;
      ASSERT_EQ("the default constructor's assert(valid()) did not fail if this assert runs", "the default constructor's assert(valid()) did not fail if this assert runs");
      //#######################################
      graph_type2 gr2;
      ASSERT_EQ("the default constructor's assert(valid()) did not fail if this assert runs", "the default constructor's assert(valid()) did not fail if this assert runs");
  }

//********************************************

  TEST_F(MyGraphTest, HasCycleHelperTest1){
    std::vector<bool> explored;
    for (int i = 0; i < num_vertices(g1); ++i){
	explored.push_back(false);
    }
    bool result = false;
    ASSERT_EQ(true, has_cycle_helper(g1, 0, explored, result));
    //#######################################
    std::vector<bool> explored2;
    for (int i = 0; i < num_vertices(g12); ++i){
	explored2.push_back(false);
    }
    bool result2 = false;
    ASSERT_EQ(true, has_cycle_helper(g12, 0, explored, result2));
  }

  TEST_F(MyGraphTest, HasCycleHelperTest2){
    std::vector<bool> explored;
    for (int i = 0; i < num_vertices(g6); ++i){
	explored.push_back(false);
    }
    bool result = false;
    ASSERT_EQ(false, has_cycle_helper(g6, 0, explored, result));
    //#######################################
    std::vector<bool> explored2;
    for (int i = 0; i < num_vertices(g62); ++i){
	explored2.push_back(false);
    }
    bool result2 = false;
    ASSERT_EQ(false, has_cycle_helper(g62, 0, explored, result2));
  }

  TEST_F(MyGraphTest, HasCycleHelperTest3){
    std::vector<bool> explored;
    for (int i = 0; i < num_vertices(g5); ++i){
	explored.push_back(false);
    }
    bool result = false;
    ASSERT_EQ(false, has_cycle_helper(g5, 0, explored, result));
    //#######################################
    std::vector<bool> explored2;
    for (int i = 0; i < num_vertices(g52); ++i){
	explored2.push_back(false);
    }
    bool result2 = false;
    ASSERT_EQ(false, has_cycle_helper(g52, 0, explored, result2));
  }

//********************************************

  TEST_F(MyGraphTest, DefaultCopyConstructorTest1){
      graph_type gr(g4);
      ASSERT_EQ(2, num_vertices(gr));
      ASSERT_EQ(1, num_edges(gr));
      ASSERT_EQ(true, edge(vdQ, vdR, gr).second);
      //#######################################
      graph_type2 gr2(g42);
      ASSERT_EQ(2, num_vertices(gr2));
      ASSERT_EQ(1, num_edges(gr2));
      ASSERT_EQ(true, edge(vdQ2, vdR2, gr2).second);
  }

//********************************************

  TEST_F(MyGraphTest, DefualtCopyAssignmentTest1){
      g1 = g4;
      ASSERT_EQ(2, num_vertices(g1));
      ASSERT_EQ(1, num_edges(g1));
      ASSERT_EQ(true, edge(vdQ, vdR, g1).second);
      //#######################################
      g12 = g42;
      ASSERT_EQ(2, num_vertices(g12));
      ASSERT_EQ(1, num_edges(g12));
      ASSERT_EQ(true, edge(vdQ2, vdR2, g12).second);
  }