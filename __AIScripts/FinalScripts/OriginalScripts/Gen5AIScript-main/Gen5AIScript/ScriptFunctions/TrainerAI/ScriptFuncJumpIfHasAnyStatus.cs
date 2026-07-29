using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHasAnyStatus : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHasAnyStatus";
    public override int Id => 0x09;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}