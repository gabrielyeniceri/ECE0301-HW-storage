#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>

#include "Database.hpp"

const double THRESHOLD = 1e-9;

/* Provided test cases */

TEST_CASE("Test default construction", "[database]"){
    Database db;
    REQUIRE(db.is_empty());
    REQUIRE(db.size() == 0);

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == 0);
}

TEST_CASE("Test construction with one Entry", "[database]"){
    // Sun data
    // id, name, mass
    Entry test_entry = {10, "Sun", 1988500e24};
    Database db(test_entry);
    REQUIRE_FALSE(db.is_empty());
    REQUIRE(db.size() == 1);

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == 1);
    REQUIRE(test[0].id == test_entry.id);
    REQUIRE(test[0].name == test_entry.name);
    REQUIRE(std::abs(test[0].mass - test_entry.mass) <= THRESHOLD);
}

TEST_CASE("Test construction with vector", "[database]"){
    // id, name, mass
    std::vector<Entry> entries = {{10, "Sun", 1988500e24},
                        {199, "Mercury", 0.330103e24}, 
                        {299, "Venus", 4.86731e24},
                        {399, "Earth", 5.97217e24},
                        {499, "Mars", 0.641691e24}};
    Database db(entries);
    REQUIRE_FALSE(db.is_empty());
    REQUIRE(db.size() == entries.size());

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == entries.size());
    for (int i=0; i<entries.size(); i++) {
        REQUIRE(test[i].id == entries[i].id);
        REQUIRE(test[i].name == entries[i].name);
        REQUIRE(std::abs(test[i].mass - entries[i].mass) <= THRESHOLD);
    }
}


TEST_CASE("Test search", "[database]"){
    // id, name, mass
    std::vector<Entry> entries = {{10, "Sun", 1988500e24},
                        {199, "Mercury", 0.330103e24}, 
                        {299, "Venus", 4.86731e24},
                        {399, "Earth", 5.97217e24},
                        {499, "Mars", 0.641691e24}};

    Database dbdefault;
    for (int i=0; i<entries.size(); i++) {
        REQUIRE_FALSE(dbdefault.search(entries[i].id));
    }

    Database dbentry(entries[0]);
    REQUIRE(dbentry.search(entries[0].id));

    Database db(entries);
    for (int i=0; i<entries.size(); i++) {
        REQUIRE(db.search(entries[i].id));
    }
}

TEST_CASE("Test sort by id", "[database]"){
    // id, name, mass
    std::vector<Entry> entries = {{10, "Sun", 1988500e24},
                        {199, "Mercury", 0.330103e24}, 
                        {299, "Venus", 4.86731e24},
                        {399, "Earth", 5.97217e24},
                        {499, "Mars", 0.641691e24}};
    Database db;
    int idxs[5] = {3, 0, 2, 1, 4};
    // add out of order
    for (int i : idxs) {
        db.add(entries[i]);
    }

    // check initial order
    std::vector<Entry> test = db.get_all_entries();
    for (int i=0; i<5; i++) {
        REQUIRE(test[i].id == entries[idxs[i]].id);
        REQUIRE(test[i].name == entries[idxs[i]].name);
        REQUIRE(std::abs(test[i].mass - entries[idxs[i]].mass) <= THRESHOLD);
    }
    
    // sort ascending
    db.sort_by_id();
    test = db.get_all_entries();
    for (int i=0; i<5; i++) {
        REQUIRE(test[i].id == entries[i].id);
        REQUIRE(test[i].name == entries[i].name);
        REQUIRE(std::abs(test[i].mass - entries[i].mass) <= THRESHOLD);
    }
}

