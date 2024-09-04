#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class GrowthPrice {
private:
    double growthPrice[100];
    int index;
    int size;

public:
    GrowthPrice(int size) {
        this->size = size;
        index = 0;
    }

    void storeGrowthPrice(double growth_price) {
        growthPrice[index++] = growth_price;
    }

    double getGrowthPrice(int year) const {
        return growthPrice[year - 2001];
    }
};

class Inflation {
private:
    double inflationRate[100];
    int index;
    int size;

public:
    Inflation(int size) {
        this->size = size;
        index = 0;
    }

    void storeInflationRate(double inflation_value) {
        inflationRate[index++] = inflation_value;
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
    LTCG(double initial_cost, int initial_year, int size): growthPrice(size), inflationobj(size) {
        initialCost = initial_cost;
        initialYear = initial_year;
        sellingPrice = initial_cost;
        profitBase = 0;
    }

    void calculate(int sell_year) {
        double ltcg_tax = 0;
        for (int i = initialYear; i < sell_year; i++) {
            double gp = growthPrice.getGrowthPrice(i);
            double inf = inflationobj.getInflationRate(i);
            sellingPrice *= (1 + (gp - inf) / 100);
        }
        profitBase = sellingPrice - initialCost;
        cout << setprecision(2);
        if (profitBase > 0) {
            cout << "Net profit: " << profitBase << endl;
            ltcg_tax = profitBase * 20 / 100;
        }
        else
            cout << "No net profit (", profitBase, ") , therefore no LTCG tax applicable." << endl;
        cout << fixed << "Selling Price: " << sellingPrice << endl;
        cout << fixed << "LTCG Tax applicable: " << ltcg_tax << endl;
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
    double costprice;
    int buyyear;
    cout << "Enter the cost price: ";
    cin >> costprice;
    cout << "Enter the year of purchase: ";
    cin >> buyyear;
    int sellyear;
    cout << "Enter the year of selling (between " << buyyear << " and 2029): ";
    cin >> sellyear;
    if (sellyear < buyyear || sellyear >= 2030) {
        throw out_of_range("Year must be between " + to_string(buyyear) + " and 2029.");
    }
    LTCG ltcg(costprice, buyyear, 29);
    ltcg.parseInput();
    ltcg.calculate(sellyear);
}
