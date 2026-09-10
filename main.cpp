#include <iostream>
#include <cstdlib> 
using namespace std;

int main() {

    int menuRes, categoryRes, subCategoryRes, productRes;
    
    cout << "────────────── PHARMACY SYSTEM OVERVIEW ──────────────" << endl;
    cout << endl;

    cout << "────────────── MAIN MENU ──────────────" << endl;
    cout << "1.) Order Products" << endl;
    cout << "2.) Exit" << endl;
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
            cout << "Thank You!" << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cout << "Invalid input!" << endl;
    }
    return 0;
}