using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfMoveEffectEQ : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfMoveEffectEQ";
    public override int Id => 0x30;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeMoveEffect(), new ScriptArgTypeLabel()];

}