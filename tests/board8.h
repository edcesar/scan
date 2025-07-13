#ifndef BOARD8_H
#define BOARD8_H
#include <string>
#include <vector>

namespace board8 {

enum Piece { EMPTY=0, WM, WK, BM, BK };
struct Board {
    Piece squares[64];
    int turn; // 0=white 1=black
};

void init(Board& b);
void from_fen(Board& b, const std::string& fen);
int evaluate(const Board& b);
std::vector<std::pair<int,int>> gen_moves(const Board& b);

} // namespace board8

#endif
