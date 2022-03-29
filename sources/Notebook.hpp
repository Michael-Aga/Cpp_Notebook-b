#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Direction.hpp"

using namespace std;

namespace ariel
{
    class Notebook
    {
    private:
        unordered_map<string, vector<char>> sheet;

    public:
        void write(int page, int row, int column, Direction direction, const string &data);
        string read(int page, int row, int column, Direction direction, int length);
        void erase(int page, int row, int column, Direction direction, int length);
        string show(int page);
    };
}