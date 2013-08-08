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

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info; 
typedef testing::Types<boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>, Graph> testlist;

template <typename T>
class TestGraphSample :  public testing::Test
{
public:
	// --------
	// typedefs
	// --------

	typedef T										graph_type;

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
	// setUp
	// -----

	virtual void SetUp () 
	{
		vdA  = add_vertex(this->g);
		vdB  = add_vertex(this->g);
		vdC  = add_vertex(this->g);
		vdD  = add_vertex(this->g);
		vdE  = add_vertex(this->g);
		vdF  = add_vertex(this->g);
		vdG  = add_vertex(this->g);
		vdH  = add_vertex(this->g);
		edAB = add_edge(vdA, vdB, this->g).first;
		edAC = add_edge(vdA, vdC, this->g).first;
		edAE = add_edge(vdA, vdE, this->g).first;
		edBD = add_edge(vdB, vdD, this->g).first;
		edBE = add_edge(vdB, vdE, this->g).first;
		edCD = add_edge(vdC, vdD, this->g).first;
		edDE = add_edge(vdD, vdE, this->g).first;
		edDF = add_edge(vdD, vdF, this->g).first;
		edFD = add_edge(vdF, vdD, this->g).first;
		edFH = add_edge(vdF, vdH, this->g).first;
		edGH = add_edge(vdG, vdH, this->g).first;
	}
};

template <typename T>
class TestGraphBasic :  public testing::Test
{
public:
	// --------
	// typedefs
	// --------

	typedef T										graph_type;

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

	edge_descriptor edAC;
	edge_descriptor edDB;
	edge_descriptor edDC;
	edge_descriptor edEB;
	edge_descriptor edFB;
	edge_descriptor edFC;
	edge_descriptor edGC;

	// -----
	// setUp
	// -----

	virtual void SetUp () 
	{
		vdA  = add_vertex(this->g);
		vdB  = add_vertex(this->g);
		vdC  = add_vertex(this->g);
		vdD  = add_vertex(this->g);
		vdE  = add_vertex(this->g);
		vdF  = add_vertex(this->g);
		vdG  = add_vertex(this->g);
		edAC = add_edge(vdA, vdC, this->g).first;
		edDB = add_edge(vdD, vdB, this->g).first;
		edDC = add_edge(vdD, vdC, this->g).first;
		edEB = add_edge(vdE, vdB, this->g).first;
		edFB = add_edge(vdF, vdB, this->g).first;
		edFC = add_edge(vdF, vdC, this->g).first;
		edGC = add_edge(vdG, vdC, this->g).first;
	}
};

template <typename T>
class TestGraphGeneral :  public testing::Test
{
public:
	// --------
	// typedefs
	// --------

	typedef T										graph_type;

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

	edge_descriptor edAA;
	edge_descriptor edAB;
	edge_descriptor edAC;
	edge_descriptor edAD;
	edge_descriptor edAE;
	edge_descriptor edAF;
	edge_descriptor edAG;
	edge_descriptor edAH;

	edge_descriptor edBA;
	edge_descriptor edBB;
	edge_descriptor edBC;
	edge_descriptor edBD;
	edge_descriptor edBE;
	edge_descriptor edBF;
	edge_descriptor edBG;
	edge_descriptor edBH;

	edge_descriptor edCA;
	edge_descriptor edCB;
	edge_descriptor edCC;
	edge_descriptor edCD;
	edge_descriptor edCE;
	edge_descriptor edCF;
	edge_descriptor edCG;
	edge_descriptor edCH;

	edge_descriptor edDA;
	edge_descriptor edDB;
	edge_descriptor edDC;
	edge_descriptor edDD;
	edge_descriptor edDE;
	edge_descriptor edDF;
	edge_descriptor edDG;
	edge_descriptor edDH;

	edge_descriptor edEA;
	edge_descriptor edEB;
	edge_descriptor edEC;
	edge_descriptor edED;
	edge_descriptor edEE;
	edge_descriptor edEF;
	edge_descriptor edEG;
	edge_descriptor edEH;

	edge_descriptor edFA;
	edge_descriptor edFB;
	edge_descriptor edFC;
	edge_descriptor edFD;
	edge_descriptor edFE;
	edge_descriptor edFF;
	edge_descriptor edFG;
	edge_descriptor edFH;

	edge_descriptor edGA;
	edge_descriptor edGB;
	edge_descriptor edGC;
	edge_descriptor edGD;
	edge_descriptor edGE;
	edge_descriptor edGF;
	edge_descriptor edGG;
	edge_descriptor edGH;

	edge_descriptor edHA;
	edge_descriptor edHB;
	edge_descriptor edHC;
	edge_descriptor edHD;
	edge_descriptor edHE;
	edge_descriptor edHF;
	edge_descriptor edHG;
	edge_descriptor edHH;

	// -----
	// setUp
	// -----

	void CycleSetUp () 
	{
		vdA  = add_vertex(this->g);
		vdB  = add_vertex(this->g);
		vdC  = add_vertex(this->g);
		vdD  = add_vertex(this->g);
		vdE  = add_vertex(this->g);
		vdF  = add_vertex(this->g);
		vdG  = add_vertex(this->g);
		vdH  = add_vertex(this->g);
		edAB = add_edge(vdA, vdB, this->g).first;
		edBC = add_edge(vdB, vdC, this->g).first;
		edCD = add_edge(vdC, vdD, this->g).first;
		edDE = add_edge(vdD, vdE, this->g).first;
		edEF = add_edge(vdE, vdF, this->g).first;
		edFG = add_edge(vdF, vdG, this->g).first;
		edGH = add_edge(vdG, vdH, this->g).first;
		edHA = add_edge(vdH, vdA, this->g).first;
	}

	void NonCycleSetUp () 
	{
		vdA  = add_vertex(this->g);
		vdB  = add_vertex(this->g);
		vdC  = add_vertex(this->g);
		vdD  = add_vertex(this->g);
		vdE  = add_vertex(this->g);
		vdF  = add_vertex(this->g);
		vdG  = add_vertex(this->g);
		vdH  = add_vertex(this->g);
		edAB = add_edge(vdA, vdB, this->g).first;
		edCD = add_edge(vdC, vdD, this->g).first;
		edEF = add_edge(vdE, vdF, this->g).first;
		edGH = add_edge(vdG, vdH, this->g).first;
	}

	void ComplexNonCycleSetUp()
	{
		vdA  = add_vertex(this->g); 
		vdB  = add_vertex(this->g); 
		vdC  = add_vertex(this->g); 
		vdD  = add_vertex(this->g); 
		vdE  = add_vertex(this->g); 
		vdF  = add_vertex(this->g); 
		vdG  = add_vertex(this->g); 
		vdH  = add_vertex(this->g); 
		edAB = add_edge(vdA, vdB, this->g).first;
		edAF = add_edge(vdA, vdF, this->g).first;
		edAG = add_edge(vdA, vdG, this->g).first;
		edBG = add_edge(vdB, vdG, this->g).first;
		edCB = add_edge(vdC, vdB, this->g).first;
		edCD = add_edge(vdC, vdD, this->g).first;
		edCE = add_edge(vdC, vdE, this->g).first;
		edCF = add_edge(vdC, vdF, this->g).first;
		edCG = add_edge(vdC, vdG, this->g).first;
		edDG = add_edge(vdD, vdG, this->g).first;
		edEG = add_edge(vdE, vdG, this->g).first;
		edHG = add_edge(vdH, vdG, this->g).first;
	}

	void Complex1NonCycleSetUp()
	{
		vdA  = add_vertex(this->g); 
		vdB  = add_vertex(this->g); 
		vdC  = add_vertex(this->g); 
		vdD  = add_vertex(this->g); 
		vdE  = add_vertex(this->g); 
		vdF  = add_vertex(this->g); 
		vdG  = add_vertex(this->g); 
		vdH  = add_vertex(this->g); 
		edAB = add_edge(vdA, vdB, this->g).first;
		edDB = add_edge(vdD, vdB, this->g).first;
		edEB = add_edge(vdE, vdB, this->g).first;
		edEH = add_edge(vdE, vdH, this->g).first;
		edFH = add_edge(vdF, vdH, this->g).first;
		edGH = add_edge(vdG, vdH, this->g).first;
	}

	void Complex2NonCycleSetUp()
	{
		vdA  = add_vertex(this->g); 
		vdB  = add_vertex(this->g); 
		vdC  = add_vertex(this->g); 
		vdD  = add_vertex(this->g); 
		vdE  = add_vertex(this->g); 
		vdF  = add_vertex(this->g); 
		vdG  = add_vertex(this->g); 
		edAB = add_edge(vdA, vdB, this->g).first;
		edDB = add_edge(vdD, vdB, this->g).first;
		edEB = add_edge(vdE, vdB, this->g).first;
		edEC = add_edge(vdE, vdC, this->g).first;
		edFC = add_edge(vdF, vdC, this->g).first;
		edGC = add_edge(vdG, vdC, this->g).first;
	}

	void Complex3NonCycleSetUp()
	{
		vdA  = add_vertex(this->g); 
		vdB  = add_vertex(this->g); 
		vdC  = add_vertex(this->g); 
		vdD  = add_vertex(this->g); 
		vdE  = add_vertex(this->g); 
		vdF  = add_vertex(this->g); 
		vdG  = add_vertex(this->g); 
		vdH  = add_vertex(this->g);
		edAB = add_edge(vdA, vdB, this->g).first;
		edDB = add_edge(vdD, vdB, this->g).first;
		edEB = add_edge(vdE, vdB, this->g).first;
		edAC = add_edge(vdA, vdC, this->g).first;
		edEC = add_edge(vdE, vdC, this->g).first;
		edFC = add_edge(vdF, vdC, this->g).first;
		edGC = add_edge(vdG, vdC, this->g).first;
		edDH = add_edge(vdF, vdH, this->g).first;
	}

	void Complex4NonCycleSetUp()
	{
		vdA  = add_vertex(this->g); 
		vdB  = add_vertex(this->g); 
		vdC  = add_vertex(this->g); 
		vdD  = add_vertex(this->g); 
		vdE  = add_vertex(this->g); 
		vdF  = add_vertex(this->g);
		edBE = add_edge(vdB, vdE, this->g).first;
		edCE = add_edge(vdC, vdE, this->g).first;
		edDE = add_edge(vdD, vdE, this->g).first;
		edAB = add_edge(vdA, vdB, this->g).first;
		edBF = add_edge(vdB, vdF, this->g).first;
	}
    
    void Complex5NonCycleSetUp()
	{
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);
        edCB = add_edge(vdC, vdB, g).first;
        edBA = add_edge(vdB, vdA, g).first;
        edCD = add_edge(vdC, vdD, g).first;
        edAD = add_edge(vdA, vdD, g).first;
    }
    
    void Complex6NonCycleSetUp()
	{
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);
		vdE	 = add_vertex(g);
		vdF  = add_vertex(g);

        edAB = add_edge(vdA, vdB, g).first;
        edCE = add_edge(vdC, vdE, g).first;
        edCF = add_edge(vdC, vdF, g).first;
        edAD = add_edge(vdA, vdD, g).first;
        edBE = add_edge(vdB, vdE, g).first;
        edED = add_edge(vdE, vdD, g).first;
    }
    
    void Complex7NonCycleSetUp()
    {
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
        edFH = add_edge(vdF, vdH, g).first;
        edGH = add_edge(vdG, vdH, g).first;
    }

	void SimpleNonCycleSetUp()
	{
		vdA  = add_vertex(this->g);
		vdB  = add_vertex(this->g);
		edAB = add_edge(vdA, vdB, this->g).first;
	}
};

TYPED_TEST_CASE(TestGraphSample, testlist);
TYPED_TEST_CASE(TestGraphBasic, testlist);
TYPED_TEST_CASE(TestGraphGeneral, testlist);

// --------------
// test_vertex
// --------------
TYPED_TEST(TestGraphGeneral, test_vertex_random_positive) 
{
   	typename TestFixture::edges_size_type es = num_edges(this->g);
	typename TestFixture::vertices_size_type vs = num_vertices(this->g);
	ASSERT_EQ(es, 0);
	ASSERT_EQ(vs, 0);
    typename TestFixture::vertex_descriptor v = vertex(101, this->g);
    ASSERT_EQ(v, 101);
}

// --------------
// test_vertex
// --------------
TYPED_TEST(TestGraphGeneral, test_vertex_random_negative) 
{
   	typename TestFixture::edges_size_type es = num_edges(this->g);
	typename TestFixture::vertices_size_type vs = num_vertices(this->g);
	ASSERT_EQ(es, 0);
	ASSERT_EQ(vs, 0);
    typename TestFixture::vertex_descriptor v = vertex(-101, this->g);
    ASSERT_EQ(v, -101);
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_false) 
{
	this->NonCycleSetUp();
	typename TestFixture::edges_size_type es = num_edges(this->g);
	typename TestFixture::vertices_size_type vs = num_vertices(this->g);
	ASSERT_EQ(es, 4);
	ASSERT_EQ(vs, 8);
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_true) 
{
	this->CycleSetUp();
	typename TestFixture::edges_size_type es = num_edges(this->g);
	typename TestFixture::vertices_size_type vs = num_vertices(this->g);
	ASSERT_EQ(es, 8);
	ASSERT_EQ(vs, 8);
	ASSERT_TRUE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_simple) 
{
	this->SimpleNonCycleSetUp();
	typename TestFixture::edges_size_type es = num_edges(this->g);
	typename TestFixture::vertices_size_type vs = num_vertices(this->g);
	ASSERT_EQ(es, 1);
	ASSERT_EQ(vs, 2);
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_complex) 
{
	this->ComplexNonCycleSetUp();
	typename TestFixture::edges_size_type es = num_edges(this->g);
	typename TestFixture::vertices_size_type vs = num_vertices(this->g);
	ASSERT_EQ(es, 12);
	ASSERT_EQ(vs, 8);
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_complex1) 
{
	this->Complex1NonCycleSetUp();
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_complex2) 
{
	this->Complex2NonCycleSetUp();
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_complex3) 
{
	this->Complex3NonCycleSetUp();
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_complex4) 
{
	this->Complex4NonCycleSetUp();
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_complex5) 
{
	this->Complex5NonCycleSetUp();
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_complex6) 
{
	this->Complex6NonCycleSetUp();
	ASSERT_FALSE(has_cycle(this->g));
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphGeneral, test_has_cycle_complex7) 
{
	this->Complex7NonCycleSetUp();
	ASSERT_FALSE(has_cycle(this->g));
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_noncycle) 
{
	this->NonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "1 0 3 2 5 4 7 6 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_cycle) 
{
	this->CycleSetUp();
	try
	{
		std::ostringstream out;
		topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
		ASSERT_TRUE(false);
	}
	catch (boost::exception &e)
	{
		std::exception const * se = dynamic_cast<std::exception const *>(&e);
		ASSERT_EQ(std::strcmp(se->what(), "The graph must be a DAG."), 0);
	}
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_complex)
{
	this->ComplexNonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "6 1 5 0 3 4 2 7 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_complex1)
{
	this->Complex1NonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "1 0 2 3 7 4 5 6 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_complex2)
{
	this->Complex2NonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "1 0 2 3 4 5 6 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_complex3)
{
	this->Complex3NonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "1 2 0 3 4 7 5 6 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_complex4)
{
	this->Complex4NonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "4 5 1 0 2 3 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_complex5)
{
	this->Complex5NonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "3 0 1 2 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_complex6)
{
	this->Complex6NonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "3 4 1 0 5 2 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_complex7)
{
	this->Complex7NonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "4 7 5 3 1 2 0 6 ");
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphGeneral, test_topological_sort_simple)
{
	this->SimpleNonCycleSetUp();
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "1 0 ");
}

// -------------
// test_add_edge
// -------------

TYPED_TEST(TestGraphGeneral, test_add_edge)
{
	this->vdA  = add_vertex(this->g); 
	this->vdB  = add_vertex(this->g); 
	std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
	ASSERT_TRUE(p.first != this->edAB);
	ASSERT_EQ(p.second, true);
	this->edAB = p.first;
	std::pair<typename TestFixture::edge_descriptor, bool> p1 = add_edge(this->vdA, this->vdB, this->g);
	ASSERT_EQ(p1.first, this->edAB);
	ASSERT_EQ(p1.second, false);
}

// -------------
// test_add_edge
// -------------
TYPED_TEST(TestGraphGeneral, test_add_edge_adjacency_list_no_change)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    this->SimpleNonCycleSetUp();
    std::pair<adjacency_iterator, adjacency_iterator> x = adjacent_vertices(this->vdA, this->g);
    ASSERT_NE(x.first, x.second);
    ASSERT_EQ(std::distance(x.first, x.second), 1);
    std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdB, this->vdA, this->g);
    ASSERT_TRUE(p.second);
    std::pair<adjacency_iterator, adjacency_iterator> y = adjacent_vertices(this->vdA, this->g);
    ASSERT_NE(y.first, y.second);
    ASSERT_EQ(std::distance(y.first, y.second), 1);
    ASSERT_TRUE(has_cycle(this->g));
}

// -------------
// test_add_edge
// -------------
TYPED_TEST(TestGraphGeneral, test_add_edge_adjacency_list_change)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    this->SimpleNonCycleSetUp();
    std::pair<adjacency_iterator, adjacency_iterator> x = adjacent_vertices(this->vdA, this->g);
    ASSERT_NE(x.first, x.second);
    ASSERT_EQ(std::distance(x.first, x.second), 1);
    std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdA, this->g);
    ASSERT_TRUE(p.second);
    std::pair<adjacency_iterator, adjacency_iterator> y = adjacent_vertices(this->vdA, this->g);
    ASSERT_NE(y.first, y.second);
    ASSERT_EQ(std::distance(y.first, y.second), 2);
    ASSERT_TRUE(has_cycle(this->g));
}

// -------------
// test_edge
// -------------

TYPED_TEST(TestGraphGeneral, test_edge_missing_edge)
{ 
	this->vdA  = add_vertex(this->g); 
	this->vdB  = add_vertex(this->g);
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
	std::pair<typename TestFixture::edge_descriptor, bool> q = edge(0, 1, this->g);
	ASSERT_EQ(p.first, q.first);
	ASSERT_EQ(p.second, false);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(TestGraphGeneral, test_adjacency_list_add_edge)
{	
	this->vdA  = add_vertex(this->g); 
	this->vdB  = add_vertex(this->g);
	add_edge(this->vdA, this->vdB, this->g);
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
    typename TestFixture::adjacency_iterator b = p.first; 
    typename TestFixture::adjacency_iterator e = p.second;
    ASSERT_EQ(true, b != e);
    typename TestFixture::vertex_descriptor vd = *b;
    ASSERT_EQ(true, vd == this->vdB);
    ++b;
	ASSERT_EQ(true, b == e);
	
	add_edge(this->vdA, this->vdA, this->g);
    p = adjacent_vertices(this->vdA, this->g);
    b = p.first; 
    e = p.second;
    ASSERT_EQ(true, b != e);
    vd = *b;
    ASSERT_EQ(true, vd == this->vdA);
    ++b;
    vd = *b;
    ASSERT_EQ(true, vd == this->vdB);
	++b;
	ASSERT_EQ(true, b == e);
}

// -------------
// test_add_edge
// -------------

TYPED_TEST(TestGraphBasic, test_add_edge)
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdC, this->g);
	ASSERT_EQ(p.first , this->edAC);
	ASSERT_EQ(p.second, false);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_A)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdC);
	}
	++b;
	ASSERT_TRUE(b == e);
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_A_reverse)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
    --e;
	typename TestFixture::vertex_descriptor vd = *e;
	ASSERT_EQ(vd, this->vdC);
	ASSERT_TRUE(b == e);
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_B)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdB, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b == e);
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_C)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdC, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b == e);
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_D)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdD, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdB);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdC);
	}
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_D_reverse)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdD, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
    --e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdC);
	}
	--e;
	if (b == e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdB);
	}
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_E)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdE, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdB);
	}
	++b;
	ASSERT_TRUE(b == e);
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_E_reverse)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdE, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
    ASSERT_TRUE(b != e);
	--e;
	if (b == e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdB);
	}
	ASSERT_TRUE(b == e);
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_F)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdF, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdB);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdC);
	}
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_F_reverse)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdF, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
    --e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdC);
	}
	--e;
	if (b == e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdB);
	}
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_G)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdG, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdC);
	}
	++b;
	ASSERT_TRUE(b == e);
}

TYPED_TEST(TestGraphBasic, test_adjacent_vertices_G_reverse)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdG, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
	ASSERT_TRUE(b != e);
    --e;
	typename TestFixture::vertex_descriptor vd = *e;
	ASSERT_EQ(vd, this->vdC);
	ASSERT_TRUE(b == e);
}

// ---------
// test_edge
// ---------

TYPED_TEST(TestGraphBasic, test_edge_AC) 
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdA, this->vdC, this->g);
	ASSERT_EQ(p.first , this->edAC);
	ASSERT_EQ(p.second, true);
}

TYPED_TEST(TestGraphBasic, test_edge_DB) 
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdD, this->vdB, this->g);
	ASSERT_EQ(p.first , this->edDB);
	ASSERT_EQ(p.second, true);
}

TYPED_TEST(TestGraphBasic, test_edge_DC) 
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdD, this->vdC, this->g);
	ASSERT_EQ(p.first , this->edDC);
	ASSERT_EQ(p.second, true);
}

TYPED_TEST(TestGraphBasic, test_edge_EB) 
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdE, this->vdB, this->g);
	ASSERT_EQ(p.first , this->edEB);
	ASSERT_EQ(p.second, true);
}

TYPED_TEST(TestGraphBasic, test_edge_FB) 
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdF, this->vdB, this->g);
	ASSERT_EQ(p.first , this->edFB);
	ASSERT_EQ(p.second, true);
}

TYPED_TEST(TestGraphBasic, test_edge_FC) 
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdF, this->vdC, this->g);
	ASSERT_EQ(p.first , this->edFC);
	ASSERT_EQ(p.second, true);
}

TYPED_TEST(TestGraphBasic, test_edge_GC) 
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdG, this->vdC, this->g);
	ASSERT_EQ(p.first , this->edGC);
	ASSERT_EQ(p.second, true);
}

// ----------
// test_edges
// ----------

TYPED_TEST(TestGraphBasic, test_edges)
{
	std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->g);
	typename TestFixture::edge_iterator                           b = p.first;
	typename TestFixture::edge_iterator                           e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edAC);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edDB);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edDC);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edEB);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edFB);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edFC);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edGC);
	}
	++b;
	ASSERT_TRUE(b == e);
}

// --------------
// test_num_edges
// --------------

TYPED_TEST(TestGraphBasic, test_num_edges) 
{
	typename TestFixture::edges_size_type es = num_edges(this->g);
	ASSERT_EQ(es, 7);
}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST(TestGraphBasic, test_num_vertices)
{
	typename TestFixture::vertices_size_type vs = num_vertices(this->g);
	ASSERT_EQ(vs, 7);
}

// -----------
// test_source
// -----------

TYPED_TEST(TestGraphBasic, test_source_AC) 
{
	typename TestFixture::vertex_descriptor vd = source(this->edAC, this->g);
	ASSERT_EQ(vd, this->vdA);
}

TYPED_TEST(TestGraphBasic, test_source_DB) 
{
	typename TestFixture::vertex_descriptor vd = source(this->edDB, this->g);
	ASSERT_EQ(vd, this->vdD);
}

TYPED_TEST(TestGraphBasic, test_source_DC) 
{
	typename TestFixture::vertex_descriptor vd = source(this->edDC, this->g);
	ASSERT_EQ(vd, this->vdD);
}

TYPED_TEST(TestGraphBasic, test_source_EB) 
{
	typename TestFixture::vertex_descriptor vd = source(this->edEB, this->g);
	ASSERT_EQ(vd, this->vdE);
}

TYPED_TEST(TestGraphBasic, test_source_FB) 
{
	typename TestFixture::vertex_descriptor vd = source(this->edFB, this->g);
	ASSERT_EQ(vd, this->vdF);
}

TYPED_TEST(TestGraphBasic, test_source_FC) 
{
	typename TestFixture::vertex_descriptor vd = source(this->edFC, this->g);
	ASSERT_EQ(vd, this->vdF);
}

TYPED_TEST(TestGraphBasic, test_source_GC) 
{
	typename TestFixture::vertex_descriptor vd = source(this->edGC, this->g);
	ASSERT_EQ(vd, this->vdG);
}

// -----------
// test_target
// -----------

TYPED_TEST(TestGraphBasic, test_target_AC) 
{
	typename TestFixture::vertex_descriptor vd = target(this->edAC, this->g);
	ASSERT_EQ(vd, this->vdC);
}

TYPED_TEST(TestGraphBasic, test_target_DB) 
{
	typename TestFixture::vertex_descriptor vd = target(this->edDB, this->g);
	ASSERT_EQ(vd, this->vdB);
}

TYPED_TEST(TestGraphBasic, test_target_DC) 
{
	typename TestFixture::vertex_descriptor vd = target(this->edDC, this->g);
	ASSERT_EQ(vd, this->vdC);
}

TYPED_TEST(TestGraphBasic, test_target_EB) 
{
	typename TestFixture::vertex_descriptor vd = target(this->edEB, this->g);
	ASSERT_EQ(vd, this->vdB);
}

TYPED_TEST(TestGraphBasic, test_target_FB) 
{
	typename TestFixture::vertex_descriptor vd = target(this->edFB, this->g);
	ASSERT_EQ(vd, this->vdB);
}

TYPED_TEST(TestGraphBasic, test_target_FC) 
{
	typename TestFixture::vertex_descriptor vd = target(this->edFC, this->g);
	ASSERT_EQ(vd, this->vdC);
}

TYPED_TEST(TestGraphBasic, test_target_GC) 
{
	typename TestFixture::vertex_descriptor vd = target(this->edGC, this->g);
	ASSERT_EQ(vd, this->vdC);
}

// -----------
// test_vertex
// -----------

TYPED_TEST(TestGraphBasic, test_vertex_A) 
{
	typename TestFixture::vertex_descriptor vd = vertex(0, this->g);
	ASSERT_EQ(vd, this->vdA);
}

TYPED_TEST(TestGraphBasic, test_vertex_B) 
{
	typename TestFixture::vertex_descriptor vd = vertex(1, this->g);
	ASSERT_EQ(vd, this->vdB);
}

TYPED_TEST(TestGraphBasic, test_vertex_C) 
{
	typename TestFixture::vertex_descriptor vd = vertex(2, this->g);
	ASSERT_EQ(vd, this->vdC);
}

TYPED_TEST(TestGraphBasic, test_vertex_D) 
{
	typename TestFixture::vertex_descriptor vd = vertex(3, this->g);
	ASSERT_EQ(vd, this->vdD);
}

TYPED_TEST(TestGraphBasic, test_vertex_E) 
{
	typename TestFixture::vertex_descriptor vd = vertex(4, this->g);
	ASSERT_EQ(vd, this->vdE);
}

TYPED_TEST(TestGraphBasic, test_vertex_F) 
{
	typename TestFixture::vertex_descriptor vd = vertex(5, this->g);
	ASSERT_EQ(vd, this->vdF);
}

TYPED_TEST(TestGraphBasic, test_vertex_G) 
{
	typename TestFixture::vertex_descriptor vd = vertex(6, this->g);
	ASSERT_EQ(vd, this->vdG);
}

// -------------
// test_vertices
// -------------

TYPED_TEST(TestGraphBasic, test_vertices) 
{
	std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g);
	typename TestFixture::vertex_iterator                             b = p.first;
	typename TestFixture::vertex_iterator                             e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdA);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdB);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdC);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdD);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdE);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdF);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdG);
	}
}

// -------------
// test_vertices
// -------------

TYPED_TEST(TestGraphBasic, test_vertices_reverse) 
{
	std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g);
	typename TestFixture::vertex_iterator                             b = p.first;
	typename TestFixture::vertex_iterator                             e = p.second;
	ASSERT_TRUE(b != e);
    --e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdG);
	}
	--e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdF);
	}
	--e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdE);
	}
	--e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdD);
	}
	--e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdC);
	}
	--e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdB);
	}
	--e;
	typename TestFixture::vertex_descriptor vd = *e;
	ASSERT_EQ(vd, this->vdA);
	ASSERT_EQ(b, e);
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphBasic, test_has_cycle) 
{
	ASSERT_FALSE(has_cycle(this->g));
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphBasic, test_topological_sort) 
{
	std::ostringstream out;
	topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
	ASSERT_EQ(out.str(), "2 0 1 3 4 5 6 ");
}

// -------------
// test_add_edge
// -------------

TYPED_TEST(TestGraphSample, test_add_edge_duplicate)
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
	ASSERT_EQ(p.first , this->edAB);
	ASSERT_EQ(p.second, false);
}

// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(TestGraphSample, test_adjacent_vertices)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
    ASSERT_EQ(std::distance(b, e), 3);
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdB);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdC);
	}
    ++b;
    if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdE);
	}
    ++b;
    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraphSample, test_adjacent_vertices_reverse)
{
	std::pair<typename TestFixture::adjacency_iterator, typename TestFixture::adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
	typename TestFixture::adjacency_iterator b = p.first;
	typename TestFixture::adjacency_iterator e = p.second;
    ASSERT_EQ(std::distance(b, e), 3);
	ASSERT_TRUE(b != e);
    --e;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdE);
	}
	--e;
    if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *e;
		ASSERT_EQ(vd, this->vdC);
	}
    --e;
	typename TestFixture::vertex_descriptor vd = *e;
	ASSERT_EQ(vd, this->vdB);
	ASSERT_EQ(b, e);
}

// ---------
// test_edge
// ---------

TYPED_TEST(TestGraphSample, test_edge) 
{
	std::pair<typename TestFixture::edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
	ASSERT_EQ(p.first , this->edAB);
	ASSERT_EQ(p.second, true);
}

// ----------
// test_edges
// ----------

TYPED_TEST(TestGraphSample, test_edges)
{
	std::pair<typename TestFixture::edge_iterator, typename TestFixture::edge_iterator> p = edges(this->g);
	typename TestFixture::edge_iterator                           b = p.first;
	typename TestFixture::edge_iterator                           e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edAB);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edAC);
	}
}

// --------------
// test_num_edges
// --------------

TYPED_TEST(TestGraphSample, test_num_edges) 
{
	typename TestFixture::edges_size_type es = num_edges(this->g);
	ASSERT_EQ(es, 11);
}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST(TestGraphSample, test_num_vertices)
{
	typename TestFixture::vertices_size_type vs = num_vertices(this->g);
	ASSERT_EQ(vs, 8);
}

// -----------
// test_source
// -----------

TYPED_TEST(TestGraphSample, test_source) 
{
	typename TestFixture::vertex_descriptor vd = source(this->edAB, this->g);
	ASSERT_EQ(vd, this->vdA);
}

// -----------
// test_target
// -----------

TYPED_TEST(TestGraphSample, test_target) 
{
	typename TestFixture::vertex_descriptor vd = target(this->edAB, this->g);
	ASSERT_EQ(vd, this->vdB);
}

// -----------
// test_vertex
// -----------

TYPED_TEST(TestGraphSample, test_vertex) 
{
	typename TestFixture::vertex_descriptor vd = vertex(0, this->g);
	ASSERT_EQ(vd, this->vdA);
}

// -------------
// test_vertices
// -------------

TYPED_TEST(TestGraphSample, test_vertices) 
{
	std::pair<typename TestFixture::vertex_iterator, typename TestFixture::vertex_iterator> p = vertices(this->g);
	typename TestFixture::vertex_iterator                             b = p.first;
	typename TestFixture::vertex_iterator                             e = p.second;
	ASSERT_TRUE(b != e);
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdA);
	}
	++b;
	if (b != e) 
	{
		typename TestFixture::vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdB);
	}
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TestGraphSample, test_has_cycle) 
{
	ASSERT_TRUE(has_cycle(this->g));
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(TestGraphSample, test_topological_sort) 
{
	try
	{
		std::ostringstream out;
		topological_sort(this->g, std::ostream_iterator<typename TestFixture::vertex_descriptor>(out, " "));
		ASSERT_TRUE(false);
	}
	catch (boost::exception &e)
	{
		std::exception const * se = dynamic_cast<std::exception const *>(&e);
		ASSERT_EQ(std::strcmp(se->what(), "The graph must be a DAG."), 0);
	}
}
