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
    /**
     * Calculates the Long Term Capital Gains (LTCG) Tax applicable
     * given the net profit.
     *
     * @param profit The net profit.
     * @return The LTCG Tax applicable.
     */
    double getLTCGTax(double profit) {
        // Calculate the LTCG Tax applicable
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
    double netProfit;

public:
    LTCG(double initial_cost, int initial_year, int size): growthPrice(size), inflationobj(size) {
        initialCost = initial_cost;
        initialYear = initial_year;
        sellingPrice = initial_cost;
        netProfit = 0;
    }

    /**
     * Calculates the selling price and LTCG tax applicable given the selling year.
     *
     * @param sell_year The year of selling.
     */
    void calculate(int sell_year) {
        double ltcg_tax = 0;
        for (int i = initialYear; i < sell_year; i++) {
            double gp = growthPrice.getGrowthPrice(i);
            double inf = inflationobj.getInflationRate(i);
            // Calculate the selling price
            sellingPrice *= (1 + (gp - inf) / 100);
        }
        netProfit = sellingPrice - initialCost;
        // Precision as 2 decimal places.
        cout << setprecision(2);
        if (netProfit > 0) {
            cout << "Net profit: " << netProfit << endl;
            ltcg_tax = netProfit * 20 / 100;
        } else
            cout << "No net profit (" << fixed << netProfit << "), therefore no LTCG tax applicable." << endl;
        cout << fixed << "Selling Price: " << sellingPrice << endl;
        cout << fixed << "LTCG Tax applicable: " << ltcg_tax << endl;
    }

    /**
     * Reads the price-inflation.csv file and stores the data in the member variables.
     */
    void parseInput() {
        string text;
        ifstream input_file("price-inflation.csv");
        if (!input_file.is_open()) throw runtime_error("Error opening file");
        // Ignore the header line
        getline(input_file, text);
        // Process the data
        while (getline(input_file, text)) {
            double growthprice = stof(text.substr(text.find_first_of(',') + 1, text.find_last_of(',')));
            double inflationrate = stof(text.substr(text.find_last_of(',') + 1));
            // Store the growth price and inflation rate
            growthPrice.storeGrowthPrice(growthprice);
            inflationobj.storeInflationRate(inflationrate);
        }
        input_file.close();
    }
};

/**
 * Calculates the selling price and Long Term Capital Gains (LTCG) Tax applicable
 * given the selling year.
 */
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
    // Check the year of selling is in the valid range
    if (sellyear < buyyear || sellyear >= 2030) {
        throw out_of_range("Year must be between " + to_string(buyyear) + " and 2029.");
    }
    LTCG ltcg(costprice, buyyear, 29);
    // Read the price-inflation.csv file and store the data in the member variables
    ltcg.parseInput();
    // Calculate the selling price and LTCG tax applicable
    ltcg.calculate(sellyear);
}
