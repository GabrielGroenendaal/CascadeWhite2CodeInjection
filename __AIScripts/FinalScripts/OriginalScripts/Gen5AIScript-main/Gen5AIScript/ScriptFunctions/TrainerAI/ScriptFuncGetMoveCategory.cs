using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetMoveCategory : ScriptFunc
{
    public override string Name => "GetMoveCategory";
    public override int Id => 0x5D;
    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeMoveCategory();
}