CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS_INIT "-lstdc++fs")

ADD_SUBDIRECTORY(googletest)
#ADD_SUBDIRECTORY(rapidjson)


ADD_EXECUTABLE(FriendlyCDB
    main.cpp src/gui.cpp src/collection.cpp src/json.cpp src/csv.cpp src/authentication.cpp src/csvtojson.cpp src/LinkedList src/LinkedList.cpp src/encrypt.cpp
)

ADD_EXECUTABLE(test
    unittest.cpp src/gui.cpp src/collection.cpp src/json.cpp src/csv.cpp src/authentication.cpp src/csvtojson.cpp src/LinkedList src/LinkedList.cpp src/encrypt.cpp

 
)

#set(FriendlyCDB "${FriendlyCDB} -std=c++17")
target_link_libraries(FriendlyCDB stdc++fs)
TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
