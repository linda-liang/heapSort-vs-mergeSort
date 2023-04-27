#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include "adjacencyList.h"
using namespace std;
using namespace std::chrono;
//class Movie {
//public:
//    string id;
//    string title;
//    string year;
//    string date_added;
//    int rating;
//
//    Movie(string id, string title, string year, string date_added, int rating) {
//        this->id = id;
//        this->title = title;
//        this->year = year;
//        this->date_added = date_added;
//        this->rating = rating;
//    }
//
//    bool operator>(const Movie& other) const {
//        if (rating != other.rating) {
//            return rating > other.rating;
//        } else {
//            return id > other.id;
//        }
//    }
//    bool operator<(const Movie& other) const {
//        if (rating != other.rating) {
//            return rating < other.rating;
//        } else {
//            return id < other.id;
//        }
//    }
//
//};

class MaxHeap {
private:
    vector<node> heap;

    void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

public:
    MaxHeap() {}

    MaxHeap(vector<node>& movies) {
         for (node movie : movies) {
            insert(movie);
        }
    }

    void insert(node movie) {
        heap.push_back(movie);

        int i = heap.size() - 1;
        int parent = (i - 1) / 2;

        while (i > 0 && heap[i] > heap[parent]) {
            swap(heap[i], heap[parent]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    node extractMax() {
        node max = heap.front();
        heap[0] = heap.back();
        heap.pop_back();

        heapify(0);

        return max;
    }

    bool isEmpty() {
        return heap.empty();
    }
};

void printTopTenRatedMovies(MaxHeap& movieHeap, const std::string& year) {
    int num = 0;
    while (!movieHeap.isEmpty()) {
        node topMovie = movieHeap.extractMax();
        if (topMovie.year == year) {
            std::cout << topMovie.name << " (" << topMovie.year << "), rating: " << topMovie.rank << std::endl;
            num++;
        }
        if (num == 10) {
            break;
        }
    }
}

int main() {
    adjacencyList list;
    MaxHeap movieHeap;
    string line;
    bool programRun = true;
    int a=0;
    int temp = 0;
    ifstream myfile ("netflix_titles.csv");
    if(myfile.is_open()){
        getline(myfile,line);//get the first row that is not gonna be used
        while(!myfile.eof() && temp < 8807) {
            string test;
            bool dquote_check = false;
            int double_quote = 0;
            vector<string> info;
            vector<string> genreList;
            getline(myfile, line);
            stringstream in(line);
            while (in.good()) {
//                if (!info.empty()&&info.at(0) =="s614"){
//                    cout<<"enter";
//                }
                string substr;
                getline(in, substr, ',');
                if (info.size() == 10) {
                    if (substr.find('"') != substr.npos) {
                        dquote_check= true;
                        genreList.push_back(substr);
                        if (double_quote % 2 != 0) {
                            dquote_check= false;
                            break;
                        }
                        double_quote++;
                    } else {
                        genreList.push_back(substr);
                        if (!dquote_check){
                            dquote_check= false;
                            if(info.at(0)=="s8202"){
                                getline(myfile, line);
                            }
                            break;
                        }
                    }
                } else {
                    if (substr.find('"') != substr.npos) {
                        int cnt = count(substr.begin(),substr.end(), '"');
                        if(cnt == 1) {
                            if (double_quote % 2 == 0) {
                                info.push_back(substr);
                                dquote_check = true;
                            }
                            if (double_quote % 2 != 0) {
                                info.at((info.size() - 1)) += substr;
                                dquote_check = false;
                            }
                            double_quote++;
                        }
                        else if(cnt==6 && !dquote_check && info.size()==4){
                            info.push_back(substr);
                        }
                        else if(cnt!=1 && !dquote_check && info.size()==4){
                            info.push_back(substr);
                            dquote_check = true;
                            double_quote++;
                        }
                        else if(cnt!=1 && !dquote_check){
                            info.push_back(substr);
                        }
                        else if(cnt ==4 && dquote_check){
                            info.at((info.size() - 1)) += substr;
                        }
                        else if(cnt!=1 && dquote_check){
                            info.at((info.size() - 1)) += substr;
                            dquote_check = false;
                            double_quote++;
                        }
                    } else {
                        if (substr == "") {
                            info.push_back("");
                        } else if (dquote_check) {
                            info.at((info.size() - 1)) += substr;
                        } else {
                            info.push_back(substr);
                        }
                    }
                }
            }
//            srand(time(nullptr)); // seed the random number generator
            double random_num = (double) std::rand() / RAND_MAX * 100;
            info.push_back(to_string( int(floor(random_num))));
//            for (int i = 0; i < 11; ++i) {
//                cout<<"  Place"<<i<<": "<<info.at(i)<<" ";
//            }
//            cout<<endl;
//            cout<<"            ";
//            for (int i = 0; i < genreList.size(); ++i) {
//                cout<<genreList.at(i)<<" ";
//            }
//            cout<<endl;
            node movie(genreList, info);
          //  Movie m1(info.at(0), info.at(2), info.at(7), info.at(6), stoi(info.at(10)));
          //  movieHeap.insert(m1);
            list.saveNode(movie, info.at(7));
            temp++;
        }
    }
    while(programRun) {
        string userInt;
        cout << "Welcome to Netflix Ranking!" << endl;
        cout << "Where you can find the best top 10 movie & Tv series" << endl;
        cout << "*********************************" << endl;
        cout << "1. Search top 10 Netflix show by released year" << endl;
        cout << "2. Exit" << endl;
        cin >> userInt;

        if (userInt == "1") {
            string year;
            cout << "Please enter a year" << endl;
            cin >> year;
            if (!list.yearExisted(year)){
                cout << "No Netflix show is found!" << endl;
            } else {
                cout << "Merge sort" << endl;
                auto start_AJ = high_resolution_clock::now();
                list.printRankAJ(year);
                auto stop_AJ = high_resolution_clock::now();
                auto duration_AJ = duration_cast<microseconds>(stop_AJ - start_AJ);
                cout << "Time for merge sort to compute:" << duration_AJ.count() << " microseconds" << endl;
//                auto start_MH = high_resolution_clock::now();
                cout << endl;
//                cout << "Max Heap" << endl;
//                MaxHeap copyHeap(movieHeap);
//                printTopTenRatedMovies(copyHeap, year);
//                auto stop_MH = high_resolution_clock::now();
//                auto duration_MH = duration_cast<microseconds>(stop_MH - start_MH);
//                cout << "Time for Max Heap to compute:" << duration_MH.count() << " microseconds" << endl;
//                cout << endl;
                for (int i = 0; i < list.size(year); ++i) {
                    node m1 = list.currentNode(year,i);
                      movieHeap.insert(m1);
                }
                cout << "Heap sort" << endl;
             //   MaxHeap copyHeap(movieHeap);
                auto start_MH = high_resolution_clock::now();
                printTopTenRatedMovies(movieHeap, year);
                auto stop_MH = high_resolution_clock::now();
                auto duration_MH = duration_cast<microseconds>(stop_MH - start_MH);
                cout << "Time for heap sort to compute:" << duration_MH.count() << " microseconds" << endl;
                cout << endl;
            }
        } else if (userInt == "2") {
            programRun = false;
        }
    }
    //list.printRankAJ("2012");
}