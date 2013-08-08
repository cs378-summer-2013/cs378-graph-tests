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
    % g++ -ansi -pedantic -I/public/linux/include/boost-1_44 -lcppunit -ldl -Wall TestGraph.c++ -o TestGraph.app
    % valgrind TestGraph.app >& TestGraph.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

// #define private public
// #define protected public

// ---------
// TestGraph
// ---------

typedef testing::Types< Graph, boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> > GraphTypes;

template <typename T>
class GraphTest : public testing::Test {
    // --------
    // typedefs
    // --------
protected:
    typedef T                                       graph_type;

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

    // directed, sparse, unweighted
    // possibly connected
    // possibly cyclic
    graph_type g;

    graph_type dag;

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
    edge_descriptor edAD;
    edge_descriptor edAE;
    edge_descriptor edBD;
    edge_descriptor edBE;
    edge_descriptor edCD;
    edge_descriptor edCE;
    edge_descriptor edCF;
    edge_descriptor edDE;
    edge_descriptor edDF;
    edge_descriptor edED;
    edge_descriptor edFD;
    edge_descriptor edFH;
    edge_descriptor edGH;

    // -----
    // setUp
    // -----

    void SetUp () {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);
        vdE  = add_vertex(g);
        vdF  = add_vertex(g);
        vdG  = add_vertex(g);
        vdH  = add_vertex(g);
        edAB = add_edge(vdA, vdB, g).first;
        edAC = add_edge(vdA, vdC, g).first;
        edAE = add_edge(vdA, vdE, g).first;
        edBD = add_edge(vdB, vdD, g).first;
        edBE = add_edge(vdB, vdE, g).first;
        edCD = add_edge(vdC, vdD, g).first;
        edDE = add_edge(vdD, vdE, g).first;
        edDF = add_edge(vdD, vdF, g).first;
        edFD = add_edge(vdF, vdD, g).first;
        edFH = add_edge(vdF, vdH, g).first;
        edGH = add_edge(vdG, vdH, g).first;}

    void SetUpDag() {
        vdA  = add_vertex(dag);
        vdB  = add_vertex(dag);
        vdC  = add_vertex(dag);
        vdD  = add_vertex(dag);
        vdE  = add_vertex(dag);
        vdF  = add_vertex(dag);
        edAB = add_edge(vdA, vdB, dag).first;
        edAD = add_edge(vdA, vdD, dag).first;
        edBE = add_edge(vdB, vdE, dag).first;
        edCE = add_edge(vdC, vdE, dag).first;
        edCF = add_edge(vdC, vdF, dag).first;
        edED = add_edge(vdE, vdD, dag).first;
    }
};

TYPED_TEST_CASE(GraphTest, GraphTypes);

// ---------------
// test_add_vertex
// ---------------

TYPED_TEST(GraphTest, test_add_vertex_1) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor v = add_vertex(this->g);
    ASSERT_EQ(v, 8);}

TYPED_TEST(GraphTest, test_add_vertex_2) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor v1 = add_vertex(this->g);
    ASSERT_EQ(v1, 8);
    vertex_descriptor v2 = add_vertex(this->g);
    ASSERT_EQ(v2, 9);}

TYPED_TEST(GraphTest, test_add_vertex_3) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor v1 = add_vertex(this->g);
    ASSERT_EQ(v1, 8);
    vertex_descriptor v2 = add_vertex(this->g);
    ASSERT_EQ(v2, 9);
    vertex_descriptor v3 = add_vertex(this->g);
    ASSERT_EQ(v3, 10);}


// -------------
// test_add_edge
// -------------

TYPED_TEST(GraphTest, test_add_edge_1) {
    typedef typename TestFixture::edge_descriptor edge_descriptor; 
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(p.first, this->edAB);
    ASSERT_FALSE(p.second);}

TYPED_TEST(GraphTest, test_add_edge_2) {
    typedef typename TestFixture::edge_descriptor edge_descriptor; 
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
    ASSERT_TRUE(p.second);}

TYPED_TEST(GraphTest, test_add_edge_3) {
    typedef typename TestFixture::edge_descriptor edge_descriptor; 
    std::pair<edge_descriptor, bool> p1 = add_edge(this->vdB, this->vdA, this->g);
    ASSERT_TRUE(p1.second);
    
    std::pair<edge_descriptor, bool> p2 = add_edge(this->vdB, this->vdA, this->g);
    ASSERT_EQ(p1.first, p2.first);
    ASSERT_FALSE(p2.second);}   

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(GraphTest, test_adjacent_vertices_1) {
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdB);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdC);}}

TYPED_TEST(GraphTest, test_adjacent_vertices_2) {
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdB, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdD);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdE);}}

TYPED_TEST(GraphTest, test_adjacent_vertices_3) {
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdC, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdD);}
    ++b;
    ASSERT_EQ(b, e);}

// ---------
// test_edge
// ---------

TYPED_TEST(GraphTest, test_edge_1) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(p.first, this->edAB);
    ASSERT_TRUE(p.second);}

TYPED_TEST(GraphTest, test_edge_2) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdD, this->g);
    ASSERT_FALSE(p.second);}

TYPED_TEST(GraphTest, test_edge_3) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->vdD, this->vdF, this->g);
    ASSERT_EQ(p.first, this->edDF);
    ASSERT_TRUE(p.second);}

// ----------
// test_edges
// ----------

TYPED_TEST(GraphTest, test_edges_1) {
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(ed, this->edAB);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(ed, this->edAC);}}

TYPED_TEST(GraphTest, test_edges_2) {
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(ed, this->edAB);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(ed, this->edAC);}++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->edAE, ed);}}

TYPED_TEST(GraphTest, test_edges_3) {
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(ed, this->edAB);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(ed, this->edAC);}++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->edAE, ed);}++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->edBD, ed);}}

// --------------
// test_num_edges
// --------------

TYPED_TEST(GraphTest, test_num_edges_1) {
    typedef typename TestFixture::edges_size_type edges_size_type;
    edges_size_type es = num_edges(this->g);
    ASSERT_EQ(es, 11);}

TYPED_TEST(GraphTest, test_num_edges_2) {
    typedef typename TestFixture::edges_size_type edges_size_type;
    this->SetUpDag();
    edges_size_type es = num_edges(this->dag);
    ASSERT_EQ(es, 6);}

TYPED_TEST(GraphTest, test_num_edges_3) {
    typedef typename TestFixture::edges_size_type edges_size_type;
    TypeParam g;
    edges_size_type es = num_edges(this->dag);
    ASSERT_EQ(es, 0);}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST(GraphTest, test_num_vertices_1) {
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    vertices_size_type vs = num_vertices(this->g);
    ASSERT_EQ(vs, 8);}

TYPED_TEST(GraphTest, test_num_vertices_2) {
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    this->SetUpDag();
    vertices_size_type vs = num_vertices(this->dag);
    ASSERT_EQ(vs, 6);}

TYPED_TEST(GraphTest, test_num_vertices_3) {
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    TypeParam g;
    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(vs, 0);}

// -----------
// test_source
// -----------

TYPED_TEST(GraphTest, test_source_1) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edAB, this->g);
    ASSERT_EQ(vd, this->vdA);}

TYPED_TEST(GraphTest, test_source_2) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edCD, this->g);
    ASSERT_EQ(vd, this->vdC);}

TYPED_TEST(GraphTest, test_source_3) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edGH, this->g);
    ASSERT_EQ(vd, this->vdG);}

// -----------
// test_target
// -----------

TYPED_TEST(GraphTest, test_target_1) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edAB, this->g);
    ASSERT_EQ(vd, this->vdB);}

TYPED_TEST(GraphTest, test_target_2) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edCD, this->g);
    ASSERT_EQ(vd, this->vdD);}

TYPED_TEST(GraphTest, test_target_3) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edGH, this->g);
    ASSERT_EQ(vd, this->vdH);}

// -----------
// test_vertex
// -----------

TYPED_TEST(GraphTest, test_vertex_1) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(0, this->g);
    ASSERT_EQ(vd, this->vdA);}

TYPED_TEST(GraphTest, test_vertex_2) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(1, this->g);
    ASSERT_EQ(vd, this->vdB);}

TYPED_TEST(GraphTest, test_vertex_3) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(2, this->g);
    ASSERT_EQ(vd, this->vdC);}

// -------------
// test_vertices
// -------------

TYPED_TEST(GraphTest, test_vertices_1) {
    typedef typename TestFixture::vertex_iterator vertex_iterator; 
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdA);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdB);}}

TYPED_TEST(GraphTest, test_vertices_2) {
    typedef typename TestFixture::vertex_iterator vertex_iterator; 
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdA);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdB);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdC);}}

TYPED_TEST(GraphTest, test_vertices_3) {
    typedef typename TestFixture::vertex_iterator vertex_iterator; 
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdA);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdB);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdC);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdD);}}


// --------------
// test_has_cycle
// --------------

TYPED_TEST(GraphTest, test_has_cycle_1) {
    ASSERT_TRUE(has_cycle(this->g));}

TYPED_TEST(GraphTest, test_has_cycle_2) {
    this->SetUpDag();
    ASSERT_FALSE(has_cycle(this->dag));}

TYPED_TEST(GraphTest, test_has_cycle_3) {
    TypeParam g;
    ASSERT_FALSE(has_cycle(g));}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(GraphTest, test_topological_sort_1) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    try {
        topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_TRUE(false);
    }
    catch (boost::not_a_dag& e) {
        ASSERT_TRUE(has_cycle(this->g));}}

TYPED_TEST(GraphTest, test_topological_sort_2) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    this->SetUpDag();
    try {
        topological_sort(this->dag, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ("3 4 1 0 5 2 ", out.str());
    }
    catch (boost::not_a_dag& e) {
        ASSERT_TRUE(false);}}

TYPED_TEST(GraphTest, test_topological_sort_3) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    TypeParam g;
    try {
        topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ("", out.str());
    }
    catch (boost::not_a_dag& e) {
        ASSERT_TRUE(false);}}