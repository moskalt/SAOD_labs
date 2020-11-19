#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

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
	//bit_size количество бит в введенном числе(для первого кода 16, перепишешь функцию когда будешь свои писать
	return log(bit_size) / log(2);
}

std::vector<unsigned short int> getCodeArray(std::vector<unsigned short int> bitArray) {
	size_t counter;
	size_t index;
	for (size_t i = 0; i < bit_size; i++) {
		if (bitArray[i] == 1) {
			counter = bit_size - i;
			index = i;
			break;
		}
		else {
			counter = 0;
			index = 0;
		}
	}
	//4 is exponent
	std::vector<unsigned short int> codeLenght = fromIntToBitArray((int)counter, getExp());
	if (counter == 0 || counter == 1) {
		return codeLenght;
	}
	std::vector<unsigned short int> codeArray (getExp() + counter - 1);
	size_t codeLenghtSize = codeLenght.size();
	for (size_t i = 0; i < codeLenghtSize; i++) {
		codeArray[i] = codeLenght[i];
	}
	size_t i = codeLenghtSize;
	size_t j = index + 1;
	for (i = codeLenghtSize, j = index + 1; i < (getExp()
		+ counter - 1); i++, j++) {
		codeArray[i] = bitArray[j];
	}
	codeLenght.clear();
	return codeArray;
}

int main() {
	//16 bit integers
	std::cout << "Input integer :";
	int num;
	std::vector <std::vector< unsigned short int >> FixedCodeArray;
	std::cin >> num;
	int temp_num = 0;
	while (temp_num <= num) {
		//calculate all codes
		std::vector<unsigned short int> bitArray = fromIntToBitArray(temp_num, bit_size);
		std::vector<unsigned short int> codeArray = getCodeArray(bitArray);
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
			if (j % 4 == 0) {
				std::cout << " ";
			}
			std::cout << FixedCodeArray[i][j];
		}
		std::cout << std::endl;
	}
	std::cin.get();
	std::cin.ignore();
	return 0;
}