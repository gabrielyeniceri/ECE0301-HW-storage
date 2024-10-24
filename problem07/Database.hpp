#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <string>
#include <vector>

struct Entry {
    int id;
    std::string name;
    double mass;
};

class Database {
private:
    std::vector<Entry> entries;
    int num_entries;

public:
    Database();

    Database(const Entry& entry);

    Database(const std::vector<Entry>& entries_vec);

    bool add(const Entry& entry);

    bool remove(int id);

    int size() const;

    bool is_empty() const;

    bool search(int id) const;

    std::vector<Entry> get_all_entries() const;

    void sort_by_id(bool ascending = true);

};

#endif
