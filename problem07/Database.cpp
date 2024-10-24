#include "Database.hpp"

// initializes the number of entries to 0, constructor
Database::Database() : num_entries(0) {}

// adds to database
Database::Database(const Entry& entry) {
    entries.push_back(entry);
    num_entries = 1;
}
Database::Database(const std::vector<Entry>& entries_vec) : entries(entries_vec), num_entries(entries_vec.size()) {}

bool Database::add(const Entry& entry) {
    // checks if it already exists and returns false if true
    for (const auto& e : entries) {
        if (e.id == entry.id) {
            return false;
        }
    }
    entries.push_back(entry);
    num_entries++;
    return true;
}

// removes, and returns true, if not found it returns false
bool Database::remove(int id) {
    for (auto it = entries.begin(); it != entries.end(); ++it) {
        if (it->id == id) {
            entries.erase(it);
            num_entries--;
            return true;
        }
    }
    return false;
}

// returns the number of entries
int Database::size() const {
    return num_entries;
}

// checks if the database is empty, returns false if not
bool Database::is_empty() const {
    return num_entries == 0;
}

// returns true if it finds a specified entry
bool Database::search(int id) const {
    for (const auto& e : entries) {
        if (e.id == id) {
            return true;
        }
    }
    return false;
}
std::vector<Entry> Database::get_all_entries() const {
    return entries;
}

//bubble sort
void Database::sort_by_id(bool ascending) {
    bool swapped;
    for (size_t i = 0; i < entries.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < entries.size() - i - 1; ++j) {
            if (ascending) {
                if (entries[j].id > entries[j + 1].id) {
                    std::swap(entries[j], entries[j + 1]);
                    swapped = true;
                }
            } else {
                if (entries[j].id < entries[j + 1].id) {
                    std::swap(entries[j], entries[j + 1]);
                    swapped = true;
                }
            }
        }
        if (!swapped) {
            break;
        }
    }
}
