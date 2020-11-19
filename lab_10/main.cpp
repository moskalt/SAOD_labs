#include <cmath>
#include <iostream>
#include <vector>

const short int bit_size = 16;

std::vector<unsigned short int> fromIntToBitArray(int num, size_t size) {
    int integer = num;
    std::vector<unsigned short int> bitArray(size);
    for (size_t i = 0; i < size; i++) {
        bitArray[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        bitArray[i] = (integer >> (size - i - 1)) & 1;
    }
    return bitArray;
}

int getExp() {
    return (int) (log((double) bit_size) / log(2));
}

std::vector<unsigned short int> getCodeArray(std::vector<unsigned short int> bitArray) {
    size_t counter;
    size_t index;
    for (size_t i = 0; i < bit_size; i++) {
        if (bitArray[i] == 1) {
            counter = bit_size - i;
            index = i;
            break;
        } else {
            counter = 0;
            index = 0;
        }
    }
    //4 is exponent
    std::vector<unsigned short int> codeLength = fromIntToBitArray((int) counter, getExp());
    if (counter == 0 || counter == 1) {
        return codeLength;
    }
    std::vector<unsigned short int> codeArray(getExp() + counter - 1);
    size_t codeLengthSize = codeLength.size();
    for (size_t i = 0; i < codeLengthSize; i++) {
        codeArray[i] = codeLength[i];
    }
    size_t i;
    size_t j;
    for (i = codeLengthSize, j = index + 1; i < (getExp() + counter - 1); i++, j++) {
        codeArray[i] = bitArray[j];
    }
    codeLength.clear();
    return codeArray;
}
std::vector<unsigned short int> getEliasYArray(std::vector<unsigned short int> bitArray, int num) {
    size_t counter;
    size_t index;
    for (size_t i = 0; i < bit_size; i++) {
        if (bitArray[i] == 1) {
            counter = bit_size - i;
            index = i;
            break;
        } else {
            counter = 0;
            index = 0;
        }
    }
    std::vector<unsigned short int> codeLength;
    if (counter != 0) {
        for (size_t i = 0; i < counter - 1; ++i) {
            codeLength.push_back(0);
        }
        for (size_t i = index; i < bit_size; ++i) {
            codeLength.push_back(bitArray[i]);
        }
    }
    return codeLength;
}

std::vector<unsigned short int> getEliasWArray(std::vector<unsigned short int> bitArray, int num) {
    size_t counter;
    size_t index;
    for (size_t i = 0; i < bit_size; i++) {
        if (bitArray[i] == 1) {
            counter = bit_size - i;
            index = i;
            break;
        } else {
            counter = 0;
            index = 0;
        }
    }
    std::vector<unsigned short int> codeArray;
    if (num == 0) {
        return codeArray;
    }
    codeArray.push_back(0);
    for (size_t i = bit_size - 1; i >= index; i--) {
        codeArray.insert(codeArray.begin(), bitArray[i]);
    }
    int exponent;
    
    std::vector<unsigned short int> temp_vector;
    int temp_exponent;
    exponent = 100;
    while (exponent > 2) {
        exponent = log(counter - 1) / log(2) + 1;
        temp_vector = fromIntToBitArray(counter - 1, exponent);
        for (size_t i = temp_vector.size(); i > 0; i--) {
            codeArray.insert(codeArray.begin(), temp_vector[i - 1]);
        }
        temp_vector.clear();
        counter = exponent;
    }
    return codeArray;
}

int main() {
    int num = 16;
    std::vector<std::vector<unsigned short int>> FixedCodeArray;
    std::vector<std::vector<unsigned short int>> YCodeArray;
    int temp_num = 0;
    std::vector<unsigned short int> Array = fromIntToBitArray(num, bit_size);
    std::vector<unsigned short int> codeWArray = getEliasWArray(Array, num);
    for (size_t i = 0; i < codeWArray.size(); i++) {
        std::cout << codeWArray[i];
    }
    std::cout << std::endl
              << std::endl;
    while (temp_num <= num) {
        //calculate all codes
        std::vector<unsigned short int> bitArray = fromIntToBitArray(temp_num, bit_size);
        std::vector<unsigned short int> codeArray = getCodeArray(bitArray);
        std::vector<unsigned short int> codeYArray = getEliasYArray(bitArray, num);
        YCodeArray.push_back(codeYArray);
        FixedCodeArray.push_back(codeArray);
        temp_num++;
        bitArray.clear();
    }
    for (size_t i = 0; i <= num; i++) {
        size_t size = FixedCodeArray[i].size();
        std::cout.width(3);
        std::cout << i << " - ";
        std::cout.width(0);
        for (size_t j = 0; j < size; j++) {
            std::cout << FixedCodeArray[i][j];
        }
        int difSize = (int) FixedCodeArray[FixedCodeArray.size() - 1].size() - (int) FixedCodeArray[i].size();
        for (int j = 0; j < difSize; ++j) {
            std::cout << " ";
        }
        std::cout << " ";
        std::cout.width(0);
        if (YCodeArray[i].empty()) {
            std::cout<< "NaN";
        }
        for (auto &j : YCodeArray[i]) {
            std::cout << j;
        }
        std::cout << std::endl;
    }

    std::cin.get();
    std::cin.ignore();
    return 0;
}
