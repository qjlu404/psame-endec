using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace ConsoleApp1
{

    
    class Program
    {
        [DllImport("../x64/Encoder.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void encode(string alert, bool attn, int attntime, int delaybeforetone,
                                         int delaybefore, int delayafter, int delayend);
        static void Main(string[] args)
        {
            
            encode(args[0], true, 1, 1, 1, 1, 1);
        }
    }
}
