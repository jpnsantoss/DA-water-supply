//
// Created by jpnsantos on 21/03/24.
//

#include "ReliabilityManager.h"
#include "utils/Dataset.h"
#include "FlowManager.h"

ReliabilityManager::ReliabilityManager() {
    Dataset *dataset = Dataset::getInstance();
    this->graph = dataset->getGraph();
}

vector<pair<string, double>> ReliabilityManager::evaluateReservoirImpact(string reservoir) {
    vector<pair<string, double>> res;
    FlowManager originalFlowManager(graph);

    // Create a new graph that is a copy of the original graph but without the reservoir
    Graph g;
    for (Vertex *v: graph.getVertexSet()) {
        if (v->getCode() != reservoir) {
            g.addVertex(new Vertex(*v));
        }
    }
    for (Vertex *v: graph.getVertexSet()) {
        if (v->getCode() != reservoir) {
            Vertex *copiedVertex = g.findVertex(v->getCode());
            for (Edge *e: v->getAdj()) {
                if (e->getDest()->getCode() != reservoir) {
                    Vertex *dest = g.findVertex(e->getDest()->getCode());
                    copiedVertex->addEdge(dest, e->getWeight());
                }
            }
        }
    }

    FlowManager flowManager(g);

    for (auto city: g.getDeliverySites()) {
        CityMetrics originalMetrics = originalFlowManager.getCityMetrics(city->getCode());
        CityMetrics changedMetrics = flowManager.getCityMetrics(city->getCode());

        // If the city has less flow in the copied graph, it's affected by the removal of the reservoir
        if (changedMetrics.incomingFlow < originalMetrics.incomingFlow && originalMetrics.difference == 0) {
            res.emplace_back(city->getCode(), changedMetrics.difference);
        }
    }

    return res;
}