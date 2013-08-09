// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
g++ -pedantic -std=c++0x -Wall Graph.h TestGraph.c++ -o TestGraph -lgtest -lpthread -lgtest_main && ./TestGraph
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

#include <exception>      // std::exception

#include <gtest/gtest.h>

#include "Graph.h"

using std::pair;


// ---------
// TestGraph
// ---------

template <class graph_type>
class TestGraph : public testing::Test {
public:
    TestGraph() : g(graph_type()) {}

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

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

    pair<edge_descriptor, bool> ep;
    pair<adjacency_iterator, adjacency_iterator> aip;
    pair<edge_iterator, edge_iterator> eip;
    pair<vertex_iterator, vertex_iterator> vip;

    adjacency_iterator ai_1;
    adjacency_iterator ai_2;
    edge_iterator ei_1;
    edge_iterator ei_2;
    vertex_iterator vi_1;
    vertex_iterator vi_2;

    edge_descriptor ed;
    vertex_descriptor vd;
    edges_size_type e_size;
    vertices_size_type v_size;

    virtual void SetUp() { 
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


using testing::Types;

typedef Types< boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>, Graph > MyTypes; //Graph
TYPED_TEST_CASE(TestGraph, MyTypes);

// directed, sparse, unweighted
// possibly connected
// possibly cyclic

TYPED_TEST(TestGraph, test_add_edge_bad_1){
    this->ep = add_edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(this->ep.first, this->edAB);
    ASSERT_FALSE(this->ep.second);
}

TYPED_TEST (TestGraph, test_add_edge_bad_2) {
    this->ep = add_edge(this->vdC, this->vdD, this->g);
    EXPECT_TRUE(this->ep.first  == this->edCD);
    EXPECT_FALSE(this->ep.second);
}

TYPED_TEST (TestGraph, test_add_edge_good_1) {
    this->ep = add_edge(this->vdA, this->vdD, this->g);
    ASSERT_TRUE(this->ep.second);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_1) {
    this->aip = adjacent_vertices(this->vdA, this->g);
    this->ai_1 = this->aip.first;
    this->ai_2 = this->aip.second;
    ASSERT_NE(this->ai_1, this->ai_2);
    if (this->ai_1 != this->ai_2) {
        this->vd = *(this->ai_1);
        ASSERT_EQ(this->vd, this->vdB);
    }
    ++(this->ai_1);
    if (this->ai_1 != this->ai_2) {
        this->vd = *(this->ai_1);
        ASSERT_EQ(this->vd, this->vdC);
    }
}

TYPED_TEST(TestGraph, test_adjacent_vertices_2) {
    this->aip = adjacent_vertices(this->vdB, this->g);
    this->ai_1 = this->aip.first;
    this->ai_2 = this->aip.second;
    ASSERT_NE(this->ai_1, this->ai_2);
    if (this->ai_1 != this->ai_2) {
        this->vd = *(this->ai_1);
        ASSERT_EQ(this->vd, this->vdD);
    }
    ++(this->ai_1);
    if (this->ai_1 != this->ai_2) {
        this->vd = *(this->ai_1);
        ASSERT_EQ(this->vd, this->vdE);
    }
}

TYPED_TEST(TestGraph, test_adjacent_vertices_3) {
    this->aip = adjacent_vertices(this->vdC, this->g);
    this->ai_1 = this->aip.first;
    this->ai_2 = this->aip.second;
    ASSERT_NE(this->ai_1, this->ai_2);
    if (this->ai_1 != this->ai_2) {
        this->vd = *(this->ai_1);
        ASSERT_EQ(this->vd, this->vdD);
    }
    ++(this->ai_1);
    ASSERT_EQ(this->ai_1, this->ai_2);
}

TYPED_TEST(TestGraph, test_edge_1) {
    this->ep = edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(this->ep.first, this->edAB);
    ASSERT_TRUE(this->ep.second);
}

TYPED_TEST(TestGraph, test_edge_2) {
    this->ep = edge(this->vdA, this->vdC, this->g);
    ASSERT_EQ(this->ep.first, this->edAC);
    ASSERT_TRUE(this->ep.second);
}

TYPED_TEST(TestGraph, test_edge_3) {
    this->ep = edge(this->vdA, this->vdE, this->g);
    ASSERT_EQ(this->ep.first, this->edAE);
    ASSERT_TRUE(this->ep.second);
}

TYPED_TEST(TestGraph, test_edge_bad_1) {
    this->ep = edge(this->vdA, this->vdD, this->g);
    ASSERT_FALSE(this->ep.second);
}

TYPED_TEST(TestGraph, test_edge_bad_2) {
    this->ep = edge(this->vdA, this->vdA, this->g);
    ASSERT_FALSE(this->ep.second);
}

TYPED_TEST(TestGraph, test_edges_1) {
    this->eip = edges(this->g);
    this->ei_1 = this->eip.first;
    this->ei_2 = this->eip.second;
    ASSERT_NE(this->ei_1, this->ei_2);
    if (this->ei_1 != this->ei_2) {
        this->ed = *(this->ei_1);
        ASSERT_EQ(this->ed, this->edAB);
    }
    ++(this->ei_1);
    if (this->ei_1 != this->ei_2) {
        this->ed = *(this->ei_1);
        ASSERT_EQ(this->ed, this->edAC);
    }
}

TYPED_TEST(TestGraph, test_num_edges_1) {
    this->e_size = num_edges(this->g);
    ASSERT_EQ(this->e_size, 11);
}

TYPED_TEST(TestGraph, test_num_edges_2) {
    add_edge(this->vdA, this->vdD, this->g);
    this->e_size = num_edges(this->g);
    ASSERT_EQ(this->e_size, 12);
}

TYPED_TEST(TestGraph, test_num_edges_3) {
    add_edge(this->vdA, this->vdD, this->g);
    add_edge(this->vdA, this->vdD, this->g);
    this->e_size = num_edges(this->g);
    ASSERT_EQ(this->e_size, 12);
}

TYPED_TEST(TestGraph, test_num_vertices_1) {
    this->v_size = num_vertices(this->g);
    ASSERT_EQ(this->v_size, 8);
}

TYPED_TEST(TestGraph, test_num_vertices_2) {
    add_vertex(this->g);
    this->v_size = num_vertices(this->g);
    ASSERT_EQ(this->v_size, 9);
}

TYPED_TEST(TestGraph, test_num_vertices_3) {
    add_vertex(this->g);
    add_vertex(this->g);
    this->v_size = num_vertices(this->g);
    ASSERT_EQ(this->v_size, 10);
}

TYPED_TEST(TestGraph, test_source_1) {
    this->vd = source(this->edAB, this->g);
    ASSERT_EQ(this->vd, this->vdA);
}

TYPED_TEST(TestGraph, test_source_2) {
    this->vd = source(this->edAC, this->g);
    ASSERT_EQ(this->vd, this->vdA);
}

TYPED_TEST(TestGraph, test_target_1) {
    this->vd = target(this->edAB, this->g);
    ASSERT_EQ(this->vd, this->vdB);
}

TYPED_TEST(TestGraph, test_target_2) {
    this->vd = target(this->edAC, this->g);
    ASSERT_EQ(this->vd, this->vdC);
}

TYPED_TEST(TestGraph, test_vertex_1) {
    this->vd = vertex(0, this->g);
    ASSERT_EQ(this->vd, this->vdA);
}

TYPED_TEST(TestGraph, test_vertex_2) {
    this->vd = vertex(1, this->g);
    ASSERT_EQ(this->vd, this->vdB);
}

TYPED_TEST(TestGraph, test_vertices_1) {
    this->vip = vertices(this->g);
    this->vi_1 = this->vip.first;
    this->vi_2 = this->vip.second;
    ASSERT_NE(this->vi_1, this->vi_2);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdA);
    }
    ++(this->vi_1);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdB);
    }
}

TYPED_TEST(TestGraph, test_vertices_2) {
    this->vip = vertices(this->g);
    this->vi_1 = this->vip.first;
    this->vi_2 = this->vip.second;
    ASSERT_NE(this->vi_1, this->vi_2);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdA);
    }
    ++(this->vi_1);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdB);
    }
    ++(this->vi_1);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdC);
    }
    ++(this->vi_1);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdD);
    }
}

TYPED_TEST(TestGraph, test_vertices_3) {
    this->vip = vertices(this->g);
    this->vi_1 = this->vip.first;
    this->vi_2 = this->vip.second;
    ASSERT_NE(this->vi_1, this->vi_2);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdA);
    }
    for (int i = 0; i < 4; ++i) {
        ++(this->vi_1);
    }
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdE);
    }
    ++(this->vi_1);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdF);
    }
    ++(this->vi_1);
    if (this->vi_1 != this->vi_2) {
        this->vd = *(this->vi_1);
        ASSERT_EQ(this->vd, this->vdG);
    }
}


class GraphOnlyTests1 : public testing::Test {
public:
    GraphOnlyTests1() : g(Graph()) {}

    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor    edge_descriptor;

    typedef typename Graph::vertex_iterator    vertex_iterator;
    typedef typename Graph::edge_iterator      edge_iterator;
    typedef typename Graph::adjacency_iterator adjacency_iterator;

    typedef typename Graph::vertices_size_type vertices_size_type;
    typedef typename Graph::edges_size_type    edges_size_type;

    Graph g;
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

    //Pairs
    pair<edge_descriptor, bool> ep;
    pair<adjacency_iterator, adjacency_iterator> aip;
    pair<edge_iterator, edge_iterator> eip;
    pair<vertex_iterator, vertex_iterator> vip;

    //Iterators
    adjacency_iterator ai_1;
    adjacency_iterator ai_2;
    edge_iterator ei_1;
    edge_iterator ei_2;
    vertex_iterator vi_1;
    vertex_iterator vi_2;

    //Descriptors
    edge_descriptor ed;
    vertex_descriptor vd;
    edges_size_type e_size;
    vertices_size_type v_size;

    virtual void SetUp() { 
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

TEST_F(GraphOnlyTests1, test_has_cycle_1) {
    ASSERT_TRUE(has_cycle(this->g));
}

class GraphOnlyTests2 : public testing::Test {
public:
    GraphOnlyTests2() : g(Graph()) {}

    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor    edge_descriptor;

    typedef typename Graph::vertex_iterator    vertex_iterator;
    typedef typename Graph::edge_iterator      edge_iterator;
    typedef typename Graph::adjacency_iterator adjacency_iterator;

    typedef typename Graph::vertices_size_type vertices_size_type;
    typedef typename Graph::edges_size_type    edges_size_type;

    Graph g;
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

    pair<edge_descriptor, bool> ep;
    pair<adjacency_iterator, adjacency_iterator> aip;
    pair<edge_iterator, edge_iterator> eip;
    pair<vertex_iterator, vertex_iterator> vip;

    adjacency_iterator ai_1;
    adjacency_iterator ai_2;
    edge_iterator ei_1;
    edge_iterator ei_2;
    vertex_iterator vi_1;
    vertex_iterator vi_2;

    edge_descriptor ed;
    vertex_descriptor vd;
    edges_size_type e_size;
    vertices_size_type v_size;

    virtual void SetUp() { 
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        edAB = add_edge(vdA, vdB, g).first;
        edAC = add_edge(vdA, vdC, g).first;
    }
};

TEST_F(GraphOnlyTests2, test_has_cycle_2) {
    ASSERT_FALSE(has_cycle(this->g));
}

TEST_F(GraphOnlyTests2, test_topological_sort_1) {
    std::ostringstream out;
    topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
    EXPECT_EQ("0 2 1 ", out.str());
}

TEST_F(GraphOnlyTests2, test_topological_sort_2) {
    this->vdD = add_vertex(this->g);
    add_edge(this->vdC, this->vdD, this->g);
    std::ostringstream out;
    topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
    EXPECT_EQ("0 2 3 1 ", out.str());
}

class GraphOnlyTests3 : public testing::Test {
public:
    GraphOnlyTests3() : g(Graph()) {}

    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor    edge_descriptor;

    typedef typename Graph::vertex_iterator    vertex_iterator;
    typedef typename Graph::edge_iterator      edge_iterator;
    typedef typename Graph::adjacency_iterator adjacency_iterator;

    typedef typename Graph::vertices_size_type vertices_size_type;
    typedef typename Graph::edges_size_type    edges_size_type;

    Graph g;
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

    pair<edge_descriptor, bool> ep;
    pair<adjacency_iterator, adjacency_iterator> aip;
    pair<edge_iterator, edge_iterator> eip;
    pair<vertex_iterator, vertex_iterator> vip;

    adjacency_iterator ai_1;
    adjacency_iterator ai_2;
    edge_iterator ei_1;
    edge_iterator ei_2;
    vertex_iterator vi_1;
    vertex_iterator vi_2;

    edge_descriptor ed;
    vertex_descriptor vd;
    edges_size_type e_size;
    vertices_size_type v_size;

    virtual void SetUp() { 
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        edAB = add_edge(vdC, vdB, g).first;
        edAC = add_edge(vdB, vdA, g).first;
        edAC = add_edge(vdA, vdC, g).first;
    }
};

TEST_F(GraphOnlyTests3, test_has_cycle_3) {
    ASSERT_TRUE(has_cycle(this->g));
}

TEST_F(GraphOnlyTests3, test_topological_sort_3) {
    std::ostringstream out;
    try {
        topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
    } catch (boost::not_a_dag& e) {
        ASSERT_TRUE(std::string(e.what()) == "The graph must be a DAG.");
    }
}

TEST_F(GraphOnlyTests3, test_topological_sort_4) {
    this->vdD = add_vertex(this->g);
    add_edge(this->vdC, this->vdD, this->g);
    std::ostringstream out;
    try {
        topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
    } catch (boost::not_a_dag& e) {
        ASSERT_TRUE(std::string(e.what()) == "The graph must be a DAG.");
    }    
}