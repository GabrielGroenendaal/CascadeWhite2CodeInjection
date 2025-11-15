using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfMoveNE : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfMoveNE";
    public override int Id => 0x1A;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeMove(), new ScriptArgTypeLabel()];

}