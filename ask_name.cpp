#include <iostream>

using namespace std;

string askWinnerName(){
    //asks for a 15 char name and returns it
    //if ctrlZ happens "__BROKEN__LOOP__" is returned
    while(1){
        string s= "";
        string s2= "";
        char c = ' ';
        cout<<endl<<"Please insert your name: \n"<<" > ";getline(cin,s2);
        if(cin.fail() && cin.eof()) return "__BROKEN__LOOP__"; // detects ctrlz
        
        //test if empty name is choosed
        if(s2.size()==0){cout<<"Empty name not allowed!"<<endl;continue;}
        
        //reduce to 15 char if needed
        if (s2.size()<=15){s=s2;}else for(int i=0;i<15;i++) s+=s2[i];

        //test if name is only spaces
        bool onlySpaces = true;
        for(char i:s) if(i!= ' ' ) onlySpaces = false;
        if(onlySpaces){cout<<"Empty name not allowed!"<<endl;continue;}
        
        //confirms name
        cout<<"Is '"<<s<< "' the name you want? (Y/N)"<<endl<<" > ";
        if ((cin >> c)){
            //raises error if more than 1 char is written by user
            if(!((char)cin.peek()=='\n' || (char)cin.peek() == ' ')){
                cout<<"Invalid Input!"<<endl;
                cin.clear();cin.ignore(1000,'\n');
                continue;
            }
            //tests user's char
            cin.clear();cin.ignore(1000,'\n');
            if(c =='y' || c=='Y') return s;
            else if(c =='N' || c=='n') continue;
            else{
                cout<<"Invalid Input!"<<endl;
                continue;
            }
        }else{
            //deals with errors when trying to get the char
            if(cin.fail() && cin.eof()) return "__BROKEN__LOOP__"; // detects ctrlz
            cin.clear();cin.ignore(1000,'\n');
            cout<<"Invalid Input! Choose Y/N"<<endl;
            continue;
        } 
    }
}

int main(){
    cout<<"DONE = "<<askWinnerName()<<endl;
    char a;cout<<"Press any key to exit...";cin>>a;
}