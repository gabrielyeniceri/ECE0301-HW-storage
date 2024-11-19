#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Agent.hpp"
#include "Flora.hpp"
#include "Prey.hpp"
#include "Predator.hpp"
#include "Grid.hpp"
#include "Simulator.hpp"

/* 
=======================================================================
    Provided test cases 
=======================================================================
*/

/* Flora unit tests */
TEST_CASE("Simulator: Test Flora energy", "[simulator]"){
    Flora f;
    REQUIRE(f.get_type() == VEGETATION);
    REQUIRE(f.get_energy() == Flora::PHOTO_ENERGY);
    REQUIRE_FALSE(f.can_act());

    f.energize(0);
    REQUIRE(f.get_energy() == 2*Flora::PHOTO_ENERGY);
    f.energize(0);
    REQUIRE(f.get_energy() == 3*Flora::PHOTO_ENERGY);
    f.energize(0);
    REQUIRE(f.get_energy() == 4*Flora::PHOTO_ENERGY);
    f.energize(0);
    REQUIRE(f.get_energy() == 5*Flora::PHOTO_ENERGY);
}

TEST_CASE("Simulator: Test Flora energy constructor", "[simulator]"){

    int start = 5*Flora::PHOTO_ENERGY;
    Flora f(start);
    REQUIRE(f.get_type() == VEGETATION);
    REQUIRE(f.get_energy() == start);
    REQUIRE(f.action() == LEFT);
    REQUIRE(f.act());
    REQUIRE(f.get_energy() == start-Flora::GROW_ENERGY);
    REQUIRE(f.action() == UP);
    f.energize(0);
    REQUIRE(f.get_energy() == start-Flora::GROW_ENERGY+Flora::PHOTO_ENERGY);
}

TEST_CASE("Simulator: Test Flora actions", "[simulator]"){
    Flora f;
    f.energize(4*Flora::GROW_ENERGY);
    // test actions
    REQUIRE(f.action() == LEFT);
    REQUIRE(f.can_act());
    REQUIRE(f.act());
    f.energize(Flora::GROW_ENERGY);
    REQUIRE(f.action() == UP);
    REQUIRE(f.can_act());
    REQUIRE(f.act());
    f.energize(Flora::GROW_ENERGY);
    REQUIRE(f.action() == RIGHT);
    REQUIRE(f.can_act());
    REQUIRE(f.act());
    f.energize(Flora::GROW_ENERGY);
    REQUIRE(f.action() == DOWN);
    REQUIRE(f.can_act());
    REQUIRE(f.act());
    f.energize(Flora::GROW_ENERGY);
    REQUIRE(f.action() == LEFT);

    // test next_action
    REQUIRE(f.next_action() == UP);
    REQUIRE(f.action() == UP);
    REQUIRE(f.next_action() == RIGHT);
    REQUIRE(f.action() == RIGHT);
    REQUIRE(f.next_action() == DOWN);
    REQUIRE(f.action() == DOWN);
    REQUIRE(f.next_action() == LEFT);
    REQUIRE(f.action() == LEFT);

}

/* Prey unit tests */
TEST_CASE("Simulator: Test Prey actions", "[simulator]"){
    Prey p;
    int start = 4*Prey::MOVE_ENERGY;
    REQUIRE(p.get_type() == PREY);
    REQUIRE(p.get_energy() == start);
    REQUIRE(p.action() == UP);
    REQUIRE(p.act());
    REQUIRE(p.get_energy() == start-Prey::MOVE_ENERGY);
    REQUIRE(p.action() == LEFT);
    REQUIRE(p.act());
    REQUIRE(p.get_energy() == start-2*Prey::MOVE_ENERGY);
    REQUIRE(p.action() == UP);
    REQUIRE(p.act());
    REQUIRE(p.get_energy() == start-3*Prey::MOVE_ENERGY);
    REQUIRE(p.action() == LEFT);
    REQUIRE(p.act());
    REQUIRE(p.get_energy() == 0);

    // test next action
    REQUIRE(p.action() == UP);
    REQUIRE(p.next_action() == LEFT);
    REQUIRE(p.action() == LEFT);
    REQUIRE(p.next_action() == UP);

}

TEST_CASE("Simulator: Test more Prey actions", "[simulator]"){
    // test energy constructor and movement below MOVE_ENERGY
    Prey p(Prey::MOVE_ENERGY-1);
    REQUIRE(p.get_type() == PREY);
    REQUIRE(p.get_energy() == Prey::MOVE_ENERGY-1);
    REQUIRE(p.action() == UP);
    REQUIRE(p.act());
    REQUIRE(p.get_energy() == 0);

    // test energize 
    p.energize(2*Prey::MOVE_ENERGY);
    REQUIRE(p.action() == LEFT);
    REQUIRE(p.act());
    REQUIRE(p.get_energy() == Prey::MOVE_ENERGY);
    REQUIRE(p.action() == UP);
}

/* Grid tests */
TEST_CASE("Simulator: Test Grid with ints", "[simulator]"){
    Grid<int> g;
    REQUIRE(g.get_size() == Grid<int>::DEFAULT_SIZE);
    bool check = true;
    for (int r=0; r<Grid<int>::DEFAULT_SIZE; r++) {
        for (int c=0; c<Grid<int>::DEFAULT_SIZE; c++) {
            check = g.get_cell(Location{r,c}) == nullptr;
            if (!check) {
                break;
            }
        }
        if (!check) {
            break;
        }
    }
    REQUIRE(check);

    Location loc{5,7};
    g.set_cell(loc, new int(5));
    REQUIRE(g.get_cell(Location{0,0}) == nullptr);
    REQUIRE(*g.get_cell(loc) == 5);
}

TEST_CASE("Simulator: Test Grid with Agents", "[simulator]"){    
    Grid<Agent> g;
    REQUIRE(g.get_size() == Grid<Agent>::DEFAULT_SIZE);
    bool check = true;
    for (int r=0; r<Grid<Agent>::DEFAULT_SIZE; r++) {
        for (int c=0; c<Grid<Agent>::DEFAULT_SIZE; c++) {
            check = g.get_cell(Location{r,c}) == nullptr;
            if (!check) {
                break;
            }
        }
        if (!check) {
            break;
        }
    }
    REQUIRE(check);

    // test get out of bounds
    REQUIRE_THROWS_AS(g.get_cell(Location{Grid<Agent>::DEFAULT_SIZE, 0}), std::out_of_range);
    REQUIRE_THROWS_AS(g.get_cell(Location{0, Grid<Agent>::DEFAULT_SIZE}), std::out_of_range);

    // test size constructor
    int size = 20;
    Grid<Agent> g2(size);
    REQUIRE(g2.get_size() == size);
    for (int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
            check = g2.get_cell(Location{r,c}) == nullptr;
            if (!check) {
                break;
            }
        }
        if (!check) {
            break;
        }
    }
    REQUIRE(check);
    // test get out of bounds
    REQUIRE_THROWS_AS(g2.get_cell(Location{size, 0}), std::out_of_range);
    REQUIRE_THROWS_AS(g2.get_cell(Location{0, size}), std::out_of_range);

    // test set_cell
    Flora* f = new Flora();
    Location loc{10,15};
    g2.set_cell(loc, f);
    REQUIRE(g2.get_cell(loc) == f);
    REQUIRE(g2.get_cell(loc)->action() == LEFT);

    // test set out of bounds
    REQUIRE_THROWS_AS(g2.set_cell(Location{size, 0}, f), std::out_of_range);
    REQUIRE_THROWS_AS(g2.set_cell(Location{0, size}, f), std::out_of_range);

    // test move
    Location mov{11,15};
    REQUIRE(g2.move(loc, mov));
    REQUIRE(g2.get_cell(mov) == f);
    // place a new flora at the "from" location, test that it can't move onto f
    Flora* f2 = new Flora();
    g2.set_cell(loc, f2);
    REQUIRE_FALSE(g2.move(loc, mov));

    // test clear
    g2.clear();
    for (int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
            check = g2.get_cell(Location{r,c}) == nullptr;
            if (!check) {
                break;
            }
        }
        if (!check) {
            break;
        }
    }
    REQUIRE(check);

    // test resize
    int new_size = 30;
    g2.resize(new_size);
    for (int r=0; r<new_size; r++) {
        for (int c=0; c<new_size; c++) {
            check = g2.get_cell(Location{r,c}) == nullptr;
            if (!check) {
                break;
            }
        }
        if (!check) {
            break;
        }
    }
    REQUIRE(check);

    // flora ptrs are deallocated with the clear/resize
}

/* Simulator tests */
TEST_CASE("Simulator: Test Simulator empty grid", "[simulator]"){ 
    // default construction
    Simulator s;
    REQUIRE(s.size() == Grid<Agent>::DEFAULT_SIZE);

    // test done state, should be done if empty
    REQUIRE(s.done());

    // invalid size should throw due to grid
    REQUIRE_THROWS_AS(Simulator(-1), std::invalid_argument);
}

TEST_CASE("Simulator: Test Simulator set Flora", "[simulator]"){ 
    Simulator s;
    // add flora
    Location flora_loc = Location{1,1};
    REQUIRE(s.set(flora_loc, VEGETATION));
    REQUIRE(s.get_type(flora_loc) == VEGETATION);

    // cannot stack agents
    REQUIRE_FALSE(s.set(flora_loc, VEGETATION));
    // cannot add invalid agent type
    REQUIRE_FALSE(s.set(Location{0,0}, NONE));

    // test done - should be done if only vegetation
    REQUIRE(s.done());

    // example of exporting an image of the simulation grid state
    s.export_image("output.bmp");
}

TEST_CASE("Simulator: Test Simulator Flora actions", "[simulator]"){ 
    Simulator s;
    Location flora_loc = Location{1,1};
    REQUIRE(s.set(flora_loc, VEGETATION));
    // test energize and update(grow), should generate vegetation in adjacent cell
    s.energize(flora_loc, 4*Flora::GROW_ENERGY);
    s.update(); // grow left
    REQUIRE(s.get_type(flora_loc) == VEGETATION); // original stays
    Location left_cell {flora_loc.row, flora_loc.col-1};
    REQUIRE(s.get_type(left_cell) == VEGETATION); // new growth
    s.update(); // grow up
    REQUIRE(s.get_type(flora_loc) == VEGETATION); // original stays
    Location up_cell {flora_loc.row-1, flora_loc.col};
    REQUIRE(s.get_type(up_cell) == VEGETATION); // new growth
    s.update(); // grow right
    REQUIRE(s.get_type(flora_loc) == VEGETATION); // original stays
    Location right_cell {flora_loc.row, flora_loc.col+1};
    REQUIRE(s.get_type(up_cell) == VEGETATION); // new growth
    s.update(); // grow down
    REQUIRE(s.get_type(flora_loc) == VEGETATION); // original stays
    Location down_cell {flora_loc.row+1, flora_loc.col};
    REQUIRE(s.get_type(down_cell) == VEGETATION); // new growth
}

TEST_CASE("Simulator: Test Simulator Flora set and remove", "[simulator]"){ 
    Simulator s;
    Location flora_loc = Location{1,1};
    Location left_cell {flora_loc.row, flora_loc.col-1};
    Location up_cell {flora_loc.row-1, flora_loc.col};
    REQUIRE(s.set(flora_loc, VEGETATION));
    s.energize(flora_loc, 2*Flora::GROW_ENERGY);
    s.update(); // grow left
    s.update(); // grow up
    // test remove
    REQUIRE_FALSE(s.remove(Location{0,0})); // no agent here
    REQUIRE(s.remove(flora_loc));
    REQUIRE(s.get_type(flora_loc) == NONE);
    REQUIRE(s.remove(left_cell));
    REQUIRE(s.get_type(left_cell) == NONE);
    REQUIRE(s.remove(up_cell));
    REQUIRE(s.get_type(up_cell) == NONE);
}   

TEST_CASE("Simulator: Test Simulator Prey movement", "[simulator]"){ 
    // test update (prey movement)
    Simulator s;
    Location prey_start = Location{4,5};
    REQUIRE(s.set(prey_start, PREY));
    REQUIRE(s.get_type(prey_start) == PREY);

    // simulation is not done becuase there is prey
    REQUIRE_FALSE(s.done());

    // test that prey moves and previous cell is cleared on move
    s.update(); // prey moves up
    Location prey_move_1 {prey_start.row-1, prey_start.col};
    REQUIRE(s.get_type(prey_move_1) == PREY);
    REQUIRE(s.get_type(prey_start) == NONE);

    s.update(); // prey moves left
    Location prey_move_2 {prey_start.row-1, prey_start.col-1};
    REQUIRE(s.get_type(prey_move_2) == PREY);
    REQUIRE(s.get_type(prey_move_1) == NONE);
    REQUIRE(s.get_type(prey_start) == NONE);

    s.update(); // prey moves up
    Location prey_move_3 {prey_start.row-2, prey_start.col-1};
    REQUIRE(s.get_type(prey_move_3) == PREY);
    REQUIRE(s.get_type(prey_move_2) == NONE);
    REQUIRE(s.get_type(prey_move_1) == NONE);
    REQUIRE(s.get_type(prey_start) == NONE);

    s.update(); // prey moves left
    Location prey_move_4 {prey_start.row-2, prey_start.col-2};
    REQUIRE(s.get_type(prey_move_4) == PREY);
    REQUIRE(s.get_type(prey_move_3) == NONE);
    REQUIRE(s.get_type(prey_move_2) == NONE);
    REQUIRE(s.get_type(prey_move_1) == NONE);
    REQUIRE(s.get_type(prey_start) == NONE);
}

/* 
=======================================================================
    TODO: Your test cases here
=======================================================================
*/