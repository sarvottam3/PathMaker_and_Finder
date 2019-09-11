/*
 * Name: Sarvottam Jalsingh
 * PA4 Class
 * This class contains the code used to parse through the user input and call
 * the functions of Graph to create a graph that contains all the Nodes 
 * specified in the file. It will then parse through user input again to 
 * determine if determine if there is a path defiend between two nodes of the 
 * user's choosing. It will output all of this information in a different file
 */

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include <stack>
#include "Node.hpp"

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file test_pairs_file output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];     //the file containing all of the ids and their friends
  char* pairs_filename = argv[2];     //the file containing all of the shortest paths we will test for
  char* output_filename = argv[3];    //the file that we will output all of the shortest paths to
  
  //open the three files 
  ifstream file1(graph_filename);
  ifstream file2(pairs_filename);
  ofstream file3(output_filename);

  //check if all of the files are valid, if user input is not correct, print 
  //message to cerr with Usage
  if(!file1.is_open()) 
  {
    cerr << "Reading" << argv[1]; 
    usage(argv[0]);
    return 1;
  }
  if(!file2.is_open())
  {
    cerr << "Reading" << argv[2];
    usage(argv[0]);
    return 1;
  }
  if(!file3.is_open())
  {
    return 1;
  }

  //variable to hold the largest id in the file, Graph will contain a vector 
  //that size + 1 to store all of the Node objects
  int largestid = -1;

  //read through the first file to find the largest id
  while(file1)
  {
    //read all of the input line by line
    string temp;
    if(!getline(file1, temp))
    {
      break;
    }
    istringstream ss(temp);

    //each line is a string, which will then be split into 2 strings
    //that contain the numbers for the 2 ids to be set as neighbors
    vector<string> record;
    while(ss)
    {
      string temp;
      if(!getline(ss, temp, ' '))
      {
        break;
      }
      record.push_back(temp);
    }
    if(record.size() != 2)
    {
      continue;
    }

    //we have the 2 ids stored as individual strings in vector record
    //so we need ot convert them to the int values
    int id1 = stoi(record[0], nullptr, 10);
    int id2 = stoi(record[1], nullptr, 10);

    //if id1 is greater than the largestid we have, set largestid to be id1
    if(id1 > largestid)
    {
      largestid = id1;
    }

    //if id2 is greater than the largestid we have, set largestid to be id2
    if(id2 > largestid)
    {
      largestid = id2;
    }
  }//we have finished parsing through the first file to find the largest id, 
   //so now we know what size to have the vector in the Graph object to be
  
  //create the Graph object dynamically
  Graph * painting = new Graph(largestid + 1);
  
  //reset the file pointer for file1, since now we need ot re read it again
  //to actually set up the Node network now
  file1.clear();
  file1.seekg(0, ios::beg);    
 
  //call the Graph object member function to create the Graph and set up all the
  //edges between the nodes
  bool loadBoolean = painting->loadFromFile(graph_filename);
 
  //if the function was not able to load the userinput into a Graph, exit program
  if(loadBoolean == false)
  {
    return 1;
  }
  
  //start reading in the input from the second file to determine all the possible
  //paths between the 2 Ids given
  //follow same structure of extracting two numbers as before
  while(file2)
  {
    string temp2;
    if(!getline(file2, temp2))
    {
      break;
    }
    istringstream ss2(temp2);
    vector<string> record2;
    while(ss2)
    {
      string temp2;
      if(!getline(ss2, temp2, ' '))
      {
        break;
      }
      record2.push_back(temp2);
      if(record2.size() != 2)
      {
        continue;
      }

      int startIndex = stoi(record2[0], nullptr, 10);
      int endIndex = stoi(record2[1], nullptr, 10);
      
      //with both of the int representations of the ids given, go to those 
      //respective positions in the Graph vector to obtain those Nodes
      Node * startNode;
      Node * endNode; 
      //see if the id given is a valid number, and that there is are actual 
      //nodes, not null pointers, at those indices
      if(startIndex < (largestid+1) && endIndex < (largestid+1) && 
        painting->getNode(startIndex) != NULL && painting->getNode(endIndex) != NULL)
      {    
        startNode = painting->getNode(startIndex);
        endNode = painting->getNode(endIndex);
      }
      else
      {
        file3 << '\n';
        continue;
      }

      //call the Graph member function to see if there is a path between two nodes
      bool searchBoolean = painting->pathfinder(startNode, endNode);
      //if there does exist a path between two nodes
      if(searchBoolean == true)
      {
        //declare an Iterator and set it equal to the endNode, and just follow
        //the prev field of each Node object until you find the startNode and
        //put them on a stack. Since they will be in reverse order, pop them
        //off the stack to get the correct order
        Node * iterator = endNode;
        std::stack<Node *> reverseorder;

        //following the prev field until we reach startNode
        while(iterator != startNode)
        {
          reverseorder.push(iterator); 
          iterator = iterator->prev;
        }
        
        //popping off each of those Ndoes off the stack and putting their ids 
        //into the file
        file3 << startNode->id;
        Node * iterator2;
        while(reverseorder.empty() == false)
        {
          iterator2 = reverseorder.top();
          reverseorder.pop();
          file3 << ' ' << iterator2->id;
        }
        file3 << '\n';
      }
      //if no path was found, just output an empty line
      else
      {
        file3 << '\n';
      }
    }
  }
  delete painting;
  return 0;
}//end of pathFinder class  
