using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasSubstitute : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasSubstitute";
    public override int Id => 0x6D;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}