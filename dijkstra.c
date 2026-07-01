#define MAX_NODES 1000

// Declare WASM export visibility macro
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define WASM_EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif

/**
 * Calculates the shortest path on a 2D grid using Dijkstra's algorithm.
 * 
 * @param width Grid column count
 * @param height Grid row count
 * @param grid Pointer to integer array representing cell states (0 = empty, 1 = blockade)
 * @param startNode Index of starting cell (y * width + x)
 * @param endNode Index of target cell (y * width + x)
 * @param outPath Pointer to integer array where path node indices will be written
 * @param outEvaluated Pointer to integer array where evaluated node indices will be written (for animation)
 * @param evaluatedCount Pointer to integer where the total count of evaluated nodes will be written
 * @return Path length (node count), or -1 if no path exists.
 */
WASM_EXPORT
int findShortestPath(int width, int height, const int* grid, int startNode, int endNode, int* outPath, int* outEvaluated, int* evaluatedCount) {
    int dist[MAX_NODES];
    int parent[MAX_NODES];
    int visited[MAX_NODES];
    int numNodes = width * height;

    // Fail-safe size check
    if (numNodes > MAX_NODES) {
        return -1;
    }

    // Initialize tracking arrays
    for (int i = 0; i < numNodes; i++) {
        dist[i] = 1000000; // Infinity representation
        parent[i] = -1;
        visited[i] = 0;
    }

    dist[startNode] = 0;
    *evaluatedCount = 0;

    for (int count = 0; count < numNodes; count++) {
        // Find unvisited node with minimum distance
        int minDist = 1000000;
        int u = -1;
        for (int i = 0; i < numNodes; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        // If target reached or remaining nodes are unreachable
        if (u == -1 || u == endNode) {
            break;
        }

        visited[u] = 1;
        outEvaluated[(*evaluatedCount)++] = u; // Track visit order for visual wavefront wave

        int ux = u % width;
        int uy = u / width;

        // 4-Directional movements (Up, Down, Right, Left)
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int vx = ux + dx[i];
            int vy = uy + dy[i];
            
            // Check grid boundaries
            if (vx >= 0 && vx < width && vy >= 0 && vy < height) {
                int v = vy * width + vx;
                
                // If cell is unvisited and is not a charcoal blockade (grid[v] == 0)
                if (!visited[v] && grid[v] == 0) {
                    int newDist = dist[u] + 1;
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        parent[v] = u;
                    }
                }
            }
        }
    }

    // If destination node was never reached
    if (dist[endNode] == 1000000) {
        return -1;
    }

    // Reconstruct the path backwards from endNode to startNode
    int curr = endNode;
    int pathLength = 0;
    int tempPath[MAX_NODES];
    while (curr != -1) {
        tempPath[pathLength++] = curr;
        curr = parent[curr];
    }

    // Reverse path sequence to startNode -> ... -> endNode
    for (int i = 0; i < pathLength; i++) {
        outPath[i] = tempPath[pathLength - 1 - i];
    }

    return pathLength;
}
