#include "AdvancedObfuscation.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <cstdlib>
#include <regex>

// 生成随机宏名称的结构
struct MacroNames {
    std::string _auto, _begin, _const, _double, _else, _for, _goto, _if;
    std::string _int, _long, _return, _size_t, _static, _struct, _typedef;
    std::string _unsigned, _void, _while, _switch, _case, _default, _break;
    std::string _continue, ktry, kcatch, kthrow;
    
    MacroNames() {
        _auto = "_" + RandomStringGenerator::generate(8);
        _begin = "_" + RandomStringGenerator::generate(8);
        _const = "_" + RandomStringGenerator::generate(8);
        _double = "_" + RandomStringGenerator::generate(8);
        _else = "_" + RandomStringGenerator::generate(8);
        _for = "_" + RandomStringGenerator::generate(8);
        _goto = "_" + RandomStringGenerator::generate(8);
        _if = "_" + RandomStringGenerator::generate(8);
        _int = "_" + RandomStringGenerator::generate(8);
        _long = "_" + RandomStringGenerator::generate(8);
        _return = "_" + RandomStringGenerator::generate(8);
        _size_t = "_" + RandomStringGenerator::generate(8);
        _static = "_" + RandomStringGenerator::generate(8);
        _struct = "_" + RandomStringGenerator::generate(8);
        _typedef = "_" + RandomStringGenerator::generate(8);
        _unsigned = "_" + RandomStringGenerator::generate(8);
        _void = "_" + RandomStringGenerator::generate(8);
        _while = "_" + RandomStringGenerator::generate(8);
        _switch = "_" + RandomStringGenerator::generate(8);
        _case = "_" + RandomStringGenerator::generate(8);
        _default = "_" + RandomStringGenerator::generate(8);
        _break = "_" + RandomStringGenerator::generate(8);
        _continue = "_" + RandomStringGenerator::generate(8);
        ktry = "_" + RandomStringGenerator::generate(8);
        kcatch = "_" + RandomStringGenerator::generate(8);
        kthrow = "_" + RandomStringGenerator::generate(8);
    }
};

std::string AdvancedObfuscation::addMacroDefinitions(const std::string& code) {
    std::string result = code;
    MacroNames macros;
    
    // 在使用命名空间之后添加宏定义
    size_t using_namespace_pos = result.find("using namespace");
    if (using_namespace_pos != std::string::npos) {
        size_t end_of_line = result.find(';', using_namespace_pos);
        if (end_of_line != std::string::npos) {
            std::stringstream ss;
            ss << "\n\n// Macro obfuscation\n";
            ss << "#define " << macros._auto << " auto\n";
            ss << "#define " << macros._begin << " begin\n";
            ss << "#define " << macros._const << " const\n";
            ss << "#define " << macros._double << " double\n";
            ss << "#define " << macros._else << " else\n";
            ss << "#define " << macros._for << " for\n";
            ss << "#define " << macros._goto << " goto\n";
            ss << "#define " << macros._if << " if\n";
            ss << "#define " << macros._int << " int\n";
            ss << "#define " << macros._long << " long\n";
            ss << "#define " << macros._return << " return\n";
            ss << "#define " << macros._size_t << " size_t\n";
            ss << "#define " << macros._static << " static\n";
            ss << "#define " << macros._struct << " struct\n";
            ss << "#define " << macros._typedef << " typedef\n";
            ss << "#define " << macros._unsigned << " unsigned\n";
            ss << "#define " << macros._void << " void\n";
            ss << "#define " << macros._while << " while\n";
            ss << "#define " << macros._switch << " switch\n";
            ss << "#define " << macros._case << " case\n";
            ss << "#define " << macros._default << " default\n";
            ss << "#define " << macros._break << " break\n";
            ss << "#define " << macros._continue << " continue\n";
            ss << "#define " << macros.ktry << " try\n";
            ss << "#define " << macros.kcatch << " catch\n";
            ss << "#define " << macros.kthrow << " throw\n";
            
            result.insert(end_of_line + 1, ss.str());
        }
    }
    
    return result;
}

std::string AdvancedObfuscation::addTEALikeObfuscation(const std::string& code) {
    std::string result = code;
    
    size_t main_pos = result.find("int main");
    if (main_pos != std::string::npos) {
        std::stringstream ss;
        ss << "\n";
        ss << "static volatile int adv_seed = 0;\n";
        ss << "int adv_init() {\n";
        ss << "    int *p = new int(13);\n";
        ss << "    adv_seed = (int)(size_t)p & 0xFF;\n";
        ss << "    delete p;\n";
        ss << "    int v = adv_seed;\n";
        ss << "    v = (v * 3 + 7) & 0xFF;\n";
        ss << "    v = ((v << 4) | (v >> 4)) & 0xFF;\n";
        ss << "    v = (v * 0xab) >> 8;\n";
        ss << "    return 13;\n";
        ss << "}\n";
        ss << "int adv_fake_dep(int x, int y) {\n";
        ss << "    int a = x + y;\n";
        ss << "    int b = x - y;\n";
        ss << "    int c = a * b;\n";
        ss << "    int d = c + y * y;\n";
        ss << "    int e = d - x * x;\n";
        ss << "    return e;\n";
        ss << "}\n";
        ss << "int adv_flat(int n, int m) {\n";
        ss << "    int state = 0, res = 0, i = 0;\n";
        ss << "    int tbl[4] = {n, m, 0, 0};\n";
        ss << "    while(state != 99) {\n";
        ss << "        switch(state) {\n";
        ss << "            case 0: tbl[2] = tbl[0] + tbl[1]; state = 1; break;\n";
        ss << "            case 1: tbl[3] = tbl[0] * tbl[1]; state = 2; break;\n";
        ss << "            case 2:\n";
        ss << "                if((tbl[0] ^ tbl[1]) & 1) state = 3;\n";
        ss << "                else state = 3;\n";
        ss << "                break;\n";
        ss << "            case 3: res = tbl[2]; state = 99; break;\n";
        ss << "        }\n";
        ss << "    }\n";
        ss << "    return res;\n";
        ss << "}\n";
        
        result.insert(main_pos, ss.str());
    }
    
    return result;
}

std::string AdvancedObfuscation::addFakeStateMachine(const std::string& code) {
    std::string result = code;
    
    size_t main_pos = result.find("int main");
    if (main_pos != std::string::npos) {
        size_t brace_pos = result.find('{', main_pos);
        if (brace_pos != std::string::npos) {
            std::stringstream ss;
            ss << "\n";
            ss << "    int adv_k = adv_init();\n";
            ss << "    int adv_fake = adv_fake_dep(adv_k, adv_k);\n";
            ss << "    int adv_state = adv_k - 13;\n";
            ss << "    \n";
            
            result.insert(brace_pos + 1, ss.str());
            
            size_t return_pos = result.rfind("return", std::string::npos);
            if (return_pos != std::string::npos && return_pos > brace_pos) {
                size_t semicolon_pos = result.find(';', return_pos);
                if (semicolon_pos != std::string::npos) {
                    size_t end_brace = result.find('}', semicolon_pos);
                    if (end_brace != std::string::npos) {
                        result.insert(return_pos, "    (void)adv_fake; (void)adv_state;\n");
                    }
                }
            }
        }
    }
    
    return result;
}

std::string AdvancedObfuscation::addIdentityChains(const std::string& code) {
    return code;
}

std::string AdvancedObfuscation::addFunctionJumpObfuscation(const std::string& code) {
    std::string result = code;
    
    size_t main_pos = result.find("int main");
    if (main_pos != std::string::npos) {
        std::stringstream ss;
        ss << "\n";
        for (int i = 0; i < 3; i++) {
            std::string f = "a" + RandomStringGenerator::generate(4);
            std::string v = "b" + RandomStringGenerator::generate(4);
            ss << "int " << f << "(){int " << v << "=" << (i*17+7) << ";" << v << "=(" << v << "^0x1234);return " << v << ";}\n";
        }
        result.insert(main_pos, ss.str());
    }
    
    return result;
}

std::string AdvancedObfuscation::addAdvancedObfuscation(const std::string& code) {
    std::string result = code;
    
    // 0. 添加函数跳转干扰（在最前面，不被其他混淆器处理）
    result = addFunctionJumpObfuscation(result);
    
    // 1. 添加宏定义（使用随机名称）
    result = addMacroDefinitions(result);
    
    // 2. 添加 TEA-like 混淆
    result = addTEALikeObfuscation(result);
    
    // 3. 添加虚假状态机和 main 函数替换
    result = addFakeStateMachine(result);
    
    // 4. 添加恒等链（替换除法）
    result = addIdentityChains(result);
    
    return result;
}
