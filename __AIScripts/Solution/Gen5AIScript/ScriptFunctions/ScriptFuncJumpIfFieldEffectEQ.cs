using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfFieldEffectEQ : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfFieldEffectEQ";
    public override int Id => 0x56;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeFieldEffect(), new ScriptArgTypeLabel()];
}