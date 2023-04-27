#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
class node {
public:
    vector<string> genre;
    vector<string> info;
    int rank;
    string name;
    string id;
    string year;
    node(vector<string> _genre, vector<string> _info);
    bool operator>(const node& other) const {
        if (rank != other.rank) {
            return rank > other.rank;
        } else {
            return id > other.id;
        }
    }
    bool operator<(const node& other) const {
        if (rank != other.rank) {
            return rank < other.rank;
        } else {
            return id < other.id;
        }
    }

};


