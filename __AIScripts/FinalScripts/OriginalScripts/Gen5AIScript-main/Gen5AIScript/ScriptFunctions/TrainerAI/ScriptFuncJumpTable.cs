using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpTable : ScriptFunc
{
    public override string Name => "JumpTable";
    public override int Id => 0x73;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeTableType(), new ScriptArgTypeInt("size"), new ScriptArgTypeDataLabel()];
    public override bool IsJump => true;

    public override void UpdateContext(ScriptContext context, byte[] buffer, int funcOffset)
    {
        base.UpdateContext(context, buffer, funcOffset);

        var firstIndex = (int)GetArgValue(buffer, funcOffset, 0);
        var lastIndex = (int)GetArgValue(buffer, funcOffset, 1);

        var count = lastIndex - firstIndex + 1;

        var dataOffset = (int)GetArgValue(buffer, funcOffset, 2);
        var dataAddressOffset = funcOffset + Size + dataOffset;

        for (var i = 0; i < count; ++i)
        {
            var element = new ScriptArgTypeMapElement($"element_{i:000}", new ScriptArgTypeMoveEffect(), new ScriptArgTypeLabel(), dataAddressOffset);
            context.SetDataOffsetSectionType(dataAddressOffset + i * 4, element);
        }
    }

    public override int[] GetJumpAddresses(byte[] buffer, int funcOffset)
    {
        // Maybe...
        var minIndex = (int)GetArgValue(buffer, funcOffset, 0);
        var maxIndex = (int)GetArgValue(buffer, funcOffset, 1);
        var dataOffset = (int)GetArgValue(buffer, funcOffset, 2);
        var dataAddressOffset = funcOffset + Size + dataOffset;

        var addressCount = maxIndex - minIndex + 1;
        var addresses = new int[addressCount];
        for (var i = 0; i < addressCount; ++i)
        {
            var index = minIndex + i;
            var indexOffset = dataAddressOffset + index * 4;
            var jumpOffset = BitConverter.ToInt32(buffer, indexOffset);
            addresses[i] = funcOffset + Size + jumpOffset + dataOffset;
        }

        return addresses;
    }

    public override bool TryGetDataAddress(byte[] buffer, int funcOffset, out int address, out int length, out ScriptArgType? dataType)
    {
        var size = (int)GetArgValue(buffer, funcOffset, 1);
        var dataOffset = (int)GetArgValue(buffer, funcOffset, 2);
        address = funcOffset + Size + dataOffset;
        length = size + 1;

        dataType = new ScriptArgTypeMapElement("element", new ScriptArgTypeMoveEffect(), new ScriptArgTypeLabel(), address);
        
        return true;
    }
}