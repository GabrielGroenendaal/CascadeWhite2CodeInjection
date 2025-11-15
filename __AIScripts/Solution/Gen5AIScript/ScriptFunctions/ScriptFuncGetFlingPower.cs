using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetFlingPower : ScriptFunc
{
    public override string Name => "GetFlingPower";
    public override string Description => "Stores the power of Fling using the item of the specified Pokémon.";
    public override int Id => 0x5A;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePosType()];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("power");
}