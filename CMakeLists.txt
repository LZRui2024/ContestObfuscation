# CMakeList.txt: ContestObfuscation 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.10)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ContestObfuscation")

# 将源代码添加到此项目的可执行文件。
add_executable (ContestObfuscation 
    "src/main/main.cpp"
    "src/random_string/RandomStringGenerator.cpp"
    "src/function_obfuscation/FunctionObfuscator.cpp"
    "src/macro_replacement/MacroReplacer.cpp"
    "src/irrelevant_code/IrrelevantCodeInjector.cpp"
    "src/useless_functions/UselessFunctionGenerator.cpp"
    "src/function_jump/FunctionJumpInjector.cpp"
    "src/variable_obfuscation/VariableObfuscator.cpp"
    "src/constant_encryption/ConstantEncryptor.cpp"
    "src/string_encryption/StringEncryptor.cpp"
    "src/code_chunking/CodeChunker.cpp"
    "src/control_flow_flattening/ControlFlowFlattener.cpp"
    "src/exception_obfuscation/ExceptionObfuscator.cpp"
    "src/function_inlining/FunctionInliner.cpp"
    "src/instruction_replacement/InstructionReplacer.cpp"
    "src/loop_transformation/LoopTransformer.cpp"
    "src/string_splitting/StringSplitter.cpp"
    "src/equivalence_replacement/EquivalenceReplacer.cpp"
    "src/fake_control_flow/FakeControlFlow.cpp"
    "src/instruction_reordering/InstructionReordering.cpp"
    "src/data_flow_obfuscation/DataFlowObfuscation.cpp"
    "src/anti_semantic/AntiSemantic.cpp"
    "src/junk_instructions/JunkInstructions.cpp"
    "src/advanced_string_encryption/AdvancedStringEncryption.cpp"
    "src/code_expansion/CodeExpansion.cpp"
    "src/advanced_control_flow/AdvancedControlFlow.cpp"
    "src/template_metaprogramming/TemplateMetaprogramming.cpp"
    "src/constexpr_obfuscation/ConstexprObfuscation.cpp"
    "src/memory_obfuscation/MemoryObfuscation.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ContestObfuscation PROPERTY CXX_STANDARD 20)
endif()

# 添加 UTF-8 编码支持
if(MSVC)
  target_compile_options(ContestObfuscation PRIVATE /utf-8)
endif()

# TODO: 如有需要，请添加测试并安装目标。
