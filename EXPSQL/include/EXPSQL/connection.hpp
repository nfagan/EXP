//
//  connection.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/15/17.
//

#ifndef connection_hpp
#define connection_hpp

#include <string>
#include <memory>

struct sqlite3;

namespace EXP {
namespace sql {

class cursor;

class connection
{
friend class cursor;
public:
    connection(std::string file, bool open = true);
    ~connection();
    
    bool is_open() const;
    bool open();
    bool close();
    
    std::shared_ptr<cursor> get_cursor() const;
private:
    sqlite3 *db;
    std::string file;
    bool is_open_;
    
    bool exec(const std::string &query) const;
};

}
}

#endif /* connection_hpp */
