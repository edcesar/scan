#include "board8.h"
#include <sstream>
#include <cstring>
#include <cstdlib>

namespace board8 {

static int idx_from_num(int n) {
    int row = (n-1)/4;
    int col = ((n-1)%4)*2 + ((row+1)%2);
    return row*8 + col;
}

void init(Board& b) {
    for(int i=0;i<64;i++) b.squares[i]=EMPTY;
    b.turn=0;
}

static void add_piece(Board& b,bool white,bool king,int num) {
    int idx=idx_from_num(num);
    if(white) b.squares[idx]= king?WK:WM; else b.squares[idx]= king?BK:BM;
}

static void parse_side(Board& b,const std::string& part,bool white) {
    std::stringstream ss(part);
    std::string token;
    while(std::getline(ss, token, ',')) {
        if(token.empty()) continue;
        bool king=false;
        if(token[0]=='K') { king=true; token=token.substr(1); }
        size_t dash = token.find('-');
        if(dash==std::string::npos) {
            int num=std::atoi(token.c_str());
            add_piece(b,white,king,num);
        } else {
            int from=std::atoi(token.substr(0,dash).c_str());
            int to=std::atoi(token.substr(dash+1).c_str());
            for(int n=from;n<=to;n++) add_piece(b,white,king,n);
        }
    }
}

void from_fen(Board& b,const std::string& fen) {
    init(b);
    size_t pos=0;
    b.turn = (fen[pos]=='W')?0:1;
    size_t w = fen.find(":W");
    size_t bpos = fen.find(":B", w+2);
    std::string wpart = fen.substr(w+2, bpos-(w+2));
    std::string bpart = fen.substr(bpos+2);
    parse_side(b,wpart,true);
    parse_side(b,bpart,false);
}

static bool on_board(int r,int c){ return r>=0 && r<8 && c>=0 && c<8; }

std::vector<std::pair<int,int>> gen_moves(const Board& b) {
    std::vector<std::pair<int,int>> moves;
    int sd=b.turn;
    int dir = sd==0?-1:1; // white moves up (-1)
    bool must=false;
    for(int idx=0; idx<64; idx++) {
        Piece pc=b.squares[idx];
        if((sd==0 && (pc==WM||pc==WK)) || (sd==1 && (pc==BM||pc==BK))) {
            int r=idx/8,c=idx%8;
            int dirs[4][2]={{dir,-1},{dir,1},{-dir,-1},{-dir,1}};
            for(int k=0;k<4;k++) {
                if(pc!=WK && pc!=BK && k>=2) break; // men only forward
                int nr=r+dirs[k][0];
                int nc=c+dirs[k][1];
                if(!on_board(nr,nc)) continue;
                int nidx=nr*8+nc;
                if(b.squares[nidx]==EMPTY) {
                    if(!must) moves.push_back({idx,nidx});
                } else {
                    int jr=nr+dirs[k][0];
                    int jc=nc+dirs[k][1];
                    if(on_board(jr,jc)) {
                        int jidx=jr*8+jc;
                        Piece op=b.squares[nidx];
                        if(((sd==0 && (op==BM||op==BK))||(sd==1 && (op==WM||op==WK))) && b.squares[jidx]==EMPTY) {
                            if(!must) { moves.clear(); must=true; }
                            moves.push_back({idx,jidx});
                        }
                    }
                }
            }
        }
    }
    return moves;
}

int evaluate(const Board& b) {
    int w=0,bk=0;
    for(int i=0;i<64;i++) {
        switch(b.squares[i]) {
            case WM: w+=100; break;
            case WK: w+=175; break;
            case BM: bk-=100; break;
            case BK: bk-=175; break;
            default: break;
        }
    }
    return w+bk;
}

} // namespace board8

