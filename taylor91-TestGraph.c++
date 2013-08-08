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
#include "boost/graph/exception.hpp"

#include "Graph.h"

#include "gtest/gtest.h" // Googletest harness


// ----------------
// GoogleTest Suite
// ----------------



// --------
// typedefs
// --------

typedef Graph												graph_type;

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

vertex_descriptor vdI;
vertex_descriptor vdJ;
vertex_descriptor vdK;
edge_descriptor edBA;
edge_descriptor edBB;
edge_descriptor edAA;


// -----
// test_setUp
// -----

TEST(Graph, test_setup) {
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


// -------------
// test_add_edge
// -------------

TEST(Graph, test_add_edge1) {
	std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
	ASSERT_TRUE (p.first  == edAB);
	ASSERT_TRUE (p.second == false);
}

TEST(Graph, test_add_edge2) {
	std::pair<edge_descriptor, bool> p = add_edge(vdA, vdD, g);
	ASSERT_TRUE (p.second == true);
}

TEST(Graph, test_add_edge3) {
	std::pair<edge_descriptor, bool> p = add_edge(vdB, vdA, g);
	edBA = p.first;
	ASSERT_TRUE (p.second == true);
}

TEST(Graph, test_add_edge4) {
	std::pair<edge_descriptor, bool> p = add_edge(vdB, vdB, g);
	edBB = p.first;
	ASSERT_TRUE (p.second == true);
}

TEST(Graph, test_add_edge5) {
	std::pair<edge_descriptor, bool> p = add_edge(vdI, vdA, g);
	std::pair<edge_descriptor, bool> t = add_edge(vdA, vdA, g);
	edAA = p.first;
	ASSERT_TRUE (p.second == true);
	ASSERT_TRUE (t.second == false);
	ASSERT_TRUE (t.first == p.first);
}

TEST(Graph, test_add_edge6) {
	vdJ = 10;
	std::pair<edge_descriptor, bool> p = add_edge(vdJ, vdA, g);
	ASSERT_TRUE (p.second == true);
}

TEST(Graph, test_add_edge7) {
	vdK = 15;
	std::pair<edge_descriptor, bool> p = add_edge(vdC, vdK, g);
	ASSERT_TRUE (p.second == true);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TEST(Graph, test_adjacent_vertices1) {
	std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
	adjacency_iterator b = p.first;
	adjacency_iterator e = p.second;
	ASSERT_TRUE (b != e);
	if (b != e) {
		vertex_descriptor vd = *b;
		ASSERT_TRUE (vd == vdA);}
	++b;
	if (b != e) {
		vertex_descriptor vd = *b;
		ASSERT_TRUE (vd == vdB);}
	++b;
	if (b != e) {
		vertex_descriptor vd = *b;
		ASSERT_TRUE (vd == vdC);}
}

TEST(Graph, test_adjacent_vertices2) {
	std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdH, g);
	adjacency_iterator b = p.first;
	adjacency_iterator e = p.second;
	ASSERT_TRUE (b == e);
}

TEST(Graph, test_adjacent_vertices3) {
	adjacent_vertices(500, g);
	ASSERT_TRUE (num_vertices(g) == 16);
	ASSERT_TRUE (num_edges(g) == 17);
}


// ---------
// test_edge
// ---------

TEST(Graph, test_edge1) {
	std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
	ASSERT_TRUE (p.first  == edAB);
	ASSERT_TRUE (p.second == true);
}

TEST(Graph, test_edge2) {
	std::pair<edge_descriptor, bool> p = edge(vdB, vdA, g);
	ASSERT_TRUE (p.first  == edBA);
	ASSERT_TRUE (p.second == true);
}

TEST(Graph, test_edge3) {
	std::pair<edge_descriptor, bool> p = edge(vdD, vdA, g);
	ASSERT_TRUE (p.second == false);
}

// ----------
// test_edges
// ----------

TEST(Graph, test_edges1) {
	std::pair<edge_iterator, edge_iterator> p = edges(g);
	edge_iterator                           b = p.first;
	edge_iterator                           e = p.second;
	ASSERT_TRUE (b != e);
	if (b != e) {
		edge_descriptor ed = *b;
		ASSERT_TRUE (ed == edAA);}
	++b;
	if (b != e) {
		edge_descriptor ed = *b;
		ASSERT_TRUE (ed == edAB);}
}

TEST(Graph, test_edges2) {
	std::pair<edge_iterator, edge_iterator> p = edges(g);
	edge_iterator                           b = p.first;
	edge_iterator                           e = p.second;
	ASSERT_TRUE (b != e);
	unsigned int count = 0;
	while (b != e) {
		++count;
		++b;
	}

	ASSERT_TRUE (count == num_edges(g)); 
}


// --------------
// test_num_edges
// --------------

TEST(Graph, test_num_edges1) {
	edges_size_type es = num_edges(g);
	ASSERT_TRUE (es == 17);
}

TEST(Graph, test_num_edges2) {
	add_edge(vdA, vdB, g);
	edges_size_type es = num_edges(g);
	ASSERT_TRUE (es == 17);
}

TEST(Graph, test_num_edges3) {
	add_edge(vdC, vdJ, g);
	edges_size_type es = num_edges(g);
	ASSERT_TRUE (es == 18);
}

// -----------------
// test_num_vertices
// -----------------

TEST(Graph, test_num_vertices1) {
	vertices_size_type vs = num_vertices(g);
	ASSERT_TRUE (vs == 16);
}

TEST(Graph, test_num_vertices2) {
	add_vertex(g);
	vertices_size_type vs = num_vertices(g);
	ASSERT_TRUE (vs == 17);
}

TEST(Graph, test_num_vertices3) {
	graph_type g2;
	vertices_size_type vs = num_vertices(g2);
	ASSERT_TRUE (vs == 0);
}

// -----------
// test_source
// -----------

TEST(Graph, test_source1) {
	vertex_descriptor vd = source(edAB, g);
	ASSERT_TRUE (vd == vdA);
}

TEST(Graph, test_source2) {
	vertex_descriptor vd = source(edBA, g);
	ASSERT_TRUE (vd == vdB);  
}

TEST(Graph, test_source3) {
	vertex_descriptor vd = source(edBB, g);
	ASSERT_TRUE (vd == vdB);  
}

TEST(Graph, test_source4) {
	graph_type g2;
	vertex_descriptor vZ = 100;
	edge_descriptor edZZ = add_edge(vZ, vZ, g2).first;
	vertex_descriptor vd = source(edZZ, g);
	ASSERT_TRUE (vd == vZ);  
}

// -----------
// test_target
// -----------

TEST(Graph, test_target1) {
	vertex_descriptor vd = target(edAB, g);
	ASSERT_TRUE (vd == vdB);
}

TEST(Graph, test_target2) {
	vertex_descriptor vd = target(edBA, g);
	ASSERT_TRUE (vd == vdA);  
}

TEST(Graph, test_target3) {
	vertex_descriptor vd = target(edBB, g);
	ASSERT_TRUE (vd == vdB);  
}

TEST(Graph, test_target4) {
	graph_type g2;
	vertex_descriptor vZ = 100;
	edge_descriptor edZZ = add_edge(vZ, vZ, g2).first;
	vertex_descriptor vd = target(edZZ, g);
	ASSERT_TRUE (vd == vZ);  
}

// -----------
// test_vertex
// -----------

TEST(Graph, test_vertex1) {
	vertex_descriptor vd = vertex(0, g);
	ASSERT_TRUE (vd == vdA);
}

TEST(Graph, test_vertex2) {
	vertex_descriptor vd = vertex(13, g);
	ASSERT_TRUE (vd == 13);
}

TEST(Graph, test_vertex3) {
	vertex_descriptor vd = vertex(99, g);
	ASSERT_TRUE (vd == 99);
}


// -------------
// test_vertices
// -------------

TEST(Graph, test_vertices1) {
	std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
	vertex_iterator                             b = p.first;
	vertex_iterator                             e = p.second;
	ASSERT_TRUE (b != e);
	if (b != e) {
		vertex_descriptor vd = *b;
		ASSERT_TRUE (vd == vdA);}
	++b;
	if (b != e) {
		vertex_descriptor vd = *b;
		ASSERT_TRUE (vd == vdB);}
}

TEST(Graph, test_vertices2) {
	graph_type empty_g;
	std::pair<vertex_iterator, vertex_iterator> p = vertices(empty_g);
	vertex_iterator                             b = p.first;
	vertex_iterator                             e = p.second;
	ASSERT_TRUE (b == e);
}

TEST(Graph, test_vertices3) {
	std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
	vertex_iterator                             b = p.first;
	vertex_iterator                             e = p.second;
	ASSERT_TRUE (b != e);
	unsigned int counter = 0;
	while (b != e) {
		++counter;
		++b;
	}
	ASSERT_TRUE (counter == num_vertices(g));
}
// --------------
// test_has_cycle
// --------------

TEST(Graph, test_has_cycle1) {
	graph_type no_cycle;
	add_edge(0, 1, no_cycle);
	add_edge(1, 2, no_cycle);
	add_edge(2, 3, no_cycle);
	ASSERT_FALSE (has_cycle(no_cycle));
}

TEST(Graph, test_has_cycle2) {
	graph_type no_cycle;
	add_edge(0, 1, no_cycle);
	ASSERT_TRUE (num_edges(no_cycle) == 1);
	ASSERT_TRUE (num_vertices(no_cycle) == 2);
	ASSERT_FALSE (has_cycle(no_cycle));
}

TEST(Graph, test_has_cycle3) {
	graph_type self_cycle;
	add_edge(0, 0, self_cycle);
	ASSERT_TRUE (num_edges(self_cycle) == 1);
	ASSERT_TRUE (has_cycle(self_cycle));
}

TEST(Graph, test_has_cycle4) {
	graph_type cycle;
	add_edge(0, 1, cycle);
	add_edge(1, 2, cycle);
	add_edge(2, 3, cycle);
	add_edge(3, 0, cycle);
	ASSERT_TRUE (has_cycle(cycle));
}


// ---------------------
// test_topological_sort
// ---------------------

TEST(Graph, test_topological_sort1) {
	std::ostringstream out;
	graph_type topo_g;
	add_edge(0, 1, topo_g);
	add_edge(1, 2, topo_g);
	add_edge(2, 3, topo_g);
	topological_sort(topo_g, std::ostream_iterator<vertex_descriptor>(out, " "));
	ASSERT_TRUE (out.str() == "3 2 1 0 ");
}

TEST(Graph, test_topological_sort2) {
	std::ostringstream out;
	graph_type topo_g;
	add_edge(1, 2, topo_g);
	add_edge(2, 3, topo_g);
	topological_sort(topo_g, std::ostream_iterator<vertex_descriptor>(out, " "));
	ASSERT_TRUE (out.str() == "0 3 2 1 ");
}

TEST(Graph, test_topological_sort3) {
	std::ostringstream out;
	graph_type topo_g;
	add_edge(1, 3, topo_g);
	add_edge(1, 7, topo_g);
	add_edge(4, 5, topo_g);
	add_edge(5, 2, topo_g);
	add_edge(6, 4, topo_g);
	add_edge(6, 5, topo_g);
	topological_sort(topo_g, std::ostream_iterator<vertex_descriptor>(out, " "));
	ASSERT_TRUE (out.str() == "0 2 3 5 7 1 4 6 ");
}

TEST(Graph, test_topological_sort4) {
	std::ostringstream out;
	graph_type topo_g;
	add_edge(0, 1, topo_g);
	add_edge(1, 2, topo_g);
	add_edge(2, 3, topo_g);
	add_edge(3, 0, topo_g);
	try {
		topological_sort(topo_g, std::ostream_iterator<vertex_descriptor>(out, " "));
		ASSERT_FALSE (true);
	}

	catch (boost::not_a_dag& e) {
		ASSERT_TRUE (true);
	}
}



// --------------------
// Const Iterator Tests
// --------------------

// -------------------------------
// test_const_iterator_constructor
// -------------------------------
TEST (ConstIterator, Constructor1) {
	graph_type igraph;
	add_edge(0, 2, igraph).first;
	graph_type::const_iterator iter(&igraph, false);
	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 2);
}

TEST (ConstIterator, Constructor2) {
	graph_type igraph;
	add_edge(0, 5, igraph).first;
	add_edge(0, 1, igraph).first;
	graph_type::const_iterator iter(&igraph, false);
	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 1);
}

TEST (ConstIterator, Constructor3) {
	graph_type igraph;
	add_edge(0, 5, igraph).first;
	add_edge(0, 1, igraph).first;
	graph_type::const_iterator iter(&igraph, true);
	--iter;
	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 5);
}

// -------------------------------
// test_const_iterator_dereference
// -------------------------------
TEST (ConstIterator, Dereference1) {
	graph_type igraph;
	add_edge(0, 0, igraph).first;
	graph_type::const_iterator iter(&igraph, false);
	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 0);
}

TEST (ConstIterator, Dereference2) {
	graph_type igraph;
	add_edge(0, 5, igraph).first;
	add_edge(0, 1, igraph).first;
	graph_type::const_iterator iter(&igraph, false);
	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 1);
}

TEST (ConstIterator, Dereference3) {
	graph_type igraph;
	add_edge(0, 5, igraph).first;
	add_edge(0, 1, igraph).first;
	graph_type::const_iterator iter(&igraph, true);
	--iter;
	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 5);
}

// -------------------------
// test_const_iterator_equal
// -------------------------
TEST (ConstIterator, Equality1) {
	graph_type igraph;
	add_edge(0, 0, igraph);
	graph_type::const_iterator iter1(&igraph, false);
	graph_type::const_iterator iter2(&igraph, false);
	ASSERT_TRUE (iter1 == iter2);
}

TEST (ConstIterator, Equality2) {
	graph_type igraph1;
	graph_type igraph2;
	add_edge(0, 0, igraph1);
	add_edge(0, 0, igraph2);
	graph_type::const_iterator iter1(&igraph1, false);
	graph_type::const_iterator iter2(&igraph2, false);
	ASSERT_TRUE (iter1 != iter2);
}

TEST (ConstIterator, Equality3) {
	graph_type igraph;
	add_edge(0, 0, igraph);
	graph_type::const_iterator iter1(&igraph, false);
	graph_type::const_iterator iter2(&igraph, true);
	ASSERT_TRUE (iter1 != iter2);
}

// ----------------------
// test_const_iterator_++
// ----------------------
TEST (ConstIterator, Increment1) {
	graph_type igraph;
	add_edge(0, 0, igraph);
	add_edge(0, 1, igraph);
	add_edge(0, 2, igraph);
	add_edge(0, 3, igraph);
	add_edge(0, 4, igraph);
	graph_type::const_iterator iter(&igraph, false);
	for (int i = 0; i < 5; ++i)
	{
		ASSERT_TRUE ((*iter).first == 0);
		ASSERT_TRUE ((*iter).second == i);
		++iter;
	}
}

TEST (ConstIterator, Increment2) {
	graph_type igraph;
	add_edge(0, 1, igraph);
	add_edge(5, 1, igraph);
	add_edge(10, 1, igraph);
	add_edge(15, 1, igraph);
	graph_type::const_iterator iter(&igraph, false);
	for (int i = 0; i < 4; ++i)
	{
		ASSERT_TRUE ((*iter).first == i * 5);
		ASSERT_TRUE ((*iter).second == 1);
		++iter;
	}
}

TEST (ConstIterator, Increment3) {
	graph_type igraph;
	add_edge(0, 1, igraph);
	add_edge(0, 3, igraph);
	add_edge(1, 3, igraph);
	add_edge(2, 1, igraph);
	graph_type::const_iterator iter(&igraph, false);

	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 1);
	++iter;

	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 3);
	++iter;

	ASSERT_TRUE ((*iter).first == 1);
	ASSERT_TRUE ((*iter).second == 3);
	++iter;

	ASSERT_TRUE ((*iter).first == 2);
	ASSERT_TRUE ((*iter).second == 1);
	++iter;

}

TEST (ConstIterator, Increment4) {
	graph_type igraph;
	add_edge(0, 1, igraph);
	add_edge(5, 1, igraph);
	add_edge(10, 1, igraph);
	add_edge(15, 1, igraph);
	graph_type::const_iterator iter1(&igraph, false);
	graph_type::const_iterator iter2(&igraph, true);
	int temp = 0;
	while (iter1 != iter2)
	{
		++temp;
		++iter1;
	}
	ASSERT_TRUE (temp == 4);
}


// ----------------------
// test_const_iterator_--
// ----------------------
TEST (ConstIterator, Decrement1) {
	graph_type igraph;
	add_edge(0, 0, igraph);
	add_edge(0, 1, igraph);
	add_edge(0, 2, igraph);
	add_edge(0, 3, igraph);
	add_edge(0, 4, igraph);
	graph_type::const_iterator iter(&igraph, true);
	--iter;
	for (int i = 4; i >= 0; --i)
	{
		ASSERT_TRUE ((*iter).first == 0);
		ASSERT_TRUE ((*iter).second == i);
		--iter;
	}
}

TEST (ConstIterator, Decrement2) {
	graph_type igraph;
	add_edge(0, 1, igraph);
	add_edge(5, 1, igraph);
	add_edge(10, 1, igraph);
	add_edge(15, 1, igraph);
	graph_type::const_iterator iter(&igraph, true);
	--iter;
	for (int i = 3; i >= 0; --i)
	{
		ASSERT_TRUE ((*iter).first == i * 5);
		ASSERT_TRUE ((*iter).second == 1);
		--iter;
	}
}

TEST (ConstIterator, Decrement3) {
	graph_type igraph;
	add_edge(0, 1, igraph);
	add_edge(0, 3, igraph);
	add_edge(1, 3, igraph);
	add_edge(2, 1, igraph);
	graph_type::const_iterator iter(&igraph, true);
	--iter;

	ASSERT_TRUE ((*iter).first == 2);
	ASSERT_TRUE ((*iter).second == 1);
	--iter;

	ASSERT_TRUE ((*iter).first == 1);
	ASSERT_TRUE ((*iter).second == 3);
	--iter;

	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 3);
	--iter;

	ASSERT_TRUE ((*iter).first == 0);
	ASSERT_TRUE ((*iter).second == 1);
	--iter;
}
