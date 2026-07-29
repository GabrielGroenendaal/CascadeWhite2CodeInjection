using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncMultiplyScore : ScriptFunc
{
    public override string Name => "MultiplyScore";
    public override int Id => 0x2B;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeMultiplier("value")];
}