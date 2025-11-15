using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfAtkGTSpa : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfAtkGTSpa";
    public override int Id => 0x76;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}