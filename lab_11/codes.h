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
    std::vector<int> length;
    std::vector<double> probSum;
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
    // general methods
    void clearMatrix() {
        m_matrix.clear();
        m_matrix.resize(m_probabilities.size());
    }
    int getProbabilitySize() {
        return m_probabilities.size();
    }
    void calcLength() {
        double pr = 0;
        length.resize(m_probabilities.size());
        probSum.resize(m_probabilities.size());
        for (int i = 0; i < m_probabilities.size(); ++i) {
            probSum[i] = pr + m_probabilities[i] / 2;
            pr += m_probabilities[i];
            length[i] = -(int) log2(m_probabilities[i]) + 1;
        }
    }
    void output() {
        double averageLen = 0;
        double entropy = 0;
        for (int i = 0; i < m_matrix.size(); ++i) {
            averageLen += m_matrix[i].size() * m_probabilities[i];
            entropy -= m_probabilities[i] * log2(m_probabilities[i]);
            std::cout.width(10);
            std::cout << " " << m_data[i] << "    ";
            std::cout.precision(5);
            std::cout << m_probabilities[i] << "    ";
            for (auto &j : m_matrix[i]) {
                std::cout << j;
            }
            std::cout << "   ";
            std::cout << m_matrix[i].size() << std::endl;
        }
        std::cout << "Average code length: " << averageLen << std::endl;
        std::cout << "Entropy: " << entropy << std::endl;
    }
    // for huffman
    std::vector<double> probabilitiesTmp;
    int up(int n, double q) {
        int j;
        for (int i = n - 1; i >= 0; i--) {
            if (i > 0 && probabilitiesTmp[i - 1] < q) {
                probabilitiesTmp[i] = probabilitiesTmp[i - 1];
                j = i;
            } else {
                j = i;
                break;
            }
        }
        probabilitiesTmp[j] = q;
        return j;
    }
    void down(int n, int j) {
        std::vector<int> s(m_matrix[j].size());
        s = m_matrix[j];
        for (int i = j; i < n - 1; i++) {
            m_matrix[i] = m_matrix[i + 1];
        }
        m_matrix[n - 1] = s;
        m_matrix[n] = s;
        m_matrix[n - 1].push_back(0);
        m_matrix[n].push_back(1);
    }
    // for fano
    int calcMedian(int left, int right) {
        long double sumLeft = 0, sumRight = m_probabilities[right];
        unsigned long median;
        for (int i = left; i < right; ++i) {
            sumLeft += m_probabilities[i];
        }
        median = right;
        while (sumLeft >= sumRight) {
            --median;
            sumLeft -= m_probabilities[median];
            sumRight += m_probabilities[median];
        }
        return (int) median;
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
    // encode methods
    void shannonCode() {
        std::cout << "Shannon code" << std::endl;
        calcLength();
        m_matrix.clear();
        m_matrix.resize(m_probabilities.size());
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
        output();
    }
    void hilbertMCode() {
        std::cout << "Hilbert M code" << std::endl;
        calcLength();
        quickSortH(0, m_probabilities.size() - 1);
        m_matrix.clear();
        m_matrix.resize(m_probabilities.size());
        for (int i = 0; i < m_probabilities.size(); ++i) {
            m_matrix[i].resize(length[i]);
            for (int j = 0; j < length[i]; ++j) {
                probSum[i] *= 2;
                m_matrix[i][j] = probSum[i];
                if (probSum[i] >= 1) probSum[i]--;
            }
        }
        output();
    }
    void fanoCode(int left, int right) {
        if (left < right) {
            int median = calcMedian(left, right);
            for (int i = left; i <= right; ++i) {
                if (i <= median)
                    m_matrix[i].push_back(0);
                else
                    m_matrix[i].push_back(1);
            }
            fanoCode(left, median);
            fanoCode(median + 1, right);
        }
    }
    void huffmanCode(int n) {
        double q;
        int j;
        if (n == 1) {
            m_matrix[0].push_back(0);
            m_matrix[1].push_back(1);
        } else {
            q = probabilitiesTmp[n - 1] + probabilitiesTmp[n];
            j = up(n, q);
            huffmanCode(n - 1);
            down(n, j);
        }
    }
    // interface for encode
    void encodeFano() {
        std::cout << "Fano code" << std::endl;
        clearMatrix();
        quickSort(0, m_probabilities.size() - 1);
        fanoCode(0, getProbabilitySize() - 1);
        output();
    }
    void encodeHuffman() {
        std::cout << "Huffman code" << std::endl;
        clearMatrix();
        quickSort(0, m_probabilities.size() - 1);
        for (auto &i : m_probabilities) {
            probabilitiesTmp.push_back(i);
        }
        huffmanCode((int) m_probabilities.size() - 1);
        output();
    }
};

class Interface : public EncodingTools {
public:
    void menu(char *path) {
        readfile(path);
        encodeFano();
        std::cout << std::endl;
        encodeHuffman();
        std::cout << std::endl;
        shannonCode();
        std::cout << std::endl;
        hilbertMCode();
        std::cout << std::endl;
    }
};