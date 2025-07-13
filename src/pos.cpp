
// pos.cpp

// includes

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bit.h"
#include "board.h"
#include "fen.h"
#include "libmy.hpp"
#include "move.h"
#include "move_gen.h"
#include "pos.h"
#include "util.h"
#include "var.h"

// geometry variables (initialised according to variant)
int Square_Size = 66;
int Square_Count = 50;
int Square_From_50[50];
int Square_To_50[Square_Size_Max];
int Square_File[Square_Size_Max];
int Square_Rank[Square_Size_Max];
int Inc[Dir_Size];

void pos_init_geometry() {

   int n = (var::Variant == var::Brazilian) ? 4 : 5;
   Square_Count = 2 * n * n;
   int W = 2 * n + 1;
   Square_Size = W * (n + 1);

   // init arrays
   for (int i = 0; i < 50; i++) Square_From_50[i] = -1;
   for (int i = 0; i < Square_Size_Max; i++) {
      Square_To_50[i] = -1;
      Square_File[i] = -1;
      Square_Rank[i] = -1;
   }

   int idx = 0;
   for (int g = 0; g < n; g++) {
      int rowA = n + 1 + g * W;
      int rowB = rowA + n;

      for (int i = 0; i < n; i++) {
         int sq = rowA + i;
         Square_From_50[idx] = sq;
         Square_To_50[sq] = idx;
         Square_File[sq] = 2 * i + 1;
         Square_Rank[sq] = 2 * g;
         idx++;
      }
      for (int i = 0; i < n; i++) {
         int sq = rowB + i;
         Square_From_50[idx] = sq;
         Square_To_50[sq] = idx;
         Square_File[sq] = 2 * i;
         Square_Rank[sq] = 2 * g + 1;
         idx++;
      }
   }

   Inc[NW] = -(n + 1);
   Inc[NE] = -n;
   Inc[SW] = +n;
   Inc[SE] = +(n + 1);
}

// functions

std::string square_to_string(int sq) {

   return ml::itos(square_to_50(sq) + 1);
}

bool string_is_square(const std::string & s) {

   if (!string_is_nat(s)) return false;

   int sq = ml::stoi(s);
   return sq >= 1 && sq <= Square_Count;
}

int square_from_string(const std::string & s) {

   if (!string_is_nat(s)) throw Bad_Input();
   return square_from_int(ml::stoi(s));
}

int square_from_int(int sq) {

   if (sq < 1 || sq > Square_Count) throw Bad_Input();
   return square_from_50(sq - 1);
}

void Pos::copy(const Pos & pos) {

   init(pos.p_turn, pos.p_piece[White], pos.p_piece[Black], pos.p_king);
}

void Pos::init() {

   pos_from_fen(*this, start_fen());
}

void Pos::init(int turn, bit_t wp, bit_t bp, bit_t k) {

   assert((wp & bp) == 0);
   assert(bit_incl(k, wp | bp));

   p_turn = turn;
   p_piece[White] = wp;
   p_piece[Black] = bp;
   p_king = k;
}

void Pos::from_bit(int turn, bit_t wm, bit_t bm, bit_t wk, bit_t bk) {

   init(turn, wm | wk, bm | bk, wk | bk);
}

extern void pos_rev(Pos & dst, const Pos & src) {

   dst.init(side_opp(src.turn()), bit_rev(src.piece(Black)), bit_rev(src.piece(White)), bit_rev(src.king()));
}

void pos_do_move(Pos & dst, const Pos & src, move_t mv) {

   int from = move_from(mv);
   int to = move_to(mv);
   bit_t captured = move_captured(mv);

   int atk = src.turn();
   int def = side_opp(atk);

   assert(bit_test(src.piece(atk), from));
   assert(from == to || bit_test(src.empty(), to));
   assert(bit_incl(captured, src.piece(def)));

   bit_t piece[Side_Size] = { src.piece(White), src.piece(Black) };
   bit_t king = src.king();

   bit_clear(piece[atk], from);
   bit_set(piece[atk], to);

   if (bit_test(src.man(), from)) { // man move

      if (square_is_promotion(to, atk)) {
         bit_set(king, to);
      }

   } else { // king move

      assert(bit_test(king, from));

      bit_clear(king, from);
      bit_set(king, to);
   }

   piece[def] &= ~captured;
   king       &= ~captured;

   dst.init(def, piece[White], piece[Black], king);
}

bool pos_is_capture(const Pos & pos) {

   return can_capture(pos, pos.turn());
}

int pos_size(const Pos & pos) {

   int nw = bit_count(pos.piece(White));
   int nb = bit_count(pos.piece(Black));

   return nw + nb;
}

bool pos_has_king(const Pos & pos) {

   return pos.king() != 0;
}

int pos_square(const Pos & pos, int sq) {

   assert(square_is_ok(sq));

   if (false) {
   } else if (bit_test(pos.empty(), sq)) {
      return Empty;
   } else if (bit_test(pos.wm(), sq)) {
      return WM;
   } else if (bit_test(pos.bm(), sq)) {
      return BM;
   } else if (bit_test(pos.wk(), sq)) {
      return WK;
   } else if (bit_test(pos.bk(), sq)) {
      return BK;
   } else {
      assert(false);
      return Frame;
   }
}

// end of pos.cpp

