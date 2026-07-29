using System.Collections;

namespace Gen5AIScript.ScriptArgTypes;

public abstract class ScriptArgTypeFlags(string name) : ScriptArgType(name)
{
    private class FlagComparer : IComparer
    {
        public int Compare(object? x, object? y)
        {
            return string.CompareOrdinal(((Tuple<string, uint>)x!).Item1, ((Tuple<string, uint>)y!).Item1);
        }
    }

    protected abstract Tuple<string, uint>[] FlagValues { get; }

    public override uint FromString(ScriptContext context, int offset,  string str)
    {
        var values = str.Split("|");
        var comparer = new FlagComparer();
        return values.Aggregate<string?, uint>(0, (current, value) => current | (uint)Array.BinarySearch(FlagValues, value, comparer));
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        List<string> values = [];
        values.AddRange(from tuple in FlagValues where (value & tuple.Item2) != 0 select tuple.Item1);
        return string.Join("|", values);
    }
}