using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfEffectivenessEQ : ScriptFuncJumpBase
{
    public override string Name => "JumpIfEffectivenessEQ";
    public override int Id => 0x2C;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeEffectiveness(), new ScriptArgTypeLabel()];
}