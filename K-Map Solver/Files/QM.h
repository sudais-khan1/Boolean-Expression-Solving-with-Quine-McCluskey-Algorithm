#include <vector>
#include <string>
#include <algorithm>
#ifndef QM_H
#define QM_H
using namespace std;
// Main class
class QM
{
public:
    int VARIABLES;
    string dontcares;

    QM(int a);

    // function to get the boolean term letters
    vector<string> getVars();

    // function to convert decimal to binary
    string decToBin(int n);
    

    // function to pad zeros to the binary equivalent of digits. Eg: 10 in 4bit is turned into 0010
    string pad(string bin);

    // function to check if two terms differ by just one bit
    bool isGreyCode(string a, string b);

    // function to replace complement terms with don't cares. Eg: 0110 and 0111 becomes 011-
    string replace_complements(string a, string b);

    // function to check if string b exists in vector a
    bool in_vector(vector<string> a, string b);

    // function to reduce minterms
    vector<string> reduce(vector<string> minterms);

    // Converting the boolean minterm into the variables. Eg: 011- becomes a'bc
    string getValue(string a);

    // function to check if 2 vectors are equal
    bool VectorsEqual(vector<string> a, vector<string> b);
};
#endif