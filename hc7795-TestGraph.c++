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

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <deque>
#include <cstdlib>
#include <climits>
#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <vector>  // vector
#include <stack>   // stack
#include <set>     // set

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h" //Google Test

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
    
    
    graph_type sampleAcyclicG;
    graph_type acyclicG;
    graph_type cyclicG;
    
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
    edge_descriptor edFH;
    edge_descriptor edGH;
    edge_descriptor edEA;
    
    
    virtual void setUP_sampleAcyclic () {
        vdA  = add_vertex( sampleAcyclicG);
        vdB  = add_vertex( sampleAcyclicG);
        vdC  = add_vertex( sampleAcyclicG);
        vdE  = add_vertex( sampleAcyclicG);
        edAB = add_edge(vdA, vdB, sampleAcyclicG).first;
        edAC = add_edge(vdA, vdC, sampleAcyclicG).first;
        edAE = add_edge(vdA, vdE, sampleAcyclicG).first;
    }
    
    virtual void setUp_acyclic () {
        vdA  = add_vertex( acyclicG);
        vdB  = add_vertex( acyclicG);
        vdC  = add_vertex( acyclicG);
        vdD  = add_vertex( acyclicG);
        vdE  = add_vertex( acyclicG);
        vdF  = add_vertex( acyclicG);
        vdG  = add_vertex( acyclicG);
        vdH  = add_vertex( acyclicG);
        edAB = add_edge( vdA,  vdB,  acyclicG).first;
        edAC = add_edge( vdA,  vdC,  acyclicG).first;
        edAE = add_edge( vdA,  vdE,  acyclicG).first;
        edBD = add_edge( vdB,  vdD,  acyclicG).first;
        edBE = add_edge( vdB,  vdE,  acyclicG).first;
        edCD = add_edge( vdC,  vdD,  acyclicG).first;
        edDE = add_edge( vdD,  vdE,  acyclicG).first;
        edDF = add_edge( vdD,  vdF,  acyclicG).first;
        edFH = add_edge( vdF,  vdH,  acyclicG).first;
        edGH = add_edge( vdG,  vdH,  acyclicG).first;
    }
    virtual void SetUp_cyclic() {
        vdA  = add_vertex( cyclicG);
        vdB  = add_vertex( cyclicG);
        vdC  = add_vertex( cyclicG);
        vdD  = add_vertex( cyclicG);
        vdE  = add_vertex( cyclicG);
        vdF  = add_vertex( cyclicG);
        vdG  = add_vertex( cyclicG);
        vdH  = add_vertex( cyclicG);
        edAB = add_edge( vdA,  vdB,  cyclicG).first;
        edAC = add_edge( vdA,  vdC,  cyclicG).first;
        edEA = add_edge( vdE,  vdA,  cyclicG).first;
        edBD = add_edge( vdB,  vdD,  cyclicG).first;
        edBE = add_edge( vdB,  vdE,  cyclicG).first;
        edCD = add_edge( vdC,  vdD,  cyclicG).first;
        edDE = add_edge( vdD,  vdE,  cyclicG).first;
        edDF = add_edge( vdD,  vdF,  cyclicG).first;
        edFH = add_edge( vdF,  vdH,  cyclicG).first;
        edGH = add_edge( vdG,  vdH,  cyclicG).first;
    }
};

typedef testing::Types< Graph, boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> > MyGraphs;

TYPED_TEST_CASE(TestGraph, MyGraphs);


// -------------
// test_add_edge
// -------------

TYPED_TEST(TestGraph , test_add_edges_1)
{
    this->setUp_acyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->vdG, this->vdH, this->acyclicG);
    ASSERT_TRUE(p.first == this->edGH);
    ASSERT_FALSE(p.second);
}

TYPED_TEST(TestGraph , test_add_edges_2)
{
    this->setUp_acyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->vdF, this->vdG, this->acyclicG);
    ASSERT_TRUE(p.second);
}


TYPED_TEST(TestGraph , test_add_edges_3)
{
    this->setUp_acyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->vdB, this->vdE, this->acyclicG);
    ASSERT_FALSE(p.second);
}

// -------------
// test_add_vertex
// -------------

TYPED_TEST(TestGraph , test_add_vertex_1)
{
    this->setUp_acyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->acyclicG);
    ASSERT_TRUE(v == 8);
}

TYPED_TEST(TestGraph , test_add_vertex_2)
{
    this->setUP_sampleAcyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->sampleAcyclicG);
    ASSERT_TRUE(v == 4);
}

TYPED_TEST(TestGraph , test_add_vertex_3)
{
    this->SetUp_cyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->cyclicG);
    ASSERT_TRUE(v == 8);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(TestGraph, test_adjacent_vertices_1)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this -> setUP_sampleAcyclic();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->sampleAcyclicG);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->vdB);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->vdE);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_2)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this -> setUp_acyclic();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdD, this->acyclicG);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->vdE);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->vdF);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_3)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this -> SetUp_cyclic();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdB, this->cyclicG);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->vdD);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->vdE);
}

// ---------
// test_edge
// ---------

TYPED_TEST(TestGraph, test_edge_1)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this -> setUP_sampleAcyclic();
    pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->sampleAcyclicG);
    ASSERT_TRUE(p.first  == this->edAB);
    ASSERT_TRUE(p.second );
}

TYPED_TEST(TestGraph, test_edge_2)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this -> setUp_acyclic();
    pair<edge_descriptor, bool> p = edge(this->vdB, this->vdD, this->acyclicG);
    ASSERT_TRUE(p.first  == this->edBD);
    ASSERT_TRUE(p.second);
}

TYPED_TEST(TestGraph, test_edge_3)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this -> setUP_sampleAcyclic();
    pair<edge_descriptor, bool> p = edge(this->vdE, this->vdF, this->sampleAcyclicG);
    ASSERT_FALSE(p.second );
}

// ----------
// test_edges
// ----------

TYPED_TEST(TestGraph, test_edges_1)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this -> setUP_sampleAcyclic();
    std::pair<edge_iterator, edge_iterator> p = edges(this->sampleAcyclicG);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor ebegin = *b;
    ASSERT_TRUE(ebegin == this->edAB);
    ++b;
    edge_descriptor eend = *b;
    ASSERT_TRUE(eend == this->edAC);
}

TYPED_TEST(TestGraph, test_edges_2)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this -> setUp_acyclic();
    std::pair<edge_iterator, edge_iterator> p = edges(this->acyclicG);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor ebegin = *b;
    ASSERT_TRUE(ebegin == this->edAB);
    ++b;
    edge_descriptor eend = *b;
    ASSERT_TRUE(eend == this->edAC);
}

TYPED_TEST(TestGraph, test_edges_3)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this -> SetUp_cyclic();
    std::pair<edge_iterator, edge_iterator> p = edges(this->cyclicG);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor ebegin = *b;
    ASSERT_TRUE(ebegin == this->edAB);
    ++b;
    edge_descriptor eend = *b;
    ASSERT_TRUE(eend == this->edAC);
}

// --------------
// test_num_edges
// --------------

TYPED_TEST (TestGraph, test_num_edges_1)
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    this->setUP_sampleAcyclic();
    edges_size_type es = num_edges(this->sampleAcyclicG);
    ASSERT_TRUE(es == 3);
}

TYPED_TEST (TestGraph, test_num_edges_2)
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    this -> setUp_acyclic();
    edges_size_type es = num_edges(this->acyclicG);
    ASSERT_TRUE(es == 10);
}

TYPED_TEST (TestGraph, test_num_edges_3)
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    this -> SetUp_cyclic();
    edges_size_type es = num_edges(this->cyclicG);
    ASSERT_TRUE(es == 10);
}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST (TestGraph, test_num_vertices_1)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    this->setUP_sampleAcyclic();
    vertices_size_type vs = num_vertices(this->sampleAcyclicG);
    ASSERT_TRUE(vs == 4);
}

TYPED_TEST (TestGraph, test_num_vertices_2)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    this -> setUp_acyclic();
    vertices_size_type vs = num_vertices(this->acyclicG);
    ASSERT_TRUE(vs == 8);
}

TYPED_TEST (TestGraph, test_num_vertices_3)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    this -> SetUp_cyclic();
    vertices_size_type vs = num_vertices(this->cyclicG);
    ASSERT_TRUE(vs == 8);
}

// -----------
// test_source
// -----------

TYPED_TEST(TestGraph, test_source_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setUP_sampleAcyclic();
    vertex_descriptor vd = source(this->edAB, this->sampleAcyclicG);
    ASSERT_TRUE(vd == this->vdA);
}

TYPED_TEST(TestGraph, test_source_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setUp_acyclic();
    vertex_descriptor vd = source(this->edFH, this->acyclicG);
    ASSERT_TRUE(vd == this->vdF);
}

TYPED_TEST(TestGraph, test_source_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> SetUp_cyclic();
    vertex_descriptor vd = source(this->edDF, this->cyclicG);
    ASSERT_TRUE(vd == this->vdD);
}

// -----------
// test_target
// -----------

TYPED_TEST(TestGraph, test_target_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setUP_sampleAcyclic();
    vertex_descriptor vd = target(this->edAB, this->sampleAcyclicG);
    ASSERT_TRUE(vd == this->vdB);
}

TYPED_TEST(TestGraph, test_target_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setUp_acyclic();
    vertex_descriptor vd = target(this->edFH, this->acyclicG);
    ASSERT_TRUE(vd == this->vdH);
}

TYPED_TEST(TestGraph, test_target_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> SetUp_cyclic();
    vertex_descriptor vd = target(this->edDF, this->cyclicG);
    ASSERT_TRUE(vd == this->vdF);
}

// -----------
// test_vertex
// -----------

TYPED_TEST (TestGraph, test_vertex_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setUP_sampleAcyclic();
    vertex_descriptor vd = vertex(1, this->sampleAcyclicG);
    ASSERT_TRUE(vd == this->vdB);
}

TYPED_TEST (TestGraph, test_vertex_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setUp_acyclic();
    vertex_descriptor vd = vertex(3, this->acyclicG);
    ASSERT_TRUE(vd == this->vdD);
}

TYPED_TEST (TestGraph, test_vertex_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> SetUp_cyclic();
    vertex_descriptor vd = vertex(5, this->cyclicG);
    ASSERT_TRUE(vd == this->vdF);
}

// -------------
// test_vertices
// -------------


TYPED_TEST(TestGraph, test_vertices_1)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setUP_sampleAcyclic();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->sampleAcyclicG);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->vdA);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->vdE);
}

TYPED_TEST(TestGraph, test_vertices_2)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setUp_acyclic();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->acyclicG);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->vdA);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->vdH);
}

TYPED_TEST(TestGraph, test_vertices_3)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> SetUp_cyclic();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->cyclicG);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->vdA);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->vdH);
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraph, test_has_cycle_1)
{
    this->setUP_sampleAcyclic();
    ASSERT_FALSE(has_cycle(this->sampleAcyclicG));
}

TYPED_TEST(TestGraph, test_has_cycle_2)
{
    this->setUp_acyclic();
    ASSERT_FALSE(has_cycle(this->acyclicG));
}

TYPED_TEST(TestGraph, test_has_cycle_3)
{
    this->SetUp_cyclic();
    ASSERT_TRUE(has_cycle(this->cyclicG));
}


// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST (TestGraph, test_topological_sort_no_cycle_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->setUp_acyclic();
    
    ostringstream out;
    try{
        topological_sort(this->acyclicG, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string("4 7 5 3 1 2 0 6 "), out.str());
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(false);
    }
}


TYPED_TEST (TestGraph, test_topological_sort_no_cycle_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->SetUp_cyclic();
    
    ostringstream out;
    try{
        topological_sort(this->cyclicG, ostream_iterator<vertex_descriptor>(out, " "));
        EXPECT_TRUE(false);
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(true);
    }
}

TYPED_TEST (TestGraph, test_topological_sort_no_cycle_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->setUP_sampleAcyclic();
    
    ostringstream out;
    try{
        topological_sort(this->sampleAcyclicG, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string("1 2 3 0 "), out.str());
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(false);
    }
}


