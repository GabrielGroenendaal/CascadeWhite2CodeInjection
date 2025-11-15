using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfCanUseLastResort : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfCanUseLastResort";
    public override int Id => 0x5C;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}