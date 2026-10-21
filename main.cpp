#include <iostream>
#include <cstdlib> 
#include <algorithm>
#include <sstream>
#include <string>

// CSV libraries
#include <fstream>
#include <vector>

// VAT
#include <set>

using namespace std;

struct Product { 
    int id;
    string name;
    string category;
    string subcategory;
    double price;
    int stock;
};

// BORDER STYLING

void printLine(int width) {
    cout << "+";
    for (int i = 0; i < width; i++) {
        cout << "-";
    }
    cout << "+" << endl;
}

void printRow(const string& text, int width) {
    cout << "| " << text;

    for (int i = static_cast<int>(text.length()); i < width - 1; i++) {
        cout << " ";
    }

    cout << "|" << endl;
}

void printHeader(const string& title) {
    int width = max(30, static_cast<int>(title.length()) + 1);
    printLine(width);
    printRow(title, width);
    printLine(width);
}

// LOAD CSV

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

// SAVE CSV CHANGES FROM ADMIN MENU

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

// AUTHENTICATE ADMIN FUNCTION

bool authenticateAdmin() {
    ifstream passwordFile("admin_password.txt");

    if (!passwordFile.is_open()) {
        cout << "Unable to open the administrator password file." << endl;
        return false;
    }

    string storedPassword;
    getline(passwordFile, storedPassword);
    passwordFile.close();

    const int maxAttempts = 3;

    for (int attempt = 1; attempt <= maxAttempts; attempt++) {
        string enteredPassword;

        cout << "Enter administrator password: ";
        cin >> enteredPassword;

        if (enteredPassword == storedPassword) {
            cout << "Access granted." << endl;
            return true;
        }

        cout << "Incorrect password." << endl;
    }

    cout << "Access denied." << endl;
    return false;

}

// CATEGORY FUNCTION

int selectCategory() {
    
    printHeader("CATEGORIES");
    cout << "1.) Medicines & Health Products" << endl;
    cout << "2.) Over-the-Counter & Personal Care Products" << endl;
    cout << "3.) Pharmacy Equipment & Supplies" << endl;
    cout << "4.) Digestive Health" << endl;
    cout << "5.) Eye and Ear Care" << endl;
    
    int categoryRes;
    cin >> categoryRes;

    return categoryRes;
}

// SUBCATEGORY FUNCTION

int selectSubCategory(int categoryRes) {
    switch (categoryRes) {
        case 1:
            printHeader("MEDICINES & HEALTH PRODUCTS");
            cout << "1.) Pain & Fever Medicine" << endl;
            cout << "2.) Cough & Cold Medicine" << endl;
            cout << "3.) Vitamins & Supplements" << endl;
        break;
        case 2:
            printHeader("OVER-THE-COUNTER & PERSONAL CARE");
            cout << "1.) Personal Care" << endl;
            cout << "2.) Hygiene Products" << endl;
            cout << "3.) Health & Wellness Accessories" << endl;
        break;
        case 3:
            printHeader("PHARMACY EQUIPMENT & SUPPLIES");
            cout << "1.) Medical Monitoring Devices" << endl;
            cout << "2.) Medical Support Products" << endl;
            cout << "3.) Healthcare Supplies" << endl;
        break;
        case 4:
            printHeader("DIGESTIVE HEALTH");
            cout << "1.) Antacids" << endl;
            cout << "2.) Anti-Diarrheal" << endl;
            cout << "3.) Digestive Relief" << endl;
        break;
        case 5:
            printHeader("EYE AND EAR CARE");
            cout << "1.) Eye Drops" << endl;
            cout << "2.) Eye Hygiene" << endl;
            cout << "3.) Ear Care" << endl;
        break;
        default:
            cout << "Invalid input!" << endl;
    }

    int subCategoryRes;
    cin >> subCategoryRes;
    return subCategoryRes;
}

// PRODUCTS FUNCTION

int selectProduct(int categoryRes, int subCategoryRes) {

    if (categoryRes == 1) {
        switch (subCategoryRes) {
        case 1:
            printHeader("PAIN & FEVER MEDICINE");
            cout << "1.) Paracetamol 500mg - ₱5.00" << endl;
            cout << "2.) Ibuprofen 200mg - ₱8.00" << endl;
            cout << "3.) Mefenamic Acid 500mg - ₱10.00" << endl;
            break;
        case 2:
            printHeader("COUGH & COLD MEDICINE");
            cout << "1.) Bioflu Tablet - ₱10.00" << endl;
            cout << "2.) Tuseran Forte - ₱12.00" << endl;
            cout << "3.) Carbocisteine 500mg - ₱15.00" << endl;
            break;
        case 3:
            printHeader("VITAMINS & SUPPLEMENTS");
            cout << "1.) Vitamin C 500mg - ₱6.00" << endl;
            cout << "2.) Vitamin B-Complex - ₱8.00" << endl;
            cout << "3.) Vitamin D3 - ₱10.00" << endl;
            break;
        default:
            cout << "Invalid input!" << endl;
        }
    } else if (categoryRes == 2) {
        switch (subCategoryRes) {
            case 1:
                printHeader("PERSONAL CARE");
                cout << "1.) Shampoo - ₱120.00" << endl;
                cout << "2.) Body Wash - ₱150.00" << endl;
                cout << "3.) Toothpaste - ₱90.00" << endl;
                break;
            case 2:
                printHeader("HYGIENE PRODUCTS");
                cout << "1.) Hand Sanitizer - ₱80.00" << endl;
                cout << "2.) Wet Wipes - ₱70.00" << endl;
                cout << "3.) Facial Tissue - ₱60.00" << endl;
                break;
            case 3:
                printHeader("HEALTH & WELLNESS ACCESSORIES");
                cout << "1.) Digital Thermometer - ₱150.00" << endl;
                cout << "2.) Face Mask Pack - ₱80.00" << endl;
                cout << "3.) Hot/Cold Compress - ₱120.00" << endl;
                break;
            default:
                cout << "Invalid input!" << endl;
        }
    } else if (categoryRes == 3) {
        switch (subCategoryRes) {
            case 1:
                printHeader("MEDICAL MONITORING DEVICES");
                cout << "1.) Digital Blood Pressure Monitor - ₱1,500.00" << endl;
                cout << "2.) Digital Pulse Oximeter - ₱800.00" << endl;
                cout << "3.) Digital Weighing Scale - ₱1,200.00" << endl;
                break;
            case 2:
                printHeader("MEDICAL SUPPORT PRODUCTS");
                cout << "1.) Elastic Knee Support - ₱350.00" << endl;
                cout << "2.) Wrist Support - ₱300.00" << endl;
                cout << "3.) Ankle Support - ₱350.00" << endl;
                break;
            case 3:
                printHeader("HEALTHCARE SUPPLIES");
                cout << "1.) Disposable Syringes - ₱20.00" << endl;
                cout << "2.) Disposable Gloves - ₱100.00" << endl;
                cout << "3.) Cotton Applicator Sticks - ₱50.00" << endl;
                break;
            default:
                cout << "Invalid input!" << endl;
        }
    } else if (categoryRes == 4) {
        switch (subCategoryRes) {
            case 1:
                printHeader("ANTACIDS");
                cout << "1.) Calcium Carbonate Tablets - ₱8.00" << endl;
                cout << "2.) Aluminum Hydroxide Suspension - ₱65.00" << endl;
                cout << "3.) Magnesium Hydroxide Tablets - ₱12.00" << endl;
                break;
            case 2:
                printHeader("ANTI-DIARRHEAL");
                cout << "1.) Loperamide 2mg - ₱6.00" << endl;
                cout << "2.) Oral Rehydration Salts - ₱15.00" << endl;
                cout << "3.) Bismuth Subsalicylate - ₱75.00" << endl;
                break;
            case 3:
                printHeader("DIGESTIVE RELIEF");
                cout << "1.) Simethicone 80mg - ₱9.00" << endl;
                cout << "2.) Digestive Enzyme Capsules - ₱120.00" << endl;
                cout << "3.) Probiotic Capsules - ₱150.00" << endl;
                break;
            default:
                cout << "Invalid input!" << endl;
        }
    } else if (categoryRes == 5) {
        switch (subCategoryRes) {
            case 1:
                printHeader("EYE DROPS");
                cout << "1.) Artificial Tears - ₱150.00" << endl;
                cout << "2.) Lubricating Eye Drops - ₱180.00" << endl;
                cout << "3.) Allergy Eye Drops - ₱220.00" << endl;
                break;
            case 2:
                printHeader("EYE HYGIENE");
                cout << "1.) Sterile Eye Wash - ₱130.00" << endl;
                cout << "2.) Eye Compress - ₱100.00" << endl;
                cout << "3.) Eyelid Cleansing Wipes - ₱160.00" << endl;
                break;
            case 3:
                printHeader("EAR CARE");
                cout << "1.) Ear-Cleaning Drops - ₱110.00" << endl;
                cout << "2.) Ear Syringe - ₱95.00" << endl;
                cout << "3.) Earplugs - ₱80.00" << endl;
                break;
            default:
                cout << "Invalid input!" << endl;
        }
    } else {
        cout << "Invalid category!" << endl;
        return 0;
    }

    int productRes;
    cin >> productRes;
    return productRes;
} 

int main() {

    int menuRes, categoryRes, subCategoryRes, productRes;
    int adminMenuRes, stockRes;
    double priceRes;

    printHeader("PHARMACY SYSTEM OVERVIEW");
    cout << endl;

    printHeader("MAIN MENU");
    cout << "1.) Order Products" << endl;
    cout << "2.) Enter as Administrator" << endl;
    cout << "3.) Exit" << endl;
    cin >> menuRes;

    switch (menuRes) {
        case 1:
            categoryRes = selectCategory();
            subCategoryRes = selectSubCategory(categoryRes);
            productRes = selectProduct(categoryRes, subCategoryRes);
        break;

        case 2:
            if (!authenticateAdmin()) {
                break;
            }

            printHeader("ADMINISTRATOR MENU");
            
            cout << "Good day, admin! Choose a product to modify its stock and prices." << endl;
            categoryRes = selectCategory();
            subCategoryRes = selectSubCategory(categoryRes);
            productRes = selectProduct(categoryRes, subCategoryRes);

        break;
        case 3:
            cout << "Thank You!" << endl;
            exit(EXIT_SUCCESS);
            break;

        default:
            cout << "Invalid input!" << endl;
    }

    vector<Product> products = loadProducts("products.csv");

    // ADMINISTRATOR BACKEND

    if (menuRes == 2 && categoryRes >= 1 && categoryRes <= 5 && subCategoryRes >= 1 && subCategoryRes <= 3 && productRes >= 1 && productRes <= 3) {

        int selectedIndex = (categoryRes - 1) * 9 + (subCategoryRes - 1) * 3 + (productRes - 1);
        Product& selectedProduct = products[selectedIndex];

        printHeader("ADMININISTRATOR OPERATIONS");
        cout << "1.) Change Product Price" << endl;
        cout << "2.) Change Product Stock Quantity" << endl;
        cin >> adminMenuRes;

        switch (adminMenuRes) {
            case 1:
                cout << "Enter the new Product price for: " << selectedProduct.name << endl;
                cin >> priceRes;
                selectedProduct.price = priceRes;
                cout << "The new Product price for: " << selectedProduct.name << " is " << priceRes << "!" << endl;
                saveProducts("products.csv", products);
            break;
            case 2:
                cout << "Enter the new Product stock for: " << selectedProduct.name << endl;
                cin >> stockRes;
                selectedProduct.stock = stockRes;
                cout << "The new Product stock for: " << selectedProduct.name << " is " << stockRes << "!" << endl;
                saveProducts("products.csv", products);
            break;
            default:
                cout << "Invalid input!" << endl;
        }
    }

    // CALCULATIONS

    if (menuRes == 1 && categoryRes >= 1 && categoryRes <= 5 && subCategoryRes >= 1 && subCategoryRes <= 3 && productRes >= 1 && productRes <= 3) {
    
        int quantity;
        double price, total, payment, change, vat, vatable;
        char discountRes;

        int selectedIndex = (categoryRes - 1) * 9 + (subCategoryRes - 1) * 3 + (productRes - 1);
        // ^^ Based on the answer of this formula, it will be the ID of the CSV itself.
        // ex. category = 1, subcategory = 2, product = 3
        // answer will be: 0 + 3 + 2 = (ID = 4 / due to zero-based indexing)

        // 1 category -> 3 subcategories -> 3 products
        // 1 subcategory -> 3 products

        Product& selectedProduct = products[selectedIndex];

        price = selectedProduct.price;
        
        printHeader("PAYMENT");
        cout << "Enter quantity: ";
        cin >> quantity;

        while (quantity < 1 || quantity > selectedProduct.stock) {
            cout << "Invalid quantity or insufficient stock! Enter again: ";
            cin >> quantity;
        }

        printHeader("DISCOUNT");
        cout << "Are you a senior citizen or PWD? (Y/N): ";
        cin >> discountRes;

        bool customerEligible;

        switch (discountRes) {
            case 'Y':
            case 'y':
                customerEligible = true;
            break;
            case 'N':
            case 'n':
                customerEligible = false;
            break;
            default:
            cout << "Invalid input!" << endl;
            break;
        }
        set<int> noVatExemptionIds = {
            10, 11, 12, 13, 14, 15,
            28, 29, 30, 31, 32, 33, 34, 35, 36,
            37, 38, 39, 40, 41, 42, 43, 44, 45
        };

        bool discountApplies = customerEligible;
        bool vatExempt = customerEligible && noVatExemptionIds.count(selectedProduct.id) == 0;

        total = price * quantity;

        if (vatExempt) {
            total /= 1.12;
        }

        if (discountApplies) {
            total *= 0.8;
        }

        if (vatExempt) {
            vat = 0;
            vatable = 0;
        } else {
            vat = total * 12.0 / 112.0;
            vatable = total - vat;
        }

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

        printHeader("RECEIPT");
        cout << "Product:  " << selectedProduct.name << endl;
        cout << "Price:    ₱" << selectedProduct.price << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Total:    ₱" << total << endl;
        cout << "VATable   ₱" << vatable << endl;
        cout << "VAT       ₱" << vat << endl;
        cout << "Payment:  ₱" << payment << endl;
        cout << "Change:   ₱" << change << endl;
        printHeader("THANK YOU!");
    }

    return 0;
}
