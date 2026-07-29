using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfStoredLT : ScriptFuncJumpBase
{
    public override string Name => "JumpIfStoredLT";
    public override int Id => 0x13;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeStored("value"), new ScriptArgTypeLabel()];
}