using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfRandEQ : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfRandEQ";
    public override int Id => 0x02;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel("address")];
}