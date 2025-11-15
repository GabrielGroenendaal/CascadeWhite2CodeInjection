using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetMovePP : ScriptFunc
{
    public override string Name => "GetMovePP";
    public override int Id => 0x5B;
    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("pp");
}