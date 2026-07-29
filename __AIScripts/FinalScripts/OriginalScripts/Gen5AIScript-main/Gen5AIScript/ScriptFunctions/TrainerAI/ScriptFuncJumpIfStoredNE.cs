using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfStoredNE : ScriptFuncJumpBase
{
    public override string Name => "JumpIfStoredNE";
    public override int Id => 0x16;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeStored("value"), new ScriptArgTypeLabel()];
}