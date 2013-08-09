// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
To test the program:
    % ls /usr/include/gtest/
    ...
    gtest.h
    ...
    % locate libgtest.a
    /usr/lib/libgtest.a
    % ls /public/linux/include/boost-1_44/boost/graph/
    ...
    adjacency_list.hpp
    ...
    % g++ -ansi -pedantic -I/public/linux/include/boost-1_44 -Wall TestGraph.c++ -o TestGraph.app -lgtest -lpthread -lgtest_main
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
#include "boost/graph/exception.hpp"       // not_a_dag

#include "gtest/gtest.h"

// -------
// defines
// -------

#define class struct
#define protected public
#define private public

#include "Graph.h"

// ---------
// TestGraph
// ---------

template <typename T>
class TestGraph : public ::testing::Test {
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

        // -----
        // tests
        // -----

        // directed, sparse, unweighted
        // possibly connected
        // possibly cyclic
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
        // setUp
        // -----

        void setUp () {
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

// -------------
// test_add_edge
// -------------

TEST(TestGraph, test_add_edge_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
    
    std::pair<Graph::edge_descriptor, bool> p = add_edge(vdA, vdB, g);
    ASSERT_EQ(p.first, edAB);
    ASSERT_TRUE(p.second);
    
    std::pair<Graph::edge_descriptor, bool> q = add_edge(vdA, vdB, g);
    ASSERT_EQ(q.first, edAB);
    ASSERT_FALSE(q.second);
}

TEST(TestGraph, test_add_edge_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
    
    ASSERT_EQ(g.edge_list.size(), 0);
    
    for (int i = 1; i < 100; ++i) {
        Graph::edge_descriptor ed = std::make_pair(g.vertex_list[0], g.vertex_list[i]);
        std::pair<Graph::edge_descriptor, bool> p = add_edge(g.vertex_list[0], g.vertex_list[i], g);
        ASSERT_EQ(p.first, ed);
        ASSERT_TRUE(p.second);
    }
    
    ASSERT_EQ(g.edge_list.size(), 99);
}

TEST(TestGraph, test_add_edge_3) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
    
    ASSERT_EQ(g.adjacency_list[0].size(), 0);
    
    for (int i = 1; i < 34; ++i) {
        Graph::edge_descriptor ed = std::make_pair(g.vertex_list[0], g.vertex_list[i]);
        std::pair<Graph::edge_descriptor, bool> p = add_edge(g.vertex_list[0], g.vertex_list[i], g);
        ASSERT_EQ(p.first, ed);
        ASSERT_TRUE(p.second);
    }
    
    for (int i = 1; i < 100; ++i) {
        Graph::edge_descriptor ed = std::make_pair(g.vertex_list[0], g.vertex_list[i]);
        std::pair<Graph::edge_descriptor, bool> p = add_edge(g.vertex_list[0], g.vertex_list[i], g);
        ASSERT_EQ(p.first, ed);
        if (i > 0 && i < 34) {
            ASSERT_FALSE(p.second);
        }
        else {
            ASSERT_TRUE(p.second);
        }
    }
    
    ASSERT_EQ(g.adjacency_list[0].size(), 99);
}

// ----------------
// test_remove_edge
// ----------------

TEST(TestGraph, test_remove_edge_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    
    add_edge(vdA, vdB, g);
    ASSERT_EQ(g.edge_list.size(), 1);
    
    remove_edge(vdA, vdB, g);
    ASSERT_EQ(g.edge_list.size(), 0);
}

TEST(TestGraph, test_remove_edge_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
    
    ASSERT_EQ(g.edge_list.size(), 0);
    
    for (int i = 1; i < 100; ++i) {
        add_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    ASSERT_EQ(g.edge_list.size(), 99);
    
    for (int i = 1; i < 100; ++i) {
        remove_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    ASSERT_EQ(g.edge_list.size(), 0);
}

TEST(TestGraph, test_remove_edge_3) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
    
    ASSERT_EQ(g.adjacency_list[0].size(), 0);
    
    for (int i = 1; i < 100; ++i) {
        add_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    ASSERT_EQ(g.adjacency_list[0].size(), 99);
    
    for (int i = 1; i < 34; ++i) {
        remove_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    ASSERT_EQ(g.adjacency_list[0].size(), 66);
}

// ---------------
// test_add_vertex
// ---------------

TEST(TestGraph, test_add_vertex_1) {
    Graph g;
    
    add_vertex(g);
    
    ASSERT_EQ(g.vertex_list.size(), 1);
}

TEST(TestGraph, test_add_vertex_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
    
    ASSERT_EQ(g.vertex_list.size(), 100);
}

TEST(TestGraph, test_add_vertex_3) {
    Graph g;
    
    for (int i = 0; i < 33; ++i) {
        add_vertex(g);
    }
    
    ASSERT_EQ(g.vertex_list.size(), 33);
    
    for (int i = 0; i < 33; ++i) {
        add_vertex(g);
    }
    
    ASSERT_EQ(g.vertex_list.size(), 66);
    
    for (int i = 0; i < 33; ++i) {
        add_vertex(g);
    }
    
    ASSERT_EQ(g.vertex_list.size(), 99);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TEST(TestGraph, test_adjacent_vertices_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);

    std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> p = adjacent_vertices(vdA, g);
    Graph::adjacency_iterator b = p.first;
    Graph::adjacency_iterator e = p.second;
    ASSERT_EQ(b, e);
}

TEST(TestGraph, test_adjacent_vertices_2) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);
    Graph::vertex_descriptor vdG = add_vertex(g);
    Graph::vertex_descriptor vdH = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdE, g);
    add_edge(vdB, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdD, g);
    add_edge(vdD, vdE, g);
    add_edge(vdD, vdF, g);
    add_edge(vdF, vdD, g);
    add_edge(vdF, vdH, g);
    add_edge(vdG, vdH, g);

    std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> p = adjacent_vertices(vdA, g);
    Graph::adjacency_iterator b = p.first;
    Graph::adjacency_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdB);
    }
    ++b;
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdC);
    }
}

TEST(TestGraph, test_adjacent_vertices_3) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdE, g);
    add_edge(vdC, vdF, g);
    add_edge(vdE, vdD, g);

    std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> p = adjacent_vertices(vdA, g);
    Graph::adjacency_iterator b = p.first;
    Graph::adjacency_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdB);
    }
    ++b;
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdD);
    }
}

// ---------
// test_edge
// ---------

TEST(TestGraph, test_edge_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    
    Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
    add_edge(vdA, vdB, g);
    
    std::pair<Graph::edge_descriptor, bool> p = edge(vdA, vdB, g);
    ASSERT_EQ(p.first, edAB);
    ASSERT_TRUE(p.second);
}

TEST(TestGraph, test_edge_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        Graph::vertex_descriptor vdA = add_vertex(g);
        Graph::vertex_descriptor vdB = add_vertex(g);

        Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
        add_edge(vdA, vdB, g);

        std::pair<Graph::edge_descriptor, bool> p = edge(vdA, vdB, g);
        ASSERT_EQ(p.first, edAB);
        ASSERT_TRUE(p.second);
    }
}

TEST(TestGraph, test_edge_3) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        Graph::vertex_descriptor vdA = add_vertex(g);
        Graph::vertex_descriptor vdB = add_vertex(g);

        Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
        add_edge(vdA, vdB, g);

        std::pair<Graph::edge_descriptor, bool> p = edge(vdA, vdB, g);
        ASSERT_EQ(p.first, edAB);
        ASSERT_TRUE(p.second);
    }
    
    for (int i = 0; i < 100; ++i) {
        Graph::vertex_descriptor vdA = g.vertex_list[i];
        Graph::vertex_descriptor vdB = g.vertex_list[i + 1];

        Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
        remove_edge(vdA, vdB, g);

        std::pair<Graph::edge_descriptor, bool> p = edge(vdA, vdB, g);
        ASSERT_EQ(p.first, edAB);
        ASSERT_FALSE(p.second);
    }
}

// ----------
// test_edges
// ----------

TEST(TestGraph, test_edges_1) {
    Graph g;

    std::pair<Graph::edge_iterator, Graph::edge_iterator> p = edges(g);
    Graph::edge_iterator b = p.first;
    Graph::edge_iterator e = p.second;
    ASSERT_EQ(b, e);
}

TEST(TestGraph, test_edges_2) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);
    Graph::vertex_descriptor vdG = add_vertex(g);
    Graph::vertex_descriptor vdH = add_vertex(g);

    Graph::edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    Graph::edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    add_edge(vdA, vdE, g);
    add_edge(vdB, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdD, g);
    add_edge(vdD, vdE, g);
    add_edge(vdD, vdF, g);
    add_edge(vdF, vdD, g);
    add_edge(vdF, vdH, g);
    add_edge(vdG, vdH, g);
    
    std::pair<Graph::edge_iterator, Graph::edge_iterator> p = edges(g);
    Graph::edge_iterator b = p.first;
    Graph::edge_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        Graph::edge_descriptor ed = *b;
        ASSERT_EQ(ed, edAB);
    }
    ++b;
    if (b != e) {
        Graph::edge_descriptor ed = *b;
        ASSERT_EQ(ed, edAC);
    }
}

TEST(TestGraph, test_edges_3) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);

    Graph::edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    Graph::edge_descriptor edAD = add_edge(vdA, vdD, g).first;
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdE, g);
    add_edge(vdC, vdF, g);
    add_edge(vdE, vdD, g);
    
    std::pair<Graph::edge_iterator, Graph::edge_iterator> p = edges(g);
    Graph::edge_iterator b = p.first;
    Graph::edge_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        Graph::edge_descriptor ed = *b;
        ASSERT_EQ(ed, edAB);
    }
    ++b;
    if (b != e) {
        Graph::edge_descriptor ed = *b;
        ASSERT_EQ(ed, edAD);
    }
}

// --------------
// test_num_edges
// --------------

TEST(TestGraph, test_num_edges_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    
    add_edge(vdA, vdB, g);
    Graph::edges_size_type es = num_edges(g);
    ASSERT_EQ(es, 1);
}

TEST(TestGraph, test_num_edges_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
    
    Graph::edges_size_type es = num_edges(g);
    ASSERT_EQ(es, 0);
    
    for (int i = 1; i < 100; ++i) {
        add_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    es = num_edges(g);
    ASSERT_EQ(es, 99);
}

TEST(TestGraph, test_num_edges_3) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
    
    Graph::edges_size_type es = num_edges(g);
    ASSERT_EQ(es, 0);
    
    for (int i = 1; i < 100; ++i) {
        add_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    es = num_edges(g);
    ASSERT_EQ(es, 99);
    
    for (int i = 1; i < 34; ++i) {
        remove_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    es = num_edges(g);
    ASSERT_EQ(es, 66);
}

// -----------------
// test_num_vertices
// -----------------

TEST(TestGraph, test_num_vertices_1) {
    Graph g;
    
    add_vertex(g);
    add_vertex(g);
    
    Graph::vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(vs, 2);
}

TEST(TestGraph, test_num_vertices_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
    
    Graph::vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(vs, 100);
}

TEST(TestGraph, test_num_vertices_3) {
    Graph g;
    
    for (int i = 0; i < 33; ++i) {
        add_vertex(g);
    }
    
    Graph::vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(vs, 33);
    
    for (int i = 0; i < 33; ++i) {
        add_vertex(g);
    }
    
    vs = num_vertices(g);
    ASSERT_EQ(vs, 66);
    
    for (int i = 0; i < 33; ++i) {
        add_vertex(g);
    }
    
    vs = num_vertices(g);
    ASSERT_EQ(vs, 99);
}

// -----------
// test_source
// -----------

TEST(TestGraph, test_source_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
    add_edge(vdA, vdB, g);
    
    Graph::vertex_descriptor vd = source(edAB, g);
    ASSERT_EQ(vd, vdA);
}

TEST(TestGraph, test_source_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        Graph::vertex_descriptor vdA = add_vertex(g);
        Graph::vertex_descriptor vdB = add_vertex(g);
        Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
        add_edge(vdA, vdB, g);
        
        Graph::vertex_descriptor vd = source(edAB, g);
        ASSERT_EQ(vd, vdA);
    }
}

TEST(TestGraph, test_source_3) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
        
    for (int i = 1; i < 100; ++i) {
        add_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    for (int i = 1; i < 100; ++i) {
        Graph::edge_descriptor ed = std::make_pair(g.vertex_list[0], g.vertex_list[i]);
        Graph::vertex_descriptor vd = source(ed, g);
        ASSERT_EQ(vd, g.vertex_list[0]);
    }
}

// -----------
// test_target
// -----------

TEST(TestGraph, test_target_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
    add_edge(vdA, vdB, g);
    
    Graph::vertex_descriptor vd = target(edAB, g);
    ASSERT_EQ(vd, vdB);
}

TEST(TestGraph, test_target_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        Graph::vertex_descriptor vdA = add_vertex(g);
        Graph::vertex_descriptor vdB = add_vertex(g);
        Graph::edge_descriptor edAB = std::make_pair(vdA, vdB);
        add_edge(vdA, vdB, g);
        
        Graph::vertex_descriptor vd = target(edAB, g);
        ASSERT_EQ(vd, vdB);
    }
}

TEST(TestGraph, test_target_3) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        add_vertex(g);
    }
        
    for (int i = 1; i < 100; ++i) {
        add_edge(g.vertex_list[0], g.vertex_list[i], g);
    }
    
    for (int i = 1; i < 100; ++i) {
        Graph::edge_descriptor ed = std::make_pair(g.vertex_list[0], g.vertex_list[i]);
        Graph::vertex_descriptor vd = target(ed, g);
        ASSERT_EQ(vd, g.vertex_list[i]);
    }
}

// -----------
// test_vertex
// -----------

TEST(TestGraph, test_vertex_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    
    Graph::vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vd, vdA);
}

TEST(TestGraph, test_vertex_2) {
    Graph g;
    
    for (int i = 0; i < 100; ++i) {
        Graph::vertex_descriptor vdA = add_vertex(g);
        
        Graph::vertex_descriptor vd = vertex(i, g);
        ASSERT_EQ(vd, vdA);
    }
}

TEST(TestGraph, test_vertex_3) {
    Graph g;
    
    add_vertex(g);
    for (int i = 0; i < 100; ++i) {
        Graph::vertex_descriptor vdA = add_vertex(g);
        
        Graph::vertex_descriptor vd = vertex(i, g);
        ASSERT_NE(vd, vdA);
    }
}

// -------------
// test_vertices
// -------------

TEST(TestGraph, test_vertices_1) {
    Graph g;
    
    std::pair<Graph::vertex_iterator, Graph::vertex_iterator> p = vertices(g);
    Graph::vertex_iterator b = p.first;
    Graph::vertex_iterator e = p.second;
    ASSERT_EQ(b, e);
}

TEST(TestGraph, test_vertices_2) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    
    std::pair<Graph::vertex_iterator, Graph::vertex_iterator> p = vertices(g);
    Graph::vertex_iterator b = p.first;
    Graph::vertex_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdA);
    }
    ++b;
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdB);
    }
}

TEST(TestGraph, test_vertices_3) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);
    add_vertex(g);
    
    std::pair<Graph::vertex_iterator, Graph::vertex_iterator> p = vertices(g);
    Graph::vertex_iterator b = p.first;
    Graph::vertex_iterator e = p.second;
    ASSERT_NE(b, e);
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdA);
    }
    ++b;
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdB);
    }
    b += 4;
    if (b != e) {
        Graph::vertex_descriptor vd = *b;
        ASSERT_EQ(vd, vdF);
    }
}

// -----------------
// test_helper_cycle
// -----------------

TEST(TestGraph, test_helper_cycle_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);
    Graph::vertex_descriptor vdG = add_vertex(g);
    Graph::vertex_descriptor vdH = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdE, g);
    add_edge(vdB, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdD, g);
    add_edge(vdD, vdE, g);
    add_edge(vdD, vdF, g);
    add_edge(vdF, vdD, g);
    add_edge(vdF, vdH, g);
    add_edge(vdG, vdH, g);
    
    Graph::vertex_descriptor dummy = -1;
    ASSERT_TRUE(helper_cycle(vdD, dummy, vdD, g));
}

TEST(TestGraph, test_helper_cycle_2) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdE, g);
    add_edge(vdC, vdF, g);
    add_edge(vdE, vdD, g);
    
    Graph::vertex_descriptor dummy = -1;
    ASSERT_FALSE(helper_cycle(vdA, dummy, vdA, g));
}

TEST(TestGraph, test_helper_cycle_3) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);

    add_edge(vdA, vdC, g);
    add_edge(vdC, vdE, g);
    add_edge(vdE, vdB, g);
    add_edge(vdB, vdD, g);
    add_edge(vdD, vdA, g);
    
    Graph::vertex_descriptor dummy = -1;
    ASSERT_TRUE(helper_cycle(vdE, dummy, vdE, g));
}

// --------------
// test_has_cycle
// --------------

TEST(TestGraph, test_has_cycle_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);
    Graph::vertex_descriptor vdG = add_vertex(g);
    Graph::vertex_descriptor vdH = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdE, g);
    add_edge(vdB, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdD, g);
    add_edge(vdD, vdE, g);
    add_edge(vdD, vdF, g);
    add_edge(vdF, vdD, g);
    add_edge(vdF, vdH, g);
    add_edge(vdG, vdH, g);
    
    ASSERT_TRUE(has_cycle(g));
}

TEST(TestGraph, test_has_cycle_2) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdE, g);
    add_edge(vdC, vdF, g);
    add_edge(vdE, vdD, g);
    
    ASSERT_FALSE(has_cycle(g));
}

TEST(TestGraph, test_has_cycle_3) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);

    add_edge(vdA, vdC, g);
    add_edge(vdC, vdE, g);
    add_edge(vdE, vdB, g);
    add_edge(vdB, vdD, g);
    add_edge(vdD, vdA, g);
    
    ASSERT_TRUE(has_cycle(g));
}

// ---------------------
// test_topological_sort
// ---------------------

TEST(TestGraph, test_topological_sort_1) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);
    Graph::vertex_descriptor vdG = add_vertex(g);
    Graph::vertex_descriptor vdH = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdE, g);
    add_edge(vdB, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdD, g);
    add_edge(vdD, vdE, g);
    add_edge(vdD, vdF, g);
    add_edge(vdF, vdD, g);
    add_edge(vdF, vdH, g);
    add_edge(vdG, vdH, g);
    
    std::ostringstream out;
    ASSERT_THROW(topological_sort(g, std::ostream_iterator<Graph::vertex_descriptor>(out, " ")), boost::not_a_dag);
}

TEST(TestGraph, test_topological_sort_2) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);
    Graph::vertex_descriptor vdF = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdD, g);
    add_edge(vdB, vdE, g);
    add_edge(vdC, vdE, g);
    add_edge(vdC, vdF, g);
    add_edge(vdE, vdD, g);
    
    std::ostringstream out;
    topological_sort(g, std::ostream_iterator<Graph::vertex_descriptor>(out, " "));
    ASSERT_EQ(out.str(), "2 5 0 1 4 3 ");
}

TEST(TestGraph, test_topological_sort_3) {
    Graph g;
    
    Graph::vertex_descriptor vdA = add_vertex(g);
    Graph::vertex_descriptor vdB = add_vertex(g);
    Graph::vertex_descriptor vdC = add_vertex(g);
    Graph::vertex_descriptor vdD = add_vertex(g);
    Graph::vertex_descriptor vdE = add_vertex(g);

    add_edge(vdA, vdC, g);
    add_edge(vdC, vdE, g);
    add_edge(vdE, vdB, g);
    add_edge(vdB, vdD, g);
    add_edge(vdD, vdA, g);
    
    std::ostringstream out;
    ASSERT_THROW(topological_sort(g, std::ostream_iterator<Graph::vertex_descriptor>(out, " ")), boost::not_a_dag);
}
