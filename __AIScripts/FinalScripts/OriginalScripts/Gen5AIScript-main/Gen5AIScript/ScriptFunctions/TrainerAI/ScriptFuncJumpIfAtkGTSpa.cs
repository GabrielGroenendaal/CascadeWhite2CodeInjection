using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfAtkGTSpa : ScriptFuncJumpBase
{
    public override string Name => "JumpIfAtkGTSpa";
    public override int Id => 0x76;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}