using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfAttackForeseen : ScriptFuncJumpBase
{
    public override string Name => "JumpIfAttackForeseen";
    public override string Description => "Jumps to the specified label if the specified Pokémon has been targeted with Future Sight or Doom Desire.";
    public override int Id => 0x74;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}