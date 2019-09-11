#include "Node.hpp"

bool Node::operator<(const Node& other)
{
  /*
  if(this->neighbors.size() < other.neighbors.size())
  {
    return false;
  }
  if(other.neighbors.size() < this->neighbors.size())
  {
    return true;
  }
  */
  if(this->degree < other.degree)
  {
    return false;
  }
  if(other.degree < this->degree)
  {
    return true;
  }

  return false;
}
