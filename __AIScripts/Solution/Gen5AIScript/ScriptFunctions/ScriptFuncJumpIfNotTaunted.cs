using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfNotTaunted : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfNotTaunted";
    public override int Id => 0x50;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}