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
class LTCG_Tax {
private:
    double ltcgTax = 0;
public:
    double getLTCGTax(double profit) {
        ltcgTax = profit * 20 / 100;
        return ltcgTax;
    }
};
class LTCG {
private:
    GrowthPrice growthPrice;
    Inflation inflationobj;
    LTCG_Tax tax;
    double initialCost;
    int initialYear;
    double sellingPrice;
    double profitBase;
public:
    LTCG(int initial_cost, int initial_year) {
        initialCost = initial_cost;
        initialYear = initial_year;
    }
    pair<double, double> calculate(int sell_year) {
        sellingPrice = initialCost;
        for (int i = initialYear; i < sell_year; i++) {
            double gp = growthPrice.getGrowthPrice(i);
            double inf = inflationobj.getInflationRate(i);
            sellingPrice *= (1 + (gp - inf)/100);
        }
        profitBase = sellingPrice - initialCost;
        cout << "Profit: " << profitBase << endl;
        double ltcg_tax = tax.getLTCGTax(profitBase);
        return {sellingPrice, ltcg_tax};
    }
    void parseInput() {
        string text;
        ifstream input_file("price-inflation.csv");
        if (!input_file.is_open()) throw runtime_error("Error opening file");
        getline(input_file, text);
        while (getline(input_file, text)) {
            double growthprice = stof(text.substr(text.find_first_of(',') + 1, text.find_last_of(',')));
            double inflationrate = stof(text.substr(text.find_last_of(',') + 1));
            growthPrice.storeGrowthPrice(growthprice);
            inflationobj.storeInflationRate(inflationrate);
        }
        input_file.close();
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
    LTCG ltcg(costprice, buyyear);
    ltcg.parseInput();
    auto [fst, snd] = ltcg.calculate(sellyear);
    cout << fixed << "Selling Price: " << fst << endl;
    cout << fixed << "LTCG Tax applicable: " << snd << endl;
}
