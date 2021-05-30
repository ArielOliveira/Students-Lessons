#include "TTrie.h"

#include <algorithm>
#include <cassert>

// TODO: implement TTrie member functions and friend functions
template< typename DataType>
TTrie<DataType>::TTrie() {
    endPoint = false;
}

template< typename DataType>
TTrie<DataType>::TTrie(const TTrie& rhs) {
    endPoint = rhs.endPoint;

    for (auto node : rhs.nodes)
        nodes.push_back({node.first, new TTrie<DataType>(*node.second)});
}

template< typename DataType>
TTrie<DataType>::~TTrie() {
    for (auto node : nodes)
        delete node.second;

    nodes.clear();
}

template< typename DataType>
TTrie<DataType>& TTrie<DataType>::operator=(const TTrie<DataType> &rhs) {
    for (auto node : nodes)
        delete node.second;

    nodes.clear();

    endPoint = rhs.endPoint;

    for (auto node : rhs.nodes)
        nodes.push_back({node.first, new TTrie<DataType>(*node.second)} );

    return *this;
}

template< typename DataType>
TTrie<DataType>& TTrie<DataType>::operator+=(const std::vector<DataType>& sequence) {
    TTrie<DataType>* nextNode = nullptr;
      
    if (nodes.size() == 0) {
        nextNode = new TTrie<DataType>();
        nodes.insert(nodes.begin(), {sequence[0], nextNode});
    } else {
        auto it = findElement(sequence[0]);
        if (it->first != sequence[0]) {
            nextNode = new TTrie<DataType>();
            nodes.insert(it, {sequence[0], nextNode} );
         } else {
            nextNode = it->second;
        }
    }

    if (sequence.size() == 1) {
        nextNode->endPoint = true;
    } else {
        *nextNode += std::vector<DataType>(sequence.begin()+1, sequence.end()); 
    }

    return *this;
}

template< typename DataType>
bool TTrie<DataType>::operator^(const std::vector<DataType> &sequence) const {
    if (sequence.size() == 0)
        return false;

    TTrie<DataType>* nodeFound = nullptr;
    for (auto node : nodes) {   
        if (node.first == sequence[0]) {
            if (sequence.size() == 1 && node.second->isEndpoint())
                return true;
      
            nodeFound = node.second;
            break;
        }
    }

    if (!nodeFound)
        return false;

    if (nodeFound->hasChild()) 
        return *nodeFound ^ std::vector<DataType>(sequence.begin()+1, sequence.end());
  
    return false;
}

template< typename DataType>
bool TTrie<DataType>::operator==(const TTrie<DataType>& rhs) const {
    if (endPoint && !hasChild())
        return true;

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

template< typename DataType>
std::string TTrie<DataType>::as_string(std::string& s, std::vector<DataType> path) const {
    if (endPoint) {
        for (auto value : path) {
            s += elementToString(value);
            s += "-";
        }
        
        s.erase(s.begin()+s.length()-1);
        s += '\n';

        if (!hasChild()) {
            return s;
        }
    }

    path.push_back(nodes[0].first);

    for (auto node : nodes) {
        path.back() = node.first;

        node.second->as_string(s, path);
    }

    return s;
}

template< typename U>
std::ostream& operator<<(std::ostream& os, const TTrie<U>& tt) {
    std::string s;
    std::vector<U> path;

    os << tt.as_string(s, path);

    return os;
}

template< typename DataType>
unsigned TTrie<DataType>::numChildren() const { return nodes.size(); }

template< typename DataType>
bool TTrie<DataType>::hasChild() const { return (nodes.size() > 0); }

template< typename DataType>
bool TTrie<DataType>::hasChild(const DataType &value) const { return std::binary_search(nodes.begin(), nodes.end(), std::pair<DataType, TTrie<DataType>*>(value, nullptr), compareElement); }

template< typename DataType>
const TTrie<DataType>* TTrie<DataType>::getChild(const DataType &value) const {
    auto it = std::lower_bound(nodes.begin(), nodes.end(), std::pair<DataType, TTrie<DataType>*>(value, nullptr), compareElement);

    if (it->first == value) 
        return it->second;

    return nullptr;
}

template< typename DataType>
bool TTrie<DataType>::isEndpoint() const { return endPoint; }


template< typename DataType>
bool TTrie<DataType>::compareElement(const std::pair<DataType, TTrie<DataType>*>& v1, const std::pair<DataType, TTrie<DataType>*>& v2) { 
    return (v1.first < v2.first); 
}

template<>
bool TTrie<std::string>::compareElement(const std::pair<std::string, TTrie<std::string>*>& v1, const std::pair<std::string, TTrie<std::string>*>& v2) { 
    return (v1.first.compare(v2.first) < 0);
}

template< typename DataType>
std::string TTrie<DataType>::elementToString(const DataType& value) const { return std::to_string(value); }

template<>
std::string TTrie<std::string>::elementToString(const std::string& value) const { return value; }

template<>
std::string TTrie<char>::elementToString(const char& value) const { std::string s; return s += value; }


template< typename DataType>
typename std::vector< std::pair<DataType, TTrie<DataType>*> >::iterator TTrie<DataType>::findElement(const DataType& value) { 
    return std::lower_bound (
        nodes.begin(),
        nodes.end(),
        std::pair<DataType, TTrie<DataType>*>(value, nullptr), 
        compareElement
    );
}
