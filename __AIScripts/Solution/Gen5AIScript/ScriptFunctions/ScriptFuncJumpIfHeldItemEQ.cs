using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHeldItemEQ : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHeldItemEQ";
    public override int Id => 0x55;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeItem(), new ScriptArgTypeLabel()];
}