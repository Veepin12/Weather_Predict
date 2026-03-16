#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <mysqlx/xdevapi.h>
using namespace std;

class WeatherData {
public:
    int minTemp;
    int maxTemp;

    WeatherData(int minT, int maxT) {
        minTemp = minT;
        maxTemp = maxT;
    }

    int avgTemp() const {
        return (minTemp + maxTemp) / 2;
    }

    int range() const {
        return maxTemp - minTemp;
    }

    string toString() const {
        return to_string(minTemp) + "-" + to_string(maxTemp);
    }
};

class TemperatureModel {
public:
    static WeatherData predictNextDay(const vector<WeatherData>& data) {
        int n = data.size();

        double avgMinChange =
            (data[n-1].minTemp - data[0].minTemp) / (double)(n - 1);

        double avgMaxChange =
            (data[n-1].maxTemp - data[0].maxTemp) / (double)(n - 1);

        int nextMin = data[n-1].minTemp + avgMinChange;
        int nextMax = data[n-1].maxTemp + avgMaxChange;

        return WeatherData(nextMin, nextMax);
    }
};

class WeatherAnalyzer {
public:
    static string predictCondition(const WeatherData& data) {
        int avg = data.avgTemp();
        int range = data.range();

        if (range <= 5)
            return "Rainy";
        else if (avg >= 30)
            return "Hot & Sunny";
        else if (avg < 18)
            return "Cold";
        else
            return "Pleasant";
    }
};

class SimpleHash {
public:
    static size_t generateHash(const string& data) {
        return hash<string>{}(data);
    }
};

class MerkleTree {
private:
    vector<size_t> hashes;

public:
    MerkleTree(const vector<string>& records) {
        for (const auto& r : records)
            hashes.push_back(SimpleHash::generateHash(r));
    }

    size_t getMerkleRoot() {
        vector<size_t> level = hashes;

        while (level.size() > 1) {
            vector<size_t> next;

            for (int i = 0; i < level.size(); i += 2) {
                if (i + 1 < level.size()) {
                    string combined =
                        to_string(level[i]) + to_string(level[i+1]);
                    next.push_back(SimpleHash::generateHash(combined));
                } else {
                    next.push_back(level[i]);
                }
            }
            level = next;
        }
        return level[0];
    }
};

vector<WeatherData> fetchWeatherDataFromDB()
{
    vector<WeatherData> data;

    MySQL_Driver *driver;
   Connection *con;
    Statement *stmt;
    ResultSet *res;

    driver = get_mysql_driver_instance();

    con = driver->connect("tcp://127.0.0.1:3306", "root", "virat");
    con->setSchema("weatherdb");

    stmt = con->createStatement();

    res = stmt->executeQuery("SELECT minTemp, maxTemp FROM weather_data");

    while (res->next())
    {
        int minT = res->getInt("minTemp");
        int maxT = res->getInt("maxTemp");

        data.push_back(WeatherData(minT, maxT));
    }

    delete res;
    delete stmt;
    delete con;

    return data;
}
int main() {
   vector<WeatherData> pastData = fetchWeatherDataFromDB();

    WeatherData nextDayTemp =
        TemperatureModel::predictNextDay(pastData);

    string condition =
        WeatherAnalyzer::predictCondition(nextDayTemp);

    cout << "Next Day Forecast\n";
    cout << "Min Temp: " << nextDayTemp.minTemp << endl;
    cout << "Max Temp: " << nextDayTemp.maxTemp << endl;
    cout << "Weather: " << condition << endl;

    vector<string> forecastRecord = {
        nextDayTemp.toString() + "-" + condition
    };

    MerkleTree tree(forecastRecord);
    cout << "Merkle Root (Forecast Integrity): "
         << tree.getMerkleRoot() << endl;

    return 0;
}
