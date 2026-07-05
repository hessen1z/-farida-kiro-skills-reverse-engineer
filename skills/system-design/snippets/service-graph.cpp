#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>

struct Service {
    std::string name;
    std::vector<std::string> dependencies;
};

std::vector<std::string> TopologicalSort(const std::vector<Service>& services) {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, int> indegree;

    for (const auto& service : services) {
        indegree[service.name];
        for (const auto& dep : service.dependencies) {
            graph[dep].push_back(service.name);
            indegree[service.name]++;
        }
    }

    std::vector<std::string> ready;
    for (const auto& [name, count] : indegree) {
        if (count == 0) {
            ready.push_back(name);
        }
    }

    std::vector<std::string> order;
    while (!ready.empty()) {
        auto name = ready.back();
        ready.pop_back();
        order.push_back(name);
        for (auto& next : graph[name]) {
            if (--indegree[next] == 0) {
                ready.push_back(next);
            }
        }
    }

    return order;
}

int main() {
    std::vector<Service> services = {
        {"ServiceA", {"ServiceB"}},
        {"ServiceB", {"ServiceC"}},
        {"ServiceC", {}}
    };

    auto order = TopologicalSort(services);
    for (auto& name : order) {
        std::cout << name << "\n";
    }

    return 0;
}
