using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfMoveEffectNE : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfMoveEffectNE";
    public override int Id => 0x31;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeMoveEffect(), new ScriptArgTypeLabel()];

}