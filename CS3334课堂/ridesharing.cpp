#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include "Minimum-Cost-Perfect-Matching-master/Matching.h"
#include <fstream>
#include "Minimum-Cost-Perfect-Matching-master/Graph.h"
#include <cstdlib>
#include <sstream>
using namespace std;

pair< Graph, vector<double> > CreateRandomGraph()
{
    //random seed
    int x;
    cin >> x;
    srand( x );

    //Please see Graph.h for a description of the interface
    int n = 50;

    Graph G(n);
    vector<double> cost;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(rand()%10 == 0)
            {
                G.AddEdge(i, j);
                cost.push_back(rand()%1000);
            }

    return make_pair(G, cost);
}

Graph ReadGraph(string filename)
{
    //Please see Graph.h for a description of the interface

    ifstream file;
    file.open(filename.c_str());

    string s;
    getline(file, s);
    stringstream ss(s);
    int n;
    ss >> n;
    getline(file, s);
    ss.str(s);
    ss.clear();
    int m;
    ss >> m;

    Graph G(n);
    for(int i = 0; i < m; i++)
    {
        getline(file, s);
        ss.str(s);
        ss.clear();
        int u, v;
        ss >> u >> v;

        G.AddEdge(u, v);
    }

    file.close();
    return G;
}

pair< Graph, vector<double> > ReadWeightedGraph(string filename)
{
    //Please see Graph.h for a description of the interface

    ifstream file;
    file.open(filename.c_str());

    string s;
    getline(file, s);
    stringstream ss(s);
    int n;
    ss >> n;
    getline(file, s);
    ss.str(s);
    ss.clear();
    int m;
    ss >> m;

    Graph G(n);
    vector<double> cost(m);
    for(int i = 0; i < m; i++)
    {
        getline(file, s);
        ss.str(s);
        ss.clear();
        int u, v;
        double c;
        ss >> u >> v >> c;

        G.AddEdge(u, v);
        cost[G.GetEdgeIndex(u, v)] = c;
    }

    file.close();
    return make_pair(G, cost);
}

void MinimumCostPerfectMatchingExample(string filename)
{
    Graph G;
    vector<double> cost;

    //Read the graph
    pair< Graph, vector<double> > p = ReadWeightedGraph(filename);
    //pair< Graph, vector<double> > p = CreateRandomGraph();
    G = p.first;
    cost = p.second;

    //Create a Matching instance passing the graph
    Matching M(G);

    //Pass the costs to solve the problem
    pair< list<int>, double > solution = M.SolveMinimumCostPerfectMatching(cost);

    list<int> matching = solution.first;
    double obj = solution.second;

    ofstream outfile("output.txt");

    cout << "Optimal matching cost: " << obj << endl;
    //outfile << "Optimal matching cost: " << obj << endl;
    cout << "Edges in the matching:" << endl;
    //outfile << "Edges in the matching:" << endl;
    for(list<int>::iterator it = matching.begin(); it != matching.end(); it++)
    {
        pair<int, int> e = G.GetEdge( *it );

        cout << e.first << " " << e.second << endl;
        outfile << e.first << " " << e.second << endl;
    }
    outfile.close();
}

void MaximumMatchingExample(string filename)
{
    Graph G = ReadGraph(filename);
    Matching M(G);

    list<int> matching;
    matching = M.SolveMaximumMatching();

    cout << "Number of edges in the maximum matching: " << matching.size() << endl;
    cout << "Edges in the matching:" << endl;
    for(list<int>::iterator it = matching.begin(); it != matching.end(); it++)
    {
        pair<int, int> e = G.GetEdge( *it );

        cout << e.first << " " << e.second << endl;
    }
}
using namespace std;
#include <fstream>
const double PI = 3.1415926535897932384626;
enum character{PASSENGER = 0,DRIVER};
class Pos_node {
public:
	Pos_node(double longt, double lat) {
		this->latitude = lat;
		this->longtitude = longt;
	}
	double longtitude;
	double latitude;
};
class Passenger {
public:
	Passenger(int start_pos_node_num, int termi_pos_node_num,int passenger_no) {
		this->start_pos_node_num = start_pos_node_num;
		this->termi_pos_node_num = termi_pos_node_num;
		this->passenger_no = passenger_no;
	}
	int start_pos_node_num;
	int termi_pos_node_num;
	int passenger_no;
};
class Driver {
public:
	Driver(int current_pos_node_num, int driver_no) {
		this->current_pos_node_num = current_pos_node_num;

		this->driver_no = driver_no;
	}
	int driver_no;
	int current_pos_node_num;
};
class MyGraph_node {
public:
	MyGraph_node() {};
	MyGraph_node(Passenger* p,int new_no) {
		this->origin = p;
		this->classification_of_source = PASSENGER;
		this->new_no = new_no;
	}
	void* origin;
	int classification_of_source;
	int new_no;
	double weight;
};
class MyGraph {
public:
	MyGraph() {}
	vector<MyGraph_node*> vertices;
	map<pair<int, int>, double> edges;
};
double distance(Pos_node* p1, Pos_node* p2) {
	return 6371.0*acos(sin(PI/ 2 - p1->latitude*PI/180)*sin(PI/2 - p2->latitude*PI/180)*
		cos(p1->longtitude * PI / 180 -p2->longtitude * PI / 180)+cos(PI/2-p1->latitude * PI / 180)*cos(PI/2-p2->latitude * PI / 180));
}
double first_stage_edge_weight(Passenger* p1, Passenger* p2,vector<Pos_node*>& pos_table) {
	int s1 = p1->start_pos_node_num - 1;
	int s2 = p2->start_pos_node_num - 1;
	int t1 = p1->termi_pos_node_num - 1;
	int t2 = p2->termi_pos_node_num - 1;
	vector<double> paths;
	paths.push_back(distance(pos_table[s1], pos_table[t1]) + distance(pos_table[t1], pos_table[s2]) + distance(pos_table[s2], pos_table[t2]));
	paths.push_back(distance(pos_table[s1], pos_table[s2]) + distance(pos_table[s2], pos_table[t1]) + distance(pos_table[t1], pos_table[t2]));
	paths.push_back(distance(pos_table[s1], pos_table[s2]) + distance(pos_table[s2], pos_table[t2]) + distance(pos_table[t2], pos_table[t1]));
	paths.push_back(distance(pos_table[s2], pos_table[t2]) + distance(pos_table[t2], pos_table[s1]) + distance(pos_table[s1], pos_table[t1]));
	paths.push_back(distance(pos_table[s2], pos_table[s1]) + distance(pos_table[s1], pos_table[t1]) + distance(pos_table[t1], pos_table[t2]));
	paths.push_back(distance(pos_table[s2], pos_table[s1]) + distance(pos_table[s1], pos_table[t2]) + distance(pos_table[t2], pos_table[t1]));
	return *min_element(paths.begin(), paths.end());
}
double first_stage_vertex_weight(Passenger* p, vector<Pos_node*>& pos_table) {
	return distance(pos_table[p->start_pos_node_num - 1], pos_table[p->termi_pos_node_num - 1]);
}
void read(string filename,vector<Pos_node*> &storage) {
	ifstream infile(filename);
	int pos_node_num;
	double lat;
	double longt;
	char comma;
	while (infile >> pos_node_num) {
		infile >> comma;
		infile >> lat;
		infile >> comma;
		infile >> longt;
		Pos_node* new_pos = new Pos_node(longt, lat);
		storage.push_back(new_pos);
	}
}
void read(string filename, vector<Passenger*>& storage) {
	ifstream infile(filename);
	int passenger_num;
	int start_pos_node_num;
	int termi_pos_node_num;
	char comma;
	while (infile >> passenger_num){
	    --passenger_num;
		infile >> comma;
		infile >> start_pos_node_num;
		infile >> comma;
		infile >> termi_pos_node_num;
		Passenger* new_passenger = new Passenger(start_pos_node_num, termi_pos_node_num,passenger_num);
		storage.push_back(new_passenger);
	}
}
void read(string filename, vector<Driver*>& storage) {
	ifstream infile(filename);
	int driver_num;
	int current_pos_node_num;
	char comma;
	while (infile >> driver_num) {
	    --driver_num;
		infile >> comma;
		infile >> current_pos_node_num;
		Driver* new_driver = new Driver(current_pos_node_num,driver_num);
		storage.push_back(new_driver);
	}
}
int main(int argc, char* argv[]) {
	vector<Pos_node*> pos_table;//node num counted from 1
	vector<Passenger*> orders;//orders counted from 0
	vector<Driver*> drivers;//drivers counted from 0
    read("../dataset_ridesharing/Nodes.csv",pos_table);
    read("../Minimum-Cost-Perfect-Matching-master/orderset_1.csv" , orders);
    read("../Minimum-Cost-Perfect-Matching-master/driverset_1.csv",drivers);
    int m = orders.size();
	int n = drivers.size();

	//part1
	MyGraph initial_graph;
	int num = 1;
	for (vector<Passenger*>::iterator it = orders.begin();it != orders.end();++it) {
		MyGraph_node* newnode = new MyGraph_node(*it, (*it)->passenger_no);
		newnode->weight = first_stage_vertex_weight(*it, pos_table);
		initial_graph.vertices.push_back(newnode);
	}
	for (vector<MyGraph_node*>::iterator it1 = initial_graph.vertices.begin();it1 != initial_graph.vertices.end();++it1) {//O(n^2)
		for (vector<MyGraph_node*>::iterator it2 = it1 + 1;it2 != initial_graph.vertices.end();++it2) {
			initial_graph.edges.insert(make_pair((make_pair((*it1)->new_no, (*it2)->new_no)),
				first_stage_edge_weight((Passenger*)((*it1)->origin), (Passenger*)((*it2)->origin), pos_table)));
		}
	}
	//part2
	/*class Complete_Graph {
	public:
	Complete_Graph() {}
	vector<MyGraph_node*> vertices;
	vector<pair<pair<int, int>, double> > edges;
};*/
	MyGraph graph2 = initial_graph;
	//for (int i = (m + 1) / 2;i != min(m,n)+1;++i) {
	int in_service = 7 * m / 10;
	int original_size = graph2.vertices.size();
	graph2.vertices.insert(graph2.vertices.end(), 2 * in_service - m, NULL);
    for (int j = 0;j!=original_size;++j){
        for(int k = 0;k!=graph2.vertices.size()-original_size;++k)
            graph2.edges.insert(make_pair(make_pair(j,original_size+k),graph2.vertices[j]->weight));
    }
    ofstream package_input("../myinput.txt");
    package_input<<graph2.vertices.size()<<"\n";
    package_input<<graph2.edges.size()<<"\n";
    for (map<pair<int,int>,double>::iterator it = graph2.edges.begin();it!=graph2.edges.end();++it){
        //cout << it->first.first<<" "<<it->first.second<<" "<<" "<<it->second<<"\n";
        package_input << it->first.first<<" "<<it->first.second<<" "<<" "<<it->second<<"\n";
    }
	//}
    //part3
    /*
    string filename = "";
    string algorithm = "";
    int i = 1;
    while(i < argc)
    {
        string a(argv[i]);
        if(a == "-f")
            filename = argv[++i];
        else if(a == "--minweight")
            algorithm = "minweight";
        else if(a == "--max")
            algorithm = "max";
        i++;
    }

    if(filename == "" || algorithm == "")
    {
        cout << "usage: ./example -f <filename> <--minweight | --max>" << endl;
        cout << "--minweight for minimum weight perfect matching" << endl;
        cout << "--max for maximum cardinality matching" << endl;
        cout << "file format:" << endl;
        cout << "the first two lines give n (number of vertices) and m (number of edges)," << endl;
        cout << "followed by m lines, each with a tuple (u, v [, c]) representing the edges," << endl;
        cout << "where u and v are the endpoints (0-based indexing) of the edge and c is its cost" << endl;
        cout << "the cost is optional if --max is specified" << endl;
        return 1;
    }

    try
    {
        if(algorithm == "minweight")
            MinimumCostPerfectMatchingExample(filename);
        else
            MaximumMatchingExample(filename);
    }
    catch(const char * msg)
    {
        cout << msg << endl;
        return 1;
    }
    */
	return 0;
}
