/* UT EID : davismc2 */

/******************************************************************************
 * Program: Project 5 - Graph
 * Student: Merrill Davis
 * CS Server ID: davismc
 * Class: CS 378
 * Summer 2013
 *
 * An adjacency list implementation of a graph.  Mimics the Boost Graph Library
 * implementation. 
 *****************************************************************************/

// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <set>		// set

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;
//using namespace boost;

// ---------
// TestGraph
// ---------

// Tests functions only available in Graph
class GraphOnly : public testing::Test {

	public:
    // --------
    // typedefs
    // --------

    typedef Graph								    graph_type;

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


    // -----
    // setUp_Graph01()
    // -----

    virtual void setUp_Graph01 () {
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

	virtual void setUp_Graph02() {
		for (int i = 0; i <= 21; ++i)
			add_vertex(g);
		std::vector<vector<int> > dep;
		dep.push_back(vector<int>({16, 18, 14, 7, 10, 6, 9, 17, 13}));
		dep.push_back(vector<int>({14, 17}));
		dep.push_back(vector<int>({20, 7, 18, 6, 17}));
		add_edge_list(dep);
	}

	virtual void setUp_Graph03() {
		for (int i = 0; i <= 21; ++i)
			add_vertex(g);
		std::vector<vector<int> > dep;
		dep.push_back(vector<int>({3, 19, 7, 9, 4, 1, 5}));
		dep.push_back(vector<int>({7, 15}));
		dep.push_back(vector<int>({4, 5, 7, 15, 12, 19}));
		dep.push_back(vector<int>({10, 12, 8, 15}));
		add_edge_list(dep);
	}

    virtual void setUp_Graph04 () {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);

        add_edge(vdC, vdB, g).first;
        add_edge(vdB, vdA, g).first;
        add_edge(vdC, vdD, g).first;
        add_edge(vdA, vdD, g).first;}

    virtual void setUp_Graph05 () {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);
		vdE	 = add_vertex(g);
		vdF  = add_vertex(g);

        add_edge(vdA, vdB, g).first;
        add_edge(vdC, vdE, g).first;
        add_edge(vdC, vdF, g).first;
        add_edge(vdA, vdD, g).first;
        add_edge(vdA, vdD, g).first;
        add_edge(vdB, vdE, g).first;
        add_edge(vdE, vdD, g).first;}

	virtual void setUp_Graph06() {
		for (int i = 0; i <= 83; ++i)
			add_vertex(g);
		std::vector<vector<int> > dep;
		dep.push_back(vector<int>({10, 58, 9, 33, 41}));
		dep.push_back(vector<int>({63, 83, 68, 40, 21}));
		dep.push_back(vector<int>({21, 13, 83, 44, 19, 68, 52, 72, 40, 9, 29}));
		dep.push_back(vector<int>({64, 9 , 44, 52, 26, 37, 11, 41, 19, 67, 27}));
		dep.push_back(vector<int>({3, 12, 40, 19, 29, 32, 7, 86, 83, 53, 41, 9, 50, 13}));
		dep.push_back(vector<int>({19, 4, 44, 40, 68, 29}));
		dep.push_back(vector<int>({1, 11, 85, 41, 52, 50, 29, 7, 3, 68, 19, 23, 63}));
		dep.push_back(vector<int>({83, 6, 68, 13, 44, 29, 40, 19}));
		dep.push_back(vector<int>({36, 6, 13, 2, 68, 44, 7, 21}));
		dep.push_back(vector<int>({20, 10, 2, 81, 87, 21, 58, 7, 29, 46, 9, 23}));
		dep.push_back(vector<int>({49, 10, 1, 53, 30, 48, 32, 81, 41, 38, 27, 21}));
		add_edge_list(dep);
	}

	// has a cycle
    virtual void setUp_Graph07 () {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);

        add_edge(vdA, vdB, g).first;
        add_edge(vdB, vdA, g).first;}

	virtual void add_edge_list(std::vector<vector<int> > x){
		for (unsigned i = 0; i < x.size(); ++i)
			for (unsigned j = 1; j < x[i].size(); ++j)
				add_edge(x[i][0], x[i][j], g);
	}

};

    // --------------
    // test_has_cycle
    // --------------

   	TEST_F(GraphOnly, test_has_cycle_01) {
		setUp_Graph01();
        ASSERT_TRUE(has_cycle(g));}

    TEST_F(GraphOnly, test_has_cycle_02) {
		setUp_Graph02();
        ASSERT_FALSE(has_cycle(g));}

    TEST_F(GraphOnly, test_has_cycle_03) {
		setUp_Graph03();
        ASSERT_FALSE(has_cycle(g));}

    TEST_F(GraphOnly, test_has_cycle_04) {
		setUp_Graph04();
        ASSERT_FALSE(has_cycle(g));}

    TEST_F(GraphOnly, test_has_cycle_05) {
		setUp_Graph06();
        ASSERT_FALSE(has_cycle(g));}

    TEST_F(GraphOnly, test_has_cycle_06) {
		setUp_Graph07();  // has a cycle
        ASSERT_TRUE(has_cycle(g));}


// Test the common interface functions with both boost::adjacency_list and Graph
typedef testing::Types<boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>, Graph > MyTypes;

template <typename T>
class InterfaceTests : public testing::Test {

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

    // -----
    // setUp_Graph01()
    // -----

    virtual void setUp_Graph01 () {
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

	virtual void setUp_Graph02() {
		for (int i = 0; i <= 21; ++i)
			add_vertex(g);
		std::vector<vector<int> > dep;
		dep.push_back(vector<int>({16, 18, 14, 7, 10, 6, 9, 17, 13}));
		dep.push_back(vector<int>({14, 17}));
		dep.push_back(vector<int>({20, 7, 18, 6, 17}));
		add_edge_list(dep);
	}

	virtual void setUp_Graph03() {
		for (int i = 0; i <= 21; ++i)
			add_vertex(g);
		std::vector<vector<int> > dep;
		dep.push_back(vector<int>({3, 19, 7, 9, 4, 1, 5}));
		dep.push_back(vector<int>({7, 15}));
		dep.push_back(vector<int>({4, 5, 7, 15, 12, 19}));
		dep.push_back(vector<int>({10, 12, 8, 15}));
		add_edge_list(dep);
	}

    virtual void setUp_Graph04 () {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);

        add_edge(vdC, vdB, g).first;
        add_edge(vdB, vdA, g).first;
        add_edge(vdC, vdD, g).first;
        add_edge(vdA, vdD, g).first;}

    virtual void setUp_Graph05 () {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);
		vdE	 = add_vertex(g);
		vdF  = add_vertex(g);

        add_edge(vdA, vdB, g).first;
        add_edge(vdC, vdE, g).first;
        add_edge(vdC, vdF, g).first;
        add_edge(vdA, vdD, g).first;
        add_edge(vdA, vdD, g).first;
        add_edge(vdB, vdE, g).first;
        add_edge(vdE, vdD, g).first;}

	virtual void setUp_Graph06() {
		for (int i = 0; i <= 83; ++i)
			add_vertex(g);
		std::vector<vector<int> > dep;
		dep.push_back(vector<int>({10, 58, 9, 33, 41}));
		dep.push_back(vector<int>({63, 83, 68, 40, 21}));
		dep.push_back(vector<int>({21, 13, 83, 44, 19, 68, 52, 72, 40, 9, 29}));
		dep.push_back(vector<int>({64, 9 , 44, 52, 26, 37, 11, 41, 19, 67, 27}));
		dep.push_back(vector<int>({3, 12, 40, 19, 29, 32, 7, 86, 83, 53, 41, 9, 50, 13}));
		dep.push_back(vector<int>({19, 4, 44, 40, 68, 29}));
		dep.push_back(vector<int>({1, 11, 85, 41, 52, 50, 29, 7, 3, 68, 19, 23, 63}));
		dep.push_back(vector<int>({83, 6, 68, 13, 44, 29, 40, 19}));
		dep.push_back(vector<int>({36, 6, 13, 2, 68, 44, 7, 21}));
		dep.push_back(vector<int>({20, 10, 2, 81, 87, 21, 58, 7, 29, 46, 9, 23}));
		dep.push_back(vector<int>({49, 10, 1, 53, 30, 48, 32, 81, 41, 38, 27, 21}));
		add_edge_list(dep);
	}

	// has a cycle
    virtual void setUp_Graph07 () {
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);

        add_edge(vdA, vdB, g).first;
        add_edge(vdB, vdA, g).first;}

	virtual void add_edge_list(std::vector<vector<int> > x){
		for (unsigned i = 0; i < x.size(); ++i)
			for (unsigned j = 1; j < x[i].size(); ++j)
				add_edge(x[i][0], x[i][j], g);
	}

};

	TYPED_TEST_CASE(InterfaceTests, MyTypes);

    // -------------
    // test_add_edge
    // -------------

    TYPED_TEST(InterfaceTests, test_add_edge_01) {
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph01();
        std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
        ASSERT_TRUE(p.first  == this->edAB);
        ASSERT_TRUE(p.second == false);}

	// Adding an edge with an integer vertex descriptor should cause the number
	// of vertices to grow
    TYPED_TEST(InterfaceTests, test_add_edge_02) {
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph01();
        std::pair<edge_descriptor, bool> p = add_edge(this->vdA, 9, this->g);
        //std::cout << "edge num is " << p.first << std::endl;
        ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(this->g) == 10);}

    TYPED_TEST(InterfaceTests, test_add_edge_03) {
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph01();
        std::pair<edge_descriptor, bool> p = add_edge(this->vdA, 8, this->g);
        //std::cout << "edge num is " << p.first << std::endl;
        ASSERT_TRUE(p.second == true);
		ASSERT_TRUE(num_vertices(this->g) == 9);}

	// Adding an edge should cause the adjacent vertices list to grow by 1
    TYPED_TEST(InterfaceTests, test_add_edge_04) {
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		typedef typename TestFixture::adjacency_iterator adjacency_iterator;
		this->setUp_Graph01();
        std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
        ASSERT_TRUE(p.second == true);
		std::pair<adjacency_iterator, adjacency_iterator> x = adjacent_vertices(this->vdA, this->g);
        adjacency_iterator b = x.first;
        adjacency_iterator e = x.second;
		ASSERT_TRUE(std::distance(b, e) == 4);
		}


    // ----------------------
    // test_adjacent_vertices
    // ----------------------

    TYPED_TEST(InterfaceTests, test_adjacent_vertices_01) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		typedef typename TestFixture::adjacency_iterator adjacency_iterator;
		this->setUp_Graph01();
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdB);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdC);}}

    TYPED_TEST(InterfaceTests, test_adjacent_vertices_02) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		typedef typename TestFixture::adjacency_iterator adjacency_iterator;
		this->setUp_Graph02();
		std::set<int> x({7, 18, 6, 17});  // Adjacent to vertex 20 in this graph
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(20, this->g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        ASSERT_TRUE(b != e);
		ASSERT_EQ(std::distance(b, e), 4);
		while (b != e){
			vertex_descriptor vd = *b;
			ASSERT_TRUE(x.find(vd) != x.end());
			++b;}}

	// Test an empty vertex
    TYPED_TEST(InterfaceTests, test_adjacent_vertices_03) {
		typedef typename TestFixture::adjacency_iterator adjacency_iterator;
		this->setUp_Graph02();
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(19, this->g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        ASSERT_TRUE(b == e);}

    // ---------
    // test_edge
    // ---------

    TYPED_TEST(InterfaceTests, test_edge_01) {
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph01();
        std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
        ASSERT_TRUE(p.first  == this->edAB);
        ASSERT_TRUE(p.second == true);}

	// No edge should exist
    TYPED_TEST(InterfaceTests, test_edge_02) {
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph01();
        std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdG, this->g);
        ASSERT_TRUE(p.second == false);}

    TYPED_TEST(InterfaceTests, test_edge_03) {
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph02();
		std::set<int> x({7, 18, 6, 17});  // Adjacent to vertex 20 in this graph
        std::pair<edge_descriptor, bool> p = edge(20, 7, this->g);
		for (const auto& elem : x){
			p = edge(20, elem, this->g);
        	ASSERT_TRUE(source(p.first, this->g) == 20);
        	ASSERT_TRUE(p.second == true);}}

    // ----------
    // test_edges
    // ----------

    TYPED_TEST(InterfaceTests, test_edges_01) {
		typedef typename TestFixture::edge_iterator edge_iterator;
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph01();
        std::pair<edge_iterator, edge_iterator> p = edges(this->g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            ASSERT_TRUE(ed == this->edAB);}
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            ASSERT_TRUE(ed == this->edAC);}}

	// Should be 11 edges
	   TYPED_TEST(InterfaceTests, test_edges_02) {
		typedef typename TestFixture::edge_iterator edge_iterator;
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph01();
        std::pair<edge_iterator, edge_iterator> p = edges(this->g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        ASSERT_TRUE(b != e);
		ASSERT_TRUE(std::distance(b, e) == 11);}

	// Empty graph should have 0 edges
	   TYPED_TEST(InterfaceTests, test_edges_03) {
		typedef typename TestFixture::edge_iterator edge_iterator;
		typedef typename TestFixture::edge_descriptor edge_descriptor;
        std::pair<edge_iterator, edge_iterator> p = edges(this->g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        ASSERT_TRUE(b == e);
		ASSERT_TRUE(std::distance(b, e) == 0);}


//	   TYPED_TEST(InterfaceTests, test_edges_04) {
//		setUp_Graph02();
//        std::pair<edge_iterator, edge_iterator> p = edges(g);
//        edge_iterator                           b = p.first;
//        edge_iterator                           e = p.second;
//        ASSERT_TRUE(b != e);
//		for_each(b, e, [] (edge_descriptor x){ std::cout << x << std::endl; });}


    // --------------
    // test_num_edges
    // --------------

    TYPED_TEST(InterfaceTests, test_num_edges_01) {
    	typedef typename TestFixture::edges_size_type    edges_size_type;
		this->setUp_Graph01();
        edges_size_type es = num_edges(this->g);
        ASSERT_TRUE(es == 11);}

    TYPED_TEST(InterfaceTests, test_num_edges_02) {
    	typedef typename TestFixture::edges_size_type    edges_size_type;
		this->setUp_Graph02();
        edges_size_type es = num_edges(this->g);
        ASSERT_TRUE(es == 13);}

    TYPED_TEST(InterfaceTests, test_num_edges_03) {
    	typedef typename TestFixture::edges_size_type    edges_size_type;
		this->setUp_Graph03();
        edges_size_type es = num_edges(this->g);
        ASSERT_TRUE(es == 15);}

	// Empty graph should have 0
    TYPED_TEST(InterfaceTests, test_num_edges_04) {
    	typedef typename TestFixture::edges_size_type    edges_size_type;
        edges_size_type es = num_edges(this->g);
        ASSERT_TRUE(es == 0);}


    // -----------------
    // test_num_vertices
    // -----------------

    TYPED_TEST(InterfaceTests, test_num_vertices_01) {
    	typedef typename TestFixture::vertices_size_type    vertices_size_type;
		this->setUp_Graph01();
        vertices_size_type vs = num_vertices(this->g);
        ASSERT_TRUE(vs == 8);}

	// empty graph should return 0
    TYPED_TEST(InterfaceTests, test_num_vertices_02) {
    	typedef typename TestFixture::vertices_size_type    vertices_size_type;
        vertices_size_type vs = num_vertices(this->g);
        ASSERT_TRUE(vs == 0);}

    TYPED_TEST(InterfaceTests, test_num_vertices_03) {
    	typedef typename TestFixture::vertices_size_type    vertices_size_type;
		this->setUp_Graph02();
        vertices_size_type vs = num_vertices(this->g);
		// Has 22 vertices, including 0
        ASSERT_TRUE(vs == 22);}

	// adding an edge with a higher vertex descriptor number than
	// highest current vertex should cause the graph to grow to that
	// number of vertices + 1
    TYPED_TEST(InterfaceTests, test_num_vertices_04) {
    	typedef typename TestFixture::vertices_size_type    vertices_size_type;
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		vertex_descriptor vdA = add_vertex(this->g);
		add_edge(vdA, 40, this->g);
        vertices_size_type vs = num_vertices(this->g);
        ASSERT_TRUE(vs == 41);}


    // -----------
    // test_source
    // -----------

    TYPED_TEST(InterfaceTests, test_source_01) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph01();
        vertex_descriptor vd = source(this->edAB, this->g);
        ASSERT_TRUE(vd == this->vdA);}

    TYPED_TEST(InterfaceTests, test_source_02) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph02();
		edge_descriptor e1 = edge(7, 16, this->g).first;
        vertex_descriptor vd = source(e1, this->g);
        ASSERT_TRUE(vd == 7);}

    TYPED_TEST(InterfaceTests, test_source_03) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph02();
		edge_descriptor e1 = edge(6, 20, this->g).first;
        vertex_descriptor vd = source(e1, this->g);
        ASSERT_TRUE(vd == 6);}

    // -----------
    // test_target
    // -----------

    TYPED_TEST(InterfaceTests, test_target_1) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph01();
        vertex_descriptor vd = target(this->edAB, this->g);
        ASSERT_TRUE(vd == this->vdB);}

    TYPED_TEST(InterfaceTests, test_target_02) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph02();
		edge_descriptor e1 = edge(7, 16, this->g).first;
        vertex_descriptor vd = target(e1, this->g);
        ASSERT_TRUE(vd == 16);}

    TYPED_TEST(InterfaceTests, test_target_03) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		typedef typename TestFixture::edge_descriptor edge_descriptor;
		this->setUp_Graph02();
		edge_descriptor e1 = edge(6, 20, this->g).first;
        vertex_descriptor vd = target(e1, this->g);
        ASSERT_TRUE(vd == 20);}

    // -----------
    // test_vertex
    // -----------

    TYPED_TEST(InterfaceTests, test_vertex_01) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph01();
        vertex_descriptor vd = vertex(0, this->g);
        ASSERT_TRUE(vd == this->vdA);}

    TYPED_TEST(InterfaceTests, test_vertex_02) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph02();
        vertex_descriptor vd = vertex(10, this->g);
        ASSERT_TRUE(vd == 10);}

    TYPED_TEST(InterfaceTests, test_vertex_03) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph02();
        vertex_descriptor vd = vertex(5, this->g);
        ASSERT_TRUE(vd == 5);}

	// vertex shouldn't exist
    TYPED_TEST(InterfaceTests, test_vertex_04) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph02();
        vertex_descriptor vd = vertex(50, this->g);
		// boost adjacency_list returns 50.  Looks like it just gives you back your index,
		// whether it exists or not.
        ASSERT_TRUE(vd == 50);
		// boost adjacency_list still reports 22 vertices in graph, however
		ASSERT_TRUE(num_vertices(this->g) == 22);}

    // -------------
    // test_vertices
    // -------------

    TYPED_TEST(InterfaceTests, test_vertices_01) {
		typedef typename TestFixture::vertex_iterator vertex_iterator;
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph01();
        std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ASSERT_TRUE(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdA);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdB);}}

    TYPED_TEST(InterfaceTests, test_vertices_02) {
		typedef typename TestFixture::vertex_iterator vertex_iterator;
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph02();
        std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ASSERT_TRUE(b != e);
		ASSERT_TRUE(std::distance(b, e) == 22);
		unsigned i = 0;
		while (b != e){
			vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == i);
			++i;
			++b;}}

	// Empty graph
    TYPED_TEST(InterfaceTests, test_vertices_03) {
		typedef typename TestFixture::vertex_iterator vertex_iterator;
		// Not calling a setup routine, so we only have def constructed graph
        std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ASSERT_TRUE(b == e);}
     


    // ---------------------
    // test_topological_sort
    // ---------------------

    TYPED_TEST(InterfaceTests, test_topological_sort_01) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph01();
        std::ostringstream out;
		try {
        	topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
			ASSERT_TRUE(false); // should throw exception, graph has a cycle
		}
		catch (boost::not_a_dag& e) {
		    //std::cout << out.str() << std::endl;
        	ASSERT_TRUE(out.str() == "4 ");}}

	// result in project 2 was: 1 2 3 4 5 6 7 8 9 10 11 12 13 15 17 14 18 16 19 20 21
	TYPED_TEST(InterfaceTests, test_topological_sort_02){
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph02();
        std::ostringstream out;
		try {
        	topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
		}
		catch (boost::not_a_dag& e) {
		    }
		//std::cout << out.str() << std::endl;
        ASSERT_TRUE(out.str() == "0 1 2 3 4 5 6 7 8 9 10 11 12 13 17 14 15 18 16 19 20 21 ");}

	// result in project 2 was: 1 2 5 6 8 9 11 12 13 14 15 7 10 16 17 18 19 4 3 20 21
	TYPED_TEST(InterfaceTests, test_topological_sort_03) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph03();
        std::ostringstream out;
		try {
        	topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
		}
		catch (boost::not_a_dag& e) {
		ASSERT_TRUE(false);}
		//std::cout << out.str() << std::endl;
        ASSERT_TRUE(out.str() == "0 1 2 5 15 7 12 19 4 9 3 6 8 10 11 13 14 16 17 18 20 21 ");}

	TYPED_TEST(InterfaceTests, test_topological_sort_04) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph04();
        std::ostringstream out;
		try {
        	topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
		}
		catch (boost::not_a_dag& e) {
		ASSERT_TRUE(false);}
		//std::cout << out.str() << std::endl;
        ASSERT_TRUE(out.str() == "3 0 1 2 ");}

	TYPED_TEST(InterfaceTests, test_topological_sort_05) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph05();
        std::ostringstream out;
		try {
        	topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
		}
		catch (boost::not_a_dag& e) {
		ASSERT_TRUE(false);}
		//std::cout << out.str() << std::endl;
        ASSERT_TRUE(out.str() == "3 4 1 0 5 2 ");}

	TYPED_TEST(InterfaceTests, test_topological_sort_06) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph06();
        std::ostringstream out;
		try {
        	topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
		}
		catch (boost::not_a_dag& e) {
		ASSERT_TRUE(false);}
		//std::cout << out.str() << std::endl;
        ASSERT_TRUE(out.str() == "0 7 9 12 13 4 29 40 44 68 19 32 41 50 53 6 83 86 3 11 23 52 72 21 63 85 1 2 5 8 33 58 10 14 15 16 17 18 46 81 87 20 22 24 25 26 27 28 30 31 34 35 36 37 38 39 42 43 45 47 48 49 51 54 55 56 57 59 60 61 62 67 64 65 66 69 70 71 73 74 75 76 77 78 79 80 82 84 ");}

    TYPED_TEST(InterfaceTests, test_topological_sort_07) {
		typedef typename TestFixture::vertex_descriptor vertex_descriptor;
		this->setUp_Graph07();
        std::ostringstream out;
		try {
        	topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
			ASSERT_TRUE(false); // should throw exception, graph has a cycle
		}
		catch (boost::not_a_dag& e) {
		    //std::cout << out.str() << std::endl;
        	ASSERT_TRUE(true);}}


