#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include <queue>

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file k_value output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    usage(argv[0]);
  }
  char* graph_filename = argv[1];
  char* output_filename = argv[3];
  istringstream ss(argv[2]);

 /* You can call the social gathering function from here */
  string knumber;
  ss >> knumber;

  int KCore = stoi(knumber , nullptr, 10);
  
  ifstream file1(graph_filename);
  ofstream file2(output_filename);

  cerr << "Reading " << argv[1] << " ...\n" ;

  if(!file1.is_open())
  {
    usage(argv[0]);
    return 1;
  }
  if(!file2.is_open())
  {
    usage(argv[0]);
  }
  
  int largestid = -1;

  while(file1)
  {
    
    string temp;
    if(!getline(file1, temp))
    {
      break;
    }
    istringstream ss(temp);

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

    int id1 = stoi(record[0], nullptr, 10);
    int id2 = stoi(record[1], nullptr, 10);
  
    if(id1 > largestid)
    {
      largestid = id1;
    }
    if(id2 > largestid)
    {
      largestid = id2;
    }
  }

  Graph * painting = new Graph(largestid + 1);
  file1.clear();
  file1.seekg(0, ios::beg);

  bool loadBoolean = painting->loadFromFile(graph_filename);
  
  if(loadBoolean == false)
  {
    return 1;
  }

  vector<int> results;

  painting->socialgathering(results, KCore);

  //priority_queue<int> forOutput;  

  std::priority_queue<int, std::vector<int>, std::greater<int> > forOutput;

  for(unsigned int i = 0; i < results.size(); i++)
  {
    int id = results.at(i);
    forOutput.push(id);
  }
  
  cout << "Preparing Invitees List\n"; 
 
  while(forOutput.empty() == false)
  {
    file2 << forOutput.top() << "\n";
    forOutput.pop(); 
  }
  delete painting;
}
