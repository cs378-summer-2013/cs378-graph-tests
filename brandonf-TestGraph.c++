// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
To test the program:
    NOTE: gtest.h dependency.
    g++ -pedantic -std=c++0x -Wall Graph.h TestGraph.c++ -o TestGraph -lgtest -lpthread -lgtest_main
    ./TestGraph
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

// ---------
// TestGraph
// ---------

template <class T>
class TestGraph : public testing::Test {
public:
    TestGraph() : g(T()) {}

    typedef typename T::vertex_descriptor  vertex_descriptor;
    typedef typename T::edge_descriptor    edge_descriptor;

    typedef typename T::vertex_iterator    vertex_iterator;
    typedef typename T::edge_iterator      edge_iterator;
    typedef typename T::adjacency_iterator adjacency_iterator;

    typedef typename T::vertices_size_type vertices_size_type;
    typedef typename T::edges_size_type    edges_size_type;

    T g;
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
    std::pair<edge_descriptor, bool> an_edge_pair;
    std::pair<adjacency_iterator, adjacency_iterator> adjacency_iterator_pair;
    std::pair<edge_iterator, edge_iterator> edge_iterator_pair;
    std::pair<vertex_iterator, vertex_iterator> vertex_iterator_pair;

    //Iterators
    adjacency_iterator adj_itr_b;
    adjacency_iterator adj_itr_e;
    edge_iterator edge_itr_b;
    edge_iterator edge_itr_e;
    vertex_iterator vertex_itr_b;
    vertex_iterator vertex_itr_e;

    //Descriptors
    edge_descriptor an_edge_descriptor;
    vertex_descriptor vertex_descrip;
    edges_size_type edge_st;
    vertices_size_type vertices_st;

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
using namespace std;
typedef Types< boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>, Graph > Implementations; //Graph
TYPED_TEST_CASE(TestGraph, Implementations);

// -----
// tests
// -----

// directed, sparse, unweighted
// possibly connected
// possibly cyclic

TYPED_TEST(TestGraph, test_add_edge_bad_1){
    this->an_edge_pair = add_edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(this->an_edge_pair.first, this->edAB);
    ASSERT_FALSE(this->an_edge_pair.second);
}

TYPED_TEST (TestGraph, test_add_edge_bad_2) {
        this->an_edge_pair = add_edge(this->vdC, this->vdD, this->g);
        EXPECT_TRUE(this->an_edge_pair.first  == this->edCD);
        EXPECT_FALSE(this->an_edge_pair.second);
}

TYPED_TEST (TestGraph, test_add_edge_good_1) {
    this->an_edge_pair = add_edge(this->vdA, this->vdD, this->g);
    ASSERT_TRUE(this->an_edge_pair.second);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_1) {
        this->adjacency_iterator_pair = adjacent_vertices(this->vdA, this->g);
        this->adj_itr_b = this->adjacency_iterator_pair.first;
        this->adj_itr_e = this->adjacency_iterator_pair.second;
        ASSERT_NE(this->adj_itr_b, this->adj_itr_e);
        if (this->adj_itr_b != this->adj_itr_e) {
            this->vertex_descrip = *(this->adj_itr_b);
            ASSERT_EQ(this->vertex_descrip, this->vdB);}
        ++(this->adj_itr_b);
        if (this->adj_itr_b != this->adj_itr_e) {
            this->vertex_descrip = *(this->adj_itr_b);
            ASSERT_EQ(this->vertex_descrip, this->vdC);}
}

TYPED_TEST(TestGraph, test_adjacent_vertices_2) {
        this->adjacency_iterator_pair = adjacent_vertices(this->vdB, this->g);
        this->adj_itr_b = this->adjacency_iterator_pair.first;
        this->adj_itr_e = this->adjacency_iterator_pair.second;
        ASSERT_NE(this->adj_itr_b, this->adj_itr_e);
        if (this->adj_itr_b != this->adj_itr_e) {
            this->vertex_descrip = *(this->adj_itr_b);
            ASSERT_EQ(this->vertex_descrip, this->vdD);}
        ++(this->adj_itr_b);
        if (this->adj_itr_b != this->adj_itr_e) {
            this->vertex_descrip = *(this->adj_itr_b);
            ASSERT_EQ(this->vertex_descrip, this->vdE);}
}

TYPED_TEST(TestGraph, test_adjacent_vertices_3) {
        this->adjacency_iterator_pair = adjacent_vertices(this->vdC, this->g);
        this->adj_itr_b = this->adjacency_iterator_pair.first;
        this->adj_itr_e = this->adjacency_iterator_pair.second;
        ASSERT_NE(this->adj_itr_b, this->adj_itr_e);
        if (this->adj_itr_b != this->adj_itr_e) {
            this->vertex_descrip = *(this->adj_itr_b);
            ASSERT_EQ(this->vertex_descrip, this->vdD);}
        ++(this->adj_itr_b);
        ASSERT_EQ(this->adj_itr_b, this->adj_itr_e);
}

TYPED_TEST(TestGraph, test_edge_1) {
        this->an_edge_pair = edge(this->vdA, this->vdB, this->g);
        ASSERT_EQ(this->an_edge_pair.first, this->edAB);
        ASSERT_TRUE(this->an_edge_pair.second);
}

TYPED_TEST(TestGraph, test_edge_2) {
        this->an_edge_pair = edge(this->vdA, this->vdC, this->g);
        ASSERT_EQ(this->an_edge_pair.first, this->edAC);
        ASSERT_TRUE(this->an_edge_pair.second);
}

TYPED_TEST(TestGraph, test_edge_3) {
        this->an_edge_pair = edge(this->vdA, this->vdE, this->g);
        ASSERT_EQ(this->an_edge_pair.first, this->edAE);
        ASSERT_TRUE(this->an_edge_pair.second);
}

TYPED_TEST(TestGraph, test_edge_bad_1) {
        this->an_edge_pair = edge(this->vdA, this->vdD, this->g);
        ASSERT_FALSE(this->an_edge_pair.second);
}

TYPED_TEST(TestGraph, test_edge_bad_2) {
        this->an_edge_pair = edge(this->vdA, this->vdA, this->g);
        ASSERT_FALSE(this->an_edge_pair.second);
}

TYPED_TEST(TestGraph, test_edges_1) {
        this->edge_iterator_pair = edges(this->g);
        this->edge_itr_b = this->edge_iterator_pair.first;
        this->edge_itr_e = this->edge_iterator_pair.second;
        ASSERT_NE(this->edge_itr_b, this->edge_itr_e);
        if (this->edge_itr_b != this->edge_itr_e) {
            this->an_edge_descriptor = *(this->edge_itr_b);
            ASSERT_EQ(this->an_edge_descriptor, this->edAB);
        }
        ++(this->edge_itr_b);
        if (this->edge_itr_b != this->edge_itr_e) {
            this->an_edge_descriptor = *(this->edge_itr_b);
            ASSERT_EQ(this->an_edge_descriptor, this->edAC);
        }
}

TYPED_TEST(TestGraph, test_num_edges_1) {
    this->edge_st = num_edges(this->g);
    ASSERT_EQ(this->edge_st, 11);
}

TYPED_TEST(TestGraph, test_num_edges_2) {
    add_edge(this->vdA, this->vdD, this->g);
    this->edge_st = num_edges(this->g);
    ASSERT_EQ(this->edge_st, 12);
}

TYPED_TEST(TestGraph, test_num_edges_3) {
    add_edge(this->vdA, this->vdD, this->g);
    add_edge(this->vdA, this->vdD, this->g);
    this->edge_st = num_edges(this->g);
    ASSERT_EQ(this->edge_st, 12);
}

TYPED_TEST(TestGraph, test_num_vertices_1) {
    this->vertices_st = num_vertices(this->g);
    ASSERT_EQ(this->vertices_st, 8);
}

TYPED_TEST(TestGraph, test_num_vertices_2) {
    add_vertex(this->g);
    this->vertices_st = num_vertices(this->g);
    ASSERT_EQ(this->vertices_st, 9);
}

TYPED_TEST(TestGraph, test_num_vertices_3) {
    add_vertex(this->g);
    add_vertex(this->g);
    this->vertices_st = num_vertices(this->g);
    ASSERT_EQ(this->vertices_st, 10);
}

TYPED_TEST(TestGraph, test_source_1) {
    this->vertex_descrip = source(this->edAB, this->g);
    ASSERT_EQ(this->vertex_descrip, this->vdA);
}

TYPED_TEST(TestGraph, test_source_2) {
    this->vertex_descrip = source(this->edAC, this->g);
    ASSERT_EQ(this->vertex_descrip, this->vdA);
}

TYPED_TEST(TestGraph, test_target_1) {
    this->vertex_descrip = target(this->edAB, this->g);
    ASSERT_EQ(this->vertex_descrip, this->vdB);
}

TYPED_TEST(TestGraph, test_target_2) {
    this->vertex_descrip = target(this->edAC, this->g);
    ASSERT_EQ(this->vertex_descrip, this->vdC);
}

TYPED_TEST(TestGraph, test_vertex_1) {
    this->vertex_descrip = vertex(0, this->g);
    ASSERT_EQ(this->vertex_descrip, this->vdA);
}

TYPED_TEST(TestGraph, test_vertex_2) {
    this->vertex_descrip = vertex(1, this->g);
    ASSERT_EQ(this->vertex_descrip, this->vdB);
}

TYPED_TEST(TestGraph, test_vertices_1) {
    this->vertex_iterator_pair = vertices(this->g);
    this->vertex_itr_b = this->vertex_iterator_pair.first;
    this->vertex_itr_e = this->vertex_iterator_pair.second;
    ASSERT_NE(this->vertex_itr_b, this->vertex_itr_e);
    if (this->vertex_itr_b != this->vertex_itr_e) {
        this->vertex_descrip = *(this->vertex_itr_b);
        ASSERT_EQ(this->vertex_descrip, this->vdA);
    }
    ++(this->vertex_itr_b);
    if (this->vertex_itr_b != this->vertex_itr_e) {
        this->vertex_descrip = *(this->vertex_itr_b);
        ASSERT_EQ(this->vertex_descrip, this->vdB);
    }
}

TYPED_TEST(TestGraph, test_vertices_2) {
    this->vertex_iterator_pair = vertices(this->g);
    this->vertex_itr_b = this->vertex_iterator_pair.first;
    this->vertex_itr_e = this->vertex_iterator_pair.second;
    ASSERT_NE(this->vertex_itr_b, this->vertex_itr_e);
    if (this->vertex_itr_b != this->vertex_itr_e) {
        this->vertex_descrip = *(this->vertex_itr_b);
        ASSERT_EQ(this->vertex_descrip, this->vdA);
    }
    ++(this->vertex_itr_b);
    if (this->vertex_itr_b != this->vertex_itr_e) {
        this->vertex_descrip = *(this->vertex_itr_b);
        ASSERT_EQ(this->vertex_descrip, this->vdB);
    }
    ++(this->vertex_itr_b);
    if (this->vertex_itr_b != this->vertex_itr_e) {
        this->vertex_descrip = *(this->vertex_itr_b);
        ASSERT_EQ(this->vertex_descrip, this->vdC);
    }
    ++(this->vertex_itr_b);
    if (this->vertex_itr_b != this->vertex_itr_e) {
        this->vertex_descrip = *(this->vertex_itr_b);
        ASSERT_EQ(this->vertex_descrip, this->vdD);
    }
}


class TestOurGraphOnly : public testing::Test {
public:
    TestOurGraphOnly() : g(Graph()) {}

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
    std::pair<edge_descriptor, bool> an_edge_pair;
    std::pair<adjacency_iterator, adjacency_iterator> adjacency_iterator_pair;
    std::pair<edge_iterator, edge_iterator> edge_iterator_pair;
    std::pair<vertex_iterator, vertex_iterator> vertex_iterator_pair;

    //Iterators
    adjacency_iterator adj_itr_b;
    adjacency_iterator adj_itr_e;
    edge_iterator edge_itr_b;
    edge_iterator edge_itr_e;
    vertex_iterator vertex_itr_b;
    vertex_iterator vertex_itr_e;

    //Descriptors
    edge_descriptor an_edge_descriptor;
    vertex_descriptor vertex_descrip;
    edges_size_type edge_st;
    vertices_size_type vertices_st;

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

TEST_F(TestOurGraphOnly, test_has_cycle) {
    ASSERT_TRUE(has_cycle(this->g));
}

class TestOurGraphOnlyNoCycle : public testing::Test {
public:
    TestOurGraphOnlyNoCycle() : g(Graph()) {}

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

    edge_descriptor edAB;
    edge_descriptor edAC;
    edge_descriptor edCD;

    //Pairs
    std::pair<edge_descriptor, bool> an_edge_pair;
    std::pair<adjacency_iterator, adjacency_iterator> adjacency_iterator_pair;
    std::pair<edge_iterator, edge_iterator> edge_iterator_pair;
    std::pair<vertex_iterator, vertex_iterator> vertex_iterator_pair;

    virtual void SetUp() { 
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        edAB = add_edge(vdA, vdB, g).first;
        edAC = add_edge(vdA, vdC, g).first;
    }
};

TEST_F(TestOurGraphOnlyNoCycle, test_has_cycle_no) {
    ASSERT_FALSE(has_cycle(this->g));
}

TEST_F(TestOurGraphOnlyNoCycle, test_topological_sort_1) {
        std::ostringstream out;
        topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
        EXPECT_EQ("0 2 1 ", out.str());
}

TEST_F(TestOurGraphOnlyNoCycle, test_topological_sort_2) {
        this->vdD = add_vertex(this->g);
        add_edge(this->vdC, this->vdD, this->g);
        std::ostringstream out;
        topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
        EXPECT_EQ("0 2 3 1 ", out.str());
}