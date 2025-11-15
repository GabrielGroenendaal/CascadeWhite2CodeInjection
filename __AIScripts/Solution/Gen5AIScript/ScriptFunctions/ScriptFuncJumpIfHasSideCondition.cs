using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasSideCondition : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasSideCondition";
    public override int Id => 0x11;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeSideCondition(), new ScriptArgTypeLabel()];
}