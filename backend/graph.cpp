// This module creates the graph structures
// and load nodes and edges from a csv file

// Reference: https://www.geeksforgeeks.org/graph-and-its-representations/

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

/**
 *Stores the Edge size and the final node id 
 *
 * @param int id_to - final node id
 * @param  int length - travel time
 */
struct Edge
{
public:
    int id_to;  // id da conexão
    int length; // tamanho da rota (considerando a velocidade)
    // construtor da Aresta
    Edge(int id_to, int length)
    {
        this->id_to = id_to;
        this->length = length;
    }
};

/**
 * Stores the id, latitude, longitude, neighbours, previous Node id and the distance from root of the Node 
 *
 * @param int id - node id
 * @param  double x -longitudee
 * @param  double y - latitude
 * 
 */
struct Node
{

    int id;
    double x;
    double y;

    // Vector in which all Edges linked to the node are stored
    vector<Edge *> neighbors;

    int previous_node_id;

    // distance from root
    double g = 0; // sexta mudança

    // heuristic node
    double f = 0;

    bool is_in_open_list = false;

    bool is_in_close_list = false;

    // Node Constructor
    Node(int id, double x, double y)
    {
        this->id = id;
        this->x = x;
        this->y = y;
    }
};

/**
 * Create the Graph Structure for finding shortest paths
 * 
 * @note The graph is created from nodes and egdes from a csv file
 * @note This csv should be in 'arquivos_grafo' folder and each file should be named Nodes.csv and Edges.csv
 * @note If you created the csv files from 'graph_to_csv.py' module it should be OK
 * 
 * @param int id - node id
 * @param  double x -longitudee
 * @param  double y - latitude
 * 
 */
class Graph
{
public:
    // Stores all nodes of graph
    vector<Node> graph_list;

    // Methods
    void A_star(double y1, double x1, double y2, double x2);
    int find_lowest_f(vector<int> open_list);
    void dijkstra(double y1, double x1, double y2, double x2);
    void alternative_A_star_paths(double y1, double x1, double y2, double x2);
    void dijkstra_with_coordinate(double y1, double x1, double y2, double x2);
    void A_star_with_coordinate(double y1, double x1, double y2, double x2);
    // Constructor
    Graph(bool by_travel_time)
    {
        loadNodes();
        loadEdges(by_travel_time);
    }

    // Load nodes from csv file
    void loadNodes()
    {

        int id;
        double x;
        double y;
        (this->graph_list).push_back(Node(0, 0, 0));
        if (std::FILE *f = std::fopen("../arquivos_grafo/Nodes.csv", "r"))
        {
            // Pulando a linha do cabeçalho
            fscanf(f, "%*[^\n]\n");
            while (std::fscanf(f, "%i;%lf;%lf", &id, &y, &x) == 3)
            {
                // cout << id << x << y << endl;
                (this->graph_list).push_back(Node(id, x, y));
            }
            std::fclose;
        }
    }

    // Add Edges in neighbors vector
    void addEdge(int id_from, int id_to, int length)
    {
        (this->graph_list[id_from]).neighbors.push_back(new Edge(id_to, length));
    }

    // Load edges from csv file
    void loadEdges(bool by_travel_time)
    {
        int id_from;
        int id_to;
        double length;
        clock_t tStart2 = clock();
        double runtime_2;
        if (by_travel_time)
        {
            if (std::FILE *f = std::fopen("../arquivos_grafo/Edges_travel_time.csv", "r"))
            {
                // Skiping header file
                fscanf(f, "%*[^\n]\n");
                while (std::fscanf(f, "%i;%i;%le", &id_from, &id_to, &length) == 3)
                {
                    addEdge(id_from, id_to, length);
                }
                std::fclose;
            }
        }
        else
        {
            if (std::FILE *f = std::fopen("../arquivos_grafo/Edges_travel_length.csv", "r"))
            {
                // Skiping header file
                fscanf(f, "%*[^\n]\n");
                while (std::fscanf(f, "%i;%i;%le", &id_from, &id_to, &length) == 3)
                {
                    addEdge(id_from, id_to, length);
                }
                std::fclose;
            }
        }
    }

    //                  Auxiliary methods

    // prints each node and its neighbors
    void printGraph()
    {
        for (auto graph : this->graph_list)
        {

            cout << graph.id;
            for (auto node : graph.neighbors)
            {
                cout << " -> " << node->id_to;
            }
            cout << endl;
        }
    }

    // returns the number of nodes in the graph
    int size()
    {
        int size = 0;
        for (Node no : this->graph_list)
        {
            size++;
        }
        return size;
    }

    // returns the node given its id
    Node *find_node_by_id(int id)
    {

        return &this->graph_list[id];
    }

    /**
     * Find the closest node to a coordinate 
     * 
     * @note Not all coordinates have nodes, so we need this method to be able to calculate the shortest path to any point on the map
     *
     * @param  double x -longitude
     * @param  double y - latitude
     * 
     */
    Node *find_node_by_coordinate(double y, double x)
    {
        Node *nearest_node = &this->graph_list[0];
        double minimun_distance = euclidean_distance((*nearest_node).y, (*nearest_node).x, y, x);
        for (Node itr : graph_list)
        {
            if (euclidean_distance(itr.y, itr.x, y, x) <= minimun_distance)
            {
                *nearest_node = itr;
                minimun_distance = euclidean_distance((*nearest_node).y, (*nearest_node).x, y, x);
            }
        }
        return nearest_node;
    }

    // Calculates the Euclidean distance between two nodes, given its coordinates
    double euclidean_distance(double y1, double x1, double y2, double x2)
    {
        return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5) * pow(10, 5);
    }

    // Returns the Euclidean distance between two nodes, given its ids
    double euclidean_distance_by_id(int id1, int id2)
    {
        Node node1 = *find_node_by_id(id1);
        Node node2 = *find_node_by_id(id2);

        return euclidean_distance(node1.y, node1.x, node2.y, node2.x);
    }
};
