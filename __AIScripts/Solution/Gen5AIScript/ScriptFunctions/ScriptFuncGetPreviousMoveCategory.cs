using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetPreviousMoveCategory : ScriptFunc
{
    public override string Name => "GetLastPreviousCategory";
    public override int Id => 0x5E;
    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeMoveCategory();
}