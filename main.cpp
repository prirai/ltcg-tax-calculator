#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class GrowthPrice {
private:
    vector<double> growthPrice;
public:
    void storeGrowthPrice(double growth_price) {
        growthPrice.push_back(growth_price);
    }
    double getGrowthPrice(int year) const {
        return growthPrice[year - 2001];
    }
};
class Inflation {
private:
    vector<double> inflationRate;
public:
    void storeInflationRate(double inflation_value) {
        inflationRate.push_back(inflation_value);
    }
    double getInflationRate(int year) const {
        return inflationRate[year - 2001];
    }
};

int main() {
    double costprice = 5000000;
    int buyyear = 2011;
    int sellyear;
    cout << "Enter the year of selling (between " << buyyear << " and 2029): ";
    cin >> sellyear;
    if (sellyear <= buyyear || sellyear >= 2030) {
        throw out_of_range("Year must be between " + to_string(buyyear) + " and 2029.");
    }
    cout << "Selling Price: " << endl;
    cout << "LTCG Tax applicable: " << endl;
}
