#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>

using namespace rapidjson;

struct MyData {
    std::vector<Value> nodes;
};

Value create_empty_json() {
    Value empty_json(kObjectType);
    return empty_json;
}

int main() {
 
    MyData my_data;
    
    //inserts it as a node
    my_data.nodes.push_back(create_empty_json());

    return 0;
}
