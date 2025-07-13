
// fen.h

#ifndef FEN_H
#define FEN_H

// includes

#include <string>

#include "libmy.hpp"

class Pos;

// constants
const std::string Start_FEN_International = "W:W31-50:B1-20";
const std::string Start_FEN_Brazilian    = "W:W21-32:B1-12";
const std::string Start_Hub = "wbbbbbbbbbbbbbbbbbbbbeeeeeeeeeewwwwwwwwwwwwwwwwwww";
const std::string Start_DXP = "Wzzzzzzzzzzzzzzzzzzzzeeeeeeeeeewwwwwwwwwwwwwwwwwww";

const std::string & start_fen();
// functions

extern void pos_from_fen (Pos & pos, const std::string & s);
extern void pos_from_hub (Pos & pos, const std::string & s);
extern void pos_from_dxp (Pos & pos, const std::string & s);

extern std::string pos_fen (const Pos & pos);
extern std::string pos_hub (const Pos & pos);
extern std::string pos_dxp (const Pos & pos);

#endif // !defined FEN_H

// end of fen.h

