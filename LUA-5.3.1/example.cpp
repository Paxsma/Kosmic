#include "disassembler/disassembler.hpp"
#include <fstream>
#include <inttypes.h>
#include <iostream>
#include <sstream>
#include <string>

Proto *compile_script(const std::string &code, bool &error, lua_State *&buffer) {

      buffer = luaL_newstate(); /* New lua state */

      if (luaL_loadstring(buffer, code.c_str()) != LUA_OK) {
            error = true; /* Return error */
            return NULL;
      }

      return gco2cl((buffer->top - 1)->value_.gc)->l.p;
}

std::int32_t main(std::int32_t argc, char const *argv[]) {

      if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <Lua script file>" << std::endl;
            return 1;
      }

      lua_State *ls = nullptr;
      bool error = false;

      /* Open file */
      std::stringstream code;
      std::ifstream file(argv[1]);

      if (file.is_open()) {
            std::string line = "";
            while (std::getline(file, line)) {
                  code << line << std::endl;
            }
            file.close();
      }

      /* Compile code */
      const auto proto = compile_script(code.str(), error, ls);

      /* Check for error */
      if (error) {
            throw std::runtime_error("Error thrown with disassembly.");
      }

      /* Print disassembly */
      auto curr = proto;
      std::vector<Proto *> ls_p;
      do {

            /* Disassemble */
            const auto dism = kosmic::lua::ver_5_3_1::disassemble(curr);

            /* Print proto information */
            std::printf("\n* function %" PRIuPTR " instructions\n", dism.size());
            std::printf("* %d constants, %d protos, %d upvalues\n", curr->sizek, curr->sizep, curr->sizeupvalues);

            /* Print proto */
            for (const auto &i : dism)
                  std::printf("%s\n", i->disassemble().c_str());

            /* Append children protos */
            for (auto i = 0; i < proto->sizep; ++i)
                  ls_p.emplace_back(proto->p[i]);

            /* Remove */
            std::erase(ls_p, curr);

      } while ((curr = (ls_p.empty()) ? nullptr : ls_p.front()) != nullptr);

      return 0;
}