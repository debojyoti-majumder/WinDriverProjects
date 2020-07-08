using System.Security.Principal;
using System;

namespace NetSummery
{
    class ProcmonLocator
    {
        public ProcmonLocator()
        {
            var user = WindowsIdentity.GetCurrent().User;
            var sid = user.Value;

            // The registry key loopup would be done based on this
            Console.WriteLine("User SID: {0}", sid);
        }
        
        public string GetExePath()
        {
            return "";
        }
    }
}
