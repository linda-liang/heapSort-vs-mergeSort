//
// Created by wwwww on 4/21/23.
//

#include "node.h"

node::node(vector<string> _genre, vector<string> _info)
{
    for(const auto & i : _genre)
        genre.push_back(i);
    for(const auto & i : _info)
        info.push_back(i);
    rank = stoi(info.at(info.size() - 1));
    name = info.at(2);
    year = info.at(7);
}