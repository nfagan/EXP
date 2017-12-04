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

template<typename ...T>
class table
{
public:
    table(std::shared_ptr<cursor> curs, std::string name)
    {
        this->curs = curs;
        this->name = name;
        row_ = std::make_shared<row<T...>>();
        status = true;
        require();
        get_size();
    }
    
    ~table() = default;
    
    auto get_row()
    {
        return row_;
    }
    
    bool insert()
    {
        return curs->insert(row_, size);
        size++;
    }
    
    std::atomic<bool> status;
private:
    std::shared_ptr<row<T...>> row_;
    int size;
    std::string name;
    std::shared_ptr<cursor> curs;
    
    void get_size()
    {
        if (!status) return;
        status = curs->size(name, &size);
    }
    
    void require()
    {
        if (!status) return;
        status = curs->require(row_, name);
    }
};
    
}
}

#endif /* table_hpp */
