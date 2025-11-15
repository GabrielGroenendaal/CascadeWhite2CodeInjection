using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfTargetWillNotFaint : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfTargetWillNot";
    public override string Description => "Jumps to the specified label if the move will faint the specified target";
    public override int Id => 0x37;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}