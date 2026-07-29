using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetMoveEffect : ScriptFunc
{
    public override string Name => "GetMoveEffect";
    public override int Id => 0x29;

    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeMoveEffect();
}