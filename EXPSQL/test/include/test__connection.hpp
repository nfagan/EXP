//
//  test__connection.hpp
//  EXPSQL_test
//
//  Created by Nick Fagan on 11/24/17.
//

#ifndef TEST__CONNECTION_H
#define TEST__CONNECTION_H

#include <EXPSQL/connection.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>

using EXP::sql::connection;

void test__connection()
{
    const char *test_file = "test.db";
    
    connection conn(test_file, false);
    
    if (!conn.open())
        std::cout << "FAILED: Expected database to be opened by open operation." << std::endl;
    
    if (!conn.close())
        std::cout << "FAILED: Expected database to be closed by close operation." << std::endl;
    
    std::ifstream test_file_stream(test_file);
    if (test_file_stream.good())
        remove(test_file);
}

#endif
