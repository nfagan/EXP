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
#include <functional>
#include <atomic>
#include <EXPUtil/io/logger.hpp>

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
            bool begin();
            bool commit();
            
            void log_level(EXP::severity::severity_ level);
            
            std::shared_ptr<cursor> get_cursor() const;
            static std::string require_quoted_text(const char *qstring, const std::string &values);
        private:
            sqlite3 *db;
            std::string file;
            std::atomic<bool> is_open_;
            std::atomic<bool> is_transacting_;
            logger log;
            
            bool exec(const std::string &query, std::string *result) const;
            bool exec_to_int(const std::string &query, int *result) const;
            void exists(const std::string &name, bool *err, bool *exist) const;
            void size(const std::string &name, bool *err, int *sz) const;
            bool drop(const std::string &name) const;
            
            static int sqlite_callback(void *data, int argc, char *argv[], char *col_namep[]);
        };
    }
}

#endif /* connection_hpp */
