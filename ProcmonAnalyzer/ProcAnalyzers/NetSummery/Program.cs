using System;
using System.IO;

namespace NetSummery
{
    class Program
    {
        static void Main(string[] args)
        {
            if( args.Length < 1 )
            {
                Console.WriteLine("Please provide the PML file");
                return;
            }

            var procMonfilename = args[0];
            Console.WriteLine("Processing Procmon file");

            if( !File.Exists(procMonfilename) )
            {
                Console.WriteLine("Provide a valid path");
                return;
            }

            ProcmonXMLConverter converter = new ProcmonXMLConverter(procMonfilename);
            Console.Write("XML File Path:");
            Console.WriteLine(converter.GetXMLPath());
        }
    }
}
