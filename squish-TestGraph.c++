// -----------------
// cs378 Summer 2013
// Project 5 - Graph
// Daniel Floyd
// eid: floyddj
// -----------------

// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
To test the program:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

    % g++ -pedantic -std=c++0x -I/public/linux/include/boost-1_44 -Wall Graph.h TestGraph.c++ -o TestGraph -lgtest -lpthread -lgtest_main

    % valgrind TestGraph > TestGraph.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <vector>   // vector
#include <set>      // set
#include <list>     // list
#include <set>      // set
#include <queue>    // queue
#include <map>      // map

#include "boost/graph/adjacency_list.hpp"   // adjacency_list
#include "boost/graph/topological_sort.hpp" // topological_sort
#include "boost/graph/exception.hpp"        // not_a_dag

#include "gtest/gtest.h"

#define private public
#define protected public
#define class struct
#include "Graph.h"

// ---------
// TestGraph
// ---------

typedef typename boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> BoostGraph;
typedef testing::Types<Graph, BoostGraph> graphs;

template <typename T>
class SuppliedTest : public testing::Test {
protected:
    // --------
    // typedefs
    // --------

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    // ----
    // data
    // ----

    graph_type g;

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

    // -----
    // SetUp
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
        edGH = add_edge(vdG, vdH, g).first;
    }
};
TYPED_TEST_CASE(SuppliedTest, graphs);

// -------------
// test_add_edge
// -------------

TYPED_TEST(SuppliedTest, test_add_edge) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(this->edAB, p.first);
    EXPECT_FALSE(p.second);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(SuppliedTest, test_adjacent_vertices) {
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->vdB, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->vdC, vd);
    }
}

// ---------
// test_edge
// ---------

TYPED_TEST(SuppliedTest, test_edge) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
    EXPECT_TRUE(p.second);
    ASSERT_EQ(this->edAB, p.first);
}

// ----------
// test_edges
// ----------

TYPED_TEST(SuppliedTest, test_edges) {
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    EXPECT_NE(b, e);
    if(b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->edAB, ed);
    }
    ++b;
    if(b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->edAC, ed);
    }
}

// --------------
// test_num_edges
// --------------

TYPED_TEST(SuppliedTest, test_num_edges) {
    typedef typename TestFixture::edges_size_type edges_size_type;

    edges_size_type es = num_edges(this->g);
    ASSERT_EQ(11, es);
}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST(SuppliedTest, test_num_vertices) {
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    vertices_size_type vs = num_vertices(this->g);
    ASSERT_EQ(8, vs);
}

// -----------
// test_source
// -----------

TYPED_TEST(SuppliedTest, test_source) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edAB, this->g);

    ASSERT_EQ(this->vdA, vd);
}


// -----------
// test_target
// -----------

TYPED_TEST(SuppliedTest, test_target) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edAB, this->g);
    ASSERT_EQ(this->vdB, vd);
}

// -----------
// test_vertex
// -----------

TYPED_TEST(SuppliedTest, test_vertex) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(0, this->g);
    ASSERT_EQ(this->vdA, vd);
}

// -------------
// test_vertices
// -------------

TYPED_TEST(SuppliedTest, test_vertices) {
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->vdA, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->vdB, vd);
    }
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(SuppliedTest, test_has_cycle) {
    ASSERT_TRUE(has_cycle(this->g));
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(SuppliedTest, test_topological_sort) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;

    ASSERT_THROW(topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " ")), boost::not_a_dag);
}


template <typename T>
class InterfaceTest_nocycle : public testing::Test {
protected:
    // --------
    // typedefs
    // --------

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    // ----
    // data
    // ----

    graph_type my_g;

    vertex_descriptor my_vd0;
    vertex_descriptor my_vd1;
    vertex_descriptor my_vd2;
    vertex_descriptor my_vd3;
    vertex_descriptor my_vd4;
    vertex_descriptor my_vd5;
    vertex_descriptor my_vd6;
    vertex_descriptor my_vd7;

    edge_descriptor my_ed01;
    edge_descriptor my_ed02;
    edge_descriptor my_ed04;
    edge_descriptor my_ed13;
    edge_descriptor my_ed14;
    edge_descriptor my_ed23;
    edge_descriptor my_ed34;
    edge_descriptor my_ed35;
    edge_descriptor my_ed57;
    edge_descriptor my_ed67;

    // -----
    // SetUp
    // -----

    void SetUp () {
        my_vd0  = add_vertex(this->my_g);
        my_vd1  = add_vertex(this->my_g);
        my_vd2  = add_vertex(this->my_g);
        my_vd3  = add_vertex(this->my_g);
        my_vd4  = add_vertex(this->my_g);
        my_vd5  = add_vertex(this->my_g);
        my_vd6  = add_vertex(this->my_g);
        my_vd7  = add_vertex(this->my_g);
        my_ed01 = add_edge(my_vd0, my_vd1, this->my_g).first;
        my_ed02 = add_edge(my_vd0, my_vd2, this->my_g).first;
        my_ed04 = add_edge(my_vd0, my_vd4, this->my_g).first;
        my_ed13 = add_edge(my_vd1, my_vd3, this->my_g).first;
        my_ed14 = add_edge(my_vd1, my_vd4, this->my_g).first;
        my_ed23 = add_edge(my_vd2, my_vd3, this->my_g).first;
        my_ed34 = add_edge(my_vd3, my_vd4, this->my_g).first;
        my_ed35 = add_edge(my_vd3, my_vd5, this->my_g).first;
        my_ed57 = add_edge(my_vd5, my_vd7, this->my_g).first;
        my_ed67 = add_edge(my_vd6, my_vd7, this->my_g).first;
    }
};
TYPED_TEST_CASE(InterfaceTest_nocycle, graphs);

// -------------
// test_add_edge
// -------------

TYPED_TEST(InterfaceTest_nocycle, test_add_edge) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->my_vd0, this->my_vd1, this->my_g);
    ASSERT_EQ(this->my_ed01, p.first);
    EXPECT_FALSE(p.second);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(InterfaceTest_nocycle, test_adjacent_vertices) {
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->my_vd0, this->my_g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd1, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd2, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd4, vd);
    }
}

// ---------
// test_edge
// ---------

TYPED_TEST(InterfaceTest_nocycle, test_edge) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->my_vd0, this->my_vd1, this->my_g);
    EXPECT_TRUE(p.second);
    ASSERT_EQ(this->my_ed01, p.first);
}

// ----------
// test_edges
// ----------

TYPED_TEST(InterfaceTest_nocycle, test_edges) {
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_iterator, edge_iterator> p = edges(this->my_g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    EXPECT_NE(b, e);
    if(b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->my_ed01, ed);
    }
    ++b;
    if(b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->my_ed02, ed);
    }
}

// --------------
// test_num_edges
// --------------

TYPED_TEST(InterfaceTest_nocycle, test_num_edges) {
    typedef typename TestFixture::edges_size_type edges_size_type;

    edges_size_type es = num_edges(this->my_g);
    ASSERT_EQ(10, es);
}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST(InterfaceTest_nocycle, test_num_vertices) {
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    vertices_size_type vs = num_vertices(this->my_g);
    ASSERT_EQ(8, vs);
}

// -----------
// test_source
// -----------

TYPED_TEST(InterfaceTest_nocycle, test_source) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->my_ed02, this->my_g);

    ASSERT_EQ(this->my_vd0, vd);
}


// -----------
// test_target
// -----------

TYPED_TEST(InterfaceTest_nocycle, test_target) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->my_ed02, this->my_g);
    ASSERT_EQ(this->my_vd2, vd);
}

// -----------
// test_vertex
// -----------

TYPED_TEST(InterfaceTest_nocycle, test_vertex) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(0, this->my_g);
    ASSERT_EQ(this->my_vd0, vd);
}

// -------------
// test_vertices
// -------------

TYPED_TEST(InterfaceTest_nocycle, test_vertices) {
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->my_g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd0, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd1, vd);
    }
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(InterfaceTest_nocycle, test_has_cycle) {
    ASSERT_FALSE(has_cycle(this->my_g));
}


// -----------------
// test_num_vertices
// -----------------

TYPED_TEST(InterfaceTest_nocycle, num_vertices_01) {
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    vertices_size_type sz = num_vertices(this->my_g);
    ASSERT_EQ(8, sz);
}

// --------------
// test_num_edges
// --------------

TYPED_TEST(InterfaceTest_nocycle, test_num_edges01) {
    typedef typename TestFixture::edges_size_type edges_size_type;
    edges_size_type sz = num_edges(this->my_g);
    ASSERT_EQ(10, sz);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(InterfaceTest_nocycle, test_adjacent_vertices_01) {
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p0, p1, p2, p3, p4, p5, p6, p7;
    p0 = adjacent_vertices(this->my_vd0, this->my_g);
    p1 = adjacent_vertices(this->my_vd1, this->my_g);
    p2 = adjacent_vertices(this->my_vd2, this->my_g);
    p3 = adjacent_vertices(this->my_vd3, this->my_g);
    p4 = adjacent_vertices(this->my_vd4, this->my_g);
    p5 = adjacent_vertices(this->my_vd5, this->my_g);
    p6 = adjacent_vertices(this->my_vd6, this->my_g);
    p7 = adjacent_vertices(this->my_vd7, this->my_g);
    EXPECT_EQ(3, std::distance(p0.first, p0.second));
    EXPECT_EQ(2, std::distance(p1.first, p1.second));
    EXPECT_EQ(1, std::distance(p2.first, p2.second));
    EXPECT_EQ(2, std::distance(p3.first, p3.second));
    EXPECT_EQ(0, std::distance(p4.first, p4.second));
    EXPECT_EQ(1, std::distance(p5.first, p5.second));
    EXPECT_EQ(1, std::distance(p6.first, p6.second));
    EXPECT_EQ(0, std::distance(p7.first, p7.second));
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(InterfaceTest_nocycle, test_topological_sort_01) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;

    topological_sort(this->my_g, std::ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ("4 7 5 3 1 2 0 6 ", out.str());
}

template <typename T>
class InterfaceTest_unconnected : public testing::Test {
protected:
    // --------
    // typedefs
    // --------

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    // ----
    // data
    // ----

    graph_type my_g;

    vertex_descriptor my_vd0;
    vertex_descriptor my_vd1;
    vertex_descriptor my_vd2;
    vertex_descriptor my_vd3;
    vertex_descriptor my_vd4;
    vertex_descriptor my_vd5;

    edge_descriptor my_ed01;
    edge_descriptor my_ed12;
    edge_descriptor my_ed34;
    edge_descriptor my_ed45;

    // -----
    // SetUp
    // -----

    void SetUp () {
        my_vd0  = add_vertex(this->my_g);
        my_vd1  = add_vertex(this->my_g);
        my_vd2  = add_vertex(this->my_g);
        my_vd3  = add_vertex(this->my_g);
        my_vd4  = add_vertex(this->my_g);
        my_vd5  = add_vertex(this->my_g);

        my_ed01 = add_edge(my_vd0, my_vd1, this->my_g).first;
        my_ed12 = add_edge(my_vd1, my_vd2, this->my_g).first;
        my_ed34 = add_edge(my_vd3, my_vd4, this->my_g).first;
        my_ed45 = add_edge(my_vd4, my_vd5, this->my_g).first;
    }
};
TYPED_TEST_CASE(InterfaceTest_unconnected, graphs);

TYPED_TEST(InterfaceTest_unconnected, test_add_edge) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->my_vd3, this->my_vd4, this->my_g);
    ASSERT_EQ(this->my_ed34, p.first);
    EXPECT_FALSE(p.second);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(InterfaceTest_unconnected, test_adjacent_vertices) {
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->my_vd3, this->my_g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd4, vd);
    }
    ++b;
    if (b != e) {
        ASSERT_TRUE(false);
    }
}

// ---------
// test_edge
// ---------

TYPED_TEST(InterfaceTest_unconnected, test_edge) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->my_vd3, this->my_vd4, this->my_g);
    EXPECT_TRUE(p.second);
    ASSERT_EQ(this->my_ed34, p.first);
}

// ----------
// test_edges
// ----------

TYPED_TEST(InterfaceTest_unconnected, test_edges) {
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_iterator, edge_iterator> p = edges(this->my_g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    EXPECT_NE(b, e);
    if(b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->my_ed01, ed);
    }
    ++b;
    EXPECT_NE(b, e);
    if(b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->my_ed12, ed);
    }
    ++b;
    EXPECT_NE(b, e);
    if(b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->my_ed34, ed);
    }
    ++b;
    EXPECT_NE(b, e);
    if(b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(this->my_ed45, ed);
    }
    ++b;
    EXPECT_EQ(b, e);
    if(b != e) {
        ASSERT_TRUE(false);
    }
}

// --------------
// test_num_edges
// --------------

TYPED_TEST(InterfaceTest_unconnected, test_num_edges) {
    typedef typename TestFixture::edges_size_type edges_size_type;

    edges_size_type es = num_edges(this->my_g);
    ASSERT_EQ(4, es);
}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST(InterfaceTest_unconnected, test_num_vertices) {
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    vertices_size_type vs = num_vertices(this->my_g);
    ASSERT_EQ(6, vs);
}

// -----------
// test_source
// -----------

TYPED_TEST(InterfaceTest_unconnected, test_source) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->my_ed45, this->my_g);

    ASSERT_EQ(this->my_vd4, vd);
}


// -----------
// test_target
// -----------

TYPED_TEST(InterfaceTest_unconnected, test_target) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->my_ed45, this->my_g);
    ASSERT_EQ(this->my_vd5, vd);
}

// -----------
// test_vertex
// -----------

TYPED_TEST(InterfaceTest_unconnected, test_vertex) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(0, this->my_g);
    ASSERT_EQ(this->my_vd0, vd);
}

// -------------
// test_vertices
// -------------

TYPED_TEST(InterfaceTest_unconnected, test_vertices) {
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->my_g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd0, vd);
    }
    ++b;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd1, vd);
    }
    ++b;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd2, vd);
    }
    ++b;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd3, vd);
    }
    ++b;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd4, vd);
    }
    ++b;
    EXPECT_NE(b, e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(this->my_vd5, vd);
    }
    ++b;
    EXPECT_EQ(b, e);
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(InterfaceTest_unconnected, test_has_cycle) {
    ASSERT_FALSE(has_cycle(this->my_g));
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(InterfaceTest_unconnected, test_topological_sort_01) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;

    topological_sort(this->my_g, std::ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ("2 1 0 5 4 3 ", out.str());
}

template <typename T>
class Topological : public testing::Test {
protected:
    // --------
    // typedefs
    // --------

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    // ----
    // data
    // ----

    graph_type my_g;

    vertex_descriptor my_vd0;
    vertex_descriptor my_vd1;
    vertex_descriptor my_vd2;
    vertex_descriptor my_vd3;
    vertex_descriptor my_vd4;
    vertex_descriptor my_vd5;
    vertex_descriptor my_vd6;
    vertex_descriptor my_vd7;
    vertex_descriptor my_vd8;
    vertex_descriptor my_vd9;
    vertex_descriptor my_vd10;
    vertex_descriptor my_vd11;
    vertex_descriptor my_vd12;
    vertex_descriptor my_vd13;
    vertex_descriptor my_vd14;
    vertex_descriptor my_vd15;

    edge_descriptor my_ed01;
    edge_descriptor my_ed12;
    edge_descriptor my_ed23;
    edge_descriptor my_ed34;
    edge_descriptor my_ed35;
    edge_descriptor my_ed56;
    edge_descriptor my_ed67;
    edge_descriptor my_ed68;
    edge_descriptor my_ed78;
    edge_descriptor my_ed89;
    edge_descriptor my_ed1011;
    edge_descriptor my_ed1213;
    edge_descriptor my_ed138;
    edge_descriptor my_ed1415;
    edge_descriptor my_ed158;

    // -----
    // SetUp
    // -----

    void SetUp () {
        my_vd0  = add_vertex(this->my_g);
        my_vd1  = add_vertex(this->my_g);
        my_vd2  = add_vertex(this->my_g);
        my_vd3  = add_vertex(this->my_g);
        my_vd4  = add_vertex(this->my_g);
        my_vd5  = add_vertex(this->my_g);
        my_vd6  = add_vertex(this->my_g);
        my_vd7  = add_vertex(this->my_g);
        my_vd8  = add_vertex(this->my_g);
        my_vd9  = add_vertex(this->my_g);
        my_vd10 = add_vertex(this->my_g);
        my_vd11 = add_vertex(this->my_g);
        my_vd12 = add_vertex(this->my_g);
        my_vd13 = add_vertex(this->my_g);
        my_vd14 = add_vertex(this->my_g);
        my_vd15 = add_vertex(this->my_g);

        my_ed01   = add_edge(my_vd0,  my_vd1,  this->my_g).first;
        my_ed12   = add_edge(my_vd1,  my_vd2,  this->my_g).first;
        my_ed23   = add_edge(my_vd2,  my_vd3,  this->my_g).first;
        my_ed34   = add_edge(my_vd3,  my_vd4,  this->my_g).first;
        my_ed35   = add_edge(my_vd3,  my_vd5,  this->my_g).first;
        my_ed56   = add_edge(my_vd5,  my_vd6,  this->my_g).first;
        my_ed67   = add_edge(my_vd6,  my_vd7,  this->my_g).first;
        my_ed68   = add_edge(my_vd6,  my_vd8,  this->my_g).first;
        my_ed89   = add_edge(my_vd8,  my_vd9,  this->my_g).first;
        my_ed1011 = add_edge(my_vd10, my_vd11, this->my_g).first;
        my_ed1213 = add_edge(my_vd12, my_vd13, this->my_g).first;
        my_ed138  = add_edge(my_vd13, my_vd8,  this->my_g).first;
        my_ed1415 = add_edge(my_vd14, my_vd15, this->my_g).first;
        my_ed158  = add_edge(my_vd15, my_vd8,  this->my_g).first;
    }
};
TYPED_TEST_CASE(Topological, graphs);

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(Topological, test_topological_sort) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;

    topological_sort(this->my_g, std::ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ( "4 7 9 8 6 5 3 2 1 0 11 10 13 12 15 14 ", out.str());
}
