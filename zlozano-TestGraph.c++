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
#include "boost/graph/topological_sort.hpp"

#include "Graph.h"

#include "gtest/gtest.h"

// -----------------
// Google Test Suite
// -----------------

// ---------
// TestGraph
// ---------

    // --------
    // typedefs
    // --------

    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>  boost_graph_type;

    typedef typename boost_graph_type::vertex_descriptor  boost_vertex_descriptor;
    typedef typename boost_graph_type::edge_descriptor    boost_edge_descriptor;

    typedef typename boost_graph_type::vertex_iterator    boost_vertex_iterator;
    typedef typename boost_graph_type::edge_iterator      boost_edge_iterator;
    typedef typename boost_graph_type::adjacency_iterator boost_adjacency_iterator;

    typedef typename boost_graph_type::vertices_size_type boost_vertices_size_type;
    typedef typename boost_graph_type::edges_size_type    boost_edges_size_type;
    
    typedef Graph									graph_type;

	typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    // -----
    // Tests
    // -----
	
	// boost graph
    // directed, sparse, unweighted
    // possibly connected
    // cyclic
    boost_graph_type b1;

    boost_vertex_descriptor boost_vdA;
    boost_vertex_descriptor boost_vdB;
    boost_vertex_descriptor boost_vdC;
    boost_vertex_descriptor boost_vdD;
    boost_vertex_descriptor boost_vdE;
    boost_vertex_descriptor boost_vdF;
    boost_vertex_descriptor boost_vdG;
    boost_vertex_descriptor boost_vdH;

    boost_edge_descriptor boost_edAB;
    boost_edge_descriptor boost_edAC;
    boost_edge_descriptor boost_edAE;
    boost_edge_descriptor boost_edBD;
    boost_edge_descriptor boost_edBE;
    boost_edge_descriptor boost_edCD;
    boost_edge_descriptor boost_edDE;
    boost_edge_descriptor boost_edDF;
    boost_edge_descriptor boost_edFD;
    boost_edge_descriptor boost_edFH;
    boost_edge_descriptor boost_edGH;
    
	// boost graph
	// directed, sparse, unweighted
    // possibly connected
    // acyclic
    boost_graph_type b2;

    boost_vertex_descriptor boost_vdI;
    boost_vertex_descriptor boost_vdJ;
    boost_vertex_descriptor boost_vdK;
    boost_vertex_descriptor boost_vdL;
    boost_vertex_descriptor boost_vdM;
    boost_vertex_descriptor boost_vdN;
    boost_vertex_descriptor boost_vdO;
    boost_vertex_descriptor boost_vdP;

    boost_edge_descriptor boost_edIJ;
    boost_edge_descriptor boost_edIL;
    boost_edge_descriptor boost_edIM;
    boost_edge_descriptor boost_edJL;
    boost_edge_descriptor boost_edJO;
    boost_edge_descriptor boost_edKM;
    boost_edge_descriptor boost_edLO;
    boost_edge_descriptor boost_edMP;
    boost_edge_descriptor boost_edNI;
    boost_edge_descriptor boost_edNO;
    boost_edge_descriptor boost_edOP;

    // -----
    // setUp
    // -----

    TEST (graph, boost_setup) {
        boost_vdA  = add_vertex(b1);
        boost_vdB  = add_vertex(b1);
        boost_vdC  = add_vertex(b1);
        boost_vdD  = add_vertex(b1);
        boost_vdE  = add_vertex(b1);
        boost_vdF  = add_vertex(b1);
        boost_vdG  = add_vertex(b1);
        boost_vdH  = add_vertex(b1);
        boost_edAB = add_edge(boost_vdA, boost_vdB, b1).first;
        boost_edAC = add_edge(boost_vdA, boost_vdC, b1).first;
        boost_edAE = add_edge(boost_vdA, boost_vdE, b1).first;
        boost_edBD = add_edge(boost_vdB, boost_vdD, b1).first;
        boost_edBE = add_edge(boost_vdB, boost_vdE, b1).first;
        boost_edCD = add_edge(boost_vdC, boost_vdD, b1).first;
        boost_edDE = add_edge(boost_vdD, boost_vdE, b1).first;
        boost_edDF = add_edge(boost_vdD, boost_vdF, b1).first;
        boost_edFD = add_edge(boost_vdF, boost_vdD, b1).first;
        boost_edFH = add_edge(boost_vdF, boost_vdH, b1).first;
        boost_edGH = add_edge(boost_vdG, boost_vdH, b1).first;
	}
    
	TEST (graph, boost_setup2) {
        boost_vdI  = add_vertex(b2);
        boost_vdJ  = add_vertex(b2);
        boost_vdK  = add_vertex(b2);
        boost_vdL  = add_vertex(b2);
        boost_vdM  = add_vertex(b2);
        boost_vdN  = add_vertex(b2);
        boost_vdO  = add_vertex(b2);
        boost_vdP  = add_vertex(b2);
		boost_edIJ = add_edge(boost_vdI, boost_vdJ, b2).first;
		boost_edIL = add_edge(boost_vdI, boost_vdL, b2).first;
		boost_edIM = add_edge(boost_vdI, boost_vdM, b2).first;
		boost_edJL = add_edge(boost_vdJ, boost_vdL, b2).first;
		boost_edJO = add_edge(boost_vdJ, boost_vdO, b2).first;
		boost_edKM = add_edge(boost_vdK, boost_vdM, b2).first;
		boost_edLO = add_edge(boost_vdL, boost_vdO, b2).first;
		boost_edMP = add_edge(boost_vdM, boost_vdP, b2).first;
		boost_edNI = add_edge(boost_vdN, boost_vdI, b2).first;
		boost_edNO = add_edge(boost_vdN, boost_vdO, b2).first;
		boost_edOP = add_edge(boost_vdO, boost_vdP, b2).first;
	}
    	
	// my graph
    // directed, sparse, unweighted
    // possibly connected
    // cyclic
    graph_type g1;

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
    
	// my graph
	// directed, sparse, unweighted
    // possibly connected
    // acyclic
    graph_type g2;

    vertex_descriptor vdI;
    vertex_descriptor vdJ;
    vertex_descriptor vdK;
    vertex_descriptor vdL;
    vertex_descriptor vdM;
    vertex_descriptor vdN;
    vertex_descriptor vdO;
    vertex_descriptor vdP;

    edge_descriptor edIJ;
    edge_descriptor edIL;
    edge_descriptor edIM;
    edge_descriptor edJL;
    edge_descriptor edJO;
    edge_descriptor edKM;
    edge_descriptor edLO;
    edge_descriptor edMP;
    edge_descriptor edNI;
    edge_descriptor edNO;
    edge_descriptor edOP;


	TEST (graph, setup) {
        vdA  = add_vertex(g1);
        vdB  = add_vertex(g1);
        vdC  = add_vertex(g1);
        vdD  = add_vertex(g1);
        vdE  = add_vertex(g1);
        vdF  = add_vertex(g1);
        vdG  = add_vertex(g1);
        vdH  = add_vertex(g1);
        edAB = add_edge(vdA, vdB, g1).first;
        edAC = add_edge(vdA, vdC, g1).first;
        edAE = add_edge(vdA, vdE, g1).first;
        edBD = add_edge(vdB, vdD, g1).first;
        edBE = add_edge(vdB, vdE, g1).first;
        edCD = add_edge(vdC, vdD, g1).first;
        edDE = add_edge(vdD, vdE, g1).first;
        edDF = add_edge(vdD, vdF, g1).first;
        edFD = add_edge(vdF, vdD, g1).first;
        edFH = add_edge(vdF, vdH, g1).first;
        edGH = add_edge(vdG, vdH, g1).first;
	}
    
	TEST (graph, setup2) {
        vdI  = add_vertex(g2);
        vdJ  = add_vertex(g2);
        vdK  = add_vertex(g2);
        vdL  = add_vertex(g2);
        vdM  = add_vertex(g2);
        vdN  = add_vertex(g2);
        vdO  = add_vertex(g2);
        vdP  = add_vertex(g2);
		edIJ = add_edge(vdI, vdJ, g2).first;
		edIL = add_edge(vdI, vdL, g2).first;
		edIM = add_edge(vdI, vdM, g2).first;
		edJL = add_edge(vdJ, vdL, g2).first;
		edJO = add_edge(vdJ, vdO, g2).first;
		edKM = add_edge(vdK, vdM, g2).first;
		edLO = add_edge(vdL, vdO, g2).first;
		edMP = add_edge(vdM, vdP, g2).first;
		edNI = add_edge(vdN, vdI, g2).first;
		edNO = add_edge(vdN, vdO, g2).first;
		edOP = add_edge(vdO, vdP, g2).first;
	}

    // -------------
    // test_add_edge
    // -------------

	// my graph

    TEST (graph, test_add_edge) {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g1);
        ASSERT_TRUE(p.first  == edAB);
        ASSERT_TRUE(p.second == false);
	}

	TEST (graph, test_add_edge_2) {
		graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		ASSERT_TRUE(num_edges(g)    == 0);
		std::pair<edge_descriptor, bool> p = add_edge(3, 5, g);
		ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(g) == 6);
		ASSERT_TRUE(num_edges(g)    == 1);
	}

	TEST (graph, test_add_edge_3) {
		graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		ASSERT_TRUE(num_edges(g)    == 0);
		std::pair<edge_descriptor, bool> p = add_edge(3, 5, g);
		ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(g) == 6);
		ASSERT_TRUE(num_edges(g)    == 1);
		std::pair<edge_descriptor, bool> p2 = add_edge(3, 5, g);
		ASSERT_TRUE(p2.second == false);
		ASSERT_TRUE(num_vertices(g) == 6);
		ASSERT_TRUE(num_edges(g)    == 1);
	}	
    
	TEST (graph, test_add_edge_4) {
		graph_type g;
        add_vertex(g);
        add_vertex(g);
		ASSERT_TRUE(num_vertices(g) == 2);
		ASSERT_TRUE(num_edges(g)    == 0);
		std::pair<edge_descriptor, bool> p = add_edge(4, 5, g);
		ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(g) == 6);
		ASSERT_TRUE(num_edges(g)    == 1);
	}
	
	TEST (graph, test_add_edge_5) {
		graph_type g;
        add_vertex(g);
        add_vertex(g);
		ASSERT_TRUE(num_vertices(g) == 2);
		ASSERT_TRUE(num_edges(g)    == 0);
		std::pair<edge_descriptor, bool> p = add_edge(90, 5, g);
		ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(g) == 91);
		ASSERT_TRUE(num_edges(g)    == 1);
	}

	// boost graph

	TEST (graph, boost_test_add_edge) {
        std::pair<boost_edge_descriptor, bool> p = add_edge(boost_vdA, boost_vdB, b1);
        ASSERT_TRUE(p.first  == boost_edAB);
        ASSERT_TRUE(p.second == false);
	}

	TEST (graph, boost_test_add_edge_2) {
		boost_graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		ASSERT_TRUE(num_edges(g)    == 0);
		std::pair<boost_edge_descriptor, bool> p = add_edge(3, 5, g);
		ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(g) == 6);
		ASSERT_TRUE(num_edges(g)    == 1);
	}

	TEST (graph, boost_test_add_edge_3) {
		boost_graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		ASSERT_TRUE(num_edges(g)    == 0);
		std::pair<boost_edge_descriptor, bool> p = add_edge(3, 5, g);
		ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(g) == 6);
		ASSERT_TRUE(num_edges(g)    == 1);
		std::pair<boost_edge_descriptor, bool> p2 = add_edge(3, 5, g);
		ASSERT_TRUE(p2.second == false);
		ASSERT_TRUE(num_vertices(g) == 6);
		ASSERT_TRUE(num_edges(g)    == 1);
	}	
	
	TEST (graph, boost_test_add_edge_4) {
		boost_graph_type g;
        add_vertex(g);
        add_vertex(g);
		ASSERT_TRUE(num_vertices(g) == 2);
		ASSERT_TRUE(num_edges(g)    == 0);
		std::pair<boost_edge_descriptor, bool> p = add_edge(4, 5, g);
		ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(g) == 6);
		ASSERT_TRUE(num_edges(g)    == 1);
	}
	
	TEST (graph, boost_test_add_edge_5) {
		boost_graph_type g;
        add_vertex(g);
        add_vertex(g);
		ASSERT_TRUE(num_vertices(g) == 2);
		ASSERT_TRUE(num_edges(g)    == 0);
		std::pair<boost_edge_descriptor, bool> p = add_edge(90, 5, g);
		ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(g) == 91);
		ASSERT_TRUE(num_edges(g)    == 1);
	}

	// ---------------
	// test_add_vertex
	// ---------------

	// my graph

	TEST (graph, test_add_vertex) {
		graph_type g;
		vertex_descriptor vA = add_vertex(g);
		ASSERT_TRUE(vA == 0);
	}
	
	TEST (graph, test_add_vertex_2) {
		graph_type g;
		vertex_descriptor vA = add_vertex(g);
		vertex_descriptor vB = add_vertex(g);
		ASSERT_TRUE(vA == 0);
		ASSERT_TRUE(vB == 1);
	}

	TEST (graph, test_add_vertex_3) {
		graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		vertex_descriptor vA = add_vertex(g);
		vertex_descriptor vB = add_vertex(g);
		ASSERT_TRUE(vA == 0);
		ASSERT_TRUE(vB == 1);
		ASSERT_TRUE(num_vertices(g) == 2);
		ASSERT_TRUE(num_edges(g)	== 0);
	}

	// boost graph

	TEST (graph, boost_test_add_vertex) {
		boost_graph_type g;
		boost_vertex_descriptor vA = add_vertex(g);
		ASSERT_TRUE(vA == 0);
	}
	
	TEST (graph, boost_test_add_vertex_2) {
		boost_graph_type g;
		boost_vertex_descriptor vA = add_vertex(g);
		boost_vertex_descriptor vB = add_vertex(g);
		ASSERT_TRUE(vA == 0);
		ASSERT_TRUE(vB == 1);
	}

	TEST (graph, boost_test_add_vertex_3) {
		boost_graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		boost_vertex_descriptor vA = add_vertex(g);
		boost_vertex_descriptor vB = add_vertex(g);
		ASSERT_TRUE(vA == 0);
		ASSERT_TRUE(vB == 1);
		ASSERT_TRUE(num_vertices(g) == 2);
		ASSERT_TRUE(num_edges(g)	== 0);
	}




    // ----------------------
    // test_adjacent_vertices
    // ----------------------
    
	// my graph

	TEST (graph, test_adjacent_vertices) {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g1);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == vdB);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == vdC);}
	}

    TEST (graph, test_adjacent_vertices_2) {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdP, g2);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
		ASSERT_TRUE(b == e);
	}

    TEST (graph, test_adjacent_vertices_3) {
		graph_type g;
		vertex_descriptor v = add_vertex(g);
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(v, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
		ASSERT_TRUE(b == e);
		add_edge(2, 7, g);	
        std::pair<adjacency_iterator, adjacency_iterator> p2 = adjacent_vertices(2, g);
        b = p2.first;
        e = p2.second;
		ASSERT_TRUE(b != e);
		++b;
		ASSERT_TRUE(b == e);
	}

	// boost graph

    TEST (graph, boost_test_adjacent_vertices) {
        std::pair<boost_adjacency_iterator, boost_adjacency_iterator> p = adjacent_vertices(boost_vdA, b1);
        boost_adjacency_iterator b = p.first;
        boost_adjacency_iterator e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            boost_vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == boost_vdB);}
        ++b;
        if (b != e) {
            boost_vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == boost_vdC);}
	}

    TEST (graph, boost_test_adjacent_vertices_2) {
        std::pair<boost_adjacency_iterator, boost_adjacency_iterator> p = adjacent_vertices(boost_vdP, b2);
        boost_adjacency_iterator b = p.first;
        boost_adjacency_iterator e = p.second;
		ASSERT_TRUE(b == e);
	}

    TEST (graph, boost_test_adjacent_vertices_3) {
		boost_graph_type g;
		boost_vertex_descriptor v = add_vertex(g);
        std::pair<boost_adjacency_iterator, boost_adjacency_iterator> p = adjacent_vertices(v, g);
        boost_adjacency_iterator b = p.first;
        boost_adjacency_iterator e = p.second;
		ASSERT_TRUE(b == e);
		add_edge(2, 7, g);	
        std::pair<boost_adjacency_iterator, boost_adjacency_iterator> p2 = adjacent_vertices(2, g);
        b = p2.first;
        e = p2.second;
		ASSERT_TRUE(b != e);
		++b;
		ASSERT_TRUE(b == e);
	}

    // ---------
    // test_edge
    // ---------

	// my graph

    TEST (graph, test_edge) {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g1);
        ASSERT_TRUE(p.first  == edAB);
        ASSERT_TRUE(p.second == true);
	}
    
TEST (graph, test_edge_2) {
	std::pair<edge_descriptor, bool> p = edge(100, vdB, g1);
	ASSERT_TRUE(p.second == false);
}

TEST (graph, test_edge_3) {
	graph_type g;
	std::pair<edge_descriptor, bool> e = add_edge(1, 2, g);
	std::pair<edge_descriptor, bool> p = edge(1, 2, g);
	ASSERT_TRUE(p.first  == e.first);
	ASSERT_TRUE(e.second == true);
	ASSERT_TRUE(p.second == true);
}

// boost graph

TEST (graph, boost_test_edge) {
	std::pair<boost_edge_descriptor, bool> p = edge(boost_vdA, boost_vdB, b1);
	ASSERT_TRUE(p.first  == boost_edAB);
	ASSERT_TRUE(p.second == true);
}

TEST (graph, boost_test_edge_3) {
	boost_graph_type g;
	std::pair<boost_edge_descriptor, bool> e = add_edge(1, 2, g);
	std::pair<boost_edge_descriptor, bool> p = edge(1, 2, g);
	ASSERT_TRUE(p.first  == e.first);
	ASSERT_TRUE(e.second == true);
	ASSERT_TRUE(p.second == true);
}

// ----------
// test_edges
// ----------

// my graph

TEST (graph, test_edges) {
	std::pair<edge_iterator, edge_iterator> p = edges(g1);
	edge_iterator                           b = p.first;
	edge_iterator                           e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) {
		edge_descriptor ed = *b;
		ASSERT_TRUE(ed == edAB);}
	++b;
	if (b != e) {
		edge_descriptor ed = *b;
		ASSERT_TRUE(ed == edAC);}
}

TEST (graph, test_edges_2) {
	std::pair<edge_iterator, edge_iterator> p = edges(g1);
	edge_iterator b = p.first;
	edge_iterator e = p.second;
	ASSERT_TRUE(b != e);

	int c = 0;

	while (b != e) {
		++c;
		++b;
	}
	ASSERT_TRUE(b == e);
	ASSERT_TRUE(c == 11);
}

TEST (graph, test_edges_3) {
	graph_type g;
	add_vertex(g);
	add_vertex(g);
	add_vertex(g);
	add_vertex(g);
	add_vertex(g);
	add_vertex(g);
	add_edge(5, 1, g);
	add_edge(5, 2, g);
	add_edge(5, 4, g);
	add_edge(4, 2, g);
	std::pair<edge_iterator, edge_iterator> p = edges(g);
	edge_iterator b = p.first;
	edge_iterator e = p.second;
	ASSERT_TRUE(b != e);

	int c = 0;

	while (b != e) {
		++c;
		++b;
	}
	ASSERT_TRUE(b == e);
	ASSERT_TRUE(c == 4);
}

// boost graph

TEST (graph, boost_test_edges) {
	std::pair<boost_edge_iterator, boost_edge_iterator> p = edges(b1);
	boost_edge_iterator                           b = p.first;
	boost_edge_iterator                           e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) {
		boost_edge_descriptor ed = *b;
		ASSERT_TRUE(ed == boost_edAB);}
	++b;
	if (b != e) {
		boost_edge_descriptor ed = *b;
		ASSERT_TRUE(ed == boost_edAC);}
}

TEST (graph, boost_test_edges_2) {
	std::pair<boost_edge_iterator, boost_edge_iterator> p = edges(b1);
	boost_edge_iterator b = p.first;
	boost_edge_iterator e = p.second;
	ASSERT_TRUE(b != e);

	int c = 0;

	while (b != e) {
		++c;
		++b;
	}
	ASSERT_TRUE(b == e);
	ASSERT_TRUE(c == 11);
}

TEST (graph, boost_test_edges_3) {
	boost_graph_type g;
	add_vertex(g);
	add_vertex(g);
	add_vertex(g);
	add_vertex(g);
	add_vertex(g);
	add_vertex(g);
	add_edge(5, 1, g);
	add_edge(5, 2, g);
	add_edge(5, 4, g);
	add_edge(4, 2, g);
	std::pair<boost_edge_iterator, boost_edge_iterator> p = edges(g);
	boost_edge_iterator b = p.first;
	boost_edge_iterator e = p.second;
	ASSERT_TRUE(b != e);

	int c = 0;

	while (b != e) {
		++c;
		++b;
	}
	ASSERT_TRUE(b == e);
	ASSERT_TRUE(c == 4);
}

// --------------
// test_num_edges
// --------------

	// my graph

    TEST (graph, test_num_edges) {
        edges_size_type es = num_edges(g1);
        ASSERT_TRUE(es == 11);
	}
    
	TEST (graph, test_num_edges_2) {
        edges_size_type es = num_edges(g2);
        ASSERT_TRUE(es == 11);
	}

    TEST (graph, test_num_edges_3) {
		graph_type g;
        edges_size_type es = num_edges(g);
        ASSERT_TRUE(es == 0);
		add_edge(1, 2, g);
        es = num_edges(g);
        ASSERT_TRUE(es == 1);
		add_edge(1, 3, g);
        es = num_edges(g);
        ASSERT_TRUE(es == 2);
		add_edge(2, 1, g);
        es = num_edges(g);
        ASSERT_TRUE(es == 3);
	}

	// boost graph

    TEST (graph, boost_test_num_edges) {
        boost_edges_size_type es = num_edges(b1);
        ASSERT_TRUE(es == 11);
	}
    
	TEST (graph, boost_test_num_edges_2) {
        boost_edges_size_type es = num_edges(b2);
        ASSERT_TRUE(es == 11);
	}

    TEST (graph, boost_test_num_edges_3) {
		boost_graph_type g;
        boost_edges_size_type es = num_edges(g);
        ASSERT_TRUE(es == 0);
		add_edge(1, 2, g);
        es = num_edges(g);
        ASSERT_TRUE(es == 1);
		add_edge(1, 3, g);
        es = num_edges(g);
        ASSERT_TRUE(es == 2);
		add_edge(2, 1, g);
        es = num_edges(g);
        ASSERT_TRUE(es == 3);
	}

    // -----------------
    // test_num_vertices
    // -----------------

	// my graph

	TEST (graph, test_num_vertices) {
        vertices_size_type vs = num_vertices(g1);
        ASSERT_TRUE(vs == 8);
	}
	
	TEST (graph, test_num_vertices_2) {
        vertices_size_type vs = num_vertices(g2);
        ASSERT_TRUE(vs == 8);
	}

	TEST (graph, test_num_vertices_3) {
		graph_type g;
        vertices_size_type vs = num_vertices(g);
        ASSERT_TRUE(vs == 0);
		add_vertex(g);
		vs = num_vertices(g);
        ASSERT_TRUE(vs == 1);
		add_edge(2, 46, g);
		vs = num_vertices(g);
        ASSERT_TRUE(vs == 47);

	}
	// boost graph

	TEST (graph, boost_test_num_vertices) {
        boost_vertices_size_type vs = num_vertices(b1);
        ASSERT_TRUE(vs == 8);
	}
	
	TEST (graph, boost_test_num_vertices_2) {
        boost_vertices_size_type vs = num_vertices(b2);
        ASSERT_TRUE(vs == 8);
	}

	TEST (graph, boost_test_num_vertices_3) {
		boost_graph_type g;
        boost_vertices_size_type vs = num_vertices(g);
        ASSERT_TRUE(vs == 0);
		add_vertex(g);
		vs = num_vertices(g);
        ASSERT_TRUE(vs == 1);
		add_edge(2, 46, g);
		vs = num_vertices(g);
        ASSERT_TRUE(vs == 47);

	}

    // -----------
    // test_source
    // -----------

	// my_graph

    TEST (graph, test_source) {
        vertex_descriptor vd = source(edAB, g1);
        ASSERT_TRUE(vd == vdA);
	}

    TEST (graph, test_source_2) {
        vertex_descriptor vd = source(edIJ, g1);
        ASSERT_TRUE(vd == vdI);
        ASSERT_TRUE(vd == vdA);
	}

    TEST (graph, test_source_3) {
		graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		vertex_descriptor vd = source(edIJ, g);
        ASSERT_TRUE(vd == vdI);
		ASSERT_TRUE(num_vertices(g) == 0);
	}

	// boost graph

    TEST (graph, boost_test_source) {
        boost_vertex_descriptor vd = source(boost_edAB, b1);
        ASSERT_TRUE(vd == boost_vdA);
	}

    TEST (graph, boost_test_source_2) {
        boost_vertex_descriptor vd = source(boost_edIJ, b1);
        ASSERT_TRUE(vd == boost_vdI);
	}

    TEST (graph, boost_test_source_3) {
		boost_graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		boost_vertex_descriptor vd = source(boost_edIJ, g);
        ASSERT_TRUE(vd == boost_vdI);
		ASSERT_TRUE(num_vertices(g) == 0);
	}

    // -----------
    // test_target
    // -----------
	
	// my_graph

    TEST (graph, test_target) {
        vertex_descriptor vd = target(edAB, g1);
        ASSERT_TRUE(vd == vdB);
	}

    TEST (graph, test_target_2) {
        vertex_descriptor vd = target(edIJ, g1);
        ASSERT_TRUE(vd == vdJ);
        ASSERT_TRUE(vd == vdB);
	}

    TEST (graph, test_target_3) {
		graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		vertex_descriptor vd = target(edIJ, g);
        ASSERT_TRUE(vd == vdJ);
		ASSERT_TRUE(num_vertices(g) == 0);
	}

	// boost graph

    TEST (graph, boost_test_target) {
        boost_vertex_descriptor vd = target(boost_edAB, b1);
        ASSERT_TRUE(vd == boost_vdB);
	}

    TEST (graph, boost_test_target_2) {
        boost_vertex_descriptor vd = target(boost_edIJ, b1);
        ASSERT_TRUE(vd == boost_vdJ);
	}

    TEST (graph, boost_test_target_3) {
		boost_graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
		boost_vertex_descriptor vd = target(boost_edIJ, g);
        ASSERT_TRUE(vd == boost_vdJ);
		ASSERT_TRUE(num_vertices(g) == 0);
	}

    // -----------
    // test_vertex
    // -----------

	// my graph

    TEST (graph, test_vertex) {
        vertex_descriptor vd = vertex(0, g1);
        ASSERT_TRUE(vd == vdA);
	}

    TEST (graph, test_vertex_2) {
        vertex_descriptor vd = vertex(2, g2);
        ASSERT_TRUE(vd == vdC);
	}

    TEST (graph, test_vertex_3) {
		graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
        vertex_descriptor vd = vertex(1, g);
		ASSERT_TRUE(num_vertices(g) == 0);
        ASSERT_TRUE(vd == 1);
	}

	// boost graph

    TEST (graph, boost_test_vertex) {
        boost_vertex_descriptor vd = vertex(0, b1);
        ASSERT_TRUE(vd == boost_vdA);
	}

    TEST (graph, boost_test_vertex_2) {
        boost_vertex_descriptor vd = vertex(2, b2);
        ASSERT_TRUE(vd == boost_vdC);
	}

    TEST (graph, boost_test_vertex_3) {
		boost_graph_type g;
		ASSERT_TRUE(num_vertices(g) == 0);
        boost_vertex_descriptor vd = vertex(1, g);
		ASSERT_TRUE(num_vertices(g) == 0);
        ASSERT_TRUE(vd == 1);
	}

    // -------------
    // test_vertices
    // -------------

    TEST (graph, test_vertices) {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g1);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == vdA);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == vdB);}
	}

    TEST (graph, test_vertices_2) {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g2);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ASSERT_TRUE(b != e);
		int c = 0;
		while (b != e) {
			++b;
			++c;
		}
		ASSERT_TRUE(c == 8);
	}

    TEST (graph, test_vertices_3) {
		graph_type g;
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ASSERT_TRUE(b == e);
	}

	// boost graph

    TEST (graph, boost_test_vertices) {
        std::pair<boost_vertex_iterator, boost_vertex_iterator> p = vertices(b1);
        boost_vertex_iterator                             b = p.first;
        boost_vertex_iterator                             e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            boost_vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == boost_vdA);}
        ++b;
        if (b != e) {
            boost_vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == boost_vdB);}
	}

    TEST (graph, boost_test_vertices_2) {
        std::pair<boost_vertex_iterator, boost_vertex_iterator> p = vertices(b2);
        boost_vertex_iterator                             b = p.first;
        boost_vertex_iterator                             e = p.second;
        ASSERT_TRUE(b != e);
		int c = 0;
		while (b != e) {
			++b;
			++c;
		}
		ASSERT_TRUE(c == 8);
	}

    TEST (graph, boost_test_vertices_3) {
		boost_graph_type g;
        std::pair<boost_vertex_iterator, boost_vertex_iterator> p = vertices(g);
        boost_vertex_iterator                             b = p.first;
        boost_vertex_iterator                             e = p.second;
        ASSERT_TRUE(b == e);
	}

    // --------------
    // test_has_cycle
    // --------------

	// boost graph

    TEST (graph, boost_test_has_cycle) {
        ASSERT_TRUE(has_cycle(b1));
	}
    
	TEST (graph, boost_test_has_cycle_2) {
        ASSERT_TRUE((has_cycle(b2)));
	}
	
	TEST (graph, boost_test_has_cycle_3) {
		boost_graph_type g;
        ASSERT_TRUE((has_cycle(g)));
	}

    // ---------------------
    // test_topological_sort
    // ---------------------
	
	// my graph

    TEST (graph, test_topological_sort) {
		graph_type g;
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_edge(0, 1, g);
		add_edge(0, 3, g);
		add_edge(1, 2, g);
		add_edge(1, 4, g);
		add_edge(2, 4, g);
		add_edge(2, 3, g);
		add_edge(3, 4, g);
        std::ostringstream out;
        topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_TRUE(out.str() == "4 3 2 1 0 ");
	}

    TEST (graph, test_topological_sort_2) {
        std::ostringstream out;
        topological_sort(g2, std::ostream_iterator<boost_vertex_descriptor>(out, " "));
        ASSERT_TRUE(out.str() == "7 4 6 2 3 1 0 5 ");
	}
	

	// boost graph

    TEST (graph, boost_test_topological_sort) {
        std::ostringstream out;
        topological_sort(b2, std::ostream_iterator<boost_vertex_descriptor>(out, " "));
        ASSERT_TRUE(out.str() == "7 6 3 1 4 0 2 5 ");
	}
	
    TEST (graph, boost_test_topological_sort_2) {
        std::ostringstream out;
		try {
			topological_sort(b1, std::ostream_iterator<boost_vertex_descriptor>(out, " "));
			ASSERT_TRUE(false);
		}
		catch(...) {
			ASSERT_TRUE(true);
		}
	}
	

	// --------------
	// Iterator tests
	// --------------

	// ------------------------
	// test_const_edge_iterator
	// ------------------------

	TEST (iterator, iterator_constructor_1) {
		Graph::const_edge_iterator ei (&g1, 0, 0);
		ASSERT_TRUE(*ei == edAB);
	}
	
	TEST (iterator, iterator_constructor_2) {
		Graph::const_edge_iterator ei (&g1, 0, 1);
		ASSERT_TRUE(*ei == edAC);
	}

	TEST (iterator, iterator_constructor_3) {
		Graph::const_edge_iterator ei (&g1, 3, 1);
		ASSERT_TRUE(*ei == edDF);
	}
	
	// ----------------
	// test operator ==
	// ----------------

	TEST (iterator, iterator_equals_1) {
		Graph::const_edge_iterator ei (&g1, 0, 0);
		Graph::const_edge_iterator ei2(&g1, 0, 0);
		ASSERT_TRUE(ei == ei2);
	}

	TEST (iterator, iterator_equals_2) {
		Graph::const_edge_iterator ei (&g1, 2, 0);
		Graph::const_edge_iterator ei2(&g1, 2, 0);
		ASSERT_TRUE(ei == ei2);
	}

	TEST (iterator, iterator_equals_3) {
		Graph::const_edge_iterator ei (&g1, 0, 2);
		Graph::const_edge_iterator ei2(&g1, 0, 2);
		ASSERT_TRUE(ei == ei2);
	}

	// ----------------
	// test operator !=
	// ----------------

	TEST (iterator, iterator_not_equals_1) {
		Graph::const_edge_iterator ei (&g1, 1, 0);
		Graph::const_edge_iterator ei2(&g1, 0, 0);
		ASSERT_TRUE(ei != ei2);
	}

	TEST (iterator, iterator_not_equals_2) {
		Graph::const_edge_iterator ei (&g1, 2, 0);
		Graph::const_edge_iterator ei2(&g1, 0, 2);
		ASSERT_TRUE(ei != ei2);
	}

	TEST (iterator, iterator_not_equals_3) {
		Graph::const_edge_iterator ei (&g1, 0, 2);
		Graph::const_edge_iterator ei2(&g2, 0, 2);
		ASSERT_TRUE(ei != ei2);
	}

	// ---------------
	// test operator *
	// ---------------

	TEST (iterator, iterator_reference_1) {
		Graph::const_edge_iterator ei (&g1, 0, 0);
		edge_descriptor e = *ei;
		ASSERT_TRUE(e == edAB);
	}

	TEST (iterator, iterator_reference_2) {
		Graph::const_edge_iterator ei (&g1, 2, 0);
		edge_descriptor e = *ei;
		ASSERT_TRUE(e == edCD);
	}
	TEST (iterator, iterator_reference_3) {
		Graph::const_edge_iterator ei (&g1, 5, 1);
		edge_descriptor e = *ei;
		ASSERT_TRUE(e == edFH);
	}

	// ----------------
	// test operator ++
	// ----------------

	TEST (iterator, iterator_increment_1) {
		Graph::const_edge_iterator ei (&g1, 0, 0);
		ASSERT_TRUE(*ei == edAB);
		++ei;
		ASSERT_TRUE(*ei == edAC);
		++ei;
		ASSERT_TRUE(*ei == edAE);
	}

	TEST (iterator, iterator_increment_2) {
		Graph::const_edge_iterator ei (&g1, 1, 0);
		ASSERT_TRUE(*ei == edBD);
		++ei;
		ASSERT_TRUE(*ei == edBE);
	}

	TEST (iterator, iterator_increment_3) {
		Graph::const_edge_iterator ei (&g1, 0, 0);
		ASSERT_TRUE(*ei == edAB);
		++ei;
		ASSERT_TRUE(*ei == edAC);
		++ei;
		ASSERT_TRUE(*ei == edAE);
		++ei;
		ASSERT_TRUE(*ei == edBD);
		++ei;
		ASSERT_TRUE(*ei == edBE);
		++ei;
		ASSERT_TRUE(*ei == edCD);
	}

	TEST (iterator, iterator_increment_4) {
		Graph::const_edge_iterator ei (&g1, 0, 0);
		ASSERT_TRUE(*ei == edAB);
		++ei;
		ASSERT_TRUE(*ei == edAC);
		++ei;
		ASSERT_TRUE(*ei == edAE);
		++ei;
		ASSERT_TRUE(*ei == edBD);
		++ei;
		ASSERT_TRUE(*ei == edBE);
		++ei;
		ASSERT_TRUE(*ei == edCD);
		++ei;
		ASSERT_TRUE(*ei == edDE);
		++ei;
		ASSERT_TRUE(*ei == edDF);
		++ei;
		ASSERT_TRUE(*ei == edFD);
	}

	TEST (iterator, iterator_increment_5) {
		graph_type g;
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_edge(0, 1, g);
		add_edge(0, 2, g);
		add_edge(0, 4, g);
		add_edge(1, 2, g);
		Graph::const_edge_iterator b (&g1, 0, 0);
		Graph::const_edge_iterator e (&g1, num_vertices(g)-1, 0);
		int c = 0;
		while (b != e) {
			++b;
			++c;
		}
		ASSERT_TRUE(c == 8);
	}

	// ----------------
	// test operator --
	// ----------------

	TEST (iterator, iterator_decrement_1) {
		Graph::const_edge_iterator ei (&g1, 0, 2);
		ASSERT_TRUE(*ei == edAE);
		--ei;
		ASSERT_TRUE(*ei == edAC);
		--ei;
		ASSERT_TRUE(*ei == edAB);
	}

	TEST (iterator, iterator_decrement_2) {
		Graph::const_edge_iterator ei (&g1, 1, 1);
		ASSERT_TRUE(*ei == edBE);
		--ei;
		ASSERT_TRUE(*ei == edBD);
	}

	TEST (iterator, iterator_decrement_3) {
		Graph::const_edge_iterator ei (&g1, 2, 0);
		ASSERT_TRUE(*ei == edCD);
		--ei;
		ASSERT_TRUE(*ei == edBE);
		--ei;
		ASSERT_TRUE(*ei == edBD);
		--ei;
		ASSERT_TRUE(*ei == edAE);
		--ei;
		ASSERT_TRUE(*ei == edAC);
		--ei;
		ASSERT_TRUE(*ei == edAB);
	}

	TEST (iterator, iterator_decrement_4) {
		Graph::const_edge_iterator ei (&g1, 5, 0);
		ASSERT_TRUE(*ei == edFD);
		--ei;
		ASSERT_TRUE(*ei == edDF);
		--ei;
		ASSERT_TRUE(*ei == edDE);
		--ei;
		ASSERT_TRUE(*ei == edCD);
		--ei;
		ASSERT_TRUE(*ei == edBE);
		--ei;
		ASSERT_TRUE(*ei == edBD);
		--ei;
		ASSERT_TRUE(*ei == edAE);
		--ei;
		ASSERT_TRUE(*ei == edAC);
		--ei;
		ASSERT_TRUE(*ei == edAB);
	}

	TEST (iterator, iterator_decrement_5) {
		graph_type g;
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_edge(5, 1, g);
		add_edge(5, 2, g);
		add_edge(5, 4, g);
		add_edge(4, 2, g);
		Graph::const_edge_iterator b (&g1, 0, 0);
		Graph::const_edge_iterator e (&g1, num_vertices(g)-1, 0);
		int c = 0;
		while (b != e) {
			--e;
			++c;
		}
		ASSERT_TRUE(c == 8);
	}
