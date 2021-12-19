// #include "graph.cpp"
#include "auxiliares.cpp"
#include "priority_queue.cpp"


#define INFINITO 100000000
#define INDEFINIDO -1

// // temporarily created class: priority_queue comparative argument (STD VERSION - NOT BEEN USED)
// class ComparaVelocidadeRota{
//     public:
//         int operator() (const Dist& p1, const Dist& p2){
//             return p1.distancia > p2.distancia ;
//     }
// };

  
/**
 * Calculates the shortest path using Dijkstra's algorithm 
 *
 * @param double y1, x1: initial coordinates
 * @param double y2, x2: final coordinates
 * 
 * @return JSON style string stream containing the shortest path and runtime 
 */
void Graph::dijkstra(double y1, double x1, double y2, double x2){
       // priority_queue<Dist, vector<Dist>, ComparaVelocidadeRota> priorityqueue; This is STD priority queue - NOT BEEN USED
        PriorityQueue priority_queue = PriorityQueue();
        
        Node start_node = *find_node_by_coordinate(y1, x1); // starting point
        Node end_node = *find_node_by_coordinate(y2, x2); // destination
        Node current_node = start_node; 

        int size = this->size(); // total number of nodes
        int alt; // auxiliary variable
        double runtime; // stores Disjktra runtime
        vector<int> dist; // distances
        vector<int> prev; // predecessors
        // vector<int> visited; // all visited nodes in order 
    
        // Inicializate 
        for (Node vertice : this->graph_list){

            if (vertice.id != start_node.id){
                dist.push_back(INFINITO);   
                prev.push_back(INDEFINIDO); 
            }
            else{
                dist.push_back(0);
            }
            
        }

        priority_queue.push(start_node.id, dist[start_node.id]); // add start_node to priorityqueue
        
         
        // Run Disjktra: 
   
        clock_t tStart = clock();

        while (!priority_queue.empty()){

             
            int top_id = priority_queue.top(); priority_queue.pop();
            current_node = *find_node_by_id(top_id);
            // visited.push_back(current_node.id); // add visited node in vector
           
            
            for (auto neighbor : current_node.neighbors){ 

                alt = dist[current_node.id] + neighbor->length;

                 if (alt < dist[neighbor->id_to])
                {
                    dist[neighbor->id_to] = alt;
                    prev[neighbor->id_to] = current_node.id;
                    priority_queue.push(neighbor->id_to, alt);
                }
                
            }
           
            
        }
  
        runtime = (clock() - tStart ) / (double) CLOCKS_PER_SEC;

        // Return results for fetch API
        cout << "{\"runtime\":" << runtime << ",";
        // Disjktra consider all nodes, so its not necessary to show them all - only if we want to see the considered order
        // // cout << "\"considered\":[";
        // // for(auto i = visited.begin(); i != visited.end()-1; ++i){
        // //      cout << *i << ","; 
        // // }
        // // cout << *(visited.end());
        cout << "\"distancia\":" << dist[end_node.id];
        cout  << ",\"path\": [";
        cout << end_node.id;
        if (prev[end_node.id] != INDEFINIDO)
        {
            current_node = end_node;
            
            while (current_node.id != start_node.id) 
            {
                current_node = *find_node_by_id(prev[current_node.id]);
                cout << "," << current_node.id;
            }
        }
        cout << "],";
};


void Graph::dijkstra_with_coordinate(double y1, double x1, double y2, double x2){
     
        // priority_queue<Dist, vector<Dist>, ComparaVelocidadeRota> priorityqueue; This is STD priority queue - NOT BEEN USED
        PriorityQueue priority_queue = PriorityQueue();
        
        Node start_node = *find_node_by_coordinate(y1, x1); // starting point
        Node end_node = *find_node_by_coordinate(y2, x2); // destination
        Node current_node = start_node; 

        int size = this->size(); // total number of nodes
        int alt; // auxiliary variable
        double runtime; // stores Disjktra runtime
        vector<int> dist; // distances
        vector<int> prev; // predecessors
        vector<int> visited; // all visited nodes in order 
        vector<int> short_path; // stores shortpath
        // vector<int> visited; // all visited nodes in order 
    
        // Inicializate 
        for (Node vertice : this->graph_list){

            if (vertice.id != start_node.id){
                dist.push_back(INFINITO);   
                prev.push_back(INDEFINIDO); 
            }
            else{
                dist.push_back(0);
            }
            
        }

        priority_queue.push(start_node.id, dist[start_node.id]); // add start_node to priorityqueue
        
         
        // Run Disjktra: 
   
        clock_t tStart = clock();

        while (!priority_queue.empty()){

             
            int top_id = priority_queue.top(); priority_queue.pop();
            current_node = *find_node_by_id(top_id);
            // visited.push_back(current_node.id); // add visited node in vector
           
            
            for (auto neighbor : current_node.neighbors){ 

                alt = dist[current_node.id] + neighbor->length;

                 if (alt < dist[neighbor->id_to])
                {
                    dist[neighbor->id_to] = alt;
                    prev[neighbor->id_to] = current_node.id;
                    priority_queue.push(neighbor->id_to, alt);
                }
                
            }
           
            
        }
  
        runtime = (clock() - tStart ) / (double) CLOCKS_PER_SEC;


         // Return results for fetch API
        cout << "Runtime: " << runtime << "\n";
        // Disjktra consider all nodes, so its not necessary to show them all - only if we want to see the considered order
        // // cout << "\"considered\":[";
        // // for(auto i = visited.begin(); i != visited.end()-1; ++i){
        // //      cout << *i << ","; 
        // // }
        // // cout << *(visited.end());
        cout << "Total Weight: " << dist[end_node.id]  << "\n";
        cout  << "Path: \n";
        cout << "{x:" << end_node.x << ",y:" << end_node.y << "}";
        if (prev[end_node.id] != INDEFINIDO)
        {
            current_node = end_node;
            while (current_node.id != start_node.id)
            {
                short_path.push_back(dist[current_node.id]);
                current_node = *find_node_by_id(prev[current_node.id]);
                cout << ",{x:" << current_node.x << ",y:" << current_node.y << "}";
            }
        }
        cout << "\n";
};
