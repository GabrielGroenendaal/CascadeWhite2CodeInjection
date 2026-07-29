using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfStoredEQ : ScriptFuncJumpBase
{
    public override string Name => "JumpIfStoredEQ";
    public override int Id => 0x15;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeStored("value"), new ScriptArgTypeLabel()];
}