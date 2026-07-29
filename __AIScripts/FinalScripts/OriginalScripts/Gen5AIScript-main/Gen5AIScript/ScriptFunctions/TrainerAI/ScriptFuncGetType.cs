using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetType : ScriptFunc
{
    public override string Name => "GetType";
    public override int Id => 0x20;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePosType()];
    public override ScriptArgType ReturnType => new ScriptArgTypePokeType();
}