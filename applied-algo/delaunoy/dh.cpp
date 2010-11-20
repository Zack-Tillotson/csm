#include <LEDA/core/list.h>
#include <LEDA/geo/rat_point.h>
#include <LEDA/geo/random_rat_point.h>
#include <LEDA/graphics/window.h>
#include <LEDA/geo/geo_alg.h>
#include <LEDA/graph/graph_misc.h>
#include <LEDA/graph/graph.h>
#include <stdlib.h> // For rand
#include <time.h> // For init'ing rand
#include <stdio.h>

using namespace leda;
using namespace std;

const int MIN_GRAPH_SIZE = 10;
const int MAX_GRAPH_SIZE = 1000;

void printGraphSizes(int);
void GABRIEL_GRAPH(const list<point>&, GRAPH<point, int>&);
void RELATIVE_NEIGHBORHOOD_GRAPH(const list<point>&, GRAPH<point, int>&);

int main()
{

        srand(time(NULL));

        for(int i = 0 ; i < 3; i++) {
                int n = rand() % (MAX_GRAPH_SIZE - MIN_GRAPH_SIZE + 1) + MIN_GRAPH_SIZE;
                cout << "Graph of " << n << " nodes" << endl;
                printGraphSizes(n);
        }

}

void printGraphSizes(int n) {

        // Create the list of random points in our graph
        //list<rat_point> L;
        list<point> L;
        random_points_in_unit_square(n, L);

        GRAPH<point,int> DT;
        GRAPH<point,int> EMST;
        GRAPH<point,int> GG;
        GRAPH<point,int> RNG;

        // Generate the graphs
        DELAUNAY_TRIANG(L, DT);
        MIN_SPANNING_TREE(L, EMST);
        GABRIEL_GRAPH(L, GG);
        RELATIVE_NEIGHBORHOOD_GRAPH(L, RNG);

        cout << "Delaunay Triangulation                 : " << DT.number_of_edges() << endl;
        cout << "Gabriel Graph                          : " << GG.number_of_edges() << endl;
        cout << "Relative Neighborhood Graph            : " << RNG.number_of_edges() << endl;
        cout << "Euclidean Minimum Spanning Tree        : " << EMST.number_of_edges() << endl;
        cout << endl;

}

void GABRIEL_GRAPH(const list<point>& L, GRAPH<point, int>& GG) {

        // GG is a subset of DT
        DELAUNAY_TRIANG(L, GG);

        // For each edge, check to see if any other points are closer to the midpoint than the two ends
        edge e;
        list<edge> ggEdges;
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
                        GG.hide_edge(e);
                }

        }


}

void RELATIVE_NEIGHBORHOOD_GRAPH(const list<point>& L, GRAPH<point, int>& RNG) {

        // GG is a subset of DT
        DELAUNAY_TRIANG(L, RNG);

        // For each edge
        edge e;
        list<edge> ggEdges;
        forall_edges(e, RNG) {

                point a = RNG[RNG.source(e)]; // The 2 ends of the edge
                point b = RNG[RNG.target(e)];

                // Check to see if any other points are closer to both points than they are to each other
                bool foundCloserPoint = false;
                node u;
                forall_nodes(u, RNG) {

                        if(RNG[u] != a && RNG[u] != b) { // Ignore the 2 end points themselves

                                if(cmp_distances(a, RNG[u], a, b) <= 0 && cmp_distances(b, RNG[u], a, b) <= 0) { // This point is closer or equal to both
                                        foundCloserPoint = true;
                                        break;
                                }

                        }

                }

                if(foundCloserPoint) { // Remove this edge from the RNG
                        RNG.hide_edge(e);
                }

        }


}
       