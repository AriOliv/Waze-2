#include <iostream>
#include <vector>
using namespace std;

/**
 * Structure of Nodes in the Priority Queue
 *
 * @param int id: Node id
 * @param int distancia: Distance associated with node in Dijkstra's algorithm
 * 
 */
struct PNode{
    public:
        int id;
        int distancia;
    PNode(int id, int distancia){
        this->id = id;
        this->distancia = distancia;
    }
};

/**
 * Min-Heap (Binary Heap) adapted for use in Dijkstra's implementation as priority queue 
 * 
 * The Binary Heap order is determined by the distance associated with the node
 * 
 * @note: this implementation can be easily adapted to other usage contexts.
 * @note: Reference: https://www.geeksforgeeks.org/binary-heap/ (This is a Min-Heap implementation)
 */
class PriorityQueue{

    public:
        vector<PNode> priorityqueue; //stores all priorityqueue element's id
        

    /**
     * Change two nodes positions
     *
     * @param PNode* pointers to nodes to swap
     */
    void swap(PNode *node1, PNode *node2) {
            PNode temp = *node2;
            *node2 = *node1;
            *node1 = temp;
    }

    /**
     * Organizes the tree, keeping its invariant
     * 
     * @param int i: 
     * @param int size: number of elements in Heap
     *
     * @note In a Min-Heap the root node shoul be the smallest
     */
    void heapify(int i, int size){

        int smallest = i;
        int left_child = 2*i +1;
        int right_child = 2*i +2;

        if (left_child < size && this->priorityqueue[left_child].distancia < this->priorityqueue[i].distancia)
            smallest = left_child;
        if (right_child < size && this->priorityqueue[right_child].distancia < this->priorityqueue[smallest].distancia)
            smallest = right_child;
        if (smallest != i) {
            swap(&priorityqueue[i], &priorityqueue[smallest]);
            heapify(smallest, priorityqueue.size());
        }


    }

    // returns the number of nodes in priority queue
    int size(){return this->priorityqueue.size();}

    /**
     * Add new node to Heap
     * 
     * @param int id: Node id
     * @param int dist: Distance associated with node
     *
     */
    void push(int id,int dist){
        // Node temp = PNode(id,dist);

         this->priorityqueue.push_back(PNode(id, dist));
        //  int len = priorityqueue.size() ;

        if (priorityqueue.size() !=0)
        {
            for (int i = priorityqueue.size() / 2 - 1; i >= 0; i--)
            {
                heapify(i, priorityqueue.size());
            }
        }       
    }

    /**
     * Remove the top (root) Node
     */
    void pop(){

        swap(&priorityqueue[0], &priorityqueue[priorityqueue.size() - 1]);
        this->priorityqueue.pop_back();

        for (int i = priorityqueue.size() / 2 - 1; i >= 0; i--)
            {
                heapify(i,priorityqueue.size());
            }
    }

    /**
     * Returns true if Priority Queue is empty
     * @note vectors already have this method
     */
    bool empty(){return priorityqueue.empty();}

    /**
     * Returns the top (root) Node
     */
    int top(){return priorityqueue[0].id;}
    

};

