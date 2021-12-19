#include <bits/stdc++.h>

/**
 * Descreva o que a função faz
 *
 * @param vector<int> descreva  o parametro
 * 
 * @return descreva o retorno
 */
int Graph::find_lowest_f(vector<int> open_list)
{

    int id_minimum = open_list[0];
    int minimum_f = find_node_by_id(open_list[0])->f;
    int temp_f;
    for (int id : open_list)
    {
        temp_f = find_node_by_id(id)->f;
        if (temp_f <= minimum_f)
        {
            minimum_f = temp_f;
            id_minimum = id;
        };
    }
    return id_minimum;
}

/**
 * Calculates the shortest path using A* algorithm 
 *
 * @param double y1, x1: initial coordinates
 * @param double y2, x2: final coordinates
 * 
 * @return JSON style string stream containing the shortest path and runtime 
 */


/**
 * Calculates the shortest path using A* algorithm 
 *
 * @param double y1, x1: initial coordinates
 * @param double y2, x2: final coordinates
 * 
 * @return JSON style string stream containing the shortest path, alternative paths and runtime
 */
void Graph::A_star(double y1, double x1, double y2, double x2)
{
    cout << "{";
    cout << "\"considered\":";
    // Criando uma um vetor de nós abertos e fechados
    vector<int> open_list;
    // vector<int> closed_list;
    // Encontrando o nó incial
    Node start_node = *find_node_by_coordinate(y1, x1);
    Node end_node = *find_node_by_coordinate(y2, x2);
    Node current_node = start_node;
    // Node neighbor_node = start_node;
    double h = euclidean_distance(y1, x1, y2, x2);
    double g = 0;
    double f = h + g;
    start_node.f = f;
    int count = 0;
    cout << "[";
    cout << start_node.id;
    // Iterando todos os nós
    double runtime;
    double runtime_remove_open_list;
    double runtime_push_find_find;
    double runtime_find_open_close;
    double runtime_if_is_not_close;
    clock_t tStart = clock();
    while (current_node.id != end_node.id)
    {
        // Iterando todos os vizinhos do Nó
        for (Edge* neighbor : current_node.neighbors)
        {
            // Veirificando se um item pertence a open list
            
            Node *neighbor_node = find_node_by_id(neighbor->id_to);
            bool is_in_open = neighbor_node->is_in_open_list;
            bool is_in_close = neighbor_node->is_in_close_list;

            is_in_open = is_in_open || is_in_close;

            if (!is_in_open) //priemeira mudança
            {
                // Adicionando o vector a open list
                // Alteração aqui
                neighbor_node->is_in_open_list = true;
                open_list.push_back(neighbor->id_to);
            }
             //Segunda mudança

            if (!is_in_close)
            {
                // AVALIAR ADICIONAR ESSE DEPOIS
                // distancia de no anterior ate o seu no adjacente   
                g = neighbor->length + current_node.g;
                h = euclidean_distance_by_id(end_node.id, neighbor->id_to);
                f = g + h;
                Node *adjacent_node = find_node_by_id(neighbor->id_to);

                if (adjacent_node->f > f || adjacent_node->f == 0)
                {
                    adjacent_node->g = g;
                    adjacent_node->f = f;
                    adjacent_node->previous_node_id = current_node.id;
                }
            }
        };
    
        // alteração aqui
        int lowest_f = find_lowest_f(open_list);
        current_node = *find_node_by_id(lowest_f);
        Node *current_node_ptr = find_node_by_id(lowest_f);

        // Alteração aqui
        current_node_ptr->is_in_close_list = true;

        cout << "," << current_node.id;

        // Alteração aqui
        current_node_ptr->is_in_open_list = false;
        open_list.erase(std::remove(open_list.begin(), open_list.end(), lowest_f), open_list.end());
    
        count+=1;
    };
    
    cout << "],";
    runtime = (clock() - tStart ) / (double) CLOCKS_PER_SEC;
    cout << "\"runtime\":"<< runtime << ",";
    int current_id = current_node.id;
    cout << "\"distancia\":" << current_node.g;
    count = 1;
    current_node = *find_node_by_id(current_id);
    cout << ",\"path\":";
    cout << "[";
    cout << current_node.id;
    while (current_node.id != start_node.id)
    {
        current_node = *find_node_by_id(current_node.previous_node_id);
        cout << ","
             << current_node.id;
        count++;
    }
    cout << "],";
    cout << "\"Algoritmo\":";
    cout << "\"A*\",";
}

void Graph::A_star_with_coordinate(double y1, double x1, double y2, double x2)
{
    
    // cout << "\"considered\":";
    // Criando uma um vetor de nós abertos e fechados
    vector<int> open_list;
    // vector<int> closed_list;
    // Encontrando o nó incial
    Node start_node = *find_node_by_coordinate(y1, x1);
    Node end_node = *find_node_by_coordinate(y2, x2);
    Node current_node = start_node;
    // Node neighbor_node = start_node;
    double h = euclidean_distance(y1, x1, y2, x2);
    double g = 0;
    double f = h + g;
    start_node.f = f;
    int count = 0;
    // cout << "[";
    // cout << start_node.id;
    // Iterando todos os nós
    double runtime;
    double runtime_remove_open_list;
    double runtime_push_find_find;
    double runtime_find_open_close;
    double runtime_if_is_not_close;
    clock_t tStart = clock();
    while (current_node.id != end_node.id)
    {
        // Iterando todos os vizinhos do Nó
        for (Edge* neighbor : current_node.neighbors)
        {
            // Veirificando se um item pertence a open list
            
            Node *neighbor_node = find_node_by_id(neighbor->id_to);
            bool is_in_open = neighbor_node->is_in_open_list;
            bool is_in_close = neighbor_node->is_in_close_list;

            is_in_open = is_in_open || is_in_close;

            if (!is_in_open) //priemeira mudança
            {
                // Adicionando o vector a open list
                // Alteração aqui
                neighbor_node->is_in_open_list = true;
                open_list.push_back(neighbor->id_to);
            }
             //Segunda mudança

            if (!is_in_close)
            {
                // AVALIAR ADICIONAR ESSE DEPOIS
                // distancia de no anterior ate o seu no adjacente   
                g = neighbor->length + current_node.g;
                h = euclidean_distance_by_id(end_node.id, neighbor->id_to);
                f = g + h;
                Node *adjacent_node = find_node_by_id(neighbor->id_to);

                if (adjacent_node->f > f || adjacent_node->f == 0)
                {
                    adjacent_node->g = g;
                    adjacent_node->f = f;
                    adjacent_node->previous_node_id = current_node.id;
                }
            }
        };
    
        // alteração aqui
        int lowest_f = find_lowest_f(open_list);
        current_node = *find_node_by_id(lowest_f);
        Node *current_node_ptr = find_node_by_id(lowest_f);

        // Alteração aqui
        current_node_ptr->is_in_close_list = true;

        // cout << "," << current_node.id;

        // Alteração aqui
        current_node_ptr->is_in_open_list = false;
        open_list.erase(std::remove(open_list.begin(), open_list.end(), lowest_f), open_list.end());
    
        count+=1;
    };
    
    // cout << "],";
    runtime = (clock() - tStart ) / (double) CLOCKS_PER_SEC;
    cout << "Runtime: "<< runtime << "\n";
    int current_id = current_node.id;
    cout << "Total Weight: " << current_node.g << "\n";
    count = 1;
    current_node = *find_node_by_id(current_id);
    cout  << "Path: \n";
    cout << "{x:" << current_node.x << ",y:" << current_node.y << "}";
    while (current_node.id != start_node.id)
    {
        current_node = *find_node_by_id(current_node.previous_node_id);
        cout << ","<< 
            "{x:" << current_node.x << ",y:" << current_node.y << "}";
        count++;
    }
    cout << "\n";
}