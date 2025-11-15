using System.Globalization;

namespace Gen5AIScript.ScriptArgTypes;

public abstract class ScriptArgTypeStringBase(string name) : ScriptArgType(name)
{
    protected abstract string[] ValueNames { get; }
    protected abstract ref string[]? SortedValueIdNames { get; }
    protected abstract ref int[]? IdToAlpha { get; }
    protected abstract ref int[]? AlphaToId { get; }

    private void TryCacheFields()
    {
        if (SortedValueIdNames != null && IdToAlpha != null && AlphaToId != null)
            return; // already cached
        
        var length = ValueNames.Length;

        SortedValueIdNames = new string[length];
        for (var i = 0; i < length; ++i)
        {
            SortedValueIdNames[i] = ToIdStr(ValueNames[i]);
        }

        Array.Sort(SortedValueIdNames);

        AlphaToId = new int[length];
        IdToAlpha = new int[length];
        for (var i = 0; i < length; ++i)
        {
            var index = Array.BinarySearch(SortedValueIdNames, ToIdStr(ValueNames[i]));
            AlphaToId[index] = i;
            IdToAlpha[i] = index;
        }
    }

    protected abstract string Prefix { get; }
    private static string EndStr => "END";
    private static uint EndValue => 0xFFFFFFFF;

    public override uint FromString(ScriptContext context, int offset, string str)
    {
        if (str == EndStr)
            return EndValue;

        TryCacheFields();
        if (SortedValueIdNames == null || AlphaToId == null)
            throw new Exception();

        if (str.StartsWith(Prefix))
            str = str[(Prefix.Length + 1)..];

        var idStr = ToIdStr(str);
        var alphaIndex = Array.BinarySearch(SortedValueIdNames, idStr);
        if (alphaIndex > -1 && alphaIndex < AlphaToId.Length)
            return (uint)AlphaToId[alphaIndex];

        return FromErrorStr(str);
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        if (value == EndValue)
            return EndStr;

        TryCacheFields();
        if (SortedValueIdNames == null || IdToAlpha == null)
            throw new Exception();

        if (value >= IdToAlpha.Length)
            return GetErrorStr(value);

        var alphaIndex = IdToAlpha[value];
        return $"{Prefix}.{SortedValueIdNames[alphaIndex]}";
    }

    private static string ToIdStr(string str)
    {
        return str.ToLower().Replace(" ", "_").Replace("'", "").Replace(".", "");
    }
}