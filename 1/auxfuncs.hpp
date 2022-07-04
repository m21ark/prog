// T07_G07 
#ifndef auxfuncs
#define auxfuncs
using namespace std;

/*
Removes spaces in the beginning and end of string
@param &s string to be strip
*/
void stripStr(string &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            s.erase(i, 1);
            i--;
        }
        else
            break;
    }
    for (int i = s.size() - 1; i >= 0; i--)
        if (s[i] == ' ')
            s.erase(i, 1);
        else
            break;
}

/*
Evaluates if cin buffer is empty
@return false if there is something in buffer and true if empty
*/
bool emptyCin()
{
    string bufferContent;
    getline(cin, bufferContent);
    stripStr(bufferContent);
    if (bufferContent == "")
        return true;
    return false;
}

/*
Keeps track of how many seconds have passed since it's first call
@return seconds since first call
*/
time_t timeElapsed()
{
    //this func returns how many seconds since its first call
    static time_t first = time(NULL);
    return time(NULL) - first;
}

/*
Gets name from a line of the file "winners"
@param &s string line which to extract name from
@return extracted name 
*/
string getName(const string &s)
{
    return s.substr(0, s.find('-') - 1);
}

/*
Gets score from a line of the file "winners"
@param &s string line which to extract number from
@return extracted number/score 
*/
int getNum(const string &s)
{
    return stoi(s.substr(s.find('-') + 2, 10));
}

/*
Creates a vector with each line of a file
@param fileName file which to extract from
@return vector with the lines read from file
*/
vector<string> readFromFile(string fileName)
{
    //returns a vector with each line name of file
    ifstream file(fileName);
    string line;
    vector<string> fnames;
    if (file.fail())
    {
        return {"NULL_FILE"};
    }

    //get rid of 2 first lines
    getline(file, line);
    getline(file, line);

    //stores remainder lines in vector
    while (getline(file, line))
    {
        stripStr(line);
        if (line != "" && line != "\n")
            fnames.push_back(line);
    }

    file.close();
    return fnames;
}

/*
Sorts winners file vector based on score
@param &v vector with the file lines to be sorted
*/
void sortNamesOrder(vector<string> &v)
{
    //quick sort Names in file by their time score (descendent)
    int n = v.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (getNum(v[j]) > getNum(v[j + 1]))
            {
                string aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
}

/*
Writes a new winner to file "winners"
@param fileName file where to write
@param name name of winner
@param score winner's time/score
*/
void writeNameToFile(string fileName, string name, int score)
{
    //rewrites file with new name and everything sorted and formatted

    vector<string> list = readFromFile(fileName); //load file names

    if (list.size() == 1 && list[0] == "NULL_FILE")
    {
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
        file << setfill(' ') << left << setw(15) << getName(s) << " - " << setfill('0') << setw(3) << right << to_string(getNum(s)) << endl;
        cout << setfill(' ') << left << setw(15) << getName(s) << " - " << setfill('0') << setw(3) << right << to_string(getNum(s)) << endl;
        cout << endl;
        file.close();
    }
    else
    {
        //if winners file already exists
        string newName = name + " - " + to_string(score);

        //add name and sort by time score
        list.push_back(newName);
        sortNamesOrder(list);

        //save to file
        ofstream file(fileName);
        if (file.fail())
        {
            cout << endl
                 << "ERRO DE FICHEIRO NAO ENCONTRADO!" << endl;
        }
        else
        {
            file << setfill(' ') << left << setw(15) << "Player "
                 << " - Time" << endl;
            file << "----------------------" << endl;
            cout << endl
                 << setfill(' ') << left << setw(15) << "Player "
                 << " - Time" << endl;
            cout << "----------------------" << endl;
            for (string s : list)
            {
                file << setfill(' ') << left << setw(15) << getName(s) << " - " << setfill('0') << setw(3) << right << to_string(getNum(s)) << endl;
                cout << setfill(' ') << left << setw(15) << getName(s) << " - " << setfill('0') << setw(3) << right << to_string(getNum(s)) << endl;
            }
            cout << endl;
            file.close();
        }
    }
}

/*
Verify if map number is valid by searching file names
@param n map number
@return true if map is valid and false otherwise 
*/
bool validMapNum(int n)
{
    // accept 0 as valid to exit to main menu
    if (n == 0)
        return true;
    if (n > 99 || n < 0)
        return false;
    string num = to_string(n);
    if (n < 10)
    {
        ifstream file("MAZE_0" + num + ".TXT");
        return file.good();
    }
    else
    {
        ifstream file("MAZE_" + num + ".TXT");
        return file.good();
    }
}

/*
Extracts map lines from file and places them in vector
@param fileName where to locate map to be read
@return vector with map lines
*/
vector<string> loadMap(string fileName)
{
    ifstream file(fileName);
    string line;
    vector<string> map;

    getline(file, line); //get rid of first line
    while (getline(file, line))
        map.push_back(line);

    file.close();
    return map;
}

#endif