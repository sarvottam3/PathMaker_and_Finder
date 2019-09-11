/*
 * Name: Sarvottam Jalsingh
 * PA4 Class
 * This file contains all of the implementation of the function declarations
 * in the Graph.hpp file. It contains all the member methods of Graph and the
 * destructor and constructor.
 */

#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <list>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

Graph::Graph(int numofNode) {
    //have it set up like a hash table possible where size+1 is largest id 
    //in the group
    size = numofNode;
    nodes = vector<Node *>(size, (Node *) 0);
}
Graph::~Graph(void) {
   //loop through all of the indices in the nodes vector, and if there is a 
   //valid pointer there, call the delete function for the Node object
   for(unsigned int i = 0; i < nodes.size(); i++)
   {
     if(nodes[i] != NULL)
     {
       delete nodes[i];
     } 
   } 
}

/* Read in relationships from an inputfile to create a graph */
bool Graph::loadFromFile(const char* in_filename) {
  //create a filestream for the file we are reading in
  ifstream infile(in_filename);
  //follow the same structure as path finder where we read each line one
  //at a time and then we stor both of the ids read into a vector
  while (infile) {
    string s;
    if (!getline(infile, s)) break;

    istringstream ss(s);
    vector<string> record;

    while (ss) {
      string s;
      if (!getline(ss, s, ' ')) break;
      record.push_back(s);
    }

    if (record.size() != 2) {
      continue;
    }

    string first = record[0];
    string second = record[1];
    
    int hash1 = stoi(first, nullptr, 10);
    int hash2 = stoi(second, nullptr, 10);
    
    //determine if the id we found already was present sometime before in 
    //the file so the Node object for that id was already created
    if(nodes[hash1] == NULL)
    {
      nodes[hash1] = new Node(hash1); 
    }
    if(nodes[hash2] == NULL)
    {
      nodes[hash2] = new Node(hash2);
    }

    //since we are using directed edges, both of the Nodes will be neighbors
    //with eachother
    nodes[hash1]->neighbors.push_back(hash2);
    nodes[hash2]->neighbors.push_back(hash1);
    nodes[hash1]->degree = nodes[hash1]->degree + 1;
    nodes[hash2]->degree = nodes[hash2]->degree + 1;
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

/*Function to see if path more than kLen exists*/
bool Graph::moreThanKLength(int sourceId, int kLen, Node*& endNode) {

  //Node We will start the search on 
  Node * startNode = getNode(sourceId);
  
  //Set the start node's distance to 0
  startNode->dist = 0;  
  
  //declare a stack Variable ot hold all of the nodes we will search through
  std::stack<Node *> S;
  
  //push the start node on the stack
  S.push(startNode);

  //loop through the stack until it is empty
  while(S.empty() == false)
  {
    //pop off from the top of the stack and store it into Node * curr
    Node * curr = S.top();
    S.pop();

    //if curr has not been visited befrore, set its visited field to true 
    //and push all of its neighbors on the stack as well, set the distance
    //of all of its neighbors as 1 + the distance of curr
    if(curr->visited == false)
    {
      curr->visited = true;
      for(unsigned int i = 0 ; i < curr->neighbors.size(); i++)
      {
        Node * neighbor = getNode(curr->neighbors[i]);
        if(neighbor->visited == false)
        {
          S.push(neighbor);
          neighbor->prev = curr;
          neighbor->dist = curr->dist + 1;
  
          //if we have found a path of more than K length, we have satisfied
          //the search. set the endNode return paramater to the node we just found
          if(neighbor->dist >= kLen)
          {
            endNode = neighbor;
            return true;
          }
        }
      }
    }
  }

  //we have not found a path of more than k length
  return false;  
}


/* Read in relationships from an inputfile to create a graph */
bool Graph::loadFromFileV2(const char* in_filename) {
  //create a filestream for the file we are reading in
  ifstream infile(in_filename);
  //follow the same structure as path finder where we read each line one
  //at a time and then we stor both of the ids read into a vector
  while (infile) {
    string s;
    if (!getline(infile, s)) break;

    istringstream ss(s);
    vector<string> record;

    while (ss) {
      string s;
      if (!getline(ss, s, ' ')) break;
      record.push_back(s);
    }

    if (record.size() != 2) {
      continue;
    }

    string first = record[0];
    string second = record[1];
    
    int hash1 = stoi(first, nullptr, 10);
    int hash2 = stoi(second, nullptr, 10);
    
    //determine if the id we found already was present sometime before in 
    //the file so the Node object for that id was already created
    if(nodes[hash1] == NULL)
    {
      nodes[hash1] = new Node(hash1); 
    }
    if(nodes[hash2] == NULL)
    {
      nodes[hash2] = new Node(hash2);
    }

    //since we are using directed edges, both of the Nodes will be neighbors
    //with eachother
    nodes[hash1]->neighbors.push_back(hash2);

    //nodes[hash2]->neighbors.push_back(hash1);
    //nodes[hash1]->degree = nodes[hash1]->degree + 1;
    //nodes[hash2]->degree = nodes[hash2]->degree + 1;
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;

}


/* Function to determine shortest path between two nodes, if
 * there exists one in the Graph
 */
bool Graph::pathfinder(Node* from, Node* to) {
  
  //set all of the visited fields of the Nodes to false
  for(unsigned int i = 0; i < nodes.size(); i++)
  {
    if(nodes[i] != NULL)
    {
      nodes[i]->visited = false;
    }
  }
  
  //create a list of Nodes, starting with the from Node, and set its
  //visited field to true
  list<Node*> queue;
  from->visited = true;
  queue.push_back(from);

  //keep cycling through the queue pop the top element, and for all of its 
  //Neighbors that have not been visited, push them on to the queue
  while(queue.empty() == false)
  {
    Node* curr = queue.front();
    queue.pop_front();

    //if we have found the destination Node we are looking for
    if(to == curr)
    {
      return true;
    }   

    //loop through all of the current Node's neighbors 
    for(unsigned int i = 0; i < curr->neighbors.size(); i++)
    {
      int indexforNext = curr->neighbors[i];
      Node * checknext = getNode(indexforNext);
    
      //if we have not visited the Node, set its visited field to true and 
      //push it on the stack
      if(checknext->visited == false)
      {
        checknext->visited = true;
        checknext->prev = curr;
        queue.push_back(checknext);
      }
    }
  }
  //if we have exhausted the connected Graph, and we have not found the 
  //destination Node
  return false;
}

/* Implement social gathering*/
void Graph::socialgathering(vector<int>& invitees, const int& k) {
  
  priority_queue<pair<Node*, int>, vector<pair<Node*,int>>, NodePtrComp>  pq; 
  
  for(unsigned int i = 0; i < nodes.size(); i++)
  {
    if(nodes[i] != NULL)
    {
      pair <Node*, int> temp(nodes[i], nodes[i]->degree);
      pq.push(temp);
    }
  }

  vector<int> core(nodes.size(), 0);

  while(pq.size() != 0)
  {
    pair <Node*, int> temp = pq.top();
    pq.pop();

    Node * curr = get<0>(temp);
    
    if(curr->visited == true)
    {
      continue;
    }    
    
    curr->visited = true;
    if(curr->degree < k) 
    {
      for(unsigned int i = 0; i < curr->neighbors.size(); i++)
      {
        Node * neighbor = getNode(curr->neighbors[i]);
        neighbor->degree = neighbor->degree - 1;
        pair<Node*, int> update{neighbor, neighbor->degree};
        pq.push(update);
      }
    }
  }

  for(unsigned int i = 0; i < nodes.size(); i++)
  {
    if(nodes[i]->degree >= k)
    {
      invitees.push_back( nodes[i]->id );
    }
  }
}

/* Function that takes in an index and will return the corresponding node
 * located at that index in the vector nodes
 */
Node* Graph::getNode(int index) {
  return nodes[index];
}

