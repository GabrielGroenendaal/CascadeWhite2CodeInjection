using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetPokeHasAbility : ScriptFunc
{
    public override string Name => "GetPokeHasAbility";
    public override string Description => "Stores TRUE if the guessed ability of the specified Pokémon matches the specified one.";
    public override int Id => 0x53;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeAbility()];
    public override ScriptArgType ReturnType => new ScriptArgTypeBool("result");
}