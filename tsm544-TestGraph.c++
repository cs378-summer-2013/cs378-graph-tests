// TestGraph
#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <string>   // string

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

// Include Graph's required headers before the compiler defines
#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include <list>    // list
#include <set>     // set
#include <queue>   // priority_queue
#include <map>     // map

#define private public
#define protected public
#define class struct
#include "Graph.h"

// These are implementation dependent tests
// This class contains some typedefs to make the constructor tests more readable
class ImplementationTest : public testing::Test {
protected:
	typedef Graph graph_type;
	typedef typename graph_type::vertex_descriptor  vertex_descriptor;
	typedef typename graph_type::edge_descriptor    edge_descriptor;

	typedef typename graph_type::vertex_iterator    vertex_iterator;
	typedef typename graph_type::edge_iterator      edge_iterator;
	typedef typename graph_type::adjacency_iterator adjacency_iterator;

	typedef typename graph_type::vertices_size_type vertices_size_type;
	typedef typename graph_type::edges_size_type    edges_size_type;

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
    edge_descriptor edHA;

    void SetUpCyclic () {
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

    void SetUpNonCyclic() {
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

    void SetUpComplexCyclic () {
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
        edHA = add_edge(vdH, vdA, g).first;
    }
};

// --- constructor ---
TEST_F(ImplementationTest, DefaultConstructor) {
	ASSERT_EQ(0, g.myVertexList.size());
}

TEST_F(ImplementationTest, AddEdgeTest1) {
	vertex_descriptor p = add_vertex(g);
	EXPECT_EQ(0, p);
	EXPECT_EQ(1, g.myVertexList.size());
	EXPECT_EQ(1, g.myVertexList[p].size());
}

TEST_F(ImplementationTest, AddEdgeTest2) {
	for (int i = 0; i < 10; i++) {
		vertex_descriptor p = add_vertex(g);
		EXPECT_EQ(i, p);
		EXPECT_EQ(i + 1, g.myVertexList.size());
		EXPECT_EQ(1, g.myVertexList[p].size());
	}
}

// --- has cycle ---

TEST_F(ImplementationTest, HasCycle1) {
	SetUpCyclic();
	ASSERT_TRUE(has_cycle(g));
}

TEST_F(ImplementationTest, HasCycle2) {
	SetUpNonCyclic();
	ASSERT_FALSE(has_cycle(g));
}

TEST_F(ImplementationTest, HasCycle3) {
	SetUpComplexCyclic();
	ASSERT_TRUE(has_cycle(g));
}

// These are interface tests
typedef testing::Types<Graph, boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> > graphs;

template <typename T>
class InterfaceTest : public testing::Test {
protected:
    // --- typedefs ---

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    graph_type g;
    graph_type non_cyclic_graph;

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

    // --- setUp ---
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

    void SetUpNonCyclic() {
        vdA  = add_vertex(non_cyclic_graph);
        vdB  = add_vertex(non_cyclic_graph);
        vdC  = add_vertex(non_cyclic_graph);
        vdD  = add_vertex(non_cyclic_graph);
        vdE  = add_vertex(non_cyclic_graph);
        vdF  = add_vertex(non_cyclic_graph);
        vdG  = add_vertex(non_cyclic_graph);
        vdH  = add_vertex(non_cyclic_graph);

        edAB = add_edge(vdA, vdB, non_cyclic_graph).first;
        edAC = add_edge(vdA, vdC, non_cyclic_graph).first;
        edAE = add_edge(vdA, vdE, non_cyclic_graph).first;
        edBD = add_edge(vdB, vdD, non_cyclic_graph).first;
        edBE = add_edge(vdB, vdE, non_cyclic_graph).first;
        edCD = add_edge(vdC, vdD, non_cyclic_graph).first;
        edDE = add_edge(vdD, vdE, non_cyclic_graph).first;
        edDF = add_edge(vdD, vdF, non_cyclic_graph).first;
        edFH = add_edge(vdF, vdH, non_cyclic_graph).first;
        edGH = add_edge(vdG, vdH, non_cyclic_graph).first;
    }
};

TYPED_TEST_CASE(InterfaceTest, graphs);

// --- add_vertex ---

TYPED_TEST(InterfaceTest, AddVertexTest1) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor p = add_vertex(this->g);
	EXPECT_EQ(8, p);
}

TYPED_TEST(InterfaceTest, AddVertexTest2) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor p = add_vertex(this->g);
	ASSERT_EQ(8, p);
	p = add_vertex(this->g);
	ASSERT_EQ(9, p);
}

TYPED_TEST(InterfaceTest, AddVertexTest3) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor p = add_vertex(this->g);
	EXPECT_EQ(8, p);
	p = add_vertex(this->g);
	ASSERT_EQ(9, p);
	p = add_vertex(this->g);
	ASSERT_EQ(10, p);
}

// --- add_edge ---

TYPED_TEST(InterfaceTest, AddEdgeTest1) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
	EXPECT_EQ(this->edAB, p.first);
	EXPECT_FALSE(p.second);
}

TYPED_TEST(InterfaceTest, AddEdgeTest2) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
	EXPECT_TRUE(p.second);
}

TYPED_TEST(InterfaceTest, AddEdgeTest3) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
	ASSERT_TRUE(p.second);

	std::pair<edge_descriptor, bool> p2 = add_edge(this->vdA, this->vdH, this->g);
	EXPECT_EQ(p.first, p2.first);
	EXPECT_FALSE(p2.second);
}

// --- ajacent_vertices ---

TYPED_TEST(InterfaceTest, AdjacentVerticesTest1) {
	typedef typename TestFixture::adjacency_iterator adjacency_iterator;
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
	adjacency_iterator b = p.first;
	adjacency_iterator e = p.second;

	ASSERT_NE(e, b);
	if (b != e) {
	    vertex_descriptor vd = *b;
	    EXPECT_EQ(this->vdB, vd);
	}
	++b;
	if (b != e) {
	    vertex_descriptor vd = *b;
	    EXPECT_EQ(this->vdC, vd);
	}
}

TYPED_TEST(InterfaceTest, AdjacentVerticesTest2) {
	typedef typename TestFixture::adjacency_iterator adjacency_iterator;
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
	adjacency_iterator b = p.first;
	adjacency_iterator e = p.second;

	ASSERT_NE(e, b);
	if (b != e) {
	    vertex_descriptor vd = *b;
	    EXPECT_EQ(this->vdB, vd);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
	    vertex_descriptor vd = *b;
	    EXPECT_EQ(this->vdC, vd);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
	    vertex_descriptor vd = *b;
	    EXPECT_EQ(this->vdE, vd);
	}
}

TYPED_TEST(InterfaceTest, AdjacentVerticesTest3) {
	typedef typename TestFixture::adjacency_iterator adjacency_iterator;
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdB, this->g);
	adjacency_iterator b = p.first;
	adjacency_iterator e = p.second;

	ASSERT_NE(e, b);
	if (b != e) {
	    vertex_descriptor vd = *b;
	    EXPECT_EQ(this->vdD, vd);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
	    vertex_descriptor vd = *b;
	    EXPECT_EQ(this->vdE, vd);
	}
}

// --- edge ---

TYPED_TEST(InterfaceTest, EdgeTest1) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
	EXPECT_EQ(this->edAB, p.first);
	EXPECT_TRUE(p.second);
}

TYPED_TEST(InterfaceTest, EdgeTest2) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = edge(this->vdA, this->vdH, this->g);
	ASSERT_FALSE(p.second);
}

TYPED_TEST(InterfaceTest, EdgeTest3) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	std::pair<edge_descriptor, bool> p = edge(this->vdB, this->vdD, this->g);
	EXPECT_EQ(this->edBD, p.first);
	EXPECT_TRUE(p.second);
}

// --- edges ---

TYPED_TEST(InterfaceTest, EdgesTest1) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	typedef typename TestFixture::edge_iterator edge_iterator;
	std::pair<edge_iterator, edge_iterator> p = edges(this->g);
	edge_iterator                           b = p.first;
	edge_iterator                           e = p.second;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edAB, ed);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edAC, ed);
	}
}

TYPED_TEST(InterfaceTest, EdgesTest2) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	typedef typename TestFixture::edge_iterator edge_iterator;
	std::pair<edge_iterator, edge_iterator> p = edges(this->g);
	edge_iterator                           b = p.first;
	edge_iterator                           e = p.second;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edAB, ed);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edAC, ed);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edAE, ed);
	}
}

TYPED_TEST(InterfaceTest, EdgesTest3) {
	typedef typename TestFixture::edge_descriptor edge_descriptor;
	typedef typename TestFixture::edge_iterator edge_iterator;
	std::pair<edge_iterator, edge_iterator> p = edges(this->g);
	edge_iterator                           b = p.first;
	edge_iterator                           e = p.second;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edAB, ed);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edAC, ed);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edAE, ed);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		edge_descriptor ed = *b;
		EXPECT_EQ(this->edBD, ed);
	}
}

// --- num_edges ---

TYPED_TEST(InterfaceTest, NumEdges1) {
	typedef typename TestFixture::edges_size_type edges_size_type;
	edges_size_type es = num_edges(this->g);
	EXPECT_EQ(11, es);
}

TYPED_TEST(InterfaceTest, NumEdges2) {
	typedef typename TestFixture::graph_type graph_type;
	typedef typename TestFixture::edges_size_type edges_size_type;
	graph_type g2;
	edges_size_type es = num_edges(g2);
	EXPECT_EQ(0, es);
}

TYPED_TEST(InterfaceTest, NumEdges3) {
	typedef typename TestFixture::graph_type graph_type;
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::edges_size_type edges_size_type;
	graph_type g2;
	vertex_descriptor ed1 = add_vertex(g2);
	vertex_descriptor ed2 = add_vertex(g2);
	add_edge(ed1, ed2, g2);
	edges_size_type es = num_edges(g2);
	EXPECT_EQ(1, es);
}

// --- num vertices ---

TYPED_TEST(InterfaceTest, NumVertices1) {
	typedef typename TestFixture::vertices_size_type vertices_size_type;
	vertices_size_type vs = num_vertices(this->g);
	EXPECT_EQ(8, vs);
}

TYPED_TEST(InterfaceTest, NumVertices2) {
	typedef typename TestFixture::graph_type graph_type;
	typedef typename TestFixture::vertices_size_type vertices_size_type;
	graph_type g2;
	vertices_size_type vs = num_vertices(g2);
	EXPECT_EQ(0, vs);
}

TYPED_TEST(InterfaceTest, NumVertices3) {
	typedef typename TestFixture::graph_type graph_type;
	typedef typename TestFixture::vertices_size_type vertices_size_type;
	graph_type g2;
	add_vertex(g2);
	vertices_size_type vs = num_vertices(g2);
	EXPECT_EQ(1, vs);
}

// --- source ---

TYPED_TEST(InterfaceTest, Source1) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = source(this->edBD, this->g);
	EXPECT_EQ(this->vdB, vd);
}

TYPED_TEST(InterfaceTest, Source2) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = source(this->edGH, this->g);
	EXPECT_EQ(this->vdG, vd);
}

TYPED_TEST(InterfaceTest, Source3) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = source(this->edAB, this->g);
	EXPECT_EQ(this->vdA, vd);
}

// --- target ---

TYPED_TEST(InterfaceTest, Target1) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = target(this->edAB, this->g);
	EXPECT_EQ(this->vdB, vd);
}

TYPED_TEST(InterfaceTest, Target2) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = target(this->edBD, this->g);
	EXPECT_EQ(this->vdD, vd);
}

TYPED_TEST(InterfaceTest, Target3) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = target(this->edGH, this->g);
	EXPECT_EQ(this->vdH, vd);
}

// --- vertex ---

TYPED_TEST(InterfaceTest, Vertex1) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = vertex(0, this->g);
	EXPECT_EQ(this->vdA, vd);
}

TYPED_TEST(InterfaceTest, Vertex2) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = vertex(1, this->g);
	EXPECT_EQ(this->vdB, vd);
}

TYPED_TEST(InterfaceTest, Vertex3) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	vertex_descriptor vd = vertex(2, this->g);
	EXPECT_EQ(this->vdC, vd);
}

// --- vertices ---

TYPED_TEST(InterfaceTest, Vertices1) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::vertex_iterator vertex_iterator;
	std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
	vertex_iterator                             b = p.first;
	vertex_iterator                             e = p.second;
	ASSERT_NE(e, b);
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdA, vd);
	}
	++b;
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdB, vd);
	}
}

TYPED_TEST(InterfaceTest, Vertices2) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::vertex_iterator vertex_iterator;
	std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
	vertex_iterator                             b = p.first;
	vertex_iterator                             e = p.second;
	ASSERT_NE(e, b);
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdA, vd);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdB, vd);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdC, vd);
	}
}

TYPED_TEST(InterfaceTest, Vertices3) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	typedef typename TestFixture::vertex_iterator vertex_iterator;
	std::pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
	vertex_iterator                             b = p.first;
	vertex_iterator                             e = p.second;
	ASSERT_NE(e, b);
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdA, vd);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdB, vd);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdC, vd);
	}
	++b;
	ASSERT_NE(e, b);
	if (b != e) {
		vertex_descriptor vd = *b;
		EXPECT_EQ(this->vdD, vd);
	}
}

// --- topological_sort ---

TYPED_TEST(InterfaceTest, TopologicalSort1) {
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::ostringstream out;
	try {
		topological_sort(this->g, std::ostream_iterator<vertex_descriptor>(out, " "));
		ASSERT_TRUE(false);
	}
	catch (boost::not_a_dag& e) {
		ASSERT_TRUE(has_cycle(this->g));
	}
}

TYPED_TEST(InterfaceTest, TopologicalSort2) {
	this->SetUpNonCyclic();
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::ostringstream out;
	try {
		topological_sort(this->non_cyclic_graph, std::ostream_iterator<vertex_descriptor>(out, " "));
		ASSERT_EQ(std::string("4 7 5 3 1 2 0 6 "), out.str());
	}
	catch (boost::not_a_dag& e) {
		ASSERT_TRUE(false);
	}
}

TYPED_TEST(InterfaceTest, TopologicalSort3) {
	typedef typename TestFixture::graph_type graph_type;
	typedef typename TestFixture::vertex_descriptor vertex_descriptor;
	std::ostringstream out;
	graph_type g2;
	try {
		topological_sort(this->non_cyclic_graph, std::ostream_iterator<vertex_descriptor>(out, " "));
		ASSERT_EQ(std::string(""), out.str());
	}
	catch (boost::not_a_dag& e) {
		ASSERT_TRUE(false);
	}
}
// TODO make interface tests for Graph and adjacency_list<setS, vecS, directedS>
