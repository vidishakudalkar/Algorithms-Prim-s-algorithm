#include <bits/stdc++.h>
  
using namespace std;
  
struct edge
{
    int u, v;
    int weight;
};
  
void Enqueue(struct edge heap[], int size, struct edge value)//adds node in queue
{
    heap[size] = value;
      
    int i = size;
    struct edge temp;
      
    while (i >= 1) {
        if (heap[i / 2].weight > heap[i].weight) {
            temp = heap[i / 2];
            heap[i / 2] = heap[i];
            heap[i] = temp;
            i = i / 2;
        } else {
            break;
        }
    }
}
  
void Heapify(struct edge heap[], int size, int index)//sorting of nodes
{
    int i = index;
    struct edge temp;
      
    while ((2 * i) < size) {
          
        if ((2 * i) + 1 >= size) {
           
            if (heap[i].weight > heap[2 * i].weight) {
              
                temp = heap[i];
                heap[i] = heap[2 * i];
                heap[2 * i] = temp;
                break;
            }
        }
          
        if (heap[i].weight > heap[2 * i].weight || heap[i].weight > heap[2 * i + 1].weight) {

            if (heap[2 * i].weight <= heap[(2 * i) + 1].weight) {
                temp = heap[2 * i];
                heap[2 * i] = heap[i];
                heap[i] = temp;
                i = 2 * i;
            } else if (heap[2 * i].weight > heap[(2 * i) + 1].weight) {
                temp = heap[(2 * i) + 1];
                heap[(2 * i) + 1] = heap[i];
                heap[i] = temp;
                i = (2 * i) + 1;
            }
        } else {
            break;
        }
    }
}
  
void DeleteNode(struct edge heap[], int size, int index)//deletion of nodes
{
    struct edge temp = heap[index];
    heap[index] = heap[size - 1];
    heap[size - 1] = temp;
    int i = index;
    --size;
    Heapify(heap, size, i);
}
  
struct edge ExtractMin(struct edge heap[], int size)
{
    struct edge min = heap[0];
   
    DeleteNode(heap, size, 0);
   
    return min;
}
  
void PrimsAlgorithm(
            vector< list< pair<int, int> > > & graph, 
            int vertexcount, 
            int edgecount, 
            int startVertex, 
            vector< list< pair<int, int> > > & primsalgo
         )
{
    int current = startVertex, newVertex;
    bool color[vertexcount + 1];
    struct edge var;
    struct edge PriorityQueue[2 * edgecount];
    int QueueSize = 0;
   
    int i;
   
    for (i = 0; i <= vertexcount; ++i) {        // Initialize color of nodes to white i.e. false
        color[i] = false;
    }
   
    i = 0;
   
    while (i < vertexcount) {
        if (!color[current]) {            // If current node is white
            color[current] = true;        // change color of node to black ie true
              
            list< pair<int, int> >::iterator itr = graph[current].begin();
              
            while (itr != graph[current].end()) {                
                if (!color[(*itr).first]) {
                   
                    var.u = current;
                    var.v = (*itr).first;
                    var.weight = (*itr).second;
                  
                    Enqueue(PriorityQueue, QueueSize, var);
                    ++QueueSize;
                }
                  
                ++itr;
            }
   
            var = ExtractMin(PriorityQueue, QueueSize);
            --QueueSize;
            newVertex = var.v;
            current = var.u;
            if (!color[newVertex]) {
                primsalgo[current].push_back(make_pair(newVertex, var.weight));
                primsalgo[newVertex].push_back(make_pair(current, var.weight));
            }
            current = newVertex;
            ++i;
        } else {
   
            var = ExtractMin(PriorityQueue, QueueSize);
            --QueueSize;
   
            newVertex = var.v;
            current = var.u;
   
            if (!color[newVertex]) {
                primsalgo[current].push_back(make_pair(newVertex, var.weight));
                primsalgo[newVertex].push_back(make_pair(current, var.weight));
            }
   
            current = newVertex;
        }
    }
}
  
int main()
{
    int vertexcount, edgecount, vertex1, vertex2, weight;
      
//input # of nodes and edges
    printf("Enter the Number of Vertices and Edges of the graph -\n");
    scanf("%d%d", &vertexcount, &edgecount);
    
    vector< list< pair<int, int> > > graph(vertexcount + 1);
    vector< list< pair<int, int> > > primsalgo(vertexcount + 1);
      
//input the nodes and its corresponing weights
    printf("Enter the Edges as Vertex1 Vertex2 Weight \n");
      
    for (int i = 1; i <= edgecount; ++i) {
        scanf("%d%d%d", &vertex1, &vertex2, &weight);
          
        graph[vertex1].push_back(make_pair(vertex2, weight));
        graph[vertex2].push_back(make_pair(vertex1, weight));
    }
    PrimsAlgorithm(graph, vertexcount, edgecount, 1, primsalgo);
   
    printf("\nBelow is the MST of the input graph-\n");
    for (int i = 1; i < primsalgo.size(); ++i) {
        list< pair<int, int> >::iterator itr = primsalgo[i].begin();
          
        while (itr != primsalgo[i].end()) {
		if(i<(*itr).first){
          printf("Edge from Vertex %d ", i);
            printf("to Vertex %d with Weight %d\n", (*itr).first, (*itr).second);
	}
            ++itr;
        }
       
    }
      
    return 0;
}
