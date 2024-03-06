//
// Created by jpnsantos on 06/03/24.
//

#ifndef DA_WATER_SUPPLY_NODE_H
#define DA_WATER_SUPPLY_NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {
protected:
    int id;
    string code;
public:
    virtual ~Node() = default;

    // Getters
    int getId() const {
        return id;
    }

    const string &getCode() const {
        return code;
    }

    // Setters
    void setId(int id) {
        Node::id = id;
    }

    void setCode(const string &code) {
        Node::code = code;
    }

    bool operator==(const Node &rhs) const {
        return id == rhs.id && code == rhs.code;
    }

    bool operator<(const Node &rhs) const {
        return id < rhs.id;
    }
};

namespace std {
    template<>
    struct hash<Node> {
        size_t operator()(const Node &node) const {
            return hash<int>()(node.getId()) ^ hash<string>()(node.getCode());
        }
    };
}

#endif //DA_WATER_SUPPLY_NODE_H
