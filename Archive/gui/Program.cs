using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace gui
{
    class Program
    {
        [DllImport("Encoder.dll", ExactSpelling=true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ezencodebin(bool[] alert, bool[] pream, bool[] eom);
        public static List<bool> S2B(string data)
        {
            StringBuilder sb = new StringBuilder();

            foreach (char c in data.ToCharArray())
            {
                sb.Append(Convert.ToString(c, 2).PadLeft(8, '0'));
            }
            string a = sb.ToString();
            List<bool> thelist = new List<bool>();
            foreach (char c in a.ToCharArray())
            {
                if (c == '0')
                {
                    thelist.Add(false);
                }
                else
                {
                    thelist.Add(true);
                }
            }
            return thelist;
        }
        static void Main(string[] args)
        {
            List<bool> al = S2B("zczc-wxr-tor-08134-fvrwc4c-4c4wef-wrefw-efwerc-cw");
            List<bool> pr = S2B("\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab");
            List<bool> eom = S2B("NNNN");
            bool[] baal = al.ToArray();
            bool[] bapr = pr.ToArray();
            bool[] baeom = eom.ToArray();
            ezencodebin(baal, bapr, baeom);
        }
    }
}