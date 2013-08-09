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

typedef testing::Types<Graph, boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> > GraphTypes;

template <typename T>
class GraphTest : public testing::Test {
 
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
	 graph_type dag;

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

    void SetUp ()
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
        edFD = add_edge(vdF, vdD, g).first;
        edFH = add_edge(vdF, vdH, g).first;
        edGH = add_edge(vdG, vdH, g).first;
	}


    // ------------
    // SetUpAcyclic
    // ------------

    void SetUpAcyclic ()
	{
        vdA  = add_vertex(dag);
        vdB  = add_vertex(dag);
        vdC  = add_vertex(dag);
        vdD  = add_vertex(dag);
        vdE  = add_vertex(dag);
        vdF  = add_vertex(dag);
        vdG  = add_vertex(dag);
        vdH  = add_vertex(dag);
		 

        edAB = add_edge(vdA, vdB, dag).first;
        edAC = add_edge(vdA, vdC, dag).first;
        edAE = add_edge(vdA, vdE, dag).first;
        edBD = add_edge(vdB, vdD, dag).first;
        edBE = add_edge(vdB, vdE, dag).first;
        edCD = add_edge(vdC, vdD, dag).first;
        edDE = add_edge(vdD, vdE, dag).first;
        edFD = add_edge(vdF, vdD, dag).first;
        edFH = add_edge(vdF, vdH, dag).first;
        edGH = add_edge(vdG, vdH, dag).first;
	}
};



TYPED_TEST_CASE(GraphTest, GraphTypes);


// -------------
// test_add_edge
// -------------

TYPED_TEST(GraphTest, test_add_edge_1)
{
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
	ASSERT_EQ(p.first, this->edAB);
	ASSERT_FALSE(p.second);
}

TYPED_TEST(GraphTest, test_add_edge_2)
{
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdF, this->g);
	ASSERT_TRUE(p.second);
}

TYPED_TEST(GraphTest, test_add_edge_3)
{
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = add_edge(1000, this->vdF, this->g);
	ASSERT_TRUE(p.second);
	ASSERT_EQ(num_vertices(this->g), 1001);
}



// ----------------------
// test_adjacent_vertices
// ----------------------

TYPED_TEST(GraphTest, test_adjacent_vertices_1)
{
	typedef typename TestFixture::adjacency_iterator adjacency_iterator;
   typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
	adjacency_iterator b = p.first;
	adjacency_iterator e = p.second;
	ASSERT_NE(b, e);
	if (b != e)
	{
		vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdB);
	}
	++b;
	if (b != e) 
	{
		vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdC);
	}
}

TYPED_TEST(GraphTest, test_adjacent_vertices_2)
{
	typedef typename TestFixture::adjacency_iterator adjacency_iterator;
   typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdE, this->g);
	ASSERT_EQ(p.first, p.second);
}

TYPED_TEST(GraphTest, test_adjacent_vertices_3)
{
	typedef typename TestFixture::adjacency_iterator adjacency_iterator;
   typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdC, this->g);
	adjacency_iterator b = p.first;
	adjacency_iterator e = p.second;
	ASSERT_NE(b, e);
	ASSERT_EQ(*b, this->vdD);
	b++;
	ASSERT_EQ(b, e);
}


// ---------
// test_edge
// ---------

TYPED_TEST(GraphTest, test_edge_1)
{
	typedef typename TestFixture::edge_descriptor edge_descriptor;

	std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
	ASSERT_EQ(p.first , this->edAB);
	ASSERT_TRUE(p.second);
}

TYPED_TEST(GraphTest, test_edge_2)
{
	typedef typename TestFixture::edge_descriptor edge_descriptor;

	std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdG, this->g);
	ASSERT_FALSE(p.second);
	p = edge(this->vdA, this->vdG, this->g);
	ASSERT_FALSE(p.second);
}

// ----------
// test_edges
// ----------

TYPED_TEST(GraphTest, test_edges_1) {
	typedef typename TestFixture::edge_iterator edge_iterator;
	typedef typename TestFixture::edge_descriptor edge_descriptor;

	std::pair<edge_iterator, edge_iterator> p = edges(this->g);
	edge_iterator                           b = p.first;
	edge_iterator                           e = p.second;
	ASSERT_NE(b, e);
	if (b != e)
	{
		edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edAB);
	}
	++b;
	if (b != e)
	{
		edge_descriptor ed = *b;
		ASSERT_EQ(ed, this->edAC);
	}
}

TYPED_TEST(GraphTest, test_edges_2) {
	typedef typename TestFixture::edge_iterator 		edge_iterator;
	typedef typename TestFixture::edge_descriptor 	edge_descriptor;
   typedef typename TestFixture::graph_type			graph_type;
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edge_descriptor   edge_descriptor;

	graph_type a;

   vertex_descriptor vdA;
   vertex_descriptor vdB;
   vertex_descriptor vdC;
   vertex_descriptor vdD;
   vertex_descriptor vdE;
   vertex_descriptor vdF;
   vertex_descriptor vdG;
   vertex_descriptor vdH;

   vdA  = add_vertex(a);
	vdB  = add_vertex(a);
	vdC  = add_vertex(a);
	vdD  = add_vertex(a);
	vdE  = add_vertex(a);
	vdF  = add_vertex(a);
	vdG  = add_vertex(a);
	vdH  = add_vertex(a);
	
	
	std::pair<edge_iterator, edge_iterator> p = edges(a);
	ASSERT_EQ(p.first, p.second);
}

TYPED_TEST(GraphTest, test_edges_3) {
	typedef typename TestFixture::edge_iterator edge_iterator;
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	typedef typename TestFixture::graph_type			graph_type;
	graph_type a;
	
	std::pair<edge_iterator, edge_iterator> p = edges(a);
	ASSERT_EQ(p.first, p.second);
}


// --------------
// test_num_edges
// --------------

TYPED_TEST(GraphTest, test_num_edges_1 ) 
{
	typedef typename TestFixture::edges_size_type edges_size_type;
   edges_size_type es = num_edges(this->g);
   ASSERT_EQ(es, 11);
}

TYPED_TEST(GraphTest, test_num_edges_2 ) 
{
	typedef typename TestFixture::edges_size_type	edges_size_type;
	typedef typename TestFixture::graph_type			graph_type;
	graph_type a;
   edges_size_type es = num_edges(a);
   ASSERT_EQ(es, 0);
}

TYPED_TEST(GraphTest, test_num_edges_3 ) 
{
	typedef typename TestFixture::edges_size_type	edges_size_type;
	typedef typename TestFixture::graph_type			graph_type;
	graph_type a;
	add_edge(0, 241, a);
   edges_size_type es = num_edges(a);
   ASSERT_EQ(es, 1);
	add_edge(0, 241, a);
	es = num_edges(a);
   ASSERT_EQ(es, 1);
}

TYPED_TEST(GraphTest, test_num_edges_4 ) 
{
	typedef typename TestFixture::edges_size_type	edges_size_type;
	typedef typename TestFixture::graph_type			graph_type;
	graph_type a;
	add_edge(0, 241, a);
   edges_size_type es = num_edges(a);
   ASSERT_EQ(es, 1);
	add_edge(4, 32, a);
	es = num_edges(a);
   ASSERT_EQ(es, 2);
}

// -----------------
// test_num_vertices
// -----------------

TYPED_TEST(GraphTest, test_num_vertices_1) 
{
	typedef typename TestFixture::vertices_size_type vertices_size_type;

   vertices_size_type vs = num_vertices(this->g);
   ASSERT_EQ(vs, 8);
}
TYPED_TEST(GraphTest, test_num_vertices_2) 
{
	typedef typename TestFixture::vertices_size_type vertices_size_type;
	typedef typename TestFixture::graph_type			graph_type;

	graph_type a;
   vertices_size_type vs = num_vertices(a);
   ASSERT_EQ(vs, 0);
	add_vertex(a);
	vs = num_vertices(a);
   ASSERT_EQ(vs, 1);
}
TYPED_TEST(GraphTest, test_num_vertices_3) 
{
	typedef typename TestFixture::vertices_size_type vertices_size_type;
	typedef typename TestFixture::graph_type			graph_type;

	graph_type a;
   vertices_size_type vs = num_vertices(a);
   ASSERT_EQ(vs, 0);
	add_edge(434, 34, a);
	vs = num_vertices(a);
   ASSERT_EQ(vs, 435);
}

// -----------
// test_source
// -----------

TYPED_TEST(GraphTest, test_source)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = source(this->edAB, this->g);
	ASSERT_EQ(vd, this->vdA);
}

// -----------
// test_target
// -----------

TYPED_TEST(GraphTest, test_target)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;

	vertex_descriptor vd = target(this->edAB, this->g);
	ASSERT_EQ(vd, this->vdB);
}

// -----------
// test_vertex
// -----------

TYPED_TEST(GraphTest, test_vertex_1)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;

	vertex_descriptor vd = vertex(0, this->g);
	ASSERT_EQ(vd, this->vdA);
}

TYPED_TEST(GraphTest, test_vertex_2)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;

	vertex_descriptor vd = vertex(3, this->g);
	ASSERT_EQ(vd, this->vdD);
}

TYPED_TEST(GraphTest, test_vertex_3)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;

	vertex_descriptor vd = vertex(5, this->g);
	ASSERT_EQ(vd, this->vdF);
}

// -------------
// test_vertices
// -------------

TYPED_TEST(GraphTest, test_vertices_1)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::vertex_iterator	vertex_iterator;

	std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
	vertex_iterator                             b = p.first;
	vertex_iterator                             e = p.second;
	ASSERT_NE(b, e);
	if (b != e)
	{
		vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdA);
	}
	++b;
	if (b != e)
	{
		vertex_descriptor vd = *b;
		ASSERT_EQ(vd, this->vdB);
	}
}

TYPED_TEST(GraphTest, test_vertices_2)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::vertex_iterator	vertex_iterator;

	std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
	vertex_iterator                             b = p.first;
	vertex_iterator                             e = p.second;
	ASSERT_NE(b, e);
	vertex_descriptor vd = *b;
	ASSERT_EQ(*b, this->vdA);
	b++;
	ASSERT_EQ(*b, this->vdB);
	b++;
	ASSERT_EQ(*b, this->vdC);
	b++;
	ASSERT_EQ(*b, this->vdD);
	b++;
	ASSERT_EQ(*b, this->vdE);
	b++;
	ASSERT_EQ(*b, this->vdF);
	b++;
	ASSERT_EQ(*b, this->vdG);
	b++;
	ASSERT_EQ(*b, this->vdH);
	b++;
	ASSERT_EQ(b, e);
}

TYPED_TEST(GraphTest, test_vertices_3)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::vertex_iterator	vertex_iterator;
	typedef typename TestFixture::graph_type			graph_type;

	graph_type a;

	std::pair<vertex_iterator, vertex_iterator> p = vertices(a);
	ASSERT_EQ(p.first, p.second);
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(GraphTest, test_has_cycle_1){
	ASSERT_TRUE(has_cycle(this->g));}

TYPED_TEST(GraphTest, test_has_cycle2)
{
	this->SetUpAcyclic();	
	ASSERT_FALSE(has_cycle(this->dag));
}

TYPED_TEST(GraphTest, test_has_cycle3)
{
	typedef typename TestFixture::graph_type			graph_type;
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edge_descriptor   edge_descriptor;

	graph_type a;

   vertex_descriptor vdA;
   vertex_descriptor vdB;
   vertex_descriptor vdC;
   vertex_descriptor vdD;
   vertex_descriptor vdE;
   vertex_descriptor vdF;
   vertex_descriptor vdG;
   vertex_descriptor vdH;

   vdA  = add_vertex(a);
	vdB  = add_vertex(a);
	vdC  = add_vertex(a);
	vdD  = add_vertex(a);
	vdE  = add_vertex(a);
	vdF  = add_vertex(a);
	vdG  = add_vertex(a);
	vdH  = add_vertex(a);	

	ASSERT_FALSE(has_cycle(a));
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST(GraphTest, test_topological_sort_1)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;

	std::ostringstream out;
	try
	{
		topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
		ASSERT_TRUE(false);
	}	
	catch(boost::not_a_dag& e)
	{
		ASSERT_TRUE(has_cycle(this->g));
	}
}


TYPED_TEST(GraphTest, test_topological_sort_2)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	
	this->SetUpAcyclic();
	std::ostringstream out;
	try
	{
		topological_sort(this->dag, std::ostream_iterator<vertex_descriptor>(out, " "));
		ASSERT_EQ(out.str(), "4 3 1 2 0 7 5 6 ");
	}	
	catch(boost::not_a_dag& e)
	{
		ASSERT_TRUE(false);
	}
}

TYPED_TEST(GraphTest, test_topological_sort_3)
{
	typedef typename TestFixture::graph_type			graph_type;
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edge_descriptor   edge_descriptor;

	graph_type a;

   vertex_descriptor vdA;
   vertex_descriptor vdB;
   vertex_descriptor vdC;
   vertex_descriptor vdD;

   vdA  = add_vertex(a);
	vdB  = add_vertex(a);
	vdC  = add_vertex(a);
	vdD  = add_vertex(a);
	add_edge(vdA, vdD, a);

	std::ostringstream out;
	try
	{
		topological_sort(a, std::ostream_iterator<vertex_descriptor>(out, " "));
		ASSERT_EQ(out.str(), "3 0 1 2 ");
	}	
	catch(boost::not_a_dag& e)
	{
		ASSERT_TRUE(false);
	}
}

TYPED_TEST(GraphTest, test_topological_sort_4)
{
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;

	std::ostringstream out;
	try
	{
		topological_sort(this->dag, std::ostream_iterator<vertex_descriptor>(out, " "));
		ASSERT_EQ(out.str(), "");
	}	
	catch(boost::not_a_dag& e)
	{
		ASSERT_TRUE(false);
	}
}
