// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
To test the program:
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % ls /public/linux/include/boost-1_44/boost/graph/
    ...
    adjacency_list.hpp
    ...
    % g++ -pedantic -std=c++0x -Wall TestGraph.c++ -o TestGraph -lgtest -lpthread -lgtest_main
    % valgrind ./TestGraph >& TestGraph.c++.out
*/

#define private public
#define protected public

// --------
// includes
// --------

#include <stddef.h>
#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include <boost/exception/all.hpp> // boost exception
#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort
#include "boost/graph/exception.hpp"
#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info; 
typedef testing::Types<boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>, Graph> testlist;

template <typename T>
class TestForGraph :  public testing::Test
{
public:
	// --------
	// typedefs
	// --------

	    typedef T	graph_type;

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

	    graph_type _g;
	    vertex_descriptor _vdA;
	    vertex_descriptor _vdB;
	    vertex_descriptor _vdC;
	    vertex_descriptor _vdD;
	    vertex_descriptor _vdE;
	    vertex_descriptor _vdF;
	    vertex_descriptor _vdG;
	    vertex_descriptor _vdH;

	    edge_descriptor _edAB;
	    edge_descriptor _edAC;
	    edge_descriptor _edAE;
	    edge_descriptor _edAD;
	    edge_descriptor _edBD;
	    edge_descriptor _edBE;
	    edge_descriptor _edCD;
	    edge_descriptor _edDE;
	    edge_descriptor _edDF;
	    edge_descriptor _edFD;
	    edge_descriptor _edFH;
	    edge_descriptor _edGH;

	    edge_descriptor _eA;
	    edge_descriptor _eB;
	    edge_descriptor _eC;
	    edge_descriptor _eD;
	    edge_descriptor _eE;
	    edge_descriptor _eF;
	    edge_descriptor _eG;
	    edge_descriptor _eH;
	    edge_descriptor _eI;
	    

	    // CycleTests():_g(graph_type()){}
	    
	    virtual void setupCyclic(){
		_vdA = add_vertex(_g);
		_vdB = add_vertex(_g);
		_vdC = add_vertex(_g);
		_vdD = add_vertex(_g);
		_vdE = add_vertex(_g);
		_vdF = add_vertex(_g);
		_vdG = add_vertex(_g);
		_vdH = add_vertex(_g);
		_edAB = add_edge(_vdA, _vdB, _g).first;
		_edAC = add_edge(_vdA, _vdC, _g).first;
		_edAE = add_edge(_vdA, _vdE, _g).first;
		_edBD = add_edge(_vdB, _vdD, _g).first;
		_edBE = add_edge(_vdB, _vdE, _g).first;
		_edCD = add_edge(_vdC, _vdD, _g).first;
		_edDE = add_edge(_vdD, _vdE, _g).first;
		_edDF = add_edge(_vdD, _vdF, _g).first;
		_edFD = add_edge(_vdF, _vdD, _g).first;
		_edFH = add_edge(_vdF, _vdH, _g).first;
		_edGH = add_edge(_vdG, _vdH, _g).first;}
	    
	    virtual void setupACyclic(){
		_vdA = add_vertex(_g);
		_vdB = add_vertex(_g);
		_vdC = add_vertex(_g);
		_vdD = add_vertex(_g);
		_vdE = add_vertex(_g);
		_vdF = add_vertex(_g);
		_vdG = add_vertex(_g);
		_vdH = add_vertex(_g);

		_edAB = add_edge(_vdA, _vdB, _g).first;
		_edAC = add_edge(_vdA, _vdC, _g).first;
		_edAE = add_edge(_vdA, _vdE, _g).first;
		_edBD = add_edge(_vdB, _vdD, _g).first;
		_edBE = add_edge(_vdB, _vdE, _g).first;
		_edCD = add_edge(_vdC, _vdD, _g).first;
		_edDE = add_edge(_vdD, _vdE, _g).first;
		// _edDF = add_edge(_vdD, _vdF, _g).first;
		_edFD = add_edge(_vdF, _vdD, _g).first;
		_edFH = add_edge(_vdF, _vdH, _g).first;
		_edGH = add_edge(_vdG, _vdH, _g).first;}

	    virtual void setupACyclic1(){
		_vdA = add_vertex(_g);
		_vdB = add_vertex(_g);
		_vdC = add_vertex(_g);
		_vdD = add_vertex(_g);
		_vdE = add_vertex(_g);
		_vdF = add_vertex(_g);
		_vdG = add_vertex(_g);
		_vdH = add_vertex(_g);}


};

template <typename T>
class TestGraphBasic :  public testing::Test
{
public:
	// --------
	// typedefs
	// --------

	typedef T	graph_type;

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


	edge_descriptor edAC;


	// -----
	// setUp
	// -----

	virtual void SetUp () 
	{
		vdA  = add_vertex(this->g);
		vdB  = add_vertex(this->g);
		vdC  = add_vertex(this->g);


		edAC = add_edge(vdA, vdC, this->g).first;

	}
};



TYPED_TEST_CASE(TestForGraph, testlist);
TYPED_TEST_CASE(TestGraphBasic, testlist);


// --------------
// test_vertex
// --------------
TYPED_TEST(TestForGraph, test_vertex) 
{
        Graph g;
        Graph::vertex_descriptor d = add_vertex(g);

        ASSERT_EQ(d, 0);

        ASSERT_EQ(num_vertices(g), 1);
        ASSERT_EQ(num_edges(g), 0);

        //ASSERT_EQ(adjacent_vertices(d,g), 0);
	//Graph::vertex_descriptor v = vertex(0, this->g);
	Graph::vertex_descriptor v = vertex(0, g);
	ASSERT_EQ(0, v);
}

TYPED_TEST(TestForGraph, test_vertex1) 
{
        Graph g;
        Graph::vertex_descriptor d = add_vertex(g);
	Graph::vertex_descriptor v = add_vertex(g);
        ASSERT_EQ(d, 0);
        ASSERT_EQ(v, 1);
        ASSERT_EQ(num_vertices(g), 2);
        ASSERT_EQ(num_edges(g), 0);
	ASSERT_EQ(vertex(1,g),1);
}

TYPED_TEST (TestForGraph, test_vertex2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setupACyclic();
    vertex_descriptor vd = vertex(1, this->_g);
    ASSERT_TRUE(vd == this->_vdB);
}

// -------------
// test_add_vertex
// -------------

TYPED_TEST(TestForGraph , test_add_vertex_1)
{
    this->setupACyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->_g);
    ASSERT_TRUE(v == 8);
}

TYPED_TEST(TestForGraph , test_add_vertex_2)
{
    this->setupACyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->_g);
    ASSERT_TRUE(v == 8);
}

TYPED_TEST(TestForGraph , test_add_vertex_3)
{
    this->setupCyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    vertex_descriptor v = add_vertex(this->_g);
    ASSERT_TRUE(v == 8);
}



// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(TestForGraph, test_adjacent_vertices_1)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this -> setupACyclic();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->_vdA, this->_g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->_vdB);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->_vdE);
}

TYPED_TEST(TestForGraph, test_adjacent_vertices_2)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this -> setupACyclic();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->_vdB, this->_g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->_vdD);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->_vdE);
}

TYPED_TEST(TestForGraph, test_adjacent_vertices_3)
{
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    
    this -> setupCyclic();
    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->_vdB, this->_g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->_vdD);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->_vdE);
}

// --------------
// test_add_edge
// --------------

TYPED_TEST(TestForGraph , test_add_edges_1)
{
    this->setupACyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->_vdA, this->_vdB, this->_g);
    ASSERT_TRUE(p.first == this->_edAB);
    ASSERT_FALSE(p.second);
}

TYPED_TEST(TestForGraph , test_add_edges_2)
{
    this->setupACyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->_vdA, this->_vdB, this->_g);
    ASSERT_TRUE(p.first == this->_edAB);
    ASSERT_FALSE(p.second);
    pair<edge_descriptor, bool> b = add_edge(this->_vdA, this->_vdC, this->_g);
    ASSERT_TRUE(b.first == this->_edAC);
    ASSERT_FALSE(b.second);
}

TYPED_TEST(TestForGraph , test_add_edges_3)
{
    this->setupACyclic();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = add_edge(this->_vdA, this->_vdB, this->_g);
    ASSERT_TRUE(p.first == this->_edAB);
    ASSERT_FALSE(p.second);
    pair<edge_descriptor, bool> b = add_edge(this->_vdA, this->_vdD, this->_g);
    ASSERT_TRUE(b.second);
}


// ---------
// test_edge
// ---------

TYPED_TEST(TestForGraph, test_edge_1)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this -> setupACyclic();
    pair<edge_descriptor, bool> p = edge(this->_vdA, this->_vdB, this->_g);
    ASSERT_TRUE(p.first == this->_edAB);
    ASSERT_TRUE(p.second );
}

TYPED_TEST(TestForGraph, test_edge_2)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this -> setupCyclic();
    pair<edge_descriptor, bool> p = edge(this->_vdB, this->_vdD, this->_g);
    ASSERT_TRUE(p.first == this->_edBD);
    ASSERT_TRUE(p.second);
}

TYPED_TEST(TestForGraph, test_edge_3)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    this -> setupCyclic();
    pair<edge_descriptor, bool> p = edge(this->_vdD, this->_vdH, this->_g);
    ASSERT_FALSE(p.second );
}



// ----------
// test_edges
// ----------

TYPED_TEST(TestForGraph, test_edges_1)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this -> setupACyclic();
    std::pair<edge_iterator, edge_iterator> p = edges(this->_g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor ebegin = *b;
    ASSERT_TRUE(ebegin == this->_edAB);
    ++b;
    edge_descriptor eend = *b;
    ASSERT_TRUE(eend == this->_edAC);
}

TYPED_TEST(TestForGraph, test_edges_2)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this -> setupACyclic();
    std::pair<edge_iterator, edge_iterator> p = edges(this->_g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor ebegin = *b;
    ASSERT_TRUE(ebegin == this->_edAB);
    ++b;
    edge_descriptor eend = *b;
    ASSERT_TRUE(eend == this->_edAC);
    ++b;
    ++b;
    ++b;
    ++b;
    ++b;
    ++b;
    ++b;
    ++b;
    edge_descriptor last = *b;
    ASSERT_TRUE(last == this->_edGH);
}

TYPED_TEST(TestForGraph, test_edges_3)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    
    this -> setupCyclic();
    std::pair<edge_iterator, edge_iterator> p = edges(this->_g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;
    ASSERT_NE(b , e);
    edge_descriptor ebegin = *b;
    ASSERT_TRUE(ebegin == this->_edAB);
    ++b;
    edge_descriptor eend = *b;
    ASSERT_TRUE(eend == this->_edAC);
}


// -----------------
// test_num_vertices
// -----------------

TYPED_TEST (TestForGraph, test_num_vertices_1)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setupACyclic();
    vertices_size_type vs = num_vertices(this->_g);
    ASSERT_TRUE(vs == 8);
}

TYPED_TEST (TestForGraph, test_num_vertices_2)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setupACyclic();
    vertices_size_type vs = num_vertices(this->_g);
    vertex_descriptor v = add_vertex(this->_g);
    ASSERT_TRUE(v == 8);
    vertex_descriptor v1 = add_vertex(this->_g);
    ASSERT_TRUE(v1 == 9);
    ASSERT_TRUE(vs == 8);
    vertices_size_type nvs = num_vertices(this->_g);
    ASSERT_TRUE(nvs == 10);
}

TYPED_TEST (TestForGraph, test_num_vertices_3)
{
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setupACyclic();
    vertices_size_type vs = num_vertices(this->_g);
    vertex_descriptor v = add_vertex(this->_g);
    ASSERT_TRUE(v == 8);
    vertex_descriptor v1 = add_vertex(this->_g);
    ASSERT_TRUE(v1 == 9);
    vertex_descriptor v2 = add_vertex(this->_g);
    ASSERT_TRUE(v2 == 10);
    vertex_descriptor v3 = add_vertex(this->_g);
    ASSERT_TRUE(v3 == 11);
    vertex_descriptor v4 = add_vertex(this->_g);
    ASSERT_TRUE(v4 == 12);
    ASSERT_TRUE(vs == 8);
    vertices_size_type nvs = num_vertices(this->_g);
    ASSERT_TRUE(nvs == 13);
}


// -----------
// test_source
// -----------

TYPED_TEST(TestForGraph, test_source_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setupACyclic();
    vertex_descriptor vd = source(this->_edAB, this->_g);
    ASSERT_TRUE(vd == this->_vdA);
}

TYPED_TEST(TestForGraph, test_source_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setupACyclic();
    vertex_descriptor vd = source(this->_edFH, this->_g);
    ASSERT_TRUE(vd == this->_vdF);
}

TYPED_TEST(TestForGraph, test_source_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setupCyclic();
    vertex_descriptor vd = source(this->_edDF, this->_g);
    ASSERT_TRUE(vd == this->_vdD);
}

// -----------
// test_target
// -----------

TYPED_TEST(TestForGraph, test_target_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setupACyclic();
    vertex_descriptor vd = target(this->_edAB, this->_g);
    ASSERT_TRUE(vd == this->_vdB);
}

TYPED_TEST(TestForGraph, test_target_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setupACyclic();
    vertex_descriptor vd = target(this->_edFH, this->_g);
    ASSERT_TRUE(vd == this->_vdH);
}

TYPED_TEST(TestForGraph, test_target_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setupCyclic();
    vertex_descriptor vd = target(this->_edDF, this->_g);
    ASSERT_TRUE(vd == this->_vdF);
}

// -------------
// test_vertices
// -------------


TYPED_TEST(TestForGraph, test_vertices_1)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this->setupACyclic();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->_g);
    vertex_iterator b = p.first;
    vertex_iterator e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->_vdA);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->_vdH);
}

TYPED_TEST(TestForGraph, test_vertices_2)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setupACyclic();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->_g);
    vertex_iterator b = p.first;
    vertex_iterator e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->_vdA);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->_vdH);
}

TYPED_TEST(TestForGraph, test_vertices_3)
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    this -> setupCyclic();
    pair<vertex_iterator, vertex_iterator> p = vertices(this->_g);
    vertex_iterator b = p.first;
    vertex_iterator e = p.second;
    ASSERT_NE(b , e);
    
    vertex_descriptor vbegin = *b;
    ASSERT_TRUE(vbegin == this->_vdA);
    --e;
    vertex_descriptor vend = *e;
    ASSERT_TRUE(vend == this->_vdH);
}



// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestForGraph, test_has_cycle_1)
{
    Graph g;
    ASSERT_FALSE(has_cycle(g));
}

TYPED_TEST(TestForGraph, test_has_cycle_2)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	Graph g;
	vertex_descriptor _vdA = add_vertex(g);
	vertex_descriptor _vdB = add_vertex(g);
	bool _edAB = add_edge(_vdA, _vdB, g).second;
	bool _edAC = add_edge(_vdB, _vdA, g).second;
	ASSERT_TRUE(_edAB);
	ASSERT_TRUE(_edAC);
	ASSERT_TRUE(has_cycle(g));
}

TYPED_TEST(TestForGraph, test_has_cycle_3)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	Graph g;
	vertex_descriptor _vdA = add_vertex(g);
	vertex_descriptor _vdB = add_vertex(g);
	bool _edAB = add_edge(_vdA, _vdB, g).second;
	ASSERT_TRUE(_edAB);
	ASSERT_FALSE(has_cycle(g));

}
TYPED_TEST(TestForGraph, test_has_cycle_4)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	Graph g;
	vertex_descriptor _vdA = add_vertex(g);
	vertex_descriptor _vdB = add_vertex(g);
	vertex_descriptor _vdC = add_vertex(g);
	bool _edAB = add_edge(_vdA, _vdB, g).second;
	bool _edBC = add_edge(_vdB, _vdC, g).second;
	bool _edCA = add_edge(_vdC, _vdA, g).second;
	ASSERT_TRUE(_edAB);
	ASSERT_TRUE(_edBC);
	ASSERT_TRUE(_edCA);
	ASSERT_TRUE(has_cycle(g));
}

TYPED_TEST(TestForGraph, test_has_cycle_5)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	Graph g;
	vertex_descriptor _vdA = add_vertex(g);
	vertex_descriptor _vdB = add_vertex(g);
	vertex_descriptor _vdC = add_vertex(g);
	bool _edAB = add_edge(_vdA, _vdB, g).second;
	bool _edBC = add_edge(_vdB, _vdC, g).second;
	ASSERT_TRUE(_edAB);
	ASSERT_TRUE(_edBC);
	ASSERT_FALSE(has_cycle(g));
}

TYPED_TEST(TestForGraph, test_has_cycle_6)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	Graph g;
	vertex_descriptor _vdA = add_vertex(g);
	vertex_descriptor _vdB = add_vertex(g);
	vertex_descriptor _vdC = add_vertex(g);
	bool _edAB = add_edge(_vdA, _vdB, g).second;
	bool _edAC = add_edge(_vdA, _vdC, g).second;
	ASSERT_TRUE(_edAB);
	ASSERT_TRUE(_edAC);
	ASSERT_FALSE(has_cycle(g));

}




// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST (TestForGraph, test_topological_sort_no_cycle_1)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->setupACyclic();
    
    ostringstream out;
    try{
        topological_sort(this->_g, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string("4 3 1 2 0 7 5 6 "), out.str());
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(false);
    }
}


TYPED_TEST (TestForGraph, test_topological_sort_no_cycle_2)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->setupCyclic();
    
    ostringstream out;
    try{
        topological_sort(this->_g, ostream_iterator<vertex_descriptor>(out, " "));
        EXPECT_TRUE(false);
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(true);
    }
}

TYPED_TEST (TestForGraph, test_topological_sort_no_cycle_3)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->setupACyclic1();
    
    ostringstream out;
    try{
        topological_sort(this->_g, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string("0 1 2 3 4 5 6 7 "), out.str());
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(false);
    }
}
