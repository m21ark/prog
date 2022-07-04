//T07_G07
#include "auxfuncs.hpp"

using namespace std;


void stripStr(string &s) {
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            s.erase(i, 1);
            i--;
        } else
            break;
    }
    for (int i = s.size() - 1; i >= 0; i--)
        if (s[i] == ' ')
            s.erase(i, 1);
        else
            break;
}


bool emptyCin() {
    string bufferContent;
    getline(cin, bufferContent);
    stripStr(bufferContent);
    if (bufferContent == "")
        return true;
    return false;
}


time_t timeElapsed() {
    static time_t first = time(NULL);
    return time(NULL) - first;
}


string getName(const string &s) {
    return s.substr(0, s.find('-') - 1);
}


int getNum(const string &s) {
    return stoi(s.substr(s.find('-') + 2, 10));
}


vector <string> readFromFile(string fileName) {
    //returns a vector with each line name of file
    ifstream file(fileName);
    if (file.fail()) {
        return {"No winners yet!"};
    }

    string line;
    vector <string> fnames;
    //get rid of 2 first lines
    getline(file, line);
    getline(file, line);

    //stores remainder lines in vector
    while (getline(file, line)) {
        stripStr(line);
        if (line != "" && line != "\n")
            fnames.push_back(line);
    }

    file.close();
    return fnames;
}


void showWinners(const string &fileName) {
    //shows winner file
    ifstream file(fileName);
    string line;

    if (file.fail()) {
        cout << "Empty List. There are no winners yet!" << endl;
    } else {
        cout << endl << setfill('=') << setw(22) << "";
        cout << endl << setfill(' ') << left << setw(15) << "Player " << " - Time" << endl;
        cout << "----------------------" << endl;

        //get rid of 2 first lines
        getline(file, line);
        getline(file, line);

        //stores remainder lines in vector
        while (getline(file, line)) {
            stripStr(line);
            if (line != "" && line != "\n")
                cout << line << endl;
        }
        cout << setfill('=') << setw(22) << "" << endl << endl;

        file.close();
    }
}


void sortNamesOrder(vector <string> &v) {
    //quick sort Names in file by their time score (descendent)
    int n = v.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (getNum(v[j]) > getNum(v[j + 1])) {
                string aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
}


void writeNameToFile(string fileName, string name, int score) {
    //rewrites file with new name and everything sorted and formatted

    vector <string> list = readFromFile(fileName); //load file names

    if (list.size() == 1 && list[0] == "No winners yet!") {
        //if winners file doesn't exist

        ofstream file(fileName);
        file << setfill(' ') << left << setw(15) << "Player "
             << " - Time" << endl;
        file << "----------------------" << endl;
        cout << endl
             << setfill(' ') << left << setw(15) << "Player "
             << " - Time" << endl;
        cout << "----------------------" << endl;

        string s = name + " - " + to_string(score);
        file << setfill(' ') << left << setw(15) << getName(s) << " - " << setfill('0') << setw(3) << right
             << to_string(getNum(s)) << endl;
        cout << setfill(' ') << left << setw(15) << getName(s) << " - " << setfill('0') << setw(3) << right
             << to_string(getNum(s)) << endl;
        cout << endl;
        file.close();
    } else {
        //if winners file already exists
        string newName = name + " - " + to_string(score);

        //add name and sort by time score
        list.push_back(newName);
        sortNamesOrder(list);

        //save to file
        ofstream file(fileName);
        if (file.fail()) {
            cerr << endl
                 << "ERRO DE FICHEIRO NAO ENCONTRADO!" << endl;
        } else {
            file << setfill(' ') << left << setw(15) << "Player "
                 << " - Time" << endl;
            file << "----------------------" << endl;
            cout << endl
                 << setfill(' ') << left << setw(15) << "Player "
                 << " - Time" << endl;
            cout << "----------------------" << endl;
            for (string s : list) {
                file << setfill(' ') << left << setw(15) << getName(s) << " - " << setfill('0') << setw(3) << right
                     << to_string(getNum(s)) << endl;
                cout << setfill(' ') << left << setw(15) << getName(s) << " - " << setfill('0') << setw(3) << right
                     << to_string(getNum(s)) << endl;
            }
            cout << endl;
            file.close();
        }
    }
}


bool validMapNum(int n) {
    // accept 0 as valid to exit to main menu
    if (n == 0)
        return true;
    if (n > 99 || n < 0)
        return false;
    string num = to_string(n);
    if (n < 10) {
        ifstream file("MAZE_0" + num + ".TXT");
        return file.good();
    } else {
        ifstream file("MAZE_" + num + ".TXT");
        return file.good();
    }
}


string createBlankString(const int &n) {
    string aString = "";
    //add spaces until the line has the desired length
    for (int i = 0; i < n; i++) {
        aString += " ";
    }
    return aString;
}

vector <string> createBlankVector(const int &n, const string &aBlankString) {
    vector <string> temp;
    //add lines until the vector has the desired size
    for (int i = 0; i < n; i++) {
        temp.push_back(aBlankString);
    }
    return temp;
}