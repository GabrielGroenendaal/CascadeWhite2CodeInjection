using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfPartyHasReducedPP : ScriptFuncJumpBase
{
    public override string Name => "JumpIfPartyHasReducedPP";
    public override string Description => "Jumps to the specified label if there is at least one member of the party who does not have full PP on a move.";
    public override int Id => 0x59;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}