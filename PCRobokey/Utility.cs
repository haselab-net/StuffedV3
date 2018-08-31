using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Robokey
{
    class Utility
    {
        [System.Runtime.InteropServices.DllImport("msvcrt.dll")]
        public static extern uint _control87(uint a, uint b);

        [System.Runtime.InteropServices.DllImport("msvcrt.dll")]
        public static extern uint _clearfp();

        public static uint cwOrg = _control87(0, 0);
        public static void TurnOnFpuException()
        {
            // Now turn on floating-point exceptions
            uint empty = 0;
            uint cw = _control87(empty, empty); // Debugger halts on this one and complains about false signature, but continue works.
            cwOrg = cw;
            //System.Console.WriteLine(cw.ToString());
            uint MCW_EM = 0x0008001f; // From float.h
            uint _EM_INVALID = 0x00000010; // From float.h (invalid corresponds to NaN
            // See http://www.fortran-2000.com/ArnaudRecipes/CompilerTricks.html#x86_FP
            cw &= ~(_EM_INVALID);
            _clearfp(); // Clear floating point error word.
            _control87(cw, MCW_EM); // Debugger halts on this one and complains about false signature, but continue works.      
            //System.Console.WriteLine(cw.ToString());
        }
        public static void TurnOffFpuException()
        {
            _control87(0xFFFFFFFF, cwOrg); // Debugger halts on this one and complains about false signature, but continue works.      
        }
        public static bool CheckDouble(double d)
        {
            bool nan = double.IsNaN(d);
            bool inf = double.IsInfinity(d);
            if (nan || inf)
            {
                System.Diagnostics.Debugger.Break();
                return false;
            }
            return true;
        }
    }
}
