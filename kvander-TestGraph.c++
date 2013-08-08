// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

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
 
#include <sstream> // ostringstream
#include <iterator> // ostream_iterator
#include <sstream> // ostringstream
#include <utility> // pair

#include "boost/graph/adjacency_list.hpp" // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "Graph.h"
#include "gtest/gtest.h"

/*
To test the program:
    g++ -pedantic -std=c++0x -Wall TestStuff.c++ -o TestStuff -lgtest -lgtest_main -pthread
*/

using namespace std;

class GraphTester: public testing::Test {
protected:
	typedef typename boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> graph_type;
	typedef typename graph_type::vertex_descriptor  vertex_descriptor;
	typedef typename graph_type::edge_descriptor    edge_descriptor;

	typedef typename graph_type::vertex_iterator    vertex_iterator;
	typedef typename graph_type::edge_iterator      edge_iterator;
	typedef typename graph_type::adjacency_iterator adjacency_iterator;

	typedef typename graph_type::vertices_size_type vertices_size_type;
	typedef typename graph_type::edges_size_type    edges_size_type;
	
    graph_type gA;
	graph_type gB;
	graph_type gC;
	graph_type gD;
	graph_type gE;
    graph_type gF;
	
	/*--------gA---------*/
	vertex_descriptor vdAA;
	vertex_descriptor vdAB;
	vertex_descriptor vdAC;
	vertex_descriptor vdAD;
	vertex_descriptor vdAE;
	vertex_descriptor vdAF;
	vertex_descriptor vdAG;
	vertex_descriptor vdAH;
	edge_descriptor edAAB;
	edge_descriptor edAAC;
	edge_descriptor edAAE;
	edge_descriptor edABD;
	edge_descriptor edABE;
	edge_descriptor edACD;
	edge_descriptor edADE;
	edge_descriptor edADF;
	edge_descriptor edAFD;
	edge_descriptor edAFH;
	edge_descriptor edAGH;
	
	/*--------gB---------*/
	vertex_descriptor vdBA;
	
	/*--------gC---------*/
	vertex_descriptor vdCA;
	vertex_descriptor vdCB;
	edge_descriptor edCAB;
	
	/*--------gD---------*/
	vertex_descriptor vdDA;
    vertex_descriptor vdDB;
    vertex_descriptor vdDC;
    vertex_descriptor vdDD;
    vertex_descriptor vdDE;
    vertex_descriptor vdDF;
    vertex_descriptor vdDG;
    vertex_descriptor vdDH;
	vertex_descriptor vdDI;
	vertex_descriptor vdDJ;
	vertex_descriptor vdDK;
	edge_descriptor edDJK;
	
	/*--------gE---------*/
	vertex_descriptor vdEA;
    vertex_descriptor vdEB;
    vertex_descriptor vdEC;
    vertex_descriptor vdED;
    vertex_descriptor vdEE;
	edge_descriptor edEAD;
    edge_descriptor edEDC;
    edge_descriptor edEBE;
	
	virtual void SetUp(){     
	    /*--------gA--------*/
	    vdAA = add_vertex(gA);
	    vdAB = add_vertex(gA);
	    vdAC = add_vertex(gA);
	    vdAD = add_vertex(gA);
	    vdAE = add_vertex(gA);
	    vdAF = add_vertex(gA);
	    vdAG = add_vertex(gA);
	    vdAH = add_vertex(gA);
	    edAAB = add_edge(vdAA, vdAB, gA).first;
	    edAAC = add_edge(vdAA, vdAC, gA).first;
	    edAAE = add_edge(vdAA, vdAE, gA).first;
	    edABD = add_edge(vdAB, vdAD, gA).first;
	    edABE = add_edge(vdAB, vdAE, gA).first;
	    edACD = add_edge(vdAC, vdAD, gA).first;
	    edADE = add_edge(vdAD, vdAE, gA).first;
	    edADF = add_edge(vdAD, vdAF, gA).first;
	    edAFD = add_edge(vdAF, vdAD, gA).first;
	    edAFH = add_edge(vdAF, vdAH, gA).first;
	    edAGH = add_edge(vdAG, vdAH, gA).first;
	    
        /*--------gB--------*/
        vdBA = add_vertex(gB);

	    /*--------gC-------*/
	    vdCA = add_vertex(gC);
	    vdCB = add_vertex(gC);
	    edCAB = add_edge(vdCA, vdCB, gC).first;  

        /*--------gD-------*/    
        vdDA = add_vertex(gD);
        vdDB = add_vertex(gD);
        vdDC = add_vertex(gD);
        vdDD = add_vertex(gD);
        vdDE = add_vertex(gD);
        vdDF = add_vertex(gD);
        vdDG = add_vertex(gD);
        vdDH = add_vertex(gD);
        vdDI = add_vertex(gD);
        vdDJ = add_vertex(gD);
        vdDK = add_vertex(gD);
        edDJK = add_edge(vdDJ, vdDK, gD).first;

        /*--------gE-------*/    
        vdEA = add_vertex(gE);
        vdEB = add_vertex(gE);
        vdEC = add_vertex(gE);
        vdED = add_vertex(gE);
        vdEE = add_vertex(gE);
        edEAD = add_edge(vdEA, vdED, gE).first;
        edEDC = add_edge(vdED, vdEC, gE).first;
        edEBE = add_edge(vdEB, vdEE, gE).first;
	}
	
	virtual void TearDown() {
	}
};

// -----------
// constructor
// -----------

TEST_F(GraphTester, DefaultConstructorTest1){
    graph_type g;
    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0, num_edges(g));
}

// --------
// add_edge
// --------

TEST_F(GraphTester, AddEdgeTest1) {
    ASSERT_EQ(0, num_edges(gF));
    vertex_descriptor vdA = add_vertex(gF);
    vertex_descriptor vdB = add_vertex(gF);
    pair<edge_descriptor, bool> e = add_edge(vdA, vdB, gF);
    ASSERT_EQ(true, e.second);
    ASSERT_EQ(1, num_edges(gF));
}

 TEST_F(GraphTester, AddEdgeTest2) {
    ASSERT_EQ(11, num_edges(gA));
    pair<edge_descriptor, bool> e = add_edge(vdAA, vdAB, gA);
    ASSERT_EQ(edAAB, e.first);
    ASSERT_EQ(true, e.second == false);
    ASSERT_EQ(11, num_edges(gA));
}

 TEST_F(GraphTester, AddEdgeTest3) {
    ASSERT_EQ(0, num_edges(gF));
    ASSERT_EQ(0, num_vertices(gF));
    vertex_descriptor vdA = vertex(10, gF);
    vertex_descriptor vdB = vertex(100, gF);
    ASSERT_EQ(0, num_vertices(gF));
    add_edge(vdA, vdB, gF);
    ASSERT_EQ(1, num_edges(gF));
    ASSERT_EQ(101, num_vertices(gF));
}

 TEST_F(GraphTester, AddEdgeTest4) {
    ASSERT_EQ(1, num_edges(gD));
    ASSERT_EQ(11, num_vertices(gD));
    vertex_descriptor vdA = vertex(10, gD);
    vertex_descriptor vdB = vertex(50, gD);
    ASSERT_EQ(11, num_vertices(gD));
    add_edge(vdA, vdB, gD);
    ASSERT_EQ(2, num_edges(gD));
    ASSERT_EQ(51, num_vertices(gD));
}

// ----------
// add_vertex
// ----------

 TEST_F(GraphTester, AddVertexTest1) {
	ASSERT_EQ(0, num_vertices(gF));
	vertex_descriptor vd = 0;
	ASSERT_EQ(vd, add_vertex(gF));
	ASSERT_EQ(1, num_vertices(gF));
	vd = 1;
	ASSERT_EQ(vd, add_vertex(gF));
	ASSERT_EQ(2, num_vertices(gF));
}

 TEST_F(GraphTester, AddVertexTest2) {
	ASSERT_EQ(8, num_vertices(gA));
	vertex_descriptor vd = 8;
	ASSERT_EQ(vd, add_vertex(gA));
	ASSERT_EQ(9, num_vertices(gA));
}

TEST_F(GraphTester, AddVertexTest3) {
    ASSERT_EQ(2, num_vertices(gC));
    for (vertex_descriptor i = 2; i < 12; ++i)
        ASSERT_EQ(i, add_vertex(gC));
    ASSERT_EQ(12, num_vertices(gC));
}

// -----------------
// adjacent_vertices
// -----------------

 TEST_F(GraphTester, AdjacenctVerticesTest1) {
    std::pair<adjacency_iterator, adjacency_iterator> a = adjacent_vertices(vdAA, gA);
    adjacency_iterator b = a.first; 
    adjacency_iterator e = a.second;
    ASSERT_EQ(true, b != e);
    ASSERT_EQ(*b, vdAB);
    ++b;
    ASSERT_EQ(*b, vdAC);
    ++b;
    ASSERT_EQ(*b, vdAE);
}

 TEST_F(GraphTester, AdjacenctVerticesTest2) {
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdBA, gB);
    adjacency_iterator b = p.first; 
    adjacency_iterator e = p.second;
    ASSERT_EQ(b, e);
}

 TEST_F(GraphTester, AdjacenctVerticesTest3) {
    vertex_descriptor vdCC = add_vertex(gC);
    vertex_descriptor vdCD = add_vertex(gC);
    add_edge(vdCA, vdCC, gC);
    add_edge(vdCA, vdCD, gC);
    pair<adjacency_iterator, adjacency_iterator> a = adjacent_vertices(vdCA, gC);
    adjacency_iterator b = a.first; 
    adjacency_iterator e = a.second;
    ASSERT_EQ(true, b != e);
    ASSERT_EQ(*b, vdCB);
    ++b;
    ASSERT_EQ(*b, vdCC);
    ++b;
    ASSERT_EQ(*b, vdCD);
}

// ----
// edge
// ----

 TEST_F(GraphTester, EdgeTest1) {
    ASSERT_EQ(0, num_edges(gB));
    ASSERT_EQ(1, num_vertices(gB));
    vertex_descriptor vdBB = add_vertex(gB);
    pair<edge_descriptor, bool> e = edge(vdBA, vdBB, gB);
    ASSERT_EQ(true, e.second == false);
}

 TEST_F(GraphTester, EdgeTest2) {
    ASSERT_EQ(1, num_edges(gC));
    ASSERT_EQ(2, num_vertices(gC));
    pair<edge_descriptor, bool> e = edge(vdCA, vdCB, gC);
    ASSERT_EQ(edCAB, e.first);
    ASSERT_EQ(true, e.second);
}

 TEST_F(GraphTester, EdgeTest3) {
    ASSERT_EQ(0, num_edges(gF));
    ASSERT_EQ(0, num_vertices(gF));
    vertex_descriptor vdFA = add_vertex(gF);
    vertex_descriptor vdFB = add_vertex(gF);
    vertex_descriptor vdFC = add_vertex(gF);
    edge_descriptor edFBC = add_edge(vdFB, vdFC, gF).first;
    pair<edge_descriptor, bool> e = edge(vdFB, vdFC, gF);
    pair<edge_descriptor, bool> e2 = edge(vdFA, vdFC, gF);
    ASSERT_EQ(edFBC, e.first);
    ASSERT_EQ(true, e.second);
    ASSERT_EQ(true, e2.second == false);
}

// -----
// edges
// -----

TEST_F(GraphTester, EdgesTest1) {
    pair<edge_iterator, edge_iterator> ed = edges(gB);
    edge_iterator b = ed.first;
    edge_iterator e = ed.second;
    ASSERT_EQ(b, e);
}

 TEST_F(GraphTester, EdgesTest2) {
    pair<edge_iterator, edge_iterator> ed = edges(gD);
    edge_iterator b = ed.first;
    edge_iterator e = ed.second;
    ASSERT_EQ(true, b != e);
    ASSERT_EQ(*b, edDJK);
    ++b;
    ASSERT_EQ(b, e);
}

TEST_F(GraphTester, EdgesTest3) {
    vertex_descriptor vdFA = add_vertex(gF);
    vertex_descriptor vdFB = add_vertex(gF);
    vertex_descriptor vdFC = add_vertex(gF);
    edge_descriptor edFAB = add_edge(vdFA, vdFB, gF).first;
    edge_descriptor edFBC = add_edge(vdFB, vdFC, gF).first;
    edge_descriptor edFCA = add_edge(vdFC, vdFA, gF).first;
    pair<edge_iterator, edge_iterator> ed = edges(gF);
    edge_iterator b = ed.first;
    edge_iterator e = ed.second;
    ASSERT_EQ(true, b != e);
    ASSERT_EQ(*b, edFAB);
    ++b;
    ASSERT_EQ(*b, edFBC);
    ++b;
    ASSERT_EQ(*b, edFCA);
    ++b;
    ASSERT_EQ(b, e);
}

// ---------
// num_edges
// ---------

TEST_F(GraphTester, NumEdgesTest1) {
    ASSERT_EQ(0, num_edges(gF));
}

 TEST_F(GraphTester, NumEdgesTest2) {
    ASSERT_EQ(11, num_edges(gA));
}

TEST_F(GraphTester, NumEdgesTest3) {
    ASSERT_EQ(1, num_edges(gC));
    vertex_descriptor vdCC = add_vertex(gC);
    vertex_descriptor vdCD = add_vertex(gC);
    vertex_descriptor vdCE = add_vertex(gC);
    add_edge(vdCB, vdCC, gC).first;
    add_edge(vdCD, vdCE, gC).first;
    ASSERT_EQ(3, num_edges(gC));
}

// ------------
// num_vertices
// ------------

 TEST_F(GraphTester, NumVerticesTest1) {
	ASSERT_EQ(0, num_vertices(gF));
    vertex_descriptor vd = 0;
    ASSERT_EQ(vd, add_vertex(gF));
    vd = 1;
    ASSERT_EQ(vd, add_vertex(gF));
	ASSERT_EQ(2, num_vertices(gF));
}

 TEST_F(GraphTester, NumVerticesTest2) {
	ASSERT_EQ(8, num_vertices(gA));
	vertex_descriptor vd = 8;
    ASSERT_EQ(vd, add_vertex(gA));
    vd = 9;
    ASSERT_EQ(vd, add_vertex(gA)); 
    vd = 10;
    ASSERT_EQ(vd, add_vertex(gA));
    vd = 11;
    ASSERT_EQ(vd, add_vertex(gA));
	ASSERT_EQ(12, num_vertices(gA));
}

TEST_F(GraphTester, NumVerticesTest3) {
    ASSERT_EQ(11, num_vertices(gD));
    vertex_descriptor vd = 11;
    ASSERT_EQ(vd, add_vertex(gD));
    add_edge(vd, vdDA, gD);
    ASSERT_EQ(12, num_vertices(gD));
}

// ----------------
// source && target
// ----------------

TEST_F(GraphTester, SourceAndTargetTest1) {
    ASSERT_EQ(0, num_edges(gF));
    ASSERT_EQ(0, num_vertices(gF));
    vertex_descriptor vdFA = add_vertex(gF);
    vertex_descriptor vdFB = add_vertex(gF);
    edge_descriptor edFAB = add_edge(vdFA, vdFB, gF).first;
    vertex_descriptor vds = source(edFAB, gF);
    vertex_descriptor vdt = target(edFAB, gF);
    ASSERT_EQ(vds, vdFA);
    ASSERT_EQ(vdt, vdFB);
    ASSERT_EQ(1, num_edges(gF));
    ASSERT_EQ(2, num_vertices(gF));
}

 TEST_F(GraphTester, SourceAndTargetTest2) {
    vertex_descriptor vds = source(edAFH, gA);
    vertex_descriptor vdt = target(edAFH, gA);
    ASSERT_EQ(vds, vdAF);
    ASSERT_EQ(vdt, vdAH);
}

 TEST_F(GraphTester, SourceAndTargetTest3) {
    vertex_descriptor vds = source(edCAB, gC);
    vertex_descriptor vdt = target(edCAB, gC);
    ASSERT_EQ(vds, vdAA);
    ASSERT_EQ(vdt, vdAB);
}

// ------
// vertex
// ------

 TEST_F(GraphTester, VertexTest1) {
    ASSERT_EQ(0, num_edges(gF));
    ASSERT_EQ(0, num_vertices(gF));
    vertex_descriptor vd = vertex(0, gF);
    ASSERT_EQ(vd, vdAA);
    ASSERT_EQ(0, num_edges(gF));
    ASSERT_EQ(0, num_vertices(gF));
}

 TEST_F(GraphTester, VertexTest2) {
    vertex_descriptor vd = vertex(1, gC);
    ASSERT_EQ(vd, vdCB);
}

 TEST_F(GraphTester, VertexTest3) {
    ASSERT_EQ(1, num_vertices(gB));
    vertex_descriptor vd = vertex(50, gB);
    ASSERT_EQ(vd, 50);
}

// --------
// vertices
// --------

 TEST_F(GraphTester, VerticesTest1) {
    pair<vertex_iterator, vertex_iterator> v = vertices(gF);
    vertex_iterator b = v.first;
    vertex_iterator e = v.second;
    ASSERT_EQ(b, e);
}

 TEST_F(GraphTester, VerticesTest2) {
    vertex_descriptor vdCC = add_vertex(gC);
    pair<vertex_iterator, vertex_iterator> v = vertices(gC);
    vertex_iterator b = v.first;
    vertex_iterator e = v.second;
    ASSERT_EQ(true, b != e);
    ASSERT_EQ(*b, vdCA);
    ++b;
    ASSERT_EQ(*b, vdCB);
    ++b;
    ASSERT_EQ(*b, vdCC);
    ++b;
    ASSERT_EQ(b, e);
}

 TEST_F(GraphTester, VerticesTest3) {
    pair<vertex_iterator, vertex_iterator> v = vertices(gB);
    vertex_iterator b = v.first;
    vertex_iterator e = v.second;
    ASSERT_EQ(true, b != e);
    ASSERT_EQ(*b, vdBA);
    ++b;
    ASSERT_EQ(b, e);
}

// ---------
// has_cycle
// ---------

  TEST_F(GraphTester, HasCycleTest1){
    ASSERT_EQ(0, num_edges(gF));
    ASSERT_EQ(0, num_vertices(gF));
    ASSERT_EQ(true, has_cycle(gF) == false);
}

 TEST_F(GraphTester, HasCycleTest2) {
    ASSERT_EQ(true, has_cycle(gA));
}

  TEST_F(GraphTester, HasCycleTest3){
    ASSERT_EQ(3, num_edges(gE));
    ASSERT_EQ(5, num_vertices(gE));
    ASSERT_EQ(true, has_cycle(gE) == false);
}

  TEST_F(GraphTester, HasCycleTest4){
    ASSERT_EQ(3, num_edges(gE));
    ASSERT_EQ(5, num_vertices(gE));
    ASSERT_EQ(true, has_cycle(gE) == false);
    add_vertex(gE);
    add_edge(vdEC, vdEA, gE);
    ASSERT_EQ(4, num_edges(gE));
    ASSERT_EQ(6, num_vertices(gE));
    ASSERT_EQ(true, has_cycle(gE));
}

// ----------------
// topological sort
// ----------------

TEST_F(GraphTester, TopologicalSortTest1){
    ostringstream out;
    topological_sort(gF, ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ(true, out.str() == "");
}

 TEST_F(GraphTester, TopologicalSortTest2) {
        ostringstream out;
    try {
        topological_sort(gA, ostream_iterator<vertex_descriptor>(out, " "));
    } catch (const boost::not_a_dag& e){
        ASSERT_EQ("The graph must be a DAG.",  std::string(e.what()));
    }
}

  TEST_F(GraphTester, TopologicalSortTest3){
        ostringstream out;
        topological_sort(gE, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ("2 3 0 4 1 ",out.str());
}

  TEST_F(GraphTester, TopologicalSortTest4){
        ostringstream out;
        topological_sort(gD, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ("0 1 2 3 4 5 6 7 8 10 9 ", out.str());
}
