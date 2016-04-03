#include <iostream>
#include "huffmannode.h"
#include "console.h"
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string.h>

using namespace std;

/* Function prototypes */
static void printHelp();
void codeHuffman(string sourceFileName, string archiveFileName);
void decodeHuffman(string archiveFileName, string outputFileName);
void buildHuffmanTree(HuffmanNode *root1);

/* Global variables */
vector<bool> symbolCode;                // vector of "0" and "1" for getWeight() function
map<char, vector<bool> > table;         // association table for symbols and codes
HuffmanNode *root;                      // pointer to the root of the binary tree
char sourceFileName[50] = "";
char archiveFileName[50] = ".huff";
char outputFileName[50] = "decompressed-";

int main ()
{
    char operation;
    printHelp();
    while (true){
        cout << endl << "Enter the operation: ";
        cin >> operation;
        if(operation == 'q' || operation == 'Q'){
            cout << "Goodbye. Pres Alt+F4 to close the window.";
            exit(EXIT_SUCCESS);
        }else if (operation == 'c' || operation == 'C'){
            cout << "Enter file name: ";
            cin >> sourceFileName;
            strcpy(archiveFileName, sourceFileName);
            strcat(archiveFileName, ".huff");
            codeHuffman(sourceFileName, archiveFileName);
            cout << "\nArchivation completed. \nThe name of the file after archiving: " << archiveFileName << endl;
        }else if(operation == 'd' || operation == 'D'){
            strcat(outputFileName, sourceFileName);
            decodeHuffman(archiveFileName, outputFileName);
            cout << "\nDearchivation completed. \nThe name of the file after dearchivation: " << outputFileName << endl;
        }else{
            cout << "\nYou made a mistake. Please try again." << endl;
        }
    }
    return 0;
}


/**
 * Function: printHelp
 * Usage: printHelp()
 * ----------------------------------------------------------------
 * The function prints the prompt to use the archiver
 */
static void printHelp()
{
    cout << "This is a simple archive program, that using Huffman's algorithm for coding files." << endl << endl;
    cout << "Select the operation:" << endl;
    cout << "C - to compress the file" << endl;
    cout << "D - to decompress the file" << endl;
    cout << "Q - to exit \n";
}



/**
 * Function: buildHuffmanTree
 * Usage: buildHuffmanTree(HuffmanNode *root1)
 * ---------------------------------------------------------------------
 * The function creates a table of frequencies of occurrences of symbols
 */
void buildHuffmanTree(HuffmanNode *root1)
{
    if (root1->leftPTR != NULL){
        symbolCode.push_back(0);
        buildHuffmanTree(root1->leftPTR);
    }
    if (root1->rightPTR != NULL){
        symbolCode.push_back(1);
        buildHuffmanTree(root1->rightPTR);
    }
    if(root1->leftPTR == NULL && root1->rightPTR == NULL){
        table[root1->symbol] = symbolCode;
    }
        symbolCode.pop_back();
}


/**
 * Fumction: codeHuffman
 * Usage: codeHuffman(string sourceFileName, string archiveFileName)
 * @param sourceFileName - the name of the file which you want to archive
 * @param archiveFileName - the name of the archived file
 * ----------------------------------------------------------------------
 * Function compresses the file
 */
void codeHuffman(string sourceFileName, string archiveFileName)
{

    ifstream sourceFile(sourceFileName, ios::in | ios::binary);

    map <char, int> symbolCount;            // for counting symbols in source file

    while(!sourceFile.eof()){
        char c = sourceFile.get();
        symbolCount[c]++;
    }

    list <HuffmanNode*> nodePointers;

    map <char,int>::iterator iter;
    for (iter = symbolCount.begin(); iter != symbolCount.end(); ++iter){
        HuffmanNode *p = new HuffmanNode;
        p->symbol = iter->first;
        p->count = iter->second;
        nodePointers.push_back(p);
    }

    while (nodePointers.size()!=1){
        nodePointers.sort(comparison());

        HuffmanNode *leftSon = nodePointers.front();
        nodePointers.pop_front();
        HuffmanNode *rightSon = nodePointers.front();
        nodePointers.pop_front();

        HuffmanNode *parent = new HuffmanNode(leftSon, rightSon);
        nodePointers.push_back(parent);
    }

    root = nodePointers.front();

    buildHuffmanTree(root);

    sourceFile.clear();
    sourceFile.seekg(0);

    ofstream archiveFile(archiveFileName, ios::out | ios::binary);
    int counter = 0;
    char buffer = 0;
    while(!sourceFile.eof()){
        char c = sourceFile.get();
        vector<bool> x = table[c];
        for (int i = 0; i < x.size(); i++){
            buffer = buffer | x[i] << (7-counter);  // bitwise shift
            counter++;
            if(counter == 8){
                counter = 0;
                archiveFile << buffer;
                buffer = 0;
            }
        }
    }

    sourceFile.close();
    archiveFile.close();

}


/**
 * Function: decodeHuffman
 * Usage: decodeHuffman(string archiveFileName, string outputFileName)
 * @param archiveFileName - the name of the source archived file
 * @param outputFileName - the name of the decompressd file
 * --------------------------------------------------------------------
 * Function decompressed file
 */
void decodeHuffman(string archiveFileName, string outputFileName)
{

    ifstream compressedFile(archiveFileName, ios::in | ios::binary);
    ofstream decompressedFile(outputFileName, ios::out | ios::binary);
    HuffmanNode *p = root;
    int counter = 0;
    char byte;
    byte = compressedFile.get();
    while(!compressedFile.eof()){
        bool b = byte & (1 << (7-counter));     // bitwise shift
        if (b)
            p = p->rightPTR;
        else p = p->leftPTR;

        if(p->leftPTR == NULL && p->rightPTR == NULL){
            decompressedFile<<(p->symbol);
            p = root;
        }
        counter++;
        if (counter == 8){
            counter = 0;
            byte = compressedFile.get();
        }
    }

    compressedFile.close();
    decompressedFile.close();

}
