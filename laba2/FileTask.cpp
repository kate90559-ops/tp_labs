#include "FileTask.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

void processFileSwapWords(const std::string& inputFilename) {
    std::ifstream inFile(inputFilename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Error: Could not open file for reading!");
    }

    std::cout << "\n--- Task 2: Swapping Adjacent Words in File ---\n";
    std::string line;
    
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        // Используем временный динамический массив или вектор для слов строки
        std::vector<std::string> words; // Вспомогательный инструмент для строки
        std::string word;

        while (ss >> word) {
            words.push_back(word);
        }

        // Меняем местами соседние слова (0 и 1, 2 и 3 и т.д.)
        for (size_t i = 0; i + 1 < words.size(); i += 2) {
            std::swap(words[i], words[i + 1]);
        }

        // Вывод измененной строки
        for (size_t i = 0; i < words.size(); ++i) {
            std::cout << words[i] << (i + 1 < words.size() ? " " : "");
        }
        std::cout << "\n";
    }

    inFile.close();
}