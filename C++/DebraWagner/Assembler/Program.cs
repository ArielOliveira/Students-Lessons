using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*

    (LABEL)
    @R0 --> 0000000000000000
    @R5 --> 0000000000000101
    
    @LABEL --> 0000000000010000

    (END)
    @R7 --> 0000000000000111
    D=M --> 1111011011110000 (?)
    @R1 -->
    D=D+M
    @SCREEN --> (16348) 
    @KBD --> (24123)

    


    LABEL --> 16
    END --> 17

 */

namespace Project5.Assembler
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("You have to specify a single parameter.");
                return;
            }

            var filename = args[0];

            var hackAssembler = new HackAssembler(filename);
            var listOfErrors = hackAssembler.Run();
            if (listOfErrors.Any())
            {
                Console.WriteLine("Compilation resulted in the following errors:");
                foreach (var error in listOfErrors)
                {
                    Console.WriteLine(error);
                }
            }
            else
            {
                Console.WriteLine($"The file {filename} was compiled successfully.");
            }
        }
    }
}
