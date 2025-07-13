#include "board.h"
#include "fen.h"
#include "move_gen.h"
#include "list.h"
#include "board8.h"
#include <iostream>
#include <vector>
#include <string>

#define ASSERT_TRUE(cond) do { if(!(cond)) { std::cerr << "FAIL:" << __FILE__ << ":" << __LINE__ << " " << #cond << std::endl; return false; } } while(0)

bool test_fen10() {
    Board bd;
    board_from_fen(bd, Start_FEN);
    std::string s = pos_fen(bd);
    ASSERT_TRUE(s == Start_FEN);
    return true;
}

bool test_movegen10() {
    Board bd;
    board_from_fen(bd, Start_FEN);
    List list;
    gen_moves(list, bd);
    ASSERT_TRUE(list.size() == 9);
    return true;
}

bool test_fen8() {
    board8::Board bd;
    board8::from_fen(bd, "W:W21-32:B1-12");
    ASSERT_TRUE(bd.turn == 0);
    return true;
}

bool test_movegen8() {
    board8::Board bd;
    board8::from_fen(bd, "W:W21-32:B1-12");
    auto mv = board8::gen_moves(bd);
    ASSERT_TRUE(mv.size() == 7);
    return true;
}

bool test_eval8() {
    board8::Board bd;
    board8::from_fen(bd, "W:W22:B11");
    int sc = board8::evaluate(bd);
    ASSERT_TRUE(sc == 0);
    return true;
}

int main() {
    int fails=0;
    if(!test_fen10()) fails++;
    if(!test_movegen10()) fails++;
    if(!test_fen8()) fails++;
    if(!test_movegen8()) fails++;
    if(!test_eval8()) fails++;
    if(fails==0) std::cout << "All tests passed" << std::endl;
    else std::cout << fails << " tests failed" << std::endl;
    return fails;
}

