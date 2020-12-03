#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

class EncodingTools {
private:
	std::vector<char> data;
	std::vector<double> probabilities;
	std::vector<std::vector<int>> matrix;
	void readfile(char* path) {
		std::ifstream file(path, std::ios::in);
		if (file.is_open()) {
			data.clear();
			probabilities.clear();
			char symbol;
			while (file.get(symbol)) {
				bool _exist = false;
				for (size_t i = 0; i < data.size(); i++) {
					if ((int)(unsigned char)symbol == data[i]) {
						probabilities[i] ++;
						_exist = true;
						break;
					}
				}
				if (!_exist) {
					data.push_back((int)(unsigned char)symbol);
					probabilities.push_back(1);
				}
			}
			QuickSort(0, probabilities.size() - 1);
			int sumOfProbabilities = 0;
			for (int i = 0; i < probabilities.size(); ++i) {
				sumOfProbabilities += probabilities[i];
			}
			for (int i = 0; i < probabilities.size(); ++i) {
				probabilities[i] /= sumOfProbabilities;
			}
			return;
		}
		std::cout << "Error opening file..." << std::endl;
	}
	void QuickSort(int L, size_t R)
	{
		int i = L;
		int j = R;
		double temp = probabilities[(i + j) / 2];

		while (i <= j) {
			while (probabilities[i] > temp) {
				i++;
			}
			while (probabilities[j] < temp) {
				j--;
			}
			if (i <= j) {
				std::swap(probabilities[i], probabilities[j]);
				std::swap(data[i], data[j]);
				i++;
				j--;
			}
		}
		if (L < j) {
			QuickSort(L, j);
		}
		if (i < R) {
			QuickSort(i, R);
		}
	}
public:
	void shannonCode() {
		if (!probabilities.empty()) {
			matrix.clear();
			std::vector<double> probaSum(probabilities.size());
			std::vector<int> lenght(probabilities.size());
			matrix.resize(probabilities.size());
			probaSum[0] = 0;
			lenght[0] = -log2(probabilities[0]) + 1;
			for (size_t i = 1; i < probabilities.size(); i++) {
				probaSum[i] = probaSum[i - 1] + probabilities[i - 1];
				lenght[i] = -log2(probabilities[i]) + 1;
			}
			for (size_t i = 0; i < probabilities.size(); i++) {
				matrix[i].resize(lenght[i]);
				for (size_t j = 0; j < lenght[i]; ++j) {
					probaSum[i] *= 2;
					matrix[i][j] = probaSum[i];
					if (probaSum[i] >= 1) {
						probaSum[i]--;
					}
				}
			}
		}
	}
	~EncodingTools() {
		probabilities.clear();
		data.clear();
		matrix.clear();
	}

	void menu() {
		return;
	}
};