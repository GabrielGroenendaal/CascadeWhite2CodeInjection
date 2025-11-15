using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfRandLT : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfRandLT";
    public override int Id => 0x00;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel("address")];
}