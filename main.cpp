#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <typeinfo>

using namespace std;

map<string, string> inititalizeData(){
    map<string, string> data;
    vector<string> allValue = {"A","B","C"};
    for(int i = 0;i<allValue.size();i++){
        for(int x = 1;x<4;x++){
            data[allValue[i]+to_string(x)] = " ";
        }
    }
    return data;
}

void printState(map<string, string> data){
    string horizontale = "  A   B   C ";
    cout<<"Joueur 1 : X     Joueur 2 : O"<<endl<<endl
    <<horizontale<<endl
    <<"1 "+data["A1"]+" | "+data["B1"]+" | "+data["C1"]+" "<<endl
    <<" ---|---|---"<<endl
    <<"2 "+data["A2"]+" | "+data["B2"]+" | "+data["C2"]+" "<<endl
    <<" ---|---|---"<<endl
    <<"3 "+data["A3"]+" | "+data["B3"]+" | "+data["C3"]+" "<<endl;
}

string getUserInput(int user,map<string, string> data){
    while(true){
        printState(data);
        vector<string> letterArray = {"A","B","C"};
        cout<<"Joueur "<<user<<" à votre tour!"<<endl;
        string PlayerChoice;
        cin>>PlayerChoice;
        if(PlayerChoice.size() == 2){
            string temp = string(1,PlayerChoice[0]);
            if(find(letterArray.begin(), letterArray.end(), temp) != letterArray.end()){
                if((PlayerChoice[1] - '0') > 0 && (PlayerChoice[1] - '0') < 4){
                    if(data[PlayerChoice] == " "){
                        return PlayerChoice;
                    }
                }
            }
        }
    }
}

map<string, string> InsertData(map<string, string> data,string playerChoice, int playerNumber){
    if(playerNumber == 1){
        data[playerChoice] = "X";
    }else{
        data[playerChoice] = "O";
    }
    return data;
}

string getPlayerSymbol(int playerLevel){
    if(playerLevel == 1){
        return "X";
    }else{
        return "O";
    }
}

int getPlayerNumber(string symbol){
    if(symbol == "X"){
        return 1;
    }else if(symbol == "O"){
        return 2;
    }else{
        return -1;
    }
}

map<string, string> GamePart(map<string, string> data,int userLevel){
    string player1Choice = getUserInput(userLevel, data);
    data = InsertData(data,player1Choice,userLevel);
    return data;
}

int getIndex(vector<string> v, string K){
    auto it = find(v.begin(), v.end(), K);

    if (it != v.end()){
        int index = it - v.begin();
        return index; 
    }
    else {
        return -1;
    }
}

bool isSymbolAligned(vector<string> list){
    map<string, int> counter = {{"A",0},{"B",0},{"C",0},{"1",0},{"2",0},{"3",0}};
    for(int i = 0;i<list.size();i++){
        for(int x = 0;x<2;x++){
            string temp (1,list[i][x]);
            counter[temp] = counter[temp]+1;
            if(counter[temp] == 3){
                return true;
            }
        }
    }
    if(getIndex(list,"B2") != -1){
        if(getIndex(list,"A1") != -1 && getIndex(list,"C3") != -1){
            return true;
        }
        if(getIndex(list,"A3") != -1 && getIndex(list,"C1") != -1){
            return true;
        }    
    }
    return false;
}

map<string, string> didAPlayerWon(map<string,string> data){
    vector<string> letterList = {"A","B","C"};
    vector<string> numberList = {"1","2","3"};
    vector<string> firstPlayerList = {};
    vector<string> secondPlayerList = {};
    for(int letterCount = 0;letterCount<letterList.size();letterCount++){
        for(int numberCount = 0;numberCount<numberList.size();numberCount++){
            string currentLocation = letterList[letterCount] + numberList[numberCount];
            if(data[currentLocation] != " "){
                int playerNumber = getPlayerNumber(data[currentLocation]);
                if(playerNumber != -1){
                    if(playerNumber == 1){
                        firstPlayerList.push_back(currentLocation);
                    }else{
                        secondPlayerList.push_back(currentLocation);
                    }
                }
            }
        }
    }
    map <string,string> result;
    if(isSymbolAligned(firstPlayerList)){
        result["number"] = "1";
        result["state"] = "true";
    }else if(isSymbolAligned(secondPlayerList)){
        result["number"] = "2";
        result["state"] = "true";
    }else{
        result["state"] = "false";
    }
    return result;
}

int main(){
    while(true){
        map<string, string> data;

        data = inititalizeData();

        while (true){
            for(int i = 1;i<3;i++){
                data = GamePart(data,i);
                if(didAPlayerWon(data)["state"] == "true"){
                    cout<<"Le joueur "+didAPlayerWon(data)["number"]+" a gagné"<<endl;
                    break;
                }
            }
            if(didAPlayerWon(data)["state"] == "true"){
                break;
            }
        }
    }

    return 0;
}