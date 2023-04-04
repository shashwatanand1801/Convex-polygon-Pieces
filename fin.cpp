#include<bits/stdc++.h>
#include "macros.h"
#include "dcel.h"
 
const float pi = 3.141592f; 
 
vector<DCEL*> decomposition;
int idx = 0;
 
 
/**
 * Returns a vector of coordinate pairs from a vector of Vertex pointers
 * Used only easier debugging.
 *  
 * @param v A vector of pointers to Vertex objects.
 * @return A vector of coordinate pairs (std::vector<std::pair<int, int>>).
 */ 
vector<pii> getCordinatePairs(vector<Vertex*> v) {
  vector<pii> r;
  for (int i = 0; i < sz(v); i++) {
    r.push_back({v[i]->x , v[i]->y});
  }
  return r;
}
 
/**
 * Checks whether a vertex is a notch or not, with respect to two other vertices.
 *
 * @param a A pointer to the first vertex (Vertex*) in the triangle.
 * @param b A pointer to the vertex (Vertex*) to be checked.
 * @param c A pointer to the third vertex (Vertex*) in the triangle.
 * @return True if b is not a notch, false otherwise.
 */
int isNotNotch(Vertex* a , Vertex*b , Vertex *c) {
    pair<float , float> ab = { b->x - a->x, b->y - a->y };
    pair<float , float> cb = { b->x - c->x, b->y - c->y };
 
    float dot = (ab.first * cb.first + ab.second * cb.second); // dot product
    float cross = (ab.first * cb.second - ab.second * cb.first); // cross product
 
    float alpha = atan2(cross, dot);
 
    int ang =  (int) floor(alpha * 180. / pi + 0.5);
    ang = ang < 0 ? 360 + ang : ang;
    return (ang > 180 ? false : true);
}
 
/**
 * Returns the set difference between P and Lm, ordered Clockwise.
 * 
 *
 * @param P A vector of pointers to vertices defining the polygon.
 * @param Lm A vector of pointers to vertices defining the guard positions.
 * @return The list of vertices in the LPVS (std::list<Vertex*>).
 */ 
list<Vertex*> getLPVS(vector<Vertex*> P , vector<Vertex*> Lm) {
 list<Vertex *> LPVS; 
 for (int i = idx; i < sz(P); i++) {
  bool flag = true;
  for (int j = 0; j < sz(Lm); j++) {
    if (Lm[j] == P[i]) {
      flag = false;
      break;
    }
  }
  if (flag) {
    Vertex* prev = P[(i - 1 + sz(P)) % sz(P)];
    Vertex* next = P[(i + 1) % sz(P)];
     LPVS.push_back(P[i]);
  }
 }
 for (int i = 0; i < idx; i++) {
  bool flag = true;
  for (int j = 0; j < sz(Lm); j++) {
    if (Lm[j] == P[i]) {
      flag = false;
      break;
    }
  }
  if (flag) {
    Vertex* prev = P[(i - 1 + sz(P)) % sz(P)];
    Vertex* next = P[(i + 1) % sz(P)];
     LPVS.push_back(P[i]);
  }
 }
 return LPVS;
}
 
/**
 * Returns the containing rectangle of a set of vertices Lm.
 *
 * @param Lm A vector of pointers to vertices defining the guard positions.
 * @return A vector of two pairs of integers (std::vector<std::pair<int,int>>),
 *         representing the bottom-left and top-right corners of the rectangle.
 */ 
vector<pii> getContainingRectangle(vector<Vertex*> Lm) {
  pii x = {INT_MAX , INT_MIN};
  pii y = {INT_MAX , INT_MIN};
  for (int i = 0; i < sz(Lm); i++) {
    if(Lm[i]->x < x.first) {
      x.first = Lm[i]->x;
    }
    if (Lm[i]->x > x.second) {
      x.second = Lm[i]->x;
    }
    if(Lm[i]->y < y.first) {
      y.first = Lm[i]->y;
    }
    if (Lm[i]->y > y.second) {
      y.second = Lm[i]->y;
    }
  }
  vector<pii> rectangle = {x , y};
  return rectangle;
}
 
 
/**
 * Checks whether a given point (x, y) is inside a rectangle defined by its
 * minimum and maximum x and y coordinates.
 *
 * @param minX The minimum x coordinate of the rectangle.
 * @param maxX The maximum x coordinate of the rectangle.
 * @param minY The minimum y coordinate of the rectangle.
 * @param maxY The maximum y coordinate of the rectangle.
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @return true if the point is inside the rectangle, false otherwise.
 */
bool insideRectangle(int minX , int maxX , int minY , int maxY , int x , int y) {
  return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}
 
 
/**
 * Determines whether a point is to the left or right of a line segment.
 *
 * @param a  The first point defining the line segment.
 * @param b  The second point defining the line segment.
 * @param p  The point to test.
 *
 * @return   Returns 0 if point p is to the right of line segment ab, 1 if it is to the left.
 */
 
int crossProduct(pair<int , int> a, pair<int , int> b , pair<int , int> p) {
  //shift origin
  b = {b.first - a.first , b.second - a.second};
  p = {p.first - a.first , p.second - a.second};
  //return cross product
  return ((b.first * p.second - b.second * p.first) <= 0 ? 0 : 1);
}
 
 
/**
 * @brief Determines if a given point is inside a polygon
 *
 * @param polygon A vector of pairs representing the vertices of the polygon in clockwise order
 * @param p A pair representing the point to be checked
 * @return A boolean value indicating whether the point is inside the polygon or not
 *
 * This function determines whether a given point is inside a polygon using the cross product algorithm.
 * It takes a vector of pairs representing the vertices of the polygon in clockwise order and a pair representing
 * the point to be checked. The function returns true if the point is inside the polygon and false otherwise.
 * Note that the polygon should be defined in a clockwise order.
 */ 
bool isInsidePolygon(vector<pair<int , int>> polygon , pair<int , int> p) {
  int cp = crossProduct(polygon[0] , polygon[1] , p);
  int curr_cp;
  for (int i = 0; i < (int)polygon.size() - 1; i++) {
    curr_cp = crossProduct(polygon[i] , polygon[i + 1] , p);
    if(curr_cp != cp) {
      return false;
    }
  }
  curr_cp = crossProduct(polygon[polygon.size() - 1] , polygon[0] , p); 
  if(curr_cp != cp) return false;
  return true;
}
 
/**
 * @brief Removes from Lm vertices that lie on the same side of the semiplane generated by
 *        v^1-v as Last[Lm] 
 *
 * @param Lm A vector of pointers to Vertex objects representing the vertices to be checked
 * @param v A pair representing the line to check against
 * @return A vector of pointers to Vertex objects with the vertices that are not on one side of the line
 *
 * This function takes a vector of pointers to Vertex objects representing the vertices to be checked and a pair
 * representing the line to check against. It then removes the vertices that are on the same side of the line as the
 * first vertex in the vector, and returns a new vector of pointers to Vertex objects containing only the vertices
 * that are not on one side of the line.
 */
vector<Vertex*> getVTRandSubract(vector<Vertex*> Lm , pii v) {
 Vertex* Last = Lm[sz(Lm) - 1];
 Vertex* v1 = Lm[0];
 vector<Vertex *> newLm;
 newLm.push_back(Lm[0]);
 int cp = crossProduct({v1->x , v1->y} , {v.fi , v.sc} , {Last->x , Last->y});
 for (int i = 1; i < sz(Lm); i++) {
  if(crossProduct({v1->x , v1->y} , {v.fi , v.sc} , {Lm[i]->x , Lm[i]->y}) != cp) {
    newLm.push_back(Lm[i]);
  }
 }
 return newLm;
}
 

/**

* @brief Generates the clockwise ordering of the vertices for the next iteration of the MP1 procedure.
* @param P A vector of pointers to the vertices in the current iteration of the procedure.
* @param Lm A vector of pointers to the vertices on the leftmost chain of the current iteration of the procedure.
* @return A vector of pointers to the vertices in the clockwise ordering for the next iteration of the procedure.

*/
 
vector<Vertex*> getNextP(vector<Vertex*> P, vector<Vertex*> Lm) {
  vector<Vertex*> nextP;
  nextP.push_back(Lm.back());
  for (int i = idx; i < sz(P); i++) {
    bool flag = true;
    for (int j = 0; j < sz(Lm); j++) {
      if((P[i]->x == Lm[j]->x) && (P[i]->y == Lm[j]->y)) {
        flag = false;
        break;
      }
    }
    if(flag) {
      if(P[i] != Lm[0] && P[i] != Lm.back())
       nextP.push_back(P[i]);
    }
  }
  for (int i = 0; i < idx; i++) {
    bool flag = true;
    for (int j = 0; j < sz(Lm); j++) {
      if((P[i]->x == Lm[j]->x) && (P[i]->y == Lm[j]->y)) {
        flag = false;
        break;
      }
    }
    if(flag) {
      if(P[i] != Lm[0] && P[i] != Lm.back())
       nextP.push_back(P[i]);
    }
  }
  nextP.push_back(Lm[0]);
  return nextP;
}
 
/**

* @brief Returns the index of the starting vertex for the current iteration of the MP1 procedure.
* @param P A vector of pointers to the vertices in the current iteration of the procedure.
* @param v A pointer to the starting vertex of the leftmost chain for the current iteration of the procedure.
* @return An integer representing the index of the starting vertex for the current iteration.

*/
 
int getIndex(vector<Vertex*> P, Vertex* v) {
    int i, j;
    int n = sz(P);
    for(i = 0; i < n; i++) {
        if(P[i] == v) {
            break;
        }
    }
    return i;
}
 
/**

* @brief Prints the content of a vector of Vertex pointers. Used for debugging.
* @param v A vector of pointers to the vertices to be printed.

*/
 
void printVV (vector<Vertex*> v) {
  for (int i = 0; i < sz(v) ; i++) {
    pii p = {v[i]->x , v[i]->y};
    debug(p);
  }
}
 
/**
 * @brief Computes the monotone partition of a given polygon using the DCEL data structure.
 *
 * This function takes a pointer to a DCEL object representing a polygon and computes its monotone partition.
 * The partition is stored in a vector of DCEL objects called 'decomposition'.
 *
 * @param polygon A pointer to a DCEL object representing the polygon.
 * @return void
 */
void MP1(DCEL *polygon) {
 int m = 1;
 vector<Vertex*> P = polygon->vertices;
 debug(getCordinatePairs(P));
 int n = (int)P.size();
 debug(n);
 vector<Vertex*> Lm;
 Lm.push_back(P[0]);
 while (n > 3) {
  //3.1
  Vertex *v1 = Lm.back(); 
  idx = getIndex(P , v1);
  Vertex *v2 = P[(idx + 1) % sz(P)];
  Lm.clear();
  //3.2
  Lm.push_back(v1); Lm.push_back(v2);
  int i = idx + 1; // index 
  Vertex *vip1 = P[(i + 1) % sz(P)];
  //3.3
  while (isNotNotch(P[(i - 1 + sz(P)) % sz(P)] , P[i] , vip1) 
    && isNotNotch(P[i] , vip1 , v1)
    && isNotNotch(vip1 , v1 , v2)
    && sz(Lm) < n) {
    Lm.push_back(vip1);
    i++;
    vip1 = P[(i + 1) % sz(P)];
  }
  debug(getCordinatePairs(Lm));
  //3.4
  if (sz(Lm) != sz(P)) {
    //3.4.1
    list<Vertex *> LPVS = getLPVS(P , Lm);
    debug(sz(LPVS));
    while (sz(LPVS) > 0) {
      vector<pii> R = getContainingRectangle(Lm);
      debug(R);
      bool backward = false;
      while (!backward and sz(LPVS) > 0) {
       Vertex *v;
       do {
        v = LPVS.front();
        bool inside = insideRectangle(R[0].first , R[0].second , R[1].first , R[1].second , v->x , v->y);
        if (!inside) {
          LPVS.pop_front();
        } else {
          break;
        }
       } while ((sz(LPVS) > 0));
       if (sz(LPVS) > 0) {
        //Check if v is inside polygon generated by Lm
         vector<pii> poly = getCordinatePairs(Lm);
         pii point = {v->x , v->y};
         debug(point);
         if(isInsidePolygon(poly , point)) {
          Lm = getVTRandSubract(Lm , point);
          backward = true;
          debug(backward);
         }
        LPVS.pop_front();
       }
      }
    }
  }
  if(Lm.back() != v2) {
    //create new DCEL and update P for next iteration
    printVV(Lm);
    DCEL* d1 = new DCEL();
    initialize_DCEL(d1 , getCordinatePairs(Lm));
    decomposition.push_back(d1);
    debug(idx);
    P = getNextP(P , Lm);
    debug(getCordinatePairs(P));
    debug(sz(P));
    n = n - sz(Lm) + 2;
  } 
  //edge-case triangle
  if(n == 3) {
    DCEL *d1 = new DCEL();
    initialize_DCEL(d1 , getCordinatePairs(P));
    decomposition.push_back(d1);
  }
 }
 m++;
}
 
 
/**
 * @brief Reads a set of 2D vertices from standard input.
 *
 * This function reads an integer 'nVertices' from standard input, followed by 'nVertices' pairs of integers representing the
 * x and y coordinates of 2D points. The coordinates are stored in a vector of pairs of integers called 'vertices'. The
 * vertices are reversed and sorted in clockwise order using the 'reverse'.
 *
 * @param vertices A reference to a vector of pairs of integers that will store the vertex coordinates.
 * @return void
 */
void read_vertices(vector<pii> &vertices) {
  int nVertices;
  cin >> nVertices;
  for (int i = 0; i < nVertices; i++) {
    int x , y;
    cin >> x >> y;
    pii p = {x , y};
    vertices.push_back(p);
  }
  //Reverse because vertices are input in Counter-clockwise order.
  reverse(all(vertices));
  debug(vertices);
}
 
 
 
/**
 * @brief Main function to run the program.
 * 
 * This function is the entry point to the program. It reads the input from a file called "input.txt" and writes the output to two files: "output.txt" and "error.txt". It initializes a DCEL object and reads the vertices from the input file using the read_vertices() function. Then it initializes the DCEL object using the initialize_DCEL() function. It calls the MP1() function on the DCEL object to perform a decomposition of the polygon. Finally, it prints the vertices of each DCEL object in the decomposition to the console.
 *
 * @return int Returns 0 to indicate that the program ran successfully.
 */
int main(){
  freopen("input.txt","r", stdin);
  freopen("output.txt", "w" , stdout);
  freopen("error.txt" , "w" , stderr);
  DCEL *d = new DCEL();
  vector<pii> v;
  read_vertices(v);
  initialize_DCEL(d , v);
  MP1(d);
  int i = 1;
  for (auto x : decomposition) {
    cout << "DCEL " << i << "\n";
    i++;
    print_vertices(x->head);  
  }
  return 0;
}