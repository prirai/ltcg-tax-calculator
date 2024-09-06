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
public:
    /**
     * Calculates the Long Term Capital Gains (LTCG) Tax applicable
     * given the net profit.
     *
     * @param profit The net profit.
     * @return The LTCG Tax applicable.
     */
    static double getLTCGTax(double profit, double taxrate) {
        // Calculate the LTCG Tax applicable
        return profit * taxrate / 100;
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
    double sellingPriceNew;
    double netProfit;
    double netProfitNew;

public:
    LTCG(double initial_cost, int initial_year, int size): growthPrice(size), inflationobj(size) {
        initialCost = initial_cost;
        initialYear = initial_year;
        sellingPrice = initial_cost;
        sellingPriceNew = initial_cost;
        netProfit = 0;
        netProfitNew = 0;
    }

    void calculate(int sell_year) {
        double ltcg_tax_old = 0;
        double ltcg_tax_new = 0;
        for (int i = initialYear; i < sell_year; i++) {
            double gp = growthPrice.getGrowthPrice(i);
            double inf = inflationobj.getInflationRate(i);
            // Calculate the selling price using both the new and old schemes
            sellingPrice *= (1 + (gp - inf) / 100);
            sellingPriceNew *= (1 + gp / 100);
        }
        netProfit = sellingPrice - initialCost;
        netProfitNew = sellingPriceNew - initialCost;
        // Precision as 2 decimal places.
        cout << setprecision(2);
        cout  << endl;
        cout << "OLD SCHEME" << endl;
        cout << fixed << "Selling Price as per the old scheme (with inflation): " << sellingPrice << endl;
        cout << fixed << "Profit as per the old scheme: " << netProfit << endl;
        if (netProfit > 0) {
            ltcg_tax_old = tax.getLTCGTax(netProfit, 20.0);
            cout << fixed << "LTCG Tax applicable as per the old scheme: " << ltcg_tax_old << endl;
        } else
            cout << "No net profit (" << fixed << netProfit <<
                    "), therefore no LTCG tax applicable if following the old scheme with inflation." << endl;
        cout << endl;
        cout << "NEW SCHEME" << endl;
        cout << fixed << "Selling Price as per the new scheme (without inflation adjustment): " <<
                sellingPriceNew << endl;
        cout << fixed << "Profit as per the new change to LTCG scheme: " << netProfitNew << endl;
        ltcg_tax_new = tax.getLTCGTax(netProfitNew, 12.5);
        cout << fixed << "LTCG Tax applicable as per the new scheme: " << ltcg_tax_new << endl;
        cout << endl;
        double tax_difference = ltcg_tax_new - ltcg_tax_old;
        if (tax_difference > 0)
            cout << "Greater tax applicable as per the new scheme: " << tax_difference << endl;
        else
            cout << "Greater tax applicable as per the old scheme: " << -(tax_difference) << endl;
    }

    /**
     * Calculates the selling price and Long Term Capital Gains (LTCG) tax applicable
     * given the selling year.
     *
     * @param sell_year The year of selling.
     */
    void calculate2(int sell_year) {
        double ltcg_tax = 0;
        double ltcg_tax_without_inflation = 0;
        for (int i = initialYear; i < sell_year; i++) {
            double gp = growthPrice.getGrowthPrice(i);
            double inf = inflationobj.getInflationRate(i);
            // Calculate the selling price using both the new and old schemes
            sellingPrice *= (1 + (gp - inf) / 100);
            sellingPriceNew *= (1 + gp / 100);
        }
        netProfit = sellingPrice - initialCost;
        netProfitNew = sellingPriceNew - initialCost;
        // Precision as 2 decimal places.
        cout << setprecision(2);
        cout  << endl;
        cout << fixed << "Selling Price as per the new scheme (without inflation adjustment): " <<
                sellingPriceNew << endl;
        cout << fixed << "Selling Price as per the old scheme (with inflation): " << sellingPrice << endl;
        cout << fixed << "Profit as per the new change to LTCG scheme: " << netProfitNew << endl;
        if (netProfit > 0) {
            cout << "Net profit obtained with old scheme (with inflation into account): " << netProfit << endl;
            ltcg_tax = tax.getLTCGTax(netProfit, 20.0);
            cout << fixed << "LTCG Tax applicable as per the old scheme: " << ltcg_tax << endl;
        } else
            cout << "No net profit (" << fixed << netProfit <<
                    "), therefore no LTCG tax applicable if following the old scheme with inflation." << endl;
        ltcg_tax_without_inflation = tax.getLTCGTax(netProfitNew, 12.5);
        cout << fixed << "LTCG Tax applicable as per the new scheme: " << ltcg_tax_without_inflation << endl;
        double tax_difference = ltcg_tax_without_inflation - ltcg_tax;
        if (tax_difference > 0)
            cout << "Greater tax applicable as per the new scheme: " << tax_difference << endl;
        else
            cout << "Greater tax applicable as per the old scheme: " << -(tax_difference) << endl;
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

void checkYearRange(int year, int lowerlim, int upperlim) {
    if(year < lowerlim || year > upperlim) {
        throw out_of_range("Year must be between " + to_string(lowerlim) + " and " + to_string(upperlim) + ".");
    }
}

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
    checkYearRange(buyyear, 2001, 2029);
    int sellyear;
    cout << "Enter the year of selling (between " << buyyear << " and 2029): ";
    cin >> sellyear;
    // Check the year of selling is in the valid range
    checkYearRange(sellyear, buyyear, 2030);
    LTCG ltcg(costprice, buyyear, 29);
    // Read the price-inflation.csv file and store the data in the member variables
    ltcg.parseInput();
    // Calculate the selling price and LTCG tax applicable
    ltcg.calculate(sellyear);
}
