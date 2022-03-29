#include "Notebook.hpp"

using ariel::Direction;
using namespace std;

const int MIN_CHAR = 32;
const int MAX_LINE_LENGHT = 100;
const int MAX_CHAR = 125;

vector<char> empty_line(MAX_LINE_LENGHT, '_'); // This is a vector for creating a new line with "_" chars

/*
We will start with the read function
*/
string ariel::Notebook::read(int page, int row, int column, Direction direction, int length)
{
    /*
    First thing we will check is if the location we got is in the notebook and not out of bounds,
    this check will help us in every other function beacuse the "read" function will be in every other function first.
    */
    if ((direction == Direction::Horizontal && column + length > MAX_LINE_LENGHT) || (column < 0 || page < 0 || row < 0 || length < 0))
    {
        throw("Please check that you have entered a location that is not out of bounds");
    }

    string result;

    if (direction == Direction::Horizontal)
    {
        // Converte the line into a string
        string line_to_string = to_string(page) + "-" + to_string(row);

        // Check if the line we are at is empty if so put the vector inside
        if (sheet[line_to_string].empty())
        {
            sheet[line_to_string] = empty_line;
        }

        // Insert the data we read into the string that we are gonna return
        for (int i = 0; i < length; i++)
        {
            result += sheet[line_to_string].at((unsigned int)(column + i));
        }
    }

    else // Vertical direction reading
    {
        for (int i = 0; i < length; i++)
        {
            string line_to_string = to_string(page) + "-" + to_string(row + i);

            if (sheet[line_to_string].empty())
            {
                sheet[line_to_string] = empty_line;
            }

            result += sheet[line_to_string].at((unsigned int)(column));
        }
    }
    return result;
}

/*
 In this function we will write to the notebook
*/
void ariel::Notebook::write(int page, int row, int column, Direction direction, const string &data)
{
    int string_length = data.length();

    /*
    Firstly we will check if the user entered a char that is smaller than 32 or higher than 125 in the ascii table
    */
    for (unsigned long i = 0; i < string_length; i++)
    {
        if (data[i] < MIN_CHAR || data[i] > MAX_CHAR)
        {
            throw("Please check that you didnt enter a char that is off limits");
        }
    }

    /*
    Now we will try to read from the location we got so we could see if we can write there
    */
    string curr_str = read(page, row, column, direction, string_length);

    // Check if if string that we read is "empty" if not we cant write
    if (curr_str != string(data.length(), '_'))
    {
        throw("You already wrote or erased here, you cant write here again");
    }

    if (direction == Direction::Horizontal)
    {
        // Converte the line into a string
        string line_to_string = to_string(page) + "-" + to_string(row);

        // Writing to the notebook horizontaly
        for (int i = 0; i < string_length; i++)
        {
            sheet[line_to_string].at((unsigned int)(column + i)) = data[(unsigned long)i];
        }
    }

    else
    {
        for (int i = 0; i < string_length; i++)
        {
            // Converte the line into a string
            string line_to_string = to_string(page) + "-" + to_string(row + i);

            // Write to the notebook verticaly
            sheet[line_to_string].at((unsigned int)(column)) = data[(unsigned long)i];
        }
    }
}

/*
Here is the erase function that changes the chars from the location that we got for the "lenght" we got to the char '~' 
*/
void ariel::Notebook::erase(int page, int row, int column, Direction direction, int length)
{
    string curr_str = read(page, row, column, direction, length);

    if (direction == Direction::Horizontal)
    {
        string line_to_string = to_string(page) + "-" + to_string(row);

        // We are changing every char to '~'
        for (int i = 0; i < length; i++)
        {
            sheet[line_to_string].at((unsigned int)(column + i)) = '~';
        }
    }

    else
    {
        for (int i = 0; i < length; i++)
        {
            string line_to_string = to_string(page) + "-" + to_string(row + i);
            sheet[line_to_string].at((unsigned int)(column)) = '~';
        }
    }
}

/*
This is the show function 
*/
string ariel::Notebook::show(int page)
{
    if (page < 0)
    {
        throw("Please enter a vaild positive page number");
    }

    string result;

    for (int i = 0; i < MAX_LINE_LENGHT; i++)
    {
        result += read(page, i, 0, Direction::Horizontal, MAX_LINE_LENGHT);
    }

    return result;
}