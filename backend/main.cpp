// include required libraries 
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

// include required modules 
#include "graph.cpp"
#include "dijkstra.cpp"
#include "A_star.cpp"

/**
 * Receives front-end parameters and call shortest path algorithm
 * 
 * @note Parameters are passed through a string and read with the 'getenv' function
 *
 * @param double y1, x1: initial coordinates
 * @param double y2, x2: final coordinates
 * @param int algorithms: user-chosen algorithm (1: A*; 2:dijkstra)
 * @param bool by_travel_time: User choice to see shortest or fastest path (1:Fastest; 0:Shortest)
 * 
 */
int main(int argc, char** argv)
{
        double y1;
        double x1;
        double y2;
        double x2;
        int algorithm;
        bool by_travel_time;

    clock_t tStart = clock();
    //initialize the graph
    try
    {
        string pontos = getenv("QUERY_STRING"); //store the request
        cout << "Content-Type: application/json\r\n\r\n";
        string delimeter = ";"; 
        y1 = stod(pontos.substr(0, pontos.find(";")));  // get coordenate y1
        pontos.erase(0, pontos.find(delimeter) + delimeter.length());

        x1 = stod(pontos.substr(0, pontos.find(";")));  // get coordenate x1
        pontos.erase(0, pontos.find(delimeter) + delimeter.length());

        y2 = stod(pontos.substr(0, pontos.find(";")));  // get coordenate y2
        pontos.erase(0, pontos.find(delimeter) + delimeter.length());

        x2 = stod(pontos.substr(0, pontos.find(";")));  // get coordenate x2
        pontos.erase(0, pontos.find(delimeter) + delimeter.length());

        algorithm = stoi(pontos.substr(0, pontos.find(";")));  // get algorithm
        pontos.erase(0, pontos.find(delimeter) + delimeter.length());

        by_travel_time = stoi(pontos.substr(0, pontos.find(";")));  // get alternative_paths option
        pontos.erase(0, pontos.find(delimeter) + delimeter.length());

        Graph GF = Graph(by_travel_time); 
        
        // run the algorithm as requested
        if(algorithm == 1){
            GF.A_star(y1, x1, y2, x2);
        }else{
            GF.dijkstra(y1, x1, y2, x2);
        }
        double runtime = (clock() - tStart ) / (double) CLOCKS_PER_SEC;
        cout << "\"tempo_total\":"<< runtime << "}";  
    }

    catch(const std::exception& e)
    {
        y1 = stod(argv[1]);
        x1 = stod(argv[2]);
        y2 = stod(argv[3]);
        x2 = stod(argv[4]);
        algorithm = stoi(argv[5]);
        by_travel_time = stoi(argv[6]);

        Graph GF = Graph(by_travel_time); 

        if(algorithm == 1){
            GF.A_star_with_coordinate(y1, x1, y2, x2);
        }else{
            GF.dijkstra_with_coordinate(y1, x1, y2, x2);
        }
        double runtime = (clock() - tStart ) / (double) CLOCKS_PER_SEC;
        cout << "Tempo Total: "<< runtime << "\n";  
    }
   
};