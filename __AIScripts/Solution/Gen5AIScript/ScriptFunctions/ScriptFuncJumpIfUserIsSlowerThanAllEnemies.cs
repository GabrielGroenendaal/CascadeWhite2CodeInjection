using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfUserIsSlowerThanAllEnemies : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfUserIsSlowerThanAllEnemies";
    public override string Description => "Jumps to the specified label if the user is slower than all enemies";
    public override int Id => 0x67;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}