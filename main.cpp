#include <iostream>
#include <bitset>
#include <iomanip>
#include <string>

using namespace std;

int parse_number(const string& input) {
    if (input.rfind("0b", 0) == 0 || input.rfind("0B", 0) == 0)
        return stoi(input.substr(2), nullptr, 2);
    else if (input.rfind("0x", 0) == 0 || input.rfind("0X", 0) == 0)
        return stoi(input.substr(2), nullptr, 16);
    else
        return stoi(input);
}

string to_binary(int value, int bit_width) {
    bitset<32> bits(value);
    return bits.to_string().substr(32 - bit_width);
}

void print_result(const string& label, int value, int bit_width, bool is_signed) {
    unsigned int mask = (1u << bit_width) - 1;
    unsigned int masked = value & mask;
    int signed_val = masked;

    if (is_signed && (masked & (1u << (bit_width - 1))))
        signed_val = masked - (1 << bit_width);

    cout << setw(35) << left << label << ": "
         << to_binary(masked, bit_width)
         << " (dec: " << (is_signed ? signed_val : masked) << ")"
         << " (hex: " << hex << uppercase << masked << dec << ")" << endl;
}

int main() {
    int mode, bit_width, shift;
    string input_x, input_y;

    cout << "Choose mode:\n1 - Signed\n2 - Unsigned\nYour choice: ";
    cin >> mode;
    bool is_signed = (mode == 1);

    cout << "Enter bit width (e.g. 8, 14, 16, 32): ";
    cin >> bit_width;
    if (bit_width <= 0 || bit_width > 32) {
        cerr << "Unsupported bit width.\n";
        return 1;
    }

    if (bit_width == 8) {
        is_signed = true;
        cout << "(Note: Signed interpretation enabled automatically for 8-bit mode using 2's complement)\n";
    }

    unsigned int mask = (1u << bit_width) - 1;

    cout << "Enter x (decimal, 0x..., or 0b...): ";
    cin >> input_x;
    int x = parse_number(input_x);

    cout << "Enter y (decimal, 0x..., or 0b...): ";
    cin >> input_y;
    int y = parse_number(input_y);

    cout << "Enter shift amount: ";
    cin >> shift;

    cout << "\n--- Bitwise Results ---\n";
    print_result("x", x, bit_width, is_signed);
    print_result("y", y, bit_width, is_signed);

    print_result("x & y", x & y, bit_width, is_signed);
    print_result("x | y", x | y, bit_width, is_signed);
    print_result("x ^ y", x ^ y, bit_width, is_signed);
    print_result("~x", ~x, bit_width, is_signed);
    print_result("~y", ~y, bit_width, is_signed);

    print_result("x << shift", x << shift, bit_width, is_signed);
    print_result("y << shift", y << shift, bit_width, is_signed);

    int signed_x = x & mask;
    if (signed_x & (1 << (bit_width - 1))) signed_x -= (1 << bit_width);

    int signed_y = y & mask;
    if (signed_y & (1 << (bit_width - 1))) signed_y -= (1 << bit_width);

    if (is_signed) {
        print_result("x >> shift (arithmetic)", signed_x >> shift, bit_width, is_signed);
        print_result("y >> shift (arithmetic)", signed_y >> shift, bit_width, is_signed);
    }

    print_result("x >> shift (logical)", ((unsigned int)x & mask) >> shift, bit_width, false);
    print_result("y >> shift (logical)", ((unsigned int)y & mask) >> shift, bit_width, false);

    return 0;
}
