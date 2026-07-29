using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfStoredIsInList : ScriptFuncListBase
{
    public override string Name => "JumpIfStoredIsInList";
    public override int Id => 0x1B;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeDataLabel(), new ScriptArgTypeLabel()];

    public override bool TryGetDataAddress(byte[] buffer, int funcOffset, out int address, out int length, out ScriptArgType? dataType)
    {
        dataType = null;
        return TryGetDataAddress(buffer, funcOffset, out address, out length, 0);
    }

    protected override int GetDataOffsetAddress(byte[] buffer, int funcOffset)
    {
        return funcOffset + (int)GetArgValue(buffer, funcOffset, 0) + 6;
    }
}