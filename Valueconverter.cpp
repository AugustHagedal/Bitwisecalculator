#include <iostream>
#include <string>
#include <bitset>
#include <cmath>
#include <limits>

using namespace std;

void print_binary(uint64_t val, int bits) {
    val &= (bits >= 64) ? UINT64_MAX : (1ULL << bits) - 1;
    for (int i = bits - 1; i >= 0; i--)
        cout << ((val >> i) & 1);
}

void show_range(bool signed_mode, int bit_width) {
    cout << "\n--- Value Range (" << (signed_mode ? "Signed" : "Unsigned")
         << ", " << bit_width << "-bit) ---\n";

    if (bit_width >= 64) {
        if (signed_mode) {
            int64_t min_signed = numeric_limits<int64_t>::min();
            int64_t max_signed = numeric_limits<int64_t>::max();
            cout << "Signed Min: " << min_signed << " | Binary: ";
            print_binary(static_cast<uint64_t>(min_signed), 64);
            cout << "\n";
            cout << "Signed Max: " << max_signed << " | Binary: ";
            print_binary(static_cast<uint64_t>(max_signed), 64);
            cout << "\n";
        } else {
            uint64_t max = numeric_limits<uint64_t>::max();
            cout << "Unsigned Min: 0 | Binary: ";
            print_binary(0, 64);
            cout << "\n";
            cout << "Unsigned Max: " << max << " | Binary: ";
            print_binary(max, 64);
            cout << "\n";
        }
    } else {
        uint64_t mask = (1ULL << bit_width) - 1;
        if (signed_mode) {
            int64_t max = (1LL << (bit_width - 1)) - 1;
            int64_t min = -(1LL << (bit_width - 1));
            cout << "Signed Min: " << min << " | Binary: ";
            print_binary(static_cast<uint64_t>(min), bit_width);
            cout << "\n";
            cout << "Signed Max: " << max << " | Binary: ";
            print_binary(static_cast<uint64_t>(max), bit_width);
            cout << "\n";
        } else {
            uint64_t max = (1ULL << bit_width) - 1;
            cout << "Unsigned Min: 0 | Binary: ";
            print_binary(0, bit_width);
            cout << "\n";
            cout << "Unsigned Max: " << max << " | Binary: ";
            print_binary(max, bit_width);
            cout << "\n";
        }
    }

    cout << "------------------------------\n\n";
}

void decimal_to_binary(int64_t n, int bit_width) {
    print_binary(static_cast<uint64_t>(n), bit_width);
    cout << "\n";
}

void decimal_to_hex(int64_t n) {
    cout << hex << uppercase << n << dec << "\n";
}

void binary_to_decimal(const string& bin) {
    int64_t result = 0;
    for (char c : bin)
        result = result * 2 + (c - '0');
    cout << result << "\n";
}

void binary_to_hex(const string& bin) {
    int64_t dec = 0;
    for (char c : bin)
        dec = dec * 2 + (c - '0');
    cout << hex << uppercase << dec << dec << "\n";
}

void hex_to_decimal(const string& hex) {
    int64_t dec = stoll(hex, nullptr, 16);
    cout << dec << "\n";
}

void hex_to_binary(const string& hex, int bit_width) {
    int64_t dec = stoll(hex, nullptr, 16);
    print_binary(static_cast<uint64_t>(dec), bit_width);
    cout << "\n";
}

int main() {
    int choice;
    string input;
    int64_t dec;

    cout << "Select conversion:\n";
    cout << "1. Decimal to Binary\n";
    cout << "2. Decimal to Hex\n";
    cout << "3. Binary to Decimal\n";
    cout << "4. Binary to Hex\n";
    cout << "5. Hex to Decimal\n";
    cout << "6. Hex to Binary\n";
    cout << "7. Show Unsigned Integer Range\n";
    cout << "8. Show Signed Integer Range\n";
    cout << "Choice: ";
    cin >> choice;

    bool signed_mode = false;
    int bit_width = 0;

    if (choice >= 1 && choice <= 2) {
        cout << "Enter bit width (1–64): ";
        cin >> bit_width;
        if (bit_width < 1 || bit_width > 64) {
            cout << "Invalid bit width.\n";
            return 1;
        }
        cout << "Enter decimal: ";
        cin >> dec;

        if (choice == 1)
            decimal_to_binary(dec, bit_width);
        else
            decimal_to_hex(dec);
    } else if (choice == 3 || choice == 4) {
        cout << "Enter binary: ";
        cin >> input;

        if (choice == 3)
            binary_to_decimal(input);
        else
            binary_to_hex(input);
    } else if (choice == 5 || choice == 6) {
        cout << "Enter hex: ";
        cin >> input;

        if (choice == 5)
            hex_to_decimal(input);
        else {
            cout << "Enter bit width (1–64): ";
            cin >> bit_width;
            if (bit_width < 1 || bit_width > 64) {
                cout << "Invalid bit width.\n";
                return 1;
            }
            hex_to_binary(input, bit_width);
        }
    } else if (choice == 7 || choice == 8) {
        signed_mode = (choice == 8);
        cout << "Enter bit width (1–64): ";
        cin >> bit_width;
        if (bit_width < 1 || bit_width > 64) {
            cout << "Invalid bit width.\n";
            return 1;
        }
        show_range(signed_mode, bit_width);
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
