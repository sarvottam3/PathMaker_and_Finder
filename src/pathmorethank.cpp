#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include <queue>
#include <stack>

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " Twitter_Data_File k_value SourceId"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  if(argc != 4) {
    usage(argv[0]);
  }

  char* graph_filename = argv[1];
  istringstream ss(argv[2]);
  istringstream ss2(argv[3]);

  //obtain the kLength number the user specified in String form
  string knumber;
  ss >> knumber;

  //obtain the source Node the user wants to start at
  string sourceIdnum;
  ss2 >> sourceIdnum;

  //convert both of the strings into ints
  int kLen = stoi(knumber, nullptr, 10);
  int sourceId = stoi(sourceIdnum, nullptr, 10);


  //create an ifstream to read from the user-specified file
  ifstream file1(graph_filename);

  cout << "Reading " << argv[1] << " ...\n" ;
  
  //check if the user specified a valid file
  if(!file1.is_open())
  {
    usage(argv[0]);
    return 1;
  }
  
  //variable to hold the largest id in the file, Graph will contain a vector
  ////that size + 1 to store all of the Node objects
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
    istringstream ss3(temp);

    //each line is a string, which will cthen be split into two strings
    //that contain the numbers for the first number to have a directed 
    //edge pointing ot the second number
    vector<string> record;
    while(ss3)
    {
      string temp;
      if(!getline(ss3, temp, ' '))
      {
        break;
      }
      record.push_back(temp);
    }
    if(record.size() != 2)
    {
      continue;
    }
     
    //we have the 2 ids stored as individual stings in vector record
    //so we need to convert them to the int values
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
    }//we have finished parsing through the first file to find the largest id,
     //so now we know what size to have the vector in the Graph object to be
  }
   
  //create the Graph object dynamically
  Graph * painting = new Graph(largestid + 1);
  
  //reset the file pointer for file1, since now we need to re read it again
  //to actually set up the Node network now
  file1.clear();
  file1.seekg(0, ios::beg);


  //call the Graph object memeber function to create the Graph and set up all 
  //the edged between the Nodes
  bool loadBoolean = painting->loadFromFileV2(graph_filename);

  //if the function was not able to load the userinput into a Graph, exit 
  //program
  if(loadBoolean == false)
  {
    return 1;
  }
  
  //declare a variable to hold the Node our search will lead us to
  Node * endNode = 0; 

  //declare a variable for the Node we will start the search at
  Node * startNode = painting->getNode(sourceId);

  if(startNode == NULL)
  {
    cout << "There is no node " << sourceId << "\n";
    delete painting;
    return 1;
  }

  //call the Graph object member function to search if there exists a 
  //path of length more than K from the startNode
  bool morethanK = painting->moreThanKLength(sourceId, kLen, endNode);
  

  //if there exists no such path, print corresponding message
  if(morethanK == false)
  {
    cout << " There exists no path of at least " << kLen << " from Node " << sourceId << "\n";
  }
  //if there exists a path, print the path that exists
  else
  {
    //iterate backward from end Node until you reach start node using the "prev"
    //field, and put all the nodes on a stack
    Node * iterator = endNode;
    std::stack<Node *> reverseorder;
    
    while(iterator != startNode)
    {
      reverseorder.push(iterator);
      iterator = iterator->prev;
    }

    //since the stack will be in reverse order, we just pop them all out to
    //get the correct order and print it to the screen
    cout << startNode->id;
    Node * iterator2;
    while(reverseorder.empty() == false)
    {
      iterator2 = reverseorder.top();
      reverseorder.pop();
      cout << ' ' << iterator2->id;
    }
    cout << "\n";
  }
  delete painting;
  return 0;
} 
