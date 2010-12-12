#include <LEDA/core/list.h>
#include <LEDA/geo/rat_point.h>
#include <LEDA/geo/random_rat_point.h>
#include <LEDA/graphics/window.h>
#include <LEDA/geo/geo_alg.h>
#include <LEDA/geo/point_set.h>
#include <LEDA/geo/random_rat_point.h>
#include <LEDA/graph/graph_misc.h>
#include <LEDA/graph/graph.h>
#include <stdio.h>

using namespace std;
using namespace leda;


int main(int argc, char ** argv)
{
 
  list<point> L;  
  GRAPH<point,int> DT;
  GRAPH<point,int> EMST;
  GRAPH<point, int>RNG;
  GRAPH<point, int> GG;
  int numofpoints = 5;  
  
  if (argc != 2){
     std::cout << "Usage: " << argv[0] << " <number of points>"<<std::endl;
     exit(1); 
  } 
  numofpoints = atoi (argv[1]);
  if ( numofpoints < 1){
     std::cout<<"number of points must be positive integer."<<std::endl;
     exit(1);
  }
  random_points_in_square(numofpoints,100,L);   

  std::cout << "number of points: " << L.length() << "\n";
  //construct Delaunay Graph 
  DELAUNAY_TRIANG(L, DT);
  DT.print();
  std::cout << "DT:  num of edges:" << DT.number_of_edges()/2 << "\n"; 
  //construct Minimum Spanning Tree
  MIN_SPANNING_TREE(L, EMST); 
  EMST.print();
  std::cout << "EMST:  num of edges:" << EMST.number_of_edges() << "\n"; 
  
  //construct relative neighborhood graph
  point_set T(L);  
  list<edge> edges;
  edges = T.relative_neighborhood_graph();  
  edge e;
  
  forall(e, edges) {
     node v, s, t;
     s=new node_struct();
     t=new node_struct();
     forall_nodes(v, RNG){
        if (RNG[v].to_point()==T.pos_source(e)){
            s = v;
        }
        if(RNG[v].to_point()==T.pos_target(e)){
            t = v;
        }            
     }
     if(graph_of(s) != &RNG){
          s=RNG.new_node(T.pos_source(e));
     
     }
     if(graph_of(t) != &RNG){
          t=RNG.new_node(T.pos_target(e));
     
     }
     RNG.new_edge(s,t); 
  }
  RNG.print();
  std::cout << "RNG:  num of edges:" << RNG.number_of_edges()/2<< "\n"; 
  
  //construct Gabriel Graph
  // For each edge, check to see if any other points are closer to the midpoint than the two ends
  GG=DT;
	// For each edge, check to see if any other points are closer to the midpoint than the two ends
  forall_edges(e, GG) {

			// The 2 ends of the edge
			point a = GG[GG.source(e)];
			point b = GG[GG.target(e)];
			point c = midpoint(a, b);
			// Check to see if any other points are closer to the midpoint than the two ends 
			bool foundCloserPoint = false;
			node u;
			forall_nodes(u, GG) {
					if(GG[u] != a && GG[u] != b) { // Ignore the 2 end points themselves
							if(cmp_distances(a, c, c, GG[u]) >= 0) { // This point is closer or equal
									foundCloserPoint = true;
									break;
							}
					}
			}
			if(foundCloserPoint) { // Remove this edge from the GG
					GG.del_edge(e);
			}

    }
	
  GG.print();
  std::cout << "Gabriel Graph:  num of edges:" << GG.number_of_edges()/2<< "\n";   	

  //visualize all graphes in window
  window W;
  W.init(-110,110,-110);
  W.open(); 
  W.display();
  W.set_node_width(2);

  point p;  //draw points in L
  forall(p,L) {W.draw_filled_node(p.to_point(),black);}
  W.read_mouse();
  
  //edge e;
  forall_edges(e,DT) { //Delaunay Triangulation
    point p=DT[DT.source(e)].to_point();
    point q=DT[DT.target(e)].to_point();
    W.draw_edge(p,q);
  }
  
  W.set_line_width(2);
  forall_edges(e,DT) {  //convex hull
    point p=DT[DT.source(e)].to_point();
    point q=DT[DT.target(e)].to_point();
    if (DT[e]==2) W.draw_edge(p,q,red);
  }

  W.set_line_width(3);
  forall_edges(e,EMST) { //Euclidean MST
    point p=EMST[EMST.source(e)].to_point();
    point q=EMST[EMST.target(e)].to_point();
    W.draw_edge(p,q,black);
  }
  
  W.set_line_width(3);
  forall_edges(e,RNG) { //Relative Neightborhood Graph
    point p=RNG[RNG.source(e)].to_point();
    point q=RNG[RNG.target(e)].to_point();
    W.draw_edge(p,q,blue);
  }
  
  W.set_line_width(3);
  forall_edges(e,GG) { //Gabriel Graph
    point p=GG[GG.source(e)].to_point();
    point q=GG[GG.target(e)].to_point();
    W.draw_edge(p,q,yellow);
  }

  W.read_mouse();

  W.screenshot("graph_visualization");
   
}
