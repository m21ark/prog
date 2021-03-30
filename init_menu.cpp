#include <iostream>
#include <iomanip>

using namespace std;

bool validMapNum(int n){
    //TODO (Verify if valid map is picked and return true in that case) 
    if (n>99 || n<0) return false;
    return true;
} 

int askMapNum(){
    while(true)
    {
        cout<<endl<<"Please choose a number between 1-99 (0 to exit)"<<endl<<"> ";
        int n;cin>>n;
        if (cin.fail()){
            if(cin.eof()){
                return -1;
            }else{cin.clear();cin.ignore(10000,'\n');continue;} 
        }else{
            //run main code to test if n is valid
            if (validMapNum(n)) return n;
            else{
                cout<<"Map doesn't exist. Please choose a different one."<<endl;
                continue;
                }
        }
        
    }
}

void GameRun(int map_num){
    cout<<"GAME RUN MAP NUM "<<map_num<<endl;
}
void showRules(){
    cout<<endl<<setfill('=')<<setw(115)<<""<<endl;
    cout<<setfill(' ')<<setw(63)<<"INSTRUCTIONS"<<endl;
    cout<<setfill('=')<<setw(115)<<""<<endl;
    cout<<"The player is placed in a maze made up of high-voltage fences and posts."<<endl;
    cout<<"There are also some interceptor robots that will try to destroy the player."<<endl;
    cout<<"If the player touches the maze or any of these robots, that is the end of the game (and the player!)."<<endl;
    cout<<"The robots are also destroyed when they touch the fences/posts or when they collide with each other."<<endl;
    cout<<"Every time the player moves in any direction (horizontally, vertically, or diagonally) to a contiguous cell, "<<endl;
    cout<<"each robot moves one cell closer to the new player's location, in whichever direction is the shortest path."<<endl;
    cout<<"The robots have no vision sensors but they have an accurate odour sensor that allows them to follow the player!"<<endl;
    cout<<"There is one hope: make the robots hit the maze or each other. If all of them are destroyed, the player wins."<<endl;
    cout<<setfill('=')<<setw(115)<<""<<endl;
    cout<<endl;
}

void calculator()
{
    int opt;
    while (true)
    {
        //Start of MENU
        cout<<"================="<<endl;
        cout<<" Human vs Robot"<<endl;
        cout<<"================="<<endl;
        cout<<"  1)  Rules"<<endl;
        cout<<"  2)  Play"<<endl; 
        cout<<"  0)  Exit"<<endl;
        cout<<"================"<<endl;
        cout<<"> ";cin>>opt;  
        //End of MENU


        //tests invalid input / ctrlZ
        if(cin.fail()){
            if(cin.eof()){
                cout<<"Game Closed."<<endl;break;}
            else{
                cin.clear();cin.ignore(10000,'\n');
                cout<<"Invalid operation. Please try again.\n\n"; 
                continue;}
        }else{cin.ignore(10000,'\n'); }
        //END of input test

        
        //choose option from menu
        if(opt == 1){
            showRules();
            continue;
        }else if(opt == 2){
            int n = askMapNum();
            // if map zero is picked, return to main menu
            if (n==0){cout<<endl;continue;}
            else if(n==-1){
                cout<<"Game Closed."<<endl;
                break;
            }
            GameRun(n); // run game
            break;
        }else if(opt == 0){
            cout<<"Game Closed."<<endl;
            break;
        }else{
            cout<<"Invalid operation. Please try again.\n\n"; 
        }
    }             
}

int main(){
    calculator();
    char a;cout<<"Press key to exit...";cin>>a;
}