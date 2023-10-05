#include "disassembler.hpp"
#include <iostream>

void set_data(std::shared_ptr<kosmic::lua::ver_5_3_2::disassembly> &buffer, const Proto *p, const OpCode op) {

      const auto descriptor = kosmic::lua::ver_5_3_2::optable::opdescriptor[op];
      const auto encoding = kosmic::lua::ver_5_3_2::optable::opencodings[op];
      const auto kind = kosmic::lua::ver_5_3_2::optable::opkinds[op];

      /* Set instruction data */
      buffer->hint = descriptor.hint;
      buffer->mnenomic = descriptor.mnemonic;
      buffer->op = op;
      buffer->data = std::string(buffer->mnenomic) + ' ';

      const auto op_count = encoding.encodings.size();
      for (auto i = 0u; i < op_count; ++i) {

            auto current_operand = std::make_shared<kosmic::lua::ver_5_3_2::operand>();

            std::int32_t operand_value = 0;

            const auto operand = encoding.encodings[i];
            const auto type = kind.kinds[i];

            const auto split = ((i + 1u) == op_count) ? " " : ", ";

            /* Set operand value. */
            switch (operand) {

                  case kosmic::lua::ver_5_3_2::optable::operand_encoding::A: {
                        operand_value = GETARG_A(*buffer->code);
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_encoding::Ax: {
                        operand_value = GETARG_Ax(*++buffer->code);
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_encoding::B: {
                        operand_value = GETARG_B(*buffer->code);
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_encoding::Bx: {
                        operand_value = GETARG_Bx(*buffer->code);
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_encoding::C: {
                        operand_value = GETARG_C(*buffer->code);
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_encoding::sBx: {
                        operand_value = GETARG_sBx(*buffer->code);
                        break;
                  }

                  default: {
                        throw std::runtime_error("Unkown operand type.");
                  }
            }

            /* Set type and operand. */
            current_operand->kind = type;
            current_operand->encoding = operand;

            /* Set type. */
            switch (current_operand->kind) {

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::table_size: {
                        current_operand->table_size = (!operand_value ? 0 : (1 << (operand_value - 1)));
                        buffer->data += std::to_string(current_operand->table_size) + split;
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::upvalue: {
                        current_operand->u_idx = operand_value;
                        buffer->data += "upvalue_" + std::to_string(current_operand->u_idx) + split;
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::uenv: {
                        current_operand->u_idx = operand_value;
                        const auto name = std::string(getstr(p->upvalues[current_operand->u_idx].name));
                        buffer->data += (!name.empty() ? name + "_" + std::to_string(current_operand->u_idx) : "upvalue_env_" + std::to_string(current_operand->u_idx)) + split;
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::jmp: {
                        current_operand->jmp = operand_value;
                        current_operand->ref_addr = current_operand->jmp + buffer->addr + 1u;
                        buffer->data += std::to_string(current_operand->jmp) + split;
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::reg:
                  case kosmic::lua::ver_5_3_2::optable::operand_kind::dest: {
                        current_operand->reg = std::uint16_t(operand_value);
                        buffer->data += 'r' + std::to_string(current_operand->reg) + split;
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::val: {
                        current_operand->val = operand_value;
                        buffer->data += std::to_string(current_operand->val) + split;
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::val_multret: {
                        current_operand->val = --operand_value;
                        buffer->data += std::to_string(current_operand->val) + split;
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::p_idx: {
                        current_operand->p_idx = operand_value;
                        current_operand->debug.proto.p = p->p[current_operand->p_idx];
                        buffer->data += std::to_string(current_operand->p_idx) + split;
                        break;
                  }

                  case kosmic::lua::ver_5_3_2::optable::operand_kind::k_idx: {

                        current_operand->k_idx = INDEXK(operand_value);
                        const auto kv = &p->k[current_operand->k_idx];
                        current_operand->debug.kvalue.kind = novariant(kv->tt_);

                        switch (current_operand->debug.kvalue.kind) {

                              case LUA_TNIL: {
                                    current_operand->debug.kvalue.str = "nil";
                                    break;
                              }

                              case LUA_TBOOLEAN: {
                                    current_operand->debug.kvalue.str = std::to_string(kv->value_.b);
                                    break;
                              }

                              case LUA_TNUMBER: {
                                    if (std::floor(kv->value_.n) == kv->value_.n) {
                                          current_operand->debug.kvalue.str = std::to_string(std::intptr_t(kv->value_.n));
                                    } else {
                                          current_operand->debug.kvalue.str = std::to_string(kv->value_.n);
                                    }
                                    break;
                              }

                              case LUA_TSTRING: {
                                    current_operand->debug.kvalue.str = std::string("\"") + getstr(gco2ts(kv->value_.gc)) + '\"';
                                    break;
                              }

                              case LUA_TLIGHTUSERDATA: {
                                    current_operand->debug.kvalue.str = "lightuserdata_" + std::to_string(current_operand->k_idx);
                                    break;
                              }

                              case LUA_TFUNCTION: {
                                    current_operand->debug.kvalue.str = "closure_" + std::to_string(current_operand->k_idx);
                                    break;
                              }

                              case LUA_TTABLE: {
                                    current_operand->debug.kvalue.str = "table_" + std::to_string(current_operand->k_idx);
                                    break;
                              }

                              case LUA_TUSERDATA: {
                                    current_operand->debug.kvalue.str = "userdata_" + std::to_string(current_operand->k_idx);
                                    break;
                              }

                              default: {
                                    throw std::runtime_error("Unkown lua type.");
                              }
                        }

                        buffer->data += current_operand->debug.kvalue.str + split;
                        break;
                  }
            }

            buffer->operands.emplace_back(current_operand);
      }

      return;
}

void kosmic::lua::ver_5_3_2::disassemble(const std::uintptr_t addr, const Proto *p, std::shared_ptr<kosmic::lua::ver_5_3_2::disassembly> &buffer) {

      /* Set code. */
      auto start_pc = p->code + addr;
      buffer->code = start_pc;
      buffer->addr = addr;

      /* Clear for next. */
      buffer->operands.clear();

      /* Init data. */
      set_data(buffer, p, GET_OPCODE(p->code[addr]));

      /* Calculate lenght. */
      buffer->len = (std::uint8_t(reinterpret_cast<const std::uintptr_t>(buffer->code) - reinterpret_cast<const std::uintptr_t>(start_pc)) / sizeof(Instruction)) + 1u;

      /* Bytes */
      for (auto i = 0u; i < buffer->len; ++i)
            for (auto s = 0u; s < sizeof(Instruction); ++s)
                  buffer->bytes.emplace_back((p->code[buffer->addr + i] >> (s * 8)) & 0xFF);

      return;
}

void kosmic::lua::ver_5_3_2::disassemble(const Proto *p, std::vector<std::shared_ptr<disassembly>> &buffer) {
      for (auto pc = 0u; pc < unsigned(p->sizecode);) {
            auto dism = std::make_shared<disassembly>();
            disassemble(pc, p, dism);
            buffer.emplace_back(dism);
            pc += dism->len;
      }
      return;
}

std::vector<std::shared_ptr<kosmic::lua::ver_5_3_2::disassembly>> kosmic::lua::ver_5_3_2::disassemble(const Proto *p) {
      std::vector<std::shared_ptr<disassembly>> result;
      disassemble(p, result);
      return result;
}