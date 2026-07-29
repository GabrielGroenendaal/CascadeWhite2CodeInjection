using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetPowerOfStoredMove : ScriptFunc
{
    public override string Name => "GetPowerOfStoredMove";
    public override int Id => 0x49;

    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("power");
}