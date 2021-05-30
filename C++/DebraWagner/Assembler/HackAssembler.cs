using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace Project5.Assembler
{
    public class HackAssembler
    {
        private readonly string _filename;

        public HackAssembler(string filename)
        {
            _filename = filename;
        }

        public List<string> Run()
        {
            var inputLines = File.ReadLines(_filename);

            var outputLines = new List<string>();

            var listOfErrors = new List<string>();

            var memoryTable = new Dictionary<string, int>();

            var memoryCounter = 16;

            // First pass
            foreach (var line in inputLines)
            {
                var trimmedLine = line.Trim();
                if (trimmedLine == string.Empty)
                {
                    continue;
                }

                if (trimmedLine[0] == '(' && trimmedLine[trimmedLine.Length - 1] == ')')
                {
                    var label = trimmedLine.Substring(1, trimmedLine.Length - 1);
                    memoryTable.Add(label, memoryCounter++);
                }
            }

            // Second pass
            var lineCounter = 0;
            foreach (var line in inputLines)
            {
                lineCounter++;

                var trimmedLine = line.Trim();

                if (trimmedLine == string.Empty)
                {
                    continue;
                }

                // A-Instruction: @R0, @R1, ..., @R15, @SCREEN, @KBD, @LABEL
                if (line[0] == '@')
                {
                    int memoryAddress;

                    var identifier = line.Substring(1);
                    if (identifier == string.Empty)
                    {
                        Console.WriteLine($"ERROR: Wrong input on line {lineCounter}.");
                    }

                    if (identifier[0] == 'R')
                    {
                        var rNumber = identifier.Substring(1);
                        if (int.TryParse(rNumber, out var number) && number >= 0 && number <= 15)
                        {
                            memoryAddress = number;

                        }
                        else




                    }
                }

            }

            return listOfErrors;
        }
    }
}
