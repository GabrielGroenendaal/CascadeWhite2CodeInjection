using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfNoDamagingMove : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfNoDamagingMove";
    public override int Id => 0x1E;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}