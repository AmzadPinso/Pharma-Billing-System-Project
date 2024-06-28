#include <bits/stdc++.h>
using namespace std;


string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n");
    size_t last = str.find_last_not_of(" \t\n");
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}


string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

class Medicine {
private:
    string name;
    double price;

public:
    Medicine() : name(""), price(0.0) {}
    Medicine(const string& n, double p) : name(n), price(p) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

class MedicineStore {
private:
    vector<Medicine> medicines;

public:
    void loadMedicines(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        int numMedicines;
        file >> numMedicines;
        file.ignore();
        for (int i = 0; i < numMedicines; ++i) {
            string line;
            getline(file, line);
            stringstream ss(line);
            string name;
            double price;
            ss >> name >> price;
            name = trim(name);
            medicines.push_back(Medicine(name, price));
        }

        file.close();
    }

    double getPrice(const string& name) const {
        string lowerName = toLowerCase(name);
        for (const auto& med : medicines) {
            if (toLowerCase(med.getName()) == lowerName) {
                return med.getPrice();
            }
        }
        return 0.0;
    }
};

int main() {
    MedicineStore store;
    store.loadMedicines("//home//amzad//Desktop//Madi_list//medilist.txt");

    vector<string> medicineNames;
    vector<int> quantities;

    string medicineName;
    int quantity;


    cout << "Enter medicine names and quantities. Press Enter twice to finish." << endl;
    while (true) {
        cout << "Enter medicine name: ";
        getline(cin, medicineName);


        if (medicineName.empty()) {
            break;
        }

        cout << "Enter quantity: ";
        cin >> quantity;
        cin.ignore();


        medicineNames.push_back(trim(medicineName));
        quantities.push_back(quantity);
    }


    double totalBill = 0.0;
    cout << endl;
    for (size_t i = 0; i < medicineNames.size(); ++i) {
        double price = store.getPrice(medicineNames[i]);
        if (price > 0) {
            double totalPrice = price * quantities[i];
            totalBill += totalPrice;
            cout << "Medicine: " << medicineNames[i] << " (" << quantities[i] << "p) = " << totalPrice << " TAKA" << endl;
        } else {
            cout << "Medicine '" << medicineNames[i] << "' not found!" << endl;
        }
    }

    cout << endl << "Total Bill: " << totalBill << " TAKA Only\n" << endl;


    string printOption;
    cout << "Do you want to print the bill copy? (yes/no): ";
    cin >> printOption;
    if (printOption == "yes") {
        cout << endl << "Print Copy:" << endl;
        cout << "=============================" << endl;
        cout << "||        MSA Pharma        ||" << endl;-
        cout << "=============================" << endl;
        cout << "||_______ Bill Copy ________||" << endl;
        cout << "||__________________________||" << endl;
        cout << "||- Med Name - QU - Price -||" << endl;
        for (size_t i = 0; i < medicineNames.size(); ++i) {
            double price = store.getPrice(medicineNames[i]);
            if (price > 0) {
                cout << "||    " << setw(8) << left << medicineNames[i] << setw(4) << quantities[i] << setw(7) << price << "   ||" << endl;
            }
        }
        cout << "||__________________________||" << endl;
        cout << "|| Total: " << setw(14) << totalBill << " TAKA ||" << endl;
        cout << "||                          ||" << endl;
        cout << "||-------- THANK YOU -------||" << endl;
        cout << "=============================" << endl;
    }

    return 0;
}
