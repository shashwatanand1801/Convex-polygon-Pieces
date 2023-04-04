#ifndef DCEL_H
#define DCEL_H
 
using namespace std;
 
class Vertex;
 
class HalfEdge;
 
class Vertex {
 public: 
  int x;
  int y;
  int key;
  HalfEdge* org_edge;
  Vertex(int x , int y , int key);
  Vertex *getNext(Vertex *v);
  Vertex *getPrev(Vertex *v);
};
 
Vertex::Vertex(int x , int y , int key) {
   this->x = x;
   this->y = y;
   this->key = key; 
}
 
 
class Face {
 public:
  HalfEdge* inc_edge;
};
 
 
class HalfEdge{
  public:
    HalfEdge* twin;
    Vertex* org;
    Face* left;
    HalfEdge* next;
    HalfEdge* prev;
    void setTwin(HalfEdge * e1 , HalfEdge *e2);
    void linkEdges(HalfEdge *first , HalfEdge *second);
};
 
void HalfEdge::setTwin(HalfEdge *e1 , HalfEdge *e2) {
    e1->twin = e2;
    e2->twin = e1;
}
 
void  HalfEdge::linkEdges(HalfEdge *first , HalfEdge *second) {
    first->next = second;
    second->prev = first;
}
 
Vertex* Vertex::getNext(Vertex *v) {
  return v->org_edge->twin->org;
}
 
Vertex* Vertex::getPrev(Vertex *v) {
  return v->org_edge->prev->org;
}
 
class DCEL {
  public:
   HalfEdge *head;
   vector<Vertex*> vertices; 
};
 
 
void print_vertices(HalfEdge *starting_edge) {
   HalfEdge *cur = starting_edge;
    do {
     cout << cur->org->x << " " << cur->org->y << "\n";
     cur = cur->next;
    } while (cur != starting_edge); 
}
void initialize_DCEL(DCEL *dlist , vector<pii> v) {
    int nvertices = sz(v);
 
    for(int i = 0; i < nvertices; i++) {
        Vertex* a = new Vertex(v[i].first , v[i].second , i);
        dlist->vertices.push_back(a);
     }
 
    HalfEdge* fwd = new HalfEdge();
    HalfEdge* bkd = new HalfEdge();
    fwd->org=dlist->vertices[0];
    dlist->vertices[0]->org_edge = fwd;
    bkd->org=dlist->vertices[1];
    fwd->setTwin(fwd , bkd);
    dlist->head = fwd;
 
    HalfEdge* prevedge = new HalfEdge();
    prevedge=dlist->head;
 
    for(int i = 1; i < nvertices - 1; i++) {
        fwd = new HalfEdge();
        bkd = new HalfEdge();
        fwd->org=dlist->vertices[i]; //cw
        dlist->vertices[i]->org_edge = fwd;
        bkd->org=dlist->vertices[i+1];
        fwd->setTwin(fwd , bkd);
        bkd->linkEdges(bkd , prevedge->twin);
        prevedge->linkEdges(prevedge , fwd);
        prevedge=prevedge->next;
    }
 
    fwd = new HalfEdge();
    bkd = new HalfEdge();
    fwd->org=dlist->vertices[nvertices-1];
    dlist->vertices[nvertices-1]->org_edge = fwd;
    bkd->org=dlist->vertices[0];
    fwd->setTwin(fwd , bkd);
    bkd->linkEdges(bkd , prevedge->twin);
    prevedge->linkEdges(prevedge , fwd);
    fwd->linkEdges(fwd , dlist->head);
    dlist->head->twin->linkEdges(dlist->head->twin , bkd);
    // print_vertices(dlist->head->twin); 
}
 
#endif