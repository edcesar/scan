
// var.cpp

// includes

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "libmy.hpp"
#include "var.h"

namespace var {

// variables

bool Book;
int  Book_Margin;
bool Ponder;
bool SMP;
int  SMP_Threads;
int  Trans_Size;
bool BB;
int  BB_Size;
std::string Variant;
bool DXP_Server;
std::string DXP_Host;
int  DXP_Port;
bool DXP_Initiator;
int  DXP_Time;
int  DXP_Moves;
bool DXP_Board;
bool DXP_Search;
variant_t Variant;

static std::map<std::string, std::string> Var;

// functions

void init() {

   set("book", "false");
   set("book-margin", "2");
   set("variant", "brazilian");
   set("ponder", "false");
   set("threads", "1");
   set("tt-size", "24");
   set("bb-size", "6");
   set("dxp-server", "true");
   set("dxp-host", "127.0.0.1");
   set("dxp-port", "27531");
   set("dxp-initiator", "false");
   set("dxp-time", "5");
   set("dxp-moves", "75");
   set("dxp-board", "false");
   set("dxp-search", "false");
   set("variant", "international");

   update();
}

void load(const std::string & file_name) {

   std::ifstream file(file_name.c_str());

   if (!file) {
      std::cerr << "unable to open file \"" << file_name << "\"" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   while (true) {

      std::string name;
      file >> name;
      if (file.eof()) break;

      std::string sep;
      file >> sep;
      if (file.eof() || sep != "=") {
         std::cerr << "invalid INI file" << std::endl;
         std::exit(EXIT_FAILURE);
      }

      std::string value;
      file >> value;
      if (file.eof()) {
         std::cerr << "invalid INI file" << std::endl;
         std::exit(EXIT_FAILURE);
      }

      set(name, value);
   }
}

void update() {

   Book          = get_bool("book");
   Book_Margin   = get_int("book-margin");
   Ponder        = get_bool("ponder");
   SMP_Threads   = get_int("threads");
   SMP           = SMP_Threads > 1;
   Trans_Size    = 1 << get_int("tt-size");
   BB_Size       = get_int("bb-size");
   BB            = BB_Size > 0;
   Variant       = get("variant");
   DXP_Server    = get_bool("dxp-server");
   DXP_Host      = get("dxp-host");
   DXP_Port      = get_int("dxp-port");
   DXP_Initiator = get_bool("dxp-initiator");
   DXP_Time      = get_int("dxp-time");
   DXP_Moves     = get_int("dxp-moves");
   DXP_Board     = get_bool("dxp-board");
   DXP_Search    = get_bool("dxp-search");

   std::string var_str = get("variant");
   if (var_str == "international") {
      Variant = International;
   } else if (var_str == "brazilian") {
      Variant = Brazilian;
   } else {
      std::cerr << "unknown variant: " << var_str << std::endl;
      std::exit(EXIT_FAILURE);
   }
}

std::string get(const std::string & name) {

   if (Var.find(name) == Var.end()) {
      std::cerr << "unknown variable: \"" << name << "\"" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   return Var[name];
}

void set(const std::string & name, const std::string & value) {

   Var[name] = value;
}

bool get_bool(const std::string & name) {

   std::string value = get(name);

   if (value == "true") {
      return true;
   } else if (value == "false") {
      return false;
   } else {
      std::cerr << "not a boolean: variable " << name << " = \"" << value << "\"" << std::endl;
      std::exit(EXIT_FAILURE);
      return false;
   }
}

int get_int(const std::string & name) {

   return ml::stoi(get(name));
}

double get_float(const std::string & name) {

   return ml::stof(get(name));
}

}

// end of var.cpp

