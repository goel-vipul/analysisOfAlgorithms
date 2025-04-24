#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cmath>

using namespace std;

// Combine all words from both input files and save only the distinct ones separately
void combineWordsAndExtractUniques(const string& input1, const string& input2, const string& combinedFile, const string& uniqueFile) {
    ifstream fileOne(input1);
    ifstream fileTwo(input2);
    ofstream mergedOutput(combinedFile);
    ofstream distinctOutput(uniqueFile);

    if (!fileOne || !fileTwo || !mergedOutput || !distinctOutput) {
        cerr << "Couldn't open one or more files." << endl;
        return;
    }

    unordered_set<string> uniqueWordsSet;
    string tempWord;

    while (fileOne >> tempWord) {
        mergedOutput << tempWord << " ";
        uniqueWordsSet.insert(tempWord);
    }

    while (fileTwo >> tempWord) {
        mergedOutput << tempWord << " ";
        uniqueWordsSet.insert(tempWord);
    }

    for (const string& word : uniqueWordsSet) {
        distinctOutput << word << "\n";
    }

    cout << "Words merged and saved to: " << combinedFile << endl;
    cout << "Distinct words saved to: " << uniqueFile << endl;
}

// Count total number of words in a given file
int countWords(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        return -1;
    }

    string word;
    int count = 0;
    while (file >> word) {
        count++;
    }

    return count;
}

// Read all words from a file into a list
void loadWordsToList(const string& file, vector<string>& wordList) {
    ifstream input(file);
    if (!input) {
        cerr << "Cannot access file: " << file << endl;
        return;
    }

    string word;
    while (input >> word) {
        wordList.push_back(word);
    }
}

// Count how many times each unique word appears in a word list
void countWordOccurrences(vector<int>& freqList, const vector<string>& allWords, const vector<string>& uniqueWords) {
    for (const string& unique : uniqueWords) {
        int count = 0;
        for (const string& word : allWords) {
            if (word == unique) {
                count++;
            }
        }
        freqList.push_back(count);
    }
}

// Display frequency array
void printFrequencies(const vector<int>& freqList) {
    cout << "[";
    for (int i = 0; i < freqList.size(); i++) {
        cout << freqList[i];
        if (i < freqList.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Print out all words in a list
void showWords(const vector<string>& wordList) {
    cout << "[";
    for (int i = 0; i < wordList.size(); i++) {
        cout << wordList[i];
        if (i < wordList.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Use cosine similarity to compare how similar two word distributions are
void calculateCosineSimilarity(const vector<int>& freqA, const vector<int>& freqB) {
    float dot = 0, magnitudeA = 0, magnitudeB = 0;

    for (int i = 0; i < freqA.size(); i++) {
        dot += freqA[i] * freqB[i];
        magnitudeA += freqA[i] * freqA[i];
        magnitudeB += freqB[i] * freqB[i];
    }

    magnitudeA = sqrt(magnitudeA);
    magnitudeB = sqrt(magnitudeB);

    float similarity = dot / (magnitudeA * magnitudeB);
    cout << "Cosine Similarity: " << similarity << endl;
    cout << similarity * 100 << "% similar" << endl;
}

int main() {
    // Paths to the files
    string pathToFile1 = "C:\\Users\\priya\\OneDrive\\Documents\\file1.txt";
    string pathToFile2 = "C:\\Users\\priya\\OneDrive\\Documents\\file2.txt";
    string mergedPath = "C:\\Users\\priya\\OneDrive\\Documents\\merged.txt";
    string uniquePath = "C:\\Users\\priya\\OneDrive\\Documents\\unique.txt";

    // Combine and filter unique words
    combineWordsAndExtractUniques(pathToFile1, pathToFile2, mergedPath, uniquePath);

    // Word counts
    int wordCount1 = countWords(pathToFile1);
    int wordCount2 = countWords(pathToFile2);
    int uniqueCount = countWords(uniquePath);

    cout << "Words in File 1: " << wordCount1 << endl;
    cout << "Words in File 2: " << wordCount2 << endl;
    cout << "Unique Words: " << uniqueCount << endl;

    // Store words from files into vectors
    vector<string> wordsFromFile1, wordsFromFile2, allUniqueWords;

    loadWordsToList(pathToFile1, wordsFromFile1);
    loadWordsToList(pathToFile2, wordsFromFile2);
    loadWordsToList(uniquePath, allUniqueWords);

    // Display content
    cout << "File 1 Words: ";
    showWords(wordsFromFile1);

    cout << "File 2 Words: ";
    showWords(wordsFromFile2);

    cout << "Distinct Words: ";
    showWords(allUniqueWords);

    // Frequency analysis
    vector<int> freqVector1, freqVector2;
    countWordOccurrences(freqVector1, wordsFromFile1, allUniqueWords);
    countWordOccurrences(freqVector2, wordsFromFile2, allUniqueWords);

    cout << "Frequency in File 1: ";
    printFrequencies(freqVector1);

    cout << "Frequency in File 2: ";
    printFrequencies(freqVector2);

    // Similarity check
    calculateCosineSimilarity(freqVector1, freqVector2);

    return 0;
}
