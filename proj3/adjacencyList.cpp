//
// Created by wwwww on 4/21/23.
//
#include <algorithm>
#include <vector>
#include "adjacencyList.h"
using namespace std;

void adjacencyList::saveNode(node& movie, string& year)
{
    List[year].push_back(movie);
}

void adjacencyList::topTenRank(string year)
{

//    for(int i = 0; i < 10; i++)
//        topRank.push_back(List[year].at(i));
//    for(int i = 10; i < List[year].size(); i++)
//    {
//        for(int j = 0; j < 10; j++)
//        {
//            if(List[year].at(i).rank > topRank[j].rank)
//            {
//                topRank[j] = List[year].at(i);
//                break;
//            }
//        }
//    }
    sort(List[year].begin(), List[year].end(),
         [](node const &a, node const &b) { return a.rank > b.rank; });

}

void adjacencyList::printRankAJ(string year)
{
    mergeSort(year,0,(List[year].size()-1));
    topTenRank(year);
    if(!existed)
        cout << "No Netflix show is found!" << endl;
    else
    {
        for(int i = 0; i < 10; i++)
        {
            if(i < List[year].size())
                cout << List[year].at(i).name << "(" << year << "), " << " rating: " << List[year].at(i).rank << endl;
            else
                break;
        }
    }

    //topRank.clear();
}

int adjacencyList::size(string year){
    return List[year].size();
}

node adjacencyList::currentNode(string year,int i){
    return List[year].at(i);
}

bool adjacencyList::yearExisted(string year){
    if(List[year].empty()) {
        existed = false;
        return false;
    }
    return true;
}

void adjacencyList::merge(string year, int left, int middle,int right){
  //  cout<<"enter";
    int sub1 = middle-left+1;
    int sub2 = right - middle;
    vector<node> leftSub,rightSub;
    for (int i = 0; i < sub1; ++i) {
        leftSub.push_back(List[year].at((left+i)));
    }
    for (int i = 0; i < sub2; ++i) {
        rightSub.push_back(List[year].at((middle+i+1)));
    }
    int leftPosition=0, rightPosition=0, sortPosition=left;
    while(leftPosition<sub1 && rightPosition<sub2){
        if (leftSub.at(leftPosition)>rightSub.at(rightPosition)){
            List[year].at(sortPosition) = leftSub.at(leftPosition);
            leftPosition++;
        }
        else{
            List[year].at(sortPosition) = rightSub.at(rightPosition);
            rightPosition++;
        }
        sortPosition++;
    }
    while (leftPosition<sub1){
        List[year].at(sortPosition) = leftSub.at(leftPosition);
        leftPosition++;
        sortPosition++;
    }
    while(rightPosition<sub2){
        List[year].at(sortPosition) = rightSub.at(rightPosition);
        rightPosition++;
        sortPosition++;
    }
  //  sub1.clear();
}

void adjacencyList::mergeSort(string year,int left,int right){
    if (left>=right){
        return;
    }
    if (left<right){
        int middle = left+(right-left)/2;
        mergeSort(year,left,middle);
        mergeSort(year,(middle+1),right);
        merge(year,left,middle,right);
    }
}