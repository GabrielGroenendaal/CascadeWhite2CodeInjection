using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetPokeHasType : ScriptFunc
{
    public override string Name => "GetPokeHasType";
    public override int Id => 0x52;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypePokeType()];
    public override ScriptArgType ReturnType => new ScriptArgTypeBool("result");
}