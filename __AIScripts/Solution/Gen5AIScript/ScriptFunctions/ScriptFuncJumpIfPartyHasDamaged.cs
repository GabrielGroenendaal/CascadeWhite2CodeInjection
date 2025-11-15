using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfPartyHasDamage : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfPartyHasDamage";
    public override string Description => "Jumps to the specified label if there is at least one member of the party who is not at full HP.";
    public override int Id => 0x58;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}