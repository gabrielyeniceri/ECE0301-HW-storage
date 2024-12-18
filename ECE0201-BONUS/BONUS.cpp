#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <bitset>
//bitset was chosen for easier handling with binary and the ability to not have a specific set of variables
#include <algorithm>
using namespace std;

//this counts the number of 1s in binary
int countOnes(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

//this checks if a term coverts a minterm
bool covers(int minterm, const string& implicant) {
    string binary = bitset<16>(minterm).to_string();
    binary = binary.substr(binary.length() - implicant.size());
    for (size_t i = 0; i < implicant.size(); ++i) {
        if (implicant[i] != '-' && implicant[i] != binary[i]) {
            return false;
        }
    }
    return true;
}

//this finds the prime implicants
vector<string> findPrimeImplicants(const vector<int>& minterms, int numVars) {
    vector<vector<string>> groups(numVars + 1);
    map<string, bool> used;
    set<string> primeImplicants;
    for (int minterm : minterms) {
        string binary = bitset<16>(minterm).to_string().substr(16 - numVars);
        groups[countOnes(minterm)].push_back(binary);
        used[binary] = false;
    }
    bool done = false;
    while (!done) {
        done = true;
        vector<vector<string>> newGroups(numVars);
        map<string, bool> newUsed;

        for (size_t i = 0; i < groups.size() - 1; ++i) {
            for (const string& term1 : groups[i]) {
                for (const string& term2 : groups[i + 1]) {
                    int diffCount = 0;
                    string combined;
                    for (size_t j = 0; j < term1.size(); ++j) {
                        if (term1[j] != term2[j]) {
                            diffCount++;
                            combined += '-';
                        } else {
                            combined += term1[j];
                        }
                    }
                    if (diffCount == 1) {
                        newGroups[i].push_back(combined);
                        used[term1] = true;
                        used[term2] = true;
                        newUsed[combined] = false;
                        done = false;
                    }
                }
            }
        }

        for (const auto& group : groups) {
            for (const string& term : group) {
                if (!used[term]) {
                    primeImplicants.insert(term);
                }
            }
        }

        groups = newGroups;
        used = newUsed;
    }

    return vector<string>(primeImplicants.begin(), primeImplicants.end());
}

//this function finds the essential prime implicants
vector<string> findEssentialPrimeImplicants(const vector<int>& minterms, const vector<string>& primeImplicants) {
    map<int, vector<int>> coverage;
    vector<string> essentialImplicants;
    set<int> essentialIndices;

    for (size_t i = 0; i < primeImplicants.size(); ++i) {
        for (int minterm : minterms) {
            if (covers(minterm, primeImplicants[i])) {
                coverage[minterm].push_back(i);
            }
        }
    }

    for (const auto& entry : coverage) {
        if (entry.second.size() == 1) {
            essentialIndices.insert(entry.second[0]);
        }
    }

    for (int index : essentialIndices) {
        essentialImplicants.push_back(primeImplicants[index]);
    }

    return essentialImplicants;
}
//this converts the terms from binary to decimal product terms
string binaryToProductTerm(const string& binary) {
    string term;
    for (size_t i = 0; i < binary.size(); ++i) {
        if (binary[i] == '1') term += "+" + to_string(i + 1) + " ";
        if (binary[i] == '0') term += "-" + to_string(i + 1) + " ";
    }
    return term;
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        cerr << "Error: Could not open input/output files." << endl;
        return 1;
    }

    vector<int> minterms;
    int minterm;
    while (inputFile >> minterm) {
        minterms.push_back(minterm);
    }
    inputFile.close();

    int numVars = ceil(log2(*max_element(minterms.begin(), minterms.end()) + 1));
    vector<string> primeImplicants = findPrimeImplicants(minterms, numVars);
    vector<string> essentialImplicants = findEssentialPrimeImplicants(minterms, primeImplicants);

    outputFile << "Prime Implicants:\n";
    for (const string& implicant : primeImplicants) {
        outputFile << binaryToProductTerm(implicant) << "\n";
    }

    outputFile << "\nEssential Prime Implicants:\n";
    for (const string& implicant : essentialImplicants) {
        outputFile << binaryToProductTerm(implicant) << "\n";
    }

    outputFile.close();
    return 0;
}