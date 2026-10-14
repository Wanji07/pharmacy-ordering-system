#include <iostream>
#include <cstdlib> 

// CSV libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Product { 
    int id;
    string name;
    string category;
    string subcategory;
    double price;
    int stock;
};

vector<Product> loadProducts(string filename) {
    
    vector<Product> products;

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open the CSV file." << endl;
        return products;
    }

    string line;

    getline(file, line);

    while (getline(file, line)) {
        stringstream row(line);

        Product product;
        string value;

        getline(row, value, ',');
        product.id = stoi(value);

        getline(row, product.name, ',');

        getline(row, product.category, ',');
        
        getline(row, product.subcategory, ',');

        getline(row, value, ',');
        product.price = stod(value);

        getline(row, value, ',');
        product.stock = stoi(value);

        products.push_back(product);

    }

    file.close();

    return products;
}

void saveProducts(string filename, const vector<Product>& products) {

    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open the CSV file for writing." << endl;
        return;
    }

    file << "ID,Name,Category,Subcategory,Price,Stock\n";

    for (const Product& product : products) {
        file << product.id << "," << product.name << "," << product.category << "," << product.subcategory << "," << product.price << "," << product.stock << endl;
    }

    file.close();

}

int main() {

    int menuRes, categoryRes, subCategoryRes, productRes;
    int adminMenuRes, stockRes;
    double priceRes;

    cout << "────────────── PHARMACY SYSTEM OVERVIEW ──────────────" << endl;
    cout << endl;

    cout << "────────────── MAIN MENU ──────────────" << endl;
    cout << "1.) Order Products" << endl;
    cout << "2.) Enter as Administrator" << endl;
    cout << "3.) Exit" << endl;
    cin >> menuRes;

    switch (menuRes) {

        case 1:
            cout << "────────────── CATEGORIES ──────────────" << endl;
            cout << "1.) Medicines & Health Products" << endl;
            cout << "2.) Over-the-Counter & Personal Care Products" << endl;
            cout << "3.) Pharmacy Equipment & Supplies" << endl;
            cin >> categoryRes;
            switch (categoryRes) {
                case 1:
                    cout << "────────────── MEDICINES & HEALTH PRODUCTS ──────────────" << endl;
                    cout << "1.) Pain & Fever Medicine" << endl;
                    cout << "2.) Cough & Cold Medicine" << endl;
                    cout << "3.) Vitamins & Supplements" << endl;
                    cin >> subCategoryRes;
                    switch (subCategoryRes) {
                        case 1:
                            cout << "────────────── PAIN & FEVER MEDICINE ──────────────" << endl;
                            cout << "1.) Paracetamol 500mg — ₱5.00" << endl;
                            cout << "2.) Ibuprofen 200mg — ₱8.00" << endl;
                            cout << "3.) Mefenamic Acid 500mg — ₱10.00" << endl;
                            cin >> productRes;
                            break;
                        case 2:
                            cout << "────────────── COUGH & COLD MEDICINE ──────────────" << endl;
                            cout << "1.) Bioflu Tablet — ₱10.00" << endl;
                            cout << "2.) Tuseran Forte — ₱12.00" << endl;
                            cout << "3.) Carbocisteine 500mg — ₱15.00" << endl;
                            cin >> productRes;
                            break;
                        case 3:
                            cout << "────────────── VITAMINS & SUPPLEMENTS ──────────────" << endl;
                            cout << "1.) Vitamin C 500mg — ₱6.00" << endl;
                            cout << "2.) Vitamin B-Complex — ₱8.00" << endl;
                            cout << "3.) Vitamin D3 — ₱10.00" << endl;
                            cin >> productRes;
                            break;
                        default:
                            cout << "Invalid input!" << endl;
                            }
                            break;
                case 2:
                    cout << "────────────── OVER-THE-COUNTER & PERSONAL CARE ──────────────" << endl;
                    cout << "1.) Personal Care" << endl;
                    cout << "2.) Hygiene Products" << endl;
                    cout << "3.) Health & Wellness Accessories" << endl;
                    cin >> subCategoryRes;
                    switch (subCategoryRes) {
                        case 1:
                            cout << "────────────── PERSONAL CARE ──────────────" << endl;
                            cout << "1.) Shampoo — ₱120.00" << endl;
                            cout << "2.) Body Wash — ₱150.00" << endl;
                            cout << "3.) Toothpaste — ₱90.00" << endl;
                            cin >> productRes;
                            break;
                        case 2:
                            cout << "────────────── HYGIENE PRODUCTS ──────────────" << endl;
                            cout << "1.) Hand Sanitizer — ₱80.00" << endl;
                            cout << "2.) Wet Wipes — ₱70.00" << endl;
                            cout << "3.) Facial Tissue — ₱60.00" << endl;
                            cin >> productRes;
                            break;
                        case 3:
                            cout << "────────────── HEALTH & WELLNESS ACCESSORIES ──────────────" << endl;
                            cout << "1.) Digital Thermometer — ₱150.00" << endl;
                            cout << "2.) Face Mask Pack — ₱80.00" << endl;
                            cout << "3.) Hot/Cold Compress — ₱120.00" << endl;
                            cin >> productRes;
                            break;
                        default:
                            cout << "Invalid input!" << endl;
                    }
                    break;
                case 3:
                    cout << "────────────── PHARMACY EQUIPMENT & SUPPLIES ──────────────" << endl;
                    cout << "1.) Medical Monitoring Devices" << endl;
                    cout << "2.) Medical Support Products" << endl;
                    cout << "3.) Healthcare Supplies" << endl;
                    cin >> subCategoryRes;
                    switch (subCategoryRes) {
                        case 1:
                            cout << "────────────── MEDICAL MONITORING DEVICES ──────────────" << endl;
                            cout << "1.) Digital Blood Pressure Monitor — ₱1,500.00" << endl;
                            cout << "2.) Digital Pulse Oximeter — ₱800.00" << endl;
                            cout << "3.) Digital Weighing Scale — ₱1,200.00" << endl;
                            cin >> productRes;
                            break;
                        case 2:
                            cout << "────────────── MEDICAL SUPPORT PRODUCTS ──────────────" << endl;
                            cout << "1.) Elastic Knee Support — ₱350.00" << endl;
                            cout << "2.) Wrist Support — ₱300.00" << endl;
                            cout << "3.) Ankle Support — ₱350.00" << endl;
                            cin >> productRes;
                            break;
                        case 3:
                            cout << "────────────── HEALTHCARE SUPPLIES ──────────────" << endl;
                            cout << "1.) Disposable Syringes — ₱20.00" << endl;
                            cout << "2.) Disposable Gloves — ₱100.00" << endl;
                            cout << "3.) Cotton Applicator Sticks — ₱50.00" << endl;
                            cin >> productRes;
                            break;
                        default:
                            cout << "Invalid input!" << endl;
                    }
                    break;
                default:
                    cout << "Invalid input!" << endl;
            }
            break;
        case 2:
            cout << "────────────── ADMINISTRATOR MENU ──────────────" << endl;
            
            cout << "Good day, admin! Choose a product to modify its stock and prices." << endl;
            cout << "────────────── CATEGORIES ──────────────" << endl;
            cout << "1.) Medicines & Health Products" << endl;
            cout << "2.) Over-the-Counter & Personal Care Products" << endl;
            cout << "3.) Pharmacy Equipment & Supplies" << endl;
            cin >> categoryRes;

            switch (categoryRes) {
                case 1:
                    cout << "────────────── MEDICINES & HEALTH PRODUCTS ──────────────" << endl;
                    cout << "1.) Pain & Fever Medicine" << endl;
                    cout << "2.) Cough & Cold Medicine" << endl;
                    cout << "3.) Vitamins & Supplements" << endl;
                    cin >> subCategoryRes;
                    switch (subCategoryRes) {
                        case 1:
                            cout << "────────────── PAIN & FEVER MEDICINE ──────────────" << endl;
                            cout << "1.) Paracetamol 500mg — ₱5.00" << endl;
                            cout << "2.) Ibuprofen 200mg — ₱8.00" << endl;
                            cout << "3.) Mefenamic Acid 500mg — ₱10.00" << endl;
                            cin >> productRes;
                            break;
                        case 2:
                            cout << "────────────── COUGH & COLD MEDICINE ──────────────" << endl;
                            cout << "1.) Bioflu Tablet — ₱10.00" << endl;
                            cout << "2.) Tuseran Forte — ₱12.00" << endl;
                            cout << "3.) Carbocisteine 500mg — ₱15.00" << endl;
                            cin >> productRes;
                            break;
                        case 3:
                            cout << "────────────── VITAMINS & SUPPLEMENTS ──────────────" << endl;
                            cout << "1.) Vitamin C 500mg — ₱6.00" << endl;
                            cout << "2.) Vitamin B-Complex — ₱8.00" << endl;
                            cout << "3.) Vitamin D3 — ₱10.00" << endl;
                            cin >> productRes;
                            break;
                        default:
                            cout << "Invalid input!" << endl;
                    }
                    break;
                case 2:
                    cout << "────────────── OVER-THE-COUNTER & PERSONAL CARE ──────────────" << endl;
                    cout << "1.) Personal Care" << endl;
                    cout << "2.) Hygiene Products" << endl;
                    cout << "3.) Health & Wellness Accessories" << endl;
                    cin >> subCategoryRes;
                    switch (subCategoryRes) {
                        case 1:
                            cout << "────────────── PERSONAL CARE ──────────────" << endl;
                            cout << "1.) Shampoo — ₱120.00" << endl;
                            cout << "2.) Body Wash — ₱150.00" << endl;
                            cout << "3.) Toothpaste — ₱90.00" << endl;
                            cin >> productRes;
                            break;
                        case 2:
                            cout << "────────────── HYGIENE PRODUCTS ──────────────" << endl;
                            cout << "1.) Hand Sanitizer — ₱80.00" << endl;
                            cout << "2.) Wet Wipes — ₱70.00" << endl;
                            cout << "3.) Facial Tissue — ₱60.00" << endl;
                            cin >> productRes;
                            break;
                        case 3:
                            cout << "────────────── HEALTH & WELLNESS ACCESSORIES ──────────────" << endl;
                            cout << "1.) Digital Thermometer — ₱150.00" << endl;
                            cout << "2.) Face Mask Pack — ₱80.00" << endl;
                            cout << "3.) Hot/Cold Compress — ₱120.00" << endl;
                            cin >> productRes;
                            break;
                        default:
                            cout << "Invalid input!" << endl;
                    }
                    break;
                case 3:
                    cout << "────────────── PHARMACY EQUIPMENT & SUPPLIES ──────────────" << endl;
                    cout << "1.) Medical Monitoring Devices" << endl;
                    cout << "2.) Medical Support Products" << endl;
                    cout << "3.) Healthcare Supplies" << endl;
                    cin >> subCategoryRes;
                    switch (subCategoryRes) {
                        case 1:
                            cout << "────────────── MEDICAL MONITORING DEVICES ──────────────" << endl;
                            cout << "1.) Digital Blood Pressure Monitor — ₱1,500.00" << endl;
                            cout << "2.) Digital Pulse Oximeter — ₱800.00" << endl;
                            cout << "3.) Digital Weighing Scale — ₱1,200.00" << endl;
                            cin >> productRes;
                            break;
                        case 2:
                            cout << "────────────── MEDICAL SUPPORT PRODUCTS ──────────────" << endl;
                            cout << "1.) Elastic Knee Support — ₱350.00" << endl;
                            cout << "2.) Wrist Support — ₱300.00" << endl;
                            cout << "3.) Ankle Support — ₱350.00" << endl;
                            cin >> productRes;
                            break;
                        case 3:
                            cout << "────────────── HEALTHCARE SUPPLIES ──────────────" << endl;
                            cout << "1.) Disposable Syringes — ₱20.00" << endl;
                            cout << "2.) Disposable Gloves — ₱100.00" << endl;
                            cout << "3.) Cotton Applicator Sticks — ₱50.00" << endl;
                            cin >> productRes;
                            break;
                        default:
                            cout << "Invalid input!" << endl;
                    }
                    break;
                default:
                    cout << "Invalid input!" << endl;
            }
            break;
        case 3:
            cout << "Thank You!" << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cout << "Invalid input!" << endl;
    }

    vector<Product> products = loadProducts("products.csv");

    // ADMIN MENU

    if (menuRes == 2 && categoryRes >= 1 && categoryRes <= 3 && subCategoryRes >= 1 && subCategoryRes <= 3 && productRes >= 1 && productRes <= 3) {

        int selectedIndex = (categoryRes - 1) * 9 + (subCategoryRes - 1) * 3 + (productRes - 1);
        Product& selectedProduct = products[selectedIndex];

        cout << "────────────── ADMININISTRATOR OPERATIONS ──────────────" << endl;
        cout << "1.) Change Product Price" << endl;
        cout << "2.) Change Product Stock Quantity" << endl;
        cin >> adminMenuRes;

        switch (adminMenuRes) {
            case 1:
                cout << "Enter the new Product price for: " << selectedProduct.name << endl;
                cin >> priceRes;
                selectedProduct.price = priceRes;
                cout << "The new Product price for: " << selectedProduct.name << "is " << priceRes << "!" << endl;
                saveProducts("products.csv", products);
            break;
            case 2:
                cout << "Enter the new Product stock for: " << selectedProduct.name << endl;
                cin >> stockRes;
                selectedProduct.stock = stockRes;
                cout << "The new Product stock for: " << selectedProduct.name << "is " << stockRes << "!" << endl;
                saveProducts("products.csv", products);
            break;
            default:
                cout << "Invalid input!" << endl;
        }
    }

    // CALCULATIONS

    if (menuRes == 1 && categoryRes >= 1 && categoryRes <= 3 && subCategoryRes >= 1 && subCategoryRes <= 3 && productRes >= 1 && productRes <= 3) {
    
        int quantity;
        double price, total, payment, change;

        int selectedIndex = (categoryRes - 1) * 9 + (subCategoryRes - 1) * 3 + (productRes - 1);
        // ^^ Based on the answer of this formula, it will be the ID of the CSV itself.
        // ex. category = 1, subcategory = 2, product = 3
        // answer will be: 0 + 3 + 2 = (ID = 4 / due to zero-based indexing)

        // 1 category -> 3 subcategories -> 3 products
        // 1 subcategory -> 3 products

        Product& selectedProduct = products[selectedIndex];

        price = selectedProduct.price;
        
        cout << "────────────── PAYMENT ──────────────" << endl;
        cout << "Enter quantity: ";
        cin >> quantity;

        while (quantity < 1 || quantity > selectedProduct.stock) {
            cout << "Invalid quantity or insufficient stock! Enter again: ";
            cin >> quantity;
        }

        total = price * quantity;

        cout.setf(ios::fixed);
        cout.precision(2);

        cout << "Total Amount: ₱" << total << endl;
        cout << "Enter payment: ₱";

        cin >> payment;

        while (payment < total) {
            cout << "Insufficient payment! Enter again: ₱";
            cin >> payment;
        }
        
        change = payment - total;

        selectedProduct.stock -= quantity;
        saveProducts("products.csv", products);

        cout << "────────────── RECEIPT ──────────────" << endl;
        cout << "Product:  " << selectedProduct.name << endl;
        cout << "Price:    ₱" << selectedProduct.price << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Total:    ₱" << total << endl;
        cout << "Payment:  ₱" << payment << endl;
        cout << "Change:   ₱" << change << endl;
        cout << "────────────── THANK YOU! ──────────────" << endl;
    }

    return 0;
}
