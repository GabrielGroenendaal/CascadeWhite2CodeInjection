using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetWeather : ScriptFunc
{
    public override string Name => "GetWeather";
    public override int Id => 0x2F;
    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeWeather();
}