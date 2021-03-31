#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream> // needed to work with files

using namespace std;

vector<string> loadMap(string fileName){
    //gets map file 
    ifstream file (fileName);
    string line;
    vector<string> map;

    getline(file,line); //get rid of first line
    //loads map lines to vector
    while(getline(file,line)) map.push_back(line);
    file.close();

    return map;
}

int main(){
    vector<string> map = loadMap("MAZE_XX.txt");
    //stores map size to height and lenght vars
    int height = map.size(); 
    int lenght = map[0].size();
    
    printf("Map size = %d x %d\n\n",height,lenght);
    for(string i:map) cout<<i<<endl;
}