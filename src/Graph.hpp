/*
 * Name: Sarvottam Jalsingh
 * PA4 Class
 * This class contains all of the header information associated with a Graph 
 * object, such as the underlying data structures and all the declarations of
 * the functon names
 */ 


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "Node.hpp"
#include <vector>
#include <utility>
//#include "Node.cpp"

using namespace std;

class NodePtrComp {
public:
    bool operator()(pair<Node*, int> n1, pair<Node*, int> n2) const {
        //return *lhs < *rhs;
        return *(get<0>(n1)) < *(get<0>(n2));
    }
};

class Graph {
private:
  int size;
  vector<Node *> nodes; 

public:
  /*
   * Graph constructor that will create a Graph object that has a vector field
   * that is as big as numofNode + 1
   */
  Graph(int numofNode);
  
  /*
   * Graph destructor that will call the destructor for all of the Node objects
   * in the vector
   */
  ~Graph(void);

  /*
   * Getter function that will return the Node at a corresponding index in the 
   * vector nodes
   */
  Node* getNode(int index);

  /*
   * Function that will take in a file name and then will read through that 
   * file to create the Graph and node objects and connect all the edges
   * between them. Returns a true if the file was read and parsed through
   * successfully, and false otherwise.
   */
  bool loadFromFile(const char* in_filename);

 
  /*
   * Function that will take in a file name and then will read through that 
   * file to create the directed Graph and node objects and connect the directed edges
   * between them. Returns a true if the file was read and parsed through
   * successfully, and false otherwise.
   */
  bool loadFromFileV2(const char* in_filename);

  /*
   * Function that will take in two Node pointers and return the shortest path
   * between them in the Graph. If a path exists it will return true, and if 
   * not it will return false. To access the path, start at the "to" node and 
   * back trace using the prev field of the Nodes until you reach the "from"
   * node
   */
  bool pathfinder(Node* from, Node* to);
    
  /*
   * Function that will determine who to invite to a party based on which
   * people will at least know k people there
   */
  void socialgathering(vector<int>& invitees, const int& k);

  /* 
   * Function that will start from the sourceId Node, and search using a
   * DFS search to see if there exists a path of length more than kLen in 
   * the graph.
   */
  bool moreThanKLength(int sourceId, int kLen, Node*& endNode); 
};

#endif  // GRAPH_HPP
