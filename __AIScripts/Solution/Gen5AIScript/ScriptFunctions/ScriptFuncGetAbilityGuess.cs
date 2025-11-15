using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetAbilityGuess : ScriptFunc
{
    public override string Name => "GetAbilityGuess";
    public override int Id => 0x2A;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeAbility();
}