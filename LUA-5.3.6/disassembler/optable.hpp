#pragma once
#include "imports.hpp"
#include <map>
#include <vector>

namespace kosmic::lua::ver_5_3_6::optable {

      enum class operand_encoding {
            A,
            B,
            Bx,
            Ax,
            C,
            sBx
      };

      enum class operand_kind {
            dest,
            reg,
            k_idx,
            val,
            jmp,
            upvalue,
            uenv,
            table_size,
            val_multret,
            p_idx
      };

     struct optable_encoding {
            OpCode op;
            std::vector<operand_encoding> encodings;
      };
      static std::map<OpCode, optable_encoding> opencodings = {
          {OpCode::OP_MOVE, {OpCode::OP_MOVE, {operand_encoding::A, operand_encoding::B}}},                              /* 0 */
          {OpCode::OP_LOADK, {OpCode::OP_LOADK, {operand_encoding::A, operand_encoding::Bx}}},                           /* 1 */
          {OpCode::OP_LOADKX, {OpCode::OP_LOADKX, {operand_encoding::Ax}}},                                              /* 2 */
          {OpCode::OP_LOADBOOL, {OpCode::OP_LOADBOOL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 3 */
          {OpCode::OP_LOADNIL, {OpCode::OP_LOADNIL, {operand_encoding::A, operand_encoding::B}}},                        /* 4 */
          {OpCode::OP_GETUPVAL, {OpCode::OP_GETUPVAL, {operand_encoding::A, operand_encoding::B}}},                      /* 5 */
          {OpCode::OP_GETTABUP, {OpCode::OP_GETTABUP, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 6 */
          {OpCode::OP_GETTABLE, {OpCode::OP_GETTABLE, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 7 */
          {OpCode::OP_SETTABUP, {OpCode::OP_SETTABUP, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 8 */
          {OpCode::OP_SETUPVAL, {OpCode::OP_SETUPVAL, {operand_encoding::A, operand_encoding::B}}},                      /* 9 */
          {OpCode::OP_SETTABLE, {OpCode::OP_SETTABLE, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* a */
          {OpCode::OP_NEWTABLE, {OpCode::OP_NEWTABLE, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* b */
          {OpCode::OP_SELF, {OpCode::OP_SELF, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* c */
          {OpCode::OP_ADD, {OpCode::OP_ADD, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* d */
          {OpCode::OP_SUB, {OpCode::OP_SUB, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* e */
          {OpCode::OP_MUL, {OpCode::OP_MUL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* f */
          {OpCode::OP_MOD, {OpCode::OP_MOD, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 10 */
          {OpCode::OP_POW, {OpCode::OP_POW, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 11 */
          {OpCode::OP_DIV, {OpCode::OP_DIV, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 12 */
          {OpCode::OP_IDIV, {OpCode::OP_IDIV, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* 13 */
          {OpCode::OP_BAND, {OpCode::OP_BAND, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* 14 */
          {OpCode::OP_BOR, {OpCode::OP_BOR, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 15 */
          {OpCode::OP_BXOR, {OpCode::OP_BXOR, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* 16 */
          {OpCode::OP_SHL, {OpCode::OP_SHL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 17 */
          {OpCode::OP_SHR, {OpCode::OP_SHR, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 18 */
          {OpCode::OP_UNM, {OpCode::OP_UNM, {operand_encoding::A, operand_encoding::B}}},                                /* 19 */
          {OpCode::OP_BNOT, {OpCode::OP_BNOT, {operand_encoding::A, operand_encoding::B}}},                              /* 1a */
          {OpCode::OP_NOT, {OpCode::OP_NOT, {operand_encoding::A, operand_encoding::B}}},                                /* 1b */
          {OpCode::OP_LEN, {OpCode::OP_LEN, {operand_encoding::A, operand_encoding::B}}},                                /* 1c */
          {OpCode::OP_CONCAT, {OpCode::OP_CONCAT, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},     /* 1d */
          {OpCode::OP_JMP, {OpCode::OP_JMP, {operand_encoding::A, operand_encoding::sBx}}},                              /* 1e */
          {OpCode::OP_EQ, {OpCode::OP_EQ, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},             /* 1f */
          {OpCode::OP_LT, {OpCode::OP_LT, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},             /* 20 */
          {OpCode::OP_LE, {OpCode::OP_LE, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},             /* 21 */
          {OpCode::OP_TEST, {OpCode::OP_TEST, {operand_encoding::A, operand_encoding::C}}},                              /* 22 */
          {OpCode::OP_TESTSET, {OpCode::OP_TESTSET, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},   /* 23 */
          {OpCode::OP_CALL, {OpCode::OP_CALL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* 24 */
          {OpCode::OP_TAILCALL, {OpCode::OP_TAILCALL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 25 */
          {OpCode::OP_RETURN, {OpCode::OP_RETURN, {operand_encoding::A, operand_encoding::B}}},                          /* 26 */
          {OpCode::OP_FORLOOP, {OpCode::OP_FORLOOP, {operand_encoding::A, operand_encoding::sBx}}},                      /* 27 */
          {OpCode::OP_FORPREP, {OpCode::OP_FORPREP, {operand_encoding::A, operand_encoding::sBx}}},                      /* 28 */
          {OpCode::OP_TFORCALL, {OpCode::OP_TFORCALL, {operand_encoding::A, operand_encoding::C}}},                      /* 29 */
          {OpCode::OP_TFORLOOP, {OpCode::OP_TFORLOOP, {operand_encoding::A, operand_encoding::sBx}}},                    /* 2a */
          {OpCode::OP_SETLIST, {OpCode::OP_SETLIST, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},   /* 2b */
          {OpCode::OP_CLOSURE, {OpCode::OP_CLOSURE, {operand_encoding::A, operand_encoding::Bx}}},                       /* 2c */
          {OpCode::OP_VARARG, {OpCode::OP_VARARG, {operand_encoding::A, operand_encoding::B}}},                          /* 2d */
          {OpCode::OP_EXTRAARG, {OpCode::OP_EXTRAARG, {operand_encoding::Ax}}}                                           /* 2e */
      };

      struct optable_kind {
            OpCode op;
            std::vector<operand_kind> kinds;
      };
      static std::map<OpCode, optable_kind> opkinds = {
          {OpCode::OP_MOVE, {OpCode::OP_MOVE, {operand_kind::dest, operand_kind::reg}}},                                           /* 0 */
          {OpCode::OP_LOADK, {OpCode::OP_LOADK, {operand_kind::dest, operand_kind::k_idx}}},                                       /* 1 */
          {OpCode::OP_LOADKX, {OpCode::OP_LOADKX, {operand_kind::dest}}},                                                          /* 2 */
          {OpCode::OP_LOADBOOL, {OpCode::OP_LOADBOOL, {operand_kind::dest, operand_kind::val, operand_kind::jmp}}},                /* 3 */
          {OpCode::OP_LOADNIL, {OpCode::OP_LOADNIL, {operand_kind::dest, operand_kind::val}}},                                     /* 4 */
          {OpCode::OP_GETUPVAL, {OpCode::OP_GETUPVAL, {operand_kind::dest, operand_kind::upvalue}}},                               /* 5 */
          {OpCode::OP_GETTABUP, {OpCode::OP_GETTABUP, {operand_kind::dest, operand_kind::uenv, operand_kind::k_idx}}},             /* 6 */
          {OpCode::OP_GETTABLE, {OpCode::OP_GETTABLE, {operand_kind::dest, operand_kind::val, operand_kind::val}}},                /* 7 */
          {OpCode::OP_SETTABUP, {OpCode::OP_SETTABUP, {operand_kind::upvalue, operand_kind::val, operand_kind::val}}},             /* 8 */
          {OpCode::OP_SETUPVAL, {OpCode::OP_SETUPVAL, {operand_kind::upvalue, operand_kind::val}}},                                /* 9 */
          {OpCode::OP_SETTABLE, {OpCode::OP_SETTABLE, {operand_kind::reg, operand_kind::k_idx, operand_kind::k_idx}}},             /* a */
          {OpCode::OP_NEWTABLE, {OpCode::OP_NEWTABLE, {operand_kind::dest, operand_kind::table_size, operand_kind::table_size}}},  /* b */
          {OpCode::OP_SELF, {OpCode::OP_SELF, {operand_kind::dest, operand_kind::val, operand_kind::val}}},                        /* c */
          {OpCode::OP_ADD, {OpCode::OP_ADD, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* d */
          {OpCode::OP_SUB, {OpCode::OP_SUB, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* e */
          {OpCode::OP_MUL, {OpCode::OP_MUL, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* f */
          {OpCode::OP_MOD, {OpCode::OP_MOD, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 10 */
          {OpCode::OP_POW, {OpCode::OP_POW, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 11 */
          {OpCode::OP_DIV, {OpCode::OP_DIV, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 12 */
          {OpCode::OP_IDIV, {OpCode::OP_IDIV, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                        /* 13 */
          {OpCode::OP_BAND, {OpCode::OP_BAND, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                        /* 14 */
          {OpCode::OP_BOR, {OpCode::OP_BOR, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 15 */
          {OpCode::OP_BXOR, {OpCode::OP_BXOR, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                        /* 16 */
          {OpCode::OP_SHL, {OpCode::OP_SHL, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 17 */
          {OpCode::OP_SHR, {OpCode::OP_SHR, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 18 */
          {OpCode::OP_UNM, {OpCode::OP_UNM, {operand_kind::dest, operand_kind::reg}}},                                             /* 19 */
          {OpCode::OP_BNOT, {OpCode::OP_BNOT, {operand_kind::dest, operand_kind::reg}}},                                           /* 1a */
          {OpCode::OP_NOT, {OpCode::OP_NOT, {operand_kind::dest, operand_kind::reg}}},                                             /* 1b */
          {OpCode::OP_LEN, {OpCode::OP_LEN, {operand_kind::dest, operand_kind::reg}}},                                             /* 1c */
          {OpCode::OP_CONCAT, {OpCode::OP_CONCAT, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                    /* 1d */
          {OpCode::OP_JMP, {OpCode::OP_JMP, {operand_kind::val, operand_kind::jmp}}},                                              /* 1e */
          {OpCode::OP_EQ, {OpCode::OP_EQ, {operand_kind::val, operand_kind::reg, operand_kind::reg}}},                             /* 1f */
          {OpCode::OP_LT, {OpCode::OP_LT, {operand_kind::val, operand_kind::reg, operand_kind::reg}}},                             /* 20 */
          {OpCode::OP_LE, {OpCode::OP_LE, {operand_kind::val, operand_kind::reg, operand_kind::reg}}},                             /* 21 */
          {OpCode::OP_TEST, {OpCode::OP_TEST, {operand_kind::reg, operand_kind::val}}},                                            /* 22 */
          {OpCode::OP_TESTSET, {OpCode::OP_TESTSET, {operand_kind::reg, operand_kind::reg, operand_kind::val}}},                   /* 23 */
          {OpCode::OP_CALL, {OpCode::OP_CALL, {operand_kind::reg, operand_kind::val_multret, operand_kind::val_multret}}},         /* 24 */
          {OpCode::OP_TAILCALL, {OpCode::OP_TAILCALL, {operand_kind::reg, operand_kind::val_multret, operand_kind::val_multret}}}, /* 25 */
          {OpCode::OP_RETURN, {OpCode::OP_RETURN, {operand_kind::reg, operand_kind::val_multret}}},                                /* 26 */
          {OpCode::OP_FORLOOP, {OpCode::OP_FORLOOP, {operand_kind::reg, operand_kind::jmp}}},                                      /* 27 */
          {OpCode::OP_FORPREP, {OpCode::OP_FORPREP, {operand_kind::reg, operand_kind::jmp}}},                                      /* 28 */
          {OpCode::OP_TFORCALL, {OpCode::OP_TFORCALL, {operand_kind::reg, operand_kind::val}}},                                    /* 29 */
          {OpCode::OP_TFORLOOP, {OpCode::OP_TFORLOOP, {operand_kind::reg, operand_kind::jmp}}},                                    /* 2a */
          {OpCode::OP_SETLIST, {OpCode::OP_SETLIST, {operand_kind::reg, operand_kind::val_multret, operand_kind::val_multret}}},   /* 2b */
          {OpCode::OP_CLOSURE, {OpCode::OP_CLOSURE, {operand_kind::reg, operand_kind::p_idx}}},                                    /* 2c */
          {OpCode::OP_VARARG, {OpCode::OP_VARARG, {operand_kind::reg, operand_kind::val_multret}}},                                /* 2d */
          {OpCode::OP_EXTRAARG, {OpCode::OP_EXTRAARG, {operand_kind::reg}}}                                                        /* 2e */
      };

      struct optable_descriptor {
            const char *opname;
            const char *mnemonic;
            const char *hint;
            std::vector<const char *> operand_encodings;
      };
      static std::map<OpCode, optable_descriptor> opdescriptor = {
          {OpCode::OP_MOVE, {"OP_MOVE", "move", "Move source register to dest register.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                           /* 0 */
          {OpCode::OP_LOADK, {"OP_LOADK", "loadk", "Load kvalue to destination register.", {"dest(Register)", "kidx(Kvalue Index)"}}},                                                                                                                                                     /* 1 */
          {OpCode::OP_LOADKX, {"OP_LOADKX", "loadkx", "Load kvalue extended.", {"dest(Register)"}}},                                                                                                                                                                                       /* 2 */
          {OpCode::OP_LOADBOOL, {"OP_LOADBOOL", "loadbool", "Load boolean to register and take jump.", {"dest(Register)", "val(Value)", "jmp(Jump)"}}},                                                                                                                                    /* 3 */
          {OpCode::OP_LOADNIL, {"OP_LOADNIL", "loadnil", "Iteration start at first target register then increments above the stack and fills with NIL set by source value.", {"dest(Register)", "val(Value)"}}},                                                                           /* 4 */
          {OpCode::OP_GETUPVAL, {"OP_GETUPVAL", "getupval", "Load upvalue to destination register.", {"dest(Register)", "upv(Upvalue)"}}},                                                                                                                                                 /* 5 */
          {OpCode::OP_GETTABUP, {"OP_GETTABUP", "gettabup", "Gets table upvalue as B and index element as C which gets load to A.", {"dest(Register)", "uenv(Upvalue Table Environment)", "kidx(Kvalue Index)"}}},                                                                         /* 6 */
          {OpCode::OP_GETTABLE, {"OP_GETTABLE", "gettable", "Gets table as B and index element as C which gets load to A.", {"dest(Register)", "val(Value)", "val(Value)"}}},                                                                                                              /* 7 */
          {OpCode::OP_SETTABUP, {"OP_SETTABUP", "settabup", "Gets table upvalue as A and index element as B and sets A to the index.", {"upv(Upvalue)", "val(Value)", "val(Value)"}}},                                                                                                     /* 8 */
          {OpCode::OP_SETUPVAL, {"OP_SETUPVAL", "setupval", "Load a value into an upvalue.", {"upv(Upvalue)", "val(Value)"}}},                                                                                                                                                             /* 9 */
          {OpCode::OP_SETTABLE, {"OP_SETTABLE", "settable", "Load a register value into a table element.", {"src(Register)", "kidx(Kvalue Index)", "kidx(Kvalue Index)"}}},                                                                                                                /* a */
          {OpCode::OP_NEWTABLE, {"OP_NEWTABLE", "newtable", "Creates new table with B being array size and C being hash size.", {"dest(Register)", "tsize(Table Size)", "tsize(Table Size)"}}},                                                                                            /* b */
          {OpCode::OP_SELF, {"OP_SELF", "self", "Call to self.", {"dest(Register)", "val(Value)", "val(Value)"}}},                                                                                                                                                                         /* c */
          {OpCode::OP_ADD, {"OP_ADD", "add", "Add B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                                  /* d */
          {OpCode::OP_SUB, {"OP_SUB", "sub", "Sub B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                                  /* e */
          {OpCode::OP_MUL, {"OP_MUL", "mul", "Multiply B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                             /* f */
          {OpCode::OP_MOD, {"OP_MOD", "mod", "Modulus B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                              /* 10 */
          {OpCode::OP_POW, {"OP_POW", "pow", "Power B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                                /* 11 */
          {OpCode::OP_DIV, {"OP_DIV", "div", "Divide B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                               /* 12 */
          {OpCode::OP_IDIV, {"OP_IDIV", "idiv", "Floor division B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                    /* 13 */
          {OpCode::OP_BAND, {"OP_BAND", "band", "Bitwise and B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                       /* 14 */
          {OpCode::OP_BOR, {"OP_BOR", "bor", "Bitwise or B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                           /* 15 */
          {OpCode::OP_BXOR, {"OP_BXOR", "bxor", "Bitwise xor division B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                              /* 16 */
          {OpCode::OP_SHL, {"OP_SHL", "shl", "Shift left B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                           /* 17 */
          {OpCode::OP_SHR, {"OP_SHR", "shr", "Shift right B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                          /* 18 */
          {OpCode::OP_UNM, {"OP_UNM", "unm", "Unary minus A to B and load results to A.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                           /* 19 */
          {OpCode::OP_BNOT, {"OP_BNOT", "bnot", "Binary not A to B and load results to A.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                         /* 1a */
          {OpCode::OP_NOT, {"OP_NOT", "not", "Unary not A to B and load results to A.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                             /* 1b */
          {OpCode::OP_LEN, {"OP_LEN", "len", "Unary length of table B and load results to A.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                      /* 1c */
          {OpCode::OP_CONCAT, {"OP_CONCAT", "concat", "Concat string where start of stack B to C.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                /* 1d */
          {OpCode::OP_JMP, {"OP_JMP", "jmp", "Jump to sBx if A is not 0 then all upvalues >= A - 1 will be closed.", {"val(Value)", "jmp(Jump)"}}},                                                                                                                                        /* 1e */
          {OpCode::OP_EQ, {"OP_EQ", "eq", "Compare equal B to C and if comparision is not A skip next instruction.", {"val(Value)", "src(Register)", "src(Register)"}}},                                                                                                                   /* 1f */
          {OpCode::OP_LT, {"OP_LT", "lt", "Compare less than B to C and if comparision is not A skip next instruction.", {"val(Value)", "src(Register)", "src(Register)"}}},                                                                                                               /* 20 */
          {OpCode::OP_LE, {"OP_LE", "le", "Compare less than equal B to C and if comparision is not A skip next instruction.", {"val(Value)", "src(Register)", "src(Register)"}}},                                                                                                         /* 21 */
          {OpCode::OP_TEST, {"OP_TEST", "test", "Compare A to C and if false skip next instruction", {"src(Register)", "val(Value)"}}},                                                                                                                                                    /* 22 */
          {OpCode::OP_TESTSET, {"OP_TESTSET", "testset", "Compare B to C and if false skip next instruction else set A to B.", {"src(Register)", "src(Register)", "val(Value)"}}},                                                                                                         /* 23 */
          {OpCode::OP_CALL, {"OP_CALL", "call", "Call A with B args and C return.", {"src(Register)", "multret(Multret Value)", "multret(Multret Value)"}}},                                                                                                                               /* 24 */
          {OpCode::OP_TAILCALL, {"OP_TAILCALL", "tailcall", "Return call A with B args and C return.", {"src(Register)", "multret(Multret Value)", "multret(Multret Value)"}}},                                                                                                            /* 25 */
          {OpCode::OP_RETURN, {"OP_RETURN", "return", "Return from start A to A + B - 2.", {"src(Register)", "multret(Multret Value)"}}},                                                                                                                                                  /* 26 */
          {OpCode::OP_FORLOOP, {"OP_FORLOOP", "forloop", "For loop follows for format starting A with sBx jump.", {"src(Register)", "jmp(Jump)"}}},                                                                                                                                        /* 27 */
          {OpCode::OP_FORPREP, {"OP_FORPREP", "forprep", "For loop follows for format starting A with sBx jump.", {"src(Register)", "jmp(Jump)"}}},                                                                                                                                        /* 28 */
          {OpCode::OP_TFORCALL, {"OP_TFORCALL", "tforcall", "For prep calls iterator function.", {"src(Register)", "val(Value)"}}},                                                                                                                                                        /* 29 */
          {OpCode::OP_TFORLOOP, {"OP_TFORLOOP", "tforloop", "For loop follows T for format starting A with sBx jump.", {"src(Register)", "jmp(Jump)"}}},                                                                                                                                   /* 2a */
          {OpCode::OP_SETLIST, {"OP_SETLIST", "setlist", "Sets the values for a range of array elements in a table referenced by A, B is the number of elements to set, C encodes the block number initialized.", {"src(Register)", "multret(Multret Value)", "multret(Multret Value)"}}}, /* 2b */
          {OpCode::OP_CLOSURE, {"OP_CLOSURE", "closure", "Set to kvalue proto.", {"src(Register)", "pidx(Proto Index)"}}},                                                                                                                                                                 /* 2c */
          {OpCode::OP_VARARG, {"OP_VARARG", "vararg", "Set range A + 1 to A + B - e1 to vararg.", {"src(Register)", "multret(Multret Value)"}}},                                                                                                                                           /* 2d */
          {OpCode::OP_EXTRAARG, {"OP_EXTRAARG", "extraarg", "Extra arg Ax for previous opcode.", {"src(Register)"}}}                                                                                                                                                                       /* 2e */
      };

} // namespace kosmic::lua::ver_5_3_6::optable