#pragma once
#include "optable.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace kosmic::lua::ver_5_3_1 {

      struct operand {

            optable::operand_kind kind;         /* Operand kind */
            optable::operand_encoding encoding; /* Operand encoding */

            union {
                  std::uint16_t reg;         /* Register */
                  std::intptr_t val;         /* Value */
                  std::intptr_t jmp;         /* Jump */
                  std::uintptr_t table_size; /* Table size */
                  std::size_t u_idx;         /* Upvalue index */
                  std::size_t k_idx;         /* Kvalue index */
                  std::size_t p_idx;         /* Proto index */
            };

            struct debug {

                  struct kvalue {
                        std::string str = "";         /* Represent Kvalue as a string */
                        std::uint8_t kind = LUA_TNIL; /* Kvalue type */
                  } kvalue;

                  struct proto {
                        Proto *p = nullptr; /* Refrenced proto */
                  } proto;

            } debug;

            std::uintptr_t ref_addr = 0u; /* Any addresses refrenced? */
      };

      struct disassembly {

            OpCode op;                /* Opcode */
            std::uintptr_t addr = 0u; /* Instruction address */
            std::uint8_t len = 0u;    /* Instruction length */

            const char *mnenomic = ""; /* Instruction mnenomic*/
            const char *hint = "";     /* Instruction hint */
            std::string data = "";     /* Disassembled instruction */

            Instruction *code; /* Instruction code */

            std::vector<std::shared_ptr<operand>> operands; /* Instruction operand */
            std::vector<std::uint8_t> bytes;                /* All bytes in instruction */

            /* Returns disassembly string. */
            template <bool include_hint = false>
            std::string disassemble() {

                  std::string result = std::to_string(this->addr) + " " + this->data;

                  if (include_hint) {
                        result += " " + std::string(this->hint);
                  }

                  return result;
            }
      };

      /* Disassemble by address. */
      void disassemble(const std::uintptr_t addr, const Proto *p, std::shared_ptr<disassembly> &buffer);

      /* Disassemble all. */
      void disassemble(const Proto *p, std::vector<std::shared_ptr<disassembly>> &buffer);

      /* Disassemble proto. */
      std::vector<std::shared_ptr<kosmic::lua::ver_5_3_1::disassembly>> disassemble(const Proto *p);

} // namespace kosmic::lua::ver_5_3_1