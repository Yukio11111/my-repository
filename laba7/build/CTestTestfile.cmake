# CMake generated Testfile for 
# Source directory: /workspaces/my-repository/laba7
# Build directory: /workspaces/my-repository/laba7/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(VariantTests "/workspaces/my-repository/laba7/build/variant_tests")
set_tests_properties(VariantTests PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/my-repository/laba7/CMakeLists.txt;25;add_test;/workspaces/my-repository/laba7/CMakeLists.txt;0;")
subdirs("_deps/catch2-build")
