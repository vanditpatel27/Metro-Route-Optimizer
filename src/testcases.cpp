#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <assert.h>
#include <exception>
#include "vatsalf.cpp"
using namespace std;

int marks = 0;

vector<string> getFileNames() {
    vector<string> filenames;
    filenames.push_back("blue.txt");
    filenames.push_back("green.txt");
    filenames.push_back("magenta.txt");
    filenames.push_back("orange.txt");
    filenames.push_back("red.txt");
    filenames.push_back("violet.txt");
    filenames.push_back("yellow.txt");
    return filenames;
}

void templatePopulateLine() {
    // cout<<"Testing populateLine()"<<endl;
    vector<string> filenames = getFileNames();
    int expectedTotalStops[] = {44, 21, 25, 6, 29,38, 62};
    for (int i = 0; i < filenames.size(); i++) {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine* metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
    }
}

void templatePopulateTree() {
    // cout<<"Testing populateTree()"<<endl;
    vector<string> filenames = getFileNames();
    AVLTree* tree = new AVLTree();
    tree->setRoot(nullptr);
    for (auto line : lines) {
        if (tree->getRoot() == nullptr) {
            tree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        tree->populateTree(line);
    }
    // cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    // cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
    // assert(tree->height(tree->getRoot()) == 9);
//     assert(tree->height(tree->getRoot()) == 22);
//     assert(tree->getTotalNodes(tree->getRoot()) == 211);
}

void testPopulateLine() {
    // cout<<"Testing populateLine()"<<endl;
    vector<string> filenames = getFileNames();
    int expectedTotalStops[] = {44, 21, 25, 6, 29,38, 62};
    int counter = 0;
    for (int i = 0; i < filenames.size(); i++) {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine* metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
        // cout << "Line name: " << metroLine->getLineName() << endl;
        // cout << "Total stops: " << metroLine->getTotalStops() << endl;
        // cout << endl;
        // assert(metroLine->getTotalStops() == expectedTotalStops[i]);
        if (metroLine->getTotalStops() == expectedTotalStops[i]) {
            counter++;
        }
        // metroLine->printLine();
    }
    if (counter == 7) {
        marks += 5;
    }
}

void testPopulateTree() {
    // cout<<"Testing populateTree()"<<endl;
    vector<string> filenames = getFileNames();
    AVLTree* tree = new AVLTree();
    tree->setRoot(nullptr);
    for (auto line : lines) {
        if (tree->getRoot() == nullptr) {
            tree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        tree->populateTree(line);
    }
    // cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    // cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
    if (tree->height(tree->getRoot()) == 9 && tree->getTotalNodes(tree->getRoot()) == 211) {
        marks += 3;
    }
}

vector<pair<string, string>> getExpectedPathPairs() {
    vector<pair<string, string>> expectedPathPairs;
    expectedPathPairs.push_back(make_pair("Pitampura", "Pul Bangash"));
    expectedPathPairs.push_back(make_pair("Brigadier Hoshiar Singh", "Inderlok"));

    return expectedPathPairs;
}

map<int, vector<string>> expectedPathMapping() {
    map<int, vector<string>> m;
    m[0] = vector<string> {"Pul Bangash", "Pratap Nagar", "Shastri Nagar", "Inder Lok", "Kanhaiya Nagar", "Keshav Puram", "Netaji Subhash Place", "Kohat Enclave", "Pitampura"};
    m[1] = vector<string> {"Inderlok", "Ashok Park Main", "Punjabi Bagh", "Shivaji Park", "Madi Pur", "Paschim Vihar East", "Paschim Vihar West", "Peera Garhi", "Udyog Nagar", "Surajmal Stadium", "Nangloi", "Nangloi Railway Station", "Rajdhani Park", "Mundka", "Mundka Industrial Area", "Ghevra Metro Station", "Tikri Kalan", "Tikri Border", "Pandit Shree Ram Sharma", "Bahadurgarh City", "Brigadier Hoshiar Singh"};

    return m;
}

void testFindPath() {
    PathFinder* pathFinder = new PathFinder(new AVLTree(), lines);
    pathFinder->createAVLTree();
    int counter = 0;
    vector<pair<string, string>> expectedPathPairs = getExpectedPathPairs();
    for (int i = 0; i < expectedPathPairs.size(); i++) {
        Path* path = pathFinder->findPath(expectedPathPairs[i].first, expectedPathPairs[i].second);
        if (path != nullptr) {
            marks += 1;
        } else {
            break;
        }
        // cout << "Total fare: " << path->getTotalFare() << endl;
        // path->printPath();
        vector<string> expectedPath = expectedPathMapping()[i];
        for (int j = 0; j < expectedPath.size(); j++) {
            // assert(path->getStops()[j]->getStopName() == expectedPath[j]);
            if (path->getStops()[j]->getStopName() == expectedPath[j]) {
                counter++;
            }
        }
    }
    if (counter == 27) {
        marks += 1;
    }
}

void test1() {
    testPopulateLine();
}

void test2() {
    templatePopulateLine();
    testPopulateTree();
}

void test3() {
    templatePopulateLine();
    templatePopulateTree();
    testFindPath();
}




int main() {
    vector<void(*)()> tests;
    tests.push_back(&test1); // 5
    tests.push_back(&test2); // 3
    tests.push_back(&test3); // 2

    for (auto test : tests) {
        test();
    }

    cerr<<","<<marks<<endl;
    return 0;
}