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
// TestDeque
// ---------

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
    

    // CycleTests():_g(graph_type()){}
    
    virtual void setupCyclic(){
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
    
    virtual void setupACyclic(){
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
        // _edDF = add_edge(_vdD, _vdF, _g).first;
        _edFD = add_edge(_vdF, _vdD, _g).first;
        _edFH = add_edge(_vdF, _vdH, _g).first;
        _edGH = add_edge(_vdG, _vdH, _g).first;}

    virtual void CrossEdge(){
        _vdA = add_vertex(_g);
        _vdB = add_vertex(_g);
        _vdC = add_vertex(_g);
        _vdD = add_vertex(_g);
        _vdE = add_vertex(_g);
        _vdF = add_vertex(_g);
        _vdG = add_vertex(_g);

        // _edAB = add_edge(_vdA, _vdB, _g).first;
        _eA = add_edge(_vdA, _vdC, _g).first;
        _eB = add_edge(_vdA, _vdD, _g).first;
        _eC = add_edge(_vdB, _vdE, _g).first;
        _eD = add_edge(_vdB, _vdF, _g).first;
        _eE = add_edge(_vdC, _vdG, _g).first;
        _eF = add_edge(_vdD, _vdG, _g).first;
        // _edDF = add_edge(_vdD, _vdF, _g).first;
        _eG = add_edge(_vdE, _vdG, _g).first;
        _eH = add_edge(_vdF, _vdG, _g).first;}

    virtual void CrossEdgeCyclic(){
        _vdA = add_vertex(_g);
        _vdB = add_vertex(_g);
        _vdC = add_vertex(_g);
        _vdD = add_vertex(_g);
        _vdE = add_vertex(_g);
        _vdF = add_vertex(_g);
        _vdG = add_vertex(_g);
        _vdH = add_vertex(_g);

        // _edAB = add_edge(_vdA, _vdB, _g).first;
        _eA = add_edge(_vdA, _vdC, _g).first;
        _eB = add_edge(_vdA, _vdD, _g).first;
        _eC = add_edge(_vdB, _vdE, _g).first;
        
        _eD = add_edge(_vdC, _vdG, _g).first;
        _eE = add_edge(_vdD, _vdG, _g).first;
        _eF = add_edge(_vdE, _vdF, _g).first;
        _eG = add_edge(_vdE, _vdG, _g).first;
        _eH = add_edge(_vdF, _vdB, _g).first;
        _eI = add_edge(_vdF, _vdG, _g).first;
        // _edGH = add_edge(_vdG, _vdH, _g).first;
    }

    virtual void sampleGraph(){
        _vdA = add_vertex(_g);
        _vdB = add_vertex(_g);
        _vdC = add_vertex(_g);
        _eA = add_edge(_vdA, _vdB, _g).first;
        _eB = add_edge(_vdA, _vdC, _g).first;
        // _eC = add_edge(_vdB, _vdE, _g).first;
    }
    
    virtual void sampleGraphCyclic(){
        _vdA = add_vertex(_g);
        _vdB = add_vertex(_g);
        _vdC = add_vertex(_g);
        _eA = add_edge(_vdA, _vdB, _g).first;
        _eB = add_edge(_vdB, _vdC, _g).first;
        _eC = add_edge(_vdC, _vdA, _g).first;
        // _eC = add_edge(_vdB, _vdE, _g).first;
    }

    virtual void sampleGraphOne(){
        _vdA = add_vertex(_g);
        _vdB = add_vertex(_g);
        _vdC = add_vertex(_g);
        _eA = add_edge(_vdA, _vdC, _g).first;
        _eB = add_edge(_vdB, _vdC, _g).first;
        // _eC = add_edge(_vdB, _vdE, _g).first;
    }};


//has cycle
TEST_F (CycleTests, test_sample_graph_cyclic){
    sampleGraphCyclic();
    EXPECT_TRUE(has_cycle(_g));}

TEST_F (CycleTests, test_sample_graph){
    sampleGraph();
    EXPECT_TRUE(!has_cycle(_g));}

TEST_F (CycleTests, test_sample_graph_1){
    sampleGraphOne();
    EXPECT_TRUE(!has_cycle(_g));}

TEST_F (CycleTests,test_has_cycle_1) {
        setupCyclic();
        EXPECT_TRUE(has_cycle(_g));}

TEST_F (CycleTests,test_has_cycle_2) {
        setupACyclic();
        EXPECT_TRUE(!has_cycle(_g));}

TEST_F (CycleTests,test_has_cycle_3) {
        CrossEdge();
        EXPECT_TRUE(!has_cycle(_g));}

TEST_F (CycleTests,test_has_cycle_4) {
        CrossEdgeCyclic();
        EXPECT_TRUE(has_cycle(_g));}





// // topological_sort
TEST_F (CycleTests,test_topological_sort_1) {
        setupACyclic();
        std::ostringstream out;
        topological_sort(_g, std::ostream_iterator<vertex_descriptor>(out, " "));
        EXPECT_TRUE(out.str() == "6 5 7 0 2 1 3 4 ");}

TEST_F (CycleTests,test_topological_sort_2) {
        setupCyclic();
        std::ostringstream out;
        try{
            topological_sort(_g, std::ostream_iterator<vertex_descriptor>(out, " "));
            EXPECT_TRUE(false);
        } catch (...){
            EXPECT_TRUE(true);
        }}

TEST_F (CycleTests,test_topological_sort_3) {
        CrossEdge();
        std::ostringstream out;
        topological_sort(_g, std::ostream_iterator<vertex_descriptor>(out, " "));
        EXPECT_TRUE(out.str() == "1 5 4 0 3 2 6 ");}

using namespace boost;
typedef testing::Types< adjacency_list<setS, vecS, directedS>, Graph > Containers;

// TYPED_TEST_CASE(DequeTest, MyDeques);
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

// add_edge
TYPED_TEST (Tests, add_edge_1) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->_vdA, this->_vdB, this->_g);
        EXPECT_TRUE(p.first  == this->_edAB);
        EXPECT_TRUE(p.second == false);}

TYPED_TEST (Tests, add_edge_2) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->_vdC, this->_vdD, this->_g);
        EXPECT_TRUE(p.first  == this->_edCD);
        EXPECT_TRUE(p.second == false);}

TYPED_TEST (Tests, add_edge_3) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->_vdA, this->_vdD, this->_g);
        // EXPECT_TRUE(p.first  == this->edAD);
        EXPECT_TRUE(p.second == true);}



// adjacent_vertices
TYPED_TEST (Tests, adjacent_vertices_1) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->_vdA, this->_g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        EXPECT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdB);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdC);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdE);}
        }

TYPED_TEST (Tests, adjacent_vertices_2) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->_vdB, this->_g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        EXPECT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdD);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdE);}}

TYPED_TEST (Tests, adjacent_vertices_3) {
        std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->_vdD, this->_g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        EXPECT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdE);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdF);}}



// edge
TYPED_TEST (Tests, test_edge_1) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->_vdA, this->_vdB, this->_g);
        EXPECT_TRUE(p.first  == this->_edAB);
        EXPECT_TRUE(p.second == true);}

TYPED_TEST (Tests, test_edge_2) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->_vdG, this->_vdH, this->_g);
        EXPECT_TRUE(p.first  == this->_edGH);
        EXPECT_TRUE(p.second == true);}

TYPED_TEST (Tests, test_edge_3) {
        std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->_vdE, this->_vdF, this->_g);
        // EXPECT_TRUE(p.first  == this->_edAB);
        EXPECT_TRUE(p.second == false);}



// edges
TYPED_TEST (Tests,test_edges_1) {
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->_g);
        typename TestFixture::edge_iterator b = p.first;
        typename TestFixture::edge_iterator e = p.second;
        EXPECT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            EXPECT_TRUE(ed == this->_edAB);}
        ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            EXPECT_TRUE(ed == this->_edAC);}}

TYPED_TEST (Tests,test_edges_2) {
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->_g);
        typename TestFixture::edge_iterator b = p.first;
        typename TestFixture::edge_iterator e = p.second;
        EXPECT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            EXPECT_TRUE(ed == this->_edAB);}
        ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            EXPECT_TRUE(ed == this->_edAC);}
        ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            EXPECT_TRUE(ed == this->_edAE);}
        }

TYPED_TEST (Tests,test_edges_3) {
        std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->_g);
        typename TestFixture::edge_iterator b = p.first;
        typename TestFixture::edge_iterator e = p.second;
        EXPECT_TRUE(b != e);
        ++b; ++b; ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            EXPECT_TRUE(ed == this->_edBD);}
        ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            EXPECT_TRUE(ed == this->_edBE);}
        ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            EXPECT_TRUE(ed == this->_edCD);}
        }



// num_edges
TYPED_TEST (Tests,test_num_edges_1) {
        typename TestFixture::edges_size_type es = num_edges(this->_g);
        EXPECT_TRUE(es == 11);}


TYPED_TEST (Tests,test_num_edges_2) {
        add_edge(this->_vdA, this->_vdD, this->_g);
        typename TestFixture::edges_size_type es = num_edges(this->_g);
        EXPECT_TRUE(es == 12);
        }

TYPED_TEST (Tests,test_num_edges_3) {
        add_edge(this->_vdA, this->_vdD, this->_g);
        add_edge(this->_vdA, this->_vdD, this->_g); // trying to add an existing edge
        typename TestFixture::edges_size_type es = num_edges(this->_g);
        EXPECT_TRUE(es == 12);
        }



// num_vertices
TYPED_TEST (Tests,test_num_vertices_1) {
        typename TestFixture::vertices_size_type vs = num_vertices(this->_g);
        EXPECT_TRUE(vs == 8);}

TYPED_TEST (Tests,test_num_vertices_2) {
        add_vertex(this->_g);
        typename TestFixture::vertices_size_type vs = num_vertices(this->_g);
        EXPECT_TRUE(vs == 9);}

TYPED_TEST (Tests,test_num_vertices_3) {
        add_vertex(this->_g);
        add_vertex(this->_g);
        typename TestFixture::vertices_size_type vs = num_vertices(this->_g);
        EXPECT_TRUE(vs == 10);}



// source
TYPED_TEST (Tests,test_source_1) {
        typename TestFixture::vertex_descriptor vd = source(this->_edAB, this->_g);
        EXPECT_TRUE(vd == this->_vdA);}

TYPED_TEST (Tests,test_source_2) {
        typename TestFixture::vertex_descriptor vd = source(this->_edCD, this->_g);
        EXPECT_TRUE(vd == this->_vdC);}

TYPED_TEST (Tests,test_source_3) {
        typename TestFixture::vertex_descriptor vd = source(this->_edCD, this->_g);
        EXPECT_TRUE(vd != this->_vdD);}



// target
TYPED_TEST (Tests,test_target_1) {
        typename TestFixture::vertex_descriptor vd = target(this->_edAB, this->_g);
        EXPECT_TRUE(vd == this->_vdB);}

TYPED_TEST (Tests,test_target_2) {
        typename TestFixture::vertex_descriptor vd = target(this->_edCD, this->_g);
        EXPECT_TRUE(vd == this->_vdD);}

TYPED_TEST (Tests,test_target_3) {
        typename TestFixture::vertex_descriptor vd = target(this->_edCD, this->_g);
        EXPECT_TRUE(vd != this->_vdC);}



// vertex
TYPED_TEST (Tests,test_vertex_1) {
        typename TestFixture::vertex_descriptor vd = vertex(0, this->_g);
        EXPECT_TRUE(vd == this->_vdA);}

TYPED_TEST (Tests,test_vertex_2) {
        typename TestFixture::vertex_descriptor vd = vertex(1, this->_g);
        EXPECT_TRUE(vd == this->_vdB);}

TYPED_TEST (Tests,test_vertex_3) {
        typename TestFixture::vertex_descriptor vd = vertex(7, this->_g);
        EXPECT_TRUE(vd == this->_vdH);}



//vertices
TYPED_TEST (Tests,test_vertices_1) {
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->_g);
        typename TestFixture::vertex_iterator b = p.first;
        typename TestFixture::vertex_iterator e = p.second;
        EXPECT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdA);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdB);}}

TYPED_TEST (Tests,test_vertices_2) {
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->_g);
        typename TestFixture::vertex_iterator b = p.first;
        typename TestFixture::vertex_iterator e = p.second;
        EXPECT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdA);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdB);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdC);}

        }

TYPED_TEST (Tests,test_vertices_3) {
        std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->_g);
        typename TestFixture::vertex_iterator b = p.first;
        typename TestFixture::vertex_iterator e = p.second;
        EXPECT_TRUE(b != e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdA);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdB);}
        ++b; ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            EXPECT_TRUE(vd == this->_vdD);}

        }

