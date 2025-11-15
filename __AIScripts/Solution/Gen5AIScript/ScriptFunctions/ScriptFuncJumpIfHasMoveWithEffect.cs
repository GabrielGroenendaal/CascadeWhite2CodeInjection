using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasMoveWithEffect : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasMoveWithEffect";
    public override int Id => 0x3A;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeMoveEffect(), new ScriptArgTypeLabel()];
}