using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfStoredAND : ScriptFuncJumpBase
{
    public override string Name => "JumpIfStoredAND";
    public override int Id => 0x17;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeStored("value"), new ScriptArgTypeLabel()];
}