// ---------------------------
// TestGraph.c++
// Implemented by:
// Sophia Hernandez eid: smh3665
// Jose Coello eid: jlc3938
// -----------------------------

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

#define private public

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp, NULL
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <cstdlib>   //rand
#include <climits>   //INT_MAX
#include <iostream>
#include <utility>   //pair    

#include "gtest/gtest.h" //g test

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "Graph.h"

// ---------
// TestGraph
// ---------
using namespace std;

template <typename T>
class TypeTest : public testing::Test 
{
    
    protected:

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
        graph_type g; // cycle
        graph_type g2; //no cycle
        graph_type g3; //no edges
        graph_type g4; //default

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

        virtual void SetUp () {
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

        virtual void SetUp_NoCycle () {
            vdA  = add_vertex(g2);
            vdB  = add_vertex(g2);
            vdC  = add_vertex(g2);
            vdD  = add_vertex(g2);
            vdE  = add_vertex(g2);
            vdF  = add_vertex(g2);
            vdG  = add_vertex(g2);
            vdH  = add_vertex(g2);
            edAB = add_edge(vdA, vdB, g2).first;
            edAC = add_edge(vdA, vdC, g2).first;
            edAE = add_edge(vdA, vdE, g2).first;
            edBD = add_edge(vdB, vdD, g2).first;
            edBE = add_edge(vdB, vdE, g2).first;
            edCD = add_edge(vdC, vdD, g2).first;
            edDE = add_edge(vdD, vdE, g2).first;
            edDF = add_edge(vdD, vdF, g2).first;
            edFH = add_edge(vdF, vdH, g2).first;
            edGH = add_edge(vdG, vdH, g2).first;
        }

        virtual void SetUp_NoEdges () {
            vdA  = add_vertex(g3);
            vdB  = add_vertex(g3);
            vdC  = add_vertex(g3);
            vdD  = add_vertex(g3);
        }

};

typedef testing::Types< Graph, boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> > MyTypes;

TYPED_TEST_CASE(TypeTest, MyTypes);

// ------------------------
// test_default_constructor
// ------------------------

TYPED_TEST(TypeTest, test_constructor)
{
    typedef typename TestFixture::graph_type graph_type;
    graph_type g;
    ASSERT_TRUE(num_vertices(g) == 0);
    ASSERT_TRUE(num_edges(g) == 0);
}

// -------------
// test_add_edge
// -------------

TYPED_TEST(TypeTest , test_add_edges_1)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
     pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g);
     ASSERT_TRUE(p.first == this->edAB);
     ASSERT_FALSE(p.second);
}

TYPED_TEST(TypeTest , test_add_edges_2)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
     pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdH, this->g);
     ASSERT_TRUE(p.second);
}   


TYPED_TEST(TypeTest , test_add_edges_3)
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    vertex_descriptor v = add_vertex(this->g);
     pair<edge_descriptor, bool> p = add_edge(this->vdA, v, this->g);
     ASSERT_TRUE(p.second);
}

TYPED_TEST(TypeTest , test_add_edges_4)
{
    this->SetUp_NoEdges();
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

     pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g3);
     ASSERT_TRUE(p.second);
} 

// ----------------------
// test_adjacent_vertices
// ---------------------- 


TYPED_TEST (TypeTest, test_adjacent_vertices_vdA)  
{
        typedef typename TestFixture::adjacency_iterator adjacency_iterator;
        typedef typename TestFixture::vertex_descriptor vertex_descriptor;
        pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdA, this->g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        ASSERT_NE(b , e);
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdB);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdC);}
}

TYPED_TEST (TypeTest, test_adjacent_vertices_vdB)  
{
        typedef typename TestFixture::adjacency_iterator adjacency_iterator;
        typedef typename TestFixture::vertex_descriptor vertex_descriptor;
        
        pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdB, this->g);
        
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        
        ASSERT_NE(b , e);
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdD);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            ASSERT_TRUE(vd == this->vdE);}
}

TYPED_TEST (TypeTest, test_adjacent_vertices_vdH)  
{
        typedef typename TestFixture::adjacency_iterator adjacency_iterator;
        typedef typename TestFixture::vertex_descriptor vertex_descriptor;
        
        pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(this->vdH, this->g);
        
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        
        ASSERT_EQ(b , e);
}

// ---------
// test_edge
// ---------

TYPED_TEST(TypeTest, test_edge) 
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = edge(this->vdA, this->vdB, this->g);
    ASSERT_TRUE(p.first  == this->edAB);
    ASSERT_TRUE(p.second );
}

TYPED_TEST(TypeTest, test_edge_not_an_edge) 
{
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    pair<edge_descriptor, bool> p = edge(this->vdA, this->vdH, this->g);
    ASSERT_FALSE(p.second );
}

// ----------
// test_edges
// ----------

TYPED_TEST(TypeTest, test_edges)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    ASSERT_NE(b , e);
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_TRUE(ed == this->edAB);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_TRUE(ed == this->edAC);}
}

TYPED_TEST(TypeTest, test_edges_no_edges)
{
    this->SetUp_NoEdges();
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g3);
    ASSERT_EQ(p.first, p.second);
}
    
TYPED_TEST(TypeTest, test_edges_default)
{
    typedef typename TestFixture::edge_iterator edge_iterator;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    std::pair<edge_iterator, edge_iterator> p = edges(this->g4);
    ASSERT_EQ(p.first, p.second);
}

// --------------
// test_num_edges
// --------------

TYPED_TEST (TypeTest, test_num_edges) 
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    edges_size_type es = num_edges(this->g);
    ASSERT_TRUE(es == 11);
}

TYPED_TEST (TypeTest, test_num_edges_no_cycle) 
{
    this->SetUp_NoCycle();
    typedef typename TestFixture::edges_size_type edges_size_type;
    edges_size_type es = num_edges(this->g2);
    ASSERT_TRUE(es == 10);
}

TYPED_TEST (TypeTest, test_num_edges_no_edges) 
{
    this->SetUp_NoEdges();
    typedef typename TestFixture::edges_size_type edges_size_type;
    edges_size_type es = num_edges(this->g3);
    ASSERT_TRUE(es == 0);
}

TYPED_TEST (TypeTest, test_num_edges_after_add) 
{
    this->SetUp_NoEdges();
    typedef typename TestFixture::edges_size_type edges_size_type;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    edges_size_type es = num_edges(this->g3);
    ASSERT_TRUE(es == 0);

    std::pair<edge_descriptor, bool> p = add_edge(this->vdA, this->vdB, this->g3);
   
    ASSERT_TRUE(p.second);

    es = num_edges(this->g3);
    ASSERT_TRUE(es == 1);
}

TYPED_TEST (TypeTest, test_num_edges_default)
{
    typedef typename TestFixture::edges_size_type edges_size_type;
    typedef typename TestFixture::edge_descriptor edge_descriptor;
    ASSERT_EQ(0, num_edges(this->g4));
}
// -----------------
// test_num_vertices
// -----------------

TYPED_TEST (TypeTest, test_num_vertices )
 {
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    vertices_size_type vs = num_vertices(this->g);
    ASSERT_TRUE(vs == 8);
}

TYPED_TEST (TypeTest, test_num_vertices_after_add )
 {
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;

    vertices_size_type vs = num_vertices(this->g);
    ASSERT_TRUE(vs == 8);
    add_vertex(this->g);
    
    vs = num_vertices(this->g);
    ASSERT_TRUE(vs == 9);
}

TYPED_TEST (TypeTest, test_num_vertices_no_edges )
 {
    this->SetUp_NoEdges();
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    vertices_size_type vs = num_vertices(this->g3);
    ASSERT_TRUE(vs == 4);
}

TYPED_TEST (TypeTest, test_num_vertices_default )
 {
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    vertices_size_type vs = num_vertices(this->g4);
    ASSERT_TRUE(vs == 0);
}

// -----------
// test_source
// -----------

TYPED_TEST(TypeTest, test_source_no_cycle ) 
{
    this->SetUp_NoCycle();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edDF, this->g2);
    ASSERT_TRUE(vd == this->vdD);
}

TYPED_TEST(TypeTest, test_source_with_cycle ) 
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = source(this->edAB, this->g);
    ASSERT_TRUE(vd == this->vdA);
    vd = source(this->edDF, this->g);
    ASSERT_TRUE(vd == this->vdD);
    vd = source(this->edFD, this->g);
    ASSERT_TRUE(vd == this->vdF);
}

// -----------
// test_target
// -----------

TYPED_TEST(TypeTest, test_target ) 
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edAB, this->g);
    ASSERT_TRUE(vd == this->vdB);
}

TYPED_TEST(TypeTest, test_target_no_cycle)
{
    this->SetUp_NoCycle();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edDF, this->g2);
    ASSERT_TRUE(vd == this->vdF);
}

TYPED_TEST(TypeTest, test_target_with_cycle)
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = target(this->edFD, this->g);
    ASSERT_TRUE(vd == this->vdD);
}

// -----------
// test_vertex
// -----------

TYPED_TEST (TypeTest, test_vertex )
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(0, this->g);
    ASSERT_TRUE(vd == this->vdA);
}

TYPED_TEST (TypeTest, test_vertex_no_cyle )
{
    this->SetUp_NoCycle();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(1, this->g2);
    ASSERT_TRUE(vd == this->vdB);
}

TYPED_TEST (TypeTest, test_vertex_no_edges )
{
    this->SetUp_NoEdges();
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    vertex_descriptor vd = vertex(7, this->g3);
    
    ASSERT_TRUE(vd == 7);
}

// -------------
// test_vertices
// -------------


TYPED_TEST(TypeTest, test_vertices ) 
{

    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    pair<vertex_iterator, vertex_iterator> p = vertices(this->g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(b , e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_TRUE(vd == this->vdA);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_TRUE(vd == this->vdB);}
}

TYPED_TEST(TypeTest, test_vertices_no_edges ) 
{
    this->SetUp_NoEdges();
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    pair<vertex_iterator, vertex_iterator> p = vertices(this->g3);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_NE(b , e);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_TRUE(vd == this->vdA);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_TRUE(vd == this->vdB);
    }
    ++b;
    if(b != e) {
        vertex_descriptor vd = *b;
        ASSERT_TRUE(vd == this->vdC);
    }
    ++b;
    if(b != e){
        vertex_descriptor vd = *b;
        ASSERT_TRUE(vd == this->vdD);
    }
    ++b;
    ASSERT_EQ(b, e);
}

TYPED_TEST(TypeTest, test_vertices_default ) 
{
    
    typedef typename TestFixture::vertex_iterator vertex_iterator;
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    pair<vertex_iterator, vertex_iterator> p = vertices(this->g4);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    ASSERT_EQ(b , e);
    
}

// --------------
// test_has_cycle
// --------------

TYPED_TEST(TypeTest, test_has_cycle ) 
{
    this->SetUp();
    ASSERT_TRUE(has_cycle(this->g));
}

TYPED_TEST(TypeTest, test_has_cycle_no_cycle ) 
{
    this->SetUp_NoCycle();
    ASSERT_FALSE(has_cycle(this->g2));
}

TYPED_TEST(TypeTest, test_has_cycle_no_cycle_no_edges ) 
{
    this->SetUp_NoEdges();
    ASSERT_FALSE(has_cycle(this->g3));
}

TYPED_TEST(TypeTest, test_has_cycle_no_cycle_default ) 
{
   
    ASSERT_FALSE(has_cycle(this->g4));
}

TYPED_TEST(TypeTest, test_has_cycle_many_cycles)
{
    this->SetUp_NoCycle();
    add_edge(this->vdH, this->vdA, this->g2);
    ASSERT_TRUE(has_cycle(this->g2));
}

// ---------------------
// test_topological_sort
// ---------------------

TYPED_TEST (TypeTest, test_topological_sort_with_cycle )
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    ostringstream out;
    try{
        topological_sort(this->g, ostream_iterator<vertex_descriptor>(out, " "));

    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(string(e.what()) == "The graph must be a DAG.");
    }
       // ASSERT_TRUE(out.str() == "2 0 1 ");
}

TYPED_TEST (TypeTest, test_topological_sort_no_cycle )
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->SetUp_NoCycle();

    ostringstream out;
    try{
        topological_sort(this->g2, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string("4 7 5 3 1 2 0 6 "), out.str());
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(false);
    }
}


TYPED_TEST (TypeTest, test_topological_sort_no_edges )
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    typedef typename TestFixture::graph_type graph_type;
    this->SetUp_NoEdges();

    ostringstream out;
    try{
        topological_sort(this->g3, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string("0 1 2 3 "), out.str());
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(false);
    }
}

TYPED_TEST (TypeTest, test_topological_sort_default )
{
    typedef typename TestFixture::vertex_descriptor vertex_descriptor;
    

    ostringstream out;
    try{
        topological_sort(this->g4, ostream_iterator<vertex_descriptor>(out, " "));
        ASSERT_EQ(std::string(""), out.str());
    }
    catch(boost::not_a_dag& e){
        ASSERT_TRUE(false);
    }
}
