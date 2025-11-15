using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetSimulationMultiplier : ScriptFunc
{
    public override string Name => "GetSimulationMultiplier";
    public override int Id => 0x3E;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType? ReturnType => new ScriptArgTypeMultiplier("simulation_multiplier");
}