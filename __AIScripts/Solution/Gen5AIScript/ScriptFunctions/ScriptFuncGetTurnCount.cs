using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetTurnCount : ScriptFunc
{
    public override string Name => "GetTurnCount";
    public override int Id => 0x1F;

    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("turn_count");
}