using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfLastMoveGTStrongest : ScriptFuncJumpBase
{
    public override string Name => "JumpIfLastMoveGTStrongest";

    public override string Description =>
        "Jumps to the specified label if a new damage calculation using the target's last move targeting the user is greater than the damage of the strongest move the user has against the target";

    public override int Id => 0x63;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeBool("random"), new ScriptArgTypeLabel()];
}