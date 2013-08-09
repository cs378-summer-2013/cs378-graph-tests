// A unit test source that makes use of gtest
#include <iostream>         // ostream
#include <vector>           // vector
#include <algorithm>        // equal
#include <deque>			//deque
#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

/*
 * This is the gtest header.
 * The usual installation is in /usr/include/
 *
 * It's already installed there on the CS machines,
 * but if you've installed it elsewhere on your own,
 * there's no need to change this line.
 *
 * You just need to make sure to include the folder where
 * you put the gtest folder when compiling.
 */
#include "gtest/gtest.h"
#include "Graph.h"


TEST(constructor, constructor_1)
{
	Graph g = Graph();
	ASSERT_EQ(num_vertices(g), num_edges(g));

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> bg = 
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>();
	ASSERT_EQ(num_vertices(bg), num_edges(bg));
}	


TEST(constructor, constructor_2)
{
	Graph g = Graph();
	ASSERT_EQ(std::distance(vertices(g).first,vertices(g).second), 0);

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> bg = 
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>();
	ASSERT_EQ(std::distance(vertices(bg).first,vertices(bg).second), 0);
}	

TEST(constructor, constructor_3)
{
	Graph g = Graph();
	ASSERT_EQ(std::distance(edges(g).first, edges(g).second), 0);

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> bg = 
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>();
	ASSERT_EQ(std::distance(edges(bg).first, edges(bg).second), 0);
}





class GraphTest : public testing::Test 
{
    	
	
    typedef typename Graph::vertex_descriptor  vertex_descriptor;
    typedef typename Graph::edge_descriptor    edge_descriptor;

    typedef typename Graph::vertex_iterator    vertex_iterator;
    typedef typename Graph::edge_iterator      edge_iterator;
    typedef typename Graph::adjacency_iterator adjacency_iterator;

    typedef typename Graph::vertices_size_type vertices_size_type;
    typedef typename Graph::edges_size_type    edges_size_type;



	protected:
	Graph g;
	vertex_descriptor a;
	vertex_descriptor b;
	edge_descriptor edAB;




	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> bg;
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_descriptor c;
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_descriptor d;
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_descriptor edCD;


	virtual void SetUp() 
	{
		a = add_vertex(g);
		b = add_vertex(g);
		edAB = add_edge(a, b, g).first;




		c = add_vertex(bg);
		d = add_vertex(bg);
		edCD =  add_edge(c, d, bg).first;


	}

};

TEST_F(GraphTest, add_vertex_1)
{
	ASSERT_TRUE( num_vertices(g) == num_vertices(bg));
	ASSERT_TRUE( add_vertex(g) == add_vertex(bg) );
	ASSERT_TRUE( add_vertex(g) == add_vertex(bg));

	ASSERT_TRUE( num_vertices(g) == num_vertices(bg));
	ASSERT_TRUE( num_vertices(g) == 4);
	ASSERT_TRUE( num_vertices(bg) == 4);

}


TEST_F(GraphTest, add_vertex_2)
{
	for(int i = 0; i < 100; i++)
	{
		add_vertex(g);
		add_vertex(bg);
	}

	ASSERT_TRUE( num_vertices(g) == num_vertices(bg));
	ASSERT_TRUE( num_vertices(g) == 102);
	ASSERT_TRUE( num_vertices(bg) == 102);

}



TEST_F(GraphTest, add_vertex_3)
{
	Graph g2 = Graph();
	
	boost::adjacency_list<boost::listS, boost::vecS> bg2 = boost::adjacency_list<boost::listS, boost::vecS>();
	ASSERT_TRUE( num_vertices(g2) == 0);
	add_vertex(g2);
	ASSERT_EQ( num_vertices(g2), 1);

	ASSERT_TRUE( num_vertices(bg2) == 0);
	add_vertex(bg2);
	ASSERT_EQ( num_vertices(bg2), 1);

}




TEST_F(GraphTest, add_edge_1)
{
	ASSERT_TRUE( add_edge(0,1, g).second == false);
	ASSERT_TRUE( add_edge(1,0, g).second == true);

	ASSERT_TRUE( add_edge(0,1, bg).second == false);
	ASSERT_TRUE( add_edge(1,0, bg).second == true);

}

TEST_F(GraphTest, add_edge_2)
{
	ASSERT_TRUE( add_edge(0,1, g).second == false);
	ASSERT_TRUE( add_edge(1,0, g).second == true);
	ASSERT_TRUE( add_edge(1,0, g).second == false);

	ASSERT_TRUE( add_edge(0,1, bg).second == false);
	ASSERT_TRUE( add_edge(1,0, bg).second == true);
	ASSERT_TRUE( add_edge(1,0, bg).second == false);

}

TEST_F(GraphTest, add_edge_3)
{

	for(int i = 100; i < 200; i++)
	{
		
	}
	ASSERT_TRUE( add_edge(1,0, g).second == true);
	ASSERT_TRUE( add_edge(1,0, g).second == false);

	ASSERT_TRUE( add_edge(1,0, bg).second == true);
	ASSERT_TRUE( add_edge(1,0, bg).second == false);

}


TEST_F(GraphTest, adjacent_vertices_1)
{

	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> p = adjacent_vertices(a,g);
	Graph::adjacency_iterator begin1 = p.first;
	Graph::adjacency_iterator end1 = p.second;


	int count = 0;
	while(begin1 != end1)
	{
		ASSERT_EQ(*begin1 , b);
		++begin1; ++count;
	}


	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::adjacency_iterator b1;
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::adjacency_iterator e1;

	b1 =  adjacent_vertices(c, bg).first;
	e1 =  adjacent_vertices(c, bg).second;

	int count2 = 0;
	while(b1 != e1)
	{
		ASSERT_EQ(*b1 ,d);
		++b1; ++count2;
	}


		ASSERT_EQ(count2, 1);

	
}



TEST_F(GraphTest, adjacent_vertices_2)
{

	add_edge(a, 100, g);



	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> p = adjacent_vertices(a,g);
	Graph::adjacency_iterator begin1 = p.first;
	Graph::adjacency_iterator end1 = p.second;

	ASSERT_EQ(*begin1++ , b);
	ASSERT_EQ(*begin1++, 100);
	ASSERT_EQ(begin1, end1);
    



	add_edge(c, 100, bg);

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::adjacency_iterator b1;
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::adjacency_iterator e1;

	b1 =  adjacent_vertices(c, bg).first;
	e1 =  adjacent_vertices(c, bg).second;
	

	ASSERT_EQ(*b1++ , d);
	ASSERT_EQ(*b1++, 100);
	ASSERT_EQ(b1, e1);



}



TEST_F(GraphTest, adjacent_vertices_3)
{


	for(int i = 0; i < 100; i++)
		add_edge(a, i + 100, g);



	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> p = adjacent_vertices(a,g);
	Graph::adjacency_iterator begin1 = p.first;
	Graph::adjacency_iterator end1 = p.second;
	
	ASSERT_EQ(std::distance(begin1, end1), 101);
    


	for(int i = 0; i < 100; i++)
		add_edge(c, i + 100, bg);


	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::adjacency_iterator b1;
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::adjacency_iterator e1;

	b1 =  adjacent_vertices(c, bg).first;
	e1 =  adjacent_vertices(c, bg).second;
	


	ASSERT_EQ(std::distance(b1, e1), 101);


}


TEST_F(GraphTest, edge_1)
{
	std::pair<Graph::edge_descriptor, bool> ed = edge(a, b, g);
	ASSERT_TRUE(ed.second);
	ASSERT_EQ(ed.first, edAB);


	std::pair<boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_descriptor, bool> ged = edge(c, d, bg);
	ASSERT_TRUE(ged.second);
	ASSERT_EQ(ged.first, edCD);

}


TEST_F(GraphTest, edge_2)
{
	std::pair<Graph::edge_descriptor, bool> ed = edge(a, 2, g);
	ASSERT_FALSE(ed.second);

	add_edge(a, 2, g);
	ed = edge(a, 2, g);
	ASSERT_TRUE(ed.second);

	std::pair<   boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_descriptor, bool> ged = edge(c, 2, bg);
	ASSERT_FALSE(ged.second);

	add_edge(c, 2, bg);
	ged = edge(c, 2, bg);
	ASSERT_TRUE(ged.second);
}


TEST_F(GraphTest, edge_3)
{

	for(int i = 100; i < 200; i++)
	{
		std::pair<Graph::edge_descriptor, bool> ed = edge(a, i, g);
		ASSERT_FALSE(ed.second);

		add_edge(a, i, g);
		ed = edge(a, i, g);
		ASSERT_TRUE(ed.second);
	}


	for(int i = 100; i < 200; i++)
	{

		std::pair<   boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_descriptor, bool> ged = edge(c, i, bg);	
		ASSERT_FALSE(ged.second);
		add_edge(a, i, bg);
		ged = edge(a, i, bg);
		ASSERT_TRUE(ged.second);
	}
}

TEST_F(GraphTest, edges_1)
{
	Graph t = Graph();
	Graph::edge_iterator b = edges(t).first;
	Graph::edge_iterator e = edges(t).second;
	ASSERT_EQ(b, e);


	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> gt = 	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>();
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_iterator b1 = edges(gt).first;
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_iterator e1 = edges(gt).second;
	ASSERT_EQ(b1, e1);

}

TEST_F(GraphTest, edges_2)
{
	Graph::edge_iterator b = edges(g).first;
	Graph::edge_iterator e = edges(g).second;
	ASSERT_EQ(std::distance(b,e), 1);
	ASSERT_EQ(++b, e);


	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_iterator b1 = edges(bg).first;

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_iterator e1 = edges(bg).second;
	ASSERT_EQ(std::distance(b1,e1), 1);
	ASSERT_EQ(++b1, e1);
}



TEST_F(GraphTest, edges_3)
{
	add_edge(a, add_vertex(g), g);
	add_edge(c, add_vertex(g), bg);
	

	Graph::edge_iterator b = edges(g).first;
	Graph::edge_iterator e = edges(g).second;
	ASSERT_EQ(std::distance(b,e), 2);

	++b; ++b;
	ASSERT_EQ(b, e);


	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_iterator b1 = edges(bg).first;

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_iterator e1 = edges(bg).second;
	ASSERT_EQ(std::distance(b1,e1), 2);
	++b1; ++b1;
	ASSERT_EQ(b1, e1);
}



TEST_F(GraphTest, num_edges_1)
{
	Graph t = Graph();
	ASSERT_EQ(num_edges(t), 0);

	
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> gt = 	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>();
	ASSERT_EQ(num_edges(gt), 0);

}



TEST_F(GraphTest, num_edges_2)
{
	ASSERT_EQ(num_edges(g), 1);
	ASSERT_EQ(num_edges(bg), 1);
}




TEST_F(GraphTest, num_edges_3)
{
	ASSERT_EQ(num_edges(g), 1);
	ASSERT_EQ(num_edges(bg), 1);


	for(int i = 0; i < 100; i++)
	{
		add_edge(a, add_vertex(g), g);
		add_edge(c, add_vertex(g), bg);
	}

	ASSERT_EQ(num_edges(g), 101);
	ASSERT_EQ(num_edges(bg), 101);	

}


TEST_F(GraphTest, num_vertices_1)
{
	Graph t = Graph();
	ASSERT_EQ(num_vertices(t), 0);

	
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> gt = 	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>();
	ASSERT_EQ(num_vertices(gt), 0);

}



TEST_F(GraphTest, num_vertices_2)
{
	ASSERT_EQ(num_vertices(g), 2);
	ASSERT_EQ(num_vertices(bg), 2);
}




TEST_F(GraphTest, num_vertices_3)
{
	ASSERT_EQ(num_vertices(g), 2);
	ASSERT_EQ(num_vertices(bg), 2);


	for(int i = 0; i < 100; i++)
	{
		add_vertex(g);
		add_vertex(bg);
	}

	ASSERT_EQ(num_vertices(g), 102);
	ASSERT_EQ(num_vertices(bg), 102);	

}


TEST_F(GraphTest, source_1)
{
	ASSERT_EQ(source(edAB, g), a);
	ASSERT_EQ(source(edCD, bg), c);
}



TEST_F(GraphTest, source_2)
{
	ASSERT_EQ(source(edAB, g), a);
	ASSERT_EQ(source(edCD, bg), c);

	Graph::edge_descriptor ed;

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_descriptor ged;

	for(int i = 0; i < 100; i++)
	{

		Graph::vertex_descriptor v = add_vertex(g);
		ASSERT_EQ(source(add_edge(a, v, g).first, g), a);
	
		boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_descriptor gv = add_vertex(bg);
		ASSERT_EQ(source(add_edge(c, gv, bg).first, bg), c);
	}

}




TEST_F(GraphTest, source_3)
{
	ASSERT_EQ(source(edAB, g), a);
	ASSERT_EQ(source(edCD, bg), c);

	Graph::edge_descriptor ed;

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_descriptor ged;

	for(int i = 0; i < 1000; i++)
	{

		Graph::vertex_descriptor v = add_vertex(g);
		ASSERT_EQ(source(add_edge(a, v, g).first, g), a);
	
		boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_descriptor gv = add_vertex(bg);
		ASSERT_EQ(source(add_edge(c, gv, bg).first, bg), c);
	}

}
TEST_F(GraphTest, target_1)
{
	ASSERT_EQ(target(edAB, g), b);
	ASSERT_EQ(target(edCD, bg), d);
}



TEST_F(GraphTest, target_2)
{
	ASSERT_EQ(target(edAB, g), b);
	ASSERT_EQ(target(edCD, bg), d);

	Graph::edge_descriptor ed;

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_descriptor ged;

	for(int i = 0; i < 100; i++)
	{

		Graph::vertex_descriptor v = add_vertex(g);
		ASSERT_EQ(target(add_edge(a, v, g).first, g), v);
	
		boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_descriptor gv = add_vertex(bg);
		ASSERT_EQ(target(add_edge(c, gv, bg).first, bg), gv);
	}

}




TEST_F(GraphTest, target_3)
{
	ASSERT_EQ(target(edAB, g), b);
	ASSERT_EQ(target(edCD, bg), d);

	Graph::edge_descriptor ed;

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::edge_descriptor ged;

	for(int i = 0; i < 1000; i++)
	{

		Graph::vertex_descriptor v = add_vertex(g);
		ASSERT_EQ(target(add_edge(a, v, g).first, g), v);
	
		boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_descriptor gv = add_vertex(bg);
		ASSERT_EQ(target(add_edge(c, gv, bg).first, bg), gv);
	}

}



TEST_F(GraphTest, vertex_1)
{
	ASSERT_EQ(a, vertex(0, g));
	ASSERT_EQ(c, vertex(0, bg));
}




TEST_F(GraphTest, vertices_1)
{
	Graph t = Graph();
	Graph::vertex_iterator b = vertices(t).first;
	Graph::vertex_iterator e = vertices(t).second;
	ASSERT_EQ(b, e);


	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> gt = 	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>();
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_iterator b1 = vertices(gt).first;
	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_iterator e1 = vertices(gt).second;
	ASSERT_EQ(b1, e1);

}

TEST_F(GraphTest, vertices_2)
{
	Graph::vertex_iterator b = vertices(g).first;
	Graph::vertex_iterator e = vertices(g).second;
	ASSERT_EQ(std::distance(b,e), 2);
	++b;
	ASSERT_EQ(++b, e);


	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_iterator b1 = vertices(bg).first;

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_iterator e1 = vertices(bg).second;
	ASSERT_EQ(std::distance(b1,e1), 2);
    ++b1;
	ASSERT_EQ(++b1, e1);
}



TEST_F(GraphTest, vertices_3)
{
	add_vertex(g);
	add_vertex(bg);

	Graph::vertex_iterator b = vertices(g).first;
	Graph::vertex_iterator e = vertices(g).second;
	ASSERT_EQ(std::distance(b,e), 3);

	++b; ++b;
	ASSERT_EQ(++b, e);


	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_iterator b1 = vertices(bg).first;

	boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>::vertex_iterator e1 = vertices(bg).second;
	ASSERT_EQ(std::distance(b1,e1), 3);
	++b1; ++b1;
	ASSERT_EQ(++b1, e1);
}








class GraphSpecialCases : public testing::Test 
{

    protected:
        typedef Graph graph_type;

        typedef typename graph_type::vertex_descriptor vertex_descriptor;
        typedef typename graph_type::edge_descriptor edge_descriptor;

        typedef typename graph_type::vertex_iterator vertex_iterator;
        typedef typename graph_type::edge_iterator edge_iterator;
        typedef typename graph_type::adjacency_iterator adjacency_iterator;

        typedef typename graph_type::vertices_size_type vertices_size_type;
        typedef typename graph_type::edges_size_type edges_size_type;

        graph_type g;

        vertex_descriptor A;
        vertex_descriptor B;
        vertex_descriptor C;
        vertex_descriptor D;
        vertex_descriptor E;
        vertex_descriptor F;
        vertex_descriptor G;
        vertex_descriptor H;

        std::vector<vertex_descriptor> vertexList;
        std::vector<edge_descriptor> edgeList;

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
        edge_descriptor edCA;


        typedef boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> bgraph_type;

        typedef typename bgraph_type::vertex_descriptor bvertex_descriptor;
        typedef typename bgraph_type::edge_descriptor   bedge_descriptor;

        typedef typename bgraph_type::vertex_iterator bvertex_iterator;
        typedef typename bgraph_type::edge_iterator bedge_iterator;
        typedef typename bgraph_type::adjacency_iterator badjacency_iterator;

        typedef typename bgraph_type::vertices_size_type bvertices_size_type;
        typedef typename bgraph_type::edges_size_type bedges_size_type;

        bgraph_type bg;

        bvertex_descriptor bA;
        bvertex_descriptor bB;
        bvertex_descriptor bC;
        bvertex_descriptor bD;
        bvertex_descriptor bE;
        bvertex_descriptor bF;
        bvertex_descriptor bG;
        bvertex_descriptor bH;

        std::vector<vertex_descriptor> bvertexList;
        std::vector<edge_descriptor> bedgeList;

        bedge_descriptor bedAB;
        bedge_descriptor bedAC;
        bedge_descriptor bedAE;
        bedge_descriptor bedAD;
        bedge_descriptor bedAF;
        bedge_descriptor bedAG;
        bedge_descriptor bedAH;
        bedge_descriptor bedBC;
        bedge_descriptor bedBD;
        bedge_descriptor bedBE;
        bedge_descriptor bedCD;
        bedge_descriptor bedDE;
        bedge_descriptor bedDF;
        bedge_descriptor bedEF;
        bedge_descriptor bedFD;
        bedge_descriptor bedFH;
        bedge_descriptor bedFG;
        bedge_descriptor bedGH;
        bedge_descriptor bedHA;
        bedge_descriptor bedCA;

};

TEST_F(GraphSpecialCases, test_simple_cycle_1)
{
    A = add_vertex(g); 
    B = add_vertex(g);
    C = add_vertex(g);

    edAB = add_edge(A, B, g).first;
    edBC = add_edge(B, C, g).first;
    edCA = add_edge(C, A, g).first;

    ASSERT_TRUE(has_cycle(g));
}


TEST_F(GraphSpecialCases, add_edge_without_declared_vertex_1)
{


   A = add_vertex(g);
   B = add_vertex(g);
   ASSERT_TRUE(add_edge(B, 3, g).second);
   ASSERT_FALSE(add_edge(B, 3, g).second);

   vertex_iterator b2 = vertices(g).first;
   vertex_iterator e2 = vertices(g).second;

   ASSERT_EQ(std::distance(b2,e2), 4);

   bA = add_vertex(bg);
   bB = add_vertex(bg);
   ASSERT_TRUE(add_edge(bB, 3, bg).second);
   ASSERT_FALSE(add_edge(bB, 3, bg).second);

   bvertex_iterator b = vertices(bg).first;
   bvertex_iterator e = vertices(bg).second;

   ASSERT_EQ(std::distance(b,e), 4);

}



TEST_F(GraphSpecialCases, add_edge_without_declared_vertex_2)
{


   bA = add_vertex(bg);
   bB = add_vertex(bg);
   ASSERT_TRUE(add_edge(23, 1000, bg).second);
   bedAB = add_edge(bA, bB, bg).first;
   ASSERT_FALSE(add_edge(23, 1000, bg).second);

   bvertex_iterator b = vertices(bg).first;
   bvertex_iterator e = vertices(bg).second;

   ASSERT_TRUE(std::distance(b,e) == 1001);


   A = add_vertex(g);
   B = add_vertex(g);
   ASSERT_TRUE(add_edge(23, 1000, g).second);
   edAB = add_edge(A, B, g).first;
   ASSERT_FALSE(add_edge(23, 1000, g).second);
   vertex_iterator b2 = vertices(g).first;
   vertex_iterator e2 = vertices(g).second;
   ASSERT_TRUE(std::distance(b2,e2) == 1001);
}

TEST_F(GraphSpecialCases, add_edge_without_declared_vertex_3)
{
	ASSERT_TRUE(add_edge(0,123, bg).second);
	ASSERT_FALSE(add_edge(0,123, bg).second);

	ASSERT_TRUE(add_edge(0,123, g).second);
	ASSERT_FALSE(add_edge(0,123, g).second);
}


TEST_F(GraphSpecialCases, edge_pointing_to_itself_1)
{
	bA = add_vertex(bg);
	ASSERT_TRUE(add_edge(bA, bA, bg).second);
	ASSERT_FALSE(add_edge(bA, bA, bg).second);

	bedge_iterator b = edges(bg).first;
	bedge_iterator e = edges(bg).second;

	ASSERT_TRUE(++b == e);


	A = add_vertex(g);
	ASSERT_TRUE(add_edge(A, A, g).second);
	ASSERT_FALSE(add_edge(A, A, g).second);
	edge_iterator b2 = edges(g).first;
	edge_iterator e2 = edges(g).second;

	ASSERT_TRUE(++b2 == e2);

}


TEST_F(GraphSpecialCases, edge_pointing_to_itself_2)
{
	bA = add_vertex(bg);
	bB = add_vertex(bg);
	ASSERT_TRUE(add_edge(bA, bA, bg).second);
	ASSERT_FALSE(add_edge(bA, bA, bg).second);
	ASSERT_TRUE(add_edge(bB, bB, bg).second);
	ASSERT_FALSE(add_edge(bB, bB, bg).second);

	bedge_iterator b = edges(bg).first;
	bedge_iterator e = edges(bg).second;

	++b;
	ASSERT_TRUE(++b == e);


	A = add_vertex(g);
	B = add_vertex(g);

	ASSERT_TRUE(add_edge(A, A, g).second);
	ASSERT_FALSE(add_edge(A, A, g).second);
	ASSERT_TRUE(add_edge(B, B, g).second);
	ASSERT_FALSE(add_edge(B, B, g).second);
	edge_iterator b2 = edges(g).first;
	edge_iterator e2 = edges(g).second;
	++b2;
	ASSERT_TRUE(++b2 == e2);

}

TEST_F(GraphSpecialCases, edge_pointing_to_itself_3)
{
	bA = add_vertex(bg);
	bB = add_vertex(bg);
	bC = add_vertex(bg);

	ASSERT_TRUE(add_edge(bA, 0, bg).second);
	ASSERT_FALSE(add_edge(bA, 0, bg).second);
	ASSERT_TRUE(add_edge(bB, 1, bg).second);
	ASSERT_FALSE(add_edge(bB, bB, bg).second);
	ASSERT_TRUE(add_edge(bC, 2, bg).second);
	ASSERT_FALSE(add_edge(bC, bC, bg).second);

	bedge_iterator b = edges(bg).first;
	bedge_iterator e = edges(bg).second;

	++b; ++b;
	ASSERT_TRUE(++b == e);


	A = add_vertex(g);
	B = add_vertex(g);
	C = add_vertex(g);


	ASSERT_TRUE(add_edge(A, A, g).second);
	ASSERT_FALSE(add_edge(A, 0, g).second);
	ASSERT_TRUE(add_edge(B, B, g).second);
	ASSERT_FALSE(add_edge(B, 1, g).second);
	ASSERT_TRUE(add_edge(C, C, g).second);
	ASSERT_FALSE(add_edge(C, 2, g).second);
	edge_iterator b2 = edges(g).first;
	edge_iterator e2 = edges(g).second;
	++b2; ++b2;
	ASSERT_TRUE(++b2 == e2);

}


class GraphAlgorithms : public testing::Test 
{

    protected:
        typedef Graph graph_type;

        typedef typename graph_type::vertex_descriptor vertex_descriptor;
        typedef typename graph_type::edge_descriptor edge_descriptor;

        typedef typename graph_type::vertex_iterator vertex_iterator;
        typedef typename graph_type::edge_iterator edge_iterator;
        typedef typename graph_type::adjacency_iterator adjacency_iterator;

        typedef typename graph_type::vertices_size_type vertices_size_type;
        typedef typename graph_type::edges_size_type edges_size_type;

        graph_type g;

        vertex_descriptor A;
        vertex_descriptor B;
        vertex_descriptor C;
        vertex_descriptor D;
        vertex_descriptor E;
        vertex_descriptor F;
        vertex_descriptor G;
        vertex_descriptor H;
        vertex_descriptor I;


        std::vector<vertex_descriptor> vertexList;
        std::vector<edge_descriptor> edgeList;

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
        edge_descriptor edCA;


        typedef boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> bgraph_type;

        typedef typename bgraph_type::vertex_descriptor bvertex_descriptor;
        typedef typename bgraph_type::edge_descriptor   bedge_descriptor;

        typedef typename bgraph_type::vertex_iterator bvertex_iterator;
        typedef typename bgraph_type::edge_iterator bedge_iterator;
        typedef typename bgraph_type::adjacency_iterator badjacency_iterator;

        typedef typename bgraph_type::vertices_size_type bvertices_size_type;
        typedef typename bgraph_type::edges_size_type bedges_size_type;

        bgraph_type bg;

        bvertex_descriptor bA;
        bvertex_descriptor bB;
        bvertex_descriptor bC;
        bvertex_descriptor bD;
        bvertex_descriptor bE;
        bvertex_descriptor bF;
        bvertex_descriptor bG;
        bvertex_descriptor bH;
        bvertex_descriptor bI;


        std::vector<vertex_descriptor> bvertexList;
        std::vector<edge_descriptor> bedgeList;

        bedge_descriptor bedAB;
        bedge_descriptor bedAC;
        bedge_descriptor bedAE;
        bedge_descriptor bedAD;
        bedge_descriptor bedAF;
        bedge_descriptor bedAG;
        bedge_descriptor bedAH;
        bedge_descriptor bedBC;
        bedge_descriptor bedBD;
        bedge_descriptor bedBE;
        bedge_descriptor bedCD;
        bedge_descriptor bedDE;
        bedge_descriptor bedDF;
        bedge_descriptor bedEF;
        bedge_descriptor bedFD;
        bedge_descriptor bedFH;
        bedge_descriptor bedFG;
        bedge_descriptor bedGH;
        bedge_descriptor bedHA;
        bedge_descriptor bedCA;

};


TEST_F(GraphAlgorithms, add_vertices_through_edge_1)
{
	add_edge(0, 1000, g);
	add_edge(0, 1000, bg);



	ASSERT_EQ(num_vertices(g), num_vertices(bg));
}


TEST_F(GraphAlgorithms, add_vertices_through_edge_2)
{
	add_edge(1232, 1000, g);
	add_edge(1000, 1232, bg);

	ASSERT_EQ(num_vertices(g), num_vertices(bg));
}

TEST_F(GraphAlgorithms, add_vertices_through_edge_3)
{
	add_edge(0,0,bg);
	add_edge(0,0,g);

	ASSERT_EQ(num_vertices(g), 1);
	ASSERT_EQ(num_vertices(bg), 1);
	ASSERT_EQ(num_vertices(g), num_vertices(bg));
}



TEST_F(GraphAlgorithms, test_simple_cycle_1)
{
    A = add_vertex(g); 
    B = add_vertex(g);
    C = add_vertex(g);

    edAB = add_edge(A, B, g).first;
    edBC = add_edge(B, C, g).first;
    edCA = add_edge(C, A, g).first;

    ASSERT_TRUE(has_cycle(g));


    bA = add_vertex(bg); 
    bB = add_vertex(bg);
    bC = add_vertex(bg);

    bedAB = add_edge(bA, bB, bg).first;
    bedBC = add_edge(bB, bC, bg).first;
    bedCA = add_edge(bC, bA, bg).first;

    ASSERT_TRUE(has_cycle(bg));
}


TEST_F(GraphAlgorithms, test_simple_cycle_2)
{
    A = add_vertex(g); 
    B = add_vertex(g);
    C = add_vertex(g);
    D = add_vertex(g);


    edAB = add_edge(A, B, g).first;
    edBC = add_edge(B, C, g).first;
    edCA = add_edge(C, D, g).first;

    ASSERT_FALSE(has_cycle(g));


    bA = add_vertex(bg); 
    bB = add_vertex(bg);
    bC = add_vertex(bg);
    bD = add_vertex(bg);

    bedAB = add_edge(bA, bB, bg).first;
    bedBC = add_edge(bB, bC, bg).first;
    bedCA = add_edge(bC, bD, bg).first;

    ASSERT_FALSE(has_cycle(bg));
}

TEST_F(GraphAlgorithms, test_larger_cycle_1)
{
    A = add_vertex(g); 
    B = add_vertex(g);
    C = add_vertex(g);
    D = add_vertex(g);
    E = add_vertex(g); 
    F = add_vertex(g);
    G = add_vertex(g);
    H = add_vertex(g);


    add_edge(A, B, g);
    add_edge(A, C, g);
    add_edge(B, D, g);
    add_edge(D, H, g);
    add_edge(H, B, g); //cycle
    add_edge(C, E, g);
    add_edge(F, E, g);
    add_edge(E, G, g);

    ASSERT_TRUE(has_cycle(g));



    bA = add_vertex(bg); 
    bB = add_vertex(bg);
    bC = add_vertex(bg);
    bD = add_vertex(bg);
    bE = add_vertex(bg); 
    bF = add_vertex(bg);
    bG = add_vertex(bg);
    bH = add_vertex(bg);


    add_edge(bA, bB, bg);
    add_edge(bA, bC, bg);
    add_edge(bB, bD, bg);
    add_edge(bD, bH, bg);
    add_edge(bH, bB, bg); //cycle
    add_edge(bC, bE, bg);
    add_edge(bF, bE, bg);
    add_edge(bE, bG, bg);

    ASSERT_TRUE(has_cycle(bg));
}



TEST_F(GraphAlgorithms, test_larger_cycle_2)
{
    A = add_vertex(g); 
    B = add_vertex(g);
    C = add_vertex(g);
    D = add_vertex(g);
    E = add_vertex(g); 
    F = add_vertex(g);
    G = add_vertex(g);
    H = add_vertex(g);


    add_edge(A, B, g);
    add_edge(A, C, g);
    add_edge(B, D, g);
    add_edge(D, H, g);
    add_edge(H, G, g); 
    add_edge(C, E, g);
    add_edge(F, E, g);
    add_edge(E, G, g);

    ASSERT_FALSE(has_cycle(bg));


    bA = add_vertex(bg); 
    bB = add_vertex(bg);
    bC = add_vertex(bg);
    bD = add_vertex(bg);
    bE = add_vertex(bg); 
    bF = add_vertex(bg);
    bG = add_vertex(bg);
    bH = add_vertex(bg);


    add_edge(bA, bB, bg);
    add_edge(bA, bC, bg);
    add_edge(bB, bD, bg);
    add_edge(bD, bH, bg);
    add_edge(bH, bG, bg); //cycle
    add_edge(bC, bE, bg);
    add_edge(bF, bE, bg);
    add_edge(bE, bG, bg);

    ASSERT_FALSE(has_cycle(bg));

}






TEST_F(GraphAlgorithms, self_cycle_1)
{
	bA = add_vertex(bg);
	add_edge(bA, bA, bg);
	ASSERT_FALSE(has_cycle(bg));

	A = add_vertex(g);
	add_edge(A, A, g);
	ASSERT_FALSE(has_cycle(g));

}


TEST_F(GraphAlgorithms, self_cycle_2)
{
	bA = add_vertex(bg);
	bB = add_vertex(bg);
	add_edge(bA, bA, bg);
	add_edge(bB, bB, bg);

	ASSERT_FALSE(has_cycle(bg));

	A = add_vertex(g);
	B = add_vertex(g);
	add_edge(A, A, g);
	add_edge(B, B, g);

	ASSERT_FALSE(has_cycle(g));

}

TEST_F(GraphAlgorithms, empty_cycle)
{

	ASSERT_FALSE(has_cycle(bg));

	ASSERT_FALSE(has_cycle(g));

}

TEST_F(GraphAlgorithms, large_cycle_true)
{
	for(int i = 1; i < 100; i++)
	{
		add_edge(i - 1, i, g);
		add_edge(i - 1, i, bg);
	}
	add_edge(99, 0, g);
	add_edge(99, 0, bg);

	ASSERT_TRUE(has_cycle(bg));
	ASSERT_TRUE(has_cycle(g));


}



TEST_F(GraphAlgorithms, cycle_true_2)
{
	for(int i = 1; i < 10; i++)
	{
		add_edge(i - 1, i, g);
		add_edge(i - 1, i, bg);
	}
	add_edge(99, 54, g);
	add_edge(99, 54, bg);

	add_edge(54, 99, g);
	add_edge(54, 99, bg);


	ASSERT_TRUE(has_cycle(bg));
	ASSERT_TRUE(has_cycle(g));

}








TEST_F(GraphAlgorithms, large_cycle_false)
{
	for(int i = 1; i < 100; i++)
	{
		add_edge(i - 1, i, g);
		add_edge(i - 1, i, bg);
	}
	add_edge(99, 101, g);
	add_edge(99, 101, bg);

	ASSERT_FALSE(has_cycle(bg));
	ASSERT_FALSE(has_cycle(g));

}






