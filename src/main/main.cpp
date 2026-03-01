#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../random_string/RandomStringGenerator.h"
#include "../function_obfuscation/FunctionObfuscator.h"
#include "../macro_replacement/MacroReplacer.h"
#include "../irrelevant_code/IrrelevantCodeInjector.h"
#include "../useless_functions/UselessFunctionGenerator.h"
#include "../function_jump/FunctionJumpInjector.h"
#include "../variable_obfuscation/VariableObfuscator.h"
#include "../constant_encryption/ConstantEncryptor.h"
#include "../string_encryption/StringEncryptor.h"
#include "../code_chunking/CodeChunker.h"
#include "../control_flow_flattening/ControlFlowFlattener.h"
#include "../instruction_replacement/InstructionReplacer.h"
#include "../string_splitting/StringSplitter.h"
#include "../function_inlining/FunctionInliner.h"
#include "../loop_transformation/LoopTransformer.h"
#include "../exception_obfuscation/ExceptionObfuscator.h"
#include "../equivalence_replacement/EquivalenceReplacer.h"
#include "../fake_control_flow/FakeControlFlow.h"
#include "../instruction_reordering/InstructionReordering.h"
#include "../data_flow_obfuscation/DataFlowObfuscation.h"
#include "../anti_semantic/AntiSemantic.h"
#include "../junk_instructions/JunkInstructions.h"
#include "../advanced_string_encryption/AdvancedStringEncryption.h"
#include "../code_expansion/CodeExpansion.h"
#include "../advanced_control_flow/AdvancedControlFlow.h"
#include "../template_metaprogramming/TemplateMetaprogramming.h"
#include "../constexpr_obfuscation/ConstexprObfuscation.h"
#include "../memory_obfuscation/MemoryObfuscation.h"

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ContestObfuscation <input_file> <output_file>" << std::endl;
        return 1;
    }
    
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    
    std::string code = readFile(input_file);
    std::cout << "Step 0: Read file completed." << std::endl;
    
    // 提取原始代码中的#include指令和using namespace语句
    std::string includes = "";
    std::string using_namespace = "";
    size_t pos = 0;
    while (pos < code.length()) {
        size_t include_pos = code.find("#include", pos);
        size_t using_pos = code.find("using namespace", pos);
        
        if (include_pos != std::string::npos && (using_pos == std::string::npos || include_pos < using_pos)) {
            size_t end_pos = code.find("\n", include_pos);
            if (end_pos == std::string::npos) break;
            includes += code.substr(include_pos, end_pos - include_pos + 1);
            pos = end_pos + 1;
        } else if (using_pos != std::string::npos) {
            size_t end_pos = code.find("\n", using_pos);
            if (end_pos == std::string::npos) break;
            using_namespace += code.substr(using_pos, end_pos - using_pos + 1);
            pos = end_pos + 1;
        } else {
            break;
        }
    }
    
    // 移除原始代码中的#include指令和using namespace语句
    std::string code_without_includes = code.substr(pos);
    
    // 1. 函数名混淆
    std::cout << "Step 1: Obfuscating functions..." << std::endl;
    FunctionObfuscator function_obfuscator;
    std::string code_with_function_obfuscation = function_obfuscator.obfuscateFunctions(code_without_includes);
    std::cout << "Step 1: Functions obfuscated." << std::endl;
    
    // 2. 注入无关代码
    std::cout << "Step 2: Injecting irrelevant code..." << std::endl;
    IrrelevantCodeInjector irrelevant_code_injector;
    std::string code_with_irrelevant = irrelevant_code_injector.injectIrrelevantCode(code_with_function_obfuscation);
    std::cout << "Step 2: Irrelevant code injected." << std::endl;
    
    // 3. 生成无用函数
    std::cout << "Step 3: Generating useless functions..." << std::endl;
    UselessFunctionGenerator useless_function_generator;
    std::string useless_functions = useless_function_generator.generateUselessFunctions(10);
    std::cout << "Step 3: Useless functions generated." << std::endl;
    
    // 4. 生成函数跳转
    std::cout << "Step 4: Injecting function jumps..." << std::endl;
    FunctionJumpInjector function_jump_injector;
    std::string code_with_jumps = function_jump_injector.injectFunctionJumps(code_with_irrelevant);
    std::cout << "Step 4: Function jumps injected." << std::endl;
    std::string jump_functions = function_jump_injector.generateJumpFunctions();
    std::cout << "Step 4: Jump functions generated." << std::endl;
    
    // 5. 变量名混淆
    std::cout << "Step 5: Obfuscating variables..." << std::endl;
    VariableObfuscator variable_obfuscator;
    std::string code_with_variable_obfuscation = variable_obfuscator.obfuscateVariables(code_with_jumps);
    std::cout << "Step 5: Variables obfuscated." << std::endl;
    
    // 6. 常量加密
    std::cout << "Step 6: Encrypting constants..." << std::endl;
    ConstantEncryptor constant_encryptor;
    std::string code_with_constant_encryption = constant_encryptor.encryptConstants(code_with_variable_obfuscation);
    std::cout << "Step 6: Constants encrypted." << std::endl;
    
    // 7. 字符串加密
    std::cout << "Step 7: Encrypting strings..." << std::endl;
    StringEncryptor string_encryptor;
    auto string_result = string_encryptor.encryptStrings(code_with_constant_encryption);
    std::string code_with_string_encryption = string_result.first;
    std::string decrypt_function = string_result.second;
    std::cout << "Step 7: Strings encrypted." << std::endl;
    
    // 8. 控制流平坦化 (在循环变换之前执行)
    std::cout << "Step 8: Flattening control flow..." << std::endl;
    ControlFlowFlattener control_flow_flattener;
    std::string code_with_flattening = control_flow_flattener.flattenControlFlow(code_with_string_encryption);
    std::cout << "Step 8: Control flow flattened." << std::endl;
    
    // 9. 代码分块
    std::cout << "Step 9: Chunking code..." << std::endl;
    CodeChunker code_chunker;
    std::string code_with_chunking = code_chunker.chunkCode(code_with_flattening);
    std::cout << "Step 9: Code chunked." << std::endl;
    
    // 10. 指令替换
    std::cout << "Step 10: Replacing instructions..." << std::endl;
    InstructionReplacer instruction_replacer;
    std::string code_with_replacement = instruction_replacer.replaceInstructions(code_with_chunking);
    std::cout << "Step 10: Instructions replaced." << std::endl;
    
    // 11. 字符串分拆与重组（暂时禁用）
    std::cout << "Step 11: Splitting strings..." << std::endl;
    StringSplitter string_splitter;
    std::string code_with_splitting = code_with_replacement;  // 直接跳过
    std::cout << "Step 11: Strings split." << std::endl;
    
    // 12. 函数内联与反内联
    std::cout << "Step 12: Inlining functions..." << std::endl;
    FunctionInliner function_inliner;
    std::string code_with_inlining = function_inliner.inlineFunctions(code_with_splitting);
    std::cout << "Step 12: Functions inlined." << std::endl;
    
    // 13. 循环变换
    std::cout << "Step 13: Transforming loops..." << std::endl;
    LoopTransformer loop_transformer;
    std::string code_with_loop_transformation = loop_transformer.transformLoops(code_with_inlining);
    std::cout << "Step 13: Loops transformed." << std::endl;
    
    // 14. 异常处理混淆（已在第 24 步实现更高级的版本）
    std::cout << "Step 14: Skipping old exception obfuscation..." << std::endl;
    std::string code_with_exception_obfuscation = code_with_loop_transformation;
    std::cout << "Step 14: Skipped." << std::endl;
    
    // 15. 等价表达式替换（对抗 AI 分析）
    std::cout << "Step 15: Replacing with equivalent expressions..." << std::endl;
    EquivalenceReplacer equivalence_replacer;
    std::string code_with_equivalence = equivalence_replacer.replaceEquivalences(code_with_exception_obfuscation);
    std::cout << "Step 15: Equivalent expressions replaced." << std::endl;
    
    // 16. 指令重排（对抗 AI 分析）
    std::cout << "Step 16: Reordering instructions..." << std::endl;
    InstructionReordering instruction_reordering;
    std::string code_with_reordering = instruction_reordering.reorderInstructions(code_with_equivalence);
    std::cout << "Step 16: Instructions reordered." << std::endl;
    
    // 17. 数据流混淆（对抗 AI 分析）
    std::cout << "Step 17: Obfuscating data flow..." << std::endl;
    DataFlowObfuscation data_flow_obfuscation;
    std::string code_with_data_flow = data_flow_obfuscation.obfuscateDataFlow(code_with_reordering);
    std::cout << "Step 17: Data flow obfuscated." << std::endl;
    
    // 18. 反语义分析（对抗 AI 分析）
    std::cout << "Step 18: Adding anti-semantic analysis..." << std::endl;
    AntiSemantic anti_semantic;
    std::string code_with_anti_semantic = anti_semantic.addAntiSemanticAnalysis(code_with_data_flow);
    std::cout << "Step 18: Anti-semantic analysis added." << std::endl;
    
    // 19. 生成宏定义
    std::cout << "Step 19: Generating macros..." << std::endl;
    MacroReplacer macro_replacer;
    std::string macros = macro_replacer.generateMacros();
    std::cout << "Step 19: Macros generated." << std::endl;
    
    // 20. 替换宏
    std::cout << "Step 20: Replacing macros..." << std::endl;
    std::string code_with_macros = macro_replacer.replaceMacros(code_with_anti_semantic);
    std::cout << "Step 20: Macros replaced." << std::endl;
    
    // 21. 虚假控制流（对抗 AI 分析）- 在宏替换之后执行，避免类型关键字被替换
    std::cout << "Step 21: Adding fake control flow..." << std::endl;
    FakeControlFlow fake_control_flow;
    std::string code_with_fake_flow = fake_control_flow.addFakeControlFlow(code_with_macros);
    std::cout << "Step 21: Fake control flow added." << std::endl;
    
    // 22. 添加花指令（对抗 AI 分析）
    std::cout << "Step 22: Adding junk instructions..." << std::endl;
    JunkInstructions junk_instructions;
    std::string code_with_junk = junk_instructions.addJunkInstructions(code_with_fake_flow);
    std::cout << "Step 22: Junk instructions added." << std::endl;
    
    // 23. 代码膨胀（循环展开）
    std::cout << "Step 23: Expanding code..." << std::endl;
    CodeExpansion code_expansion;
    std::string code_with_expansion = code_expansion.expandLoops(code_with_junk);
    std::cout << "Step 23: Code expanded." << std::endl;
    
    // 24. 异常混淆
    std::cout << "Step 24: Adding exception handling..." << std::endl;
    ExceptionObfuscator exception_obfuscator;
    std::string code_with_exceptions = exception_obfuscator.addExceptionHandling(code_with_expansion);
    std::cout << "Step 24: Exception handling added." << std::endl;
    
    // 25. 控制流平坦化增强
    std::cout << "Step 25: Adding advanced control flow flattening..." << std::endl;
    AdvancedControlFlow advanced_control_flow;
    std::string code_with_advanced_flow = advanced_control_flow.addAdvancedFlattening(code_with_exceptions);
    std::cout << "Step 25: Advanced control flow flattening added." << std::endl;
    
    // 26. 模板元编程混淆
    std::cout << "Step 26: Adding template metaprogramming..." << std::endl;
    TemplateMetaprogramming template_metaprogramming;
    std::string code_with_templates = template_metaprogramming.addTemplateMetaprogramming(code_with_advanced_flow);
    std::cout << "Step 26: Template metaprogramming added." << std::endl;
    
    // 27. 常量表达式混淆
    std::cout << "Step 27: Obfuscating constants with constexpr..." << std::endl;
    ConstexprObfuscation constexpr_obfuscation;
    std::string code_with_constexpr = constexpr_obfuscation.obfuscateConstants(code_with_templates);
    std::cout << "Step 27: Constants obfuscated with constexpr." << std::endl;
    
    // 28. 内存操作混淆
    std::cout << "Step 28: Adding memory operations..." << std::endl;
    MemoryObfuscation memory_obfuscation;
    std::string code_with_memory_ops = memory_obfuscation.addMemoryOperations(code_with_constexpr);
    std::cout << "Step 28: Memory operations added." << std::endl;
    
    // 确保包含必要的头文件
    if (includes.find("#include <iostream>") == std::string::npos) {
        includes += "#include <iostream>\n";
    }
    if (includes.find("#include <vector>") == std::string::npos) {
        includes += "#include <vector>\n";
    }
    if (includes.find("#include <string>") == std::string::npos) {
        includes += "#include <string>\n";
    }
    
    // 组合所有内容
    std::string obfuscated_code = includes + "\n" + using_namespace + "\n" + macros + decrypt_function + useless_functions + jump_functions + code_with_memory_ops;
    
    writeFile(output_file, obfuscated_code);
    
    std::cout << "Obfuscation completed!" << std::endl;
    std::cout << "Input file: " << input_file << std::endl;
    std::cout << "Output file: " << output_file << std::endl;
    
    return 0;
}