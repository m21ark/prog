#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream> // needed to work with files

using namespace std;

int getNum(const string &s){
    //returns the time score of person in file line string
    string score;
    bool numStart = false;
    for(char c:s){
        if(c=='-') numStart = true;
        if(numStart) score+=c;
    }
    score.erase(0,1);
    return stoi(score);
}

string getName(const string &s){
    //returns the name of person in file line string
    string name;
    for(char c:s){
        if(c!='-') name+=c;
        else break;
    }
    name.erase(name.length()-1,1);
    return name;
}

vector<string> readFromFile(string fileName){
    //returns a vector with each line name of file
    ifstream file (fileName);
    string line;
    vector<string> fnames;

    int i = 0;
    while(getline(file,line)){
        if(i>1) fnames.push_back(line);
        i++;
    }

    file.close();
    return fnames;
}

void sortNamesOrder(vector<string> &v){
    //sorts lines based on their time score
    int n = v.size();
    for (int i = 0; i < n; i++) for(int j = 0 ;j < n-i-1; j++) 
    if(getNum(v[j]) > getNum(v[j+1])){string aux = v[j];v[j] = v[j+1];v[j+1] = aux;} 
}


void writeNameToFile(string fileName, string name, int score){
    //rewrites file with new name and everything sorted and formatted

    vector<string> list = readFromFile(fileName); //load file names

    string newName = name + " - " + to_string(score);

    //add name and sort by time score
    list.push_back(newName);
    sortNamesOrder(list);

    //save to file
    ofstream file (fileName);
    file<<setfill(' ')<<left<<setw(15)<<"Player "<<" - Time"<<endl;
    file<<"----------------------"<<endl;
    for(string s: list) 
        file<<setfill(' ')<<left<<setw(15)<<getName(s)<<" - "<<setfill('0')<<setw(3)<<right<<to_string(getNum(s))<<endl;
    file.close();
}


int main(){
    string name = "ABC DEF";
    int time = 8;
    writeNameToFile("MAZE_WINNERSXX.txt",name,time);
}