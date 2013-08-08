// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2013
// Kevin Tran
// Pratik Patel
// CS378 Summer 2013
// ----------------------

// TestGraph
#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <string>   // string

#include "boost/graph/adjacency_list.hpp"  // adjacency_list

#include "gtest/gtest.h"

// Include Graph's required headers before the compiler defines
#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector

#define private public
#define protected public
#define class struct
#include "Graph.h"





// These are interface tests
typedef testing::Types<Graph, boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> > graphs;

template <typename T>
class TestCases : public testing::Test {
protected:
    // --- typedefs ---

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    graph_type g;
    graph_type ncg;
    graph_type gcomplex;

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
    edge_descriptor edHA;

    edge_descriptor edBC;
    edge_descriptor edAG;
    edge_descriptor edHB;




    // --- Setups ---
    void SetUp () {

    }

    void DefSetup(){
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

    void nc() {
        vdA  = add_vertex(ncg);
        vdB  = add_vertex(ncg);
        vdC  = add_vertex(ncg);
        vdD  = add_vertex(ncg);
        vdE  = add_vertex(ncg);
        vdF  = add_vertex(ncg);
        vdG  = add_vertex(ncg);
        vdH  = add_vertex(ncg);

        edAB = add_edge(vdA, vdB, ncg).first;
        edAC = add_edge(vdA, vdC, ncg).first;
        edAE = add_edge(vdA, vdE, ncg).first;
        edBD = add_edge(vdB, vdD, ncg).first;
        edBE = add_edge(vdB, vdE, ncg).first;
        edCD = add_edge(vdC, vdD, ncg).first;
        edDE = add_edge(vdD, vdE, ncg).first;
        edDF = add_edge(vdD, vdF, ncg).first;
        edFH = add_edge(vdF, vdH, ncg).first;
        edGH = add_edge(vdG, vdH, ncg).first;
    }


     void cyclic () {
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


    void ccomplex () {
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
        edFH = add_edge(vdF, vdH, g).first;
        edGH = add_edge(vdG, vdH, g).first;
        edHA = add_edge(vdH, vdA, g).first;
    }


    void weird_case()
    {
        add_edge(2,26, gcomplex);
    }

    void cyclic2 () {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);
        vdE  = add_vertex(g);
        vdF  = add_vertex(g);
        vdG  = add_vertex(g);
        vdH  = add_vertex(g);
        edAB = add_edge(vdA, vdB, g).first;
        edBC = add_edge(vdB, vdC, g).first;
        edCD = add_edge(vdC, vdD, g).first;
        edDF = add_edge(vdD, vdF, g).first;
        edAG = add_edge(vdA, vdG, g).first;
        edGH = add_edge(vdG, vdH, g).first;
        edHB = add_edge(vdH, vdB, g).first;
    }

};




TYPED_TEST_CASE(TestCases, graphs);

TYPED_TEST(TestCases, weird_test_1) {
    this->weird_case();
    ASSERT_EQ(vertex(99, this->gcomplex), 99);
}

TYPED_TEST(TestCases, weird_test_2) {
    this->weird_case();
    ASSERT_EQ(num_vertices(this->gcomplex), 27);
}

TYPED_TEST(TestCases, weird_test_3) {
    this->weird_case();
    ASSERT_EQ(num_edges(this->gcomplex), 1);
}



// --- has cycle ---

TYPED_TEST(TestCases, has_cycle_1) {
    this->cyclic();
    ASSERT_TRUE(has_cycle(this->g));
}


TYPED_TEST(TestCases, has_cycle_2) {
    this->nc();
    ASSERT_FALSE(has_cycle(this->ncg));
}

TYPED_TEST(TestCases, has_cycle_3) {
    this->ccomplex();
    ASSERT_TRUE(has_cycle(this->g));
}

TYPED_TEST(TestCases, has_cycle_4) {
    this->cyclic2();
    ASSERT_FALSE(has_cycle(this->g));
}

// --- add_vertex ---

TYPED_TEST(TestCases, add_vertex_test_1) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor p = add_vertex(this->g);
    EXPECT_EQ(8, p);
}

TYPED_TEST(TestCases, add_vertex_test_2) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor p = add_vertex(this->g);
    ASSERT_EQ(8, p);
    p = add_vertex(this->g);
    ASSERT_EQ(9, p);
}

TYPED_TEST(TestCases, add_vertex_test_3) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor p = add_vertex(this->g);
    EXPECT_EQ(8, p);
    p = add_vertex(this->g);
    ASSERT_EQ(9, p);
    p = add_vertex(this->g);
    ASSERT_EQ(10, p);
}

TYPED_TEST(TestCases, add_vertex_test_4) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor p = add_vertex(this->g);
    EXPECT_EQ(8, p);
    p = add_vertex(this->g);
    ASSERT_EQ(9, p);
    p = add_vertex(this->g);
    ASSERT_EQ(10, p);
    p = add_vertex(this->g);
    ASSERT_EQ(11, p);
    p = add_vertex(this->g);
    ASSERT_EQ(12, p);
    p = add_vertex(this->g);
    ASSERT_EQ(13, p);
    p = add_vertex(this->g);
    ASSERT_EQ(14, p);
    p = add_vertex(this->g);
    ASSERT_EQ(15, p);
    p = add_vertex(this->g);
    ASSERT_EQ(16, p);
}

// --- add_edge ---

TYPED_TEST(TestCases, add_edge_test_1) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
    EXPECT_EQ(this->edAB, p.first);
    EXPECT_FALSE(p.second);
}

TYPED_TEST(TestCases, add_edge_test_2) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
    EXPECT_TRUE(p.second);
}

TYPED_TEST(TestCases, add_edge_test_3) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
    ASSERT_TRUE(p.second);

    std::pair<edge_descriptor, bool> p2 = add_edge(this->vdA, this->vdH, this->g);
    EXPECT_EQ(p.first, p2.first);
    EXPECT_FALSE(p2.second);
}

TYPED_TEST(TestCases, add_edge_test_4) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, 3, this->g);

    ASSERT_TRUE(p.second);
    ASSERT_EQ(12, num_edges(this->g));
    ASSERT_EQ(8, num_vertices(this->g));
}

TYPED_TEST(TestCases, add_edge_test_5) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, 3, this->g);
    p = add_edge(this->vdA, 10, this->g);

    ASSERT_TRUE(p.second);
    ASSERT_EQ(13, num_edges(this->g));
    //ASSERT_EQ(1, num_vertices(this->g));      //Don't work for some reason -- boost segfaults :P
}

// --- ajacent_vertices ---

TYPED_TEST(TestCases, adjacent_vertices_test_1) {
    this->DefSetup();
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdB, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdC, vd);
    }
}

TYPED_TEST(TestCases, adjacent_vertices_test_2) {
    this->DefSetup();
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdB, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdC, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdE, vd);
    }
}

TYPED_TEST(TestCases, adjacent_vertices_test_3) {
    this->DefSetup();
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdB, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdD, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdE, vd);
    }
}

TYPED_TEST(TestCases, adjacent_vertices_test_4) {
    this->cyclic2();
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdB, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdG, vd);
    }
}

// --- edge ---

TYPED_TEST(TestCases, edge_test_1) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
    EXPECT_EQ(this->edAB, p.first);
    EXPECT_TRUE(p.second);
}

TYPED_TEST(TestCases, edge_test_2) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdH, this->g);
    ASSERT_FALSE(p.second);
}

TYPED_TEST(TestCases, edge_test_3) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->vdB, this->vdD, this->g);
    EXPECT_EQ(this->edBD, p.first);
    EXPECT_TRUE(p.second);
}

TYPED_TEST(TestCases, edge_test_4) {
    this->cyclic2();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdH, this->g);
    EXPECT_FALSE(p.second);
}

// --- edges ---

TYPED_TEST(TestCases, edges_test_1) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::edge_iterator edge_iterator;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAB, ed);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAC, ed);
    }
}

TYPED_TEST(TestCases, edges_test_2) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::edge_iterator edge_iterator;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAB, ed);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAC, ed);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAE, ed);
    }
}

TYPED_TEST(TestCases, edges_test_3) {
    this->DefSetup();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::edge_iterator edge_iterator;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAB, ed);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAC, ed);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAE, ed);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edBD, ed);
    }
}

TYPED_TEST(TestCases, edges_test_4) {
    this->cyclic2();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::edge_iterator edge_iterator;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(e, b);
    if (b != e) {
        edge_descriptor ed = *b;
        EXPECT_EQ(this->edAB, ed);
    }
}

// --- num_edges ---

TYPED_TEST(TestCases, Num_Edges_1) {
    this->DefSetup();
    typedef typename TestFixture::edges_size_type edges_size_type;
    edges_size_type es = num_edges(this->g);
    EXPECT_EQ(11, es);
}

TYPED_TEST(TestCases, Num_Edges_2) {
    this->DefSetup();
    typedef typename TestFixture::graph_type graph_type;
    typedef typename TestFixture::edges_size_type edges_size_type;
    graph_type g2;
    edges_size_type es = num_edges(g2);
    EXPECT_EQ(0, es);
}

TYPED_TEST(TestCases, Num_Edges_3) {
    this->DefSetup();
    typedef typename TestFixture::graph_type graph_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::edges_size_type edges_size_type;
    graph_type g2;
    vertex_descriptor ed1 = add_vertex(g2);
    vertex_descriptor ed2 = add_vertex(g2);
    add_edge(ed1, ed2, g2);
    edges_size_type es = num_edges(g2);
    EXPECT_EQ(1, es);
}

TYPED_TEST(TestCases, Num_Edges_4) {
    this->cyclic2();
    typedef typename TestFixture::edges_size_type edges_size_type;
    edges_size_type es = num_edges(this->g);
    EXPECT_EQ(7, es);
}

// --- num vertices ---

TYPED_TEST(TestCases, Num_Vertices_1) {
    this->DefSetup();
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    vertices_size_type vs = num_vertices(this->g);
    EXPECT_EQ(8, vs);
}

TYPED_TEST(TestCases, Num_Vertices_2) {
    this->DefSetup();
    typedef typename TestFixture::graph_type graph_type;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    graph_type g2;
    vertices_size_type vs = num_vertices(g2);
    EXPECT_EQ(0, vs);
}

TYPED_TEST(TestCases, Num_Vertices_3) {
    this->DefSetup();
    typedef typename TestFixture::graph_type graph_type;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    graph_type g2;
    add_vertex(g2);
    vertices_size_type vs = num_vertices(g2);
    EXPECT_EQ(1, vs);
}

TYPED_TEST(TestCases, Num_Vertices_4) {
    this->cyclic2();
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    vertices_size_type vs = num_vertices(this->g);
    EXPECT_EQ(8, vs);
}

// --- source ---

TYPED_TEST(TestCases, Source_1) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edBD, this->g);
    EXPECT_EQ(this->vdB, vd);
}

TYPED_TEST(TestCases, Source_2) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edGH, this->g);
    EXPECT_EQ(this->vdG, vd);
}

TYPED_TEST(TestCases, Source_3) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edAB, this->g);
    EXPECT_EQ(this->vdA, vd);
}

TYPED_TEST(TestCases, Source_4) {
    this->cyclic2();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edAB, this->g);
    EXPECT_EQ(this->vdA, vd);
}

// --- target ---

TYPED_TEST(TestCases, Target_1) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edAB, this->g);
    EXPECT_EQ(this->vdB, vd);
}

TYPED_TEST(TestCases, Target_2) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edBD, this->g);
    EXPECT_EQ(this->vdD, vd);
}

TYPED_TEST(TestCases, Target_3) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edGH, this->g);
    EXPECT_EQ(this->vdH, vd);
}

TYPED_TEST(TestCases, Target_4) {
    this->cyclic2();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edAB, this->g);
    EXPECT_EQ(this->vdB, vd);
}

// --- vertex ---

TYPED_TEST(TestCases, Vertex_1) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(0, this->g);
    EXPECT_EQ(this->vdA, vd);
}

TYPED_TEST(TestCases, Vertex_2) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(1, this->g);
    EXPECT_EQ(this->vdB, vd);
}

TYPED_TEST(TestCases, Vertex_3) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(2, this->g);
    EXPECT_EQ(this->vdC, vd);
}

TYPED_TEST(TestCases, Vertex_4) {
    this->cyclic();
    ASSERT_EQ(vertex(99, this->g), 99);
}

// --- vertices ---

TYPED_TEST(TestCases, Vertices_1) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdA, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdB, vd);
    }
}

TYPED_TEST(TestCases, Vertices_2) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdA, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdB, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdC, vd);
    }
}

TYPED_TEST(TestCases, Vertices_3) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdA, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdB, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdC, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdD, vd);
    }
}

TYPED_TEST(TestCases, Vertices_4) {
    this->cyclic2();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdA, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdB, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdC, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdD, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdE, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdF, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdG, vd);
    }
    ++b;
    ASSERT_NE(e, b);
    if (b != e) {
        vertex_descriptor vd = *b;
        EXPECT_EQ(this->vdH, vd);
    }
}

// --- topological_sort ---

TYPED_TEST(TestCases, TopologicalSort_1) {
    this->DefSetup();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    try {
        topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_TRUE(false);
    }
    catch (boost::not_a_dag& e) {
        ASSERT_TRUE(has_cycle(this->g));
    }
}

TYPED_TEST(TestCases, TopologicalSort_2) {
    this->nc();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    try {
        topological_sort(this->ncg, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string("4 7 5 3 1 2 0 6 "), out.str());
    }
    catch (boost::not_a_dag& e) {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestCases, TopologicalSort_3) {
    this->DefSetup();
    typedef typename TestFixture::graph_type graph_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    graph_type g2;
    try {
        topological_sort(this->ncg, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string(""), out.str());
    }
    catch (boost::not_a_dag& e) {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestCases, TopologicalSort_4) {
    this->cyclic2();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ(std::string("5 3 2 1 7 6 0 4 "), out.str());
}
// Took some examples from Tylor's TestGraph.c++ file and Created my own to it
