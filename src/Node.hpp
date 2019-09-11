/*
 * Name: Sarvottam Jalsingh
 * PA4 Class
 * This class contains all the relevant information associated with the
 * Node object, which will go into the Graph. A Node object contains 
 * the number of the Node, the vector which will have the pointers to 
 * all of the neighbors of the Node, the boolean variable that will 
 * indicate if the Node has been visited, and a Node pointer that points 
 * to the previous Node in the search.
 */

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <limits>

using namespace std;

class Node {
public:
	int id;
	std::vector<int> neighbors;
        int degree;
        bool visited;
        Node * prev;
        int dist;

        Node(int IDNum) { 
          id = IDNum;
          degree = 0;
          visited = false;
          prev = 0;
          dist = std::numeric_limits<int>::max();
        }

        bool operator<(const Node& other);
};

#endif
