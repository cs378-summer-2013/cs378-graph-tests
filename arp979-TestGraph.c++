// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
 To test the program:
 % ls /usr/include/cppunit/
 ...
 HelperMacros.h
 ...
 % locate libcppunit.a
 /usr/lib/libcppunit.a
 % ls /public/linux/include/boost-1_44/boost/graph/
 ...
 adjacency_list.hpp
 ...
 % g++ -pedantic -std=c++0x -Wall TestGraph.c++ -o TestGraph -lgtest -lgtest_main -lpthread
 */

// --------
// includes
// --------

#include <algorithm> 
#include <cstring>  
#include <stdexcept> 
#include <string>    
#include <deque>
#include <cstdlib>
#include <climits>
#include <iostream> 
#include <iterator> 
#include <sstream>  
#include <utility>  
#include <vector>  
#include <stack>   
#include <set>     

#include "boost/graph/adjacency_list.hpp"  
#include "boost/graph/topological_sort.hpp"

#include "gtest/gtest.h" 

#include "Graph.h"

#define private public
using namespace std;

// ---------
// TestGraph
// ---------
template <typename T>
class TestGraph : public testing::Test{
    
public:
    
    typedef T                                      graph_type;
    
    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;
    
    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;
    
    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;
    // -----
    // tests
    // -----
    
    
    graph_type graph1;
    graph_type graph2;
    graph_type graph3;
  graph_type graph4;
    
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    vertex_descriptor vdC;
    vertex_descriptor vdD;
    vertex_descriptor vdE;
    vertex_descriptor vdF;
    vertex_descriptor vdG;
    vertex_descriptor vdH;
	vertex_descriptor vdI;
	vertex_descriptor vdJ;
	
    
    edge_descriptor edAB;
    edge_descriptor edAC;
    edge_descriptor edAE;
	edge_descriptor edAH;
	edge_descriptor edBC;
    edge_descriptor edBD;
    edge_descriptor edBE;
    edge_descriptor edCD;
    edge_descriptor edDE;
    edge_descriptor edDF;
	edge_descriptor edEF;
	edge_descriptor edFG;
	edge_descriptor edFJ;
    edge_descriptor edFH;
    edge_descriptor edGH;
	edge_descriptor edGI;
    edge_descriptor edEA;
    
    
    virtual void init_graph1 () {
        vdA  = add_vertex(graph1);
        vdB  = add_vertex(graph1);
        vdC  = add_vertex(graph1);
		vdD  = add_vertex(graph1);
        vdE  = add_vertex(graph1);
        edAB = add_edge(vdA, vdB, graph1).first;
        edAC = add_edge(vdA, vdC, graph1).first;
        edAE = add_edge(vdA, vdE, graph1).first;
		edBD = add_edge(vdB, vdD, graph1).first;
    }
    
    virtual void init_graph2 () {
        vdA  = add_vertex(graph2);
        vdB  = add_vertex(graph2);
        vdC  = add_vertex(graph2);
        vdD  = add_vertex(graph2);
        vdE  = add_vertex(graph2);
        vdF  = add_vertex(graph2);
        vdG  = add_vertex(graph2);
        vdH  = add_vertex(graph2);
        edAB = add_edge(vdA, vdB, graph2).first;
        edAC = add_edge(vdA, vdC, graph2).first;
        edAE = add_edge(vdA, vdE, graph2).first;
		edAH = add_edge(vdA, vdH, graph2).first;
        edBE = add_edge(vdB, vdE, graph2).first;
        edCD = add_edge(vdC, vdD, graph2).first;
        edDE = add_edge(vdD, vdE, graph2).first;
        edDF = add_edge(vdD, vdF, graph2).first;
        edFH = add_edge(vdF, vdH, graph2).first;
        edGH = add_edge(vdG, vdH, graph2).first;

    }
    virtual void init_graph3() {
        vdA  = add_vertex(graph3);
        vdB  = add_vertex(graph3);
        vdC  = add_vertex(graph3);
        vdD  = add_vertex(graph3);
        vdE  = add_vertex(graph3);
        vdF  = add_vertex(graph3);
        vdG  = add_vertex(graph3);
        vdH  = add_vertex(graph3);
        edAB = add_edge(vdA, vdB, graph3).first;
        edAC = add_edge(vdA, vdC, graph3).first;
        edEA = add_edge(vdE, vdA, graph3).first;
        edBD = add_edge(vdB, vdD, graph3).first;
        edBE = add_edge(vdB, vdE, graph3).first;
        edCD = add_edge(vdC, vdD, graph3).first;
        edDE = add_edge(vdD, vdE, graph3).first;
        edDF = add_edge(vdD, vdF, graph3).first;
        edFH = add_edge(vdF, vdH, graph3).first;
        edGH = add_edge(vdG, vdH, graph3).first;
    }
	
	virtual void init_graph4 () {
        vdA  = add_vertex(graph4);
        vdB  = add_vertex(graph4);
        vdC  = add_vertex(graph4);
        vdD  = add_vertex(graph4);
        vdE  = add_vertex(graph4);
        vdF  = add_vertex(graph4);
        vdG  = add_vertex(graph4);
        vdH  = add_vertex(graph4);
		vdI  = add_vertex(graph4);
		vdJ  = add_vertex(graph4);
        edAB = add_edge(vdA, vdB, graph4).first;
        edBC = add_edge(vdB, vdC, graph4).first;
        edCD = add_edge(vdC, vdD, graph4).first;
        edDE = add_edge(vdD, vdE, graph4).first;
        edEF = add_edge(vdE, vdF, graph4).first;
        edFG = add_edge(vdF, vdG, graph4).first;
        edFH = add_edge(vdF, vdH, graph4).first;
        edDF = add_edge(vdD, vdF, graph4).first;
        edFJ = add_edge(vdF, vdJ, graph4).first;
        edGI = add_edge(vdG, vdI, graph4).first;
    }
};

typedef testing::Types< Graph, boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> > MyGraphs;

TYPED_TEST_CASE(TestGraph, MyGraphs);


// -------------
// test_add_edge
// -------------

TYPED_TEST(TestGraph , test_add_edges_1)
{
    this->init_graph1();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->vdB, this->vdC, this->graph1);
    ASSERT_TRUE(p.second);
}

TYPED_TEST(TestGraph , test_add_edges_2)
{
    this->init_graph2();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->graph2);
    ASSERT_FALSE(p.second);
}

TYPED_TEST(TestGraph , test_add_edges_3)
{
    this->init_graph3();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->vdD, this->vdH, this->graph3);
    ASSERT_TRUE(p.second);
}


TYPED_TEST(TestGraph , test_add_edges_4)
{
    this->init_graph4();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->vdB, this->vdE, this->graph4);
    ASSERT_TRUE(p.second);
}


// -------------
// test_add_vertex
// -------------

TYPED_TEST(TestGraph , test_add_vertex_1)
{
    this->init_graph1();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->graph1);
    ASSERT_TRUE(v == 5);
}

TYPED_TEST(TestGraph , test_add_vertex_2)
{
    this->init_graph2();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->graph2);
    ASSERT_TRUE(v == 8);
}

TYPED_TEST(TestGraph , test_add_vertex_3)
{
    this->init_graph3();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->graph3);
    ASSERT_TRUE(v == 8);
}

TYPED_TEST(TestGraph , test_add_vertex_4)
{
    this->init_graph4();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->graph4);
    ASSERT_TRUE(v == 10);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(TestGraph, test_adjacent_vertices_1)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this->init_graph1();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->graph1);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    vertex_descriptor v = *b;
    ASSERT_TRUE(v == this->vdB);
    ++b;
    v = *b;
    ASSERT_TRUE(v == this->vdC);
	++b;
    v = *b;
    ASSERT_TRUE(v == this->vdE);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_2)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this->init_graph2();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->graph2);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    vertex_descriptor v = *b;
    ASSERT_TRUE(v == this->vdB);
	++b;
    v = *b;
    ASSERT_TRUE(v == this->vdC);
    ++b;
    v = *b;
    ASSERT_TRUE(v == this->vdE);
	++b;
    v = *b;
    ASSERT_TRUE(v == this->vdH);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_3)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this->init_graph3();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdB, this->graph3);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    vertex_descriptor v = *b;
    ASSERT_TRUE(v == this->vdD);
	++b;
    v = *b;
    ASSERT_TRUE(v == this->vdE);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_4)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this->init_graph4();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->graph4);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    vertex_descriptor v = *b;
    ASSERT_TRUE(v == this->vdB);
}

// ---------
// test_edge
// ---------

TYPED_TEST(TestGraph, test_edge_1)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this->init_graph1();
    pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->graph1);
    ASSERT_TRUE(p.first  == this->edAB);
    ASSERT_TRUE(p.second);
}

TYPED_TEST(TestGraph, test_edge_2)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this->init_graph2();
    pair<edge_descriptor, bool> p = edge(this->vdD, this->vdE, this->graph2);
    ASSERT_TRUE(p.first  == this->edDE);
    ASSERT_TRUE(p.second);
}

TYPED_TEST(TestGraph, test_edge_3)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this->init_graph3();
    pair<edge_descriptor, bool> p = edge(this->vdA, this->vdF, this->graph3);
    ASSERT_FALSE(p.second);
}

TYPED_TEST(TestGraph, test_edge_4)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this->init_graph4();
    pair<edge_descriptor, bool> p = edge(this->vdE, this->vdF, this->graph4);
    ASSERT_TRUE(p.first  == this->edEF);
    ASSERT_TRUE(p.second);
}

// ----------
// test_edges
// ----------

TYPED_TEST(TestGraph, test_edges_1)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this->init_graph1();
    std::pair<edge_iterator, edge_iterator> p = edges(this->graph1);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor _e = *b;
    ASSERT_TRUE(_e == this->edAB);
    ++b;
    _e = *b;
    ASSERT_TRUE(_e == this->edAC);
}

TYPED_TEST(TestGraph, test_edges_2)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this->init_graph2();
    std::pair<edge_iterator, edge_iterator> p = edges(this->graph2);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor _e = *b;
    ASSERT_TRUE(_e == this->edAB);
    ++b;
	_e = *b;
    ASSERT_TRUE(_e == this->edAC);
	++b;
	_e = *b;
    ASSERT_TRUE(_e == this->edAE);
}

TYPED_TEST(TestGraph, test_edges_3)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this->init_graph3();
    std::pair<edge_iterator, edge_iterator> p = edges(this->graph3);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor _e = *b;
    ASSERT_TRUE(_e == this->edAB);
    ++b;
	++b;
    _e = *b;
    ASSERT_TRUE(_e == this->edAC);
	++b;
	++b;
    _e = *b;
    ASSERT_TRUE(_e == this->edEA);
}

TYPED_TEST(TestGraph, test_edges_4)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this->init_graph1();
    std::pair<edge_iterator, edge_iterator> p = edges(this->graph1);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor _e = *b;
    ASSERT_TRUE(_e == this->edAB);
    ++b;
	++b;
    _e = *b;
    ASSERT_TRUE(_e == this->edBC);
	++b;
	++b;
    _e = *b;
    ASSERT_TRUE(_e == this->edCD);
} 

// --------------
// test_num_edges
// --------------

TYPED_TEST (TestGraph, test_num_edges_1)
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    this->init_graph1();
    edges_size_type s = num_edges(this->graph1);
    ASSERT_TRUE(s == 4);
}

TYPED_TEST (TestGraph, test_num_edges_2)
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    this->init_graph2();
    edges_size_type s = num_edges(this->graph2);
    ASSERT_TRUE(s == 10);
}

TYPED_TEST (TestGraph, test_num_edges_3)
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    this->init_graph3();
    edges_size_type s = num_edges(this->graph3);
    ASSERT_TRUE(s == 10);
}

TYPED_TEST (TestGraph, test_num_edges_4)
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    this->init_graph4();
    edges_size_type s = num_edges(this->graph4);
    ASSERT_TRUE(s == 10);
}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST (TestGraph, test_num_vertices_1)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    this->init_graph1();
    vertices_size_type s = num_vertices(this->graph1);
    ASSERT_TRUE(s == 5);
}

TYPED_TEST (TestGraph, test_num_vertices_2)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    this->init_graph2();
    vertices_size_type s = num_vertices(this->graph2);
    ASSERT_TRUE(s == 8);
}

TYPED_TEST (TestGraph, test_num_vertices_3)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    this->init_graph3();
    vertices_size_type s = num_vertices(this->graph3);
    ASSERT_TRUE(s == 8);
}

TYPED_TEST (TestGraph, test_num_vertices_4)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    this->init_graph4();
    vertices_size_type s = num_vertices(this->graph4);
    ASSERT_TRUE(s == 10);
}

// -----------
// test_source
// -----------

TYPED_TEST(TestGraph, test_source_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph1();
    vertex_descriptor vd = source(this->edAB, this->graph1);
    ASSERT_TRUE(vd == this->vdA);
}

TYPED_TEST(TestGraph, test_source_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph2();
    vertex_descriptor vd = source(this->edCD, this->graph2);
    ASSERT_TRUE(vd == this->vdC);
}

TYPED_TEST(TestGraph, test_source_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph3();
    vertex_descriptor vd = source(this->edEA, this->graph3);
    ASSERT_TRUE(vd == this->vdE);
}

TYPED_TEST(TestGraph, test_source_4)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph4();
    vertex_descriptor vd = source(this->edGI, this->graph4);
    ASSERT_TRUE(vd == this->vdG);
}

// -----------
// test_target
// -----------

TYPED_TEST(TestGraph, test_target_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph1();
    vertex_descriptor vd = target(this->edAB, this->graph1);
    ASSERT_TRUE(vd == this->vdB);
}

TYPED_TEST(TestGraph, test_target_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph2();
    vertex_descriptor vd = target(this->edCD, this->graph2);
    ASSERT_TRUE(vd == this->vdD);
}

TYPED_TEST(TestGraph, test_target_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph3();
    vertex_descriptor vd = target(this->edEA, this->graph3);
    ASSERT_TRUE(vd == this->vdA);
}

TYPED_TEST(TestGraph, test_target_4)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph4();
    vertex_descriptor vd = target(this->edGI, this->graph4);
    ASSERT_TRUE(vd == this->vdI);
}

// -----------
// test_vertex
// -----------

TYPED_TEST (TestGraph, test_vertex_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph1();
    vertex_descriptor vd = vertex(1, this->graph1);
    ASSERT_TRUE(vd == this->vdB);
}

TYPED_TEST (TestGraph, test_vertex_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph2();
    vertex_descriptor vd = vertex(3, this->graph2);
    ASSERT_TRUE(vd == this->vdD);
}

TYPED_TEST (TestGraph, test_vertex_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph3();
    vertex_descriptor vd = vertex(5, this->graph3);
    ASSERT_TRUE(vd == this->vdF);
}

TYPED_TEST (TestGraph, test_vertex_4)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph4();
    vertex_descriptor vd = vertex(8, this->graph4);
    ASSERT_TRUE(vd == this->vdI);
}

// -------------
// test_vertices
// -------------


TYPED_TEST(TestGraph, test_vertices_1)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph1();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->graph1);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor _b = *b;
    ASSERT_TRUE(_b == this->vdA);
    --e;
    vertex_descriptor _e = *e;
    ASSERT_TRUE(_e == this->vdE);
}

TYPED_TEST(TestGraph, test_vertices_2)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph2();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->graph2);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor _b = *b;
    ASSERT_TRUE(_b == this->vdA);
    --e;
    vertex_descriptor _e = *e;
    ASSERT_TRUE(_e == this->vdH);
}

TYPED_TEST(TestGraph, test_vertices_3)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph3();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->graph3);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor _b = *b;
    ASSERT_TRUE(_b == this->vdA);
    --e;
    vertex_descriptor _e = *e;
    ASSERT_TRUE(_e == this->vdH);
}

TYPED_TEST(TestGraph, test_vertices_4)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->init_graph4();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->graph4);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor _b = *b;
    ASSERT_TRUE(_b == this->vdA);
    --e;
    vertex_descriptor _e = *e;
    ASSERT_TRUE(_e == this->vdJ);
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraph, test_has_cycle_1)
{
    this->init_graph1();
    ASSERT_FALSE(has_cycle(this->graph1));
}

TYPED_TEST(TestGraph, test_has_cycle_2)
{
    this->init_graph2();
    ASSERT_FALSE(has_cycle(this->graph2));
}

TYPED_TEST(TestGraph, test_has_cycle_3)
{
    this->init_graph3();
    ASSERT_FALSE(has_cycle(this->graph3));
}

TYPED_TEST(TestGraph, test_has_cycle_4)
{
    this->init_graph4();
    ASSERT_FALSE(has_cycle(this->graph4));
} 



// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST (TestGraph, test_topological_sort_no_cycle_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->init_graph1();
    
    ostringstream out;
    try{
        topological_sort(this->graph1, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string("3 1 2 4 0 "), out.str());
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(false);
    }
}



 
 


