include_directories(${gtest_SOURCE_DIR}/include)

set(test_sources
 libTest.cpp
 ../performance/systemStat.cpp
 ../url/url_parser.c
 ../cryptography/aesCrypto.cpp
)

add_executable(all_tests ${test_sources})

target_link_libraries(all_tests gtest_main crypto)
