using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfAtkEQSpa : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfAtkEQSpa";
    public override int Id => 0x77;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel("address")];
}