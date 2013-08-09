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
/*
template <typename T>
class TypeTest : public testing::Test {
	protected:
		typedef int value_type;
	
		T x;
		T y;

		TypeTest(): x(0), y(0){}
};*/

template <typename T>
class TypeTest : public testing::Test {
	protected:
	typedef  T		graph_type;
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
	}
	
	virtual void TearDown() {
	}
};

typedef testing::Types< Graph<int>, boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> > MyTypes;


TYPED_TEST_CASE(TypeTest, MyTypes);


TYPED_TEST(TypeTest, TemplateTypeEquals) { //testing the test
	ASSERT_EQ(1, 1);
}

//********************************************

 TYPED_TEST(TypeTest, AddVertexTest1) {
	ASSERT_EQ(0, num_vertices(this->g2));
	typename TestFixture::vertex_descriptor q = 0;
	ASSERT_EQ(q, add_vertex(this->g2));
	ASSERT_EQ(1, num_vertices(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, AddVertexTest2) {
	ASSERT_EQ(8, num_vertices(this->g1));
	typename TestFixture::vertex_descriptor q = 8;
	ASSERT_EQ(q, add_vertex(this->g1));
	ASSERT_EQ(9, num_vertices(this->g1));
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, NumVerticesTest1) {
	ASSERT_EQ(0, num_vertices(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, NumVerticesTest2) {
	ASSERT_EQ(8, num_vertices(this->g1));
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, NumEdgesTest1) {
	ASSERT_EQ(0, num_edges(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, NumEdgesTest2) {
	ASSERT_EQ(11, num_edges(this->g1));
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, AddEdgeTest1) {
	ASSERT_EQ(0, num_edges(this->g2));
	typename TestFixture::vertex_descriptor q = add_vertex(this->g2);
	typename TestFixture::vertex_descriptor r = add_vertex(this->g2);
	std::pair<typename TestFixture::edge_descriptor, bool> p2 = add_edge(q, r, this->g2);
	ASSERT_EQ(source(this->edQR, this->g2), source(p2.first, this->g2));
	ASSERT_EQ(target(this->edQR, this->g2), target(p2.first, this->g2));
	ASSERT_EQ(true, p2.second);
	ASSERT_EQ(1, num_edges(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, AddEdgeTest2) {
	ASSERT_EQ(11, num_edges(this->g1));
	std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g1);
	ASSERT_EQ(this->edAB, p.first);
	ASSERT_EQ(true, p.second == false);
	ASSERT_EQ(11, num_edges(this->g1));
	//#######################################
}

 TYPED_TEST(TypeTest, AddEdgeTest3) {
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
	typename TestFixture::vertex_descriptor q = vertex(100, this->g2);
	typename TestFixture::vertex_descriptor r = vertex(101, this->g2);
	ASSERT_EQ(0, num_vertices(this->g2));
	std::pair<typename TestFixture::edge_descriptor, bool> p2 = add_edge(q, r, this->g2);
	ASSERT_EQ(1, num_edges(this->g2));
	ASSERT_EQ(102, num_vertices(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, AddEdgeTest4) {
	ASSERT_EQ(11, num_edges(this->g1));
	ASSERT_EQ(8, num_vertices(this->g1));
	typename TestFixture::vertex_descriptor q = vertex(100, this->g1);
	typename TestFixture::vertex_descriptor r = 1;
	ASSERT_EQ(8, num_vertices(this->g1));
	std::pair<typename TestFixture::edge_descriptor, bool> p2 = add_edge(q, r, this->g1);
	ASSERT_EQ(12, num_edges(this->g1));
	ASSERT_EQ(101, num_vertices(this->g1));
	//#######################################
}

 TYPED_TEST(TypeTest, AddEdgeTest5) {
	ASSERT_EQ(11, num_edges(this->g1));
	ASSERT_EQ(8, num_vertices(this->g1));
	typename TestFixture::vertex_descriptor q = vertex(100, this->g2);
	typename TestFixture::vertex_descriptor r = 1;
	ASSERT_EQ(8, num_vertices(this->g1));
	std::pair<typename TestFixture::edge_descriptor, bool> p2 = add_edge(q, r, this->g1);
	ASSERT_EQ(12, num_edges(this->g1));
	ASSERT_EQ(101, num_vertices(this->g1));
	//#######################################
}

 TYPED_TEST(TypeTest, AddEdgeTest6) {
	ASSERT_EQ(11, num_edges(this->g1));
	ASSERT_EQ(8, num_vertices(this->g1));
	typename TestFixture::vertex_descriptor q = 1;
	typename TestFixture::vertex_descriptor r = vertex(100, this->g2);
	ASSERT_EQ(8, num_vertices(this->g1));
	std::pair<typename TestFixture::edge_descriptor, bool> p2 = add_edge(q, r, this->g1);
	ASSERT_EQ(12, num_edges(this->g1));
	ASSERT_EQ(101, num_vertices(this->g1));
	//#######################################
}

 TYPED_TEST(TypeTest, AddEdgeTest7) {
	ASSERT_EQ(11, num_edges(this->g1));
	std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdA, this->g1);
	ASSERT_EQ(0, source(p.first, this->g1));
	ASSERT_EQ(0, target(p.first, this->g1));
	ASSERT_EQ(true, p.second == true);
	ASSERT_EQ(12, num_edges(this->g1));
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, AdjacenctVerticesTest1) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g1);
        typename TestFixture::adjacency_iterator b = p.first; 
        typename TestFixture::adjacency_iterator e = p.second;
        ASSERT_EQ(true, b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_EQ(true, vd == this->vdB);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_EQ(true, vd == this->vdC);}
	//#######################################
}

 TYPED_TEST(TypeTest, AdjacenctVerticesTest2) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdQ, this->g4);
        typename TestFixture::adjacency_iterator b = p.first; 
        typename TestFixture::adjacency_iterator e = p.second;
        ASSERT_EQ(true, b != e);
        typename TestFixture::vertex_descriptor vd = *b;
        ASSERT_EQ(true, vd == this->vdR);
        ++b;
	ASSERT_EQ(true, b == e);
	
	add_edge(this->vdQ, this->vdQ, this->g4);
        p = adjacent_vertices(this->vdQ, this->g4);
        b = p.first; 
        e = p.second;
        ASSERT_EQ(true, b != e);
        vd = *b;
        ASSERT_EQ(true, vd == this->vdQ);
        ++b;
        vd = *b;
        ASSERT_EQ(true, vd == this->vdR);
	++b;
	ASSERT_EQ(true, b == e);
	
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, EdgeTest1) {
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
	// produces runtime-error
        //std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g2);
        //ASSERT_EQ(true, p.first  == this->edAB);
	//ASSERT_EQ(true, p.second == true);
	//#######################################
}

 TYPED_TEST(TypeTest, EdgeTest2) {
	ASSERT_EQ(0, source(this->edAB, this->g1));
	ASSERT_EQ(1, target(this->edAB, this->g1));
	ASSERT_EQ(11, num_edges(this->g1));
	ASSERT_EQ(8, num_vertices(this->g1));
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g1);
	ASSERT_EQ(11, num_edges(this->g1));
	ASSERT_EQ(8, num_vertices(this->g1));
        ASSERT_EQ(source(this->edAB, this->g1), source(p.first, this->g1));
        ASSERT_EQ(target(this->edAB, this->g1), target(p.first, this->g1));
	ASSERT_EQ(0, source(this->edAB, this->g1));
	ASSERT_EQ(1, target(this->edAB, this->g1));
        ASSERT_EQ(true, p.first  == this->edAB);
        ASSERT_EQ(true, p.second == true);
	//#######################################
}

 TYPED_TEST(TypeTest, EdgeTest3) {
	ASSERT_EQ(11, num_edges(this->g1));
	ASSERT_EQ(8, num_vertices(this->g1));
	ASSERT_EQ(9, this->vdBB);
	ASSERT_EQ(10, this->vdCC);
        //std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdBB, this->vdCC, this->g1);
	// ___ASSERT_EQ(11, num_edges(this->g1));
	//ASSERT_EQ(8, num_vertices(this->g1));
        //ASSERT_EQ(source(this->edBBCC, this->g1), source(p.first, this->g1));
        //ASSERT_EQ(target(this->edBBCC, this->g1), target(p.first, this->g1));
	//ASSERT_EQ(9, source(this->edBBCC, this->g1));
	//ASSERT_EQ(10, target(this->edBBCC, this->g1));
	
	// extra wrinkle/detail of edge_descriptor: why does/should the ASSERT_EQ below work??
        //ASSERT_EQ(false, p.first == this->edBBCC);
        //ASSERT_EQ(true, p.second == false);^^^
	//#######################################
}
// ^^^
//********************************************
// ___
 TYPED_TEST(TypeTest, EdgesTest1) {
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->g2);
        typename TestFixture::edge_iterator                           b = p.first;
        typename TestFixture::edge_iterator                           e = p.second;
        ASSERT_EQ(true, b == e);
	//#######################################
}

 TYPED_TEST(TypeTest, EdgesTest2) {
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->g1);
        typename TestFixture::edge_iterator                           b = p.first;
        typename TestFixture::edge_iterator                           e = p.second;
        ASSERT_EQ(true, b != e);
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            ASSERT_EQ(true, ed == this->edAB);}
        ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            ASSERT_EQ(true, ed == this->edAC);}
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, SourceTest1) {
	// NOTICE: source() doesn't care if the 
	// edge_descriptor is in the graph that
	// you give it, so long as the 
	// edge_descriptor is in scope
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
        typename TestFixture::vertex_descriptor vd = source(this->edAB, this->g2);
        ASSERT_EQ(true, vd == this->vdA);
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, SourceTest2) {
        typename TestFixture::vertex_descriptor vd = source(this->edAB, this->g1);
        ASSERT_EQ(true, vd == this->vdA);
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, TargetTest1) {
	// NOTICE: target() doesn't care if the 
	// edge_descriptor is in the graph that
	// you give it, so long as the 
	// edge_descriptor is in scope
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
        typename TestFixture::vertex_descriptor vd = target(this->edAB, this->g2);
        ASSERT_EQ(true, vd == this->vdB);
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, TargetTest2) {
        typename TestFixture::vertex_descriptor vd = target(this->edAB, this->g1);
        ASSERT_EQ(true, vd == this->vdB);
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, VertexTest1) {
	//NOTICE: vertex() doesn't require that
	// the vertex be in the graph given to
	// it ie vertex(typename TestFixture::vertex_descriptor, graph)
   
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
        typename TestFixture::vertex_descriptor vd = vertex(0, this->g2);
        ASSERT_EQ(true, vd == this->vdA);
        ASSERT_EQ(true, vd == this->vdI);
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, VertexTest2) {
        typename TestFixture::vertex_descriptor vd = vertex(0, this->g1);
        ASSERT_EQ(true, vd == this->vdA);
	//#######################################
}

 TYPED_TEST(TypeTest, VertexTest3) {
	// vertex() seems to act like a 
	// vertex_descriptor constructor
	int wayOutOfRange = 1000;
        typename TestFixture::vertex_descriptor vd = vertex(wayOutOfRange, this->g1);
        ASSERT_EQ(true, vd == wayOutOfRange);
	typename TestFixture::vertex_descriptor vd1 = vd;
	vd = 80;
        ASSERT_EQ(true, vd == 80);
        ASSERT_EQ(true, vd != wayOutOfRange);
        ASSERT_EQ(true, vd1 != 80);
        ASSERT_EQ(true, vd1 == wayOutOfRange);
	//#######################################
}

//********************************************

 TYPED_TEST(TypeTest, VerticesTest1) {
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g2);
        typename TestFixture::vertex_iterator                             b = p.first;
        typename TestFixture::vertex_iterator                             e = p.second;
        ASSERT_EQ(true, b == e);
	//#######################################
}

 TYPED_TEST(TypeTest, VerticesTest2) {
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g1);
        typename TestFixture::vertex_iterator                             b = p.first;
        typename TestFixture::vertex_iterator                             e = p.second;
        ASSERT_EQ(true, b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_EQ(true, vd == this->vdA);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_EQ(true, vd == this->vdB);}
	//#######################################
}

//********************************************

  TYPED_TEST(TypeTest, HasCycleTest1){
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
	ASSERT_EQ(false, has_cycle(this->g2));
	ASSERT_EQ(0, num_edges(this->g2));
	ASSERT_EQ(0, num_vertices(this->g2));
	//#######################################
}

 TYPED_TEST(TypeTest, HasCycleTest2) {
	ASSERT_EQ(true, has_cycle(this->g1));
	//#######################################
}

  TYPED_TEST(TypeTest, HasCycleTest3){
	ASSERT_EQ(1, num_edges(this->g4));
	ASSERT_EQ(2, num_vertices(this->g4));
	ASSERT_EQ(false, has_cycle(this->g4));
	ASSERT_EQ(1, num_edges(this->g4));
	ASSERT_EQ(2, num_vertices(this->g4));
	//#######################################
}

  TYPED_TEST(TypeTest, HasCycleTest4){
	ASSERT_EQ(10, num_edges(this->g6));
	ASSERT_EQ(8, num_vertices(this->g6));
	ASSERT_EQ(false, has_cycle(this->g6));
	ASSERT_EQ(10, num_edges(this->g6));
	ASSERT_EQ(8, num_vertices(this->g6));
	//#######################################
}

 TYPED_TEST(TypeTest, HasCycleTest5) {
	//add self-loop
	
	ASSERT_EQ(false, has_cycle(this->g6));
	
	ASSERT_EQ(10, num_edges(this->g6));
	ASSERT_EQ(8, num_vertices(this->g6));
	std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdAAA, this->vdAAA, this->g6);
	ASSERT_EQ(0, source(p.first, this->g6));
	ASSERT_EQ(0, target(p.first, this->g6));
	ASSERT_EQ(true, p.second == true);
	ASSERT_EQ(11, num_edges(this->g6));
	ASSERT_EQ(8, num_vertices(this->g6));
	
	ASSERT_EQ(true, has_cycle(this->g6));
	
	ASSERT_EQ(11, num_edges(this->g6));
	ASSERT_EQ(8, num_vertices(this->g6));
	//#######################################
}

//********************************************

  TYPED_TEST(TypeTest, TopologicalSortTest1){
        std::ostringstream out;
        topological_sort(this->g2, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
        ASSERT_EQ(true, out.str() == "");
	//#######################################
}

 TYPED_TEST(TypeTest, TopologicalSortTest2) {
        std::ostringstream out;
	try {
	    topological_sort(this->g1, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	    ASSERT_EQ(false, true); // must fail if reaches this point
	} catch (const boost::not_a_dag& e){
	    ASSERT_EQ("The graph must be a DAG.",  std::string(e.what()));
	}
	//#######################################
}

  TYPED_TEST(TypeTest, TopologicalSortTest3){
        std::ostringstream out;
        topological_sort(this->g4, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
        ASSERT_EQ("1 0 ",out.str());
	//#######################################
}

  TYPED_TEST(TypeTest, TopologicalSortTest4){
        std::ostringstream out;
        topological_sort(this->g6, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
        ASSERT_EQ("4 7 5 3 1 2 0 6 ", out.str());
	//#######################################
}

//********************************************

  TYPED_TEST(TypeTest, DefaultConstructorTest1){
      typename TestFixture::graph_type gr;
      ASSERT_EQ(0, num_vertices(gr));
      ASSERT_EQ(0, num_edges(gr));
      //#######################################
  }

//********************************************

  TYPED_TEST(TypeTest, ValidTest1){
      typename TestFixture::graph_type gr;
      ASSERT_EQ("the default constructor's assert(valid()) did not fail if this assert runs", "the default constructor's assert(valid()) did not fail if this assert runs");
      //#######################################
  }

//********************************************

  TYPED_TEST(TypeTest, HasCycleHelperTest1){
    std::vector<bool> explored;
    for (int i = 0; i < num_vertices(this->g1); ++i){
	explored.push_back(false);
    }
    bool result = false;
    ASSERT_EQ(true, has_cycle_helper(this->g1, 0, explored, result));
    //#######################################
  }

  TYPED_TEST(TypeTest, HasCycleHelperTest2){
    std::vector<bool> explored;
    for (int i = 0; i < num_vertices(this->g6); ++i){
	explored.push_back(false);
    }
    bool result = false;
    ASSERT_EQ(false, has_cycle_helper(this->g6, 0, explored, result));
    //#######################################
  }

  TYPED_TEST(TypeTest, HasCycleHelperTest3){
    std::vector<bool> explored;
    for (int i = 0; i < num_vertices(this->g5); ++i){
	explored.push_back(false);
    }
    bool result = false;
    ASSERT_EQ(false, has_cycle_helper(this->g5, 0, explored, result));
    //#######################################
  }

//********************************************

  TYPED_TEST(TypeTest, DefaultCopyConstructorTest1){
      typename TestFixture::graph_type gr(this->g4);
      ASSERT_EQ(2, num_vertices(gr));
      ASSERT_EQ(1, num_edges(gr));
      ASSERT_EQ(true, edge(this->vdQ, this->vdR, gr).second);
      //#######################################
  }

//********************************************

  TYPED_TEST(TypeTest, DefualtCopyAssignmentTest1){
      this->g1 = this->g4;
      ASSERT_EQ(2, num_vertices(this->g1));
      ASSERT_EQ(1, num_edges(this->g1));
      ASSERT_EQ(true, edge(this->vdQ, this->vdR, this->g1).second);
      //#######################################
  }