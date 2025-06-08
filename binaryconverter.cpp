#include <iostream>
#include <string>
#include <bitset>
#include <cmath>
#include <limits>

using namespace std;

long long binaryToUnsigned(const string& bin) {
    return stoull(bin, nullptr, 2);
}

long long binaryToSigned(const string& bin, int bits) {
    if (bin[0] == '0') {
        return binaryToUnsigned(bin);
    } else {
        long long value = binaryToUnsigned(bin);
        return value - (1LL << bits);
    }
}

int main() {
    string binaryInput;
    int bitSize;

    cout << "Enter binary value: ";
    cin >> binaryInput;

    cout << "Enter bit size: ";
    cin >> bitSize;

    if (binaryInput.length() > bitSize) {
        cerr << "Error: Binary input is longer than the specified bit size." << endl;
        return 1;
    }

    while (binaryInput.length() < bitSize) {
        binaryInput = "0" + binaryInput;
    }

    long long unsignedVal = binaryToUnsigned(binaryInput);
    long long signedVal = binaryToSigned(binaryInput, bitSize);

    cout << "Bit size: " << bitSize << endl;
    cout << "Binary: " << binaryInput << endl;
    cout << "Unsigned decimal: " << unsignedVal << endl;
    cout << "Signed decimal: " << signedVal << endl;

    return 0;
}
