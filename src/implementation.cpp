#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;



// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    MetroStop *temp = this->getNode();
    int stops = 0;
    while(temp){
        stops++;
        temp = temp->getNextStop();
    }
    return stops;
}

void MetroLine::populateLine(std::string filename) {
    ifstream file(filename);
    string line;
    MetroStop *prev = NULL;
    while(!file.eof()){
        getline(file, line);
        string num = "", name = "";
        int n = line.size()-1, i = 0;
        while(line[n] != ' '){
            num += line[n--];
        }
        reverse(num.begin(), num.end());
        int fare = stoi(num);
        while(i != n){
            name += line[i++];
        }
        MetroStop *m = new MetroStop(name, this, fare); 
        if(!this->getNode()){
            this->setNode(m);
            prev = m;
        }
        else{
            m->setPrevStop(prev);
            prev->setNextStop(m);
            prev = m;
        }
    }
    // Read the file and populate the line
}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}


// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if(node == NULL){
        return 0;
    }
    int left = height(node->getLeft());
    int right = height(node->getRight());
    return max(left, right)+1;
}

int AVLTree::stringCompare(string s1, string s2) {
    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    if(node == NULL){
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}

void AVLTree::rotateLeft(AVLNode* node) 
{
    AVLNode *x = node->getRight();
    AVLNode *y = x->getLeft();
    if(node == this->getRoot())
    {
        this->setRoot(x);
    }
    if(y){
        y->setParent(node);
    }
    x->setParent(node->getParent());
    node->setParent(x);
    x->setLeft(node);
    node->setRight(y);
    if(x != this->getRoot()){
        if(x->getParent()->getLeft() == node)
        {
            x->getParent()->setLeft(x); 
        }
        else{
            x->getParent()->setRight(x);
        }
    }
}

void AVLTree::rotateRight(AVLNode* node) {
    AVLNode *x = node->getLeft();
    AVLNode *y = x->getRight();
    if(node == this->getRoot()){
        this->setRoot(x);
    }
    if(y){
        y->setParent(node);
    }
    x->setParent(node->getParent());
    node->setParent(x);
    x->setRight(node);
    node->setLeft(y);
    if(x != this->getRoot()){
        if(x->getParent()->getLeft() == node){
            x->getParent()->setLeft(x);
        }
        else{
            x->getParent()->setRight(x);
        }
    }
}

void AVLTree::balance(AVLNode* node) {
}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
    AVLNode *temp = node;
    AVLNode *prev = NULL;
    while(temp){
        int res = stringCompare(metroStop->getStopName(), temp->getStopName());
        if(res<0){
            prev = temp;
            temp = temp->getLeft();
        }
        else if(res>0){
            prev = temp;
            temp = temp->getRight();
        }
        else if(res == 0)
        {
            temp->addMetroStop(metroStop);
            return;
        }
    }
    int res = stringCompare(metroStop->getStopName(), prev->getStopName());
    if(res<0){
        AVLNode *newNode = new AVLNode(metroStop->getStopName());
        prev->setLeft(newNode);
        newNode->setParent(prev);
        newNode->addMetroStop(metroStop);
    }
    else if(res>0){
        AVLNode *newNode = new AVLNode(metroStop->getStopName());
        prev->setRight(newNode);
        newNode->setParent(prev);
        newNode->addMetroStop(metroStop);
    }
    AVLNode *temp1 = prev;
    while(temp1)
    {
        int balance = balanceFactor(temp1);
        AVLNode* par = temp1->getParent();
        if(balance > 1 && stringCompare(metroStop->getStopName(), temp1->getLeft()->getStopName()) < 0){
            rotateRight(temp1);  
        }
        else if(balance < -1 && stringCompare(metroStop->getStopName(), temp1->getRight()->getStopName()) > 0){
            rotateLeft(temp1);
        }
        else if(balance > 1 && stringCompare(metroStop->getStopName(), temp1->getLeft()->getStopName()) > 0){
            rotateLeft(temp1->getLeft());
            rotateRight(temp1);
        }
        else if(balance < -1 && stringCompare(metroStop->getStopName(), temp1->getRight()->getStopName()) < 0){
            rotateRight(temp1->getRight());
            rotateLeft(temp1);
        }
        temp1 = par;
    }
}

void AVLTree::populateTree(MetroLine* metroLine) {
    if(!this->getRoot()){
        this->setRoot(new AVLNode(metroLine->getNode()->getStopName()));
    }
    MetroStop *temp = metroLine->getNode();
    while(temp){
        insert(this->getRoot(), temp);
        temp = temp->getNextStop();
    }

}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode *temp = this->getRoot();
    while(temp){
        if(temp->getStopName() == stopName){
            return temp;
        }
        else if(stringCompare(stopName, temp->getStopName()) < 0){
            temp = temp->getLeft();
        }
        else if(stringCompare(stopName, temp->getStopName()) > 0){
            temp = temp->getRight();
        }
    }
    return NULL;
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    if(trip != nullptr)
    {
        cout << "Dequeued: " << trip->getNode()->getStopName() << "\n";
    }
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() 
{
    tree->setRoot(NULL);
    for(int i=0; i<lines.size(); i++){
        tree->populateTree(lines[i]);
    }
}

Path* PathFinder::findPath(std::string origin, std::string destination) 
{
    AVLNode *node = tree->searchStop(origin);
    AVLNode *dest = tree->searchStop(destination);
    if(!node || !dest){
        return NULL;
    }
    Exploration *exp = new Exploration();
    vector<Path*> ans;
    vector<MetroLine*> visited;
    vector<MetroStop*> ms = node->getStops();
    for(int i=0; i<ms.size(); i++)
    {
        Trip *t1 = new Trip(ms[i], NULL);
        Trip *t2 = new Trip(ms[i], NULL);
        exp->enqueue(t1);
        exp->enqueue(t2);
    }

    MetroLine *containsdest = NULL;
    while(!exp->isEmpty())
    {
        Trip *tn = exp->dequeue();
        Trip *temp = tn;
       
        while(temp != NULL && temp->getNode())
        {
            
            if(temp->getNode()->getStopName() == destination)
            {
                if(containsdest == NULL)containsdest = temp->getNode()->getLine();
                Path *p = new Path();
                int fare = 0;
                Trip *temp1 = temp;
                while(temp1->getNode()->getStopName() != origin)
                {
                    if((tree->searchStop(temp1->getPrev()->getNode()->getStopName())->getStops()).size() >1){
                        if(temp1->getNode()->getPrevStop()->getStopName() == temp1->getPrev()->getNode()->getStopName()){
                            fare += abs(temp1->getNode()->getFare() - temp1->getNode()->getPrevStop()->getFare());
                        }
                        else{
                            fare += abs(temp1->getNode()->getFare() - temp1->getNode()->getNextStop()->getFare());
                        }
                    }
                    else{
                        fare += abs(temp1->getNode()->getFare() - temp1->getPrev()->getNode()->getFare());
                    }
                    p->addStop(temp1->getNode());
                    temp1 = temp1->getPrev();
                }
                p->addStop(temp1->getNode());
                p->setTotalFare(fare);
                ans.push_back(p);
                break;
            }
            vector<MetroStop*> stops = tree->searchStop(temp->getNode()->getStopName())->getStops();
            if(stops.size() > 1)
            {
                for(int j=0; j<stops.size(); j++){
                    bool flag = false;
                    for(int k=0; k<visited.size(); k++){
                        if(visited[k] == stops[j]->getLine()){
                            flag = true;
                        }
                    }
                    if(!flag)
                    {
                        if(stops[j] != temp->getNode() && stops[j]->getNextStop() != NULL && stops[j]->getPrevStop() != NULL){
                            Trip *t1 = new Trip(stops[j]->getNextStop() , temp);
                            Trip *t2 = new Trip(stops[j]->getPrevStop() , temp);
                            exp->enqueue(t1);
                            exp->enqueue(t2);
                        }
                    }
                }
            }

            MetroStop *m = temp->getNode()->getNextStop();
            Trip *trip1 = new Trip(m, temp);
            temp = trip1;
        }
        Trip *tp = exp->dequeue();
        Trip *temp2 = tp;


        while(temp2 != NULL && temp2->getNode())
        {

            if(temp2->getNode()->getStopName() == destination){
                if(containsdest == NULL)containsdest = temp2->getNode()->getLine();
                Path *p = new Path();
                int fare = 0;
                Trip *temp1 = temp2;
                while(temp1->getNode()->getStopName() != origin){
                    if((tree->searchStop(temp1->getPrev()->getNode()->getStopName())->getStops()).size() >1){
                        if(temp1->getNode()->getPrevStop()->getStopName() == temp1->getPrev()->getNode()->getStopName()){
                            fare += abs(temp1->getNode()->getFare() - temp1->getNode()->getPrevStop()->getFare());
                        }
                        else{
                            fare += abs(temp1->getNode()->getFare() - temp1->getNode()->getNextStop()->getFare());
                        }
                    }
                    else{
                        fare += abs(temp1->getNode()->getFare() - temp1->getPrev()->getNode()->getFare());
                    }
                    p->addStop(temp1->getNode());
                    temp1 = temp1->getPrev();
                }
                p->addStop(temp1->getNode());
                p->setTotalFare(fare);
                ans.push_back(p);
                break;
            }
            vector<MetroStop*> stops = tree->searchStop(temp2->getNode()->getStopName())->getStops();
            if(stops.size() > 1){
                for(int j=0; j<stops.size(); j++){
                    bool flag = false;
                    for(int k=0; k<visited.size(); k++){
                        if(visited[k] == stops[j]->getLine()){
                            flag = true;
                        }
                    }
                    if(!flag)
                    {   
                        if(stops[j] != temp2->getNode() && stops[j]->getNextStop() != NULL && stops[j]->getPrevStop() != NULL)
                        {
                            Trip *t1 = new Trip(stops[j]->getNextStop() , temp2);
                            Trip *t2 = new Trip(stops[j]->getPrevStop() , temp2);
                            exp->enqueue(t1);
                            exp->enqueue(t2);
                        }
                    }
                }
            }
            MetroStop *m = temp2->getNode()->getPrevStop();
            Trip *trip1 = new Trip(m, temp2);
            temp2 = trip1;
        }
        MetroLine* line = NULL;
        if(tn != NULL) line = tn->getNode()->getLine();
        if(tp != NULL) line = tp->getNode()->getLine();

        if(containsdest != line){
            visited.push_back(line);
        }

    }

    Path *finalans = NULL;
    int size = 0;
    if(ans.size() >= 1)
    {
        finalans = ans[0];
        size = ans[0]->getStops().size();
    }
    for(int n=1; n<ans.size(); n++)
    {
        if(ans[n]->getStops().size() < size){
            finalans = ans[n];
            size = ans[n]->getStops().size();
        }
    }
    return finalans;
}
vector<MetroLine*> lines;