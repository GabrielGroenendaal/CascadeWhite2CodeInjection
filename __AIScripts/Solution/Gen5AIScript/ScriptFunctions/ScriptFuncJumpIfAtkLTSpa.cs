using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfAtkLTSpa : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfAtkLTSpa";
    public override int Id => 0x75;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}