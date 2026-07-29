using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetMaxMovePower : ScriptFunc
{
    public override string Name => "GetMaxMovePower";
    public override int Id => 0x22;

    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("power");
}