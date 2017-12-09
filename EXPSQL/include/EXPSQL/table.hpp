//
//  table.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/3/17.
//

#ifndef table_hpp
#define table_hpp

#include <EXPSQL/cursor.hpp>
#include <EXPSQL/row.hpp>
#include <memory>
#include <string>
#include <atomic>

namespace EXP {
namespace sql {

template<const char *name_, typename ...T>
class table
{
public:
    table(std::shared_ptr<cursor> curs);
    
    ~table() = default;
    
    template<typename N, typename X>
    bool commit(X data);
    bool insert();
    bool create();
    bool drop();
    std::atomic<bool> status;
private:
    std::shared_ptr<row<T...>> row_;
    int size;
    std::string name;
    std::shared_ptr<cursor> curs;
    
    void get_size();
    void require();
};
    
//
//  impl
//
    
#include <EXPSQL/table_impl.hpp>
    
}
}

#endif /* table_hpp */
