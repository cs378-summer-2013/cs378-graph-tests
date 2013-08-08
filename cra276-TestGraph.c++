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

// ---------
// TestGraph
// ---------

using namespace std;

typedef testing::Types<boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
											 Graph> MyTypes;

template <typename T>
class TestGraph : public testing::Test {
	public:
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


		// extra stuff
		edge_descriptor edBC;
		edge_descriptor edDA;
		edge_descriptor edEF;
		edge_descriptor edFG;
		edge_descriptor edAF;
		


    // -----
    // setUp
    // -----

		// CYCLIC
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
        edGH = add_edge(vdG, vdH, g).first;}
		
		// CYCLIC
		void setUp2 () {
				vdA  = add_vertex(g);
				vdB  = add_vertex(g);
				vdC	 = add_vertex(g);
				vdD  = add_vertex(g);
        edAB = add_edge(vdA, vdB, g).first;
        edBC = add_edge(vdB, vdC, g).first;
        edCD = add_edge(vdC, vdD, g).first;
        edDA = add_edge(vdD, vdA, g).first;}

		// NON-CYCLIC
		void setUp3 () {
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
				edDE = add_edge(vdD, vdE, g).first;
        edEF = add_edge(vdE, vdF, g).first;
        edFG = add_edge(vdF, vdG, g).first;}

		// NON-CYCLIC
		void setUp4 () {
				vdA  = add_vertex(g);
				vdB  = add_vertex(g);
				vdC	 = add_vertex(g);
				vdD  = add_vertex(g);
        edAB = add_edge(vdA, vdB, g).first;
        edBC = add_edge(vdB, vdC, g).first;
        edCD = add_edge(vdC, vdD, g).first;}

		// NON-CYCLIC
		void setUp5 () {
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
				edDE = add_edge(vdD, vdE, g).first;
        edAF = add_edge(vdA, vdF, g).first;
        edFG = add_edge(vdF, vdG, g).first;
        edGH = add_edge(vdG, vdH, g).first;}				
};

		TYPED_TEST_CASE(TestGraph, MyTypes);


    // -------------
    // test_add_edge
    // -------------
 
		// test adding a duplicate edge
		TYPED_TEST(TestGraph, add_edge_1) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
	    pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
      ASSERT_TRUE(p.first  == this->edAB);
      ASSERT_TRUE(p.second == false);}
		
		// test adding a new edge
		TYPED_TEST(TestGraph, add_edge_2) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
	    pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdD, this->g);
      ASSERT_TRUE(p.second == true);}

		// test adding a parallel edge
		TYPED_TEST(TestGraph, add_edge_3) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
	    pair<edge_descriptor, bool> p = add_edge(this->vdB, this->vdA, this->g);
      ASSERT_TRUE(p.second == true);}

		// test adding a new edge with non-existent vertices
		TYPED_TEST(TestGraph, add_edge_4) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
	    pair<edge_descriptor, bool> p = add_edge(10, 20, this->g);
			ASSERT_TRUE(p.second == true);
		  ASSERT_EQ(num_vertices(this->g), 21);}
	
	
    // ----------------------
    // test_adjacent_vertices
    // ----------------------

		// test size of adjacency lists
		TYPED_TEST(TestGraph, adjacent_vertices_1) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::adjacency_iterator adjacency_iterator;
			this->setUp();
			pair<adjacency_iterator, adjacency_iterator> p1 = adjacent_vertices(this->vdG, this->g);
			adjacency_iterator b1 = p1.first;
			adjacency_iterator e1 = p1.second;
			ASSERT_TRUE(distance(b1, e1) == 1);
			pair<adjacency_iterator, adjacency_iterator> p2 = adjacent_vertices(this->vdH, this->g);
			adjacency_iterator b2 = p2.first;
			adjacency_iterator e2 = p2.second;
			ASSERT_TRUE(distance(b2, e2) == 0);}
    
		// test values of adjacency lists
		TYPED_TEST(TestGraph, adjacent_vertices_2) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::adjacency_iterator adjacency_iterator;
			this->setUp();
			pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
			adjacency_iterator b = p.first;
			adjacency_iterator e = p.second;
			ASSERT_TRUE(b != e);
			vertex_descriptor vd1 = *b;
			ASSERT_TRUE(vd1 == this->vdB);
			++b;
			vertex_descriptor vd2 = *b;
			ASSERT_TRUE(vd2 == this->vdC);}


    // ---------
    // test_edge
    // ---------

		// test if valid edge is in edge list
		TYPED_TEST(TestGraph, edge_1) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
			pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
			ASSERT_TRUE(p.first == this->edAB);
			ASSERT_TRUE(p.second == true);}

		// test if invalid edge is in edge list
		TYPED_TEST(TestGraph, edge_2) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
			pair<edge_descriptor, bool> p = edge(this->vdA, this->vdH, this->g);
			ASSERT_TRUE(p.second == false);}

		// test if parallel edges are auto'd to edge list
		TYPED_TEST(TestGraph, edge_3) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
			pair<edge_descriptor, bool> p1 = edge(this->vdG, this->vdH, this->g);
			ASSERT_TRUE(p1.second == true);
			pair<edge_descriptor, bool> p2 = edge(this->vdH, this->vdG, this->g);
			ASSERT_TRUE(p2.second == false);}

		// test addition of new edge with non-existent vertices
		TYPED_TEST(TestGraph, edge_4) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
			pair<edge_descriptor, bool> p1 = add_edge(10, 15, this->g);
			ASSERT_TRUE(p1.second == true);
			pair<edge_descriptor, bool> p2 = edge(10, 15, this->g);
			ASSERT_TRUE(p2.second == true);}

    // ----------
    // test_edges
    // ----------

		// test setUp() graph
		TYPED_TEST(TestGraph, edges_1) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			typedef typename TestFixture::edge_iterator edge_iterator;
			this->setUp();
			pair<edge_iterator, edge_iterator> p = edges(this->g);
			edge_iterator b = p.first;
			edge_iterator e = p.second;
			ASSERT_TRUE(b != e);
			edge_descriptor ed1 = *b;
			ASSERT_TRUE(ed1 == this->edAB);
			++b;
			edge_descriptor ed2 = *b;
			ASSERT_TRUE(ed2 == this->edAC);}

		// test setUp2() graph
		TYPED_TEST(TestGraph, edges_2) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			typedef typename TestFixture::edge_iterator edge_iterator;
			this->setUp2();
			pair<edge_iterator, edge_iterator> p = edges(this->g);
			edge_iterator b = p.first;
			edge_iterator e = p.second;
			ASSERT_TRUE(b != e);
			edge_descriptor ed1 = *b;
			ASSERT_TRUE(ed1 == this->edAB);
			++b;
			edge_descriptor ed2 = *b;
			ASSERT_TRUE(ed2 == this->edBC);}

		// test empty graph
		TYPED_TEST(TestGraph, edges_3) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			typedef typename TestFixture::edge_iterator edge_iterator;
			pair<edge_iterator, edge_iterator> p = edges(this->g);
			edge_iterator b = p.first;
			edge_iterator e = p.second;
			ASSERT_TRUE(distance(b, e) == 0);}


    // --------------
    // test_num_edges
    // --------------

		// test empty graph
		TYPED_TEST(TestGraph, num_edges_1) {
			typedef typename TestFixture::edges_size_type edges_size_type;
			edges_size_type es = num_edges(this->g);
			ASSERT_TRUE(es == 0);}
		
		// test setUp() graph
		TYPED_TEST(TestGraph, num_edges_2) {
			typedef typename TestFixture::edges_size_type edges_size_type;
			this->setUp();
			edges_size_type es = num_edges(this->g);
			ASSERT_TRUE(es == 11);}

		// test setUp() graph with edge added
		TYPED_TEST(TestGraph, num_edges_3) {
			typedef typename TestFixture::edges_size_type edges_size_type;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
	    pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdD, this->g);
      ASSERT_TRUE(p.second == true);
			edges_size_type es = num_edges(this->g);
			ASSERT_TRUE(es == 12);}

		// test setUp() graph with duplicate edge added
 		TYPED_TEST(TestGraph, num_edges_4) {
			typedef typename TestFixture::edges_size_type edges_size_type;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
	    pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
 			ASSERT_TRUE(p.first  == this->edAB);
     	ASSERT_TRUE(p.second == false);
			edges_size_type es = num_edges(this->g);
			ASSERT_TRUE(es == 11);}
  
    // -----------------
    // test_num_vertices
    // -----------------

		TYPED_TEST(TestGraph, num_vertices_1) {
			typedef typename TestFixture::vertices_size_type vertices_size_type;
		  vertices_size_type vs = num_vertices(this->g);
      ASSERT_TRUE(vs == 0);}
		
		TYPED_TEST(TestGraph, num_vertices_2) {
			typedef typename TestFixture::vertices_size_type vertices_size_type;
			this->setUp();
		  vertices_size_type vs = num_vertices(this->g);
      ASSERT_TRUE(vs == 8);}

		TYPED_TEST(TestGraph, num_vertices_3) {
			typedef typename TestFixture::vertices_size_type vertices_size_type;
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
	    vertex_descriptor vdK = add_vertex(this->g);
			ASSERT_TRUE(vdK == 8);
			vertices_size_type vs = num_vertices(this->g);
			ASSERT_TRUE(vs == 9);}

		TYPED_TEST(TestGraph, num_vertices_4) {
			typedef typename TestFixture::vertices_size_type vertices_size_type;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
			pair< edge_descriptor, bool > p = add_edge(16, 9, this->g);
			ASSERT_TRUE(p.second == true);
			vertices_size_type vs = num_vertices(this->g);
			ASSERT_TRUE(vs == 17);}

	  // -----------
    // test_source
    // -----------

		TYPED_TEST(TestGraph, source_1) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
			vertex_descriptor vd = source(this->edAB, this->g);
			ASSERT_TRUE(vd == this->vdA);}

		TYPED_TEST(TestGraph, source_2) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp2();
			vertex_descriptor vd = source(this->edBC, this->g);
			ASSERT_TRUE(vd == this->vdB);}

		TYPED_TEST(TestGraph, source_3) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
      pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
			ASSERT_TRUE(p.second == true);
			vertex_descriptor vd = source(p.first, this->g);
			ASSERT_TRUE(vd == this->vdA);}

		TYPED_TEST(TestGraph, source_4) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
			vertex_descriptor vdK	= add_vertex(this->g);
      pair<edge_descriptor, bool> p = add_edge(vdK, this->vdH, this->g);
			ASSERT_TRUE(p.second == true);
			vertex_descriptor vd = source(p.first, this->g);
			ASSERT_TRUE(vd == vdK);}


    // -----------
    // test_target
    // -----------

		TYPED_TEST(TestGraph, target_1) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
			vertex_descriptor vd = target(this->edAB, this->g);
			ASSERT_TRUE(vd == this->vdB);}
		
		TYPED_TEST(TestGraph, target_2) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp2();
			vertex_descriptor vd = target(this->edBC, this->g);
			ASSERT_TRUE(vd == this->vdC);}

		TYPED_TEST(TestGraph, target_3) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
      pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
			ASSERT_TRUE(p.second == true);
			vertex_descriptor vd = target(p.first, this->g);
			ASSERT_TRUE(vd == this->vdH);}

		TYPED_TEST(TestGraph, target_4) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
			vertex_descriptor vdK = add_vertex(this->g);
      pair<edge_descriptor, bool> p = add_edge(vdK, this->vdH, this->g);
			ASSERT_TRUE(p.second == true);
			vertex_descriptor vd = target(p.first, this->g);
			ASSERT_TRUE(vd == this->vdH);}


    // -----------
    // test_vertex
    // -----------
		
		TYPED_TEST(TestGraph, vertex_1) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
    	vertex_descriptor vd = vertex(0,this->g);
      ASSERT_TRUE(vd == this->vdA);}

		TYPED_TEST(TestGraph, vertex_2) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
    	vertex_descriptor vd = vertex(7,this->g);
      ASSERT_TRUE(vd == this->vdH);}

		TYPED_TEST(TestGraph, vertex_3) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp2();
    	vertex_descriptor vd = vertex(3,this->g);
      ASSERT_TRUE(vd == 3);}

		TYPED_TEST(TestGraph, vertex_4) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
    	vertex_descriptor vd = vertex(7,this->g);
      ASSERT_TRUE(vd == this->vdH);
			vertex_descriptor v1 = add_vertex(this->g);
			vertex_descriptor v2 = vertex(8,this->g);
			ASSERT_TRUE(v1 == v2);}

		TYPED_TEST(TestGraph, vertex_5) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
			pair< edge_descriptor, bool > p = add_edge(15, 3, this->g);
			ASSERT_TRUE(p.second == true);
			vertex_descriptor vd = vertex(15, this->g);
			ASSERT_TRUE(vd == 15);}

    // -------------
    // test_vertices
    // -------------
		
		TYPED_TEST(TestGraph, vertices_1) {
			typedef typename TestFixture::vertex_iterator vertex_iterator;
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
      pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
      vertex_iterator b = p.first;
      vertex_iterator e = p.second;
			ASSERT_TRUE(b != e);
      vertex_descriptor vd1 = *b;
      ASSERT_TRUE(vd1 == this->vdA);
      ++b;
      vertex_descriptor vd2 = *b;
      ASSERT_TRUE(vd2 == this->vdB);}

		TYPED_TEST(TestGraph, vertices_2) {
			typedef typename TestFixture::vertex_iterator vertex_iterator;
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp();
			pair < edge_descriptor, bool > ped = add_edge(15, 10, this->g);
			ASSERT_TRUE(ped.second == true);
      pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
      vertex_iterator b = p.first;
      vertex_iterator e = p.second;
			ASSERT_TRUE(b != e);
			--e;
      vertex_descriptor vd1 = *e;
	    ASSERT_TRUE(vd1 == 15);}


    // --------------
    // test_has_cycle
    // --------------

		TYPED_TEST(TestGraph, has_cycle_1) {
			this->setUp();
			ASSERT_TRUE(has_cycle(this->g));}

		TYPED_TEST(TestGraph, has_cycle_2) {
			this->setUp2();
			ASSERT_TRUE(has_cycle(this->g));}

		TYPED_TEST(TestGraph, has_cycle_3) {
			this->setUp3();
			ASSERT_FALSE(has_cycle(this->g));}

		TYPED_TEST(TestGraph, has_cycle_4) {
			typedef typename TestFixture::edge_descriptor edge_descriptor;
			this->setUp3();
			ASSERT_FALSE(has_cycle(this->g));
			pair< edge_descriptor, bool > p = add_edge(this->vdG, this->vdA, this->g);
			ASSERT_TRUE(p.second == true);
			edge_descriptor edGA = p.first;
			ASSERT_TRUE(source(edGA, this->g) == this->vdG);
			ASSERT_TRUE(target(edGA, this->g) == this->vdA);
			ASSERT_TRUE(has_cycle(this->g));}
			
		TYPED_TEST(TestGraph, has_cycle_5) {
			this->setUp4();
			ASSERT_FALSE(has_cycle(this->g));}

		TYPED_TEST(TestGraph, has_cycle_6) {
			this->setUp5();
			ASSERT_FALSE(has_cycle(this->g));}


    // ---------------------
    // test_topological_sort
    // ---------------------

		TYPED_TEST(TestGraph, topological_sort_1) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp();
			std::ostringstream out;
			try {
				topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));}
			catch (boost::not_a_dag& e) {
				ASSERT_TRUE(std::string(e.what()) == "The graph must be a DAG.");}}

		TYPED_TEST(TestGraph, topological_sort_2) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp3();
			std::ostringstream out;
			topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
      ASSERT_EQ(out.str(), "6 5 4 3 2 1 0 7 ");}

		TYPED_TEST(TestGraph, topological_sort_3) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp4();
			std::ostringstream out;
			topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
      ASSERT_EQ(out.str(), "3 2 1 0 ");}
		
		TYPED_TEST(TestGraph, topological_sort_4) {
			typedef typename TestFixture::vertex_descriptor vertex_descriptor;
			this->setUp5();
			std::ostringstream out;
			topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
      ASSERT_EQ(out.str(), "4 3 2 1 7 6 5 0 ");}
