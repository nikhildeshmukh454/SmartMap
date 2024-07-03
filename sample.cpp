#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <graphviz/gvc.h> // Include Graphviz C API headers

using namespace std;

// Define your Node and Edge classes here as per your original code...

void generateDotFile(const vector<Node>& nodes, const vector<vector<Edge>>& edges) {
    ofstream dotFile("graph.dot");
    if (!dotFile.is_open()) {
        cerr << "Failed to open graph.dot for writing." << endl;
        return;
    }

    dotFile << "graph SmartMap {" << endl;

    // Write nodes
    for (const auto& node : nodes) {
        dotFile << "  " << node.id << " [label=\"" << node.name << "\"];" << endl;
    }

    // Write edges
    for (size_t i = 0; i < edges.size(); ++i) {
        for (const auto& edge : edges[i]) {
            dotFile << "  " << edge.start.id << " -- " << edge.end.id;
            dotFile << " [label=\"" << edge.type << ", " << edge.distance << " km\"];" << endl;
        }
    }

    dotFile << "}" << endl;
    dotFile.close();
}

void plotGraph() {
    generateDotFile(records, edges);

    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    char *graphFile = "graph.dot";
    char *graphImage = "graph.png";

    gvc = gvContext();
    if (gvc == NULL) {
        cerr << "Failed to initialize Graphviz context." << endl;
        return;
    }

    fp = fopen(graphFile, "r");
    if (fp == NULL) {
        cerr << "Failed to open " << graphFile << " for reading." << endl;
        gvFreeContext(gvc);
        return;
    }

    g = agread(fp, NULL);
    if (g == NULL) {
        cerr << "Failed to read graph from " << graphFile << endl;
        fclose(fp);
        gvFreeContext(gvc);
        return;
    }

    fclose(fp);

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", graphImage);

    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);

    cout << "Graph plotted as " << graphImage << endl;
}

int main() {
    DataExtract();
    addEdge();
    plotGraph();

    return 0;
}
