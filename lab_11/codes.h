#pragma once
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class EncodingTools {
private:
    std::vector<char> m_data;
    std::vector<double> m_probabilities;
    std::vector<std::vector<int>> m_matrix;
    void quickSort(int L, size_t R) {
        int i = L;
        int j = R;
        double temp = m_probabilities[(i + j) / 2];

        while (i <= j) {
            while (m_probabilities[i] > temp) {
                i++;
            }
            while (m_probabilities[j] < temp) {
                j--;
            }
            if (i <= j) {
                std::swap(m_probabilities[i], m_probabilities[j]);
                std::swap(m_data[i], m_data[j]);
                i++;
                j--;
            }
        }
        if (L < j) {
            quickSort(L, j);
        }
        if (i < R) {
            quickSort(i, R);
        }
    }
    void quickSortH(int L, size_t R) {
        int i = L;
        int j = R;
        char temp = m_data[(i + j) / 2];

        while (i <= j) {
            while (m_data[i] < temp && i >= 0) {
                i++;
            }
            while (m_data[j] > temp && j >= 0) {
                j--;
            }
            if (i <= j) {
                std::swap(m_probabilities[i], m_probabilities[j]);
                std::swap(m_data[i], m_data[j]);
                i++;
                j--;
            }
        }
        if (L < j) {
            quickSortH(L, j);
        }
        if (i < R) {
            quickSortH(i, R);
        }
    }

protected:
    void readfile(char *path) {
        std::ifstream file(path, std::ios::in);
        if (file.is_open()) {
            m_data.clear();
            m_probabilities.clear();
            char symbol;
            while (file.get(symbol)) {
                bool isExist = false;
                for (size_t i = 0; i < m_data.size(); i++) {
                    if ((int) (unsigned char) symbol == m_data[i]) {
                        m_probabilities[i]++;
                        isExist = true;
                        break;
                    }
                }
                if (!isExist) {
                    m_data.push_back((int) (unsigned char) symbol);
                    m_probabilities.push_back(1);
                }
            }
            quickSort(0, m_data.size() - 1);
            int sumOfProbabilities = 0;
            for (auto &probability : m_probabilities) {
                sumOfProbabilities += probability;
            }
            for (auto &probability : m_probabilities) {
                probability /= sumOfProbabilities;
            }
            return;
        }
        std::cout << "Error opening file..." << std::endl;
    }
    void output() {
        for (int i = 0; i < m_matrix.size(); ++i) {
            std::cout << m_data[i] << "    ";
            std::cout << m_probabilities[i] << "    ";
            for (auto &j : m_matrix[i]) {
                std::cout << j;
            }
            std::cout << "   ";
            std::cout << m_matrix[i].size() << std::endl;
        }
    }
    void shannonCode() {
        std::cout << "Shannon code" << std::endl;
        if (!m_probabilities.empty()) {
            m_matrix.clear();
            std::vector<double> probSum(m_probabilities.size());
            std::vector<int> length(m_probabilities.size());
            m_matrix.resize(m_probabilities.size());
            probSum[0] = 0;
            length[0] = -log2(m_probabilities[0]) + 1;
            for (size_t i = 1; i < m_probabilities.size(); i++) {
                probSum[i] = probSum[i - 1] + m_probabilities[i - 1];
                length[i] = -log2(m_probabilities[i]) + 1;
            }
            for (size_t i = 0; i < m_probabilities.size(); i++) {
                m_matrix[i].resize(length[i]);
                for (size_t j = 0; j < length[i]; ++j) {
                    probSum[i] *= 2;
                    m_matrix[i][j] = probSum[i];
                    if (probSum[i] >= 1) {
                        probSum[i]--;
                    }
                }
            }
        }
        output();
    }
    void hilbertMCode() {
        std::cout << "Hilbert M code" << std::endl;
        quickSortH(0, m_probabilities.size() - 1);
        if (!m_probabilities.empty()) {
            m_matrix.clear();
            double pr = 0;
            std::vector<int> length(m_probabilities.size());
            std::vector<double> probSum(m_probabilities.size());
            m_matrix.resize(m_probabilities.size());
            for (int i = 0; i < m_probabilities.size(); ++i) {
                probSum[i] = pr + m_probabilities[i] / 2;
                pr += m_probabilities[i];
                length[i] = -(int) log2(m_probabilities[i]) + 1;
            }
            for (int i = 0; i < m_probabilities.size(); ++i) {
                m_matrix[i].resize(length[i]);
                for (int j = 0; j < length[i]; ++j) {
                    probSum[i] *= 2;
                    m_matrix[i][j] = probSum[i];
                    if (probSum[i] >= 1) probSum[i]--;
                }
            }
        }
        output();
    }
    ~EncodingTools() {
        m_probabilities.clear();
        m_data.clear();
        m_matrix.clear();
    }
};

class Interface : public EncodingTools {
public:
    void menu(char *path) {
        readfile(path);
        shannonCode();
        std::cout << std::endl;
        hilbertMCode();
        std::cout << std::endl;
    }
};