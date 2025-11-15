using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfUserAboutToWakeUp : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfUserAboutToWakeUp";
    public override string Description => "Jumps to the specified label if the user is about to wake up";
    public override int Id => 0x66;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}