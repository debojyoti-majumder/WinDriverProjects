using System.IO;

namespace NetSummery
{
    class ProcmonXMLConverter
    {
        public ProcmonXMLConverter(string pathName)
        {
            var locator = new ProcmonLocator();
            locator.GetExePath();
        }

        public string GetXMLPath()
        {
            return "";
        }
    }
}
