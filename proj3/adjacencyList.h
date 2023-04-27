#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include "node.h"
using namespace std;

class adjacencyList {
    map<string, vector<node>> List;
    vector<node> topRank;
    vector<node> temp;
public:
    bool existed= true;
    void saveNode(node& movie, string& year);
    void topTenRank(string year);
    void printRankAJ(string year);
    int size(string year);
    node currentNode(string year,int i);
    bool yearExisted(string year);
    void mergeSort(string year,int left,int right);
    void merge(string year, int left, int middle,int right);
    //bool CompareRank(const node & left, const node & right);
};


