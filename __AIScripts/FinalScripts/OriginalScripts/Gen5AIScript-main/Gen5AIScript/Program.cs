// See https://aka.ms/new-console-template for more information

using System.Text;
using Gen5AIScript;
using Gen5AIScript.ScriptFunctionLibraries;
using Gen5AIScript.ScriptLines;

const string scriptFileExt = ".txt";
const string binExt = ".bin";

{
    var isDebugMode = GetIsDebugMode();

    string? path = null;
    var command = GetArgStr(1, "command", cmd => cmd is "-c" or "-d", "-c (compile) or -d (decompile)");
    var type = GetArgStr(2, "type", type => type is "-ai" or "-anim", "-ai (trainer AI) or -anim (animations)");

    ScriptFunctionLibrary? scriptFuncLibrary = type switch
    {
        "-ai" => new TrainerAIScriptFuncLibrary(),
        "-anim" => new AnimationScriptFuncLibrary(),
        _ => null
    };

    if (scriptFuncLibrary == null)
        return;

    switch (command)
    {
        case "-d":
        {
            path = GetArgStr(0, "path", f => File.Exists(f) || Directory.Exists(f), $"an existing {binExt} file or directory");

            var filePaths = Directory.Exists(path) ? Directory.EnumerateFiles(path, "*" + binExt).ToArray() : [path];
            foreach (var filePath in filePaths)
            {
                try
                {
                    var buffer = File.ReadAllBytes(filePath);
                    var outStr = ReadBinFile(scriptFuncLibrary, buffer, type == "-anim", isDebugMode);
                    File.WriteAllText(Path.ChangeExtension(filePath, scriptFileExt), outStr);
                }
                catch (Exception e)
                {
                    Console.Error.WriteLine(e.ToString());
                }
            }

            break;
        }
        case "-c":
        {
            var oldFilepath = GetArgStr(0, "path", file => File.Exists(file.EndsWith(scriptFileExt) ? file : file + scriptFileExt), $"an existing {scriptFileExt} file");
            path = oldFilepath + binExt;

            var lines = File.ReadAllLines(oldFilepath);
            var bytes = WriteBinFile(scriptFuncLibrary, lines, type == "-anim");
            File.WriteAllBytes(path, bytes);

            break;
        }
    }

    if (path == null)
        throw new Exception("Failed to save file with command " + command);

    Console.WriteLine("Done!");
    Console.WriteLine("Saved as " + path);
}

bool GetIsDebugMode()
{
    if (args.Length < 4)
        return false;

    return args[3].ToLower().Equals("-debug") ? true : throw new Exception($"Invalid flag {args[3]}");
}

string GetArgStr(int argIndex, string valueName, Func<string, bool> isExpectedValueFunc, string expectation)
{
    if (args.Length > argIndex)
    {
        var arg = args[argIndex].ToLower();
        return isExpectedValueFunc(arg) ? arg : throw new Exception($"Invalid {valueName} \"{args[0]}\"\nExpected {expectation}");
    }

    string? str;
    for (;;)
    {
        Console.Write($"Enter {valueName}: ");
        str = Console.ReadLine();
        str = str?.ToLower();

        if (str != null && isExpectedValueFunc(str))
            break;

        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine($"Invalid {valueName} \"{str?.ToLower()}\"");
        Console.WriteLine($"Expected {expectation}");
        Console.ResetColor();
    }

    return str;
}

string ReadBinFile(ScriptFunctionLibrary scriptFuncLibrary, byte[] buffer, bool isAnimMode, bool debugMode)
{
    var hash = buffer.Aggregate<byte, uint>(0, (current, bufferByte) => ((current << 5) + current) ^ bufferByte);

    var byteTypes = new ScriptByteType[buffer.Length];
    Dictionary<int, Tuple<ScriptFunc?, uint[]>> scriptFuncDict = new();
    var context = new ScriptContext();

    var scriptCount = 1;
    var scriptFuncQueue = new Queue<ScriptState>();

    if (isAnimMode)
    {
        scriptCount = BitConverter.ToInt32(buffer);

        for (var i = 0; i < scriptCount; i++)
        {
            var scriptOffset = BitConverter.ToInt32(buffer.AsSpan(4 + i * 0x38));
            context.AddLabel($"SCRIPT_{i + 1}", scriptOffset);

            scriptFuncQueue.Enqueue(new ScriptState(scriptOffset));
        }
    }
    else
    {
        scriptFuncQueue.Enqueue(new ScriptState());
    }

    while (scriptFuncQueue.TryDequeue(out var scriptState))
    {
        var funcOffset = scriptState.FuncOffset;
        var scriptFuncId = BitConverter.ToUInt16(buffer, funcOffset);
        var scriptFunc = scriptFuncLibrary.GetScriptFunc(scriptFuncId);

        if (scriptFunc == null)
            throw new Exception();

        if (scriptFunc.ReturnType != null)
            scriptState.ReturnType = scriptFunc.ReturnType;

        scriptFunc.UpdateContext(context, buffer, funcOffset);

        if (scriptFunc.TryGetDataAddress(buffer, funcOffset, out var address, out var length, out var dataType))
        {
            for (var i = 0; i < length; ++i)
            {
                var dataAddress = address + i * 4;
                byteTypes[dataAddress] = ScriptByteType.Data;

                dataType ??= scriptState.ReturnType;

                if (dataType != null)
                    context.SetDataOffsetSectionType(dataAddress, dataType);
            }
        }

        scriptFuncDict.TryAdd(funcOffset, new Tuple<ScriptFunc?, uint[]>(scriptFunc, new uint[scriptFunc.ArgCount]));
        var scriptFuncArgs = scriptFuncDict[funcOffset];
        var args = scriptFuncArgs.Item2;

        for (var i = 0; i < scriptFunc.ArgCount; ++i)
        {
            var argOffset = funcOffset + 2 + i * 4;
            var arg = BitConverter.ToUInt32(buffer, argOffset);

            var argType = scriptFunc.ArgTypes[i];
            argType.UpdateContext(context, scriptState, argOffset + 4, arg);

            args[i] = arg;
        }

        for (var i = 0; i < scriptFunc.Size; ++i)
            byteTypes[funcOffset + i] = ScriptByteType.Func;

        var nextOffset = funcOffset + scriptFunc.Size;

        if (scriptFunc.Continue && byteTypes[nextOffset] == ScriptByteType.Unknown)
        {
            byteTypes[nextOffset] = ScriptByteType.Locked;
            scriptFuncQueue.Enqueue(new ScriptState(nextOffset, scriptState.ReturnType));
        }

        if (!scriptFunc.IsJump)
            continue;

        var jumpAddresses = scriptFunc.GetJumpAddresses(buffer, funcOffset);
        foreach (var jumpAddress in jumpAddresses)
        {
            if (byteTypes[jumpAddress] != ScriptByteType.Unknown)
                continue;

            var labelName = $"Label_0x{jumpAddress:X4}";
            context.AddLabel(labelName, jumpAddress);

            byteTypes[jumpAddress] = ScriptByteType.Func;
            scriptFuncQueue.Enqueue(new ScriptState(jumpAddress, scriptState.ReturnType));
        }
    }

    StringBuilder sb = new();

    if (isAnimMode)
    {
        for (var i = 0; i < scriptCount; i++)
            sb.AppendLine($"- SCRIPT_{i + 1}");

        sb.AppendLine();
    }

    var startingByte = isAnimMode ? scriptCount * 0x38 + 4 : 0;
    for (var i = startingByte; i < buffer.Length;)
    {
        if (context.TryGetLabel(i, out var label))
        {
            if (sb.Length > 0)
                sb.AppendLine();

            sb.AppendLine($"{label}:");
        }

        var linePrefix = debugMode ? $"[0x{i:X4}]" : "";

        switch (byteTypes[i])
        {
            case ScriptByteType.Unknown:
            {
                var dataValue = BitConverter.ToUInt16(buffer, i);
                sb.AppendLine($"{linePrefix}\t0x{dataValue:X4} [{(int)dataValue}]");
                i += 2;
                continue;
            }
            case ScriptByteType.Func:
            {
                if (!scriptFuncDict.TryGetValue(i, out var scriptFuncStrs))
                {
                    i += 2;
                    continue;
                }

                var scriptFunc = scriptFuncStrs.Item1;
                if (scriptFunc == null)
                    throw new Exception();

                var args = scriptFuncStrs.Item2;
                var argStrs = new string?[args.Length];
                for (var j = 0; j < args.Length; ++j)
                {
                    var argType = scriptFunc.ArgTypes[j];
                    var argOffset = i + 2 + j * 4;
                    argStrs[j] = argType.FromData(context, argOffset + 4, args[j]);
                }

                sb.AppendLine($"{linePrefix}\t{scriptFunc.Name}({string.Join(", ", argStrs)})");

                i += scriptFunc.Size;

                if (scriptFunc.AddSpaceBelow)
                    sb.AppendLine();

                if (scriptFunc.ReturnType != null)
                    context.ReturnType = scriptFunc.ReturnType;

                continue;
            }
            case ScriptByteType.Locked:
            // Treat Locked (which is an error) as data
            case ScriptByteType.Data:
            {
                var dataValue = BitConverter.ToUInt32(buffer, i);

                var dataSectionType = context.GetDataSectionType(i);
                if (dataSectionType != null)
                    sb.AppendLine($"{linePrefix}\t{dataSectionType.FromData(context, i, dataValue)}");
                else
                    sb.AppendLine($"{linePrefix}\t0x{dataValue:X8} [{(int)dataValue}]");

                i += 4;

                continue;
            }
            default:
                throw new ArgumentOutOfRangeException("");
        }
    }

    return sb.ToString();
}

byte[] WriteBinFile(ScriptFunctionLibrary scriptFuncLibrary, string[] lines, bool isAnimMode)
{
    var context = new ScriptContext();

    var scriptLines = new List<ScriptLine>();

    var offset = isAnimMode ? 4 : 0;
    var scriptLabels = new List<string>();
    var scriptLabelOffsets = new List<int>();

    foreach (var fullLine in lines)
    {
        if (isAnimMode && fullLine.StartsWith('-'))
        {
            var scriptLabel = fullLine[1..].Trim();
            offset += 0x38;
            scriptLabels.Add(scriptLabel);
            continue;
        }

        // Label
        var colonIndex = fullLine.IndexOf(':');
        if (colonIndex > -1)
        {
            var label = fullLine[..colonIndex];
            context.AddLabel(label, offset);

            if (!isAnimMode)
                continue;

            var index = scriptLabels.FindIndex(l => l == label);
            if (index < 0)
                continue;

            while (scriptLabelOffsets.Count <= index)
                scriptLabelOffsets.Add(-1);

            scriptLabelOffsets[index] = offset;
            continue;
        }

        var debug = fullLine.StartsWith('[');
        var line = fullLine[(debug ? 8 : 0)..].Replace('\t', ' ').Trim();

        // Empty line or comment
        if (line.Length < 3 || line.StartsWith("//"))
            continue;

        var openParaIndex = line.IndexOf('(');
        if (openParaIndex == -1 || line.StartsWith("0x"))
        {
            // Data
            scriptLines.Add(new ScriptLineData(offset, line));
            offset += line.StartsWith("0x") ? 2 : 4;
            continue;
        }

        var funcName = line[..openParaIndex].Trim();
        var scriptFunc = scriptFuncLibrary.GetScriptFunc(funcName);

        if (scriptFunc == null)
            throw new Exception();

        var closeParaIndex = line.IndexOf(')');
        if (closeParaIndex == -1)
            throw new Exception();

        var args = line.Substring(openParaIndex + 1, closeParaIndex - openParaIndex - 1).Split(',', StringSplitOptions.TrimEntries);
        scriptLines.Add(new ScriptLineFunc(offset, scriptFunc, args));
        offset += scriptFunc.Size;
    }

    var buffer = new byte[offset];

    if (isAnimMode)
    {
        BitConverter.TryWriteBytes(buffer.AsSpan(), scriptLabels.Count);

        for (var i = 0; i < scriptLabels.Count; i++)
        for (var j = 0; j < 14; j++)
            BitConverter.TryWriteBytes(buffer.AsSpan(4 + i * 0x38 + j * 4), scriptLabelOffsets[i]);
    }

    foreach (var scriptLine in scriptLines)
        scriptLine.Write(buffer, context);

    return buffer;
}