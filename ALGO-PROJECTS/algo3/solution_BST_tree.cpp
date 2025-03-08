// EMRE YAMAÇ 150210077

#include <iostream>              
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <chrono>
#include <string>
#include <random>

using namespace std;
using namespace std::chrono;

/////////////////// Player ///////////////////
class publisher
{
public:
	string name;
	float na_sales;
	float eu_sales;
	float others_sales;
};

/////////////////// Node ///////////////////
class Node{
	public:
		publisher key;
		int color; // "Red"=1 or "Black"=0
		Node *parent, *left, *right;
	
		Node(publisher);
		~Node();
		int get_color();
        void set_color(int);
};

/////////////////// BST-Tree ///////////////////
class BST_tree{
	private:
		Node* root;
        void preorder_print(int, Node*);
	public:	
        publisher* best_seller[3];	
		stack<string> tree_deep_stack;

        Node* get_root();

		Node* BST_insert(Node* root, Node* ptr);
		void insertValue(vector<string>);
        void find_best_seller(); 
        Node* search(string);
        vector<string> publisher_vector();
        void preorder();

        BST_tree();
		~BST_tree();
};

void print_best_sellers(int year, publisher* temp_publisher[3]){
    cout.precision(5);
    cout<< "End of the "+to_string(year)+" Year"<<endl;
    cout<< "Best seller in North America: "+temp_publisher[0]->name+" - "<<temp_publisher[0]->na_sales<<" million"<<endl;
    cout<< "Best seller in Europe: "+temp_publisher[1]->name+" - "<<temp_publisher[1]->eu_sales<<" million"<<endl;
    cout<< "Best seller rest of the World: "+temp_publisher[2]->name+" - "<<temp_publisher[2]->others_sales<<" million"<<endl;
}

BST_tree generate_BST_tree_from_csv(string file_name) {
    BST_tree temp_BSTtree;
    ifstream file(file_name);

    string line;
    getline(file, line); 

    int decade = 1980; 
    int year;
    auto total_insertion_timing = 0;

     while (getline(file, line)){
		int pos = 0;
		vector<string> input_line;

		for (size_t i = 0; i < 6; i++){
			pos = line.find(',');
			input_line.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		input_line.push_back(line);
	
	
        year = stoi(input_line[2]);
        

        if (year > decade + 10) {
            decade += 10;
            temp_BSTtree.find_best_seller();
            print_best_sellers(decade, temp_BSTtree.best_seller);
        }
        auto start_insertion_timing = high_resolution_clock::now();
        temp_BSTtree.insertValue(input_line);
        auto end_insertion_timing = high_resolution_clock::now();
        auto timing_insertion = duration_cast<microseconds>(end_insertion_timing - start_insertion_timing);
        
        total_insertion_timing += timing_insertion.count();
    }
    
    temp_BSTtree.find_best_seller();
	print_best_sellers(year, temp_BSTtree.best_seller);
    cout << "Time taken to insert all data into BST: " << total_insertion_timing << " µs" << endl;

    file.close();
    return temp_BSTtree;    
}   

////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char* argv[]){

	string fname = argv[1];    
    BST_tree BSTtree = generate_BST_tree_from_csv(fname);

        cout << endl;

    auto publishers = BSTtree.publisher_vector();
    auto total_search_time = 0.0;

    
    BSTtree.preorder();   // IMPORTANT ! = PDF DIDNT WANT BST PREORDER BUT I IMPLEMENTED FOR REPORT. U CAN TRY DELETING COMMENT LINES
    

    random_device rand_dev;
    mt19937 gen(rand_dev());
    uniform_int_distribution<> dis(0, publishers.size() - 1);
   
    for (int i = 0; i < 50; i++) {
        int index = dis(gen);
        string publisher = publishers[index];

        auto start_publisher_vector_timing = high_resolution_clock::now(); 
        BSTtree.search(publisher);
        auto end_publisher_vector_timing = high_resolution_clock::now(); 

        auto publisher_vector_timing = duration_cast<nanoseconds>(end_publisher_vector_timing - start_publisher_vector_timing);
        total_search_time += publisher_vector_timing.count();
    }

    double average_publisher_vector_timing = (total_search_time) / 50.0;

    cout << "Average time for 50 random searches: " << average_publisher_vector_timing << " ns" << endl;  // IMPORTANT! = IN MY COMPUTER AVERAGE TIMING IS SEEN AS 0 NANOSECONDS 
                                                                                                          // I DONT KNOW BUT I TRIED MY FRIEND FILE THAT WORKS ON HIS COMPUTER 
    return EXIT_SUCCESS;                                                                                  // STILL I SEE 0 NANOSECONDS MAYBE PROBLEM CAN BE IN MY COMPUTER
    
}


/////////////////// Node ///////////////////

Node::Node(publisher key){
	this->key = key;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}


Node* BST_tree::get_root(){

    // Fill this function.

    return this->root;
}

Node* BST_tree::BST_insert(Node* root, Node* ptr) {
    if (!root) {
        return ptr; 
    }
    else if (ptr->key.name == root->key.name)
    {
        root->key.eu_sales += ptr->key.eu_sales;
        root->key.na_sales += ptr->key.na_sales;
        root->key.others_sales += ptr->key.others_sales;

    }
    
    else if (ptr->key.name < root->key.name) {
        root->left = BST_insert(root->left, ptr);
        root->left->parent = root;
    } else {
        root->right = BST_insert(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void BST_tree::insertValue(vector<string> n) {
    publisher pub;
    pub.name = n[3];
    pub.na_sales = stof(n[4]);
    pub.eu_sales = stof(n[5]);
    pub.others_sales = stof(n[6]);

    Node* newNode = new Node(pub);

    if (!root) {
        root = newNode;
    } else {
        BST_insert(root, newNode);
    }
}


void BST_tree::find_best_seller(){

     if (!root) return;

    stack<Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node* current = nodeStack.top();
        nodeStack.pop();

        if (!best_seller[0] || current->key.na_sales > best_seller[0]->na_sales) {
            best_seller[0] = &current->key;
        }
        if (!best_seller[1] || current->key.eu_sales > best_seller[1]->eu_sales) {
            best_seller[1] = &current->key;
        }
        if (!best_seller[2] || current->key.others_sales > best_seller[2]->others_sales) {
            best_seller[2] = &current->key;
        }

        if (current->left) nodeStack.push(current->left);
        if (current->right) nodeStack.push(current->right);
    }

}


BST_tree::BST_tree(){
	this->root = NULL;
    this->best_seller[0] = NULL;
    this->best_seller[1] = NULL;
    this->best_seller[2] = NULL;
}

BST_tree::~BST_tree(){
}

Node* BST_tree::search(string name) {
    Node* current = root;
    
    while (current) {
        if (current->key.name == name) {
            return current; 
        } else if (name < current->key.name) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current; 
}

vector<string> BST_tree::publisher_vector() {

    vector<string> nodes;
    stack<Node*> stack;
    stack.push(root);

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();
        nodes.push_back(current->key.name);

        if (current->left) stack.push(current->left);
        if (current->right) stack.push(current->right);
    }
    return nodes;
}   

void BST_tree::preorder(){
    if (!root) return;
    preorder_print(0 , root);
};
void BST_tree::preorder_print(int depth , Node* node){
    if(!node) return;
    for(int i  = 0; i < depth; i++){
    cout << "-";
    }

    cout << " " << node->key.name << endl;

    preorder_print(depth+1 , node->left);
    preorder_print(depth+1 ,node->right);
    

}