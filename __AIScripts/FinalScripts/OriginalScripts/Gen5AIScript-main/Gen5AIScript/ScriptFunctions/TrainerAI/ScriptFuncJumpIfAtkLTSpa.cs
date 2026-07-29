using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfAtkLTSpa : ScriptFuncJumpBase
{
    public override string Name => "JumpIfAtkLTSpa";
    public override int Id => 0x75;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}