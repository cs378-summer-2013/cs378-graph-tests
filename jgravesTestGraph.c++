// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
 * TestDeque
 *
 * To compile this, use the command
 * g++ -pedantic -std=c++0x -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread
 *
 * Then it can run with
 * TestDeque
 *
 * It will work on any machine with gtest and the precompiled libraries installed
 */

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <iostream>  // cout, endl

#include "gtest/gtest.h"                        // Google Test framework

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "Graph.h"

// #include <cassert>
// #include <iterator>
// #include <memory>

#include <utility>
#include <cstdlib>


#define class struct
#define protected public
#define private public


// ---------
// TestGraph
// ---------

// Tests for hasCycle and topological sort

class CycleTests : public testing::Test {
    typedef Graph graph_type;
    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;
    public:
    graph_type _g;
    vertex_descriptor _vdA;
    vertex_descriptor _vdB;
    vertex_descriptor _vdC;
    vertex_descriptor _vdD;
    vertex_descriptor _vdE;
    vertex_descriptor _vdF;
    vertex_descriptor _vdG;
    vertex_descriptor _vdH;

    edge_descriptor _edAB;
    edge_descriptor _edAC;
    edge_descriptor _edAE;
    edge_descriptor _edBD;
    edge_descriptor _edBE;
    edge_descriptor _edCD;
    edge_descriptor _edDE;
    edge_descriptor _edDF;
    edge_descriptor _edFD;
    edge_descriptor _edFH;
    edge_descriptor _edGH;

    edge_descriptor _eA;
    edge_descriptor _eB;
    edge_descriptor _eC;
    edge_descriptor _eD;
    edge_descriptor _eE;
    edge_descriptor _eF;
    edge_descriptor _eG;
    edge_descriptor _eH; 
    edge_descriptor _eI;
    edge_descriptor _eJ;
    edge_descriptor _eK;

    // has cycle
    virtual void setUp1(){
        _vdA = add_vertex(_g);
        _vdB = add_vertex(_g);
        _vdC = add_vertex(_g);
        _vdD = add_vertex(_g);
        _vdE = add_vertex(_g);
        _vdF = add_vertex(_g);
        _vdG = add_vertex(_g);
        _vdH = add_vertex(_g);
        _edAB = add_edge(_vdA, _vdB, _g).first;
        _edAC = add_edge(_vdA, _vdC, _g).first;
        _edAE = add_edge(_vdA, _vdE, _g).first;
        _edBD = add_edge(_vdB, _vdD, _g).first;
        _edBE = add_edge(_vdB, _vdE, _g).first;
        _edCD = add_edge(_vdC, _vdD, _g).first;
        _edDE = add_edge(_vdD, _vdE, _g).first;
        _edDF = add_edge(_vdD, _vdF, _g).first;
        _edFD = add_edge(_vdF, _vdD, _g).first;
        _edFH = add_edge(_vdF, _vdH, _g).first;
        _edGH = add_edge(_vdG, _vdH, _g).first;}
    
    // no cycle
    virtual void setUp2(){
        _vdA = add_vertex(_g);
        _vdB = add_vertex(_g);
        _vdC = add_vertex(_g);
        _vdD = add_vertex(_g);

        _edAB = add_edge(_vdA, _vdB, _g).first;
        _edAC = add_edge(_vdA, _vdC, _g).first;
        _edBD = add_edge(_vdB, _vdD, _g).first;
}

    virtual void setUp3(){
        _vdA = add_vertex(_g);
        _vdB = add_vertex(_g);
        _vdC = add_vertex(_g);
        _vdD = add_vertex(_g);
        _vdE = add_vertex(_g);
        _vdF = add_vertex(_g);
        _vdG = add_vertex(_g);

        _eA = add_edge(_vdA, _vdC, _g).first;
        _eB = add_edge(_vdA, _vdD, _g).first;
        _eC = add_edge(_vdB, _vdE, _g).first;
        _eD = add_edge(_vdB, _vdF, _g).first;
        _eE = add_edge(_vdC, _vdB, _g).first;
        _eF = add_edge(_vdD, _vdG, _g).first;
        _eG = add_edge(_vdC, _vdD, _g).first;
        _eH = add_edge(_vdF, _vdD, _g).first;
	_eI = add_edge(_vdE, _vdG, _g).first;
	_eJ = add_edge(_vdF, _vdE, _g).first;
}};


//has cycle
TEST_F (CycleTests,test_has_cycle_1) {
        setUp1();
        EXPECT_TRUE(has_cycle(_g));}

TEST_F (CycleTests,test_has_cycle_2) {
        setUp2();
        EXPECT_TRUE(!has_cycle(_g));}

TEST_F (CycleTests,test_has_cycle_3) {
        setUp3();
        EXPECT_TRUE(!has_cycle(_g));}
// topological_sort
TEST_F (CycleTests,test_topological_sort_1) {
        setUp2();
        std::ostringstream out;
        topological_sort(_g, std::ostream_iterator<vertex_descriptor>(out, " "));
        EXPECT_TRUE(out.str() == "0 1 3 2 ");}

TEST_F (CycleTests,test_topological_sort_2) {
        setUp1();
        std::ostringstream out;
        try{
            topological_sort(_g, std::ostream_iterator<vertex_descriptor>(out, " "));
            EXPECT_TRUE(false);
        } catch (...){
            EXPECT_TRUE(true);
        };}

TEST_F (CycleTests,test_topological_sort_3) {
        setUp3();
        std::ostringstream out;
        topological_sort(_g, std::ostream_iterator<vertex_descriptor>(out, " "));
        EXPECT_TRUE(out.str() == "0 2 1 5 4 3 6 ");}

using namespace boost;
typedef testing::Types< adjacency_list<setS, vecS, directedS>, Graph > Containers;

// Tests for graph setUp funtions
template <typename C>
class Tests : public testing::Test {
    typedef C graph_type;
    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;
    public:
    graph_type _g;
    vertex_descriptor _vdA;
    vertex_descriptor _vdB;
    vertex_descriptor _vdC;
    vertex_descriptor _vdD;
    vertex_descriptor _vdE;
    vertex_descriptor _vdF;
    vertex_descriptor _vdG;
    vertex_descriptor _vdH;

    edge_descriptor _edAB;
    edge_descriptor _edAC;
    edge_descriptor _edAE;
    edge_descriptor _edBD;
    edge_descriptor _edBE;
    edge_descriptor _edCD;
    edge_descriptor _edDE;
    edge_descriptor _edDF;
    edge_descriptor _edFD;
    edge_descriptor _edFH;
    edge_descriptor _edGH;

    Tests():_g(graph_type()),
        _vdA(add_vertex(_g)),
        _vdB(add_vertex(_g)),
        _vdC(add_vertex(_g)),
        _vdD(add_vertex(_g)),
        _vdE(add_vertex(_g)),
        _vdF(add_vertex(_g)),
        _vdG(add_vertex(_g)),
        _vdH(add_vertex(_g)),
        _edAB(add_edge(_vdA, _vdB, _g).first),
        _edAC(add_edge(_vdA, _vdC, _g).first),
        _edAE(add_edge(_vdA, _vdE, _g).first),
        _edBD(add_edge(_vdB, _vdD, _g).first),
        _edBE(add_edge(_vdB, _vdE, _g).first),
        _edCD(add_edge(_vdC, _vdD, _g).first),
        _edDE(add_edge(_vdD, _vdE, _g).first),
        _edDF(add_edge(_vdD, _vdF, _g).first),
        _edFD(add_edge(_vdF, _vdD, _g).first),
        _edFH(add_edge(_vdF, _vdH, _g).first),
        _edGH(add_edge(_vdG, _vdH, _g).first){}
};



TYPED_TEST_CASE(Tests, Containers);

    // -------------
    // test_add_edge
    // -------------

TYPED_TEST (Tests, add_edge1) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->_vdA, this->_vdB, this->_g);
        EXPECT_TRUE(p.first  == this->_edAB);
        EXPECT_TRUE(p.second == false);}

TYPED_TEST (Tests, add_edge2) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->_vdC, this->_vdD, this->_g);
        EXPECT_TRUE(p.first  == this->_edCD);
        EXPECT_TRUE(p.second == false);}

TYPED_TEST (Tests, add_edge3) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->_vdA, this->_vdH, this->_g);
        EXPECT_TRUE(p.second == true);}

TYPED_TEST (Tests, add_edge4) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->_vdF, this->_vdG, this->_g);
        EXPECT_TRUE(p.second == true);
	EXPECT_TRUE(num_edges(this->_g) == 12);}

    // ----------------------
    // test_adjacent_vertices
    // ----------------------
    
TYPED_TEST (Tests, adjacent_vertices1) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->_vdA, this->_g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        EXPECT_TRUE(b != e);
  	typename TestFixture::vertex_descriptor v = *b;
        EXPECT_TRUE(v == this->_vdB);
        ++b;
        v = *b;
        EXPECT_TRUE(v == this->_vdC);
        ++b;
        v = *b;
        EXPECT_TRUE(v == this->_vdE);
        ++b;
        EXPECT_TRUE(b == e); 
        }

TYPED_TEST (Tests, adjacent_vertices2) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->_vdF, this->_g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        EXPECT_TRUE(b != e);
        typename TestFixture::vertex_descriptor v = *b;
        EXPECT_TRUE(v == this->_vdD);
        ++b;
        v = *b;
        EXPECT_TRUE(v == this->_vdH);
	++b;
	EXPECT_TRUE(b == e);	
}

TYPED_TEST (Tests, adjacent_vertices3) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->_vdE, this->_g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        EXPECT_TRUE(b == e);
}

TYPED_TEST (Tests, adjacent_vertices4) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->_vdH, this->_g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        EXPECT_TRUE(b == e);
}

TYPED_TEST (Tests, adjacent_vertices5) {
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->_vdC, this->_g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	EXPECT_TRUE(b!=e);
	typename TestFixture::vertex_descriptor v = *b;
	EXPECT_TRUE(v == this->_vdD);
	++b;
	EXPECT_TRUE(b == e);
}

    // ---------
    // test_edge
    // ---------
TYPED_TEST (Tests, test_edge1) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->_vdA, this->_vdB, this->_g);
        EXPECT_TRUE(p.first  == this->_edAB);
        EXPECT_TRUE(p.second == true);}

TYPED_TEST (Tests, test_edge2) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->_vdA, this->_vdC, this->_g);
        EXPECT_TRUE(p.first  == this->_edAC);
        EXPECT_TRUE(p.second == true);}

TYPED_TEST (Tests, test_edge3) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->_vdE, this->_vdA, this->_g);
        EXPECT_TRUE(p.second == false);}

TYPED_TEST (Tests, test_edge4) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->_vdH, this->_vdA, this->_g);
        EXPECT_TRUE(p.second == false);}

    // ----------
    // test_edges
    // ----------
TYPED_TEST (Tests,test_edges1) {
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->_g);
        typename TestFixture::edge_iterator b = p.first;
        typename TestFixture::edge_iterator e = p.second;
        EXPECT_TRUE(b != e);
        typename TestFixture::edge_descriptor ed = *b;
        EXPECT_TRUE(ed == this->_edAB);
        ++b;
        ed = *b;
        EXPECT_TRUE(ed == this->_edAC);
        ++b;
        ed = *b;
        EXPECT_TRUE(ed == this->_edAE);
	++b;
        ed = *b;
        EXPECT_TRUE(ed == this->_edBD);
        ++b;
        ed = *b;
        EXPECT_TRUE(ed == this->_edBE);
        ++b;
        ed = *b;
        EXPECT_TRUE(ed == this->_edCD);
        }


 // --------------
    // test_num_edges
    // --------------
TYPED_TEST (Tests,test_num_edges1) {
        typename TestFixture::edges_size_type n = num_edges(this->_g);
        EXPECT_TRUE(n == 11);}


TYPED_TEST (Tests,test_num_edges2) {
        add_edge(this->_vdA, this->_vdB, this->_g);
        typename TestFixture::edges_size_type n = num_edges(this->_g);
        EXPECT_TRUE(n == 11);
        }

TYPED_TEST (Tests,test_num_edges3) {
        add_edge(this->_vdA, this->_vdD, this->_g);
        typename TestFixture::edges_size_type n = num_edges(this->_g);
        EXPECT_TRUE(n == 12);
        }
TYPED_TEST (Tests,test_num_edges4) {
	add_edge(this->_vdA, this->_vdD, this->_g);
	add_edge(this->_vdD, this->_vdA, this->_g);
	typename TestFixture::edges_size_type n = num_edges(this->_g);
	EXPECT_TRUE(n == 13);
}

TYPED_TEST (Tests,test_num_edges5) {
	add_edge(this->_vdD, this->_vdA, this->_g);
	add_edge(this->_vdA, this->_vdF, this->_g);
	typename TestFixture::edges_size_type n = num_edges(this->_g);
	EXPECT_TRUE(n == 13);
}
    // -----------------
    // test_num_vertices
    // -----------------
TYPED_TEST (Tests,test_num_vertices1) {
        typename TestFixture::vertices_size_type n = num_vertices(this->_g);
        EXPECT_TRUE(n == 8);}

TYPED_TEST (Tests,test_num_vertices2) {
        add_vertex(this->_g);
        typename TestFixture::vertices_size_type n = num_vertices(this->_g);
        EXPECT_TRUE(n == 9);}

TYPED_TEST (Tests,test_num_vertices3) {
        add_vertex(this->_g);
        add_vertex(this->_g);
        typename TestFixture::vertices_size_type n = num_vertices(this->_g);
        EXPECT_TRUE(n == 10);}



    // -----------
    // test_source
    // -----------
TYPED_TEST (Tests,test_source_1) {
        typename TestFixture::vertex_descriptor v = source(this->_edAB, this->_g);
        EXPECT_TRUE(v == this->_vdA);}

TYPED_TEST (Tests,test_source_2) {
        typename TestFixture::vertex_descriptor v = source(this->_edAB, this->_g);
        EXPECT_TRUE(v != this->_vdB);}

TYPED_TEST (Tests,test_source_3) {
        typename TestFixture::vertex_descriptor v = source(this->_edAC, this->_g);
        EXPECT_TRUE(v == this->_vdA);
	EXPECT_TRUE(v != this->_vdC);}



    // -----------
    // test_target
    // -----------
TYPED_TEST (Tests,test_target_1) {
        typename TestFixture::vertex_descriptor v = target(this->_edAB, this->_g);
        EXPECT_TRUE(v == this->_vdB);}

TYPED_TEST (Tests,test_target_2) {
        typename TestFixture::vertex_descriptor v = target(this->_edAB, this->_g);
        EXPECT_TRUE(v != this->_vdA);}

TYPED_TEST (Tests,test_target_3) {
        typename TestFixture::vertex_descriptor v = target(this->_edAC, this->_g);
        EXPECT_TRUE(v == this->_vdC);
	EXPECT_TRUE(v != this->_vdA);
}



    // -----------
    // test_vertex
    // -----------
TYPED_TEST (Tests,test_vertex_1) {
        typename TestFixture::vertex_descriptor v = vertex(0, this->_g);
        EXPECT_TRUE(v == this->_vdA);}

TYPED_TEST (Tests,test_vertex_2) {
        typename TestFixture::vertex_descriptor v = vertex(1, this->_g);
        EXPECT_TRUE(v == this->_vdB);}

TYPED_TEST (Tests,test_vertex_3) {
        typename TestFixture::vertex_descriptor v = vertex(2, this->_g);
        EXPECT_TRUE(v == this->_vdC);}

TYPED_TEST (Tests,test_vertex_4) {
        typename TestFixture::vertex_descriptor v = vertex(3, this->_g);
        EXPECT_TRUE(v == this->_vdD);}

TYPED_TEST (Tests,test_vertex_5) {
        typename TestFixture::vertex_descriptor v = vertex(3, this->_g);
        EXPECT_TRUE(v != this->_vdE);}

    // -------------
    // test_vertices
    // -------------

TYPED_TEST (Tests,test_vertices_1) {
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->_g);
        typename TestFixture::vertex_iterator b = p.first;
        typename TestFixture::vertex_iterator e = p.second;
        EXPECT_TRUE(b != e);
        typename TestFixture::vertex_descriptor vd = *b;
        EXPECT_TRUE(vd == this->_vdA);
        ++b;
        vd = *b;
        EXPECT_TRUE(vd == this->_vdB);
        ++b;
        vd = *b;
        EXPECT_TRUE(vd == this->_vdC);
	++b;
	vd = *b;
	EXPECT_TRUE(vd == this->_vdD);
	++b;
	vd = *b;
	EXPECT_TRUE(vd == this->_vdE);
	++b;
	vd = *b;	
	EXPECT_TRUE(vd == this->_vdF);
	++b;
	vd = *b;
	EXPECT_TRUE(vd == this->_vdG);
	++b;
	vd = *b;
	EXPECT_TRUE(vd == this->_vdH);
	++b;
	EXPECT_TRUE(b == e);
        }
