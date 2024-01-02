#include <iostream>
using namespace std;

#ifndef functions_H
#define functions_H

void genTruthTable()
{
    int num_literals;
    int num_trueMins;
    int Y = 0;

    // Takes inputs from User
    cout << "Enter number of Literals (MAX : 14): " << endl;
    cin >> num_literals;

    int num_totalMins = pow(2, num_literals);

    cout << "Enter number of Minterms for which the Output is 1: " << endl;
    cin >> num_trueMins;

    int MinsDefault[num_totalMins];
    int MinsTrue[num_trueMins];
    int MinsInBin[num_totalMins][num_literals] = {{}};

    cout << "Enter the True Minterms (RANGE : 0 - " << num_totalMins - 1 << ")(e.g : 0 1 2 3 - - -) : " << endl;

    // Saves all input minterms in an array
    for (int i = 0; i < num_trueMins; i++)
    {
        cin >> MinsTrue[i];
    }

    // Generates an array having all minterms
    for (int i = 0; i < num_totalMins; i++)
    {
        MinsDefault[i] = i;
    }

    // Converts all Minterms to Their Corresponding Binary
    for (int i = 0; i < num_totalMins; i++)
    {
        int y = MinsDefault[i];
        int arr[num_literals] = {0};
        int a;
        int count = 1;

        while (y > 0)
        {
            a = y % 2;
            y = y / 2;
            arr[num_literals - count] = a;
            count++;
        }

        for (int k = 0; k < num_literals; k++)
        {
            MinsInBin[i][k] = arr[k];
        }
    }

    // Layout of the truth table
    cout << "\n---------------Truth Table---------------" << endl;
    cout << "Minterms | ";
    for (int i = 0; i < num_literals; i++)
    {
        char var = 'A' + i;
        cout << var << " ";
    }
    cout << "| Outputs (Y)";
    cout << "\n-----------------------------------------\n";

    // Contents of the truth table
    for (int i = 0; i < num_totalMins; i++)
    {
        if (MinsDefault[i] < 10)
        {
            cout << "     m" << MinsDefault[i] << "  | ";
        }
        else if (MinsDefault[i] >= 10 && MinsDefault[i] < 100)
        {
            cout << "    m" << MinsDefault[i] << "  | ";
        }
        else if (MinsDefault[i] >= 100 && MinsDefault[i] < 1000)
        {
            cout << "   m" << MinsDefault[i] << "  | ";
        }
        else
        {
            cout << "  m" << MinsDefault[i] << "  | ";
        }

        for (int j = 0; j < num_literals; j++)
        {
            cout << MinsInBin[i][j] << " ";
        }

        Y = 0;
        for (int j = 0; j < num_trueMins; j++)
        {
            if (MinsTrue[j] == i)
            {
                Y = 1;
                break;
            }
        }
        cout << "|  " << Y;
        cout << endl;
    }
    cout << "-----------------------------------------\n";
}

void displayKMapGrid(const vector<vector<char>> &grid, int rows, int cols, int vars)
{
    string indices[4] = {"00", "01", "11", "10"};

    // Display the column indices
    if (vars == 2)
    {
        cout << "\n  \\ B |" << endl;
        cout << " A \\  | ";
    }
    if (vars == 3)
    {
        cout << "\n  \\BC |" << endl;
        cout << " A \\  | ";
    }
    if (vars == 4)
    {
        cout << "\n  \\CD |" << endl;
        cout << "AB \\  | ";
    }

    for (int c = 0; c < cols; ++c)
    {
        cout << indices[c] << "   ";
    }
    cout << endl
         << "------";

    for (int c = 0; c < cols; ++c)
    {
        cout << "+----";
    }
    cout << "+" << endl;

    // Display the grid
    for (int r = 0; r < rows; ++r)
    {
        cout << "  " << indices[r] << " ";
        for (int c = 0; c < cols; ++c)
        {
            cout << " | " << grid[r][c] << " ";
        }
        cout << " |" << endl;

        // Print horizontal separator
        cout << "      ";
        for (int c = 0; c < cols; ++c)
        {
            cout << "+----";
        }
        cout << "+" << endl;
    }
}

#endif