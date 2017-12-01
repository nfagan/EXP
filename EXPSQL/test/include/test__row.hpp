//
//  test__row.hpp
//  EXPSQL_test
//
//  Created by Nick Fagan on 11/24/17.
//

#ifndef test__row_h
#define test__row_h

#include <EXPSQL/field.hpp>
#include <EXPSQL/row.hpp>
#include <EXPSQL/cursor.hpp>
#include <string>

using EXP::sql::connection;
using EXP::sql::cursor;
using EXP::sql::field;
using EXP::sql::row;
using std::string;

namespace ft {
    typedef field<int> fieldi;
    typedef field<float> fieldf;
    typedef field<string> fieldstr;

    typedef row<fieldi, fieldi, fieldi, fieldf, fieldstr> DATA;
    typedef row<fieldi> ERRORS;
}

namespace tables {
    const std::string data = "data";
    const std::string errors = "errors";
}

std::shared_ptr<ft::DATA> create_data_row()
{
    field<int> f1("field1", 1000);
    field<int> f2("field2", 20);
    field<int> f3("field3", 10);
    field<float> f5("field5", 3.3f);
    field<string> f6("field6", "hi   there");
    
    return std::make_shared<ft::DATA>(f1, f2, f3, f5, f6);
}

std::shared_ptr<ft::ERRORS> create_error_row()
{
    field<int> f1("field1", 1);
    return std::make_shared<ft::ERRORS>(f1);
}

void test_row()
{
    
    const char *test_file = "test1.db";
    
    connection conn(test_file);
    std::shared_ptr<cursor> curs = conn.get_cursor();
    
    auto data = create_data_row();
    auto errors = create_error_row();
    auto &f1 = data->get<0>();
    auto &f2 = data->get<1>();
    
    bool status;
    
    status = curs->create(data, tables::data);
    status = curs->create(errors, tables::errors);
                          
    status = curs->insert(data, 0, tables::data);
    status = curs->insert(data, 1, tables::data);
    status = curs->insert(data, 2, tables::data);
    
    status = curs->insert(errors, 0, tables::errors);
    
    if (!f1.did_commit)
    {
        std::cout << "FAILED: Committing data did not register as having been committed." << std::endl;
    }
    else
    {
        std::cout << "OK: Committed data were registered as committed." << std::endl;
    }
    
    try {
        f1.commit(100);
        std::cout << "FAILED: Committed data after already comitting data." << std::endl;
    } catch (...) {
        std::cout << "OK: Failed to commit data after already committing data." << std::endl;
    }
    
    try {
        f2.commit(200);
        std::cout << "FAILED: Committed data after already comitting data." << std::endl;
    } catch (...) {
        std::cout << "OK: Failed to commit data after already committing data." << std::endl;
    }
    
    data->reset();
    errors->reset();
    
    if (f1.did_commit)
    {
        std::cout << "FAILED: Expected resetted data to not be committed." << std::endl;
    }
    else
    {
        std::cout << "OK: Resetted data were registered as not committed." << std::endl;
    }
    
    /*std::ifstream test_file_stream(test_file);
    if (test_file_stream.good());
        remove(test_file);*/
}

#endif /* test__row_h */
