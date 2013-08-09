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

using namespace std;
//using namespace boost;
#include "Graph.h"
// ---------
// TestGraph
// ---------





template <typename T>
class GraphTest : public ::testing:: Test {
    protected:
        typedef T                                       graph_type;
        typedef typename graph_type::vertex_descriptor  vertex_descriptor;
        typedef typename graph_type::edge_descriptor    edge_descriptor;

        typedef typename graph_type::vertex_iterator    vertex_iterator;
        typedef typename graph_type::edge_iterator      edge_iterator;
        typedef typename graph_type::adjacency_iterator adjacency_iterator;

        typedef typename graph_type::vertices_size_type vertices_size_type;
        typedef typename graph_type::edges_size_type    edges_size_type;
        
    // directed, sparse, unweighted
    // possibly connected
    // possibly cyclic
    protected:
        graph_type g;
        graph_type top;
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

typedef ::testing::Types< boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>, Graph > MyTypes;
TYPED_TEST_CASE(GraphTest, MyTypes);




    // -------------
    // test_add_edge
    // -------------
TYPED_TEST(GraphTest,  test_add_edge_1) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(p.first, this->edAB);
    ASSERT_EQ(p.second , false);
}

TYPED_TEST(GraphTest, test_add_edge_2) {
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdD, this->g);
    ASSERT_EQ(p.second, true);
}

TYPED_TEST(GraphTest, test_add_edge_3){
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdA, this->g);
    ASSERT_EQ(p.second, true);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(GraphTest,test_adjacent_vertices_1){
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdB);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdC);
    }
}

TYPED_TEST(GraphTest, test_adjacent_vertices_2){
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    adjacency_iterator b = p.first;
    ASSERT_EQ(*b, this->vdB);
    ++b;
    ASSERT_EQ(*b, this->vdC);
    ++b;
    ASSERT_EQ(*b, this->vdE);
}

TYPED_TEST(GraphTest, test_adjacent_vertices_3){
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdE, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_EQ(b, e);
}

/*TYPED_TEST(GraphTest, test_adjacent_vertices_4){
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
}*/


    // ---------
    // test_edge
    // ---------

TYPED_TEST(GraphTest, test_edge_1){
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(p.first, this->edAB);
    ASSERT_EQ(p.second , true);
}

TYPED_TEST(GraphTest, test_edge_2){
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdD, this->g);
    std::pair<int, int> v (0, 3);
    //ASSERT_EQ(p.first, v);
    ASSERT_EQ(p.second , false);
}

//go back and change this to be a different test
TYPED_TEST(GraphTest, test_edge_3){
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
    ASSERT_EQ(p.first, this->edAB);
    ASSERT_EQ(p.second , true);
}


    // ----------
    // test_edges
    // ----------

TYPED_TEST(GraphTest, test_edges_1){
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(ed, this->edAB);
    }
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(ed, this->edAC);
    }
}

TYPED_TEST(GraphTest, test_edges_2){
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;


    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edAB);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edAC);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edAE);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edBD);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edBE);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edCD);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edDE);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edDF);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edFD);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edFH);
    ++b;
    ASSERT_TRUE(b != e);
    ASSERT_EQ(*b, this->edGH);
    ++b;
    ASSERT_EQ(b, e);
}

    // --------------
    // test_num_edges
    // --------------

TYPED_TEST(GraphTest, test_num_edges_1){
    typedef typename TestFixture::edges_size_type edges_size_type;

    edges_size_type es = num_edges(this->g);
    ASSERT_EQ(es, 11);
}

TYPED_TEST(GraphTest, test_num_edges_2){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::edges_size_type edges_size_type;

    vertex_descriptor a = add_vertex(this->top);
    vertex_descriptor b = add_vertex(this->top);
    add_edge(a, b, this->top);
    edges_size_type es = num_edges(this->top);
    ASSERT_EQ(es, 1);
}

TYPED_TEST(GraphTest, test_num_edges_3){
    typedef typename TestFixture::edges_size_type edges_size_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    vertex_descriptor a = add_vertex(this->top);
    vertex_descriptor b = add_vertex(this->top);
    vertex_descriptor c = add_vertex(this->top);
    vertex_descriptor d = add_vertex(this->top);
    add_edge(a, b, this->top);
    add_edge(a, a, this->top);
    add_edge(a, c, this->top);
    add_edge(a, d, this->top);
    edges_size_type es = num_edges(this->top);
    ASSERT_EQ(es, 4);
}

    // -----------------
    // test_num_vertices
    // -----------------

TYPED_TEST(GraphTest, test_num_vertices_1){
    typedef typename TestFixture::vertices_size_type vertices_size_type;

        vertices_size_type vs = num_vertices(this->g);
        ASSERT_EQ(vs,8);
}

TYPED_TEST(GraphTest, test_num_vertices_2){
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    add_vertex(this->top);
    add_vertex(this->top);
    ASSERT_EQ(num_vertices(this->top), 2);
}

TYPED_TEST(GraphTest, test_num_vertices_3){
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    add_vertex(this->top);
    add_vertex(this->top);
    add_vertex(this->top);
    add_vertex(this->top);
    ASSERT_EQ(num_vertices(this->top), 4);
}


    // -----------
    // test_source
    // -----------
TYPED_TEST(GraphTest, test_source_1){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    vertex_descriptor vd = source(this->edAB, this->g);
    ASSERT_EQ(vd, this->vdA);
}

TYPED_TEST(GraphTest, test_source_2){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edAC, this->g);
    ASSERT_EQ(vd, this->vdA);
}

TYPED_TEST(GraphTest, test_source_3){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edFH, this->g);
    ASSERT_EQ(vd, this->vdF);


}

    // -----------
    // test_target
    // -----------

TYPED_TEST(GraphTest, test_target_1){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edAB, this->g);
    ASSERT_EQ(vd, this->vdB);
}

    // -----------
    // test_vertex
    // -----------

TYPED_TEST(GraphTest, test_vertex_1){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(0, this->g);
    ASSERT_EQ(vd, this->vdA);
}

TYPED_TEST(GraphTest, test_vertex_2){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(3, this->g);
    ASSERT_EQ(vd, this->vdD);
}

TYPED_TEST(GraphTest, test_vertex_3){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(1, this->g);
    ASSERT_EQ(vd, this->vdB);
}

    // -------------
    // test_vertices
    // -------------

TYPED_TEST(GraphTest, test_vertices_1){
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdA);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdB);
    }
}

TYPED_TEST(GraphTest, test_vertices_2){
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdA);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdB);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdC);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdD);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdE);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdF);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdG);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdH);
    }
    ++b;
    ASSERT_EQ(b,e);
}

TYPED_TEST(GraphTest, test_vertices_3){
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator b = p.first;
    vertex_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vd, this->vdA);}
    ASSERT_FALSE(b == e);
}

    // --------------
    // test_has_cycle
    // --------------

TYPED_TEST(GraphTest, test_has_cycle_1){
  ASSERT_TRUE(has_cycle(this->g));
}


TYPED_TEST(GraphTest, test_has_cycle_2){
    typedef typename TestFixture::edges_size_type edges_size_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    vertex_descriptor a = add_vertex(this->top);
    add_edge(a, a, this->top);
    ASSERT_TRUE(has_cycle(this->top));
}

TYPED_TEST(GraphTest, test_has_cycle_3){
    typedef typename TestFixture::edges_size_type edges_size_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::edge_descriptor edge_descriptor;

    add_vertex(this->top);
    add_vertex(this->top);
    add_vertex(this->top);
    add_vertex(this->top);
    ASSERT_FALSE(has_cycle(this->top));
}
      

//     // ---------------------
//     // test_topological_sort
//     // ---------------------

TYPED_TEST(GraphTest, test_topological_sort_1){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    try {
        topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_FALSE(1 == 4);
    }
    catch(boost::not_a_dag& e) {
        
    }
}

TYPED_TEST(GraphTest, test_topological_sort_2) {
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    vertex_descriptor a  = add_vertex(this->top);
    add_vertex(this->top);
    add_vertex(this->top);
    add_vertex(this->top);
    vertex_descriptor c  = add_vertex(this->top);
    add_edge(a, c, this->top);
    topological_sort(this->top, std::ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ(out.str(), "4 0 1 2 3 ");

}


TYPED_TEST(GraphTest, test_topological_sort_3){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    vertex_descriptor a  = add_vertex(this->top);
    vertex_descriptor c  = add_vertex(this->top);
    vertex_descriptor d  = add_vertex(this->top);
    vertex_descriptor e  = add_vertex(this->top);
    add_edge(a, c, this->top);
    add_edge(a, e, this->top);
    add_edge(c, d, this->top);
    topological_sort(this->top, std::ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ(out.str(), "2 1 3 0 ");

}

TYPED_TEST(GraphTest, test_topological_sort_4){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    vertex_descriptor a  = add_vertex(this->top);
    vertex_descriptor b  = add_vertex(this->top);
    vertex_descriptor t  = add_vertex(this->top);
    vertex_descriptor c  = add_vertex(this->top);
    vertex_descriptor d  = add_vertex(this->top);
    add_edge(a, d, this->top);
    add_edge(a, c, this->top);
    add_edge(d, b, this->top);
    add_edge(d, t, this->top);

    topological_sort(this->top, std::ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ(out.str(), "3 1 2 4 0 ");

}

TYPED_TEST(GraphTest, test_topological_sort_5){
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    std::ostringstream out;
    vertex_descriptor a  = add_vertex(this->top);
    vertex_descriptor b  = add_vertex(this->top);
    vertex_descriptor c  = add_vertex(this->top);
    vertex_descriptor d  = add_vertex(this->top);
    add_edge(a, b, this->top);
    add_edge(d, c, this->top);

    topological_sort(this->top, std::ostream_iterator<vertex_descriptor>(out, " "));
    ASSERT_EQ(out.str(), "1 0 2 3 ");

}




TEST(GraphConst, test_constructor_1){
    Graph g;
    ASSERT_EQ(num_edges(g), 0);
    ASSERT_EQ(num_vertices(g), 0);
}

TEST(Graphaddv, test_addingvertex_1){
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    Graph g;
    vertex_descriptor a;
    a = add_vertex(g);
    ASSERT_EQ(a, 0);
    ASSERT_EQ(num_edges(g), 0);
    ASSERT_EQ(num_vertices(g), 1);
}

TEST(Graphaddv, test_addingvertex_2){
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    vertex_descriptor d = add_vertex(g);
    ASSERT_EQ(a, 0);
    ASSERT_EQ(b, 1);
    ASSERT_EQ(c, 2);
    ASSERT_EQ(d, 3);
    ASSERT_EQ(num_vertices(g), 4);
}

TEST(Graphadde, test_addingedge_1){
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor edge_descriptor;

    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    std::pair<edge_descriptor, bool> p = add_edge(a, b, g);
    ASSERT_TRUE(p.second);
    ASSERT_EQ(p.first.first, 0);
    ASSERT_EQ(p.first.second, 1);
    ASSERT_EQ(num_edges(g), 1);
}

TEST(Graphadde, test_addingedge_2){
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor edge_descriptor;

    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    std::pair<edge_descriptor, bool> p = add_edge(a, b, g);
    std::pair<edge_descriptor, bool> t = add_edge(a, b, g);
    ASSERT_TRUE(p.second);
    ASSERT_EQ(p.first.first, 0);
    ASSERT_EQ(p.first.second, 1);
    ASSERT_FALSE(t.second);
    ASSERT_EQ(t.first.first, 0);
    ASSERT_EQ(t.first.second, 1);
    ASSERT_EQ(num_vertices(g) , 2);
    ASSERT_EQ(num_edges(g), 1);
}


TEST(Graphiterators, test_adj_iterators_1){
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::adjacency_iterator adjacency_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;    
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    add_edge(a, b, g);
    add_edge(a, c, g);


    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(a, g);
    adjacency_iterator q = p.first;
    ASSERT_EQ(*q, b);
    ++q;
    ASSERT_EQ(*q, c);
    
}

TEST(Graphiterators, test_adj_iterators_2){
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::adjacency_iterator adjacency_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;    
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    vertex_descriptor d = add_vertex(g);
    add_edge(d, a, g);
    add_edge(a, b, g);
    add_edge(a, c, g);
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(a, g);
    adjacency_iterator q = p.first;
    ASSERT_EQ(*q, b);
    ++q;
    ASSERT_EQ(*q, c);
}


TEST(Graphiterators, test_adj_iterators_3){
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::adjacency_iterator adjacency_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;    
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    vertex_descriptor d = add_vertex(g);

    add_edge(d, a, g);
    add_edge(a, b, g);
    add_edge(b, a, g);
    add_edge(a, c, g);
    add_edge(a, d, g);
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(a, g);
    adjacency_iterator q = p.first;
    ASSERT_EQ(num_edges(g), 5);
    ASSERT_EQ(*q, b);
    ++q;
    ASSERT_EQ(*q, c);
    ++q;
    ASSERT_EQ(*q, d);
    ++q;
}

TEST(Graphiterators, test_vertex_iterators_1){
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::adjacency_iterator adjacency_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;  
    typedef typename Graph::vertex_iterator vertex_iterator;
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    vertex_descriptor d = add_vertex(g);
    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator t = p.first;
    vertex_iterator e = p.second;
    ASSERT_TRUE(t != e);
    ASSERT_EQ(*t, a);
    ++t;
    ASSERT_TRUE(t != e);
    ASSERT_EQ(*t, b);
    ++t;
    ASSERT_TRUE(t != e);
    ASSERT_EQ(*t, c);
    ++t;
    ASSERT_TRUE(t != e);
    ASSERT_EQ(*t, d);
    ++t;
    ASSERT_EQ(t, e);
}

    //-----------
    //source
    //----------

TEST(Graph_source, test_source_1){
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::adjacency_iterator adjacency_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    add_vertex(g);
    add_vertex(g);

    edge_descriptor ab = add_edge(a, b, g).first;
    add_edge(b, a, g);
    vertex_descriptor vd = source(ab, g);
    ASSERT_EQ(vd, a);
}

TEST(Graph_source, test_source_2){
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::adjacency_iterator adjacency_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    add_vertex(g);

    edge_descriptor ab = add_edge(a, b, g).first;
    edge_descriptor cc = add_edge(c, c, g).first;
    add_edge(b, a, g);
    vertex_descriptor vd = source(ab, g);
    ASSERT_EQ(vd, a);
    vertex_descriptor cd = source(cc, g);
    ASSERT_EQ(cd, c);
}

    //--------------
    //egde iterators
    //--------------

TEST(Graph_edges, test_edges_1){
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    //5 verticies
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    vertex_descriptor d = add_vertex(g);
    vertex_descriptor e = add_vertex(g);

    edge_descriptor ab = add_edge(a, b, g).first;
    edge_descriptor ac = add_edge(a, c, g).first;
    edge_descriptor ad = add_edge(a, d, g).first;
    edge_descriptor ae = add_edge(a, e, g).first;
    edge_descriptor bc = add_edge(b, c, g).first;
    edge_descriptor aa = add_edge(a, a, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator x = p.first;
    edge_iterator y = p.second;
    ASSERT_TRUE(x != y);
    ASSERT_EQ(*x, ab);
    ++x;
    ASSERT_TRUE(x != y);
    ASSERT_EQ(*x, ac);
    ++x;
    ASSERT_TRUE(x != y);
    ASSERT_EQ(*x, ad);
    ++x;
    ASSERT_TRUE(x != y);
    ASSERT_EQ(*x, ae);
    ++x;
    ASSERT_TRUE(x != y);
    ASSERT_EQ(*x, bc);
    ++x;
    ASSERT_TRUE(x != y);
    ASSERT_EQ(*x, aa);
    ++x;


}

TEST(Graph_edge, test_edge_1){
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    //3 verticies
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    edge_descriptor ab = add_edge(a, b, g).first;
    add_edge(a, c, g).first;
    edge_descriptor bc = add_edge(b, c, g).first;

    std::pair<edge_descriptor, bool> p = edge(a, b, g);
    ASSERT_EQ(p.first, ab);
    ASSERT_EQ(p.second , true);

    std::pair<edge_descriptor, bool> y = edge(b, c, g);
    ASSERT_EQ(y.first, bc);
    ASSERT_EQ(y.second , true);

    std::pair<edge_descriptor, bool> x = edge(c, c, g);
    ASSERT_EQ(x.first, make_pair(c, c));
    ASSERT_EQ(x.second , false);

}


TEST(Graph_cycle, test_cycle_1){
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    add_edge(a, b, g);
    ASSERT_FALSE(has_cycle(g));
}

TEST(Graph_cycle, test_cycle_2){
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    add_edge(a, b, g);
    add_edge(b, a, g);
    ASSERT_TRUE(has_cycle(g));
}

TEST(Graph_cycle, test_cycle_3){
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    vertex_descriptor a = add_vertex(g);
    add_edge(a, a, g);
    ASSERT_TRUE(has_cycle(g));
}

TEST(Graph_cycle, test_cycle_4){
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    vertex_descriptor d = add_vertex(g);
    add_edge(a, b, g);
    add_edge(a, c, g);
    add_edge(a, d, g);
    add_edge(b, c, g);
    add_edge(c, d, g);
    ASSERT_FALSE(has_cycle(g));
}

TEST(Graph_cycle, test_cycle_5) {
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    ASSERT_FALSE(has_cycle(g));
}

TEST(Graph_cycle, test_cycle_6) {
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    vertex_descriptor d = add_vertex(g);
    add_edge(a, b, g);
    add_edge(b, c, g);
    add_edge(c, d, g);
    ASSERT_FALSE(has_cycle(g));
    add_edge(d, a, g);
    ASSERT_TRUE(has_cycle(g));
}

TEST(Graph_cycle, test_cycle_7) {
    typedef typename Graph::edge_descriptor edge_descriptor;
    typedef typename Graph::edge_iterator edge_iterator;
    typedef typename Graph::vertex_descriptor vertex_descriptor;     
    Graph g;
    vertex_descriptor a = add_vertex(g);
    vertex_descriptor b = add_vertex(g);
    vertex_descriptor c = add_vertex(g);
    vertex_descriptor d = add_vertex(g);
    add_edge(a, b, g);
    add_edge(c, d, g);
    ASSERT_FALSE(has_cycle(g));
    add_edge(a, d, g);
    add_edge(b, c, g);
    add_edge(a, c, g);
    add_edge(b, d, g);
    ASSERT_FALSE(has_cycle(g));
    add_edge(d, a, g);
    ASSERT_TRUE(has_cycle(g));

}



