#include <iostream>
using namespace std;

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
