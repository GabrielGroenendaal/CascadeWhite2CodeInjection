using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfFieldEffectEQ : ScriptFuncJumpBase
{
    public override string Name => "JumpIfFieldEffectEQ";
    public override int Id => 0x56;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeFieldEffect(), new ScriptArgTypeLabel()];
}