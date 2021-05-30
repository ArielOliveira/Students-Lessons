#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <utility>
// TODO: add other #includes as needed

#include "CTrie.h"
using std::pair;
using std::cout;
using std::endl;

// TODO: implement the CTrie member functions and friend functions

CTrie::CTrie() {
  endPoint = false;
}

CTrie::CTrie(const CTrie& rhs) {
  endPoint = rhs.endPoint;
  for (auto node : rhs.nodes) 
    nodes.insert(std::pair<char, CTrie*>(node.first, new CTrie(*node.second)));
}

CTrie::~CTrie() {
  for (auto node : nodes) 
    delete node.second;
  
  nodes.clear();
}

bool CTrie::operator==(const CTrie& rhs) const {
  if (endPoint && !hasChild()) {
    return true;
  }

  if (numChildren() == rhs.numChildren()) {
    auto it1 = nodes.begin();
    auto it2 = rhs.nodes.begin();

    while (it1 != nodes.end()) {
      if (it1->first != it2->first)
        return false;

      if (it1->second->isEndpoint() != it2->second->isEndpoint())
        return false;

      if (!((*it1->second) == (*it2->second)))
        return false;
      
      it1++;
      it2++;
    }
  } else {
    return false;
  }

  return true;
}

CTrie& CTrie::operator=(const CTrie& rhs) {
  for (auto node : nodes)
    delete node.second;

  nodes.clear();

  endPoint = rhs.endPoint;

  for (auto node : rhs.nodes)
    nodes.insert( {node.first, new CTrie(*node.second)} );

  return *this;
}


CTrie& CTrie::operator+=(const std::string& word) {  
  CTrie* nextNode;
  auto it = nodes.find(word[0]);

  //checking to see if character is in the node. If it is not, then add it, if it is, continue
  if (it == nodes.end()) {
    nextNode = new CTrie();
    nodes.insert( {word[0], nextNode} );
  } else {
    nextNode = it->second;
  }

   if (&word[0] == &word.back())
    nextNode->endPoint = true;
   else 
    *nextNode += word.substr(1, word.length()-1);

  return *this;
}

bool CTrie::operator^(const std::string& word) const {
  if (word.length() == 0)
    return false;

  CTrie* nodeFound = nullptr;
  for (auto node : nodes) {   
    if (node.first == word[0]) {
      if (word.length() == 1 && node.second->isEndpoint()) return true;
      
      nodeFound = node.second;
      break;
    }
  }

  if (!nodeFound)    
    return false;



  if (nodeFound->hasChild()) 
    return *nodeFound ^ word.substr(1, word.length()-1);
  
  return false;
}

bool CTrie::isEndpoint() const { return endPoint; }

bool CTrie::hasChild() const { return nodes.size(); }

bool CTrie::hasChild(char character) const {
  auto it = nodes.find(character);

  if (it == nodes.end())
    return false;
  else
    return true;  
}

const CTrie* CTrie::getChild(char character) const {
  auto it = nodes.find(character);

  if (it != nodes.end())
    return it->second; 

  return nullptr;
}

unsigned CTrie::numChildren() const { return nodes.size(); }

std::string CTrie::as_string(std::string& s, std::string path) const {
   if (isEndpoint()) {
    s += path;
    s += '\n';
    
    if (!hasChild())
      return s;
  } 

  path += " ";

  for (auto node : nodes) {
    path.back() = node.first;

    node.second->as_string(s, path);
  }
  
  return s;
}

std::ostream& operator<<(std::ostream& os, const CTrie& ct) {
  std::string s;
  std::string path;
  
  os << ct.as_string(s, path);

  return os;
}



