#include "gtest/gtest.h"
#include "src/csvtojson.h"
#include "rapidjson/include/rapidjson/document.h"
#include "src/csvtojson.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "src/json.h"
#include "src/LinkedList.h"

/*
//TEST(s) goes above main
TEST(csvtojson, withoutextension){
  csvtojson c;
  stringstream ss;
  c.printcsv("test1", 3, ss);
 // EXPECT_EQ(ss, "JohnBluetrueBobRedfalseJhonnyGreentrue");
}

TEST(csvtojson, withextension){
  csvtojson c;
  stringstream ss;
  c.printcsv("test1.csv", 3,ss);
  //EXPECT_EQ(ss, "JohnBluetrueBobRedfalseJhonnyGreentrue");
}
*/

/*TEST(JsonTest, ParseErrorTest) {
   // Create a file with a JSON syntax error
  std::ofstream file("data.json");
  file << "{ \"name\": \"John\", \"age\": 30, }"; // Syntax error: trailing comma
  file.close();

  // Call the function being tested
  Json json;
  json.parseError();

  // Check that the function output contains the expected error message
  testing::internal::CaptureStdout();
  json.parseError();
  std::string output = testing::internal::GetCapturedStdout();
  bool hasError = output.find("Error(offset ") != std::string::npos;
  bool hasMissingNameError = output.find("Missing a name") != std::string::npos;
  EXPECT_TRUE(hasError && hasMissingNameError);

  // Remove the test file
  std::remove("data.json");
}*/

/*TEST(JsonTest, WriteJsonTest) {
  Json json;
  json.writeJson();

  // Read the contents of the output file
  std::ifstream inputFile("output.json");
  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  std::string fileContents = buffer.str();

  // Remove tabs from the file contents
  fileContents.erase(std::remove(fileContents.begin(), fileContents.end(), '\t'), fileContents.end());

  // Check that the output file has the right JSON data
  std::string expectedOutput = "{\n\"people\": [{\n\"id\": \"9873e87e879ueid\",\n\"name\": \"Farnaz\",\n\"age\": 23,\n\"college\": \"UC Riverside\"\n}, {\n\"id\": \"98e89r8983009id\",\n\"name\": \"Golnaz\",\n\"age\": 27,\n\"college\": \"UC Berkely\"\n}, {\n\"id\": \"9898378747382id\",\n\"name\": \"Niloofar\",\n\"age\": 30,\n\"college\": \"UCLA\"\n}, {\n\"id\": \"959067fs9d798id\",\n\"name\": \"Muneeb\",\n\"age\": 23,\n\"college\": \"UC Riverside\"\n}]\n}";

  EXPECT_EQ(fileContents, expectedOutput);
}*/

/*TEST(JsonTest, InitializeEMPTYjsonTest) {
  Json json;
  std::string collectionName = "myCollection";
  std::string jsonName = "myJson";
  json.intiializeEMPTYjson(collectionName, jsonName);

  // Check that the file is created
  std::string directory = "Database/" + collectionName + jsonName;
  std::ifstream inputFile(directory);
  bool fileExists = inputFile.good();
  inputFile.close();
  EXPECT_TRUE(fileExists);
}*/

TEST(LinkedList, CheckEmptyList) {
  LinkedList* list = new LinkedList();
  EXPECT_EQ(list->size(), 0);
}
TEST(LinkedList, CorrectListSize) {
  LinkedList* list = new LinkedList();

  pair t = make_pair("Age", "20");
  pair t2 = make_pair("Age", "77");
  pair t3 = make_pair("Age", "13");

  vector<pair<string,string>> vec1;
  vector<pair<string,string>> vec2;
  vector<pair<string,string>> vec3;

  vec1.push_back(t);
  vec2.push_back(t2);
  vec3.push_back(t3);

  list->insertToRear(vec1);
  list->insertToRear(vec2);
  list->insertToRear(vec3);
  EXPECT_EQ(list->size(), 3);
}
TEST(LinkedList, getCorrectVector) {
  LinkedList* list = new LinkedList();

  pair t = make_pair("Age", "20");
  pair t2 = make_pair("Age", "77");
  pair t3 = make_pair("Age", "13");

  vector<pair<string,string>> vec1;
  vector<pair<string,string>> vec2;
  vector<pair<string,string>> vec3;

  vec1.push_back(t);
  vec2.push_back(t2);
  vec3.push_back(t3);

  list->insertToRear(vec1);
  list->insertToRear(vec2);
  list->insertToRear(vec3);

  vector<pair<string,string>> result = list->get(1);
  EXPECT_EQ(result[0].second, "77");
}
TEST(LinkedList, correctDelete) {
  LinkedList* list = new LinkedList();

  pair t = make_pair("Age", "20");
  pair t2 = make_pair("Age", "77");
  pair t3 = make_pair("Age", "13");

  vector<pair<string,string>> vec1;
  vector<pair<string,string>> vec2;
  vector<pair<string,string>> vec3;

  vec1.push_back(t);
  vec2.push_back(t2);
  vec3.push_back(t3);

  list->insertToRear(vec1);
  list->insertToRear(vec2);
  list->insertToRear(vec3);
  list->deleteNode(1);
  EXPECT_EQ(list->size(), 2);
}
// TEST(JSON, Filter)
// {
//   Json* n = new Json("Collection_1", "Data.json");
//   n->filterFunc("Age", {"30"});

//   EXPECT_EQ(n->getResult()->size(), 1);
// }
// TEST(JSON, Sort)
// {
//   Json* n = new Json("Collection_1", "Data.json");
//   //n->sortFunc("Age", 1);

//   //EXPECT_EQ(n->getResult()->get(0)[2].second, "23");
// }


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
