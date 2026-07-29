using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetEffectOfStoredMove : ScriptFunc
{
    public override string Name => "GetEffectOfStoredMove";
    public override int Id => 0x4A;

    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeMoveEffect();
}