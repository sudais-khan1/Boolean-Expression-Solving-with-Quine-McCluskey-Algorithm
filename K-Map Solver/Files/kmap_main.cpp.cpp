#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cstring>
#include <cmath>
#include "QM.h"
#include "QM.cpp"
#include "functions.h"
using namespace std;

//------------------------------------------------------------------------------------------

const int MAX_ROWS = 4;
const int MAX_COLS = 4;

int main()
{
    char check = 'y';
    int prompt;

    while (check == 'y')
    { // Layout of the Main Menu
        cout << "\n============ :Choose an Option: ============" << endl;
        cout << "1 => Generate Truth Table" << endl;
        cout << "2 => Solve Boolean Expression" << endl;
        cout << "============================================" << endl;
        cout << "Enter Here: ";

        cin >> prompt;
        if (prompt == 1)
        {
            genTruthTable();
            cout << "\nWould you like to enter another expression? (y/n)" << endl;
            cin >> check;
        }
        else if (prompt == 2)
        {
            vector<string> minterms;
            int num_variables;
            cout << endl
                 << "===== :Welcome to Karnaugh Map Solver: =====\n"
                 << "============================================\n"
                 << "Enter the number of Variables (Literals):" << endl;
            cin >> num_variables;
            QM QM_Object(num_variables);

            if (num_variables > 8 || num_variables < 2)
            {
                cout << "Invalid number of Variables (RANGE: 2-8)" << endl;
                continue;
            }

            //===========================================================
            if (num_variables >= 2 && num_variables < 5)
            {
                int rows, cols;
                switch (num_variables)
                {
                case 2:
                {
                    rows = 2;
                    cols = 2;
                }
                break;
                case 3:
                {
                    rows = 2;
                    cols = 4;
                }
                break;
                case 4:
                {
                    rows = 4;
                    cols = 4;
                }
                break;
                default:
                    break;
                }

                // Create a grid of size rows x cols initialized with empty spaces
                vector<vector<char>> grid(rows, vector<char>(cols, ' '));

                displayKMapGrid(grid, rows, cols, num_variables);
                cout << endl;
                // Input characters into the grid
                int i = 0;
                for (int r = 0; r < rows; ++r)
                {
                    for (int c = 0; c < cols; ++c)
                    {
                        char inputChar;
                        while (true)
                        {
                            cout << "Enter Minterm (m" << i << "): ";
                            cin >> inputChar;
                            if (inputChar == '1' || inputChar == '0')
                            {
                                break;
                            }
                            cout << "Invalid Value!" << endl;
                        }
                        if (inputChar == '1')
                        {
                            minterms.push_back(QM_Object.pad(QM_Object.decToBin(i)));
                        }
                        // Fills boxes according to gray code
                        if (c == 2 && r == 2)
                        {
                            grid[r + 1][c + 1] = inputChar;
                        }
                        else if (c == 3 && r == 3)
                        {
                            grid[r - 1][c - 1] = inputChar;
                        }
                        else if (c == 3 && r == 2)
                        {
                            grid[r + 1][c - 1] = inputChar;
                        }
                        else if (c == 2 && r == 3)
                        {
                            grid[r - 1][c + 1] = inputChar;
                        }
                        else if (c == 2)
                        {
                            grid[r][c + 1] = inputChar;
                        }
                        else if (c == 3)
                        {
                            grid[r][c - 1] = inputChar;
                        }
                        else if (r == 2)
                        {
                            grid[r + 1][c] = inputChar;
                        }
                        else if (r == 3)
                        {
                            grid[r - 1][c] = inputChar;
                        }
                        else
                        {
                            // Limit input to a single character
                            grid[r][c] = inputChar;
                        }
                        // Display updated grid
                        system("cls");
                        displayKMapGrid(grid, rows, cols, num_variables);
                        i++;
                    }
                }
            }
            //=====================================================================
            if (num_variables >= 5)
            {
                string temp = "";
                cout << "\nEnter the Minterms separated by Commas (RANGE: 0-" << pow(2, num_variables) - 1 << ") e.g: F(0,1,2,3,---):" << endl;
                cin >> temp;

                // splitting the input
                istringstream f(temp);
                string s;
                while (getline(f, s, ','))
                {
                    // cout << s << endl;
                    int t = atoi(s.data());
                    minterms.push_back(QM_Object.pad(QM_Object.decToBin(t)));
                }
            }

            sort(minterms.begin(), minterms.end());

            do
            {
                minterms = QM_Object.reduce(minterms);
                sort(minterms.begin(), minterms.end());
            } while (!QM_Object.VectorsEqual(minterms, QM_Object.reduce(minterms)));

            int i;
            cout << "\nThe Reduced Boolean Expression in (SOP) form is:" << endl;
            for (i = 0; i < minterms.size() - 1; i++)
                cout << QM_Object.getValue(minterms[i]) << "+";
            cout << QM_Object.getValue(minterms[i]) << endl;

            cout << "\nWould you like to enter another expression? (y/n)" << endl;
            cin >> check;
        }
        else
        {
            cout << "\nWrong Option! Please choose from list (1-2)" << endl;
        }
    }
    cout << endl
         << "Program exited!" << endl
         << "\n------------------END-------------------" << endl;
    return 0;
}
