file(READ "${TARGET_FILE}" FILE_CONTENT)
string(REPLACE "cmake_minimum_required(VERSION 3.1)" "cmake_minimum_required(VERSION 3.10)" FILE_CONTENT "${FILE_CONTENT}")
file(WRITE "${TARGET_FILE}" "${FILE_CONTENT}")
