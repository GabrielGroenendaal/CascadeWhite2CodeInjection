using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetGetProtectCount : ScriptFunc
{
    public override string Name => "GetProtectCount";
    public override int Id => 0x4B;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("count");
}