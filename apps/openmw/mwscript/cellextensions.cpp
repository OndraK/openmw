
#include "cellextensions.hpp"

#include <components/compiler/extensions.hpp>

#include <components/interpreter/interpreter.hpp>
#include <components/interpreter/runtime.hpp>
#include <components/interpreter/opcodes.hpp>

#include "../mwworld/world.hpp"

#include "interpretercontext.hpp"

namespace MWScript
{
    namespace Cell
    {
        class OpCellChanged : public Interpreter::Opcode0
        {
            public:
            
                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context
                        = static_cast<InterpreterContext&> (runtime.getContext());
                        
                    runtime.push (context.getWorld().hasCellChanged() ? 1 : 0);
                } 
        };

        class OpCOC : public Interpreter::Opcode0
        {
            public:
            
                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context
                        = static_cast<InterpreterContext&> (runtime.getContext());
                        
                    std::string cell = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();                        
                        
                    ESM::Position pos;
                    pos.pos[0] = pos.pos[1] = pos.pos[2] = 0;
                    pos.rot[0] = pos.rot[1] = pos.rot[2] = 0;
                    context.getWorld().changeCell (cell, pos);
                } 
        };
    
        const int opcodeCellChanged = 0x2000000;
        const int opcodeCOC = 0x2000026;
    
        void registerExtensions (Compiler::Extensions& extensions)
        {
            extensions.registerFunction ("cellchanged", 'l', "", opcodeCellChanged);
            extensions.registerInstruction ("coc", "S", opcodeCOC);
            extensions.registerInstruction ("centeroncell", "S", opcodeCOC);
        }
        
        void installOpcodes (Interpreter::Interpreter& interpreter)
        {
            interpreter.installSegment5 (opcodeCellChanged, new OpCellChanged);
            interpreter.installSegment5 (opcodeCOC, new OpCOC);
        }
    }
}

