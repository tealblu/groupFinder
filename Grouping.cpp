/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Represents an occupied square in the grid
//Do not modify the GridSquare class or its member functions
class GridSquare
{
    private:
        int row, col;
    public:
        GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square
        GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square
        //Compare with == operator, used in test cases
        bool operator== (const GridSquare r) const
        {
            if ((row == r.row) && (col == r.col))
            {
                return true;
            }
            return false;
        }
        int getRow() { return row; } //return row value
        int getCol() { return col; } //return column value
        //Output using << operator, used in Grouping::printGroups()
        friend ostream& operator<< (ostream& os, const GridSquare obj);
};

//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

/*
Groups squares in 10x10 grid upon construction
Additional private helper functions may be added
Need to implement the constructor that takes a file name
as well as findGroup
The findGroup function's parameter list may be changed based
on how the function is implemented
*/
class Grouping
{
    private:
        int grid[10][10];
        vector<vector<GridSquare>> groups;
    public:
        Grouping() : grid{},groups() {} //Default constructor, no groups
        Grouping(string fileName); //Implement this function
        vector<GridSquare> findGroup(int r, int c, vector<GridSquare> group); //Implement this function (recursive)
        bool isFound(int r, int c, vector<GridSquare> group); // Determines whether a cell is already stored in groups
        void printGroups() //Displays grid's groups of squares
        {
            for(int g=0; g<groups.size(); g++)
            {
                cout << "Group " << g+1 << ": ";
                for(int s=0; s<groups[g].size(); s++)
                {
                    cout << " " << groups[g][s];
                }
                cout << endl;
            }
        }
        vector<vector<GridSquare>> getGroups() //Needed in unit tests
        {
            return groups;
        }
};

//Implement the (parameterized) constructor and findGroup functions below

//Parameterized constructor implementation
Grouping::Grouping(string fileName) {
    string temp;
    vector<GridSquare> group;
    int row=0;
    int col=0;

    // Opening the file
    ifstream file(fileName);

    // Parsing the file into grid
    while(getline(file,temp)) {
        row = 0;
        for(int count=0;count<10;count++) {
            if(temp[count]=='.') {
                grid[row][col] = 0;
            } else {
                grid[row][col] = 1;
            }
            col++;
        }
        row++;
    }

    puts("Grid created!");
    for(int row=0;row<10;row++) {
        for(int col=0;col<10;col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    } 

    // Traversing the grid
    for(row=0;row<10;row++) {
        for(col=0;col<10;col++) {
            // Clear the singular group vector before each pass
            group.clear();

            // Calling the recursive function on each element
            group = findGroup(row,col,group);

            // If a group was found, add it to the vector of vectors of gridsquares
            if(group.size()>0) {
                groups.push_back(group);
            }
        }
    }
}


// Checks to see if coordinates are already in the vector of vectors of GridSquares
bool Grouping::isFound(int r, int c, vector<GridSquare> group) {
    // For loop to traverse the outside vector
    for(int out=0;out<groups.size(); out++) {
        // For loop to traverse the inside vectors
        for(int in=0;in<groups[out].size();in++) {
            // Determines whether the element is equal to the rows and columns in question
            if(groups[out][in].getRow()==r && groups[out][in].getCol()==c) {
                return true;
            }
        }
    }

    for(int count=0;count<group.size();count++) {
        if(group[count].getRow()==r && group[count].getCol()==c) {
            return true;
        }
    }

    return false;
}

// Determines whether a set of coordinates exist in a grid
bool isValid(int r, int c) {
    // If coordinates are in bounds, return true. Else, return false.
    if(r<=9 && c<=9 && r>=0 && c>=0) {
        return true;
    } else {
        return false;
    }
}

// Given coordinates, determines whether a group exists
vector<GridSquare> Grouping::findGroup(int r, int c, vector<GridSquare> group) {
    // Test to see if given cell is an X
    if(grid[r][c]==1 && isValid(r,c) && !isFound(r,c,group)) {
        // Add to vector of coordinates
        GridSquare temp1(r,c);
        group.push_back(temp1);

        // Search right side:
        if(grid[r][c+1]==1 && isValid(r,c+1)) {
            if(!isFound(r,c+1,group)) {
                group = findGroup(r,c+1,group);
            }
     }

        // Search bottom side:
        if(grid[r-1][c]==1 && isValid(r-1,c)) {
            if(!isFound(r-1,c,group)) {
                group = findGroup(r-1,c,group);
            }
        }

        // Search left side:
        if(grid[r][c-1]==1 && isValid(r,c-1)) {
            if(!isFound(r,c-1,group)) {
                group = findGroup(r,c-1,group);
            }
        }

        // Search top side:
        if(grid[r+1][c]==1 && isValid(r+1,c)) {
            if(!isFound(r+1,c,group)) {
                group = findGroup(r+1,c,group);
            }
        }
    }

    return group;
}




//Simple main function to test Grouping
int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}