#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
#include <iostream>
#include <cstdlib> 
#include <algorithm>
#include <sstream>
#include <string>
#include <limits>
#include <stdexcept>
 
// CSV libraries
#include <fstream>
#include <vector>
 
// VAT
#include <set>

// REFERENCE NUMBER
#include <iomanip>
#include <cctype>
#include <ctime>
#include <cmath>

using namespace std;

class InvalidInputException : public runtime_error {
public:
    explicit InvalidInputException(const string& message) : runtime_error(message) {}
};

[[noreturn]] void invalidInput(const string& message = "Invalid input!") {
    if (cin.eof()) {
        cout << endl << "Input ended. Exiting." << endl;
        exit(EXIT_FAILURE);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << message << endl;
    throw InvalidInputException(message);
}

// SAFE INPUT HELPERS
int readInt() {
    int value;
    if (!(cin >> value)) {
        if (cin.eof()) {
            cout << endl << "Input ended. Exiting." << endl;
            exit(EXIT_FAILURE);
        }
        invalidInput("Invalid input! Please enter a number.");
    }
    string remainder;
    getline(cin, remainder);
    if (remainder.find_first_not_of(" \t\r") != string::npos) {
        invalidInput("Invalid input! Please enter a number.");
    }
    return value;
}

double readDouble() {
    double value;
    if (!(cin >> value)) {
        if (cin.eof()) {
            cout << endl << "Input ended. Exiting." << endl;
            exit(EXIT_FAILURE);
        }
        invalidInput("Invalid input! Please enter a number.");
    }
    string remainder;
    getline(cin, remainder);
    if (remainder.find_first_not_of(" \t\r") != string::npos) {
        invalidInput("Invalid input! Please enter a number.");
    }
    return value;
}
 
struct Product { 
    int id;
    string name;
    string category;
    string subcategory;
    double price;
    int stock;
};
 
struct CartItem {
    Product product;
    int quantity;
};
 
// BORDER STYLING
 
void printLine(int width) {
    cout << "+";
    for (int i = 0; i < width; i++) {
        cout << "=";
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
 
// LOAD CSV FOR PRODUCTS
 
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
 
// SAVE TRANSACTION CSV
void saveTransactions(const string& filename, const vector<CartItem>& cartItems,
    const string& referenceNumber, double subtotal, double vat, double total,
    double payment, double change, const string& paymentMethod, const string& paymentRef) 
    
    {
    ifstream existingFile(filename);
    bool writeHeader = !existingFile || existingFile.peek() == ifstream::traits_type::eof();
    existingFile.close();
 
    ofstream file(filename, ios::app);
 
    if (!file.is_open()) {
        cout << "Unable to open the CSV file for writing." << endl;
        return;
    }
 
    file.setf(ios::fixed);
    file.precision(2);
 
    if (writeHeader) {
        file << "Reference Number,Product ID,Product Name,Quantity,Unit Price,Subtotal,VAT,Total,Payment,Change,Payment Method,Payment Reference\n";
    }
 
    for (const CartItem& item : cartItems) {
        file << referenceNumber << "," << item.product.id << "," << item.product.name << ","
             << item.quantity << "," << item.product.price << "," << subtotal << ","
             << vat << "," << total << "," << payment << "," << change << ","
             << paymentMethod << "," << paymentRef << endl;
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
        if (!(cin >> enteredPassword)) {
            invalidInput("Unable to read administrator password!");
        }
 
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
    categoryRes = readInt();
 
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
            invalidInput("Invalid category selection!");
    }
 
    int subCategoryRes;
    subCategoryRes = readInt();
    if (subCategoryRes < 1 || subCategoryRes > 3) {
        invalidInput("Invalid subcategory selection!");
    }
    return subCategoryRes;
}
 
// PRODUCTS FUNCTION
 
int selectProduct(int categoryRes, int subCategoryRes, const vector<Product>& products) {
    if (categoryRes < 1 || categoryRes > 5 || subCategoryRes < 1 || subCategoryRes > 3) {
        invalidInput("Invalid product selection!");
    }

    int firstProductIndex = (categoryRes - 1) * 9 + (subCategoryRes - 1) * 3;
    if (firstProductIndex + 2 >= static_cast<int>(products.size())) {
        invalidInput("Product selection is unavailable!");
    }

    printHeader(products[firstProductIndex].subcategory);

    cout << fixed << setprecision(2);
    
    for (int i = 0; i < 3; i++) {
        const Product& product = products[firstProductIndex + i];
        cout << i + 1 << ".) " << product.name << " - ₱" << product.price << endl;
    }

    int productRes;
    productRes = readInt();
    if (productRes < 1 || productRes > 3) {
        invalidInput("Invalid product selection!");
    }
    return productRes;
}
 
// PAYMENT METHOD FUNCTION
 
string selectPaymentMethod() {
 
    int methodRes, providerRes;
 
    printHeader("PAYMENT METHOD");
    cout << "1.) Cash" << endl;
    cout << "2.) E-Wallet" << endl;
    cout << "3.) Bank" << endl;
    methodRes = readInt();
 
    if (methodRes < 1 || methodRes > 3) {
        invalidInput("Invalid payment method selection!");
    }
 
    switch (methodRes) {
        case 1:
            return "Cash";
        case 2:
            printHeader("E-WALLET");
            cout << "1.) GCash" << endl;
            cout << "2.) MariBank" << endl;
            cout << "3.) GoTyme" << endl;
            providerRes = readInt();
 
            if (providerRes < 1 || providerRes > 3) {
                invalidInput("Invalid e-wallet selection!");
            }
 
            if (providerRes == 1) return "E-Wallet - GCash";
            if (providerRes == 2) return "E-Wallet - MariBank";
            return "E-Wallet - GoTyme";
        default:
            printHeader("BANK");
            cout << "1.) BDO" << endl;
            cout << "2.) BPI" << endl;
            cout << "3.) China Bank" << endl;
            providerRes = readInt();
 
            if (providerRes < 1 || providerRes > 3) {
                invalidInput("Invalid bank selection!");
            }
 
            if (providerRes == 1) return "Bank - BDO";
            if (providerRes == 2) return "Bank - BPI";
            return "Bank - China Bank";
    }
}
 
int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    vector<CartItem> cart; //Cart vector load in int main so it can be accessed from the switch and receipt at the bottom
    vector<Product> products = loadProducts("products.csv"); //same with this one
    int menuRes, categoryRes, subCategoryRes, productRes;
    int adminMenuRes, stockRes;
    double priceRes;
    string referenceNumber;
 
    cout << R"(  
    ░██████████                      ░██                                ░██████                                    
        ░██                          ░██                               ░██   ░██                                   
        ░██     ░███████   ░███████  ░████████  ░████████   ░███████  ░██        ░██    ░██ ░██░████  ░███████     
        ░██    ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██        ░██    ░██ ░███     ░██    ░██    
        ░██    ░█████████ ░██        ░██    ░██ ░██    ░██ ░██    ░██ ░██        ░██    ░██ ░██      ░█████████    
        ░██    ░██        ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██  ░██   ░██ ░██   ░███ ░██      ░██           
        ░██     ░███████   ░███████  ░██    ░██ ░██    ░██  ░███████    ░██████   ░█████░██ ░██       ░███████     
    )" << endl;
 
    while (true) {
        try {
            printHeader("MAIN MENU");
            cout << "1.) Order Products" << endl;
            cout << "2.) Enter as Administrator" << endl;
            cout << "3.) Exit" << endl;
            menuRes = readInt();

            switch (menuRes) {
        case 1: {
        char looper;
        do {
            categoryRes = selectCategory();
            subCategoryRes = selectSubCategory(categoryRes);
            productRes = selectProduct(categoryRes, subCategoryRes, products);
            
            if (categoryRes >= 1 && categoryRes <= 5 && subCategoryRes >= 1 && subCategoryRes <= 3 && productRes >= 1 && productRes <= 3) {
            
            // Each category has 3 subcategories with 3 products each.
            // Example: category 1, subcategory 2, product 3 gives index 5 (CSV ID 6).
            int selectedIndex = (categoryRes - 1) * 9 + (subCategoryRes - 1) * 3 + (productRes - 1);
            Product& selectedProduct = products[selectedIndex];
 
            int inCart = 0;
            for (const auto& item : cart) {
                if (item.product.id == selectedProduct.id) inCart += item.quantity;
            }
            int available = selectedProduct.stock - inCart;

            int quantity = 0;
            cout << "You selected: " << selectedProduct.name << endl;
            if (available < 1) {
                cout << "Sorry, no more stock available for this product." << endl;
            } else {
                cout << "Available Stock: " << available << endl;
                cout << "Enter quantity: ";
                quantity = readInt();

                if (quantity < 1 || quantity > available) {
                    invalidInput("Invalid quantity or insufficient stock!");
                }

                bool found = false;
                for (auto& item : cart) {
                    if (item.product.id == selectedProduct.id) {
                        item.quantity += quantity;
                        found = true;
                        break;
                    }
                }
                if (!found) cart.push_back({selectedProduct, quantity});
            }
 
            if (quantity > 0) cout << "Successfully added " << quantity << "x " << selectedProduct.name << " to your cart!" << endl;
 
        } else {
            invalidInput("Invalid selection!");
        }
        cout << "Would you like to order more? (Y/N): ";
        cin >> looper;
        if (!cin || (looper != 'y' && looper != 'Y' && looper != 'n' && looper != 'N')) {
            invalidInput("Invalid response!");
        }
        } while (looper == 'y' || looper == 'Y');
        break;
        }  
        case 2:
            if (!authenticateAdmin()) {
                break;
            }
 
            printHeader("ADMINISTRATOR MENU");
            
            cout << "Good day, admin! What would you like to change?" << endl;
            cout << "1.) Change Product Price" << endl;
            cout << "2.) Change Product Stock Quantity" << endl;
            adminMenuRes = readInt();

            if (adminMenuRes != 1 && adminMenuRes != 2) {
                invalidInput("Invalid administrator menu selection!");
            }
 
            cout << "Choose a product to modify." << endl;
            categoryRes = selectCategory();
            subCategoryRes = selectSubCategory(categoryRes);
            productRes = selectProduct(categoryRes, subCategoryRes, products);
 
        break;
        case 3:
            cout << "Thank You!" << endl;
            exit(EXIT_SUCCESS);
            break;
 
        default:
            invalidInput("Invalid main menu selection!");
    }
 
    
    // ADMINISTRATOR BACKEND
 
    if (menuRes == 2 && categoryRes >= 1 && categoryRes <= 5 && subCategoryRes >= 1 && subCategoryRes <= 3 && productRes >= 1 && productRes <= 3) {
 
        int selectedIndex = (categoryRes - 1) * 9 + (subCategoryRes - 1) * 3 + (productRes - 1);
        Product& selectedProduct = products[selectedIndex];
 
        printHeader("ADMININISTRATOR OPERATIONS");
 
        switch (adminMenuRes) {
            case 1:
                cout << "Enter the new Product price for: " << selectedProduct.name << endl;
                priceRes = readDouble();
                if (!std::isfinite(priceRes) || priceRes <= 0) {
                    invalidInput("Product price must be a positive number!");
                }
                selectedProduct.price = priceRes;
                cout << "The new Product price for: " << selectedProduct.name << " is " << priceRes << "!" << endl;
                saveProducts("products.csv", products);
            break;
            case 2:
                cout << "Enter the new Product stock for: " << selectedProduct.name << endl;
                stockRes = readInt();
                if (stockRes < 0) {
                    invalidInput("Product stock cannot be negative!");
                }
                selectedProduct.stock = stockRes;
                cout << "The new Product stock for: " << selectedProduct.name << " is " << stockRes << "!" << endl;
                saveProducts("products.csv", products);
            break;
            default:
                invalidInput("Invalid administrator operation!");
        }
    }
 
    //RECEIPT AND DISCOUNT CALCULATION
    if (!cart.empty()) {
        char discountRes;
        
        printHeader("DISCOUNT");
        cout << "Are you a senior citizen or PWD? (Y/N): ";
        if (!(cin >> discountRes)) {
            invalidInput("Unable to read discount response!");
        }
 
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
                invalidInput("Invalid discount response!");
        }
 
        set<int> noVatExemptionIds = {
            10, 11, 12, 13, 14, 15,
            28, 29, 30, 31, 32, 33, 34, 35, 36,
            37, 38, 39, 40, 41, 42, 43, 44, 45
        };
 
        double grandTotal = 0.0;
        double totalVat = 0.0;
        double totalVatable = 0.0;
 
        // Loop through the cart to accumulate totals for all items ordered
        for (const auto& item : cart) {
            double itemPrice = item.product.price;
            int itemQuantity = item.quantity;
            
            bool discountApplies = customerEligible;
            bool vatExempt = customerEligible && noVatExemptionIds.count(item.product.id) == 0;
 
            double itemTotal = itemPrice * itemQuantity;
 
            if (vatExempt) {
                itemTotal /= 1.12;
            }
 
            if (discountApplies) {
                itemTotal *= 0.8;
            }
 
            double itemVat = 0.0;
            double itemVatable = 0.0;
            if (vatExempt) {
                itemVat = 0;
                itemVatable = 0;
            } else {
                itemVat = itemTotal * 12.0 / 112.0;
                itemVatable = itemTotal - itemVat;
            }
 
            grandTotal += itemTotal;
            totalVat += itemVat;
            totalVatable += itemVatable;
        }
 
        double payment, change;
        
        cout.setf(ios::fixed);
        cout.precision(2);
 
        cout << "Total Amount: ₱" << grandTotal << endl;
 
        // PAYMENT METHOD AND PAYMENT CONFIRMATION
 
        string paymentMethod = selectPaymentMethod();
        string paymentRef = "N/A";
        bool orderCancelled = false;
 
        if (paymentMethod == "Cash") {
            cout << "Enter payment (0 to cancel order): ₱";
            payment = readDouble();

            if (!std::isfinite(payment) || payment < 0 || (payment != 0 && payment < grandTotal)) {
                invalidInput("Invalid or insufficient payment!");
            }
 
            if (payment == 0) {
                orderCancelled = true;
            }
        } else {
            cout << "Enter the payment reference number: ";
            if (!(cin >> paymentRef)) {
                invalidInput("Unable to read payment reference!");
            }
 
            char confirmRes;
            cout << "Payment received? (Y = yes, C = cancel order): ";
            if (!(cin >> confirmRes)) {
                invalidInput("Unable to read payment confirmation!");
            }

            if (!cin || (confirmRes != 'Y' && confirmRes != 'y' && confirmRes != 'C' && confirmRes != 'c')) {
                invalidInput("Invalid payment confirmation!");
            }
 
            if (confirmRes == 'C' || confirmRes == 'c') {
                orderCancelled = true;
            } else {
                payment = grandTotal;   // exact amount for e-wallet and bank, so no change
            }
        }
 
        // Cancelled orders stop here: no stock deduction, no transaction saved
        if (orderCancelled) {
            cout << "Order cancelled. No payment was made." << endl;
            return 0;
        }
        
        change = payment - grandTotal;
 
        // REFERENCE NUMBER 
 
        // Local time from PC
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        
        stringstream referenceStream;
 
        referenceStream << "PH-"
                        << put_time(localTime, "%Y%m%d-%H%M%S");
 
        referenceNumber = referenceStream.str();
 
 
        for (const auto& item : cart) {
            for (auto& p : products) {
                if (p.id == item.product.id) {
                    p.stock -= item.quantity;
                }
            }
        }
        saveProducts("products.csv", products);
 
        saveTransactions("transactions.csv", cart, referenceNumber, totalVatable,
            totalVat, grandTotal, payment, change, paymentMethod, paymentRef);
 
        // ITEMIZED RECEIPT
        printHeader("RECEIPT");
        cout << "Products Ordered:" << endl;
        for (const auto& item : cart) {
            cout << " - " << item.product.name << " (Qty: " << item.quantity << ") @ ₱" << item.product.price << " each" << endl;
        }
        cout << "----------------------------------------" << endl;
        cout << "Total:    ₱" << grandTotal << endl;
        cout << "Subtotal  ₱" << totalVatable << endl;
        cout << "VAT       ₱" << totalVat << endl;
        cout << "Payment:  ₱" << payment << endl;
        cout << "Change:   ₱" << change << endl;
        cout << "Method:   " << paymentMethod << endl;
        cout << "Pay Ref:  " << paymentRef << endl;
        cout << "Status:   PAID" << endl;
        cout << "Reference Number: " << referenceNumber << endl;
        printHeader("THANK YOU!");
    }
 
            return 0;
        } catch (const InvalidInputException&) {
            cout << "Returning to the main menu." << endl;
        }
    }
}
