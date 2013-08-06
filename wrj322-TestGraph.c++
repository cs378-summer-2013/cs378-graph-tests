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
    % this->g++ -ansi -pedantic -I/public/linux/include/boost-1_44 -lcppunit -ldl -Wall TestGraph.c++ -o TestGraph.app
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
#include "boost/graph/exception.hpp"  // adjacency_list
//#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h" // Include GoogleTest.

#define class struct
#define protected public
#define private public

#include "Graph.h"

using namespace std;
using namespace boost;

// ---------
// TestGraph
// ---------

/* 
    Setting test fixture up for typed tests.
*/
typedef testing::Types<adjacency_list<setS, vecS, directedS>, Graph > implementationsToTest;



template <typename T>
class GraphTest : public testing::Test {

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

        vertex_descriptor vdA;
        vertex_descriptor vdB;
        vertex_descriptor vdC;
        vertex_descriptor vdD;
        vertex_descriptor vdE;
        vertex_descriptor vdF;
        vertex_descriptor vdG;
        vertex_descriptor vdH;

        vector<vertex_descriptor> Vds;
        vector<edge_descriptor> Eds;

        edge_descriptor edAB;
        edge_descriptor edAC;
        edge_descriptor edAE;
        edge_descriptor edAD;
        edge_descriptor edAF;
        edge_descriptor edAG;
        edge_descriptor edAH;
        edge_descriptor edBC;
        edge_descriptor edBD;
        edge_descriptor edBE;
        edge_descriptor edCD;
        edge_descriptor edDE;
        edge_descriptor edDF;
        edge_descriptor edEF;
        edge_descriptor edFD;
        edge_descriptor edFH;
        edge_descriptor edFG;
        edge_descriptor edGH;
        edge_descriptor edHA;

        // -----
        // setUp
        // -----

        void setup () {
            this->vdA  = add_vertex(this->g);
            this->vdB  = add_vertex(this->g);
            this->vdC  = add_vertex(this->g);
            this->vdD  = add_vertex(this->g);
            this->vdE  = add_vertex(this->g);
            this->vdF  = add_vertex(this->g);
            this->vdG  = add_vertex(this->g);
            this->vdH  = add_vertex(this->g);
             Vds = {this->vdA, this->vdB, this->vdC, this->vdD, 
                this->vdE, this->vdF, this->vdG, this->vdH};
            this->edAB = add_edge(this->vdA, this->vdB, this->g).first;
            this->edAC = add_edge(this->vdA, this->vdC, this->g).first;
            this->edAE = add_edge(this->vdA, this->vdE, this->g).first;
            this->edBD = add_edge(this->vdB, this->vdD, this->g).first;
            this->edBE = add_edge(this->vdB, this->vdE, this->g).first;
            this->edCD = add_edge(this->vdC, this->vdD, this->g).first;
            this->edDE = add_edge(this->vdD, this->vdE, this->g).first;
            this->edDF = add_edge(this->vdD, this->vdF, this->g).first;
            this->edFD = add_edge(this->vdF, this->vdD, this->g).first;
            this->edFH = add_edge(this->vdF, this->vdH, this->g).first;
            this->edGH = add_edge(this->vdG, this->vdH, this->g).first;
        }

        void setup_noCycle () {
            this->vdA  = add_vertex(this->g);
            this->vdB  = add_vertex(this->g);
            this->vdC  = add_vertex(this->g);
            this->vdD  = add_vertex(this->g);
            this->vdE  = add_vertex(this->g);
            this->vdF  = add_vertex(this->g);
            this->vdG  = add_vertex(this->g);
            this->vdH  = add_vertex(this->g);
             Vds = {this->vdA, this->vdB, this->vdC, this->vdD, 
                this->vdE, this->vdF, this->vdG, this->vdH};
            this->edAB = add_edge(this->vdA, this->vdB, this->g).first;
            this->edAC = add_edge(this->vdA, this->vdC, this->g).first;
            this->edAE = add_edge(this->vdA, this->vdE, this->g).first;
            this->edBD = add_edge(this->vdB, this->vdD, this->g).first;
            this->edBE = add_edge(this->vdB, this->vdE, this->g).first;
            this->edCD = add_edge(this->vdC, this->vdD, this->g).first;
            this->edDE = add_edge(this->vdD, this->vdE, this->g).first;
            this->edFD = add_edge(this->vdF, this->vdD, this->g).first;
            this->edFH = add_edge(this->vdF, this->vdH, this->g).first;
            this->edGH = add_edge(this->vdG, this->vdH, this->g).first;
        }

        void setupStar () {
            this->vdA  = add_vertex(this->g);
            this->vdB  = add_vertex(this->g);
            this->vdC  = add_vertex(this->g);
            this->vdD  = add_vertex(this->g);
            this->vdE  = add_vertex(this->g);
            this->vdF  = add_vertex(this->g);
            this->vdG  = add_vertex(this->g);
            this->vdH  = add_vertex(this->g);
            Vds = {this->vdA, this->vdB, this->vdC, this->vdD, 
                this->vdE, this->vdF, this->vdG, this->vdH};
            this->edAB = add_edge(this->vdA, this->vdB, this->g).first;
            this->edAC = add_edge(this->vdA, this->vdC, this->g).first;
            this->edAD = add_edge(this->vdA, this->vdD, this->g).first;
            this->edAE = add_edge(this->vdA, this->vdE, this->g).first;
            this->edAF = add_edge(this->vdA, this->vdF, this->g).first;
            this->edAG = add_edge(this->vdA, this->vdG, this->g).first;
            this->edAH = add_edge(this->vdA, this->vdH, this->g).first;
            Eds = {this->edAB, this->edAC, this->edAD, this->edAE, 
                this->edAF, this->edAG, this->edAH};
        }


        void setupReverseStar () {
            this->vdA  = add_vertex(this->g);
            this->vdB  = add_vertex(this->g);
            this->vdC  = add_vertex(this->g);
            this->vdD  = add_vertex(this->g);
            this->vdE  = add_vertex(this->g);
            this->vdF  = add_vertex(this->g);
            this->vdG  = add_vertex(this->g);
            this->vdH  = add_vertex(this->g);
            Vds = {this->vdA, this->vdB, this->vdC, this->vdD, 
                this->vdE, this->vdF, this->vdG, this->vdH};
            this->edAE = add_edge(this->vdE, this->vdA, this->g).first;
            this->edAB = add_edge(this->vdB, this->vdA, this->g).first;
            this->edAD = add_edge(this->vdD, this->vdA, this->g).first;
            this->edAF = add_edge(this->vdF, this->vdA, this->g).first;
            this->edAG = add_edge(this->vdG, this->vdA, this->g).first;
            this->edAH = add_edge(this->vdH, this->vdA, this->g).first;
            this->edAC = add_edge(this->vdC, this->vdA, this->g).first;
            Eds = {this->edAB, this->edAC, this->edAD, this->edAE, 
                this->edAF, this->edAG, this->edAH};


        }



        void setupOct () {
            this->vdA  = add_vertex(this->g);
            this->vdB  = add_vertex(this->g);
            this->vdC  = add_vertex(this->g);
            this->vdD  = add_vertex(this->g);
            this->vdE  = add_vertex(this->g);
            this->vdF  = add_vertex(this->g);
            this->vdG  = add_vertex(this->g);
            this->vdH  = add_vertex(this->g);
            Vds = {this->vdA, this->vdB, this->vdC, this->vdD, 
                this->vdE, this->vdF, this->vdG, this->vdH};
            this->edAB = add_edge(this->vdA, this->vdB, this->g).first;
            this->edBC = add_edge(this->vdB, this->vdC, this->g).first;
            this->edCD = add_edge(this->vdC, this->vdD, this->g).first;
            this->edDE = add_edge(this->vdD, this->vdE, this->g).first;
            this->edEF = add_edge(this->vdE, this->vdF, this->g).first;
            this->edFG = add_edge(this->vdF, this->vdG, this->g).first;
            this->edGH = add_edge(this->vdG, this->vdH, this->g).first;
            this->edHA = add_edge(this->vdH, this->vdA, this->g).first;
            Eds = {this->edAB, this->edBC, this->edCD, this->edDE, 
                this->edEF, this->edFG, this->edGH,this->edHA};

        }

        void printStar () {
            cout << "this->vdA: " << this->vdA << endl;
            cout << "this->vdB: " << this->vdB << endl;
            cout << "this->vdC: " << this->vdC << endl;
            cout << "this->vdD: " << this->vdD << endl;
            cout << "this->vdE: " << this->vdE << endl;
            cout << "this->vdF: " << this->vdF << endl;
            cout << "this->vdG: " << this->vdG << endl;
            cout << "this->vdH: " << this->vdH << endl;
        }


};


TYPED_TEST_CASE(GraphTest, implementationsToTest);


TYPED_TEST(GraphTest, constructor_01) {
    ASSERT_TRUE(true);
}



    // ---------------
    // test_add_vertex
    // ---------------


    TEST(MyGraphTest,  test_add_vertex_1) {
        Graph g;
        Graph::vertex_descriptor d = add_vertex(g);

        ASSERT_EQ(d, 0);

        ASSERT_EQ(g.vertices.size(), 1);
        ASSERT_EQ(g.edges.size(), 0);

        ASSERT_EQ(g.adjacentVertices.size(), 0);
        ASSERT_EQ(g.triples.size(), 0); 
    }

    // -----------------
    // test_add_vertex_2
    // -----------------

    TEST(MyGraphTest,  test_add_vertex_2) {
        Graph g;
        int limit = 3;

        for (int i = 0; i < limit; ++i) {
            Graph::vertex_descriptor d = add_vertex(g);

            ASSERT_EQ(d, i);

            ASSERT_EQ(g.vertices.size(), i+1);
            ASSERT_EQ(g.edges.size(), 0);

            ASSERT_EQ(g.adjacentVertices.size(), 0);
            ASSERT_EQ(g.triples.size(), 0); 
        }
    }

    // ---------------
    // test_add_edge_1
    // ---------------

    TEST(MyGraphTest,  test_add_edge_1) {
        Graph g;
        Graph::vertex_descriptor vdA = add_vertex(g);
        Graph::vertex_descriptor vdB = add_vertex(g);

        pair<Graph::edge_descriptor, bool> p = add_edge(vdA, vdB, g);

        ASSERT_EQ(vdA, 0);
        ASSERT_EQ(vdB, 1);

        ASSERT_EQ(p.first, 0);
        ASSERT_TRUE(p.second);

        ASSERT_EQ(g.vertices.size(), 2);
        ASSERT_EQ(g.edges.size(), 1);

        ASSERT_EQ(g.adjacentVertices.size(), 1); // Only because g is directed.
        ASSERT_EQ(g.triples.size(), 1); 
    }

    // ---------------
    // test_add_edge_2
    // ---------------

    TEST(MyGraphTest,  test_add_edge_2) {
        Graph g;

        int limit = 1002;

        for (int i = 0; i < limit; ++i) {
            Graph::vertex_descriptor vdA = add_vertex(g);
            Graph::vertex_descriptor vdB = add_vertex(g);

            pair<Graph::edge_descriptor, bool> p = add_edge(vdA, vdB, g);

            ASSERT_EQ(vdA, 2*i);
            ASSERT_EQ(vdB, 2*i+1);

            ASSERT_EQ(p.first, i);
            ASSERT_TRUE(p.second);

            ASSERT_EQ(g.vertices.size(), 2*i+2);
            ASSERT_EQ(g.edges.size(), i+1);

            ASSERT_EQ(g.adjacentVertices.size(), i+1); // Only because g is directed.
            ASSERT_EQ(g.triples.size(), i+1); 
        }
    }

    // ---------------
    // test_add_edge_3
    // ---------------

    TEST(MyGraphTest,  test_add_edge_3) {
        Graph g;

        int limit = 1002;

        add_vertex(g);

        for (int i = 0; i < limit; ++i) {
            Graph::vertex_descriptor vdB = add_vertex(g);

            pair<Graph::edge_descriptor, bool> p = add_edge(i, vdB, g);

            ASSERT_EQ(vdB, i+1);

            ASSERT_EQ(p.first, i);
            ASSERT_TRUE(p.second);

            ASSERT_EQ(g.vertices.size(), i+2);
            ASSERT_EQ(g.edges.size(), i+1);

            ASSERT_EQ(g.adjacentVertices.size(), i+1); // Only because g is directed.
            ASSERT_EQ(g.triples.size(), i+1); 
        }
    }


    // ----------------
    // test_edge_exists
    // ----------------

    TEST(MyGraphTest,  test_edge_exists) {
        Graph g;
        Graph::vertex_descriptor vdA = add_vertex(g);
        Graph::vertex_descriptor vdB = add_vertex(g);
        Graph::edge_descriptor edAB = add_edge(vdA,vdB,g).first;
        ASSERT_EQ(g.edgeExists(vdA,vdB),edAB);
    }

    // ------------------
    // test_edge_exists_2
    // ------------------

    TEST(MyGraphTest,  test_edge_exists_2) {
        Graph g;
        Graph::vertex_descriptor vdA = add_vertex(g);
        Graph::vertex_descriptor vdB = add_vertex(g);
        ASSERT_EQ(g.edgeExists(vdA,vdB),-1);
    }


    // -------------
    // test_add_edge
    // -------------

    TYPED_TEST(GraphTest,  test_add_edge_1) {
        this->setup();
        pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
        ASSERT_EQ(p.first, this->edAB);
        ASSERT_EQ(p.second, false);
    }


    // ----------------------
    // test_adjacent_vertices
    // ----------------------

    TYPED_TEST(GraphTest,  test_adjacent_vertices_1) {
        this->setup();
        pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;
        ASSERT_NE(b, e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_EQ(vd, this->vdB);
        }
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_EQ(vd, this->vdC);
        }
    }

    // ------------------------
    // test_adjacent_vertices_2
    // ------------------------

    TYPED_TEST(GraphTest,  test_adjacent_vertices_2) {
        this->setupStar();
        //this->printStar();
        pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);

        typename TestFixture::adjacency_iterator b = p.first;
        typename TestFixture::adjacency_iterator e = p.second;

        ASSERT_NE(b, e);
        while (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_NE(vd, this->vdA);
            ASSERT_NE(find(this->Vds.begin(),this->Vds.end(),vd), this->Vds.end());
            ++b;

        }
    }


    // ------------------------
    // test_adjacent_vertices_3
    // ------------------------

    TYPED_TEST(GraphTest,  test_adjacent_vertices_3) {
        this->setupOct();
        for (auto &v : this->Vds) {
            pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(v, this->g);
            typename TestFixture::adjacency_iterator b = p.first;
            typename TestFixture::adjacency_iterator e = p.second;
            ASSERT_NE(b, e);
            ++b;
            ASSERT_EQ(b, e);
        }
    }


    // ---------
    // test_edge
    // ---------

    TYPED_TEST(GraphTest,  test_edge_1) {
        this->setup();
        pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
        ASSERT_EQ(p.first, this->edAB);
        ASSERT_EQ(p.second, true);
    }


    // ---------
    // test_edge
    // ---------

    TYPED_TEST(GraphTest,  test_edge_2) {
        this->setupStar();
        for (auto &e : this->Vds) {
            pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdA, e, this->g);
            if (e == this->vdA) {
                ASSERT_EQ(p.second, false);
            }
            else {
                ASSERT_EQ(p.second, true);
            }
        }
    }


    // ---------
    // test_edge
    // ---------

    TYPED_TEST(GraphTest,  test_edge_3) {
        this->setupOct();
        typename TestFixture::vertex_descriptor before = this->vdH;
        for (auto &current : this->Vds) {
            pair<typename TestFixture::edge_descriptor, bool> p = edge(before, current, this->g);
            ASSERT_EQ(p.second, true);
            before = current;
        }
    }

    // ----------
    // test_edges
    // ----------

    TYPED_TEST(GraphTest,   test_edges_1) {
        this->setup();
        pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->g);
        typename TestFixture::edge_iterator                           b = p.first;
        typename TestFixture::edge_iterator                           e = p.second;
        ASSERT_NE(b, e);
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            ASSERT_EQ(ed, this->edAB);
        }
        ++b;
        if (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            ASSERT_EQ(ed, this->edAC);
        }
    }


    // ------------
    // test_edges_2
    // ------------

    TYPED_TEST(GraphTest,   test_edges_2) {
        this->setupStar();
        pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->g);
        typename TestFixture::edge_iterator                           b = p.first;
        typename TestFixture::edge_iterator                           e = p.second;
        ASSERT_NE(b, e);
        while (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            ASSERT_NE(find(this->Eds.begin(),this->Eds.end(),ed), this->Eds.end());
            ++b;
        }
    }



    // ------------
    // test_edges_3
    // ------------

    TYPED_TEST(GraphTest,   test_edges_3) {
        this->setupOct();
        pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->g);
        typename TestFixture::edge_iterator                           b = p.first;
        typename TestFixture::edge_iterator                           e = p.second;
        ASSERT_NE(b, e);
        while (b != e) {
            typename TestFixture::edge_descriptor ed = *b;
            ASSERT_NE(find(this->Eds.begin(),this->Eds.end(),ed), this->Eds.end());
            ++b;
        }
    }


    // --------------
    // test_num_edges
    // --------------

    TYPED_TEST(GraphTest,   test_num_edges_1) {
        this->setup();
        typename TestFixture::edges_size_type es = num_edges(this->g);
        ASSERT_EQ(es, 11);
    }


    // ----------------
    // test_num_edges_2
    // ----------------

    TYPED_TEST(GraphTest,   test_num_edges_2) {
        this->setupStar();
        typename TestFixture::edges_size_type es = num_edges(this->g);
        ASSERT_EQ(es, this->Eds.size());
        ASSERT_EQ(es, this->Vds.size()-1);
    }



    // ----------------
    // test_num_edges_3
    // ----------------

    TYPED_TEST(GraphTest,   test_num_edges_3) {
        this->setupOct();
        typename TestFixture::edges_size_type es = num_edges(this->g);
        ASSERT_EQ(es, this->Eds.size());
        ASSERT_EQ(es, this->Vds.size());
    }

    // -----------------
    // test_num_vertices
    // -----------------

    TYPED_TEST(GraphTest,   test_num_vertices_1) {
        this->setup();
        typename TestFixture::vertices_size_type vs = num_vertices(this->g);
        ASSERT_EQ(vs, 8);
    }

    // -------------------
    // test_num_vertices_2
    // -------------------

    TYPED_TEST(GraphTest,   test_num_vertices_2) {
        this->setupStar();
        typename TestFixture::vertices_size_type vs = num_vertices(this->g);
        ASSERT_EQ(vs, this->Vds.size());
        ASSERT_EQ(vs, this->Eds.size()+1);
    }


    // -------------------
    // test_num_vertices_3
    // -------------------

    TYPED_TEST(GraphTest,   test_num_vertices_3) {
        this->setupOct();
        typename TestFixture::vertices_size_type vs = num_vertices(this->g);
        ASSERT_EQ(vs, this->Vds.size());
        ASSERT_EQ(vs, this->Eds.size());
    }

    // -----------
    // test_source
    // -----------

    TYPED_TEST(GraphTest,   test_source_1) {
        this->setup();
        typename TestFixture::vertex_descriptor vd = source(this->edAB, this->g);
        ASSERT_EQ(vd, this->vdA);
    }

    // -------------
    // test_source_2
    // -------------

    TYPED_TEST(GraphTest,   test_source_2) {
        this->setupStar();
        for (auto &edge : this->Eds) {
            typename TestFixture::vertex_descriptor vd = source(edge, this->g);
            ASSERT_EQ(vd, this->vdA);
        }
    }

    // -------------
    // test_source_3
    // -------------

    TYPED_TEST(GraphTest,  test_source_3) {
        this->setupOct();
        typename TestFixture::vertex_descriptor before = this->vdA;
        for (auto &edge : this->Eds) {
            typename TestFixture::vertex_descriptor vd = source(edge, this->g);
            ASSERT_EQ(vd, before);
            before = target(edge, this->g);
        }
    }

    // -----------
    // test_target
    // -----------

    TYPED_TEST(GraphTest,   test_target_1) {
        this->setup();
        typename TestFixture::vertex_descriptor vd = target(this->edAB, this->g);
        ASSERT_EQ(vd, this->vdB);
    }

    // -------------
    // test_target_2
    // -------------

    TYPED_TEST(GraphTest,   test_target_2) {
        this->setupStar();
        for (auto &edge : this->Eds) {
            typename TestFixture::vertex_descriptor vd = target(edge, this->g);
            ASSERT_NE(vd, this->vdA);
            ASSERT_NE(find(this->Vds.begin(), this->Vds.end(), vd), this->Vds.end());
        }
    }

    // -------------
    // test_target_3
    // -------------

    TYPED_TEST(GraphTest,  test_target_3) {
        this->setupOct();
        typename TestFixture::vertex_descriptor next = this->vdB;
        for (auto &edge : this->Eds) {
            typename TestFixture::vertex_descriptor vd = target(edge, this->g);
            ASSERT_EQ(vd, next);

            pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(vd, this->g);
            typename TestFixture::adjacency_iterator new_next_itr = p.first;
            next = *new_next_itr;
        }
    }

    // -----------
    // test_vertex
    // -----------

    TYPED_TEST(GraphTest,   test_vertex_1) {
        this->setup();
        typename TestFixture::vertex_descriptor vd = vertex(0, this->g);
        ASSERT_EQ(vd, this->vdA);
    }

    // -------------
    // test_vertex_2
    // -------------

    TYPED_TEST(GraphTest,  test_vertex_2) {
        this->setupStar();
        int count = 0;

        for (auto &v : this->Vds) {
            typename TestFixture::vertex_descriptor vd = vertex(count, this->g);
            ASSERT_EQ(vd, v);
            ++count;
        }
    }

    // -------------
    // test_vertex_3
    // -------------

    TYPED_TEST(GraphTest,  test_vertex_3) {
        this->setupOct();
        int count = 0;

        for (auto &v : this->Vds) {
            typename TestFixture::vertex_descriptor vd = vertex(count, this->g);
            ASSERT_EQ(vd, v);
            ++count;
        }
    }

    // -------------
    // test_vertices
    // -------------

    TYPED_TEST(GraphTest,   test_vertices_1) {
        this->setup();
        pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g);
        typename TestFixture::vertex_iterator b = p.first;
        typename TestFixture::vertex_iterator e = p.second;
        ASSERT_NE(b, e);
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_EQ(vd, this->vdA);}
        ++b;
        if (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_EQ(vd, this->vdB);
        }
    }

    // ---------------
    // test_vertices_2
    // ---------------

    TYPED_TEST(GraphTest,   test_vertices_2) {
        this->setupStar();
        pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g);
        typename TestFixture::vertex_iterator b = p.first;
        typename TestFixture::vertex_iterator e = p.second;
        ASSERT_NE(b, e);
        while (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_NE(find(this->Vds.begin(),this->Vds.end(), vd), this->Vds.end());
            ++b;
        }
    }

    // ---------------
    // test_vertices_3
    // ---------------

    TYPED_TEST(GraphTest,   test_vertices_3) {
        this->setupOct();
        pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g);
        typename TestFixture::vertex_iterator b = p.first;
        typename TestFixture::vertex_iterator e = p.second;
        ASSERT_NE(b, e);
        while (b != e) {
            typename TestFixture::vertex_descriptor vd = *b;
            ASSERT_NE(find(this->Vds.begin(),this->Vds.end(), vd), this->Vds.end());
            ++b;
        }
    }

    // --------------
    // test_has_cycle
    // --------------

    TYPED_TEST(GraphTest,   test_has_cycle_1) {
        this->setup();
        ASSERT_TRUE(has_cycle(this->g));
    }

    // ----------------
    // test_has_cycle_2
    // ----------------

    TYPED_TEST(GraphTest,   test_has_cycle_2) {
        this->setupStar();
        ASSERT_FALSE(has_cycle(this->g));
    }

    // ----------------
    // test_has_cycle_3
    // ----------------

    TYPED_TEST(GraphTest,   test_has_cycle_3) {
        this->setupOct();
        ASSERT_TRUE(has_cycle(this->g));
    }

    // ----------------
    // test_has_cycle_4
    // ----------------

    TYPED_TEST(GraphTest,   test_has_cycle_4) {
        this->setupReverseStar();
        ASSERT_FALSE(has_cycle(this->g));
    }

    // ---------------------
    // test_topological_sort
    // ---------------------

    TYPED_TEST(GraphTest,   test_topological_sort_1) {
        this->setup();
        ostringstream out;
        ASSERT_THROW(topological_sort(this->g, ostream_iterator<typename TestFixture::vertex_descriptor>(out, " ")), not_a_dag);
    }



    // -----------------------
    // test_topological_sort_2
    // -----------------------

    TYPED_TEST(GraphTest,   test_topological_sort_2) {
        this->setup_noCycle();
        ostringstream out;
        topological_sort(this->g, ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
        ASSERT_EQ(out.str(), "0 1 2 5 3 4 6 7 ");
    }


    // -----------------------
    // test_topological_sort_3
    // -----------------------

    TYPED_TEST(GraphTest,   test_topological_sort_3) {
        this->setupStar();
        ostringstream out;
        topological_sort(this->g, ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
        ASSERT_EQ(out.str(), "0 1 2 3 4 5 6 7 ");
    }


    // -----------------------
    // test_topological_sort_4
    // -----------------------

    TYPED_TEST(GraphTest,   test_topological_sort_4) {
        this->setupReverseStar();
        ostringstream out;
        topological_sort(this->g, ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
        ASSERT_EQ(out.str(), "1 2 3 4 5 6 7 0 ");
    }

    // -----------------------
    // test_topological_sort_5
    // -----------------------

    TYPED_TEST(GraphTest,   test_topological_sort_5) {
        this->setupOct();
        ostringstream out;
        ASSERT_THROW(topological_sort(this->g, ostream_iterator<typename TestFixture::vertex_descriptor>(out, " ")), not_a_dag);
    }

