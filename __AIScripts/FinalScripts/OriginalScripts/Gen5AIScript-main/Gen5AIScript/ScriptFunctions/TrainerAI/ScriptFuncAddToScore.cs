using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncAddToScore : ScriptFunc
{
    public override string Name => "AddToScore";
    public override int Id => 0x04;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value")];
}