using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetMoveBasePower : ScriptFunc
{
    public override string Name => "GetMoveBasePower";
    public override int Id => 0x21;

    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("power");
}