using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfUserWillFaint_Priority : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfEnemyHasKO_Priority";
    public override string Description => "Jumps to the specified label if the target can faint the user (used with priority logic)";
    public override int Id => 0x68;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}