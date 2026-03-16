#include <iostream>
#include <vector>
#include <string>

using namespace std;

class WeatherData {
public:
    int minTemp;
    int maxTemp;

    WeatherData(int minT,int maxT){
        minTemp=minT;
        maxTemp=maxT;
    }

    int avgTemp(){
        return (minTemp+maxTemp)/2;
    }

    int range(){
        return maxTemp-minTemp;
    }
};

class TemperatureModel{
public:

    static WeatherData predictNextDay(vector<WeatherData> data){

        int n=data.size();

        int sumMin=0;
        int sumMax=0;

        for(auto d:data){
            sumMin+=d.minTemp;
            sumMax+=d.maxTemp;
        }

        int nextMin=sumMin/n;
        int nextMax=sumMax/n;

        return WeatherData(nextMin,nextMax);
    }
};

class WeatherAnalyzer{
public:

    static string predictCondition(WeatherData data){

        int avg=data.avgTemp();
        int range=data.range();

        if(range<=5)
        return "Rainy";

        if(avg>=30)
        return "Hot & Sunny";

        if(avg<18)
        return "Cold";

        return "Pleasant";
    }
};

class SimpleHash{
public:

    static size_t generateHash(string data){
        return hash<string>{}(data);
    }
};

class MerkleTree{

vector<size_t> hashes;

public:

MerkleTree(vector<string> records){

for(auto r:records)
hashes.push_back(SimpleHash::generateHash(r));
}

size_t getMerkleRoot(){

vector<size_t> level=hashes;

while(level.size()>1){

vector<size_t> next;

for(int i=0;i<level.size();i+=2){

if(i+1<level.size()){

string combined=
to_string(level[i])+
to_string(level[i+1]);

next.push_back(SimpleHash::generateHash(combined));
}
else
next.push_back(level[i]);
}

level=next;
}

return level[0];
}
};





int main() {
    vector<WeatherData> pastData = {
        {22, 30},
        {23, 31},
        {24, 32},
        {25, 33},
        {24,38}
    };
    WeatherData prediction = TemperatureModel::predictNextDay(pastData);
    string Analysis = WeatherAnalyzer::predictCondition(prediction);

    vector<string> records;
    records.push_back(
        to_string(prediction.minTemp) + "-" +
        to_string(prediction.maxTemp) + "-" + Analysis
    );

    MerkleTree tree(records);
    size_t root = tree.getMerkleRoot();

    cout << "Weather Prediction System\n";
    cout << "Predicted Min Temp: " << prediction.minTemp << endl;
    cout << "Predicted Max Temp: " << prediction.maxTemp << endl;
    cout << "Weather Condition: " << Analysis << endl;
    cout << "Merkle Root: " << root << endl;

    return 0;
}

